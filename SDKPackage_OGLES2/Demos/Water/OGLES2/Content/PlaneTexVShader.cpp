// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: PlaneTexVShader.vsh ********

// File data
static const char _PlaneTexVShader_vsh[] = 
	"attribute highp vec3  inVertex;\r\n"
	"\r\n"
	"uniform highp mat4  MVPMatrix;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\t// Convert each vertex into projection-space and output the value\r\n"
	"\thighp vec4 vInVertex = vec4(inVertex, 1.0);\r\n"
	"\tgl_Position = MVPMatrix * vInVertex;\r\n"
	"}\r\n";

// Register PlaneTexVShader.vsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_PlaneTexVShader_vsh("PlaneTexVShader.vsh", _PlaneTexVShader_vsh, 241);

// ******** End: PlaneTexVShader.vsh ********

