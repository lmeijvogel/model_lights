CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -pedantic

APP_FILES_O = obj/StateMachine.o obj/NullLightsDriver.o obj/LightsDriver.o obj/GuiLight.o
TEST_FILES_O = obj/StateMachineTests.o obj/LightsDriverTests.o $(APP_FILES_O)

default: bin bin/main

bin/main: src/main.cpp $(APP_FILES_O)
	$(CXX) src/main.cpp $(APP_FILES_O) $(CXXFLAGS) -lncurses -o $@

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

obj/LightsDriverTests.o: __tests__/LightsDriverTests.cpp
	$(CXX) __tests__/LightsDriverTests.cpp -c -o $@ $(CXXFLAGS)

obj/LightsDriver.o: src/LightsDriver.hpp src/LightsDriver.cpp src/AbstractLightsDriver.hpp src/Light.hpp
	$(CXX) src/LightsDriver.cpp -c -o $@ $(CXXFLAGS)

obj/StateMachine.o: src/StateMachine.hpp src/StateMachine.cpp src/AbstractLightsDriver.hpp
	$(CXX) src/StateMachine.cpp -c -o $@ $(CXXFLAGS)

obj/GuiLight.o: src/GuiLight.hpp src/GuiLight.cpp src/Light.hpp
	$(CXX) src/GuiLight.cpp -c -o $@ $(CXXFLAGS)

obj/NullLightsDriver.o: src/NullLightsDriver.cpp src/AbstractLightsDriver.hpp
	$(CXX) src/NullLightsDriver.cpp -c -o $@ $(CXXFLAGS)

bin: obj
	mkdir -p bin

bin/run_tests: $(APP_FILES_O) $(TEST_FILES_O) obj/catch.o
	$(CXX) $(TEST_FILES_O) obj/catch.o -o $@ $(CXXFLAGS)
