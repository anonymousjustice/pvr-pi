#
# File			Makefile
# Title			Demo makefile
#
# Copyright		Copyright (C) Imagination Technologies Limited.
#

.PHONY: clean

SDKDIR  = ../../../../..
OUTNAME = OGLES2Water

OBJECTS +=	\
           NewNormalMap.o	\
           Mountain.o	\
           wood.o	\
           sail.o	\
           MountainFloor.o	\
           FragShader.o	\
           VertShader.o	\
           SkyboxFShader.o	\
           SkyboxVShader.o	\
           ModelFShader.o	\
           ModelVShader.o	\
           Tex2DFShader.o	\
           Tex2DVShader.o	\
           PlaneTexFShader.o	\
           PlaneTexVShader.o	\
           Scene.o

include $(SDKDIR)/Builds/OGLES2/LinuxGeneric/make_demo.mak

../../Content/NewNormalMap.cpp ../../Content/Mountain.cpp ../../Content/wood.cpp ../../Content/sail.cpp ../../Content/MountainFloor.cpp ../../Content/FragShader.cpp ../../Content/VertShader.cpp ../../Content/SkyboxFShader.cpp ../../Content/SkyboxVShader.cpp ../../Content/ModelFShader.cpp ../../Content/ModelVShader.cpp ../../Content/Tex2DFShader.cpp ../../Content/Tex2DVShader.cpp ../../Content/PlaneTexFShader.cpp ../../Content/PlaneTexVShader.cpp ../../Content/Scene.cpp: build_textures_and_shaders 

%.o: ../../Content/%.cpp
	$(CC) -c $(COMMON_INCLUDES) $(PLAT_INCLUDES) $(INCLUDES) $(COMMON_CFLAGS) $(PLAT_CFLAGS) $(CFLAGS) $^ -o$@

clean:
	-rm -rf $(PLAT_OBJPATH)/*.o
	make -C ../.. -f content.mak clean
