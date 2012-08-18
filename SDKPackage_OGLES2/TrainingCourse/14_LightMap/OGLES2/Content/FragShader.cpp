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
	"uniform sampler2D  sBasetex;\r\n"
	"uniform sampler2D  sReflect;\r\n"
	"uniform sampler2D  sShadow;\r\n"
	"\r\n"
	"varying mediump vec2   TexCoord;\r\n"
	"varying mediump vec3   ShadowCoord;\r\n"
	"varying mediump vec2   ReflectCoord;\r\n"
	"varying lowp    float  LightIntensity;\r\n"
	"\r\n"
	"const lowp float  cReflect = 0.2;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\tlowp vec3 baseColor = texture2D(sBasetex, TexCoord).rgb;\r\n"
	"\tbaseColor *= 0.2 + 0.8 * texture2DProj(sShadow, ShadowCoord).r * LightIntensity;\r\n"
	"\t\r\n"
	"\tlowp vec3 reflectColor = texture2D(sReflect, ReflectCoord).rgb;\r\n"
	"\r\n"
	"\tgl_FragColor = vec4(baseColor +  reflectColor * cReflect, 1.0);\r\n"
	"}";

// Register FragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_FragShader_fsh("FragShader.fsh", _FragShader_fsh, 575);

// ******** End: FragShader.fsh ********

