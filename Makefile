###
# @author VaL Doroshchuk
# @license GNU GPL v2
###

# Points to the root of Google Test, relative to where this file is.
GTEST_DIR = lib/gtest
LIB_DIR = lib
BUILD_DIR = build

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include -I$(GTEST_DIR)

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -std=c++0x -I.

# All tests produced by this Makefile. Remember to add new tests you
# created to the list.
TARGETS = $(BUILD_DIR)/NodeTest $(BUILD_DIR)/GraphTest $(BUILD_DIR)/ChmTest 
# HEngine_s_test HEngine_sn_test HEngine_sn_dict_test query duplicates matches

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping $(BUILD_DIR) targets.

all : $(TARGETS)

clean :
	rm -f $(BUILD_DIR)/*

# builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
$(BUILD_DIR)/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc -o $@

$(BUILD_DIR)/gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc -o $@

$(BUILD_DIR)/gtest.a : $(BUILD_DIR)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^ -o $@

$(BUILD_DIR)/gtest_main.a : $(BUILD_DIR)/gtest-all.o $(BUILD_DIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^ -o $@

# builds a sample test. A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

$(BUILD_DIR)/node.o : common/graph/Node.cpp common/graph/Node.hpp
	$(CXX) $(CXXFLAGS) -c common/graph/Node.cpp -o $@

$(BUILD_DIR)/graph.o : common/graph/Graph.cpp common/graph/Graph.hpp
	$(CXX) $(CXXFLAGS) -c common/graph/Graph.cpp -o $@

$(BUILD_DIR)/jenkins.o : common/hashes/jenkins.cpp common/hashes/jenkins.hpp 
	$(CXX) $(CXXFLAGS) -c common/hashes/jenkins.cpp -o $@

$(BUILD_DIR)/Chm.o : kernel/chm/Chm.cpp kernel/chm/Chm.hpp
	$(CXX) $(CXXFLAGS) -c kernel/chm/Chm.cpp -o $@

$(BUILD_DIR)/ChmTest.o : kernel/chm/tests/ChmTest.cpp \
                     kernel/chm/Chm.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c kernel/chm/tests/ChmTest.cpp -o $@

$(BUILD_DIR)/ChmTest : $(BUILD_DIR)/node.o $(BUILD_DIR)/graph.o $(BUILD_DIR)/jenkins.o $(BUILD_DIR)/Chm.o $(BUILD_DIR)/ChmTest.o \
					$(BUILD_DIR)/gtest_main.a 
	$(CXX) -lpthread $(CPPFLAGS) $(CXXFLAGS) -pthread $^ -o $@

$(BUILD_DIR)/GraphTest.o : common/graph/tests/GraphTest.cpp \
                     common/graph/Graph.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c common/graph/tests/GraphTest.cpp -o $@

$(BUILD_DIR)/GraphTest : $(BUILD_DIR)/node.o $(BUILD_DIR)/graph.o $(BUILD_DIR)/GraphTest.o \
					$(BUILD_DIR)/gtest_main.a 
	$(CXX) -lpthread $(CPPFLAGS) $(CXXFLAGS) -pthread $^ -o $@

$(BUILD_DIR)/NodeTest.o : common/graph/tests/NodeTest.cpp \
                     common/graph/Node.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c common/graph/tests/NodeTest.cpp -o $@

$(BUILD_DIR)/NodeTest : $(BUILD_DIR)/node.o $(BUILD_DIR)/NodeTest.o \
					$(BUILD_DIR)/gtest_main.a 
	$(CXX) -lpthread $(CPPFLAGS) $(CXXFLAGS) -pthread $^ -o $@
