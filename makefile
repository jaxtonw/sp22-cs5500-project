SHELL := /bin/bash

SRC_DIRS ?= ./src
TEST_BUILD_DIR ?= ./testbuild
TEST_SRC_DIRS ?= ./test
TEST_RESULT_DIRS ?= ./testresult

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
TESTS := $(shell find $(TEST_SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
TEST_OBJS := $(TESTS:%=$(TEST_BUILD_DIR)/%.o)
TEST_DEPS := $(TEST_OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)

CXX := mpicxx

# build test files
$(TEST_BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(SRCS) $< -o $@

.PHONY: clean test

# create one library
clean:
	$(RM) -r $(TEST_BUILD_DIR)
	$(RM) -r $(TEST_RESULT_DIRS)

testresults: $(TEST_OBJS)
	@echo "$(TEST_OBJS)"
	$(MKDIR_P) $(TEST_RESULT_DIRS)
	mpirun -np 4 $< > ./testresult/$(notdir $<).result

-include $(TEST_DEPS)

MKDIR_P ?= mkdir -p