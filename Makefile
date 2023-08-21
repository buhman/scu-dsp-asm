CXXFLAGS = -Og -g -Wall -Wextra -Werror -Wfatal-errors -Wpedantic -Wno-c99-designator -std=c++20
LDFLAGS =

TARGET =
CXX = $(TARGET)clang++

SRC = main.cpp
SRC += lexer.cpp
SRC += ast_printer.cpp
SRC += ast_resolver.cpp
SRC += ast_emitter.cpp
SRC += parser.cpp
SRC += stmt_string.cpp
OBJ = $(patsubst %.cpp,%.o,$(SRC))
DEP = $(patsubst %.cpp,%.d,$(SRC))

all: main

-include $(DEP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MF $(basename $<).d -c $< -o $@

main: $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	rm -f *.o *.d *.gch main

.SUFFIXES:
.INTERMEDIATE:
.SECONDARY:
.PHONY: all clean

%: RCS/%,v
%: RCS/%
%: %,v
%: s.%
%: SCCS/s.%
