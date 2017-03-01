
OUTPUT	:= xcs_lbp
CFLAGS := `pkg-config --cflags --libs opencv` -ggdb3 --std=c++11

SRC	:= main.cpp lbp.cpp

all: $(OUTPUT)

lbp.cpp: lbp.hpp

$(OUTPUT): $(SRC)
	g++ $(CFLAGS) $(SRC) -o $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)

clean:
	rm -f $(OUTPUT)
