debug: test
	@builds/FireWorks
test: main.cpp src/*.cpp
	@g++ main.cpp src/*.cpp -o builds/FireWorks -L./lib -lraylib -framework Cocoa -framework IOKit -std=c++11
clean:
	rm builds/* -r
	rm temp -r
