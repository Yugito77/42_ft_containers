#!/bin/bash

NAME="Containers"
CXX="g++"
CXXFLAGS="-Wall -Werror -Wextra -std=c++98 -fsanitize=address -g3"
SRCS="../main.cpp
    ../tests/vector_assign.cpp
    ../tests/vector_begin.cpp
    ../tests/vector_construct.cpp
    ../tests/vector_front.cpp
    ../tests/vector_reserve.cpp
    ../tests/vector_resize.cpp
    ../tests/map_find.cpp
    ../tests/map_insert.cpp
    ../tests/map_operator.cpp
    ../tests/map_size.cpp
        "

#------------------FT----------------------------#
echo "compiling with FT"
make="$CXX $CXXFLAGS $SRCS -DLIB=ft -o $NAME"

${make}

echo "compilation FT done"

./Containers > result_ft

#--------------------STD-------------------------#
echo "compiling with STD"

make="$CXX $CXXFLAGS $SRCS -DLIB=std -o $NAME"

${make}

echo "compilation STD done"

./Containers > result_std

diff result_ft result_std > result_diff