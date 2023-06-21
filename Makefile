# GNU ARM Embedded Toolchain
CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy
OD=arm-none-eabi-objdump
CXX=arm-none-eabi-g++

# Build Parameters: MCU Flags, Definitions, Includes, 
#                   Compile Flags, Linker Script, Linker Flags
MCFLAGS=-mcpu=cortex-m4 -mthumb -mlittle-endian \
-mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb-interwork
DEFS=-DUSE_STDPERIPH_DRIVER -DSTM32F4XX

STM32_BASE=../STM32F4-Discovery_FW_V1.1.0

INCLUDES=-I. \
-I../instant-rodos-demo \
-I$(STM32_BASE)/Libraries/CMSIS/ST/STM32F4xx/Include \
-I$(STM32_BASE)/Utilities/STM32F4-Discovery \
-I$(STM32_BASE)/Libraries/CMSIS/Include \
-I$(STM32_BASE)/Libraries/STM32F4xx_StdPeriph_Driver/inc
CFLAGS=-c -g $(MCFLAGS) $(DEFS) $(INCLUDES)
CXXFLAGS=-c -g $(MCFLAGS) $(DEFS) $(INCLUDES)
LDSCRIPT = stm32_flash.ld
LDFLAGS=-T $(LDSCRIPT) --specs=nosys.specs $(MCFLAGS)

# Inputs: C Sources, Assembler Sources
SOURCES=stm32f4xx_it.c system_stm32f4xx.c \
$(STM32_BASE)/Utilities/STM32F4-Discovery/stm32f4_discovery.c \
$(STM32_BASE)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c \
$(STM32_BASE)/Libraries/STM32F4xx_StdPeriph_Driver/src/misc.c \
$(STM32_BASE)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c \
$(STM32_BASE)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c \
$(STM32_BASE)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c \
$(STM32_BASE)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c \
stm32f4xx_tim.c
ASMSOURCES=$(STM32_BASE)/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f4xx.s
CPPSOURCES=main.cpp ThreadWithTimer.cpp

# Outputs: Object Files, ELF Executable & 
#          Converted ELF Executable to Intel HEX format
OBJECTS=$(SOURCES:%.c=%.o)
OBJECTS+=$(ASMSOURCES:%.s=%.o)
OBJECTS+=$(CPPSOURCES:%.cpp=%.o)
EXECUTABLE=iotoggle.elf
TARGET=iotoggle.hex
LIBRARY_PATH="/home/mike/instant-rodos/"
LIBRARY_NAME="instant-rodos.a"
# Build Rules
.PHONY: release
release: $(TARGET)

.PHONY: all
all: $(TARGET)

.PHONY: debug
debug: CFLAGS+=-g # Add debug flag
debug: LDFLAGS+=-g
debug: $(TARGET) 

$(TARGET): $(EXECUTABLE)
	$(CP) -O ihex $< $@
	@echo "Objcopy from ELF to IHEX complete!\n"

$(EXECUTABLE): $(OBJECTS)
	#$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	$(CC) $(LDFLAGS) $(OBJECTS)  instant-rodos.a -lstdc++ -o $@
	@echo "Linking complete!\n"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo "Compiled "$<"!\n"
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	@echo "Compiled "$<"!\n"


%.o: %.s
	$(CC) $(CFLAGS) $< -o $@
	@echo "Assambled "$<"!\n"

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(TARGET)
