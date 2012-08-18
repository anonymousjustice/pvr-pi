#
# File			Makefile
# Title			Demo makefile
#
# Copyright		Copyright (C) Imagination Technologies Limited.
#

.PHONY: clean

SDKDIR  = ../../../../..
OUTNAME = OGLES2IntroducingPrint3D

OBJECTS +=	\
           Text.o	\
           arial_36.o	\
           starjout_60.o	\
           title_36.o	\
           title_46.o	\
           title_56.o

include $(SDKDIR)/Builds/OGLES2/LinuxGeneric/make_demo.mak

../../Content/Text.cpp ../../Content/arial_36.cpp ../../Content/starjout_60.cpp ../../Content/title_36.cpp ../../Content/title_46.cpp ../../Content/title_56.cpp: build_textures_and_shaders 

%.o: ../../Content/%.cpp
	$(CC) -c $(COMMON_INCLUDES) $(PLAT_INCLUDES) $(INCLUDES) $(COMMON_CFLAGS) $(PLAT_CFLAGS) $(CFLAGS) $^ -o$@

clean:
	-rm -rf $(PLAT_OBJPATH)/*.o
	make -C ../.. -f content.mak clean
