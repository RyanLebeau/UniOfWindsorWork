CXXFLAGS=-std=c++17 -Wall -Wextra -O3

all: a05.exe run-demo

clean: 
	rm -f *.exe

a05.exe: a05.cxx a05-provided.hxx
	$(CXX) $(CXXFLAGS) -o $@ $<

run-demo: a05.exe hamlet-words.dat \
	hamlet-words.dat.output.txt
	(cat hamlet-words.dat | ./$< | diff --to-file=hamlet-words.dat.output.txt -) \
		&& echo "$< produces valid output."

