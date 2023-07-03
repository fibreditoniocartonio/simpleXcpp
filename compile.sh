#!
appname="simpleXcpp"

rm $appname
g++ -c main.cpp
g++ -c src/*.cpp 
g++ *.o -o $appname -lsfml-graphics -lsfml-window -lsfml-system
rm -rf *.o
