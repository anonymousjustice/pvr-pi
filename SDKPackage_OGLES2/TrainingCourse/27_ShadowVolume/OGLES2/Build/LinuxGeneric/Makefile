#
# File			Makefile
# Title			Demo makefile
#
# Copyright		Copyright (C) Imagination Technologies Limited.
#

.PHONY: clean

SDKDIR  = ../../../../..
OUTNAME = OGLES2ShadowVolume

OBJECTS +=	\
           Background.o	\
           Rust.o	\
           BaseFragShader.o	\
           BaseVertShader.o	\
           ConstFragShader.o	\
           ShadowVolVertShader.o	\
           FullscreenVertShader.o	\
           scene.o

include $(SDKDIR)/Builds/OGLES2/LinuxGeneric/make_demo.mak

../../Content/Background.cpp ../../Content/Rust.cpp ../../Content/BaseFragShader.cpp ../../Content/BaseVertShader.cpp ../../Content/ConstFragShader.cpp ../../Content/ShadowVolVertShader.cpp ../../Content/FullscreenVertShader.cpp ../../Content/scene.cpp: build_textures_and_shaders 

%.o: ../../Content/%.cpp
	$(CC) -c $(COMMON_INCLUDES) $(PLAT_INCLUDES) $(INCLUDES) $(COMMON_CFLAGS) $(PLAT_CFLAGS) $(CFLAGS) $^ -o$@

clean:
	-rm -rf $(PLAT_OBJPATH)/*.o
	make -C ../.. -f content.mak clean
