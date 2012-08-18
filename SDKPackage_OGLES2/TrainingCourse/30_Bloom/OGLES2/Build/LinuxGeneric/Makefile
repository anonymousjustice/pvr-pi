#
# File			Makefile
# Title			Demo makefile
#
# Copyright		Copyright Imagination Technologies Limited.
#

.PHONY: clean

SDKDIR  = ../../../../..
OUTNAME = OGLES2Bloom

OBJECTS +=	\
           BaseTex.o	\
           bloom_mapping.o	\
           PostBloomFragShader.o	\
           PostBloomVertShader.o	\
           PreBloomFragShader.o	\
           PreBloomVertShader.o	\
           BlurFragShader.o	\
           BlurVertShader.o	\
           FragShader.o	\
           VertShader.o	\
           Mask.o

include $(SDKDIR)/Builds/OGLES2/LinuxGeneric/make_demo.mak

../../Content/BaseTex.cpp ../../Content/bloom_mapping.cpp ../../Content/PostBloomFragShader.cpp ../../Content/PostBloomVertShader.cpp ../../Content/PreBloomFragShader.cpp ../../Content/PreBloomVertShader.cpp ../../Content/BlurFragShader.cpp ../../Content/BlurVertShader.cpp ../../Content/FragShader.cpp ../../Content/VertShader.cpp ../../Content/Mask.cpp: build_textures_and_shaders 

%.o: ../../Content/%.cpp
	$(CC) -c $(COMMON_INCLUDES) $(PLAT_INCLUDES) $(INCLUDES) $(COMMON_CFLAGS) $(PLAT_CFLAGS) $(CFLAGS) $^ -o$@

clean:
	-rm -rf $(PLAT_OBJPATH)/*.o
	make -C ../.. -f content.mak clean
