#####################################################
# Set config
#####################################################

.PHONY : clean all GreenHouse

CONFIG =

all:
	@echo ALL
	@python .setup_config.py
	${MAKE} CONFIG=BuildConfig.mk

clean:
	rm -rf build

include $(CONFIG)

ifdef BOARD

######################################
# source
######################################

CURR_DIR = $(shell pwd)
HW_MODULES_DIR = ../../
COMMON_DIR = $(HW_MODULES_DIR)common/
COMMON_LOGGER_DIR = $(COMMON_DIR)logger/
BoardGenDir = $(CURR_DIR)/boards/$(BOARD)/
BoardMakefile = $(BoardGenDir)/Makefile

include $(BoardMakefile)

BUILD_DIR = $(CURR_DIR)/build

LIB_DIR = $(CURR_DIR)/lib/
APP_DIR = $(CURR_DIR)/app/

# Find all sources
SOURCES := $(shell find $(COMMON_DIR)src -name '*.c')
SOURCES += $(shell find $(LIB_DIR)src -name '*.c')
SOURCES += $(shell find $(APP_DIR)src -name '*.c')

Board_INCLUDES = $(C_INCLUDES:-I%=%)

C_SOURCES := $(addprefix $(BoardGenDir), $(C_SOURCES)) $(SOURCES)
ASM_SOURCES := $(addprefix $(BoardGenDir), $(ASM_SOURCES))
C_INCLUDES := $(addprefix -I$(BoardGenDir), $(Board_INCLUDES))\
	-I$(COMMON_DIR)inc\
	-I$(COMMON_LOGGER_DIR)inc\
	-I$(LIB_DIR)inc\
	-I$(APP_DIR)inc

LDSCRIPT := $(addprefix $(BoardGenDir), $(LDSCRIPT))
GreenHouse: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
	@echo GREEN_HOUSE

#######################################
# build the application
#######################################

# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
	
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@

#######################################
# flash
#######################################
flash: $(BUILD_DIR)/$(TARGET).elf
	openocd -f interface/stlink-v2-1.cfg  -f target/stm32f1x.cfg -c "program $(BUILD_DIR)/$(TARGET).elf"
endif
