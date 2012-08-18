// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: FragShader.fsh ********

// File data
static const char _FragShader_fsh[] = 
	"uniform sampler2D  sBaseTex;\r\n"
	"uniform sampler2D  sReflectTex;\r\n"
	"\r\n"
	"varying mediump vec2   ReflectCoord;\r\n"
	"varying mediump vec2   TexCoord;\r\n"
	"varying lowp    float  ReflectRatio;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\tlowp vec3 baseColor = vec3(texture2D(sBaseTex, TexCoord));\r\n"
	"\tlowp vec3 reflection = vec3(texture2D(sReflectTex, ReflectCoord));\r\n"
	"\tlowp vec3 color = mix(baseColor, reflection, ReflectRatio);\r\n"
	"\tgl_FragColor = vec4(color, 1.0);\r\n"
	"}\r\n";

// Register FragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_FragShader_fsh("FragShader.fsh", _FragShader_fsh, 423);

// ******** End: FragShader.fsh ********

