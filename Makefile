#####################################################
# Set config
#####################################################

.PHONY : clean all green_house

BUILD_CONFIG=

all:
	@echo ALL
	@python .setup_config.py
	${MAKE} BUILD_CONFIG=BuildConfig.mk
clean:
	rm -rf build

include $(BUILD_CONFIG)

ifdef BOARD

GREEN_HOUSE_DIR = $(shell pwd | sed "s/\(green_house\).*/\1/")

BOARDS_DIR = $(GREEN_HOUSE_DIR)/boards

MAKE_TARGETS_DIR = $(GREEN_HOUSE_DIR)/make_targets
TARGET_Makefile = $(MAKE_TARGETS_DIR)/$(MK_TARGET)Target.mk

all: green_house

include $(TARGET_Makefile)

endif
