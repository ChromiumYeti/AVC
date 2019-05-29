#pragma once
#include "E101.h"
class camera_control
{
	

private:
	int minWhite;
	int maxWhite;
	int image_width;
	int image_height;
	int dead_stop;
	int base_speed;
public:
	camera_control(); //Constructor
	

	double whiteAmnt = 0;


	void followLine();

	void updateWhiteThreshold();
	double getProportional();




};

