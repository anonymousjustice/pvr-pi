// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: SpriteShaderV.vsh ********

// File data
static const char _SpriteShaderV_vsh[] = 
	"attribute highp vec3 inVertex;\r\n"
	"attribute highp vec2 inUVs;\r\n"
	"attribute mediump float inTransIdx;\r\n"
	"attribute lowp vec4\t inRGBA;\r\n"
	"\r\n"
	"uniform mediump mat4 MTransforms[30];\r\n"
	"uniform mediump mat4 MVPMatrix;\r\n"
	"\r\n"
	"varying highp vec2 TexCoord;\r\n"
	"varying lowp vec4 RGBA;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\tTexCoord = inUVs;\r\n"
	"\tRGBA     = inRGBA;\r\n"
	"\t\r\n"
	"\tlowp int iTransIdx = int(inTransIdx);\r\n"
	"\thighp vec4 position = MTransforms[iTransIdx] * vec4(inVertex, 1.0);\r\n"
	"\t\t\r\n"
	"\tgl_Position = MVPMatrix * position;\r\n"
	"}";

// Register SpriteShaderV.vsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_SpriteShaderV_vsh("SpriteShaderV.vsh", _SpriteShaderV_vsh, 474);

// ******** End: SpriteShaderV.vsh ********

