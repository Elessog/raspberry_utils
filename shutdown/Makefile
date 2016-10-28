#######################################################
#
#    Aland Sailing Robot
#    ===========================================
#    sailingrobot
#    -------------------------------------------
#
#######################################################


#######################################################
# TOOLCHAINS
#######################################################


# Options include:
#		linux_local = For a local linux machine (MOCK objects used)
#		raspi_cc = For cross compiling to the PI on a linux machine
#		raspi_local = For compiling on the PI itself
export TOOLCHAIN = linux-local
C_TOOLCHAIN = 0


#######################################################
# FILES
#######################################################

# Directories
export BUILD_DIR = build
SRC_DIR = ./
OUTPUT_DIR = ./


# Sources

CORE= Timer.cpp

SRC_MAIN = button_Int.cpp

SRC = $(CORE)


#SOURCES = $(addprefix src/, $(SRC))

# Includes

INC = -I./

# Object files
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SRC:.cpp=.o))
OBJECT_MAIN = $(addprefix $(BUILD_DIR)/, $(SRC_MAIN:.cpp=.o))

# Target Output
EXECUTABLE = shutdown_on_button.run
export OBJECT_FILE = $(BUILD_DIR)/objects.tmp


#######################################################
# TOOLS
#######################################################


export CFLAGS = -Wall -g -o2
export CPPFLAGS = -g -Wall -pedantic -Werror -std=c++14

export LIBS = -lwiringPi -lpthread

C_TOOLCHAIN = 1
CC = gcc
CXX = g++
SIZE = size

export MKDIR_P = mkdir -p

#######################################################
# Rules
#######################################################

.PHONY: clean

all: $(EXECUTABLE) stats


# Builds the intergration test, requires the whole system to be built before

#  Create the directories needed
$(BUILD_DIR):
	@$(MKDIR_P) $(BUILD_DIR)

# Link and build
$(EXECUTABLE) : $(BUILD_DIR) $(OBJECTS) $(OBJECT_MAIN)
	rm -f $(OBJECT_FILE)
	@echo Linking object files
	@echo -n " " $(OBJECTS) >> $(OBJECT_FILE)
	$(CXX) $(LDFLAGS) @$(OBJECT_FILE) $(OBJECT_MAIN) -Wl,-rpath=./ -o $@ $(LIBS)
	@echo Built using toolchain: $(TOOLCHAIN)

# Compile CPP files into the build folder
$(BUILD_DIR)/%.o:$(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo Compiling CPP File: $@
	@$(CXX) -c $(CPPFLAGS) $(INC) -o ./$@ $< -DTOOLCHAIN=$(TOOLCHAIN) $(LiBS)

 # Compile C files into the build folder
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo Compiling C File: $@
	@$(C) -c $(CFLAGS) $(INC) -o $@ $ -DTOOLCHAIN=$(C_TOOLCHAIN)

#####################################################################
# Tool Rules

stats:$(EXECUTABLE)
	@echo Final executable size:
	$(SIZE) $(EXECUTABLE)

clean:
	@echo Removing existing object files and executable
	@rm -f -r $(BUILD_DIR)
	@rm -f $(EXECUTABLE)
	@echo DONE
