# Microsoft Developer Studio Project File - Name="DiO" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DiO - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DiO.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DiO.mak" CFG="DiO - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DiO - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DiO - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DiO - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /fo".\Release\DiO.res" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o".\Release\DiO.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386 /out:"..\_exe\DiO.exe" /libpath:"winmm.lib"

!ELSEIF  "$(CFG)" == "DiO - Win32 Debug"

# PROP BASE Use_MFC 5
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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /fo".\Debug\DiO.res" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o".\Debug\DiO.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\_exe\DiO.exe" /pdbtype:sept /libpath:"winmm.lib"

!ENDIF 

# Begin Target

# Name "DiO - Win32 Release"
# Name "DiO - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DiO.cpp
# End Source File
# Begin Source File

SOURCE=.\DiO.rc
# End Source File
# Begin Source File

SOURCE=.\DiODlg.cpp
# End Source File
# Begin Source File

SOURCE=.\InputSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\IPAddress.cpp
# End Source File
# Begin Source File

SOURCE=.\MySocket.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UserName.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Define.h
# End Source File
# Begin Source File

SOURCE=.\DiO.h
# End Source File
# Begin Source File

SOURCE=.\DiODlg.h
# End Source File
# Begin Source File

SOURCE=.\InputSettings.h
# End Source File
# Begin Source File

SOURCE=.\IPAddress.h
# End Source File
# Begin Source File

SOURCE=.\MySocket.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UserName.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ChainDn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DiO.ico
# End Source File
# Begin Source File

SOURCE=.\res\DiO.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Off.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OffG.bmp
# End Source File
# Begin Source File

SOURCE=.\res\On.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OnG.bmp
# End Source File
# Begin Source File

SOURCE=.\res\StartExt.bmp
# End Source File
# Begin Source File

SOURCE=.\res\X.bmp
# End Source File
# End Group
# Begin Group "RaspBerry"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=..\_exe\DiO.ini
# End Source File
# Begin Source File

SOURCE=..\_exe\DiO.SQL
# End Source File
# Begin Source File

SOURCE=..\Main.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\TestDiO.c

!IF  "$(CFG)" == "DiO - Win32 Release"

!ELSEIF  "$(CFG)" == "DiO - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
