STATIC = -static -static-libgcc -static-libstdc++
CXXFLAGS = -Og -g -Wall -Wextra -Werror -Wfatal-errors -Wno-c99-designator -std=c++20
LDFLAGS =

TARGET =
CXX = $(TARGET)g++

SRC = main.cpp
SRC += lexer.cpp
SRC += ast_printer.cpp
SRC += ast_resolver.cpp
SRC += ast_emitter.cpp
SRC += parser.cpp
SRC += stmt_string.cpp
OBJ = $(patsubst %.cpp,%.o,$(SRC))
DEP = $(patsubst %.cpp,%.d,$(SRC))

MAIN = scu-dsp-asm

all: $(MAIN)

-include $(DEP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MF $(basename $<).d -c $< -o $@

$(MAIN): $(OBJ)
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
