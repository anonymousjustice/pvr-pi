/******************************************************************************

 @File         PVRShellOS.h

 @Title        LinuxX11/PVRShellOS

 @Version      

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     Linux X11

 @Description  Makes programming for 3D APIs easier by wrapping surface
               initialization, Texture allocation and other functions for use by a demo.

******************************************************************************/
#ifndef _PVRSHELLOS_
#define _PVRSHELLOS_

#include "X11/Xlib.h"
#include "X11/Xutil.h"
#ifdef BUILD_OGL
#include "X11/extensions/xf86vmode.h"
#endif

#define PVRSHELL_DIR_SYM	'/'
#define _stricmp strcasecmp

/*!***************************************************************************
 PVRShellInitOS
 @Brief Class. Interface with specific Operative System.
*****************************************************************************/
class PVRShellInitOS
{
public:
	Display*     m_X11Display;
	long         m_X11Screen;
	XVisualInfo* m_X11Visual;
	Colormap     m_X11ColorMap;
	Window       m_X11Window;
	timeval 	 m_StartTime;
#ifdef BUILD_OGL
    XF86VidModeModeLine m_OriginalMode;  // modeline that was active at the starting point of this aplication
    int         m_i32OriginalModeDotClock;
#endif

	// Pixmap support: variables for the pixmap
	Pixmap		m_X11Pixmap;
	GC			m_X11GC;

	float m_vec2PointerLocation[ 2 ];
	unsigned int m_u32ButtonState; // 1 = left, 2 = right, 4 = middle

public:
	int OpenX11Window(const PVRShell &shell);
	void CloseX11Window();
};

#endif /* _PVRSHELLOS_ */
/*****************************************************************************
 End of file (PVRShellOS.h)
*****************************************************************************/

