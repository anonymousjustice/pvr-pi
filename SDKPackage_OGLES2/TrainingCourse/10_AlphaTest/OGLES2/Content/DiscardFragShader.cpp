// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: DiscardFragShader.fsh ********

// File data
static const char _DiscardFragShader_fsh[] = 
	"uniform sampler2D  sTexture;\r\n"
	"\r\n"
	"uniform lowp float  AlphaReference;\r\n"
	"\r\n"
	"varying mediump vec2  TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\tlowp vec4 color = texture2D(sTexture, TexCoord);\r\n"
	"\tif (color.a < AlphaReference) \r\n"
	"\t{\r\n"
	"\t\tdiscard;\r\n"
	"\t}\r\n"
	"\tgl_FragColor = color;\r\n"
	"}\r\n";

// Register DiscardFragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_DiscardFragShader_fsh("DiscardFragShader.fsh", _DiscardFragShader_fsh, 253);

// ******** End: DiscardFragShader.fsh ********

