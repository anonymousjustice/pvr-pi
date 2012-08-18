// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: AlphaMaskFragShader.fsh ********

// File data
static const char _AlphaMaskFragShader_fsh[] = 
	"uniform mediump sampler2D  sTexture;\r\n"
	"uniform lowp    vec4       FlatColour;\r\n"
	"\r\n"
	"varying mediump vec2    TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\t\r\n"
	"\tgl_FragColor = vec4(FlatColour.rgb, FlatColour.a * texture2D(sTexture, TexCoord).a);\t\t\r\n"
	"}\r\n";

// Register AlphaMaskFragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_AlphaMaskFragShader_fsh("AlphaMaskFragShader.fsh", _AlphaMaskFragShader_fsh, 226);

// ******** End: AlphaMaskFragShader.fsh ********

