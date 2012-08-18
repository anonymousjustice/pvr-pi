#
# File			Makefile
# Title			Demo makefile
#
# Copyright		Copyright (C) Imagination Technologies Limited.
#

.PHONY: clean

SDKDIR  = ../../../../..
OUTNAME = OGLES2EdgeDetection

OBJECTS +=	\
           PreFragShader.o	\
           PreVertShader.o	\
           PostFragShader.o	\
           PostVertShader.o	\
           SketchObject.o

include $(SDKDIR)/Builds/OGLES2/LinuxGeneric/make_demo.mak

../../Content/PreFragShader.cpp ../../Content/PreVertShader.cpp ../../Content/PostFragShader.cpp ../../Content/PostVertShader.cpp ../../Content/SketchObject.cpp: build_textures_and_shaders 

%.o: ../../Content/%.cpp
	$(CC) -c $(COMMON_INCLUDES) $(PLAT_INCLUDES) $(INCLUDES) $(COMMON_CFLAGS) $(PLAT_CFLAGS) $(CFLAGS) $^ -o$@

clean:
	-rm -rf $(PLAT_OBJPATH)/*.o
	make -C ../.. -f content.mak clean
