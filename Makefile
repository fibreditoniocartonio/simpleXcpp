TARGET_EXEC := simpleXcpp

BUILD_DIR := ./temp
SRC_DIRS := ./src
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
SRCS := ./main.cpp $(SRCS)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
INC_DIRS := ./inc
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS := $(INC_FLAGS) -MMD -MP
SFMLFLAGS := -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS := $(LDFLAGS SFMLFLAGS)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET_EXEC) $(LDFLAGS) $(SFMLFLAGS)

$(BUILD_DIR)/make.cpp.o: make.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c main.cpp -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
	rm -r $(TARGET_EXEC)

-include $(DEPS)
