// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: ColShaderF.fsh ********

// File data
static const char _ColShaderF_fsh[] = 
	"uniform lowp vec4 vRGBA;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\tgl_FragColor = vRGBA;\r\n"
	"}";

// Register ColShaderF.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_ColShaderF_fsh("ColShaderF.fsh", _ColShaderF_fsh, 69);

// ******** End: ColShaderF.fsh ********

