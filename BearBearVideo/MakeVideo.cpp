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
	// ��Ļ���ڴ��豸������
	HBITMAP hBitmap,hOldBitmap;   
	// λͼ���
	int       nX, nY, nX2, nY2,xScrn,yScrn;      
	// ѡ����������
	int       nWidth, nHeight;      
	// λͼ��Ⱥ͸߶�
      
	// ��Ļ�ֱ���
	// ȷ��ѡ������Ϊ�վ���
	if (IsRectEmpty(lpRect))
		return NULL;
	//Ϊ��Ļ�����豸������
	hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);
	// ���ѡ����������
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	// �����Ļ�ֱ���
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//ȷ��ѡ�������ǿɼ���
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
	// ����һ������Ļ�豸��������ݵ�λͼ
	hBitmap=CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
	// ����λͼѡ���ڴ��豸��������

	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC, nX, nY, SRCCOPY);
	//�õ���Ļλͼ�ľ��
	hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);
	//��� 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);


	// ����λͼ���
	return hBitmap;
}

void CMakeVideo::MakeAvi(CString FName,int times,CString filename,BOOL isAudio)
{
	
	AVIFileInit(); 
	int hr; 

	FILE *fp = fopen(filename,"rb");

	if(fp==NULL)
	{
		AfxMessageBox("��BIDʧ��");
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
		//����Ϣ
		AVISTREAMINFO strhdr,shrhdrAuido;

		hr =AVIFileOpen(&pfile,FName,OF_WRITE | OF_CREATE,NULL);
		if(hr!=0)
		{
			AfxMessageBox("����avi�ļ�ʧ��");
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
			AfxMessageBox("ͼƬ�������ʧ��");
			exit(1);
		}
		// And create the stream;
		hr = AVIFileCreateStream(pfile,&ps,&strhdr); 
		if(hr!=0)
		{
			AfxMessageBox("��Ƶ������ʧ��");
			exit(1);
		}
		//��Ƶѹ����
		AVICOMPRESSOPTIONS opts;
		opts.fccHandler   =   mmioFOURCC('M', 'S', 'V', 'C');   
		opts.dwQuality   =   6600;     //100%   quality,   9000   would   be   90%,   etc.   
		opts.dwFlags   =   7;   
		opts.lpParms   =   (LPVOID*)GlobalAlloc(NULL,4);   
		opts.cbParms   =   4;   
		*((long*)opts.lpParms)=75;   
		AVIMakeCompressedStream(&psCompressed,ps,&opts,NULL);

	//��Ƶ��
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
			AfxMessageBox("��Ƶ������ʧ��");
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
    int iBits = ::GetDeviceCaps(hDC, BITSPIXEL) * ::GetDeviceCaps(hDC, PLANES);//��ǰ�ֱ�����ÿ��������ռ�ֽ���  
    ::DeleteDC(hDC);
	
    WORD   wBitCount;   //λͼ��ÿ��������ռ�ֽ���    
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
	
	DWORD   dwPaletteSize=0; //��ɫ���С�� λͼ�������ֽڴ�С 
    if (wBitCount <= 8)  
		dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD); 
	
	
	BITMAP  bm;        //λͼ���Խṹ
    ::GetObject(hBitmap, sizeof(bm), (LPSTR)&bm);  
	
    
	BITMAPINFOHEADER   bi;       //λͼ��Ϣͷ�ṹ     
	bi.biSize            = sizeof(BITMAPINFOHEADER);  
    bi.biWidth           = bm.bmWidth;
    bi.biHeight          = bm.bmHeight;
    bi.biPlanes          = 1;
    bi.biBitCount        = wBitCount;
    bi.biCompression     = BI_RGB;//BI_RGB; //BI_RGB��ʾλͼû��ѹ��
    bi.biSizeImage       = 0;
    bi.biXPelsPerMeter   = 0;
    bi.biYPelsPerMeter   = 0;
    bi.biClrUsed         = 0;
    bi.biClrImportant    = 0;
	
    DWORD dwBmBitsSize = ((bm.bmWidth * wBitCount+31)/32) * 4 * bm.bmHeight;    
    HANDLE hDib  = ::GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));  //Ϊλͼ���ݷ����ڴ�
    LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
    *lpbi = bi;
	
    HANDLE hPal = ::GetStockObject(DEFAULT_PALETTE);  // �����ɫ�� 
	HANDLE  hOldPal=NULL; 
    if (hPal)
    {
		hDC = ::GetDC(NULL);
		hOldPal = SelectPalette(hDC,(HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
    }
    ::GetDIBits(hDC, hBitmap, 0, (UINT) bm.bmHeight,(LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize,(BITMAPINFO*)lpbi,DIB_RGB_COLORS);// ��ȡ�õ�ɫ�����µ�����ֵ
    if (hOldPal)//�ָ���ɫ��
    {
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
    } 
	
	BITMAPFILEHEADER   bmfHdr; //λͼ�ļ�ͷ�ṹ     
	bmfHdr.bfType = 0x4D42;  // "BM"   // ����λͼ�ļ�ͷ
	DWORD dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;  
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	
	HANDLE hFile = CreateFile(lpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);//����λͼ�ļ�   
	DWORD dwWritten;
	WriteFile(hFile, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL); // д��λͼ�ļ�ͷ
	WriteFile(hFile, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);// д��λͼ�ļ���������
	
	GlobalUnlock(hDib);   //���   
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
	//ɾ��ͼƬ�ļ�
	AVIFileExit();
	
	::DeleteFile (picname);
//�˳�¼��
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
	//��ʼ��
	m_sampsize=sampsize;
	m_freq=freq;
	//¼�Ƶ�ʱ�䳤����Ϊ��λ
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

	mmioSetBuffer(hmmio, NULL, size, 0); //���ô�С

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



