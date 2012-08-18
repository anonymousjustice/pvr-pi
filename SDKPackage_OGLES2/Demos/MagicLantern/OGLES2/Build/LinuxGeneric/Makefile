#
# File			Makefile
# Title			Demo makefile
#
# Copyright		Copyright (C) Imagination Technologies Limited.
#

.PHONY: clean

SDKDIR  = ../../../../..
OUTNAME = OGLES2MagicLantern

OBJECTS +=	\
           Marble.o	\
           Floor.o	\
           LanternCubemap.o	\
           MagicLanternShaders.o	\
           MagicLantern.o

include $(SDKDIR)/Builds/OGLES2/LinuxGeneric/make_demo.mak

../../Content/Marble.cpp ../../Content/Floor.cpp ../../Content/LanternCubemap.cpp ../../Content/MagicLanternShaders.cpp ../../Content/MagicLantern.cpp: build_textures_and_shaders 

%.o: ../../Content/%.cpp
	$(CC) -c $(COMMON_INCLUDES) $(PLAT_INCLUDES) $(INCLUDES) $(COMMON_CFLAGS) $(PLAT_CFLAGS) $(CFLAGS) $^ -o$@

clean:
	-rm -rf $(PLAT_OBJPATH)/*.o
	make -C ../.. -f content.mak clean
