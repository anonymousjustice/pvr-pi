/******************************************************************************

 @File         PVRTPrint3DShaders.h

 @Title        OGLES2\PVRTPrint3DShaders

 @Version      

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     ANSI compatible

 @Description  The shaders used by Print3D. Created by Filewrap 1.0. DO NOT EDIT.

******************************************************************************/

// This file was created by Filewrap 1.0
// DO NOT EDIT

// using 32 bit to guarantee alignment. Adds endianness dependency.
#ifndef A32BIT
 #define A32BIT PVRTuint32
#endif

// ******** Start: Print3DFragShader.fsh ********

// File data
static const char _Print3DFragShader_fsh[] =
	"uniform sampler2D\tsampler2d;\r\n"
	"\r\n"
	"varying lowp vec4\t\tvarColour;\r\n"
	"varying mediump vec2\ttexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\tgl_FragColor = vec4(varColour.rgb, varColour.a * texture2D(sampler2d, texCoord).a);\r\n"
	"}\r\n";

// ******** End: Print3DFragShader.fsh ********

// ******** Start: Print3DVertShader.vsh ********

// File data
static const char _Print3DVertShader_vsh[] =
	"attribute highp vec4\tmyVertex;\r\n"
	"attribute mediump vec2\tmyUV;\r\n"
	"attribute lowp vec4\t\tmyColour;\r\n"
	"\r\n"
	"uniform highp mat4\t\tmyMVPMatrix;\r\n"
	"\r\n"
	"varying lowp vec4\t\tvarColour;\r\n"
	"varying mediump vec2\ttexCoord;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\tgl_Position = myMVPMatrix * myVertex;\r\n"
	"\ttexCoord = myUV.st;\r\n"
	"\tvarColour = myColour;\r\n"
	"}\r\n";

// ******** End: Print3DVertShader.vsh ********

