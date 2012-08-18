#
# File			Makefile
# Title			Demo makefile
#
# Copyright		Copyright Imagination Technologies Limited.
#

.PHONY: clean

SDKDIR  = ../../../../..
OUTNAME = OGLES2IntroducingPOD

OBJECTS +=	\
           tex_base.o	\
           tex_arm.o	\
           FragShader.o	\
           VertShader.o	\
           Scene.o

include $(SDKDIR)/Builds/OGLES2/LinuxGeneric/make_demo.mak

../../Content/tex_base.cpp ../../Content/tex_arm.cpp ../../Content/FragShader.cpp ../../Content/VertShader.cpp ../../Content/Scene.cpp: build_textures_and_shaders 

%.o: ../../Content/%.cpp
	$(CC) -c $(COMMON_INCLUDES) $(PLAT_INCLUDES) $(INCLUDES) $(COMMON_CFLAGS) $(PLAT_CFLAGS) $(CFLAGS) $^ -o$@

clean:
	-rm -rf $(PLAT_OBJPATH)/*.o
	make -C ../.. -f content.mak clean
