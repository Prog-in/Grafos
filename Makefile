CXX := g++
CXXFLAGS := -Wall -Wextra
LDFLAGS := -lstdc++ -lm

BUILD := ./build
OBJ_DIR := $(BUILD)/objects
APP_DIR := $(BUILD)/apps

ACTIVITIES := $(wildcard A*)

ALL_SOURCES := $(wildcard A*/src/*.cpp)

LIB_SOURCES := #A1/src/A1_1.cpp
LIB_OBJECTS := $(LIB_SOURCES:%.cpp=$(OBJ_DIR)/%.o)

APP_SOURCES := $(filter-out $(LIB_SOURCES), $(ALL_SOURCES))
APP_OBJECTS := $(APP_SOURCES:%.cpp=$(OBJ_DIR)/%.o)

APPS := $(foreach src, $(APP_SOURCES), $(APP_DIR)/$(basename $(notdir $(src))))

INCLUDE := $(addprefix -I, $(wildcard A*/include/))

all: build $(APPS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(APP_DIR)/%: $(OBJ_DIR)/*/src/%.o $(LIB_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(ACTIVITIES):
	@$(MAKE) $(filter $(APP_DIR)/$@_%, $(APPS))

-include $($(OBJ_DIR)/%.d)

.PHONY: all build clean $(ACTIVITIES)

build:
	@mkdir -p $(APP_DIR) $(OBJ_DIR)

clean:
	-@rm -r $(BUILD)