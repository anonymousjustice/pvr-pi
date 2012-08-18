/******************************************************************************

 @File         PVRShellOS.h

 @Title        LinuxEWS/PVRShellOS

 @Version       @Version      

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     Example Window System support for Linux

 @Description  Makes programming for 3D APIs easier by wrapping surface
               initialization, Texture allocation and other functions for use by a demo.

******************************************************************************/
#ifndef _PVRSHELLOS_
#define _PVRSHELLOS_

#include <termios.h>
#include <unistd.h>
#include <EWS/ews.h>

#define PVRSHELL_DIR_SYM	'/'
#define _stricmp strcasecmp

/*!***************************************************************************
 PVRShellInitOS
 @Brief Class. Interface with specific Operative System.
*****************************************************************************/
class PVRShellInitOS
{
public:
	EWS_DISPLAY m_EWSDisplay;
	EWS_WINDOW  m_EWSWindow;

	timeval 	 m_StartTime;
};

#endif /* _PVRSHELLOS_ */
/*****************************************************************************
 End of file (PVRShellOS.h)
*****************************************************************************/

