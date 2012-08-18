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
	"uniform sampler2D  sTexture;\r\n"
	"\r\n"
	"uniform lowp vec3  FogColor;\r\n"
	"\r\n"
	"varying mediump vec2  TexCoord;\r\n"
	"varying lowp    vec3  DiffuseLight;\r\n"
	"varying lowp    vec3  FogIntensity;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\t// Get color from the texture and modulate with diffuse lighting\r\n"
	"    lowp vec3 texColor  = texture2D(sTexture, TexCoord).rgb;\r\n"
	"    lowp vec3 color = texColor * DiffuseLight;\r\n"
	"\t\r\n"
	"\t// interpolate the fog color with the texture-diffuse color using the \r\n"
	"\t// fog intensity calculated in the vertex shader\r\n"
	"\tcolor = mix(FogColor, color, FogIntensity);\r\n"
	"\tgl_FragColor = vec4(color, 1.0);\r\n"
	"}\r\n";

// Register FragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_FragShader_fsh("FragShader.fsh", _FragShader_fsh, 577);

// ******** End: FragShader.fsh ********

