Target = MathStringParser
CC = g++
bin = bin/
build = build/

folders = ${bin}
folders += ${build}



SRC = ${wildcard *.cpp}
OBJ = ${patsubst %.cpp,${bin}%.o,${SRC}}




Main: fileMaker compiler
	${build}${Target}
	
fileMaker:
	if not exist ${bin} mkdir ${subst /,\, ${folders}}

compiler: ${OBJ}
	${CC} -o ${build}${Target} $^ 

${bin}%.o: %.cpp
	${CC} -o $@ -c $^