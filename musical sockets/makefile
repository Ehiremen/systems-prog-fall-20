
# Go to dir with project in terminal and run:
#	c++ -MM *.cpp >> makefile

# Compile with debug option and all warnings on. ------------
CXX = c++
CXXFLAGS = -std=c++14 -g -Wall -O1

# Object modules comprising this application ----------------
OBJ-MOM = mom.o momLogic.o tools.o
OBJ-KID = kid.o kidLogic.o tools.o

# Build targets
TARGETS = mom kid

# .PHONY: means that the targets that follow should be built even
# though the are not real files.
.PHONY: all clean
all: $(TARGETS)

mom: $(OBJ-MOM)
	$(CXX)  -o $@ $(CXXFLAGS) $(OBJ-MOM)
	
kid: $(OBJ-KID)
	$(CXX)  -o $@ $(CXXFLAGS) $(OBJ-KID)

# Delete .o and exe files and force recompilation. ----------
clean:
	rm -f $(OBJ-MOM) $(OBJ-KID) $(TARGETS)

# Dependencies ----------------------------------------------
kid.o: kid.cpp
kidLogic.o: kidLogic.cpp kidLogic.hpp protocol.hpp socktypes.h tools.hpp
mom.o: mom.cpp momLogic.hpp protocol.hpp socktypes.h tools.hpp
momLogic.o: momLogic.cpp momLogic.hpp protocol.hpp socktypes.h tools.hpp
tools.o: tools.cpp tools.hpp
