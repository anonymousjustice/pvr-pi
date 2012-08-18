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
	"\r\n"
	"uniform highp mat4   MVPMatrix;\r\n"
	"uniform highp vec3   EyePosition;\r\n"
	"uniform highp float  RIRSquare;\r\n"
	"\r\n"
	"varying mediump vec2   ReflectCoord;\r\n"
	"varying mediump vec2   TexCoord;\r\n"
	"varying lowp    float  ReflectRatio;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\t// Transform position\r\n"
	"\tgl_Position = MVPMatrix * inVertex;\r\n"
	"\t\r\n"
	"\t// Calculate direction from vertex to eye (model space)\r\n"
	"\thighp vec3 eyeDir = normalize(EyePosition - inVertex.xyz);\r\n"
	"\t\r\n"
	"\t// The reflection intensity depends on the angle between eye direction and\r\n"
	"\t// surface normal.\r\n"
	"\t// The relative index of refraction (RIR) is a material parameter\r\n"
	"\thighp float c = abs(dot(eyeDir, inNormal));\r\n"
	"\thighp float g = sqrt(RIRSquare + c * c - 1.0);\r\n"
	"\thighp float f1 = (g - c) / (g + c);\r\n"
	"\thighp float f2 = (c * (g + c) - 1.0) / (c * (g - c) + 1.0);\r\n"
	"\tReflectRatio = 0.5 * f1 * f1 * (1.0 + f2 * f2);\r\n"
	"\t\r\n"
	"\t// map reflection vector to 2D\r\n"
	"\tReflectCoord = normalize(reflect(eyeDir, inNormal)).xy * 0.5;\r\n"
	"\t\r\n"
	"\tTexCoord = inTexCoord;\r\n"
	"}\r\n";

// Register VertShader.vsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_VertShader_vsh("VertShader.vsh", _VertShader_vsh, 1063);

// ******** End: VertShader.vsh ********

