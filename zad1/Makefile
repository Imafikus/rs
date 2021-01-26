PROGRAM = encoder
CXX       = clang++
CXXFLAGS  = -g -std=c++17

$(PROGRAM): encoder_test.o catch.o
	$(CXX) -o $(PROGRAM) $^
	
encoder_test.o: test.cpp encoder.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
catch.o: catch.cpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -czvf $(PROGRAM).tar.bz2 *
