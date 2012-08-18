#
# File			Makefile
# Title			Makes the PVREngine
# Author		PowerVR
#
# Copyright		Copyright 2003-2004 by Imagination Technologies Limited.
#

.PHONY: clean
.PHONY: build_tools

BUILD_API = OGLES2
SDKDIR  = ../../../../..

include $(SDKDIR)/Builds/$(BUILD_API)/$(PLATFORM)/make_platform.mak

OUTNAME = libPVREngine.a

ifndef SHELLOS
SHELLOS = Linux$(WS)
endif

ifndef SHELLAPI
SHELLAPI = KEGL
endif

SHELLOSPATH = $(SDKDIR)/Shell/OS/$(SHELLOS)
SHELLAPIPATH = $(SDKDIR)/Shell/API/$(SHELLAPI)

INCLUDES += -I$(SDKDIR)/Tools -I$(SDKDIR)/Tools/$(BUILD_API) -I$(SDKDIR)/Extras/PVREngine/Include -I$(SDKDIR)/Extras/PVREngine/Include/$(BUILD_API)
VPATH = $(SDKDIR)/Tools $(SDKDIR)/Tools/$(BUILD_API) $(SDKDIR)/Extras/PVREngine/Source $(SDKDIR)/Extras/PVREngine/Source/$(BUILD_API)

INCLUDES += -I$(SDKDIR)/Tools/$(BUILD_API) -I$(SDKDIR)/Shell -I$(SHELLAPIPATH) -I$(SHELLOSPATH) -I../../.. $(addprefix -I,$(PLAT_INC))
VPATH += .. : ../.. : ../../.. : $(SDKDIR)/Shell : $(SHELLAPIPATH) : $(SHELLOSPATH) : $(SDKDIR)/Tools

OBJECTS = PVREngine.o \
	PVRShell.o	\
	PVRShellAPI.o	\
	PVRShellOS.o	\
	UniformHandlerBase.o	\
	UniformHandler.o	\
	UniformBase.o	\
	Uniform.o	\
	TimeController.o	\
	TextureManager.o	\
	TextureBase.o	\
	Texture.o	\
	SimpleCamera.o	\
	PVRESettingsBase.o	\
	PVRESettings.o	\
	Plane.o	\
	OptionsMenu.o	\
	Option.o	\
	MeshManager.o	\
	MeshBase.o	\
	Mesh.o	\
	MaterialManager.o	\
	MaterialBase.o	\
	Material.o	\
	LightManager.o	\
	LightBase.o	\
	Light.o	\
	ConsoleLog.o	\
	ContextManager.o	\
	BoundingHex.o	\
	BoundingBox.o
		
OBJECTS := $(addprefix $(PLAT_OBJPATH)/, $(OBJECTS))

all: $(PLAT_OBJPATH)/$(OUTNAME)

$(PLAT_OBJPATH)/$(OUTNAME) : $(OBJECTS) 
	@mkdir -p $(PLAT_OBJPATH)
	@echo "+a+ $@"
	@$(PLAT_AR) -r $(PLAT_OBJPATH)/$(OUTNAME) $(OBJECTS)

$(PLAT_OBJPATH)/%.o: %.cpp
	@mkdir -p $(PLAT_OBJPATH)
	@echo "+c+ $(OUTNAME) $@"
	$(PLAT_CC) -c $(INCLUDES) $(PLAT_CFLAGS) $^ -o$@

# Builds the tools if necessary
build_tools: $(SDKDIR)/Tools/$(BUILD_API)/Build/LinuxGeneric/$(PLAT_OBJPATH)/libogles2tools.a

$(SDKDIR)/Tools/$(BUILD_API)/Build/LinuxGeneric/$(PLAT_OBJPATH)/libogles2tools.a:
	@echo "***************************************"
	@echo "* Tools not built yet, building them. *"
	@echo "***************************************"
	make -C $(SDKDIR)/Tools/$(BUILD_API)/Build/LinuxGeneric/ clean $(MAKECMDGOALS)
	make -C $(SDKDIR)/Tools/$(BUILD_API)/Build/LinuxGeneric/ $(MAKECMDGOALS)
