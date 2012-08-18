#
# File			Makefile
# Title			Demo makefile
#
# Copyright		Copyright (C) Imagination Technologies Limited.
#

.PHONY: clean

SDKDIR  = ../../../../..
OUTNAME = OGLES2ParallaxBumpMap

OBJECTS +=	\
           FragShader.o	\
           VertShader.o	\
           base_COLOR.o	\
           base_NRM.o	\
           base_DISP.o	\
           base_SPEC.o	\
           Box.o

include $(SDKDIR)/Builds/OGLES2/LinuxGeneric/make_demo.mak

../../Content/FragShader.cpp ../../Content/VertShader.cpp ../../Content/base_COLOR.cpp ../../Content/base_NRM.cpp ../../Content/base_DISP.cpp ../../Content/base_SPEC.cpp ../../Content/Box.cpp: build_textures_and_shaders 

%.o: ../../Content/%.cpp
	$(CC) -c $(COMMON_INCLUDES) $(PLAT_INCLUDES) $(INCLUDES) $(COMMON_CFLAGS) $(PLAT_CFLAGS) $(CFLAGS) $^ -o$@

clean:
	-rm -rf $(PLAT_OBJPATH)/*.o
	make -C ../.. -f content.mak clean
