#--------------------------------------------------------------------------
# Name         : content.mak
# Title        : Makefile to build content files
#
# Copyright    : Copyright (C)  Imagination Technologies Limited.
#              : No part of this software, either material or conceptual 
#              : may be copied or distributed, transmitted, transcribed,
#              : stored in a retrieval system or translated into any 
#              : human or computer language in any form by any means,
#              : electronic, mechanical, manual or other-wise, or 
#              : disclosed to third parties without the express written
#              : permission of VideoLogic Limited, Unit 8, HomePark
#              : Industrial Estate, King's Langley, Hertfordshire,
#              : WD4 8LZ, U.K.
#
# Description  : Makefile to build content files for demos in the PowerVR SDK
#
# Platform     :
#
#--------------------------------------------------------------------------

#############################################################################
## Variables
#############################################################################
PVRTEXTOOL 	= ..\..\..\Utilities\PVRTexTool\PVRTexToolCL\Windows_x86_32\PVRTexTool.exe
FILEWRAP 	= ..\..\..\Utilities\Filewrap\Windows_x86_32\Filewrap.exe
PVRUNISCO 	= ..\..\..\Utilities\PVRUniSCo\OGLES\Windows_x86_32\glslcompiler_sgx535.exe

MEDIAPATH = ../Media
CONTENTDIR = Content

#############################################################################
## Instructions
#############################################################################

TEXTURES =

BIN_SHADERS = \
	PreFragShader.fsc \
	PreVertShader.vsc \
	PostFragShader.fsc \
	PostVertShader.vsc

RESOURCES = \
	$(CONTENTDIR)/PreFragShader.cpp \
	$(CONTENTDIR)/PreVertShader.cpp \
	$(CONTENTDIR)/PostFragShader.cpp \
	$(CONTENTDIR)/PostVertShader.cpp \
	$(CONTENTDIR)/SketchObject.cpp

all: resources
	
help:
	@echo Valid targets are:
	@echo resources, textures, binary_shaders, clean
	@echo PVRTEXTOOL, FILEWRAP and PVRUNISCO can be used to override the default paths to these utilities.

clean:
	-rm $(RESOURCES)
	-rm $(BIN_SHADERS)
	-rm $(TEXTURES)

resources: 		$(CONTENTDIR) $(RESOURCES)
textures: 		$(TEXTURES)
binary_shaders:	$(BIN_SHADERS)

$(CONTENTDIR):
	-mkdir $@

$(CONTENTDIR)/PreFragShader.cpp: PreFragShader.fsh PreFragShader.fsc
	$(FILEWRAP)  -s  -o $@ PreFragShader.fsh
	-$(FILEWRAP)  -oa $@ PreFragShader.fsc

$(CONTENTDIR)/PreVertShader.cpp: PreVertShader.vsh PreVertShader.vsc
	$(FILEWRAP)  -s  -o $@ PreVertShader.vsh
	-$(FILEWRAP)  -oa $@ PreVertShader.vsc

$(CONTENTDIR)/PostFragShader.cpp: PostFragShader.fsh PostFragShader.fsc
	$(FILEWRAP)  -s  -o $@ PostFragShader.fsh
	-$(FILEWRAP)  -oa $@ PostFragShader.fsc

$(CONTENTDIR)/PostVertShader.cpp: PostVertShader.vsh PostVertShader.vsc
	$(FILEWRAP)  -s  -o $@ PostVertShader.vsh
	-$(FILEWRAP)  -oa $@ PostVertShader.vsc

$(CONTENTDIR)/SketchObject.cpp: SketchObject.pod
	$(FILEWRAP)  -o $@ SketchObject.pod

PreFragShader.fsc: PreFragShader.fsh
	$(PVRUNISCO) PreFragShader.fsh $@  -f 

PreVertShader.vsc: PreVertShader.vsh
	$(PVRUNISCO) PreVertShader.vsh $@  -v 

PostFragShader.fsc: PostFragShader.fsh
	$(PVRUNISCO) PostFragShader.fsh $@  -f 

PostVertShader.vsc: PostVertShader.vsh
	$(PVRUNISCO) PostVertShader.vsh $@  -v 

############################################################################
# End of file (content.mak)
############################################################################
