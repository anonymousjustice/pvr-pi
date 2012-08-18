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
	"attribute highp vec4  inVertex;\r\n"
	"attribute highp vec3  inNormal;\r\n"
	"attribute highp vec2  inTexCoord;\r\n"
	"attribute highp vec3  inTangent;\r\n"
	"\r\n"
	"uniform highp mat4  MVPMatrix;\t\t// model view projection transformation\r\n"
	"uniform highp vec3  LightPosModel;\t// Light position (point light) in model space\r\n"
	"\r\n"
	"varying lowp vec3  LightVec;\r\n"
	"varying mediump vec2  TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\t// Transform position\r\n"
	"\tgl_Position = MVPMatrix * inVertex;\r\n"
	"\t\r\n"
	"\t// Calculate light direction from light position in model space\r\n"
	"\t// You can skip this step for directional lights\r\n"
	"\thighp vec3 lightDirection = normalize(LightPosModel - vec3(inVertex));\r\n"
	"\t\r\n"
	"\t// transform light direction from model space to tangent space\r\n"
	"\thighp vec3 bitangent = cross(inNormal, inTangent);\r\n"
	"\thighp mat3 tangentSpaceXform = mat3(inTangent, bitangent, inNormal);\r\n"
	"\tLightVec = lightDirection * tangentSpaceXform;\r\n"
	"\t\r\n"
	"\tTexCoord = inTexCoord;\r\n"
	"}\r\n";

// Register VertShader.vsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_VertShader_vsh("VertShader.vsh", _VertShader_vsh, 903);

// ******** End: VertShader.vsh ********

