// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: BaseVertShader.vsh ********

// File data
static const char _BaseVertShader_vsh[] = 
	"/*\r\n"
	"  Simple vertex shader:\r\n"
	"  - standard vertex transformation\r\n"
	"  - diffuse lighting for one directional light\r\n"
	"  - texcoord passthrough\r\n"
	"*/\r\n"
	"\r\n"
	"attribute highp   vec3  inVertex;\r\n"
	"attribute mediump vec3  inNormal;\r\n"
	"attribute mediump vec2  inTexCoord;\r\n"
	"\r\n"
	"uniform highp   mat4  MVPMatrix;\r\n"
	"uniform mediump vec3  LightPosModel;\r\n"
	"\r\n"
	"varying lowp    float  LightIntensity;\r\n"
	"varying mediump vec2   TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\tgl_Position = MVPMatrix * vec4(inVertex, 1.0);\r\n"
	"\t\r\n"
	"\tmediump vec3 lightDir = normalize(LightPosModel - inVertex);\r\n"
	"\tLightIntensity = max(0.0, dot(inNormal, lightDir));\r\n"
	"\t\r\n"
	"\tTexCoord = inTexCoord;\r\n"
	"}\r\n";

// Register BaseVertShader.vsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_BaseVertShader_vsh("BaseVertShader.vsh", _BaseVertShader_vsh, 620);

// ******** End: BaseVertShader.vsh ********

