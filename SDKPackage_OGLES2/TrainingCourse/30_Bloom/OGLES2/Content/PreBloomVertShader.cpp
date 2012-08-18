// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: PreBloomVertShader.vsh ********

// File data
static const char _PreBloomVertShader_vsh[] = 
	"attribute highp   vec3  inVertex;\r\n"
	"attribute mediump vec3  inNormal;\r\n"
	"attribute mediump vec2  inTexCoord;\r\n"
	"\r\n"
	"uniform highp   mat4  MVPMatrix;\r\n"
	"uniform mediump vec3  LightDirection;\r\n"
	"\r\n"
	"varying mediump vec2   TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\t// Transform position\r\n"
	"\tgl_Position = MVPMatrix * vec4(inVertex, 1.0);\t\r\n"
	"\r\n"
	"\t// Use the light intensity as texture coords for the bloom mapping\r\n"
	"\tTexCoord = vec2(dot(inNormal, -LightDirection), 0);\t\r\n"
	"}";

// Register PreBloomVertShader.vsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_PreBloomVertShader_vsh("PreBloomVertShader.vsh", _PreBloomVertShader_vsh, 437);

// ******** End: PreBloomVertShader.vsh ********

