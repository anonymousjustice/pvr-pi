// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: BWFragShader.fsh ********

// File data
static const char _BWFragShader_fsh[] = 
	"uniform sampler2D  sTexture;\r\n"
	"\r\n"
	"varying lowp    float  LightIntensity;\r\n"
	"varying mediump vec2   TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\tlowp vec3 fCol = texture2D(sTexture, TexCoord).rgb;\r\n"
	"\tlowp float fAvg = (fCol.r + fCol.g + fCol.b) / 3.0;\r\n"
	"    gl_FragColor.rgb = vec3(fAvg * LightIntensity);\r\n"
	"    gl_FragColor.a = 1.0;\r\n"
	"}\r\n";

// Register BWFragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_BWFragShader_fsh("BWFragShader.fsh", _BWFragShader_fsh, 315);

// ******** End: BWFragShader.fsh ********

