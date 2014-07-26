// MakeVideo.h: interface for the CMakeVideo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAKEVIDEO_H__E70BC6D3_E9DD_4EF5_B52F_70656EEC61CC__INCLUDED_)
#define AFX_MAKEVIDEO_H__E70BC6D3_E9DD_4EF5_B52F_70656EEC61CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "vfw.h"
#include "Mmsystem.h"


class CMakeVideo  
{
public:

	void SaveWave(CString tmp,LPMMIOPROC WaveIOProc);
	void InitWave(LPMMIOPROC WaveIOProc);
	void StopWave();
	void RecordWave(int sampsize , int freq,HWND hwnd);
	void Stop(CString filename="",CString filepath="",CString picname="",HWND hWnd=NULL);
	CMakeVideo();
	virtual ~CMakeVideo();
	void SavePicture(HBITMAP hBitmap,CString pchFileName);
	void MakeAvi(CString pfile,int times,CString filename,BOOL isAudio=FALSE);
	HBITMAP  CatchBitmap(LPRECT lpRect);
	//HBITMAP 信息
	LPBITMAPINFOHEADER  lpbi ;
	LPBYTE              lpBits ;


	//视频帧数
	int nFrames;   

	//视频流

	PAVIFILE pfile;
	PAVISTREAM ps,psCompressed; 



//音频stream
	PAVISTREAM psA;

	WAVEFORMATEX waveformat;
	PWAVEHDR hdr;
	DWORD size;
	UINT wDeviceID;
	PBYTE buf;
	PBYTE oldptr;
	HWAVEIN in;
	BOOL m_bClose;
	int m_sampsize,m_freq;

	//摄像头图片格式
	BITMAPINFO     m_InInfo,m_OutInfo; //位图格式

};

#endif // !defined(AFX_MAKEVIDEO_H__E70BC6D3_E9DD_4EF5_B52F_70656EEC61CC__INCLUDED_)
