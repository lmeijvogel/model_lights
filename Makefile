CXX = g++
CXXFLAGS = -g -Wall -pedantic

APP_FILES_O = obj/StateMachine.o obj/NullLightController.o obj/LightCollectionController.o obj/LightController.o obj/GuiLight.o obj/RandomGenerator.o
TEST_FILES_O = obj/MockLightController.o obj/StateMachineTests.o obj/LightCollectionControllerTests.o obj/LightControllerTests.o $(APP_FILES_O)

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

obj/MockLightController.o: __tests__/MockLightController.cpp __tests__/MockLightController.hpp
	$(CXX) __tests__/MockLightController.cpp -c -o $@ $(CXXFLAGS)

obj/StateMachineTests.o: __tests__/StateMachineTests.cpp
	$(CXX) __tests__/StateMachineTests.cpp -c -o $@ $(CXXFLAGS)

obj/LightControllerTests.o: __tests__/LightControllerTests.cpp
	$(CXX) __tests__/LightControllerTests.cpp -c -o $@ $(CXXFLAGS)

obj/LightCollectionControllerTests.o: __tests__/LightCollectionControllerTests.cpp
	$(CXX) __tests__/LightCollectionControllerTests.cpp -c -o $@ $(CXXFLAGS)

obj/LightCollectionController.o: src/LightCollectionController.hpp src/LightCollectionController.cpp src/AbstractLightController.hpp src/Light.hpp
	$(CXX) src/LightCollectionController.cpp -c -o $@ $(CXXFLAGS)

obj/StateMachine.o: src/StateMachine.hpp src/StateMachine.cpp src/AbstractLightController.hpp
	$(CXX) src/StateMachine.cpp -c -o $@ $(CXXFLAGS)

obj/LightController.o: src/LightController.hpp src/LightController.cpp src/AbstractLightController.hpp
	$(CXX) src/LightController.cpp -c -o $@ $(CXXFLAGS)

obj/GuiLight.o: src/GuiLight.hpp src/GuiLight.cpp src/Light.hpp
	$(CXX) src/GuiLight.cpp -c -o $@ $(CXXFLAGS)

obj/NullLightController.o: src/NullLightController.cpp src/AbstractLightController.hpp
	$(CXX) src/NullLightController.cpp -c -o $@ $(CXXFLAGS)

obj/RandomGenerator.o: src/RandomGenerator.cpp
	$(CXX) src/RandomGenerator.cpp -c -o $@ $(CXXFLAGS)

bin: obj
	mkdir -p bin

bin/run_tests: $(APP_FILES_O) $(TEST_FILES_O) obj/catch.o
	$(CXX) $(TEST_FILES_O) obj/catch.o -o $@ $(CXXFLAGS)
