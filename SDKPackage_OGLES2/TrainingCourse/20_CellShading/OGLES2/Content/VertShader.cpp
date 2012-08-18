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
	"attribute highp   vec3  inVertex;\r\n"
	"attribute mediump vec3  inNormal;\r\n"
	"\r\n"
	"uniform highp mat4  MVPMatrix;\t\t// model view projection transformation\r\n"
	"uniform highp vec3  LightDirection;\t// light direction in model space\r\n"
	"uniform highp vec3  EyePosition;\t// eye position in model space\r\n"
	"\r\n"
	"varying mediump vec2  TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\tgl_Position = MVPMatrix * vec4(inVertex,1.0);\r\n"
	"\t\r\n"
	"\tmediump vec3 eyeDirection = normalize(EyePosition - inVertex);\r\n"
	"\t\r\n"
	"\tTexCoord.x = dot(LightDirection, inNormal);\r\n"
	"\tTexCoord.y = dot(eyeDirection, inNormal);\r\n"
	"}\r\n";

// Register VertShader.vsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_VertShader_vsh("VertShader.vsh", _VertShader_vsh, 546);

// ******** End: VertShader.vsh ********

