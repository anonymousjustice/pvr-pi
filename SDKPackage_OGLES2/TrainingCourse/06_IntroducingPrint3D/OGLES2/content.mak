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

BIN_SHADERS =

RESOURCES = \
	$(CONTENTDIR)/Text.cpp \
	$(CONTENTDIR)/arial_36.cpp \
	$(CONTENTDIR)/starjout_60.cpp \
	$(CONTENTDIR)/title_36.cpp \
	$(CONTENTDIR)/title_46.cpp \
	$(CONTENTDIR)/title_56.cpp

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

$(CONTENTDIR)/Text.cpp: Text.txt
	$(FILEWRAP)  -o $@ Text.txt

$(CONTENTDIR)/arial_36.cpp: arial_36.pvr
	$(FILEWRAP)  -o $@ arial_36.pvr

$(CONTENTDIR)/starjout_60.cpp: starjout_60.pvr
	$(FILEWRAP)  -o $@ starjout_60.pvr

$(CONTENTDIR)/title_36.cpp: title_36.pvr
	$(FILEWRAP)  -o $@ title_36.pvr

$(CONTENTDIR)/title_46.cpp: title_46.pvr
	$(FILEWRAP)  -o $@ title_46.pvr

$(CONTENTDIR)/title_56.cpp: title_56.pvr
	$(FILEWRAP)  -o $@ title_56.pvr

############################################################################
# End of file (content.mak)
############################################################################
