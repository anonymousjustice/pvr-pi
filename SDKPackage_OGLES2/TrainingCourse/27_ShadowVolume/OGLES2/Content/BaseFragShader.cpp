// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: BaseFragShader.fsh ********

// File data
static const char _BaseFragShader_fsh[] = 
	"/*\r\n"
	"  Simple fragment shader:\r\n"
	"  - Single texturing modulated with vertex lighting\r\n"
	"*/\r\n"
	"\r\n"
	"uniform sampler2D sTexture;\r\n"
	"\r\n"
	"varying lowp    float LightIntensity;\r\n"
	"varying mediump vec2  TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"    gl_FragColor = vec4(texture2D(sTexture, TexCoord).rgb * LightIntensity, 1.0);\r\n"
	"}\r\n";

// Register BaseFragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_BaseFragShader_fsh("BaseFragShader.fsh", _BaseFragShader_fsh, 297);

// ******** End: BaseFragShader.fsh ********

