CXX = g++
CXXFLAGS = -g -Wall -pedantic

APP_FILES_O = obj/StateMachine.o
TEST_FILES_O = obj/StateMachineTests.o $(APP_FILES_O)

clean:
	rm -r bin
	rm -f $(APP_FILES_O) $(TEST_FILES_O)

purge: clean
	rm -rf obj

test: bin bin/run_tests
	bin/run_tests

obj:
	mkdir -p obj

obj/catch.o:  __tests__/suite.cpp
	$(CXX) __tests__/suite.cpp -c -o $@ $(CXXFLAGS) 

obj/StateMachineTests.o: __tests__/StateMachineTests.cpp
	$(CXX) __tests__/StateMachineTests.cpp -c -o $@ $(CXXFLAGS)

obj/StateMachine.o: StateMachine.hpp StateMachine.cpp LightsDriver.hpp
	$(CXX) StateMachine.cpp -c -o $@ $(CXXFLAGS)

bin: obj
	mkdir -p bin

bin/run_tests: $(APP_FILES_O) $(TEST_FILES_O) obj/catch.o
	$(CXX) $(TEST_FILES_O) obj/catch.o -o $@ $(CXXFLAGS)
