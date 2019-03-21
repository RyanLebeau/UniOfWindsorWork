CXXFLAGS=-std=c++17 -O3 -Wall -Wextra

all: a04.exe run-demo

clean:
	rm -f *.exe *.o

a04-provided.o: a04-provided.cxx a04-provided.hxx
	$(CXX) $(CXXFLAGS) -c -o $@ $<

a04.o: a04.cxx a04-provided.hxx a04-main-provided.hxx
	$(CXX) $(CXXFLAGS) -c -o $@ $<

a04.exe: a04.o a04-provided.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $+

run-demo: a04.exe unclean-input.csv unclean-correct-output.csv
	(cat unclean-input.csv | ./$< | diff --to-file=unclean-correct-output.csv -) \
		&& echo "$< produces valid output."

