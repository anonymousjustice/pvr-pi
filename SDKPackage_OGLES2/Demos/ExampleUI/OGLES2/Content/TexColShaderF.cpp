// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: TexColShaderF.fsh ********

// File data
static const char _TexColShaderF_fsh[] = 
	"uniform sampler2D Texture;\r\n"
	"uniform lowp vec4 vRGBA;\r\n"
	"\r\n"
	"varying highp vec2 TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\tgl_FragColor = texture2D(Texture, TexCoord) * vRGBA;\r\n"
	"}";

// Register TexColShaderF.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_TexColShaderF_fsh("TexColShaderF.fsh", _TexColShaderF_fsh, 160);

// ******** End: TexColShaderF.fsh ********

