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
	"uniform sampler2D  sThicknessTex;\r\n"
	"\r\n"
	"uniform highp float  MinThickness;\r\n"
	"uniform highp float  MaxVariation;\r\n"
	"\r\n"
	"varying mediump float  CosViewAngle;\r\n"
	"varying mediump float  LightIntensity;\r\n"
	"varying mediump vec2   TexCoord;\r\n"
	"\r\n"
	"// We use wave numbers (k) for the iridescence effect, given as\r\n"
	"//   k =  2 * pi / wavelength in nm.\r\n"
	"const highp float  PI = 3.141592654;\r\n"
	"const highp vec3   cRgbK = 2.0 * PI * vec3(1.0/475.0, 1.0/510.0, 1.0/650.0);\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\thighp float thickness = texture2D(sThicknessTex, TexCoord).r * MaxVariation + MinThickness;\r\n"
	"\thighp float delta = (thickness / LightIntensity) + (thickness / CosViewAngle);\r\n"
	"\tlowp vec3 color = cos(delta * cRgbK) * LightIntensity;\r\n"
	"\tgl_FragColor = vec4(color, 1.0);\r\n"
	"}";

// Register FragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_FragShader_fsh("FragShader.fsh", _FragShader_fsh, 730);

// ******** End: FragShader.fsh ********

