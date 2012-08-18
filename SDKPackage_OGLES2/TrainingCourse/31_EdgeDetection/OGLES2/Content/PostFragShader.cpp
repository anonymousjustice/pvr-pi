// This file was created by Filewrap 1.1
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: PostFragShader.fsh ********

// File data
static const char _PostFragShader_fsh[] = 
	"uniform sampler2D  sColorBufferTexture;\t// Texture containing color info in rgb and an object ID value in the alpha channel.\r\n"
	"varying mediump vec2 t1;\t\t\t\t// Texture coordinate for this fragment.\r\n"
	"//#define EDGE_DETECTION\r\n"
	"//#define INVERSE\t\t\tThese are for editing only, leave disabled as they are passed in by the main program\r\n"
	"//#define BLUR\r\n"
	"\r\n"
	"#ifdef EDGE_DETECTION\r\n"
	"varying mediump vec2 t2;\t\t\t\t// Texel directly above this fragment's.\r\n"
	"varying mediump vec2 t3;\t\t\t\t// Texel directly to the right of this fragment's.\r\n"
	"#endif\r\n"
	"\r\n"
	"const lowp vec3 black = vec3(0.0);\r\n"
	"\r\n"
	"void main()\r\n"
	"{\r\n"
	"\t// Gets the color from the render texture.\r\n"
	"\tlowp vec4 Color = texture2D(sColorBufferTexture, t1);\r\n"
	"\t\t\r\n"
	"\t// Temporary color store to be written to, data transferred to gl_FragColor at the end.\r\n"
	"\tlowp vec3 newColor=Color.rgb;\r\n"
	"\t\r\n"
	"#ifdef EDGE_DETECTION\r\n"
	"\t// Reads in values from the color texture, for two surrounding texels;\r\n"
	"\tlowp vec4 upFrag = texture2D(sColorBufferTexture, t2);\r\n"
	"\tlowp vec4 rightFrag = texture2D(sColorBufferTexture, t3);\r\n"
	"\t\r\n"
	"\t// If the object IDs covering this area differ, draw an edge\r\n"
	"\tif(upFrag.a-Color.a!=0.0 || rightFrag.a-Color.a!=0.0)\r\n"
	"\t{\r\n"
	"\t#ifdef INVERSE\r\n"
	"\t\t// Sets edge color to inverse of original color.\r\n"
	"\t\tnewColor=1.0-Color.rgb;\r\n"
	"\t#else \r\n"
	"\t#ifdef BLUR\r\n"
	"\t\t// Sets edge to a mixture of surrounding colors.\r\n"
	"\t\t//newColor=((2.0*Color.rgb+upFrag.rgb+rightFrag.rgb)*0.25);\r\n"
	"\t\t\r\n"
	"\t\t//newColor=((Color.rgb+upFrag.rgb)*0.25+(Color.rgb+rightFrag.rgb)*0.25);\r\n"
	"\t\tnewColor=(Color.rgb*0.5+(upFrag.rgb+rightFrag.rgb)*0.25);\r\n"
	"\t\t\r\n"
	"\t\t\r\n"
	"\t#else\r\n"
	"\t\t// Sets edge to black\r\n"
	"\t\tnewColor=black;\r\n"
	"\t#endif\r\n"
	"\t#endif\r\n"
	"\t}\r\n"
	"\telse\r\n"
	"\t{\r\n"
	"\t#ifdef INVERSE\r\n"
	"\t\t//Sets non-edges to black\r\n"
	"\t\tnewColor=black;\r\n"
	"\t#endif\r\n"
	"\t}\r\n"
	"#endif\r\n"
	"\r\n"
	"\t// Finally assigns gl_FragColor, with a default alpha value of 1.\r\n"
	"\tgl_FragColor=vec4(newColor,1.0);\r\n"
	"}";

// Register PostFragShader.fsh in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_PostFragShader_fsh("PostFragShader.fsh", _PostFragShader_fsh, 1812);

// ******** End: PostFragShader.fsh ********

