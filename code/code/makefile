compile: main.cpp
	g++ -c  main.cpp

build: main.o
	g++ -o main main.o -le101
run:
	 sudo ./main

core.o : core.cpp
	g++ -c core.cpp

main.o : main.cpp
	g++ -c main.cpp

coreVII.o : coreVII.cpp
	g++ -c coreVII.cpp

camera_control.o: camera_control.cpp camera_control.h
	g++ -c camera_control.cpp

gate_control.o: gate_control.cpp gate_control.h
	g++ -c gate_control.cpp


