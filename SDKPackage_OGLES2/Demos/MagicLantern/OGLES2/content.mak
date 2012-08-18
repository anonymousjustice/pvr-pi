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

TEXTURES = \
	Marble.pvr \
	Floor.pvr \
	LanternCubemap.pvr

BIN_SHADERS =

RESOURCES = \
	$(CONTENTDIR)/Marble.cpp \
	$(CONTENTDIR)/Floor.cpp \
	$(CONTENTDIR)/LanternCubemap.cpp \
	$(CONTENTDIR)/MagicLanternShaders.cpp \
	$(CONTENTDIR)/MagicLantern.cpp

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

Marble.pvr: $(MEDIAPATH)/Marble.png
	$(PVRTEXTOOL) -m -fOGLPVRTC4 -i$(MEDIAPATH)/Marble.png -o$@

Floor.pvr: $(MEDIAPATH)/Floor.png
	$(PVRTEXTOOL) -m -fOGLPVRTC4 -i$(MEDIAPATH)/Floor.png -o$@

LanternCubemap.pvr: $(MEDIAPATH)/LanternF_1.png $(MEDIAPATH)/LanternF_2.png $(MEDIAPATH)/LanternF_3.png $(MEDIAPATH)/LanternF_4.png $(MEDIAPATH)/LanternF_5.png $(MEDIAPATH)/LanternF_6.png
	$(PVRTEXTOOL) -s -m -fOGL565 -i$(MEDIAPATH)/LanternF_1.png -o$@

$(CONTENTDIR)/Marble.cpp: Marble.pvr
	$(FILEWRAP)  -o $@ Marble.pvr

$(CONTENTDIR)/Floor.cpp: Floor.pvr
	$(FILEWRAP)  -o $@ Floor.pvr

$(CONTENTDIR)/LanternCubemap.cpp: LanternCubemap.pvr
	$(FILEWRAP)  -o $@ LanternCubemap.pvr

$(CONTENTDIR)/MagicLanternShaders.cpp: MagicLanternShaders.pfx
	$(FILEWRAP)  -s  -o $@ MagicLanternShaders.pfx

$(CONTENTDIR)/MagicLantern.cpp: MagicLantern.pod
	$(FILEWRAP)  -o $@ MagicLantern.pod

############################################################################
# End of file (content.mak)
############################################################################
