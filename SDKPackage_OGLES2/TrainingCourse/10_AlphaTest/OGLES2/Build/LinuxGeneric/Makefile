#
# File			Makefile
# Title			Demo makefile
#
# Copyright		Copyright Imagination Technologies Limited.
#

.PHONY: clean

SDKDIR  = ../../../../..
OUTNAME = OGLES2AlphaTest

OBJECTS +=	\
           Wallwire.o	\
           TexFragShader.o	\
           DiscardFragShader.o	\
           VertShader.o

include $(SDKDIR)/Builds/OGLES2/LinuxGeneric/make_demo.mak

../../Content/Wallwire.cpp ../../Content/TexFragShader.cpp ../../Content/DiscardFragShader.cpp ../../Content/VertShader.cpp: build_textures_and_shaders 

%.o: ../../Content/%.cpp
	$(CC) -c $(COMMON_INCLUDES) $(PLAT_INCLUDES) $(INCLUDES) $(COMMON_CFLAGS) $(PLAT_CFLAGS) $(CFLAGS) $^ -o$@

clean:
	-rm -rf $(PLAT_OBJPATH)/*.o
	make -C ../.. -f content.mak clean
