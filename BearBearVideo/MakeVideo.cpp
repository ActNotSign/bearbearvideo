// MakeVideo.cpp: implementation of the CMakeVideo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bearbearvideo.h"
#include "MakeVideo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CMakeVideo::CMakeVideo()
{
	nFrames=0;
	psA=NULL;
	in=NULL;
}

CMakeVideo::~CMakeVideo()
{

}
HBITMAP  CMakeVideo::CatchBitmap(LPRECT lpRect)
{
	HDC hScrDC, hMemDC;      
	// 屏幕和内存设备描述表
	HBITMAP hBitmap,hOldBitmap;   
	// 位图句柄
	int       nX, nY, nX2, nY2,xScrn,yScrn;      
	// 选定区域坐标
	int       nWidth, nHeight;      
	// 位图宽度和高度
      
	// 屏幕分辨率
	// 确保选定区域不为空矩形
	if (IsRectEmpty(lpRect))
		return NULL;
	//为屏幕创建设备描述表
	hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	//为屏幕设备描述表创建兼容的内存设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);
	// 获得选定区域坐标
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	// 获得屏幕分辨率
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//确保选定区域是可见的
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;
	if (nX2 > xScrn)
		nX2 = xScrn;
	if (nY2 > yScrn)
		nY2 = yScrn;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	// 创建一个与屏幕设备描述表兼容的位图
	hBitmap=CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
	// 把新位图选到内存设备描述表中

	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中
	BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC, nX, nY, SRCCOPY);
	//得到屏幕位图的句柄
	hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);
	//清除 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);


	// 返回位图句柄
	return hBitmap;
}

void CMakeVideo::MakeAvi(CString FName,int times,CString filename,BOOL isAudio)
{
	
	AVIFileInit(); 
	int hr; 

	FILE *fp = fopen(filename,"rb");

	if(fp==NULL)
	{
		AfxMessageBox("打开BID失败");
		exit(1);
		
	}
	BITMAPFILEHEADER bmpFileHdr;
	BITMAPINFOHEADER bmpInfoHdr;
	fseek( fp,0,SEEK_SET);
	fread(&bmpFileHdr,sizeof(BITMAPFILEHEADER),1, fp);
	fread(&bmpInfoHdr,sizeof(BITMAPINFOHEADER),1, fp);



	BYTE *tmp_buf = NULL;
	if(nFrames ==0 )
	{
		//流信息
		AVISTREAMINFO strhdr,shrhdrAuido;

		hr =AVIFileOpen(&pfile,FName,OF_WRITE | OF_CREATE,NULL);
		if(hr!=0)
		{
			AfxMessageBox("创建avi文件失败");
			exit(1);
		}
		memset(&strhdr, 0, sizeof(strhdr));
		strhdr.fccType = streamtypeVIDEO ;// stream type
		strhdr.fccHandler = 0;
		strhdr.dwScale = 1;
		strhdr.dwRate = times; // 15 fps
		strhdr.dwSuggestedBufferSize = bmpInfoHdr.biSizeImage ;
		hr=SetRect(&strhdr.rcFrame, 0, 0, bmpInfoHdr.biWidth, bmpInfoHdr.biHeight);
		if(hr==0)
		{
			AfxMessageBox("图片框架设置失败");
			exit(1);
		}
		// And create the stream;
		hr = AVIFileCreateStream(pfile,&ps,&strhdr); 
		if(hr!=0)
		{
			AfxMessageBox("视频流创建失败");
			exit(1);
		}
		//视频压缩流
		AVICOMPRESSOPTIONS opts;
		opts.fccHandler   =   mmioFOURCC('M', 'S', 'V', 'C');   
		opts.dwQuality   =   6600;     //100%   quality,   9000   would   be   90%,   etc.   
		opts.dwFlags   =   7;   
		opts.lpParms   =   (LPVOID*)GlobalAlloc(NULL,4);   
		opts.cbParms   =   4;   
		*((long*)opts.lpParms)=75;   
		AVIMakeCompressedStream(&psCompressed,ps,&opts,NULL);

	//音频流
		/**/
			
		memset(&shrhdrAuido, 0, sizeof(shrhdrAuido));
		
		shrhdrAuido.fccType = streamtypeAUDIO ;// stream type
		shrhdrAuido.dwScale = 2;
		shrhdrAuido.dwRate = m_freq; // 15 fps
		//	shrhdrAuido.dwSuggestedBufferSize = (LONG)hdr->dwBytesRecorded ;
		//create audio stream
		hr = AVIFileCreateStream(pfile,&psA,&shrhdrAuido); 
		if(hr!=0)
		{
			AfxMessageBox("视频流创建失败");
			exit(1);
		}
		
	}
//write video stream
	tmp_buf = new BYTE[bmpInfoHdr.biWidth * bmpInfoHdr.biHeight * 10];
	fread(tmp_buf, 1, bmpInfoHdr.biWidth * bmpInfoHdr.biHeight * 10, fp);

	hr = AVIStreamSetFormat(psCompressed,nFrames,&bmpInfoHdr,sizeof(bmpInfoHdr));

	hr = AVIStreamWrite(psCompressed, // stream pointer
		nFrames , // time of this frame
		1, // number to write
		(LPBYTE)tmp_buf,
		bmpInfoHdr.biSizeImage ,
		AVIIF_KEYFRAME, // flags....
		NULL,
		NULL);

	nFrames ++; 
	fclose(fp);

	delete [] tmp_buf;
/*write audio stream*/
	if(isAudio==TRUE)
	{
		hr = AVIStreamSetFormat(psA,nFrames,&waveformat,sizeof(waveformat));
		hr = AVIStreamWrite(psA, // stream pointer
			nFrames , // time of this frame
			1, // number to write
			(HPSTR)hdr->lpData ,
			(LONG)hdr->dwBytesRecorded  ,
			AVIIF_KEYFRAME, // flags....
			NULL,
			NULL);
		nFrames ++; 

		hdr->lpData =NULL;
	}

}

void CMakeVideo::SavePicture(HBITMAP hBitmap,CString lpFileName)
{
    HDC hDC =::CreateDC("DISPLAY",NULL,NULL,NULL); 
    int iBits = ::GetDeviceCaps(hDC, BITSPIXEL) * ::GetDeviceCaps(hDC, PLANES);//当前分辨率下每个像素所占字节数  
    ::DeleteDC(hDC);
	
    WORD   wBitCount;   //位图中每个像素所占字节数    
    if (iBits <= 1)
		wBitCount = 1;
    else if (iBits <= 4)
		wBitCount = 4;
    else if (iBits <= 8)
		wBitCount = 8;
    else if (iBits <= 24)
		wBitCount = 24;
    else
		wBitCount = iBits;
	
	DWORD   dwPaletteSize=0; //调色板大小， 位图中像素字节大小 
    if (wBitCount <= 8)  
		dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD); 
	
	
	BITMAP  bm;        //位图属性结构
    ::GetObject(hBitmap, sizeof(bm), (LPSTR)&bm);  
	
    
	BITMAPINFOHEADER   bi;       //位图信息头结构     
	bi.biSize            = sizeof(BITMAPINFOHEADER);  
    bi.biWidth           = bm.bmWidth;
    bi.biHeight          = bm.bmHeight;
    bi.biPlanes          = 1;
    bi.biBitCount        = wBitCount;
    bi.biCompression     = BI_RGB;//BI_RGB; //BI_RGB表示位图没有压缩
    bi.biSizeImage       = 0;
    bi.biXPelsPerMeter   = 0;
    bi.biYPelsPerMeter   = 0;
    bi.biClrUsed         = 0;
    bi.biClrImportant    = 0;
	
    DWORD dwBmBitsSize = ((bm.bmWidth * wBitCount+31)/32) * 4 * bm.bmHeight;    
    HANDLE hDib  = ::GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));  //为位图内容分配内存
    LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
    *lpbi = bi;
	
    HANDLE hPal = ::GetStockObject(DEFAULT_PALETTE);  // 处理调色板 
	HANDLE  hOldPal=NULL; 
    if (hPal)
    {
		hDC = ::GetDC(NULL);
		hOldPal = SelectPalette(hDC,(HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
    }
    ::GetDIBits(hDC, hBitmap, 0, (UINT) bm.bmHeight,(LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize,(BITMAPINFO*)lpbi,DIB_RGB_COLORS);// 获取该调色板下新的像素值
    if (hOldPal)//恢复调色板
    {
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
    } 
	
	BITMAPFILEHEADER   bmfHdr; //位图文件头结构     
	bmfHdr.bfType = 0x4D42;  // "BM"   // 设置位图文件头
	DWORD dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;  
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	
	HANDLE hFile = CreateFile(lpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);//创建位图文件   
	DWORD dwWritten;
	WriteFile(hFile, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL); // 写入位图文件头
	WriteFile(hFile, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);// 写入位图文件其余内容
	
	GlobalUnlock(hDib);   //清除   
	GlobalFree(hDib);
	CloseHandle(hFile);  
	::DeleteObject (hBitmap);
}

void CMakeVideo::Stop(CString filename,CString filepath,CString picname,HWND hWnd)
{
	if(hWnd!=NULL)
	{
		capSetCallbackOnVideoStream(hWnd,NULL);
	}
	if(ps!=NULL)
	{
		AVIStreamClose(ps);
		ps=NULL;
	}

	if(psCompressed!=NULL)
	{
		AVIStreamClose(psCompressed);
		psCompressed=NULL;

	}

	if(psA!=NULL)
	{
		AVIStreamClose(psA);
		psA=NULL;
	};
	if(pfile != NULL)
	{
		AVIFileRelease(pfile);
		pfile=NULL;
	}
	//删除图片文件
	AVIFileExit();
	
	::DeleteFile (picname);
//退出录音
	if(in!=NULL)
	{
		waveInStop(in);
		waveInClose(in);
//		free(buf);
		in=NULL;
	}
}

void CMakeVideo::RecordWave(int sampsize, int freq,HWND hwnd)
{
	//初始化
	m_sampsize=sampsize;
	m_freq=freq;
	//录制的时间长度秒为单位
	size=freq*(4/3) ;

//	buf=(PBYTE)malloc(size);
//	oldptr=buf;
//	memset(buf,0,sizeof(BYTE));
	waveformat.nChannels=2;
	waveformat.wFormatTag=WAVE_FORMAT_PCM;
	waveformat.cbSize=0;
	waveformat.wBitsPerSample=sampsize;
	waveformat.nSamplesPerSec=freq;
	waveformat.nBlockAlign=waveformat.nChannels*(waveformat.wBitsPerSample/8);
	waveformat.nAvgBytesPerSec=waveformat.nSamplesPerSec*waveformat.nBlockAlign;
	
	hdr=new WAVEHDR;
	hdr->dwBufferLength=size;
	hdr->lpData=(char*)buf;
	hdr->dwFlags=WHDR_BEGINLOOP | WHDR_ENDLOOP;
	hdr->dwLoops=1;
	hdr->lpNext=NULL;
	hdr->dwUser=0;
	hdr->dwBytesRecorded=0;
	hdr->reserved=0;

	waveInOpen(&in,0,&waveformat,(DWORD)hwnd,0,                   
                       CALLBACK_WINDOW);
	m_bClose=TRUE;
	waveInPrepareHeader(in,hdr,sizeof(WAVEHDR));
	waveInAddBuffer(in,hdr,sizeof(WAVEHDR));
	waveInStart(in);
}

void CMakeVideo::StopWave()
{
	waveInUnprepareHeader(in,hdr,sizeof(WAVEHDR));
}

void CMakeVideo::InitWave(LPMMIOPROC WaveIOProc)
{


	mmioInstallIOProc((FOURCC)mmioStringToFOURCC("WAV", 0),
										 WaveIOProc, MMIO_INSTALLPROC);
}



void CMakeVideo::SaveWave(CString tmp ,LPMMIOPROC WaveIOProc)
{


	HMMIO       hmmio; 
    MMCKINFO    ciRiffChunk; 
    MMCKINFO    ciSubChunk;
    MMIOINFO    mmioInfo;
	TCHAR file[100];
	if(m_bClose)
	{
		waveInStop(in);
		waveInClose(in);
		m_bClose=false;
	}

	mmioInfo.dwFlags     = 0;
    mmioInfo.fccIOProc   = mmioStringToFOURCC("WAV ", 0);
    mmioInfo.pIOProc     = WaveIOProc;

    mmioInfo.wErrorRet   = 0;
    mmioInfo.htask       = 0;
    mmioInfo.cchBuffer   = 0;
    mmioInfo.pchBuffer   = 0;
    mmioInfo.pchNext     = 0;
    mmioInfo.pchEndRead  = 0;
    mmioInfo.pchEndWrite = 0;
    mmioInfo.lBufOffset  = 0;
    mmioInfo.lDiskOffset = 0;
    mmioInfo.adwInfo[0]  = 0;
    mmioInfo.adwInfo[1]  = 0;
    mmioInfo.adwInfo[2]  = 0;
    mmioInfo.adwInfo[3]  = 0;
    mmioInfo.dwReserved1 = 0;
    mmioInfo.dwReserved2 = 0;
    mmioInfo.hmmio       = 0;

	wsprintf(file,_T("%s"),tmp);
	hmmio = mmioOpen(file, &mmioInfo, 
                     MMIO_CREATE | MMIO_WRITE | MMIO_ALLOCBUF);

	mmioSetBuffer(hmmio, NULL, size, 0); //设置大小

	mmioSeek(hmmio, 0, SEEK_SET); 
    ciRiffChunk.fccType   = mmioFOURCC('W', 'A', 'V', 'E');
    ciRiffChunk.cksize    = 0L;
    
	mmioCreateChunk(hmmio, &ciRiffChunk, MMIO_CREATERIFF);
	ciSubChunk.ckid   = mmioStringToFOURCC("fmt", 0);
    ciSubChunk.cksize = sizeof(WAVEFORMATEX)-2;
    
	mmioCreateChunk(hmmio, &ciSubChunk, 0);
    mmioWrite(hmmio, (HPSTR)&waveformat, sizeof(WAVEFORMATEX));
	mmioAscend(hmmio, &ciSubChunk, 0);
	ciSubChunk.ckid   = mmioStringToFOURCC("data", 0);
    ciSubChunk.cksize = size;//
    
	mmioCreateChunk(hmmio, &ciSubChunk, 0);
	mmioWrite(hmmio, (HPSTR)hdr->lpData,(LONG)hdr->dwBytesRecorded);
	mmioAscend(hmmio, &ciSubChunk, 0);
	mmioAscend(hmmio, &ciRiffChunk, 0);
	mmioFlush(hmmio, 0);
    mmioClose(hmmio, 0);
	if(m_bClose)
	{
		waveInStop(in);
		waveInClose(in);
		m_bClose=false;
	}

}



