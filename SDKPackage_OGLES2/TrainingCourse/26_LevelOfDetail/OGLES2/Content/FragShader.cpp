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
	"uniform sampler2D  sReflectTex;\r\n"
	"uniform sampler2D  sNormalMap;\r\n"
	"\r\n"
	"uniform bool  bHighDetail;\r\n"
	"\r\n"
	"varying mediump vec3  EyeDirection;\r\n"
	"varying mediump vec2  TexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\tif (bHighDetail)\r\n"
	"\t{\r\n"
	"\t\t// Get the normal direction per pixel from the normal map\r\n"
	"\t\t// The tNormal vector is defined in surface local coordinates (tangent space).\r\n"
	"\t\tmediump vec3 normal = texture2D(sNormalMap, TexCoord).rgb * 2.0 - 1.0;\r\n"
	"\t\t\r\n"
	"\t\t// reflect(): For the incident vector I and surface orientation N, returns the reflection direction:\r\n"
	"\t\t// I - 2 * dot(N, I) * N, N must already be normalized in order to achieve the desired result.\r\n"
	"\t\tmediump vec3 reflectDir = reflect(normal, EyeDirection);\r\n"
	"\t\tmediump vec2 reflectCoord = (reflectDir.xy) * 0.5 + 0.5;\r\n"
	"\t\r\n"
	"\t\t// Look-up in the 2D texture using the normal map disturbance\r\n"
	"\t\tgl_FragColor = texture2D(sReflectTex, reflectCoord);\r\n"
	"\t}\r\n"
	"\telse\r\n"
	"\t{\r\n"
	"\t\tgl_FragColor = texture2D(sReflectTex, TexCoord);\r\n"
	"\t}\r\n"
	"}\r\n";

// Register FragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_FragShader_fsh("FragShader.fsh", _FragShader_fsh, 949);

// ******** End: FragShader.fsh ********

