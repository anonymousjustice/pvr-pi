// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: PlaneTexFShader.fsh ********

// File data
static const char _PlaneTexFShader_fsh[] = 
	"uniform sampler2D\t\tTexture;\r\n"
	"\r\n"
	"uniform mediump vec2 \tRcpWindowSize;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\t\r\n"
	"\tmediump vec2 vTexCoord = gl_FragCoord.xy * RcpWindowSize;\r\n"
	"\tgl_FragColor = texture2D(Texture, vTexCoord);\r\n"
	"}\r\n";

// Register PlaneTexFShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_PlaneTexFShader_fsh("PlaneTexFShader.fsh", _PlaneTexFShader_fsh, 199);

// ******** End: PlaneTexFShader.fsh ********

