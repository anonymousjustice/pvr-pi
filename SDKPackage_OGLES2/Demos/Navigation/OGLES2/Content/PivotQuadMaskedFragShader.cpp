// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: PivotQuadMaskedFragShader.fsh ********

// File data
static const char _PivotQuadMaskedFragShader_fsh[] = 
	"uniform lowp    sampler2D  sTexture;\r\n"
	"uniform lowp    vec4       Colour;\r\n"
	"\r\n"
	"varying mediump vec2       TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{ \r\n"
	"\t// Write the constant colour and modulate the alpha with the intensity value from the texture   \r\n"
	"\tgl_FragColor = vec4(Colour.rgb, Colour.a * texture2D(sTexture, TexCoord).r);\r\n"
	"}\r\n";

// Register PivotQuadMaskedFragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_PivotQuadMaskedFragShader_fsh("PivotQuadMaskedFragShader.fsh", _PivotQuadMaskedFragShader_fsh, 314);

// ******** End: PivotQuadMaskedFragShader.fsh ********

