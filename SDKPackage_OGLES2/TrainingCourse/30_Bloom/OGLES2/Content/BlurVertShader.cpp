// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: BlurVertShader.vsh ********

// File data
static const char _BlurVertShader_vsh[] = 
	"// Blur filter kernel shader\r\n"
	"//\r\n"
	"// 0  1  2  3  4\r\n"
	"// x--x--X--x--x    <- original filter kernel\r\n"
	"//   y---X---y      <- filter kernel abusing the hardware texture filtering\r\n"
	"//       |\r\n"
	"//      texel center\r\n"
	"//\r\n"
	"// \r\n"
	"// Using hardware texture filtering, the amount of samples can be\r\n"
	"// reduced to three. To calculate the offset, use this formula:\r\n"
	"// d = w1 / (w1 + w2),  whereas w1 and w2 denote the filter kernel weights\r\n"
	"\r\n"
	"attribute highp   vec3  inVertex;\r\n"
	"attribute mediump vec2  inTexCoord;\r\n"
	"\r\n"
	"uniform mediump float  TexelOffsetX;\r\n"
	"uniform mediump float  TexelOffsetY;\r\n"
	"\r\n"
	"varying mediump vec2  TexCoord0;\r\n"
	"varying mediump vec2  TexCoord1;\r\n"
	"varying mediump vec2  TexCoord2;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\t// Pass through vertex\r\n"
	"\tgl_Position = vec4(inVertex, 1.0);\r\n"
	"\t\r\n"
	"\t// Calculate texture offsets and pass through\t\r\n"
	"\tmediump vec2 offset = vec2(TexelOffsetX, TexelOffsetY);\r\n"
	"  \r\n"
	"    TexCoord0 = inTexCoord - offset;\r\n"
	"    TexCoord1 = inTexCoord;\r\n"
	"    TexCoord2 = inTexCoord + offset;    \r\n"
	"\r\n"
	"}";

// Register BlurVertShader.vsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_BlurVertShader_vsh("BlurVertShader.vsh", _BlurVertShader_vsh, 989);

// ******** End: BlurVertShader.vsh ********

