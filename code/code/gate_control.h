#pragma once
#include <string>
#include <iostream>
#include "E101.h"
using std::string;
/*
Gate control interface
Author: Jack Naish

*/
class gate_control
{
	//Interface for the gate control class
private:
	char* IP;      //Ip of the server we are connecting to
	char* REQUEST; //Holds the 'please' request
	char* PASSWORD;//The password for the server
	char* KNOWN_PASSWORD;//The actual password for the server. Shhhh!
public:
	gate_control(); //Constructor
	~gate_control(); //Constructor


	/*
	Abstract interfaces of two methods to get and set Ip address of gate
	we are to connect to.

	Note: gate takes a char array as the IP address.
	*/
	void setIP(char ip[]);
	void getIP(char * outIP);
	void printIP();




	/*
	This is the main method which sents the request to the server
	to open the gate.
	*/
	void openGate();


};

