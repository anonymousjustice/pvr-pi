#
# File			make_platform.mak
# Title			Platform specific makefile
# Author		PowerVR
#
# Copyright		Copyright 2003-2004 by Imagination Technologies Limited.
#

# The following line was removed for Raspberry Pi distribution. To cross-compile for the Pi, set CROSS_COMPILE.
#CROSS_COMPILE ?= arm-none-linux-gnueabi-

ifdef TOOLCHAIN
PLAT_CC  = $(TOOLCHAIN)/bin/$(CROSS_COMPILE)gcc
PLAT_CPP = $(TOOLCHAIN)/bin/$(CROSS_COMPILE)g++
PLAT_AR  = $(TOOLCHAIN)/bin/$(CROSS_COMPILE)ar
else
PLAT_CC  = $(CROSS_COMPILE)gcc
PLAT_CPP = $(CROSS_COMPILE)g++
PLAT_AR  = $(CROSS_COMPILE)ar
endif

ifeq "$(X11BUILD)" "1"
	ifndef X11ROOT
		$(error When building an X11 BUILD you must set X11ROOT to point at the location where your X11 headers and libs can be found.)
	endif
	ifeq "$(EWSBUILD)" "1"
		$(error Cannot have both X11BUILD and EWSBUILD enabled at the same time)
	endif
	WS_LIBS = -L$(X11ROOT)/lib -lX11 -lXau
	WS_RPATH = $(X11ROOT)/lib
	WS_INC  = $(X11ROOT)/include
	WS = X11
else
	ifeq "$(EWSBUILD)" "1"
		PLAT_CFLAGS = -DEWS
		WS_LIBS = -lews
		WS_INC =
		WS = EWS
	else
		ifeq "$(PIBUILD)" "1"
			WS_LIBS = -L/opt/vc/lib -lbcm_host
			WS_INC = /opt/vc/include/interface/vcos/pthreads
			WS = Pi
			PLAT_CFLAGS = -DRASPBERRY_PI -DHAVE_LIBBCM_HOST -DUSE_EXTERNAL_LIBBCM_HOST \
					-I/opt/vc/include
		else
			WS_LIBS =
			WS_RPATH = 
			WS_INC  = 
			WS = Raw
		endif
	endif
endif

LIBDIR ?= $(SDKDIR)/Builds/OGLES2/$(PLATFORM)/Lib
LIBDIR_FLAGS = -L$(LIBDIR) -Wl,--rpath-link,$(LIBDIR):$(WS_RPATH)

ifdef Debug
DEBUG_RELEASE = Debug
PLAT_CFLAGS   += -DBUILD_OGLES2 -Wall -DDEBUG -g -DKEYPAD_INPUT="\"/dev/input/event0\""
else
DEBUG_RELEASE = Release
PLAT_CFLAGS   += -DBUILD_OGLES2 -Wall -DRELEASE -O2 -DKEYPAD_INPUT="\"/dev/input/event0\""
endif

ifdef SDKDIR
SDKDIR   := $(shell cd $(SDKDIR) && pwd)
PLAT_INC  = 	$(WS_INC) \
		$(SDKDIR)/Builds/OGLES2/Include
endif

PLAT_OBJPATH = ../$(PLATFORM)/$(DEBUG_RELEASE)$(WS)
PLAT_LINK = $(LIBDIR_FLAGS) -lEGL -lGLESv2 $(WS_LIBS)

