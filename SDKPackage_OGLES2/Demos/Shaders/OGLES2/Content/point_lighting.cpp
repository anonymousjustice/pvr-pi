// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: point_lighting.pfx ********

// File data
static const char _point_lighting_pfx[] = 
	"[HEADER]\r\n"
	"\tVERSION\t\t00.00.00.00\r\n"
	"\tDESCRIPTION Complex Lighting Example\r\n"
	"\tCOPYRIGHT\tImagination Technologies Ltd.\r\n"
	"[/HEADER]\r\n"
	"\r\n"
	"[TEXTURES]\r\n"
	"\tFILE base \t\t\tbase.pvr\t\tLINEAR-LINEAR-LINEAR\t\r\n"
	"[/TEXTURES]\r\n"
	"\r\n"
	"[VERTEXSHADER]\r\n"
	"\tNAME myVertShader\r\n"
	"\t[GLSL_CODE]\r\n"
	"\t\tattribute highp vec3\tmyVertex, myNormal;\r\n"
	"\t\tattribute mediump vec2\tmyUV;\r\n"
	"\t\tuniform mediump mat4\tmyMVPMatrix, myModelView;\r\n"
	"\t\tuniform mediump mat3\tmyModelViewIT;\r\n"
	"\t\tvarying mediump vec2\ttexCoord;\r\n"
	"\t\tvarying mediump vec3\tdiffuse, specular;\r\n"
	"\t\tconst mediump float\t\tshininess = 16.0;\r\n"
	"\t\tconst mediump float\t\tcutoff = 0.975, exp = 100.0;\r\n"
	"\t\tconst mediump vec3\t\tLightPos = vec3(4.0, 4.0, 4.0);\r\n"
	"\t\tconst mediump vec3\t\tLightCol = vec3(1.0,1.0,1.0);\r\n"
	"\t\r\n"
	"\t//point light function //\r\n"
	"\t// spFlg\tflag using specular or not.\r\n"
	"\t// nrml\t\tnrml vector in the eye coordinate.\r\n"
	"\t// ePos\t\tvertex position in the eye coordinate.\r\n"
	"\tvoid PointLight(in mediump int spFlg, in mediump vec3 nrml, in mediump vec3 ePos){\r\n"
	"\t\tmediump float pf;\r\n"
	"\t\t// calculate the vector from vertex to light.\r\n"
	"\t\tmediump vec3 VP = normalize(LightPos- ePos);\r\n"
	"\t\t// calculate the half vector between eye position and light position.\r\n"
	"\t\tmediump vec3 halfV = normalize(-ePos + LightPos);\r\n"
	"\t\t// calculate the diffuse light intensity.\r\n"
	"\t\tmediump float dVP = max(dot(nrml,VP), 0.0);\r\n"
	"\t\t// calculate approximated specular light base intensity.\r\n"
	"\t\tmediump float dHV = max(dot(nrml,halfV), 0.0);\r\n"
	"\t\t// if the diffuse is not zero and spFlg is On,\r\n"
	"\t\t// calculate specular light intensity with shininess,\r\n"
	"\t\t// or turn off the specular light.\r\n"
	"\t\tif(dVP>.0) pf = pow(dHV, shininess);\r\n"
	"\t\telse       pf = 0.0;\r\n"
	"\t\tdiffuse += dVP*LightCol;\r\n"
	"\t\tspecular += pf*LightCol;\r\n"
	"\t}\r\n"
	"\r\n"
	"\t// main function //\r\n"
	"\tvoid main(void){\r\n"
	"\t\t// transform the normal vector from the model coordinate to the eye coordinate.\r\n"
	"\t\tmediump vec3 normal = normalize(myModelViewIT * myNormal);\r\n"
	"\t\t// calculate the vertex position in the eye coordinate.\r\n"
	"\t\thighp vec3 ePos = vec3(myModelView * vec4(myVertex,1.0));\r\n"
	"\t\t// initalize light intensity parameter.\r\n"
	"\t\tdiffuse = vec3(0.0);\r\n"
	"\t\tspecular = vec3(0.0);\r\n"
	"\t\t\r\n"
	"\t\tPointLight(0, normal, ePos);\r\n"
	"\r\n"
	"\t\t// Transform position\r\n"
	"\t\tgl_Position = myMVPMatrix * vec4(myVertex,1.0);\r\n"
	"\t\t// Pass UV co-ordinates\r\n"
	"\t\ttexCoord = myUV.st;\r\n"
	"\t}\r\n"
	"\t[/GLSL_CODE]\r\n"
	"[/VERTEXSHADER]\r\n"
	"\r\n"
	"[FRAGMENTSHADER]\r\n"
	"\tNAME myFragShader\r\n"
	"\t[GLSL_CODE]\r\n"
	"\t\tuniform sampler2D \t\tsampler2d;\r\n"
	"\t\tvarying mediump vec2\ttexCoord;\r\n"
	"\t\tvarying mediump vec3\tdiffuse;\r\n"
	"\t\tvarying mediump vec3\tspecular;\r\n"
	"\t\tvoid main (void)\r\n"
	"\t\t{\r\n"
	"\t\t\tmediump vec3 texColour  = vec3(texture2D(sampler2d, texCoord));\r\n"
	"\t\t\tmediump vec3 colour = (texColour * diffuse) + specular;\r\n"
	"\t\t\tgl_FragColor = vec4(colour, 1.0);\r\n"
	"\t\t}\r\n"
	"\t[/GLSL_CODE]\r\n"
	"[/FRAGMENTSHADER]\r\n"
	"\r\n"
	"[EFFECT]\r\n"
	"\tNAME myEffect\r\n"
	"\r\n"
	"\tATTRIBUTE\tmyVertex\t\t\tPOSITION\r\n"
	"\tATTRIBUTE\tmyNormal\t\t\tNORMAL\r\n"
	"\tATTRIBUTE\tmyUV\t\t\t\tUV\r\n"
	"\tUNIFORM\t\tmyMVPMatrix\t\t\tWORLDVIEWPROJECTION\r\n"
	"\tUNIFORM\t\tmyModelView\t\t\tWORLDVIEW\r\n"
	"\tUNIFORM\t\tmyModelViewIT\t\tWORLDVIEWIT\r\n"
	"\tUNIFORM\t\tsampler2d\t\t\tTEXTURE0\r\n"
	"\r\n"
	"\tTEXTURE 0 base\r\n"
	"\r\n"
	"\tVERTEXSHADER myVertShader\r\n"
	"\tFRAGMENTSHADER myFragShader\r\n"
	"[/EFFECT]\r\n";

// Register point_lighting.pfx in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_point_lighting_pfx("point_lighting.pfx", _point_lighting_pfx, 3036);

// ******** End: point_lighting.pfx ********

