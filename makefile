OBJ = plugboard.o main.o errors.o reflector.o rotor.o enigma.o
EXE = enigma
CXX = g++
CXXFLAGS = -Wall -g -Wextra

$(EXE): $(OBJ)
	$(CXX) $^ -o $@

%.o: %.cpp makefile
	$(CXX) $(CXXFLAGS) -c $<
clean:
	rm -f $(OBJ) $(EXE)
