MODULE := engines/unity

MODULE_OBJS := \
	debug.o \
	detection.o \
	graphics.o \
	object.o \
	sound.o \
	sprite.o \
	sprite_player.o \
	unity.o

# This module can be built as a plugin
ifeq ($(ENABLE_UNITY), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
