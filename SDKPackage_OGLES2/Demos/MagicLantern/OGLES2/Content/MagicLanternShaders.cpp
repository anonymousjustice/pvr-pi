// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: MagicLanternShaders.pfx ********

// File data
static const char _MagicLanternShaders_pfx[] = 
	"////////////////////////////////////////////////////////////////////////////////////\r\n"
	"// MagicLantern PFX file.\r\n"
	"// \r\n"
	"// This file contains two shaders sets.\r\n"
	"// The first one transform and light the vertices using a coloured point \r\n"
	"// light with diffuse and specular components. It also projects a cubemap\r\n"
	"// texture containing the light-map which is blended (modulation) with the base \r\n"
	"// texture.\r\n"
	"// The second set is just to draw the cubemap on the sphere with a diffuse colour.\r\n"
	"////////////////////////////////////////////////////////////////////////////////////\r\n"
	"\r\n"
	"[HEADER]\t\r\n"
	"\tVERSION\t\t00.00.00.00\t\r\n"
	"\tDESCRIPTION MagicLantern: Dynamic Lighting example. \t\r\n"
	"\tCOPYRIGHT\tImagination Technologies Ltd.\t\r\n"
	"[/HEADER]\r\n"
	"\r\n"
	"// Texture description\r\n"
	"// For cubemap always use clamp to edge to avoid wrapping artefacts\r\n"
	"// that might show the seams of the textures. \r\n"
	"[TEXTURE]\r\n"
	"\tNAME\t\t\tlantern\r\n"
	"\tPATH\t\t\tLanternCubemap.pvr\r\n"
	"\tMINIFICATION\tLINEAR\r\n"
	"\tMAGNIFICATION\tLINEAR\r\n"
	"\tMIPMAP\t\t\tNEAREST\r\n"
	"\tWRAP_S\t\t\tCLAMP\r\n"
	"\tWRAP_T\t\t\tCLAMP\r\n"
	"[/TEXTURE]\r\n"
	"[TEXTURE]\r\n"
	"\tNAME\t\t\tfloor\r\n"
	"\tPATH\t\t\tFloor.pvr\r\n"
	"\tMINIFICATION\tLINEAR\r\n"
	"\tMAGNIFICATION\tLINEAR\r\n"
	"\tMIPMAP\t\t\tNEAREST\r\n"
	"\tWRAP_S\t\t\tREPEAT\r\n"
	"\tWRAP_T\t\t\tREPEAT\r\n"
	"[/TEXTURE]\r\n"
	"[TEXTURE]\r\n"
	"\tNAME\t\t\tmarble\r\n"
	"\tPATH\t\t\tMarble.pvr\r\n"
	"\tMINIFICATION\tLINEAR\r\n"
	"\tMAGNIFICATION\tLINEAR\r\n"
	"\tMIPMAP\t\t\tNEAREST\r\n"
	"\tWRAP_S\t\t\tREPEAT\r\n"
	"\tWRAP_T\t\t\tREPEAT\r\n"
	"[/TEXTURE]\r\n"
	"\t\r\n"
	"// Projected light-map vertex shader\r\n"
	"[VERTEXSHADER]\r\n"
	"\tNAME myProjectionVSh\r\n"
	"\t[GLSL_CODE]\r\n"
	"\t\tattribute highp   vec3  inVertex;\r\n"
	"\t\tattribute mediump vec3  inNormal;\r\n"
	"\t\tattribute mediump vec2  inTexCoord;\r\n"
	"\r\n"
	"\t\tuniform highp mat4  MVPMatrix;\r\n"
	"\t\tuniform highp mat3  ModelIT;\r\n"
	"\t\tuniform highp vec3  LightPosition;\r\n"
	"\t\tuniform highp vec3 \tLightColor;\r\n"
	"\r\n"
	"\t\tvarying mediump vec4  DiffuseLight;\r\n"
	"\t\tvarying mediump vec4  SpecularLight;\r\n"
	"\t\tvarying mediump vec2  TexCoord;\r\n"
	"\t\tvarying mediump vec3  ReflectDir;\r\n"
	"\r\n"
	"\t\tconst highp float  cShininess = 32.0;\r\n"
	"\r\n"
	"\r\n"
	"\t\tvoid main()\r\n"
	"\t\t{\r\n"
	"\t\t\t// LIGHTING\r\n"
	"\t\t\t// This demo uses point light with specular using a  \r\n"
	"\t\t\t// simplified algorithm without half-vector.\r\n"
	"\t\t\t// For a complete implementation of point light, please, \r\n"
	"\t\t\t// check our ComplexLighting training course.\t\r\n"
	"\t\t\t\r\n"
	"\t\t\t// Get the direction vector from the position of the light\r\n"
	"\t\t\t// to the vertex (it has to be normalised for the dot product to work).\r\n"
	"\t\t\thighp vec3 lightDir = -normalize(inVertex - LightPosition);\r\n"
	"\r\n"
	"\t\t\t// Calculate smooth-shading as the cosine between the light angle \r\n"
	"\t\t\t// and the normal at that vertex (i.e. dot product)\r\n"
	"\t\t\t// The clamping will give us 1.0 (full light) when the normal and the \r\n"
	"\t\t\t// light direction coincide and 0.0 when they are at 90 degrees\t\r\n"
	"\t\t\thighp float Intensity = max(dot(inNormal, lightDir), 0.0);\t\r\n"
	"\t\t\t\r\n"
	"\t\t\t// Calculate now the specular component\r\n"
	"\t\t\tSpecularLight = pow(Intensity, cShininess) * vec4(LightColor,1.0);\r\n"
	"\t\t\tDiffuseLight = Intensity * vec4(LightColor,1.0);\t\r\n"
	"\t\t\t\t\r\n"
	"\t\t\t// The direction from the light position to the vertex is transformed\r\n"
	"\t\t\t// with the inverse-transpose of the same matrix used to transform\r\n"
	"\t\t\t// the sphere. The resulting vector will be used to map into the\r\n"
	"\t\t\t// cubemap texture with our lightmap.\r\n"
	"\t\t\tReflectDir =  lightDir * ModelIT;\r\n"
	"\r\n"
	"\t\t\t// Transform position\r\n"
	"\t\t\tgl_Position = MVPMatrix * vec4(inVertex, 1.0);\r\n"
	"\t\t\t\r\n"
	"\t\t\t// Pass through texcoords\r\n"
	"\t\t\tTexCoord = inTexCoord;\r\n"
	"\t\t}\r\n"
	"\t[/GLSL_CODE]\r\n"
	"[/VERTEXSHADER]\r\n"
	"\r\n"
	"// Projected light-map fragment shader\r\n"
	"[FRAGMENTSHADER]\r\n"
	"\tNAME myProjectionFSh\r\n"
	"\t[GLSL_CODE]\r\n"
	"\t\t\r\n"
	"\r\n"
	"\t\tuniform sampler2D  sTexture;\r\n"
	"\t\tuniform samplerCube sLightMap;\r\n"
	"\t\t\r\n"
	"\t\tvarying mediump vec3  ReflectDir;\r\n"
	"\t\tvarying mediump vec2  TexCoord;\r\n"
	"\t\t\r\n"
	"\t\tvarying lowp    vec4  DiffuseLight;\r\n"
	"\t\tvarying lowp    vec4  SpecularLight;\r\n"
	"\r\n"
	"\t\tvoid main()\r\n"
	"\t\t{\r\n"
	"\t\t\t// Get the lightmap colour\r\n"
	"\t\t\tlowp vec4 lightMap = (textureCube(sLightMap, ReflectDir));\r\n"
	"\r\n"
	"\t\t\t// Compose the final colour modulating the base texture with the lightmap and multiplying by the diffuse colour.\r\n"
	"\t\t\t// The specular component is added at the end.\r\n"
	"\t\t\tgl_FragColor = texture2D(sTexture,TexCoord)*lightMap * DiffuseLight + SpecularLight;\r\n"
	"\t\t}\r\n"
	"\t[/GLSL_CODE]\r\n"
	"[/FRAGMENTSHADER]\r\n"
	"\r\n"
	"// Simple textured sphere vertex shader\r\n"
	"[VERTEXSHADER]\r\n"
	"\tNAME \t\tSphereVertexShader\r\n"
	"\r\n"
	"\t// LOAD GLSL AS CODE\r\n"
	"\t[GLSL_CODE]\r\n"
	"\t\tattribute highp   vec3  inVertex;\r\n"
	"\t\tattribute mediump vec3  inNormal;\r\n"
	"\t\tuniform highp   mat4  MVPMatrix;\r\n"
	"\t\tvarying mediump vec3   ReflectDir;\r\n"
	"\r\n"
	"\t\tvoid main()\r\n"
	"\t\t{\r\n"
	"\t\t\t// Transfotm position\r\n"
	"\t\t\tgl_Position = MVPMatrix * vec4(inVertex, 1.0);\r\n"
	"\r\n"
	"\t\t\t// Pass the inverse of the normal (to map into the cubamap)\r\n"
	"\t\t\tReflectDir = -inNormal;\r\n"
	"\t\t}\r\n"
	"\t[/GLSL_CODE]\r\n"
	"[/VERTEXSHADER]\r\n"
	"\r\n"
	"// Simple textured sphere fragment shader\r\n"
	"[FRAGMENTSHADER] \r\n"
	"\tNAME \t\tSphereFragmentShader \r\n"
	"\r\n"
	"\t// LOAD GLSL AS CODE\r\n"
	"\t[GLSL_CODE]\r\n"
	"\t\tuniform samplerCube sLightMap;\r\n"
	"\t\tuniform lowp  vec3  LightColor;\r\n"
	"\t\tvarying mediump vec3 ReflectDir;\r\n"
	"\r\n"
	"\t\tvoid main()\r\n"
	"\t\t{\r\n"
	"\t\t\t// Final colour is the modulaion of the base texture with the diffuse colour.\r\n"
	"\t\t\tgl_FragColor = (textureCube(sLightMap, ReflectDir)) * vec4(LightColor, 1.0);\r\n"
	"\t\t}\r\n"
	"\t[/GLSL_CODE]\r\n"
	"[/FRAGMENTSHADER]\r\n"
	"\r\n"
	"[EFFECT]\r\n"
	"\tNAME MarbleProjection\r\n"
	"\r\n"
	"\tATTRIBUTE \tinVertex\tPOSITION\r\n"
	"\tATTRIBUTE\tinNormal\tNORMAL\r\n"
	"\tATTRIBUTE\tinTexCoord\tUV\r\n"
	"\t\r\n"
	"\tUNIFORM MVPMatrix WORLDVIEWPROJECTION\r\n"
	"\tUNIFORM ModelIT WORLDIT\r\n"
	"\tUNIFORM LightPosition LIGHTPOSWORLD\r\n"
	"\tUNIFORM LightColor LIGHTCOLOR\r\n"
	"\t\r\n"
	"\tUNIFORM sTexture TEXTURE0\r\n"
	"\tUNIFORM sLightMap TEXTURE1\r\n"
	"\tTEXTURE 0 marble\r\n"
	"\tTEXTURE 1 lantern\r\n"
	"\r\n"
	"\tVERTEXSHADER myProjectionVSh\r\n"
	"\tFRAGMENTSHADER myProjectionFSh\r\n"
	"[/EFFECT]\r\n"
	"\r\n"
	"[EFFECT]\r\n"
	"\tNAME FloorProjection\r\n"
	"\r\n"
	"\tATTRIBUTE \tinVertex\tPOSITION\r\n"
	"\tATTRIBUTE\tinNormal\tNORMAL\r\n"
	"\tATTRIBUTE\tinTexCoord\tUV\r\n"
	"\t\r\n"
	"\tUNIFORM MVPMatrix WORLDVIEWPROJECTION\r\n"
	"\tUNIFORM ModelIT WORLDIT\r\n"
	"\tUNIFORM LightPosition LIGHTPOSWORLD\r\n"
	"\tUNIFORM LightColor LIGHTCOLOR\r\n"
	"\t\r\n"
	"\tUNIFORM sTexture TEXTURE0\r\n"
	"\tUNIFORM sLightMap TEXTURE1\r\n"
	"\tTEXTURE 0 floor\r\n"
	"\tTEXTURE 1 lantern\r\n"
	"\r\n"
	"\tVERTEXSHADER myProjectionVSh\r\n"
	"\tFRAGMENTSHADER myProjectionFSh\r\n"
	"[/EFFECT]\r\n"
	"\r\n"
	"[EFFECT]\r\n"
	"\tNAME Sphere\r\n"
	"\r\n"
	"\tATTRIBUTE \tinVertex\tPOSITION\r\n"
	"\tATTRIBUTE\tinNormal\tNORMAL\r\n"
	"\t\r\n"
	"\tUNIFORM MVPMatrix WORLDVIEWPROJECTION\r\n"
	"\tUNIFORM LightColor LIGHTCOLOR\r\n"
	"\tUNIFORM sLightMap TEXTURE0\r\n"
	"\tTEXTURE 0 lantern\r\n"
	"\r\n"
	"\tVERTEXSHADER SphereVertexShader\r\n"
	"\tFRAGMENTSHADER SphereFragmentShader\r\n"
	"[/EFFECT]";

// Register MagicLanternShaders.pfx in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_MagicLanternShaders_pfx("MagicLanternShaders.pfx", _MagicLanternShaders_pfx, 6224);

// ******** End: MagicLanternShaders.pfx ********

