// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: VertShader.vsh ********

// File data
static const char _VertShader_vsh[] = 
	"attribute highp  vec2  inVertex;\r\n"
	"\r\n"
	"uniform highp vec2  LowerLeft;\r\n"
	"uniform highp mat2  ScaleMatrix; // width/height and screen rotation\r\n"
	"\r\n"
	"varying mediump vec2  TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\tgl_Position = vec4(ScaleMatrix * inVertex + LowerLeft, 0, 1);\r\n"
	"\t\r\n"
	"\tTexCoord = inVertex;\r\n"
	"}\r\n";

// Register VertShader.vsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_VertShader_vsh("VertShader.vsh", _VertShader_vsh, 284);

// ******** End: VertShader.vsh ********

