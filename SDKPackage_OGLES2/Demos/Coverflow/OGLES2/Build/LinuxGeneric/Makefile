#
# File			Makefile
# Title			Demo makefile
#
# Copyright		Copyright Imagination Technologies Limited.
#

.PHONY: clean

SDKDIR  = ../../../../..
OUTNAME = OGLES2Coverflow

OBJECTS +=	\
           Album1.o	\
           Album2.o	\
           Album3.o	\
           Album4.o	\
           Album5.o	\
           Album6.o	\
           Album7.o	\
           Album8.o	\
           Album9.o	\
           Album10.o	\
           Album11.o	\
           Album12.o	\
           Album13.o	\
           Album14.o	\
           Album15.o	\
           Album16.o	\
           FragShader.o	\
           VertShader.o

include $(SDKDIR)/Builds/OGLES2/LinuxGeneric/make_demo.mak

../../Content/Album1.cpp ../../Content/Album2.cpp ../../Content/Album3.cpp ../../Content/Album4.cpp ../../Content/Album5.cpp ../../Content/Album6.cpp ../../Content/Album7.cpp ../../Content/Album8.cpp ../../Content/Album9.cpp ../../Content/Album10.cpp ../../Content/Album11.cpp ../../Content/Album12.cpp ../../Content/Album13.cpp ../../Content/Album14.cpp ../../Content/Album15.cpp ../../Content/Album16.cpp ../../Content/FragShader.cpp ../../Content/VertShader.cpp: build_textures_and_shaders 

%.o: ../../Content/%.cpp
	$(CC) -c $(COMMON_INCLUDES) $(PLAT_INCLUDES) $(INCLUDES) $(COMMON_CFLAGS) $(PLAT_CFLAGS) $(CFLAGS) $^ -o$@

clean:
	-rm -rf $(PLAT_OBJPATH)/*.o
	make -C ../.. -f content.mak clean
