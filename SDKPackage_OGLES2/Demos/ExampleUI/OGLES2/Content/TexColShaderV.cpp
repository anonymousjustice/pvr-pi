// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: TexColShaderV.vsh ********

// File data
static const char _TexColShaderV_vsh[] = 
	"attribute highp vec3 inVertex;\r\n"
	"attribute highp vec2 inUVs;\r\n"
	"\r\n"
	"uniform mediump mat4 MVPMatrix;\r\n"
	"\r\n"
	"varying highp vec2 TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\tTexCoord = inUVs;\r\n"
	"\tgl_Position = MVPMatrix * vec4(inVertex, 1.0);\r\n"
	"}";

// Register TexColShaderV.vsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_TexColShaderV_vsh("TexColShaderV.vsh", _TexColShaderV_vsh, 216);

// ******** End: TexColShaderV.vsh ********

