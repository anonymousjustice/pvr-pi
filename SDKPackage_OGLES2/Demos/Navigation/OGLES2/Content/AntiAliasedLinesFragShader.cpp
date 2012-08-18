// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: AntiAliasedLinesFragShader.fsh ********

// File data
static const char _AntiAliasedLinesFragShader_fsh[] = 
	"uniform mediump sampler2D  sTexture;\r\n"
	"uniform lowp    vec4       FlatColour;\r\n"
	"\r\n"
	"varying mediump vec2    TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\tlowp vec4 texcol = texture2D(sTexture, TexCoord);\r\n"
	"\tgl_FragColor = vec4(FlatColour.rgb * texcol.r, texcol.a);\r\n"
	"}\r\n";

// Register AntiAliasedLinesFragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_AntiAliasedLinesFragShader_fsh("AntiAliasedLinesFragShader.fsh", _AntiAliasedLinesFragShader_fsh, 248);

// ******** End: AntiAliasedLinesFragShader.fsh ********

