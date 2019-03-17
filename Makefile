CXX = g++
CXXFLAGS = -std=c++0x -g -Wall -pedantic

APP_FILES_O = obj/ExpanderOutput.o obj/Expander.o obj/CircularActivator.o obj/StateMachine.o obj/WheelStateMachine.o obj/LightCollectionController.o obj/LightController.o obj/NullLightController.o obj/GuiLight.o obj/RandomGenerator.o
TEST_FILES_O = obj/CircularActivatorTests.o obj/MockLightController.o obj/StateMachineTests.o obj/WheelStateMachineTests.o obj/LightCollectionControllerTests.o obj/LightControllerTests.o $(APP_FILES_O)

default: bin bin/main

arduino:
	$(MAKE) -C src

upload:
	$(MAKE) -C src upload

all: default arduino

bin/main: main.cpp $(APP_FILES_O) obj/BareGui.o obj/NCursesGui.o
	$(CXX) main.cpp $(APP_FILES_O) obj/BareGui.o obj/NCursesGui.o $(CXXFLAGS) -lncurses -o $@

clean:
	rm -rf bin
	rm -f $(APP_FILES_O) $(TEST_FILES_O)
	$(MAKE) -C src clean

purge: clean
	rm -rf obj

test: bin bin/run_tests
	bin/run_tests

obj:
	mkdir -p obj

obj/catch.o:  __tests__/suite.cpp
	$(CXX) __tests__/suite.cpp -c -o $@ $(CXXFLAGS)

obj/MockLightController.o: __tests__/MockLightController.cpp __tests__/MockLightController.h
	$(CXX) __tests__/MockLightController.cpp -c -o $@ $(CXXFLAGS)

obj/CircularActivatorTests.o: __tests__/CircularActivatorTests.cpp
	$(CXX) __tests__/CircularActivatorTests.cpp -c -o $@ $(CXXFLAGS)

obj/StateMachineTests.o: __tests__/StateMachineTests.cpp
	$(CXX) __tests__/StateMachineTests.cpp -c -o $@ $(CXXFLAGS)

obj/WheelStateMachineTests.o: __tests__/WheelStateMachineTests.cpp
	$(CXX) __tests__/WheelStateMachineTests.cpp -c -o $@ $(CXXFLAGS)

obj/LightControllerTests.o: __tests__/LightControllerTests.cpp
	$(CXX) __tests__/LightControllerTests.cpp -c -o $@ $(CXXFLAGS)

obj/LightCollectionControllerTests.o: __tests__/LightCollectionControllerTests.cpp
	$(CXX) __tests__/LightCollectionControllerTests.cpp -c -o $@ $(CXXFLAGS)

obj/LightCollectionController.o: src/LightCollectionController.h src/LightCollectionController.cpp src/AbstractLightController.h src/Light.h
	$(CXX) src/LightCollectionController.cpp -c -o $@ $(CXXFLAGS)

obj/CircularActivator.o: src/CircularActivator.h src/CircularActivator.cpp src/AbstractLightController.h
	$(CXX) src/CircularActivator.cpp -c -o $@ $(CXXFLAGS)

obj/StateMachine.o: src/StateMachine.h src/StateMachine.cpp src/AbstractLightController.h
	$(CXX) src/StateMachine.cpp -c -o $@ $(CXXFLAGS)

obj/WheelStateMachine.o: src/WheelStateMachine.h src/WheelStateMachine.cpp src/AbstractLightController.h
	$(CXX) src/WheelStateMachine.cpp -c -o $@ $(CXXFLAGS)

obj/BareGui.o: BareGui.h BareGui.cpp Gui.h
	$(CXX) BareGui.cpp -c -o $@ $(CXXFLAGS)

obj/NCursesGui.o: NCursesGui.h NCursesGui.cpp Gui.h
	$(CXX) NCursesGui.cpp -c -o $@ $(CXXFLAGS)

obj/LightController.o: src/LightController.h src/LightController.cpp src/AbstractLightController.h
	$(CXX) src/LightController.cpp -c -o $@ $(CXXFLAGS)

obj/NullLightController.o: src/NullLightController.h src/NullLightController.cpp src/AbstractLightController.h
	$(CXX) src/NullLightController.cpp -c -o $@ $(CXXFLAGS)

obj/GuiLight.o: src/GuiLight.h src/GuiLight.cpp src/Light.h
	$(CXX) src/GuiLight.cpp -c -o $@ $(CXXFLAGS)

obj/RandomGenerator.o: src/RandomGenerator.cpp
	$(CXX) src/RandomGenerator.cpp -c -o $@ $(CXXFLAGS)

obj/ExpanderOutput.o: ExpanderOutput.h ExpanderOutput.cpp
	$(CXX) ExpanderOutput.cpp -c -o $@ $(CXXFLAGS)

obj/Expander.o: Expander.h Expander.cpp
	$(CXX) Expander.cpp -c -o $@ $(CXXFLAGS)

bin: obj
	mkdir -p bin

bin/run_tests: $(APP_FILES_O) $(TEST_FILES_O) obj/catch.o
	$(CXX) $(TEST_FILES_O) obj/catch.o -o $@ $(CXXFLAGS)
