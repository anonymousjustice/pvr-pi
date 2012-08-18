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
	"uniform sampler2D s2DMap;\r\n"
	"uniform samplerCube sCubeMap;\r\n"
	"\r\n"
	"uniform bool bCubeReflection;\r\n"
	"\r\n"
	"varying mediump vec3  ReflectDir;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\t// select whether to use cube map reflection or 2d reflection\t\r\n"
	"\tif(bCubeReflection)\r\n"
	"\t{\r\n"
	"\t\tgl_FragColor = textureCube(sCubeMap, ReflectDir);\r\n"
	"\t}\r\n"
	"\telse \r\n"
	"\t{\r\n"
	"\t\tgl_FragColor = texture2D(s2DMap, ReflectDir.xy * 0.5 + 0.5);\r\n"
	"\t}\r\n"
	"}";

// Register FragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_FragShader_fsh("FragShader.fsh", _FragShader_fsh, 375);

// ******** End: FragShader.fsh ********

