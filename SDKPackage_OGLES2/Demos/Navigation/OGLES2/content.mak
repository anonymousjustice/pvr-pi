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
	Alphabet.pvr \
	Road.pvr \
	StreetSigns.pvr

BIN_SHADERS = \
	AlphaMaskFragShader.fsc \
	AntiAliasedLinesFragShader.fsc \
	AntiAliasedLinesVertShader.vsc \
	FragShader.fsc \
	VertShader.vsc \
	PivotQuadFragShader.fsc \
	PivotQuadMaskedFragShader.fsc \
	PivotQuadVertShader.vsc

RESOURCES = \
	$(CONTENTDIR)/Alphabet.cpp \
	$(CONTENTDIR)/Road.cpp \
	$(CONTENTDIR)/StreetSigns.cpp \
	$(CONTENTDIR)/AlphaMaskFragShader.cpp \
	$(CONTENTDIR)/AntiAliasedLinesFragShader.cpp \
	$(CONTENTDIR)/AntiAliasedLinesVertShader.cpp \
	$(CONTENTDIR)/FragShader.cpp \
	$(CONTENTDIR)/VertShader.cpp \
	$(CONTENTDIR)/PivotQuadFragShader.cpp \
	$(CONTENTDIR)/PivotQuadMaskedFragShader.cpp \
	$(CONTENTDIR)/PivotQuadVertShader.cpp \
	$(CONTENTDIR)/cameratrack.cpp \
	$(CONTENTDIR)/Landmark_meshes.cpp \
	$(CONTENTDIR)/LandUseA_meshes.cpp \
	$(CONTENTDIR)/LandUseB_meshes.cpp \
	$(CONTENTDIR)/MajHwys_meshes.cpp \
	$(CONTENTDIR)/MajHwyShield_text.cpp \
	$(CONTENTDIR)/RailRds_meshes.cpp \
	$(CONTENTDIR)/SecHwys_meshes.cpp \
	$(CONTENTDIR)/SecHwyShield_text.cpp \
	$(CONTENTDIR)/Signs_billboards.cpp \
	$(CONTENTDIR)/Streets_meshes.cpp \
	$(CONTENTDIR)/Streets_text.cpp \
	$(CONTENTDIR)/WaterPoly_meshes.cpp \
	$(CONTENTDIR)/WaterSeg_meshes.cpp

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

Alphabet.pvr: $(MEDIAPATH)/Alphabet.png
	$(PVRTEXTOOL) -m -fOGL88 -i$(MEDIAPATH)/Alphabet.png -o$@

Road.pvr: $(MEDIAPATH)/Road.png
	$(PVRTEXTOOL) -m -fOGL88 -i$(MEDIAPATH)/Road.png -o$@

StreetSigns.pvr: $(MEDIAPATH)/StreetSigns.png
	$(PVRTEXTOOL) -m -fOGL4444 -i$(MEDIAPATH)/StreetSigns.png -o$@

$(CONTENTDIR)/Alphabet.cpp: Alphabet.pvr
	$(FILEWRAP)  -o $@ Alphabet.pvr

$(CONTENTDIR)/Road.cpp: Road.pvr
	$(FILEWRAP)  -o $@ Road.pvr

$(CONTENTDIR)/StreetSigns.cpp: StreetSigns.pvr
	$(FILEWRAP)  -o $@ StreetSigns.pvr

$(CONTENTDIR)/AlphaMaskFragShader.cpp: AlphaMaskFragShader.fsh AlphaMaskFragShader.fsc
	$(FILEWRAP)  -s  -o $@ AlphaMaskFragShader.fsh
	-$(FILEWRAP)  -oa $@ AlphaMaskFragShader.fsc

$(CONTENTDIR)/AntiAliasedLinesFragShader.cpp: AntiAliasedLinesFragShader.fsh AntiAliasedLinesFragShader.fsc
	$(FILEWRAP)  -s  -o $@ AntiAliasedLinesFragShader.fsh
	-$(FILEWRAP)  -oa $@ AntiAliasedLinesFragShader.fsc

$(CONTENTDIR)/AntiAliasedLinesVertShader.cpp: AntiAliasedLinesVertShader.vsh AntiAliasedLinesVertShader.vsc
	$(FILEWRAP)  -s  -o $@ AntiAliasedLinesVertShader.vsh
	-$(FILEWRAP)  -oa $@ AntiAliasedLinesVertShader.vsc

$(CONTENTDIR)/FragShader.cpp: FragShader.fsh FragShader.fsc
	$(FILEWRAP)  -s  -o $@ FragShader.fsh
	-$(FILEWRAP)  -oa $@ FragShader.fsc

$(CONTENTDIR)/VertShader.cpp: VertShader.vsh VertShader.vsc
	$(FILEWRAP)  -s  -o $@ VertShader.vsh
	-$(FILEWRAP)  -oa $@ VertShader.vsc

$(CONTENTDIR)/PivotQuadFragShader.cpp: PivotQuadFragShader.fsh PivotQuadFragShader.fsc
	$(FILEWRAP)  -s  -o $@ PivotQuadFragShader.fsh
	-$(FILEWRAP)  -oa $@ PivotQuadFragShader.fsc

$(CONTENTDIR)/PivotQuadMaskedFragShader.cpp: PivotQuadMaskedFragShader.fsh PivotQuadMaskedFragShader.fsc
	$(FILEWRAP)  -s  -o $@ PivotQuadMaskedFragShader.fsh
	-$(FILEWRAP)  -oa $@ PivotQuadMaskedFragShader.fsc

$(CONTENTDIR)/PivotQuadVertShader.cpp: PivotQuadVertShader.vsh PivotQuadVertShader.vsc
	$(FILEWRAP)  -s  -o $@ PivotQuadVertShader.vsh
	-$(FILEWRAP)  -oa $@ PivotQuadVertShader.vsc

$(CONTENTDIR)/cameratrack.cpp: cameratrack.pod
	$(FILEWRAP)  -o $@ cameratrack.pod

$(CONTENTDIR)/Landmark_meshes.cpp: Landmark_meshes.nav
	$(FILEWRAP)  -o $@ Landmark_meshes.nav

$(CONTENTDIR)/LandUseA_meshes.cpp: LandUseA_meshes.nav
	$(FILEWRAP)  -o $@ LandUseA_meshes.nav

$(CONTENTDIR)/LandUseB_meshes.cpp: LandUseB_meshes.nav
	$(FILEWRAP)  -o $@ LandUseB_meshes.nav

$(CONTENTDIR)/MajHwys_meshes.cpp: MajHwys_meshes.nav
	$(FILEWRAP)  -o $@ MajHwys_meshes.nav

$(CONTENTDIR)/MajHwyShield_text.cpp: MajHwyShield_text.nav
	$(FILEWRAP)  -o $@ MajHwyShield_text.nav

$(CONTENTDIR)/RailRds_meshes.cpp: RailRds_meshes.nav
	$(FILEWRAP)  -o $@ RailRds_meshes.nav

$(CONTENTDIR)/SecHwys_meshes.cpp: SecHwys_meshes.nav
	$(FILEWRAP)  -o $@ SecHwys_meshes.nav

$(CONTENTDIR)/SecHwyShield_text.cpp: SecHwyShield_text.nav
	$(FILEWRAP)  -o $@ SecHwyShield_text.nav

$(CONTENTDIR)/Signs_billboards.cpp: Signs_billboards.nav
	$(FILEWRAP)  -o $@ Signs_billboards.nav

$(CONTENTDIR)/Streets_meshes.cpp: Streets_meshes.nav
	$(FILEWRAP)  -o $@ Streets_meshes.nav

$(CONTENTDIR)/Streets_text.cpp: Streets_text.nav
	$(FILEWRAP)  -o $@ Streets_text.nav

$(CONTENTDIR)/WaterPoly_meshes.cpp: WaterPoly_meshes.nav
	$(FILEWRAP)  -o $@ WaterPoly_meshes.nav

$(CONTENTDIR)/WaterSeg_meshes.cpp: WaterSeg_meshes.nav
	$(FILEWRAP)  -o $@ WaterSeg_meshes.nav

AlphaMaskFragShader.fsc: AlphaMaskFragShader.fsh
	$(PVRUNISCO) AlphaMaskFragShader.fsh $@  -f 

AntiAliasedLinesFragShader.fsc: AntiAliasedLinesFragShader.fsh
	$(PVRUNISCO) AntiAliasedLinesFragShader.fsh $@  -f 

AntiAliasedLinesVertShader.vsc: AntiAliasedLinesVertShader.vsh
	$(PVRUNISCO) AntiAliasedLinesVertShader.vsh $@  -v 

FragShader.fsc: FragShader.fsh
	$(PVRUNISCO) FragShader.fsh $@  -f 

VertShader.vsc: VertShader.vsh
	$(PVRUNISCO) VertShader.vsh $@  -v 

PivotQuadFragShader.fsc: PivotQuadFragShader.fsh
	$(PVRUNISCO) PivotQuadFragShader.fsh $@  -f 

PivotQuadMaskedFragShader.fsc: PivotQuadMaskedFragShader.fsh
	$(PVRUNISCO) PivotQuadMaskedFragShader.fsh $@  -f 

PivotQuadVertShader.vsc: PivotQuadVertShader.vsh
	$(PVRUNISCO) PivotQuadVertShader.vsh $@  -v 

############################################################################
# End of file (content.mak)
############################################################################
