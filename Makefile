CXX := g++
CXXFLAGS := -Wall -Wextra
LDFLAGS := -lstdc++ -lm

BUILD := ./build
OBJ_DIR := $(BUILD)/objects
APP_DIR := $(BUILD)/apps

ACTIVITIES := $(wildcard A*)
ALL_SOURCES := $(wildcard A*/src/*.cpp)

LIB_SOURCES := A1/src/A1_1.cpp
APP_SOURCES := $(filter-out $(LIB_SOURCES), $(ALL_SOURCES))

LIB_OBJECTS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(LIB_SOURCES))
APP_OBJECTS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(APP_SOURCES))

APPS := $(foreach src, $(APP_SOURCES), $(APP_DIR)/$(basename $(notdir $(src))))

INCLUDE := $(addprefix -I, $(wildcard A*/include/))

all: build $(APPS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

define MAKE_APP_RULE
# Target: apps/A1_2  | Prerequisites: objects/A1/src/A1_2.o + objects/A1/src/A1_1.o
$(APP_DIR)/$(basename $(notdir $(1))): $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(1)) $(LIB_OBJECTS)
	@mkdir -p $$(@D)
	$$(CXX) $$(CXXFLAGS) -o $$@ $$^ $$(LDFLAGS)
endef

$(foreach src, $(APP_SOURCES), $(eval $(call MAKE_APP_RULE,$(src))))

$(ACTIVITIES):
	@$(MAKE) $(filter $(APP_DIR)/$@_%, $(APPS))

.PHONY: all build clean info $(ACTIVITIES)

build:
	@mkdir -p $(APP_DIR) $(OBJ_DIR)

clean:
	-@rm -r $(BUILD)

info:
	@echo "--- Makefile Variables ---"
	@echo "ACTIVITIES:  $(ACTIVITIES)"
	@echo "ALL_SOURCES: $(ALL_SOURCES)"
	@echo "LIB_SOURCES: $(LIB_SOURCES)"
	@echo "APP_SOURCES: $(APP_SOURCES)"
	@echo "--- Object Mappings ---"
	@echo "LIB_OBJECTS: $(LIB_OBJECTS)"
	@echo "APP_OBJECTS: $(APP_OBJECTS)"
	@echo "--- Final Targets ---"
	@echo "APPS:        $(APPS)"
	@echo "INCLUDE:     $(INCLUDE)"
	@echo "--------------------------"

-include $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d)