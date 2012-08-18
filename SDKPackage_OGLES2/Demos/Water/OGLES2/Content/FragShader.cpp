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
	"uniform sampler2D\t\tNormalTex;\r\n"
	"uniform sampler2D\t\tReflectionTex;\r\n"
	"#ifdef ENABLE_REFRACTION\r\n"
	"\tuniform sampler2D\t\tRefractionTex;\r\n"
	"#endif\r\n"
	"uniform samplerCube NormalisationCubeMap;\r\n"
	"\r\n"
	"uniform mediump mat4\tModelViewMatrix;\r\n"
	"uniform lowp vec4\t\tWaterColour;\r\n"
	"#ifdef ENABLE_DISTORTION\r\n"
	"\tuniform mediump float\tWaveDistortion;\r\n"
	"#endif\r\n"
	"uniform mediump vec2 \tRcpWindowSize;\r\n"
	"\r\n"
	"varying mediump vec2 \tBumpCoord0;\r\n"
	"varying mediump vec2 \tBumpCoord1;\r\n"
	"varying mediump vec3\tWaterToEye;\r\n"
	"varying mediump float\tWaterToEyeLength;\r\n"
	"\r\n"
	"void main()\r\n"
	"{\t\r\n"
	"\t// Calculate the tex coords of the fragment (using it's position on the screen), normal map is z-axis major.\r\n"
	"\tlowp vec3 vAccumulatedNormal = vec3(0.0,0.0,1.0);\r\n"
	"\tmediump vec2 vTexCoord = gl_FragCoord.xy * RcpWindowSize;\r\n"
	"\t\r\n"
	"\t#ifdef ENABLE_DISTORTION\r\n"
	"\t\t// When distortion is enabled, use the normal map to calculate perturbation\r\n"
	"\t\tvAccumulatedNormal = texture2D(NormalTex, BumpCoord0).rgb;\r\n"
	"\t\tvAccumulatedNormal += texture2D(NormalTex, BumpCoord1).rgb;\r\n"
	"\t\tvAccumulatedNormal -= 1.0; // Same as * 2.0 - 2.0\r\n"
	"\t\r\n"
	"\t\tlowp vec2 vTmp = vAccumulatedNormal.xy;\r\n"
	"\t\t/* \t\r\n"
	"\t\t\tDivide by WaterToEyeLength to scale down the distortion\r\n"
	"\t\t \tof fragments based on their distance from the camera \r\n"
	"\t\t*/\r\n"
	"\t\tvTexCoord.xy -= vTmp * (WaveDistortion / WaterToEyeLength);\r\n"
	"\t#endif\r\n"
	"\r\n"
	"#ifdef ENABLE_REFRACTION\r\n"
	"\tlowp vec4 vReflectionColour = texture2D(ReflectionTex, vTexCoord);\r\n"
	"\tlowp vec4 vRefractionColour = texture2D(RefractionTex, vTexCoord);\r\n"
	"\t\r\n"
	"\t#ifdef ENABLE_FRESNEL\r\n"
	"\t\t// Calculate the Fresnel term to determine amount of reflection for each fragment\r\n"
	"\t\t\r\n"
	"\t\t// Use normalisation cube map instead of normalize() - See section 3.3.1 of white paper for more info\r\n"
	"\t\tlowp vec3 vWaterToEyeCube = textureCube(NormalisationCubeMap,WaterToEye).rgb * 2.0 - 1.0;\r\n"
	"\r\n"
	"\t\t//Normal map uses z-axis major instead of y-axis major, so we have to swizzle to switch the normal map's z and y axis.\r\n"
	"\t\tmediump float fEyeToNormalAngle = clamp(dot(vWaterToEyeCube,vAccumulatedNormal.xzy),0.0,1.0);\r\n"
	"\t\t\r\n"
	"\t\tmediump float fAirWaterFresnel = 1.0 - fEyeToNormalAngle;\r\n"
	"\t\tfAirWaterFresnel = pow(fAirWaterFresnel, 5.0);\r\n"
	"\t\tfAirWaterFresnel = (0.98 * fAirWaterFresnel) + 0.02;\t// R(0)-1 = ~0.98 , R(0)= ~0.02\r\n"
	"\t\tlowp float fTemp = fAirWaterFresnel;\r\n"
	"\t\t\r\n"
	"\t\t// Blend reflection and refraction\r\n"
	"\t\tgl_FragColor = mix(vRefractionColour, vReflectionColour, fTemp);\r\n"
	"\t#else\r\n"
	"\t\tgl_FragColor = mix(vRefractionColour, vReflectionColour, 0.4);\t// Constant mix\r\n"
	"\t#endif\r\n"
	"#else\r\n"
	"\tgl_FragColor = texture2D(ReflectionTex, vTexCoord);\t\t\t\t\t// Reflection only\r\n"
	"#endif\r\n"
	"}\r\n";

// Register FragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_FragShader_fsh("FragShader.fsh", _FragShader_fsh, 2540);

// ******** End: FragShader.fsh ********

