# Microsoft Developer Studio Project File - Name="BearBearVideo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BearBearVideo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BearBearVideo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BearBearVideo.mak" CFG="BearBearVideo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BearBearVideo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BearBearVideo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BearBearVideo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Vfw32.lib msimg32.lib Winmm.lib Key.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "BearBearVideo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Vfw32.lib msimg32.lib Winmm.lib Key.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "BearBearVideo - Win32 Release"
# Name "BearBearVideo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AD.cpp
# End Source File
# Begin Source File

SOURCE=.\BearBearVideo.cpp
# End Source File
# Begin Source File

SOURCE=.\BearBearVideo.rc
# End Source File
# Begin Source File

SOURCE=.\BearBearVideoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\timerdialog\beautifulcanlendarmonthcombo.cpp
# End Source File
# Begin Source File

SOURCE=.\timerdialog\beautifulcanlendaryearcombox.cpp
# End Source File
# Begin Source File

SOURCE=.\timerdialog\BeautifulDateTimePicker.cpp
# End Source File
# Begin Source File

SOURCE=.\timerdialog\Calendar.cpp
# End Source File
# Begin Source File

SOURCE=.\DarwDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawButton.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawTab.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\HideDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MakeVideo.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuButton.cpp
# End Source File
# Begin Source File

SOURCE=.\NewButton.cpp
# End Source File
# Begin Source File

SOURCE=.\Set.cpp
# End Source File
# Begin Source File

SOURCE=.\SetLZ.cpp
# End Source File
# Begin Source File

SOURCE=.\SetTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\SetWave.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\Soft.cpp
# End Source File
# Begin Source File

SOURCE=.\Spy.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticHttp.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\VideoEncodeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoShow.cpp
# End Source File
# Begin Source File

SOURCE=.\webbrowser.cpp
# End Source File
# Begin Source File

SOURCE=.\timerdialog\XPGroupBox.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AD.h
# End Source File
# Begin Source File

SOURCE=.\BearBearVideo.h
# End Source File
# Begin Source File

SOURCE=.\BearBearVideoDlg.h
# End Source File
# Begin Source File

SOURCE=.\timerdialog\beautifulcanlendarmonthcombo.h
# End Source File
# Begin Source File

SOURCE=.\timerdialog\beautifulcanlendaryearcombox.h
# End Source File
# Begin Source File

SOURCE=.\timerdialog\BeautifulDateTimePicker.h
# End Source File
# Begin Source File

SOURCE=.\timerdialog\Calendar.h
# End Source File
# Begin Source File

SOURCE=.\DarwDialog.h
# End Source File
# Begin Source File

SOURCE=.\DrawButton.h
# End Source File
# Begin Source File

SOURCE=.\DrawEdit.h
# End Source File
# Begin Source File

SOURCE=.\DrawListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DrawTab.h
# End Source File
# Begin Source File

SOURCE=.\DrawToolBar.h
# End Source File
# Begin Source File

SOURCE=.\HideDialog.h
# End Source File
# Begin Source File

SOURCE=.\MakeVideo.h
# End Source File
# Begin Source File

SOURCE=.\MenuButton.h
# End Source File
# Begin Source File

SOURCE=.\NewButton.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Set.h
# End Source File
# Begin Source File

SOURCE=.\SetLZ.h
# End Source File
# Begin Source File

SOURCE=.\SetTimer.h
# End Source File
# Begin Source File

SOURCE=.\SetWave.h
# End Source File
# Begin Source File

SOURCE=.\ShowWindow.h
# End Source File
# Begin Source File

SOURCE=.\Soft.h
# End Source File
# Begin Source File

SOURCE=.\Spy.h
# End Source File
# Begin Source File

SOURCE=.\StaticHttp.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\VideoEncodeDlg.h
# End Source File
# Begin Source File

SOURCE=.\VideoShow.h
# End Source File
# Begin Source File

SOURCE=.\webbrowser.h
# End Source File
# Begin Source File

SOURCE=.\WriteAVI.h
# End Source File
# Begin Source File

SOURCE=.\timerdialog\XPGroupBox.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\10.cur
# End Source File
# Begin Source File

SOURCE=.\res\8.ico
# End Source File
# Begin Source File

SOURCE=.\res\9.ico
# End Source File
# Begin Source File

SOURCE=.\res\BearBearVideo.ico
# End Source File
# Begin Source File

SOURCE=.\res\BearBearVideo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\bg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BG_MENU_HILIGHT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BondiBlue.ico
# End Source File
# Begin Source File

SOURCE=.\res\btn_select.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Common.bmp
# End Source File
# Begin Source File

SOURCE=.\res\del.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Hand.cur
# End Source File
# Begin Source File

SOURCE=".\res\Home-Movie.ico"
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\IDB_PUSH_BUTTON_HOVER.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_PUSH_BUTTON_NORMAL.bmp
# End Source File
# Begin Source File

SOURCE=.\res\open.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pause.bmp
# End Source File
# Begin Source File

SOURCE=.\res\QuickCamExpress.ico
# End Source File
# Begin Source File

SOURCE=.\res\resrc_btn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\start.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TabButton.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tabunsel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Î´ÃüÃû.bmp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section BearBearVideo : {D30C1661-CDAF-11D0-8A3E-00C04FC9E26E}
# 	2:5:Class:CWebBrowser
# 	2:10:HeaderFile:webbrowser.h
# 	2:8:ImplFile:webbrowser.cpp
# End Section
# Section BearBearVideo : {8856F961-340A-11D0-A96B-00C04FD705A2}
# 	2:21:DefaultSinkHeaderFile:webbrowser.h
# 	2:16:DefaultSinkClass:CWebBrowser
# End Section
