// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: SkyboxVShader.vsh ********

// File data
static const char _SkyboxVShader_vsh[] = 
	"attribute mediump vec3 inVertex;\r\n"
	"\r\n"
	"uniform mediump mat4 ModelMatrix;\r\n"
	"uniform mediump mat4 ModelViewMatrix;\r\n"
	"uniform mediump mat4 MVPMatrix;\r\n"
	"#ifdef ENABLE_FOG_DEPTH\r\n"
	"uniform mediump float WaterHeight;\t\t//Assume water always lies on the y-axis\r\n"
	"#endif\r\n"
	"#ifdef ENABLE_DISCARD_CLIP\r\n"
	"uniform bool ClipPlaneBool;\r\n"
	"uniform mediump vec4 ClipPlane;\r\n"
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
	"\tEyeDir = -inVertex;\r\n"
	"\tgl_Position = MVPMatrix * vec4(inVertex, 1.0);\r\n"
	"\t\r\n"
	"\t#ifdef ENABLE_DISCARD_CLIP\r\n"
	"\t\t// Compute the distance between the vertex and clipping plane (in world space coord system)\r\n"
	"\t\tmediump vec4 vVertexView = ModelMatrix * vec4(inVertex.xyz,1.0);\r\n"
	"\t\tClipDist = dot(vVertexView, ClipPlane);\r\n"
	"\t#endif\r\n"
	"\t\r\n"
	"\t#ifdef ENABLE_FOG_DEPTH\r\n"
	"\t\t// Calculate the vertex's distance under water surface. This assumes clipping has removed all objects above the water\r\n"
	"\t\tmediump float vVertexHeight = (ModelMatrix * vec4(inVertex,1.0)).y;\r\n"
	"\t\tVertexDepth = WaterHeight - vVertexHeight;\r\n"
	"\t#endif\r\n"
	"}";

// Register SkyboxVShader.vsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_SkyboxVShader_vsh("SkyboxVShader.vsh", _SkyboxVShader_vsh, 1133);

// ******** End: SkyboxVShader.vsh ********

