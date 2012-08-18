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
	"uniform sampler2D\tbasemap;\r\n"
	"uniform sampler2D\tnormalmap;\r\n"
	"uniform sampler2D\theightmap;\r\n"
	"\r\n"
	"varying lowp vec3\tlightDir;\r\n"
	"varying lowp vec3\tviewDir;\r\n"
	"varying lowp vec2\ttexCoord;\r\n"
	"\r\n"
	"void main (void)\r\n"
	"{\r\n"
	"\t// Normalise the directions in tangent space\r\n"
	"\tlowp vec3 vLightDir = normalize(lightDir);\r\n"
	"\t\r\n"
	"\t// Initial texture read\r\n"
	"\t// Calculate how far we're shifting by (using parallax scale).\r\n"
	"\tlowp float fDepth = texture2D(heightmap, texCoord).x;\r\n"
	"\t\r\n"
	"\t// Set the UV Coord appropriately\r\n"
	"\tlowp vec2 vTexCoord = texCoord + (fDepth * viewDir.xy);\r\n"
	"\t\r\n"
	"\t// Base map Lookup\r\n"
	"\tlowp vec3 texColour = texture2D(basemap, vTexCoord).rgb;\r\n"
	"\t\r\n"
	"\t// Now do everything else, diffuse, ambient etc.\r\n"
	"\tlowp vec3 vNormal = (texture2D(normalmap, vTexCoord).rbg)*2.0-1.0;\r\n"
	"\t\t\r\n"
	"\t// diffuse lighting\r\n"
	"\tlowp float diffIntensity = max(dot(vLightDir, vNormal), 0.0);\t\r\n"
	"\t\r\n"
	"\t// calculate actual colour\r\n"
	"\tlowp vec3 colour = vec3(diffIntensity) * texColour;\r\n"
	"\t\r\n"
	"\tgl_FragColor = vec4(colour, 1.0);\r\n"
	"}";

// Register FragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_FragShader_fsh("FragShader.fsh", _FragShader_fsh, 961);

// ******** End: FragShader.fsh ********

