#####################################################
# Set config
#####################################################

BUILD_CONFIG=BuildConfig.mk

include $(BUILD_CONFIG)

ifdef BOARD

GREEN_HOUSE_DIR = $(shell pwd | sed "s/\(green_house\).*/\1/")

BOARDS_DIR = $(GREEN_HOUSE_DIR)/boards

MAKE_TARGETS_DIR = $(GREEN_HOUSE_DIR)/make_targets
TARGET_Makefile = $(MAKE_TARGETS_DIR)/$(MK_TARGET)Target.mk

all: green_house
.PHONY : green_house

include $(TARGET_Makefile)

endif
