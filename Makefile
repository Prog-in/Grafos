CXX := g++
CXXFLAGS := -Wall -Wextra
LDFLAGS := -lstdc++ -lm

BUILD := ./build
OBJ_DIR := $(BUILD)/objects
APP_DIR := $(BUILD)/apps

ACTIVITIES := $(wildcard A*)
ALL_SOURCES := $(wildcard A*/src/*.cpp)

LIB_SOURCES := A1/src/A1_1.cpp A2/src/A2_Graph.cpp A2/src/A1_1.cpp A3/src/A2_Graph.cpp A3/src/A1_Graph.cpp
APP_SOURCES := $(filter-out $(LIB_SOURCES), $(ALL_SOURCES))

ALL_OBJECTS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(ALL_SOURCES))

APPS := $(foreach src, $(APP_SOURCES), $(APP_DIR)/$(basename $(notdir $(src))))

INCLUDE := $(addprefix -I, $(wildcard A*/include/))

all: build $(APPS)

# Standard rule for object files
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

# HELPER: Get activity name from path (e.g., A1/src/main.cpp -> A1)
get_activity = $(firstword $(subst /, ,$(1)))

# DYNAMIC LINKING RULE
define MAKE_APP_RULE
# We calculate the library object inline so it bakes the correct path directly into the rule
$(APP_DIR)/$(basename $(notdir $(1))): $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(1)) $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(filter $(call get_activity,$(1))/src/%, $(LIB_SOURCES)))
	@mkdir -p $$(@D)
	$(CXX) $(CXXFLAGS) -o $$@ $$^ $(LDFLAGS)
endef

# Generate rules for every app source
$(foreach src, $(APP_SOURCES), $(eval $(call MAKE_APP_RULE,$(src))))

# Target to build a specific activity (e.g., 'make A1' or 'make A2')
$(ACTIVITIES):
	@$(MAKE) $(filter $(APP_DIR)/$@_%, $(APPS))

.PHONY: all build clean info $(ACTIVITIES)

build:
	@mkdir -p $(APP_DIR) $(OBJ_DIR)

clean:
	-@rm -r $(BUILD)

info:
	@echo "--- Isolated Activities ---"
	@echo "Detected Activities: $(ACTIVITIES)"
	@echo "Library Sources:     $(LIB_SOURCES)"
	@echo "App Sources:         $(APP_SOURCES)"
	@echo "--- Final Binaries ---"
	@echo "APPS:                $(APPS)"
	@echo "--------------------------"

-include $(ALL_OBJECTS:.o=.d)
