#cs335 mid

all: mid335

mid335: mid335.cpp
	g++ mid335.cpp -Wall -o mid  -lm

clean:
	rm -f mid
	rm -f *.o
