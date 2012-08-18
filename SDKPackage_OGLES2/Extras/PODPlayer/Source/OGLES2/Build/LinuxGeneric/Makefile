#
# File			Makefile
# Title			Makes the PODPlayer using the PVREngine and PVRTools
# Author		PowerVR
#
# Copyright		Copyright 2003-2004 by Imagination Technologies Limited.
#

.PHONY: clean

BUILD_API = OGLES2
SDKDIR  = ../../../../../..
OUTNAME = $(BUILD_API)PODPlayer
INCLUDES += -I$(SDKDIR)/Tools -I$(SDKDIR)/Tools/$(BUILD_API) -I$(SDKDIR)/Extras/PVREngine/Include \
			-I$(SDKDIR)/Extras/PVREngine/Include/$(BUILD_API)
INCLUDES += -I$(SDKDIR)/Shell -I$(SDKDIR)/Shell/API/KEGL -I$(SHELLOSPATH) -I../../..
VPATH += .. : ../.. : ../../..

LINK = -L$(SDKDIR)/Tools/$(BUILD_API)/Build/$(PLATFORM)/$(DebugReleasePath) \
	   -L$(SDKDIR)/Extras/PVREngine/$(BUILD_API)/Build/LinuxGeneric/$(PLAT_OBJPATH) \
	   -L$(SDKDIR)/Builds/OGLES2/$(PLATFORM)/Lib	\
	   -lPVREngine -logles2tools -lGLESv2 -lEGL  -lm  
LINKCOMMAND = $(PLAT_CPP) -o $(PLAT_OBJPATH)/$(OUTNAME) $(OBJECTS) $(LINK) $(PLAT_LINK)



.PHONY: build_tools

# Files to compile
OBJECTS += PODPlayer.o PVRES.o PVRESParser.o

include $(SDKDIR)/Builds/$(BUILD_API)/LinuxGeneric/make_common.mak

ifndef SHELLOS
SHELLOS = Linux$(WS)
endif

SHELLOSPATH = $(SDKDIR)/Shell/OS/$(SHELLOS)

