debug: test
	@builds/FireWorks
test: main.cpp src/*.cpp
	@g++ main.cpp src/*.cpp -o builds/FireWorks -L./lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -std=c++14
clean:
	rm builds/* -r
	rm temp -r
