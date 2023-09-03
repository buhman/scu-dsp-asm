STATIC = -static -static-libgcc -static-libstdc++
CXXFLAGS = -Og -g -Wall -Wextra -Werror -Wfatal-errors -Wno-c99-designator -std=c++20
LDFLAGS =

TARGET ?=
CXX = $(TARGET)g++

SUFFIX ?=

ASM_SRC = main.cpp
ASM_SRC += lexer.cpp
ASM_SRC += ast_printer.cpp
ASM_SRC += ast_resolver.cpp
ASM_SRC += ast_emitter.cpp
ASM_SRC += parser.cpp
ASM_SRC += stmt_string.cpp
ASM_OBJ = $(patsubst %.cpp,%.o,$(ASM_SRC))
ASM_DEP = $(patsubst %.cpp,%.d,$(ASM_SRC))
ASM_MAIN ?= scu-dsp-asm$(SUFFIX)

DIS_SRC = disassemble.cpp
DIS_SRC += ast_printer.cpp
DIS_SRC += stmt_string.cpp
DIS_OBJ = $(patsubst %.cpp,%.o,$(DIS_SRC))
DIS_DEP = $(patsubst %.cpp,%.d,$(DIS_SRC))
DIS_MAIN ?= scu-dsp-dis$(SUFFIX)

all: $(ASM_MAIN) $(DIS_MAIN)

-include $(sort $(ASM_DEP) $(DIS_DEP))

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MF $(basename $<).d -c $< -o $@

$(ASM_MAIN): $(ASM_OBJ)
	$(CXX) $(STATIC) $(LDFLAGS) $^ -o $@

$(DIS_MAIN): $(DIS_OBJ)
	$(CXX) $(STATIC) $(LDFLAGS) $^ -o $@

clean:
	rm -f *.o *.d *.gch $(MAIN)

.SUFFIXES:
.INTERMEDIATE:
.SECONDARY:
.PHONY: all clean

%: RCS/%,v
%: RCS/%
%: %,v
%: s.%
%: SCCS/s.%
