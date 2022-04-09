SHELL:= /bin/bash

COMPILER_DEFINES  			:= -DMAKE_TEST

SRC_DIR  					:= src
ARITHMETIC_DIR 				:= src/arithmetic
COMMON_DIR 					:= src/common
LU_DIR 						:= src/lu
MATRIX_DIR 					:= src/matrix
NORMS_DIR 					:= src/norms
VECTOR_DIR 					:= src/vector

TEST_DIR 					:= test
TEST_ARITHMETIC_DIR 		:= test/arithmetic
TEST_COMMON_DIR 			:= test/common
TEST_LU_DIR 				:= test/lu
TEST_MATRIX_DIR 			:= test/matrix
TEST_NORMS_DIR 				:= test/norms
TEST_VECTOR_DIR 			:= test/vector

TESTBUILD_DIR 				:= testbuild
TESTBUILD_ARITHMETIC_DIR 	:= testbuild/arithmetic
TESTBUILD_COMMON_DIR 		:= testbuild/common
TESTBUILD_LU_DIR 			:= testbuild/lu
TESTBUILD_MATRIX_DIR 		:= testbuild/matrix
TESTBUILD_NORMS_DIR 		:= testbuild/norms
TESTBUILD_VECTOR_DIR 		:= testbuild/vector

TESTRESULT_DIR 				:= testresult
TESTRESULT_ARITHMETIC_DIR 	:= testresult/arithmetic
TESTRESULT_COMMON_DIR 		:= testresult/common
TESTRESULT_LU_DIR 			:= testresult/lu
TESTRESULT_MATRIX_DIR 		:= testresult/matrix
TESTRESULT_NORMS_DIR 		:= testresult/norms
TESTRESULT_VECTOR_DIR 		:= testresult/vector

ARITHMETIC_SRC := $(shell find $(ARITHMETIC_DIR) -name *.cpp)
COMMON_SRC := $(shell find $(COMMON_DIR) -name *.cpp)
LU_SRC := $(shell find $(LU_DIR) -name *.cpp)
MATRIX_SRC := $(shell find $(MATRIX_DIR) -name *.cpp)
NORMS_SRC := $(shell find $(NORMS_DIR) -name *.cpp)
VECTOR_SRC := $(shell find $(VECTOR_DIR) -name *.cpp)

ARITHMETIC_TESTS := $(shell find $(TEST_ARITHMETIC_DIR) -name *.cpp)
# LU_TESTS := $(shell find $(TEST_LU_DIR) -name *.cpp)
MATRIX_TESTS := $(shell find $(TEST_MATRIX_DIR) -name *.cpp)
NORMS_TESTS := $(shell find $(TEST_NORMS_DIR) -name *.cpp)
VECTOR_TESTS := $(shell find $(TEST_VECTOR_DIR) -name *.cpp)

ARITHMETIC_TEST_OBJS := $(ARITHMETIC_TESTS:%=$(TESTBUILD_ARITHMETIC_DIR)/%.o)
# LU_TEST_OBJS := $(LU_TESTS:%=$(TESTBUILD_LU_DIR)/%.o)
MATRIX_TEST_OBJS := $(MATRIX_TESTS:%=$(TESTBUILD_MATRIX_DIR)/%.o)
NORMS_TEST_OBJS := $(NORMS_TESTS:%=$(TESTBUILD_NORMS_DIR)/%.o)
VECTOR_TEST_OBJS := $(VECTOR_TESTS:%=$(TESTBUILD_VECTOR_DIR)/%.o)

ARITHMETIC_RESULTS := $(ARITHMETIC_TEST_OBJS:%=$(TESTRESULT_ARITHMETIC_DIR)/%.result)
# LU_RESULTS := $(LU_TEST_OBJS:%=$(TESTRESULT_LU_DIR)/%.result)
MATRIX_RESULTS := $(MATRIX_TEST_OBJS:%=$(TESTRESULT_MATRIX_DIR)/%.result)
NORMS_RESULTS := $(NORMS_TEST_OBJS:%=$(TESTRESULT_NORMS_DIR)/%.result)
VECTOR_RESULTS := $(VECTOR_TEST_OBJS:%=$(TESTRESULT_VECTOR_DIR)/%.result)

# Our compiler is mpicxx
CXX := mpicxx

# # Build test files
# $(TEST_BUILD_DIR)/%.cpp.o: %.cpp
# 	@mkdir -p $(dir $@)
# 	$(CXX) -DMAKE_TEST $(SRCS) $< -o $@

# # Create test results
# $(TEST_RESULT_DIR)/%.cpp.o.result: %.cpp.o
# #	@echo "TEST_RESULTS: ${TEST_RESULTS}"
# 	@mkdir -p $(dir $(@:$(TEST_RESULT_DIR)/$(TEST_BUILD_DIR)/%=$(TEST_RESULT_DIR)/%))
# #	@echo "$<"
# #	@echo "$@"
# 	mpirun -np 4 $< > $(@:$(TEST_RESULT_DIR)/$(TEST_BUILD_DIR)/%=$(TEST_RESULT_DIR)/%)
# 	diff -q $(@:$(TEST_RESULT_DIR)/$(TEST_BUILD_DIR)/%=$(TEST_RESULT_DIR)/%) $(@:$(TEST_RESULT_DIR)/$(TEST_BUILD_DIR)/%=%)

.PHONY: clean build-tests run-test

$(TESTBUILD_ARITHMETIC_DIR)/%.cpp.o: $(ARITHMETIC_TESTS)
	@mkdir -p $(TESTBUILD_ARITHMETIC_DIR)
	$(CXX) $(COMPILER_DEFINES) $(COMMON_SRC) $(ARITHMETIC_SRC) $< -o $(TESTBUILD_ARITHMETIC_DIR)/$(@F)

$(TESTBUILD_MATRIX_DIR)/%.cpp.o: $(MATRIX_TESTS)
	@mkdir -p $(TESTBUILD_MATRIX_DIR)
	$(CXX) $(COMPILER_DEFINES) $(COMMON_SRC) $(MATRIX_SRC) $< -o $(TESTBUILD_MATRIX_DIR)/$(@F)

$(TESTBUILD_NORMS_DIR)/%.cpp.o: $(NORMS_TESTS)
	@mkdir -p $(TESTBUILD_NORMS_DIR)
	$(CXX) $(COMPILER_DEFINES) $(COMMON_SRC) $(NORMS_SRC) $< -o $(TESTBUILD_NORMS_DIR)/$(@F)

$(TESTBUILD_VECTOR_DIR)/%.cpp.o: $(VECTOR_TESTS)
	@mkdir -p $(TESTBUILD_VECTOR_DIR)
	$(CXX) $(COMPILER_DEFINES) $(COMMON_SRC) $(VECTOR_SRC) $< -o $(TESTBUILD_VECTOR_DIR)/$(@F)

$(TESTRESULT_ARITHMETIC_DIR)/%.cpp.o.result: $(ARITHMETIC_TEST_OBJS)
	@mkdir -p $(TESTRESULT_ARITHMETIC_DIR)
	mpirun -np 4 $< > $(TESTRESULT_ARITHMETIC_DIR)/$(@F)

build-tests: $(ARITHMETIC_TEST_OBJS) $(MATRIX_TEST_OBJS) $(NORMS_TEST_OBJS) $(VECTOR_TEST_OBJS)

run-test: $(ARITHMETIC_RESULTS)

clean:
	$(RM) -r $(TESTBUILD_DIR)
	$(RM) -r $(TESTRESULT_DIR)
