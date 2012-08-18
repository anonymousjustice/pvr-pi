// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: SkyboxFShader.fsh ********

// File data
static const char _SkyboxFShader_fsh[] = 
	"uniform samplerCube CubeMap;\r\n"
	"\r\n"
	"#ifdef ENABLE_FOG_DEPTH\r\n"
	"uniform lowp vec3 FogColour;\r\n"
	"uniform mediump float RcpMaxFogDepth;\r\n"
	"#endif\r\n"
	"#ifdef ENABLE_DISCARD_CLIP\r\n"
	"uniform bool ClipPlaneBool;\r\n"
	"#endif\r\n"
	"\r\n"
	"varying mediump vec3 EyeDir;\r\n"
	"#ifdef ENABLE_FOG_DEPTH\r\n"
	"varying mediump float VertexDepth;\r\n"
	"#endif\r\n"
	"#ifdef ENABLE_DISCARD_CLIP\r\n"
	"varying highp float ClipDist;\r\n"
	"#endif\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\t#ifdef ENABLE_DISCARD_CLIP\r\n"
	"\t\t// Reject fragments behind the clip plane\r\n"
	"\t\tif(ClipDist < 0.0)\r\n"
	"\t\t{\r\n"
	"\t\t\tdiscard; // Too slow for hardware. Left as an example of how not to do this!\r\n"
	"\t\t}\r\n"
	"\t#endif\r\n"
	"\t\r\n"
	"\t#ifdef ENABLE_FOG_DEPTH\r\n"
	"\t\t// Mix the object's colour with the fogging colour based on fragment's depth\r\n"
	"\t\tlowp vec3 vFragColour = textureCube(CubeMap, EyeDir).rgb;\r\n"
	"\t\t\r\n"
	"\t\t// Test depth\r\n"
	"\t\tlowp float fFogBlend = clamp(VertexDepth * RcpMaxFogDepth, 0.0, 1.0);\r\n"
	"\t\tvFragColour.rgb = mix(vFragColour.rgb, FogColour.rgb, fFogBlend);\r\n"
	"\t\t\t\r\n"
	"\t\tgl_FragColor = vec4(vFragColour.rgb, 1.0);\r\n"
	"\t#else\r\n"
	"\t\tgl_FragColor = textureCube(CubeMap, EyeDir);\r\n"
	"\t\t\r\n"
	"\t#endif\r\n"
	"}";

// Register SkyboxFShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_SkyboxFShader_fsh("SkyboxFShader.fsh", _SkyboxFShader_fsh, 1035);

// ******** End: SkyboxFShader.fsh ********

