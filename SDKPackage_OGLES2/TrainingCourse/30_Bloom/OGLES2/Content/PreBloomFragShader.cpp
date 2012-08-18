// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: PreBloomFragShader.fsh ********

// File data
static const char _PreBloomFragShader_fsh[] = 
	"uniform sampler2D  sBloomMapping;\r\n"
	"\r\n"
	"uniform mediump float fBloomIntensity;\r\n"
	"\r\n"
	"varying mediump vec2 TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"    gl_FragColor = texture2D(sBloomMapping, TexCoord) * fBloomIntensity;\r\n"
	"}\r\n";

// Register PreBloomFragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_PreBloomFragShader_fsh("PreBloomFragShader.fsh", _PreBloomFragShader_fsh, 206);

// ******** End: PreBloomFragShader.fsh ********

