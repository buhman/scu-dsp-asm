CXXFLAGS = -Og -g -Wall -Wextra -Werror -Wfatal-errors -Wpedantic -std=c++20
LDFLAGS =

TARGET =
CXX = $(TARGET)clang++

SRC = main.cpp
SRC += lexer.cpp
SRC += ast.cpp
SRC += parser.cpp
OBJ = $(patsubst %.cpp,%.o,$(SRC))
DEP = $(patsubst %.cpp,%.d,$(SRC))

all: main

-include $(DEP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MF $(basename $<).d -c $< -o $@

main: $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	rm -f *.o *.d *.gch

.SUFFIXES:
.INTERMEDIATE:
.SECONDARY:
.PHONY: all clean

%: RCS/%,v
%: RCS/%
%: %,v
%: s.%
%: SCCS/s.%
