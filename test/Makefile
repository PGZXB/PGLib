src = $(wildcard *.cpp)
bin = $(patsubst %.cpp, ./bin/%.out, $(src))

includePathArgs = -I ../include -I ../include/base 

extArgs = -g -Wall $(includePathArgs)

$(bin) : ./bin/%.out : ./%.cpp
	g++ $< -o $@ $(extArgs)

clean :
	-rm -rf ./bin/*

remake : 
	make clean && make

.PHONY : clean
