# Go to dir with project in terminal and run:
#	c++ -MM *.cpp >> makefile

# Compile with debug option and all warnings on. ------------
CXX = c++
CXXFLAGS = -std=c++14 -g -Wall -O1

# Object modules comprising this application ----------------
OBJ = main.o FileID.o Params.o Sniff.o tools.o

# Build targets
TARGETS = findit

# .PHONY: means that the targets that follow should be built even 
# though the are not real files.
.PHONY: all clean
all: $(TARGETS)

findit: $(OBJ)
	$(CXX)  -o $@ $(CXXFLAGS) $(OBJ)

# Delete .o and exe files and force recompilation. ----------
clean:
	rm -f $(OBJ) $(TARGETS)

# Dependencies ----------------------------------------------
# The  lines below were generated by the c++ -MM command up at the top.
FileID.o: FileID.cpp FileID.hpp tools.hpp
Params.o: Params.cpp Params.hpp tools.hpp
Sniff.o: Sniff.cpp Sniff.hpp Params.hpp tools.hpp FileID.hpp
main.o: main.cpp Params.hpp tools.hpp FileID.hpp Sniff.hpp
tools.o: tools.cpp tools.hpp
