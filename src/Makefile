
CXX = g++
CXXFLAGS = -O0 -g -Wall
#CXXFLAGS = -O2 -Wall
INCLUDE = 
TLIB = 

#-----Suffix Rules---------------------------
# set up C++ suffixes and relationship between .cc and .o files

.SUFFIXES: .cpp

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $<

.cpp :
	$(CXX) $(CXXFLAGS) $(INCLUDE) $< -o $@ -lm $(TLIB) -lg++

#-----File Dependencies----------------------

GOAL = SGA

SRC = ga.cpp GAmain.cpp myrand.cpp chromosome.cpp global.cpp mt19937ar.cpp line_operator.cpp


OBJ = $(addsuffix .o, $(basename $(SRC)))

$(GOAL): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(TLIB) -o $@ $(OBJ)

#-----Other stuff----------------------------
depend:
	makedepend $(SRC)

clean:
	rm -f $(OBJ) $(GOAL)
