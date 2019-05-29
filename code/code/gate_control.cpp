#include "gate_control.h"
#include "E101.h"


gate_control::gate_control()
{
	IP = new char[14]{ '1','3','0','.','1','9','5','.','6','.','1','9','6' };
	PASSWORD = new char[6];
	REQUEST = new char[6]{ 'P', 'l', 'e', 'a', 's', 'e' };
	KNOWN_PASSWORD = new char[6]{ '1', '2', '3', '4', '5', '6' };
}


gate_control::~gate_control()
{
}

void gate_control::setIP(char ip[])
{
	IP = ip;
}

void gate_control::getIP(char* outIP)
{
	outIP = IP;
}

/*
	Helpful function to print out what we have currently set the IP of the server to be.
*/
void gate_control::printIP()
{
	std::cout << "Current Gate IP is set at: " << IP << "\n";
}

/*
	Main gate opening logic. Performs the following steps
	- connect to server
	- send please to the server
	- get and store the password from the server
	- sends password to server
	- opens gate
*/
void gate_control::openGate()
{
	std::cout << "Connecting to server...\n";
	//connect_to_server(IP, 1024); //Connect to server with IP variable on port 1024

	std::cout << "Sending message to server...\n";
	//send_to_server(REQUEST); //Send 'please' to the server

	std::cout << "Recieving password from server\n";
	//receive_from_server(PASSWORD); //Get the password back from the server

	std::cout << "Sending password to server...\n";
	//send_to_server(KNOWN_PASSWORD); //Send the password to the server and open the gate

	std::cout << "Opening Gate";
}


