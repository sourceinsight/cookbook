all : Calculator
Calculator : main.cpp Node.cpp Scanner.cpp Parser.cpp
	g++ $^ -o $@ 

clean:
	rm -f Calculator

.PHONY : all clean
