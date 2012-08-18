// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: PivotQuadFragShader.fsh ********

// File data
static const char _PivotQuadFragShader_fsh[] = 
	"uniform lowp    sampler2D  sTexture;\r\n"
	"uniform lowp    vec4       Colour;\r\n"
	"\r\n"
	"varying mediump vec2       TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{    \r\n"
	"\t// Multiply the texture colour with the constant colour\r\n"
	"\tgl_FragColor = texture2D(sTexture, TexCoord) * Colour;\t\r\n"
	"}\r\n";

// Register PivotQuadFragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_PivotQuadFragShader_fsh("PivotQuadFragShader.fsh", _PivotQuadFragShader_fsh, 255);

// ******** End: PivotQuadFragShader.fsh ********

