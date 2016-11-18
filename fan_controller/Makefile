#######################################################
#
#    Raspberry Utils
#    ===========================================
#    Elessog
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

CORE_CPP=
#CORE_C= mailbox.c

SRC_MAIN = main.cpp

SRC_CPP = $(CORE_CPP)
SRC_C = $(CORE_C)


#SOURCES = $(addprefix src/, $(SRC))

# Includes

INC = -I./

# Object files
OBJECTS_1 = $(addprefix $(BUILD_DIR)/, $(SRC_CPP:.cpp=.o))
OBJECTS = $(OBJECTS_1) $(addprefix $(BUILD_DIR)/, $(SRC_C:.c=.o))
OBJECT_MAIN = $(addprefix $(BUILD_DIR)/, $(SRC_MAIN:.cpp=.o))

# Target Output
EXECUTABLE = fan_controller.run
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
$(BUILD_DIR)/%.o:$(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo Compiling C File: $@
	@$(CC) -c $(CFLAGS) $(INC) -o ./$@ $< -DTOOLCHAIN=$(C_TOOLCHAIN) $(LiBS)

#####################################################################
# Tool Rules

install: all
	@echo Installing service file
	@systemctl stop fan_controller.service || true
	@cp $(OUTPUT_DIR)/fan_controller.service /etc/systemd/system/
	@systemctl daemon-reload
	@systemctl enable fan_controller.service
	@systemctl start fan_controller.service
	@echo DONE

stats:$(EXECUTABLE)
	@echo Final executable size:
	$(SIZE) $(EXECUTABLE)

clean:
	@echo Removing existing object files and executable
	@rm -f -r $(BUILD_DIR)
	@rm -f $(EXECUTABLE)
	@echo DONE

debug:
	@echo -n $(OBJECTS) " cpp : " $(OBJECTS_1)
	@echo DONE
