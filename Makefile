
CXX       := g++
CXX_FLAGS := -lGL -lglut

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   :=
EXECUTABLE  := main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $^ $(CXX_FLAGS) -I${INCLUDE} -o $@ $(LIBRARIES)


clean:
	rm $(BIN)/*