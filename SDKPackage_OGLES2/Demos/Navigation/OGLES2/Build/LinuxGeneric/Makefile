#
# File			Makefile
# Title			Demo makefile
#
# Copyright		Copyright (C) Imagination Technologies Limited.
#

.PHONY: clean

SDKDIR  = ../../../../..
OUTNAME = OGLES2Navigation

OBJECTS +=	\
           Alphabet.o	\
           Road.o	\
           StreetSigns.o	\
           AlphaMaskFragShader.o	\
           AntiAliasedLinesFragShader.o	\
           AntiAliasedLinesVertShader.o	\
           FragShader.o	\
           VertShader.o	\
           PivotQuadFragShader.o	\
           PivotQuadMaskedFragShader.o	\
           PivotQuadVertShader.o	\
           cameratrack.o	\
           Landmark_meshes.o	\
           LandUseA_meshes.o	\
           LandUseB_meshes.o	\
           MajHwys_meshes.o	\
           MajHwyShield_text.o	\
           RailRds_meshes.o	\
           SecHwys_meshes.o	\
           SecHwyShield_text.o	\
           Signs_billboards.o	\
           Streets_meshes.o	\
           Streets_text.o	\
           WaterPoly_meshes.o	\
           WaterSeg_meshes.o

include $(SDKDIR)/Builds/OGLES2/LinuxGeneric/make_demo.mak

../../Content/Alphabet.cpp ../../Content/Road.cpp ../../Content/StreetSigns.cpp ../../Content/AlphaMaskFragShader.cpp ../../Content/AntiAliasedLinesFragShader.cpp ../../Content/AntiAliasedLinesVertShader.cpp ../../Content/FragShader.cpp ../../Content/VertShader.cpp ../../Content/PivotQuadFragShader.cpp ../../Content/PivotQuadMaskedFragShader.cpp ../../Content/PivotQuadVertShader.cpp ../../Content/cameratrack.cpp ../../Content/Landmark_meshes.cpp ../../Content/LandUseA_meshes.cpp ../../Content/LandUseB_meshes.cpp ../../Content/MajHwys_meshes.cpp ../../Content/MajHwyShield_text.cpp ../../Content/RailRds_meshes.cpp ../../Content/SecHwys_meshes.cpp ../../Content/SecHwyShield_text.cpp ../../Content/Signs_billboards.cpp ../../Content/Streets_meshes.cpp ../../Content/Streets_text.cpp ../../Content/WaterPoly_meshes.cpp ../../Content/WaterSeg_meshes.cpp: build_textures_and_shaders 

%.o: ../../Content/%.cpp
	$(CC) -c $(COMMON_INCLUDES) $(PLAT_INCLUDES) $(INCLUDES) $(COMMON_CFLAGS) $(PLAT_CFLAGS) $(CFLAGS) $^ -o$@

clean:
	-rm -rf $(PLAT_OBJPATH)/*.o
	make -C ../.. -f content.mak clean
