CPP_C=g++
CPP_FLAGS=-std=c++23 -Wall -g -MMD -MP
BIN_DIR=bin
OBJ_DIR=obj/lib
SRC_DIR=src
LIB=$(BIN_DIR)/cpp_commons_lib

# Source files
SRC=$(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJ=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

.PHONY: clean lib

ifeq ($(DEBUG),1)
CPP_FLAGS += -DDEBUG
endif

lib: $(LIB).a

## LIB

$(LIB).a: $(OBJ)
	@mkdir -p $(BIN_DIR)
	ar -r $@ $^

# Rule for compiling all object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CPP_C) $(CPP_FLAGS) -c $< -o $@

# Clean all generated files
clean:
	@find obj -mindepth 1 ! -name .gitkeep -delete
	@find bin -mindepth 1 ! -name .gitkeep -delete
