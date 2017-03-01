
OUTPUT	:= xcs_lbp
CFLAGS := `pkg-config --cflags --libs opencv` -ggdb3

all: $(OUTPUT)

$(OUTPUT): LBP.cpp
	g++ $(CFLAGS) LBP.cpp -o $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)

clean:
	rm -f $(OUTPUT)
