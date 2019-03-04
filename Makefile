CXX = g++
CXXFLAGS = -g -Wall -pedantic

clean:
	rm -r bin

purge: clean
	rm -rf obj

test: bin/run_tests
	bin/run_tests

obj:
	mkdir -p obj

obj/catch.o: obj __tests__/suite.cpp
	$(CXX) __tests__/suite.cpp -c -o $@ $(CXXFLAGS) 

bin:
	mkdir -p bin

bin/run_tests: bin obj/catch.o __tests__/StateMachineTests.cpp
	$(CXX) obj/catch.o __tests__/StateMachineTests.cpp -o $@ $(CXXFLAGS) 
