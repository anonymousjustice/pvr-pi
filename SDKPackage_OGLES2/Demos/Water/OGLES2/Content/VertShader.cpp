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
	"attribute highp vec3  inVertex;\r\n"
	"\r\n"
	"uniform highp mat4  ModelViewMatrix;\r\n"
	"uniform highp mat4  MVPMatrix;\r\n"
	"uniform highp vec3  EyePosition;\t\t// Eye (aka Camera) positon in model-space\r\n"
	"uniform mediump vec2 BumpTranslation0;\r\n"
	"uniform mediump vec2 BumpScale0;\r\n"
	"uniform mediump vec2 BumpTranslation1;\r\n"
	"uniform mediump vec2 BumpScale1;\r\n"
	" \r\n"
	"varying mediump vec2 BumpCoord0;\r\n"
	"varying mediump vec2 BumpCoord1;\r\n"
	"varying mediump vec3\tWaterToEye;\r\n"
	"varying mediump float\tWaterToEyeLength;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\t// Convert each vertex into projection-space and output the value\r\n"
	"\thighp vec4 vInVertex = vec4(inVertex, 1.0);\r\n"
	"\tgl_Position = MVPMatrix * vInVertex;\r\n"
	"\r\n"
	"\t// The texture coordinate is calculated this way to reduce the number of attributes needed\r\n"
	"\tmediump vec2 vTexCoord = inVertex.xz;\r\n"
	"\r\n"
	"\t// Scale and translate texture coordinates used to sample the normal map - section 2.2 of white paper\r\n"
	"\tBumpCoord0 = vTexCoord.xy * BumpScale0;\r\n"
	"\tBumpCoord0 += BumpTranslation0;\r\n"
	"\t\r\n"
	"\tBumpCoord1 = vTexCoord.xy * BumpScale1;\r\n"
	"\tBumpCoord1 += BumpTranslation1;\r\n"
	"\t\r\n"
	"\t/* \t\r\n"
	"\t\tThe water to eye vector is used to calculate the Fresnel term\r\n"
	"\t\tand to fade out perturbations based on distance from the viewer\r\n"
	"\t*/\r\n"
	"\tWaterToEye = EyePosition - inVertex;\r\n"
	"\tWaterToEyeLength = length(WaterToEye);\r\n"
	"}\r\n";

// Register VertShader.vsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_VertShader_vsh("VertShader.vsh", _VertShader_vsh, 1274);

// ******** End: VertShader.vsh ********

