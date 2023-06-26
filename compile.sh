#!
appname="simpleXcpp"

rm $appname
g++ -c main.cpp $1
g++ main.o -o $appname -lsfml-graphics -lsfml-window -lsfml-system
rm -rf *.o
