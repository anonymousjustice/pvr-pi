// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: PostBloomVertShader.vsh ********

// File data
static const char _PostBloomVertShader_vsh[] = 
	"attribute highp   vec2  inVertex;\r\n"
	"attribute mediump vec2  inTexCoord;\r\n"
	"\r\n"
	"varying mediump vec2   TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"    // Pass through vertex\r\n"
	"\tgl_Position = vec4(inVertex, 0.0, 1.0);\r\n"
	"\t\r\n"
	"\t// Pass through texcoords\r\n"
	"\tTexCoord = inTexCoord;\r\n"
	"}\r\n";

// Register PostBloomVertShader.vsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_PostBloomVertShader_vsh("PostBloomVertShader.vsh", _PostBloomVertShader_vsh, 255);

// ******** End: PostBloomVertShader.vsh ********

