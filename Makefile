#####################################################
# Set config
#####################################################

.PHONY : clean all GreenHouse

BOARD_MK=

all:
	@echo ALL
	@python .setup_config.py
	${MAKE} BOARD_MK=BuildConfig.mk

clean:
	rm -rf build

include $(BOARD_MK)

ifdef BOARD
PREFIX = arm-none-eabi-
CXX=$(PREFIX)g++

endif
