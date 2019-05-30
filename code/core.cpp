// offlineDevelopment.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include "gate_control.h"
#include "camera_control.h"
#include "E101.h"
using namespace std;

int main() {

	// Declare gate control object
	//gate_control control;
	//control.printIP();
	//control.openGate();
	cout << "hello";
	camera_control camera;
	camera.followLine();
	camera.goToRedColumn()
	camera.goToGreenColumn()
	camera.goToBlueColumn()
	camera.goToFinish()

	return 0;
}
