// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: ModelFShader.fsh ********

// File data
static const char _ModelFShader_fsh[] = 
	"#define ENABLE_TEXTURE\r\n"
	"#ifdef ENABLE_TEXTURE\r\n"
	"uniform sampler2D\t\tModelTexture;\r\n"
	"#endif\r\n"
	"\r\n"
	"#ifdef ENABLE_FOG_DEPTH\r\n"
	"uniform lowp vec3 \t\tFogColour;\r\n"
	"uniform mediump float \tRcpMaxFogDepth;\r\n"
	"#endif\r\n"
	"\r\n"
	"#ifdef ENABLE_LIGHTING\r\n"
	"\tvarying lowp float\t\tLightIntensity;\r\n"
	"#endif\r\n"
	"#ifdef ENABLE_TEXTURE\r\n"
	"\tvarying mediump vec2   \tTexCoord;\r\n"
	"#endif\r\n"
	"#ifdef ENABLE_FOG_DEPTH\r\n"
	"\tvarying mediump float \tVertexDepth;\r\n"
	"#endif\r\n"
	"\r\n"
	"void main()\r\n"
	"{\t\r\n"
	"\t#ifdef ONLY_ALPHA\r\n"
	"\t\tgl_FragColor = vec4(vec3(0.5),0.0);\r\n"
	"\t#else\r\n"
	"\t\t#ifdef ENABLE_TEXTURE\r\n"
	"\t\t\t#ifdef ENABLE_FOG_DEPTH\t\t\r\n"
	"\t\t\t\t// Mix the object's colour with the fogging colour based on fragment's depth\r\n"
	"\t\t\t\tlowp vec3 vFragColour = texture2D(ModelTexture, TexCoord).rgb;\r\n"
	"\t\t\t\t\r\n"
	"\t\t\t\t// Perform depth test and clamp the values\r\n"
	"\t\t\t\tlowp float fFogBlend = clamp(VertexDepth * RcpMaxFogDepth, 0.0, 1.0);\r\n"
	"\t\t\t\t\r\n"
	"\t\t\t\t#ifdef ENABLE_LIGHTING\r\n"
	"\t\t\t\t\tvFragColour.rgb = mix(vFragColour.rgb * LightIntensity, FogColour.rgb, fFogBlend);\r\n"
	"\t\t\t\t#else\r\n"
	"\t\t\t\t\tvFragColour.rgb = mix(vFragColour.rgb, FogColour.rgb, fFogBlend);\r\n"
	"\t\t\t\t#endif\r\n"
	"\t\t\t\tgl_FragColor = vec4(vFragColour,1.0);\r\n"
	"\t\t\t#else\r\n"
	"\t\t\t\t#ifdef ENABLE_LIGHTING\r\n"
	"\t\t\t\t\tgl_FragColor = vec4(texture2D(ModelTexture, TexCoord).rgb * LightIntensity, 1.0);\r\n"
	"\t\t\t\t#else\r\n"
	"\t\t\t\t\tgl_FragColor = vec4(texture2D(ModelTexture, TexCoord).rgb, 1.0);\r\n"
	"\t\t\t\t#endif\r\n"
	"\t\t\t#endif\r\n"
	"\t\t#else\r\n"
	"\t\t\t// Solid colour is used instead of texture colour\r\n"
	"\t\t\t#ifdef ENABLE_LIGHTING\r\n"
	"\t\t\t\tgl_FragColor = vec4(vec3(0.3,0.3,0.3)* LightIntensity, 1.0);\r\n"
	"\t\t\t#else\r\n"
	"\t\t\t\tgl_FragColor = vec4(vec3(0.3,0.3,0.3), 1.0);\t\r\n"
	"\t\t\t#endif\r\n"
	"\t\t#endif\r\n"
	"\t#endif\r\n"
	"}\r\n";

// Register ModelFShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_ModelFShader_fsh("ModelFShader.fsh", _ModelFShader_fsh, 1568);

// ******** End: ModelFShader.fsh ********

