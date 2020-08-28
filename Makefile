src = $(wildcard ./src/*.cpp)
obj = $(patsubst ./src/%.cpp, ./obj/%.o, $(src))

includePath = ./include

extArgs = -levent -g -Wall

ALL : main.out

$(obj) : ./obj/%.o : ./src/%.cpp
	g++ -c $< -o $@ $(extArgs) -I $(includePath)
 
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
