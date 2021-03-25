#####################################################
# Build for STM32 boards
#####################################################

include $(BOARD_MK)

ifdef BOARD

all: green_house

COMMON_DIR = $(shell sed "s/\(hw_modules\).*/\1/" <<< $PWD)/common

GREEN_HOUSE_DIR = $(shell sed "s/\(green_house\).*/\1/" <<< $PWD)
STM32GenDir = $(GREEN_HOUSE_DIR)/boards/$(BOARD)
STM32Makefile = $(STM32GenDir)/Makefile

include $(STM32Makefile)

TARGET = GreenHouse

BUILD_DIR = $(GREEN_HOUSE_DIR)/build

CXX=$(PREFIX)g++

#################################################################################
# Change path to the STM32 generated files
#################################################################################
STM32_C_INCLUDES = $(C_INCLUDES:-I%=%)
STM32_AS_INCLUDES = $(AS_INCLUDES:-I%:=%)

C_SOURCES := $(addprefix $(STM32GenDir), $(C_SOURCES)) $(SOURCES)
ASM_SOURCES := $(addprefix $(STM32GenDir), $(ASM_SOURCES))

C_INCLUDES := $(addprefix -I$(STM32GenDir), $(STM32_C_INCLUDES))
AS_INCLUDES := $(addprefix -I$(STM32GenDir), $(STM32_AS_INCLUDES))

LDSCRIPT := $(addprefix $(STM32GenDir), $(LDSCRIPT))

######################################
# Update source
######################################
# C sources
C_SOURCES +=  \
$(COMMON_DIR)/logger/src/logger.c

C_INCLUDES += \
$(COMMON_DIR)/inc \
$(COMMON_DIR)/logger/inc

# CXX sources
CXX_SOURCES = \
$(GREEN_HOUSE_DIR)/app/src/green_house.cpp

CXX_INCLUDES = \
$(GREEN_HOUSE_DIR)/app/inc

#######################################
# FLAGS
#######################################

# CXX flags
CXX_FLAGS = $(CFLAGS) $(CXX_INCLUDES)
CXXFLAGS+=-fno-rtti -fno-exceptions
CXXFLAGS+=-std=c++17

#######################################
# build the application
#######################################

# build green_house
green_house: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

# list of C objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of CXX objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CXX_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CXX_SOURCES)))

# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c $(STM32Makefile) | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cpp $(STM32Makefile) | $(BUILD_DIR) 
	$(CXX) -c $(CXX_FLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s $(STM32Makefile) | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) $(STM32Makefile)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
endif
