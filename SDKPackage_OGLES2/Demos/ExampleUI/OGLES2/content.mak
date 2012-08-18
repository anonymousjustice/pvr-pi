#--------------------------------------------------------------------------
# Name         : content.mak
# Title        : Makefile to build content files
#
# Copyright    : Copyright (C)  Imagination Technologies Limited.
#              : No part of this software, either material or conceptual 
#              : may be copied or distributed, transmitted, transcribed,
#              : stored in a retrieval system or translated into any 
#              : human or computer language in any form by any means,
#              : electronic, mechanical, manual or other-wise, or 
#              : disclosed to third parties without the express written
#              : permission of VideoLogic Limited, Unit 8, HomePark
#              : Industrial Estate, King's Langley, Hertfordshire,
#              : WD4 8LZ, U.K.
#
# Description  : Makefile to build content files for demos in the PowerVR SDK
#
# Platform     :
#
#--------------------------------------------------------------------------

#############################################################################
## Variables
#############################################################################
PVRTEXTOOL 	= ..\..\..\Utilities\PVRTexTool\PVRTexToolCL\Windows_x86_32\PVRTexTool.exe
FILEWRAP 	= ..\..\..\Utilities\Filewrap\Windows_x86_32\Filewrap.exe
PVRUNISCO 	= ..\..\..\Utilities\PVRUniSCo\OGLES\Windows_x86_32\glslcompiler_sgx535.exe

MEDIAPATH = ../Media
CONTENTDIR = Content

#############################################################################
## Instructions
#############################################################################

TEXTURES = \
	container-corner.pvr \
	container-vertical.pvr \
	container-horizontal.pvr \
	topbar.pvr \
	background.pvr \
	clock-face.pvr \
	clock-face-small.pvr \
	hand.pvr \
	hand-small.pvr \
	battery.pvr \
	internet-web-browser.pvr \
	mail-message-new.pvr \
	network-wireless.pvr \
	office-calendar.pvr \
	weather-sun-cloud.pvr \
	weather-storm.pvr \
	weather-rain.pvr \
	text1.pvr \
	text2.pvr \
	text-weather.pvr \
	text-fri.pvr \
	text-sat.pvr \
	text-sun.pvr \
	text-mon.pvr \
	weather-sun-cloud-big.pvr \
	window-bottom.pvr \
	window-bottomcorner.pvr \
	window-side.pvr \
	window-top.pvr \
	window-topleft.pvr \
	window-topright.pvr \
	loremipsum.pvr

BIN_SHADERS = \
	SpriteShaderF.fsc \
	SpriteShaderV.vsc \
	TexColShaderF.fsc \
	TexColShaderV.vsc \
	ColShaderF.fsc \
	ColShaderV.vsc

RESOURCES = \
	$(CONTENTDIR)/SpriteShaderF.cpp \
	$(CONTENTDIR)/SpriteShaderV.cpp \
	$(CONTENTDIR)/TexColShaderF.cpp \
	$(CONTENTDIR)/TexColShaderV.cpp \
	$(CONTENTDIR)/ColShaderF.cpp \
	$(CONTENTDIR)/ColShaderV.cpp \
	$(CONTENTDIR)/container-corner.cpp \
	$(CONTENTDIR)/container-vertical.cpp \
	$(CONTENTDIR)/container-horizontal.cpp \
	$(CONTENTDIR)/topbar.cpp \
	$(CONTENTDIR)/background.cpp \
	$(CONTENTDIR)/clock-face.cpp \
	$(CONTENTDIR)/clock-face-small.cpp \
	$(CONTENTDIR)/hand.cpp \
	$(CONTENTDIR)/hand-small.cpp \
	$(CONTENTDIR)/battery.cpp \
	$(CONTENTDIR)/internet-web-browser.cpp \
	$(CONTENTDIR)/mail-message-new.cpp \
	$(CONTENTDIR)/network-wireless.cpp \
	$(CONTENTDIR)/office-calendar.cpp \
	$(CONTENTDIR)/weather-sun-cloud.cpp \
	$(CONTENTDIR)/weather-storm.cpp \
	$(CONTENTDIR)/weather-rain.cpp \
	$(CONTENTDIR)/text1.cpp \
	$(CONTENTDIR)/text2.cpp \
	$(CONTENTDIR)/text-weather.cpp \
	$(CONTENTDIR)/text-fri.cpp \
	$(CONTENTDIR)/text-sat.cpp \
	$(CONTENTDIR)/text-sun.cpp \
	$(CONTENTDIR)/text-mon.cpp \
	$(CONTENTDIR)/weather-sun-cloud-big.cpp \
	$(CONTENTDIR)/window-bottom.cpp \
	$(CONTENTDIR)/window-bottomcorner.cpp \
	$(CONTENTDIR)/window-side.cpp \
	$(CONTENTDIR)/window-top.cpp \
	$(CONTENTDIR)/window-topleft.cpp \
	$(CONTENTDIR)/window-topright.cpp \
	$(CONTENTDIR)/loremipsum.cpp

all: resources
	
help:
	@echo Valid targets are:
	@echo resources, textures, binary_shaders, clean
	@echo PVRTEXTOOL, FILEWRAP and PVRUNISCO can be used to override the default paths to these utilities.

clean:
	-rm $(RESOURCES)
	-rm $(BIN_SHADERS)
	-rm $(TEXTURES)

resources: 		$(CONTENTDIR) $(RESOURCES)
textures: 		$(TEXTURES)
binary_shaders:	$(BIN_SHADERS)

$(CONTENTDIR):
	-mkdir $@

container-corner.pvr: $(MEDIAPATH)/container-corner.png
	$(PVRTEXTOOL) -fOGL4444 -i$(MEDIAPATH)/container-corner.png -o$@

container-vertical.pvr: $(MEDIAPATH)/container-vertical.png
	$(PVRTEXTOOL) -fOGL4444 -i$(MEDIAPATH)/container-vertical.png -o$@

container-horizontal.pvr: $(MEDIAPATH)/container-horizontal.png
	$(PVRTEXTOOL) -fOGL4444 -i$(MEDIAPATH)/container-horizontal.png -o$@

topbar.pvr: $(MEDIAPATH)/topbar.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/topbar.png -o$@

background.pvr: $(MEDIAPATH)/background.png
	$(PVRTEXTOOL) -fOGLPVRTC4 -i$(MEDIAPATH)/background.png -o$@

clock-face.pvr: $(MEDIAPATH)/clock-face.png
	$(PVRTEXTOOL) -fOGL4444 -i$(MEDIAPATH)/clock-face.png -o$@

clock-face-small.pvr: $(MEDIAPATH)/clock-face-small.png
	$(PVRTEXTOOL) -fOGL4444 -i$(MEDIAPATH)/clock-face-small.png -o$@

hand.pvr: $(MEDIAPATH)/hand.png
	$(PVRTEXTOOL) -fOGL4444 -i$(MEDIAPATH)/hand.png -o$@

hand-small.pvr: $(MEDIAPATH)/hand-small.png
	$(PVRTEXTOOL) -fOGL4444 -i$(MEDIAPATH)/hand-small.png -o$@

battery.pvr: $(MEDIAPATH)/battery.png
	$(PVRTEXTOOL) -fOGL4444 -i$(MEDIAPATH)/battery.png -o$@

internet-web-browser.pvr: $(MEDIAPATH)/internet-web-browser.png
	$(PVRTEXTOOL) -fOGL4444 -i$(MEDIAPATH)/internet-web-browser.png -o$@

mail-message-new.pvr: $(MEDIAPATH)/mail-message-new.png
	$(PVRTEXTOOL) -fOGL4444 -i$(MEDIAPATH)/mail-message-new.png -o$@

network-wireless.pvr: $(MEDIAPATH)/network-wireless.png
	$(PVRTEXTOOL) -fOGL4444 -i$(MEDIAPATH)/network-wireless.png -o$@

office-calendar.pvr: $(MEDIAPATH)/office-calendar.png
	$(PVRTEXTOOL) -fOGL4444 -i$(MEDIAPATH)/office-calendar.png -o$@

weather-sun-cloud.pvr: $(MEDIAPATH)/weather-sun-cloud.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/weather-sun-cloud.png -o$@

weather-storm.pvr: $(MEDIAPATH)/weather-storm.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/weather-storm.png -o$@

weather-rain.pvr: $(MEDIAPATH)/weather-rain.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/weather-rain.png -o$@

text1.pvr: $(MEDIAPATH)/text1.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/text1.png -o$@

text2.pvr: $(MEDIAPATH)/text2.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/text2.png -o$@

text-weather.pvr: $(MEDIAPATH)/text-weather.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/text-weather.png -o$@

text-fri.pvr: $(MEDIAPATH)/text-fri.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/text-fri.png -o$@

text-sat.pvr: $(MEDIAPATH)/text-sat.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/text-sat.png -o$@

text-sun.pvr: $(MEDIAPATH)/text-sun.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/text-sun.png -o$@

text-mon.pvr: $(MEDIAPATH)/text-mon.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/text-mon.png -o$@

weather-sun-cloud-big.pvr: $(MEDIAPATH)/weather-sun-cloud-big.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/weather-sun-cloud-big.png -o$@

window-bottom.pvr: $(MEDIAPATH)/window-bottom.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/window-bottom.png -o$@

window-bottomcorner.pvr: $(MEDIAPATH)/window-bottomcorner.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/window-bottomcorner.png -o$@

window-side.pvr: $(MEDIAPATH)/window-side.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/window-side.png -o$@

window-top.pvr: $(MEDIAPATH)/window-top.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/window-top.png -o$@

window-topleft.pvr: $(MEDIAPATH)/window-topleft.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/window-topleft.png -o$@

window-topright.pvr: $(MEDIAPATH)/window-topright.png
	$(PVRTEXTOOL) -fOGL8888 -i$(MEDIAPATH)/window-topright.png -o$@

loremipsum.pvr: $(MEDIAPATH)/loremipsum.png
	$(PVRTEXTOOL) -fOGL4444 -i$(MEDIAPATH)/loremipsum.png -o$@

$(CONTENTDIR)/SpriteShaderF.cpp: SpriteShaderF.fsh SpriteShaderF.fsc
	$(FILEWRAP)  -s  -o $@ SpriteShaderF.fsh
	-$(FILEWRAP)  -oa $@ SpriteShaderF.fsc

$(CONTENTDIR)/SpriteShaderV.cpp: SpriteShaderV.vsh SpriteShaderV.vsc
	$(FILEWRAP)  -s  -o $@ SpriteShaderV.vsh
	-$(FILEWRAP)  -oa $@ SpriteShaderV.vsc

$(CONTENTDIR)/TexColShaderF.cpp: TexColShaderF.fsh TexColShaderF.fsc
	$(FILEWRAP)  -s  -o $@ TexColShaderF.fsh
	-$(FILEWRAP)  -oa $@ TexColShaderF.fsc

$(CONTENTDIR)/TexColShaderV.cpp: TexColShaderV.vsh TexColShaderV.vsc
	$(FILEWRAP)  -s  -o $@ TexColShaderV.vsh
	-$(FILEWRAP)  -oa $@ TexColShaderV.vsc

$(CONTENTDIR)/ColShaderF.cpp: ColShaderF.fsh ColShaderF.fsc
	$(FILEWRAP)  -s  -o $@ ColShaderF.fsh
	-$(FILEWRAP)  -oa $@ ColShaderF.fsc

$(CONTENTDIR)/ColShaderV.cpp: ColShaderV.vsh ColShaderV.vsc
	$(FILEWRAP)  -s  -o $@ ColShaderV.vsh
	-$(FILEWRAP)  -oa $@ ColShaderV.vsc

$(CONTENTDIR)/container-corner.cpp: container-corner.pvr
	$(FILEWRAP)  -o $@ container-corner.pvr

$(CONTENTDIR)/container-vertical.cpp: container-vertical.pvr
	$(FILEWRAP)  -o $@ container-vertical.pvr

$(CONTENTDIR)/container-horizontal.cpp: container-horizontal.pvr
	$(FILEWRAP)  -o $@ container-horizontal.pvr

$(CONTENTDIR)/topbar.cpp: topbar.pvr
	$(FILEWRAP)  -o $@ topbar.pvr

$(CONTENTDIR)/background.cpp: background.pvr
	$(FILEWRAP)  -o $@ background.pvr

$(CONTENTDIR)/clock-face.cpp: clock-face.pvr
	$(FILEWRAP)  -o $@ clock-face.pvr

$(CONTENTDIR)/clock-face-small.cpp: clock-face-small.pvr
	$(FILEWRAP)  -o $@ clock-face-small.pvr

$(CONTENTDIR)/hand.cpp: hand.pvr
	$(FILEWRAP)  -o $@ hand.pvr

$(CONTENTDIR)/hand-small.cpp: hand-small.pvr
	$(FILEWRAP)  -o $@ hand-small.pvr

$(CONTENTDIR)/battery.cpp: battery.pvr
	$(FILEWRAP)  -o $@ battery.pvr

$(CONTENTDIR)/internet-web-browser.cpp: internet-web-browser.pvr
	$(FILEWRAP)  -o $@ internet-web-browser.pvr

$(CONTENTDIR)/mail-message-new.cpp: mail-message-new.pvr
	$(FILEWRAP)  -o $@ mail-message-new.pvr

$(CONTENTDIR)/network-wireless.cpp: network-wireless.pvr
	$(FILEWRAP)  -o $@ network-wireless.pvr

$(CONTENTDIR)/office-calendar.cpp: office-calendar.pvr
	$(FILEWRAP)  -o $@ office-calendar.pvr

$(CONTENTDIR)/weather-sun-cloud.cpp: weather-sun-cloud.pvr
	$(FILEWRAP)  -o $@ weather-sun-cloud.pvr

$(CONTENTDIR)/weather-storm.cpp: weather-storm.pvr
	$(FILEWRAP)  -o $@ weather-storm.pvr

$(CONTENTDIR)/weather-rain.cpp: weather-rain.pvr
	$(FILEWRAP)  -o $@ weather-rain.pvr

$(CONTENTDIR)/text1.cpp: text1.pvr
	$(FILEWRAP)  -o $@ text1.pvr

$(CONTENTDIR)/text2.cpp: text2.pvr
	$(FILEWRAP)  -o $@ text2.pvr

$(CONTENTDIR)/text-weather.cpp: text-weather.pvr
	$(FILEWRAP)  -o $@ text-weather.pvr

$(CONTENTDIR)/text-fri.cpp: text-fri.pvr
	$(FILEWRAP)  -o $@ text-fri.pvr

$(CONTENTDIR)/text-sat.cpp: text-sat.pvr
	$(FILEWRAP)  -o $@ text-sat.pvr

$(CONTENTDIR)/text-sun.cpp: text-sun.pvr
	$(FILEWRAP)  -o $@ text-sun.pvr

$(CONTENTDIR)/text-mon.cpp: text-mon.pvr
	$(FILEWRAP)  -o $@ text-mon.pvr

$(CONTENTDIR)/weather-sun-cloud-big.cpp: weather-sun-cloud-big.pvr
	$(FILEWRAP)  -o $@ weather-sun-cloud-big.pvr

$(CONTENTDIR)/window-bottom.cpp: window-bottom.pvr
	$(FILEWRAP)  -o $@ window-bottom.pvr

$(CONTENTDIR)/window-bottomcorner.cpp: window-bottomcorner.pvr
	$(FILEWRAP)  -o $@ window-bottomcorner.pvr

$(CONTENTDIR)/window-side.cpp: window-side.pvr
	$(FILEWRAP)  -o $@ window-side.pvr

$(CONTENTDIR)/window-top.cpp: window-top.pvr
	$(FILEWRAP)  -o $@ window-top.pvr

$(CONTENTDIR)/window-topleft.cpp: window-topleft.pvr
	$(FILEWRAP)  -o $@ window-topleft.pvr

$(CONTENTDIR)/window-topright.cpp: window-topright.pvr
	$(FILEWRAP)  -o $@ window-topright.pvr

$(CONTENTDIR)/loremipsum.cpp: loremipsum.pvr
	$(FILEWRAP)  -o $@ loremipsum.pvr

SpriteShaderF.fsc: SpriteShaderF.fsh
	$(PVRUNISCO) SpriteShaderF.fsh $@  -f 

SpriteShaderV.vsc: SpriteShaderV.vsh
	$(PVRUNISCO) SpriteShaderV.vsh $@  -v 

TexColShaderF.fsc: TexColShaderF.fsh
	$(PVRUNISCO) TexColShaderF.fsh $@  -f 

TexColShaderV.vsc: TexColShaderV.vsh
	$(PVRUNISCO) TexColShaderV.vsh $@  -v 

ColShaderF.fsc: ColShaderF.fsh
	$(PVRUNISCO) ColShaderF.fsh $@  -f 

ColShaderV.vsc: ColShaderV.vsh
	$(PVRUNISCO) ColShaderV.vsh $@  -v 

############################################################################
# End of file (content.mak)
############################################################################
