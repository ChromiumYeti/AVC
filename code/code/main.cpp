/*
Main.cpp
This file supports functionality to: 
1. Communicate with the server and open the gate
2. Follow the Q2 and Q3 line. 
  2a. Adjust camera tilt servo.
*/
#include <iostream>
#include "E101.h"

using namespace std;

class Gate {
private:
	char* IP;      //Ip of the server we are connecting to
	char* REQUEST; //Holds the 'please' request
	char* PASSWORD;//The password for the server
	char* KNOWN_PASSWORD;//The actual password for the server. Shhhh!
public:
	Gate();


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


Gate::Gate()
{
	IP = new char[14]{ '1','3','0','.','1','9','5','.','6','.','1','9','6' };
	PASSWORD = new char[6];
	REQUEST = new char[6]{ 'P', 'l', 'e', 'a', 's', 'e' };
	KNOWN_PASSWORD = new char[6]{ '1', '2', '3', '4', '5', '6' };
}



void Gate::setIP(char ip[])
{
	IP = ip;
}

void Gate::getIP(char* outIP)
{
	outIP = IP;
}

/*
	Helpful function to print out what we have currently set the IP of the server to be.
*/
void Gate::printIP()
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
void Gate::openGate()
{
	std::cout << "Connecting to server...\n";
	connect_to_server(IP, 1024); //Connect to server with IP variable on port 1024

	std::cout << "Sending message to server...\n";
	send_to_server(REQUEST); //Send 'please' to the server

	std::cout << "Recieving password from server\n";
	receive_from_server(PASSWORD); //Get the password back from the server

	std::cout << "Sending password to server...\n";
	send_to_server(KNOWN_PASSWORD); //Send the password to the server and open the gate

	std::cout << "Opening Gate";
}

class Robot {

private:
	int dv;
	double line_error;
	int quadrant;
	const int cam_width=320;
	const int cam_height=260;
	const int v_left_go=48;
	const int v_right_go=40;
	double kp;
	int line_present = 1;

public:
	Robot(){};
	int v_left;
	int v_right;
	int cam_tilt;
	int InitHardware();
	void ReadSetMotors();
	void SetMotors();
	int MeasureLine();
	int FollowLine();
};

int Robot::InitHardware() {
	int err;
	err = init(0);
	v_left = 48;
	v_right = 48;
	cam_tilt = 48;
	dv = 0;
	set_motors(5, v_left);
	set_motors(1, v_right);
	set_motors(4, cam_tilt);
	set_motors(2, cam_tilt);
	set_motors(3, cam_tilt);

	hardware_exchange();
	return err;

}

void Robot::ReadSetMotors() {
	cout << "Cam Tilt:" << endl;
	cin >> cam_tilt;
	cin.ignore();

	cout << "Enter v_left" << endl;
	cin >> v_left;

	cout << "Enter v_right" << endl;
	cin >> v_right;
	cin.ignore();

	cout << "Values entered" << endl;
	dv = 0;
	SetMotors();
	sleep1(600);


}

void Robot::SetMotors() {
	cout << "v_left" << v_left << "v_right" << v_right;
	cout << "cam_tilt" << cam_tilt << endl;

	set_motors(5, v_left);
	set_motors(1, v_right);
	set_motors(4, cam_tilt);
	set_motors(2, cam_tilt);
	set_motors(3, cam_tilt);

	hardware_exchange();

}

int Robot::MeasureLine() {
	take_picture();
	update_screen();
	int row = 120;
	int col = 0;
	int max = 0;
	int min = 256;

	for (col = 0; col < cam_width; col++) {
		int wh = get_pixel(row, col, 3);
		if (wh > max) max = wh;
		if (wh < max) min = wh;

	}
	line_present = 1;
	if (min > 80) {
		line_present = 0;
		return -1;
	}

	double thr = (max + min) / 2.0;
	line_error = 0.0;
	int nblack = 0;

	for (col = 0; col < cam_width; col++) {
		if (get_pixel(row, col, 3) > thr) {
			
		}

		if (get_pixel(row, col, 3) <= thr) {
			line_error = line_error + (col - cam_width / 2);
			nblack++;

		}
	}
	if (nblack == 0) {
		line_present = 0;
		return -1;
	}

	line_present = 1;
	line_error = line_error / nblack;
	return 0;

}

int Robot::FollowLine() {
	MeasureLine();
	if (line_present) {
		dv = (int)(line_error*kp);
		v_left = v_left_go + dv;
		v_right = v_right_go + dv;
		cout << "line_error" << line_error << "dv=" << dv;
		SetMotors();
	}
	else {
		cout << "Line missing" << endl;
		v_left = 43;
		v_right = 52;
		cam_tilt = 48;
		SetMotors();
		sleep1(100);

	}
	return 0;
}

int main()
{
	Robot robot;
	robot.InitHardware();
	
	open_screen_stream();
	while (true) {
		//robot.ReadSetMotors();
		robot.MeasureLine();

		robot.FollowLine();
		update_screen();

		
	}

	close_screen_stream();
	stoph();
	return 0;
}
