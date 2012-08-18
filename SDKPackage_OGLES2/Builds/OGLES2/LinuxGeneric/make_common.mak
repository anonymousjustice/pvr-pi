#
# File			make_common.mak
# Title			Used by the other makefiles
# Author		PowerVR
#
# Copyright		Copyright 2003-2004 by Imagination Technologies Limited.
#


ifndef PLATFORM
$(error Error building application. You must define the PLATFORM variable to be the value of the target platform you want to build for. )
endif

include $(SDKDIR)/Builds/OGLES2/$(PLATFORM)/make_platform.mak

# Compile options for every OGLES2 linux builds
COMMON_CFLAGS = -DBUILD_OGLES2 -Wall
COMMON_INCLUDES = \
	-I$(SDKDIR)/Builds/OGLES2/$(PLATFORM)/Include \
	-I$(SDKDIR)/Builds/OGLES2/Include \
	-I/usr/X11R6/include

# Calculates the output directory OBJPATH
ifdef Debug
	DebugReleasePath = Debug$(WS)
	COMMON_CFLAGS += -DDEBUG -g -DDLL_METRIC
else
	DebugReleasePath = Release$(WS)
	COMMON_CFLAGS += -DRELEASE -O2
endif

COMMON_INCLUDES += $(addprefix -I, $(PLAT_INC))

#PLAT_OBJPATH = ../$(PLATFORM)/$(DebugReleasePath)
OBJECTS := $(addprefix $(PLAT_OBJPATH)/, $(OBJECTS))

# Final step to link the app. It's up to the calling makefile to specify LINKCOMMAND
$(PLAT_OBJPATH)/$(OUTNAME) : $(ADDITIONAL_DEPENDENCIES) $(OBJECTS) 
	@-mkdir -p $(PLAT_OBJPATH)
	$(LINKCOMMAND)

# Step to compile source files
$(PLAT_OBJPATH)/%.o: %.cpp
	@mkdir -p $(PLAT_OBJPATH)
	@$(PLAT_CC) -c $(COMMON_INCLUDES) $(PLAT_INCLUDES) $(INCLUDES) $(COMMON_CFLAGS) $(PLAT_CFLAGS) $(CFLAGS) $^ -o$@

# Cleaning
clean:
	rm -rf $(PLAT_OBJPATH) *.o

