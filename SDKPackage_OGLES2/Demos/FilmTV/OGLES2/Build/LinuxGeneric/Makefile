#
# File			Makefile
# Title			Demo makefile
#
# Copyright		Copyright Imagination Technologies Limited.
#

.PHONY: clean

SDKDIR  = ../../../../..
OUTNAME = OGLES2FilmTV

OBJECTS +=	\
           Table.o	\
           Floor.o	\
           Wall.o	\
           TV.o	\
           TVCase.o	\
           TVSpeaker.o	\
           Alum.o	\
           Skirting.o	\
           Camera.o	\
           FragShader.o	\
           BWFragShader.o	\
           VertShader.o	\
           FilmTVScene.o

include $(SDKDIR)/Builds/OGLES2/LinuxGeneric/make_demo.mak

../../Content/Table.cpp ../../Content/Floor.cpp ../../Content/Wall.cpp ../../Content/TV.cpp ../../Content/TVCase.cpp ../../Content/TVSpeaker.cpp ../../Content/Alum.cpp ../../Content/Skirting.cpp ../../Content/Camera.cpp ../../Content/FragShader.cpp ../../Content/BWFragShader.cpp ../../Content/VertShader.cpp ../../Content/FilmTVScene.cpp: build_textures_and_shaders 

%.o: ../../Content/%.cpp
	$(CC) -c $(COMMON_INCLUDES) $(PLAT_INCLUDES) $(INCLUDES) $(COMMON_CFLAGS) $(PLAT_CFLAGS) $(CFLAGS) $^ -o$@

clean:
	-rm -rf $(PLAT_OBJPATH)/*.o
	make -C ../.. -f content.mak clean
