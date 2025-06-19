del time0.o
del usetime.exe
g++ -c ./timelib/*.cpp 
g++ -o usetime.exe usetime.cpp time0.o

del vector.o
del randwalk.exe
g++ -c ./vectorlib/*.cpp 
g++ -o randwalk.exe randwalk.cpp vector.o