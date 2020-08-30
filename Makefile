src = $(wildcard ./src/*.cpp)
obj = $(patsubst ./src/%.cpp, ./obj/%.o, $(src))

includePath = ./include
includePathForRapidJson =  ./include/rapidjson

extArgs = -levent -g -Wall -I $(includePath)

ALL : main.out

$(obj) : ./obj/%.o : ./src/%.cpp
	g++ -c $< -o $@ $(extArgs)
 
main.out : $(obj)
	g++ $^ -o ./bin/$@ $(extArgs)

clean :
	-rm -rf $(obj) ./bin/main.out

run :
	./bin/main.out

init : 
	mkdir src && mkdir bin && mkdir obj && mkdir include

rerun : 
	make clean && make && make run

.PHONY : clean ALL run init rerun
