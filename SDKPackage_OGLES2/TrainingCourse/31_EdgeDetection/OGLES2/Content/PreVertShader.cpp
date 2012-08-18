// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: PreVertShader.vsh ********

// File data
static const char _PreVertShader_vsh[] = 
	"attribute highp vec3 inVertex;\t\t// Vertex coordinates\r\n"
	"uniform highp   mat4 MVPMatrix;\t\t// Model/View/Position matrix\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\t// Assign and transform position of the vertex so it is viewed from the correct angle.\r\n"
	"\tgl_Position = MVPMatrix * vec4(inVertex, 1.0);\r\n"
	"}";

// Register PreVertShader.vsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_PreVertShader_vsh("PreVertShader.vsh", _PreVertShader_vsh, 276);

// ******** End: PreVertShader.vsh ********

