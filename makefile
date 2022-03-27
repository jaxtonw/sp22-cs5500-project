SHELL := /bin/bash

SRC_DIRS ?= src
TEST_BUILD_DIR ?= testbuild
TEST_SRC_DIRS ?= test
TEST_RESULT_DIR ?= testresult

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
TESTS := $(shell find $(TEST_SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
TEST_OBJS := $(TESTS:%=$(TEST_BUILD_DIR)/%.o)
TEST_RESULTS := $(TEST_OBJS:%=$(TEST_RESULT_DIR)/%.result)
TEST_DEPS := $(TEST_OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)

CXX := mpicxx

# build test files
$(TEST_BUILD_DIR)/%.cpp.o: %.cpp
	@$(MKDIR_P) $(dir $@)
	$(CXX) -DMAKE_TEST $(SRCS) $< -o $@


$(TEST_RESULT_DIR)/%.cpp.o.result: %.cpp.o
#	@echo "TEST_RESULTS: ${TEST_RESULTS}"
	@$(MKDIR_P) $(dir $(@:$(TEST_RESULT_DIR)/$(TEST_BUILD_DIR)/%=$(TEST_RESULT_DIR)/%))
#	@echo "$<"
#	@echo "$@"
	mpirun -np 4 $< > $(@:$(TEST_RESULT_DIR)/$(TEST_BUILD_DIR)/%=$(TEST_RESULT_DIR)/%)
	diff -q $(@:$(TEST_RESULT_DIR)/$(TEST_BUILD_DIR)/%=$(TEST_RESULT_DIR)/%) $(@:$(TEST_RESULT_DIR)/$(TEST_BUILD_DIR)/%=%)

.PHONY: clean build test

buildtest: $(TEST_OBJS)

runtest: build $(TEST_RESULTS)

clean:
	$(RM) -r $(TEST_BUILD_DIR)
	$(RM) -r $(TEST_RESULT_DIR)

-include $(TEST_DEPS)

MKDIR_P ?= mkdir -p