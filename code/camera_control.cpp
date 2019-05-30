
#include "camera_control.h"
#include "E101.h"
#include <iostream>
#define swap(a,b) {int16_t t = a; a = b; b = t;}

camera_control::camera_control()
{
	image_width = 320;
	image_height = 240;
	dead_stop = 48;
	base_speed = 5;
	
}



const int IMG_WIDTH = 320;
const int IMG_HEIGHT = 240;
	
const int ROW = IMG_HEIGHT - 50;
const int ROW_AHEAD = 50;

int lumosity_threshhold = 50;

void bresenhamLine(float x1, float y1, float x2, float y2, int r, int g, int b){
	// Bresenham's line algorithm 
	bool steep = ((abs(y2 - y1)) > (abs(x2 - x1)));
	if (steep){
		swap(x1, y1);
		swap(x2, y2);
	}

	if (x1 > x2){
		swap(x1, x2);
		swap(y1, y2);
	}

	float dx = x2 - x1;
	float dy = abs(y2 - y1);

	float error = dx / 2.0f;
	int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	int maxX = (int)x2;

	for (int x = (int)x1; x < maxX; x++){
		if (steep){
			set_pixel(y,x, r,g,b);
		}
		else{
			set_pixel(x,y, r,g,b);
		}

		error -= dy;
		if (error < 0){
			y += ystep;
			error += dx;
		}
	}
}


int coefLeft = 0;
int coefRight = 0;

void camera_control::followLine()
{
	init(0);
	open_screen_stream();
	
	
		
	while (true){
		
			
		//60 = max forward
		//30 = max blackward
		//40 = 0
		//set_motors(1,40);//right wheel, pin 1
		//set_motors(5,40);//left wheel, pin 5
		
		getProportional();
		
		//printf("lm=%f rm=%f prop=%f", leftSpd, rightSpd, propSpd);
		
		double scale = 0.025;
		
		double ls = 45 + ((-coefLeft * scale)); 
		double rs = 50 + ((coefRight * scale)); 
		
		std::cout << "Left Speed: " << ls << "  Right speed: " << rs << std::endl;
		
		//std::cout << propSpd << std::endl;
		
		set_motors(5, ls);
		set_motors(1, rs);
		

		hardware_exchange();
	
	}
	

}
 

void camera_control::updateWhiteThreshold()
{

	//take_picture();
	int min = 255;
	int max = 0;

	for (int i = 0; i < 320; i++) {
		int curPix = get_pixel(120, i, 3);

		if (curPix > max) {
			max = curPix;
		}
		else if (curPix < min) {
			min = curPix;
		}

	}

	lumosity_threshhold = (max + min) / 2;

}                                                                                                                                                                                                                                                    



int lineCentre = 0;

double camera_control::getProportional()
{
	int white[320];
	take_picture();
	//updateWhiteThreshold();
	
	int tapeWidth = 0;
	int tapeStart = 0;
	bool first = true;
	for (int i = 0; i < image_width; i++) {
		white[i] = -1;

		int intensity = (int)get_pixel(120,i, 3);
		
		
		
		bool blackPresent = intensity < 60;
		
		
		if (blackPresent ){
			if (first){
				first = false;
				tapeStart = i;
			}
			tapeWidth++;
			set_pixel(120,i, 0, 255, 255);
			white[i] = 1;
		} 
	}
	
	if (tapeWidth == 0){
		tapeStart = 320;
	}
	lineCentre = tapeStart + ((int)tapeWidth/2);
	bresenhamLine(110, lineCentre, 130, lineCentre, 0,255,255);
	//set_pixel(125, lineCentre, 255,0,0); // Identify center of tape
	
	
	
	update_screen();

	double err = 0;

	//for (int i = 0; i < 320; i++) {
	//	err += (i - 160) * white[i];
	//}
	
	coefLeft = 160 - lineCentre;
	coefRight = lineCentre - 160;

	return err;

}
// Quad 4

void camera_control::goToRedColumn()
{
	init(0);
	open_screen_stream();
	
	
		
	while (true){
		

		
		getRedProportional();
		//getGreenProportional();
		//getBlueProportional();
		

		
		double scale = 0.025;
		
		double ls = 45 + ((-coefLeft * scale)); 
		double rs = 50 + ((coefRight * scale)); 
		
		std::cout << "Left Speed: " << ls << "  Right speed: " << rs << std::endl;
		
		//std::cout << propSpd << std::endl;
		
		set_motors(5, ls);
		set_motors(1, rs);
		

		hardware_exchange();
	
	}
	

}
void camera_control::goToGreenColumn()
{
	init(0);
	open_screen_stream();
	
	
		
	while (true){
		

		
		//getRedProportional();
		getGreenProportional();
		//getBlueProportional();
		

		
		double scale = 0.025;
		
		double ls = 45 + ((-coefLeft * scale)); 
		double rs = 50 + ((coefRight * scale)); 
		
		std::cout << "Left Speed: " << ls << "  Right speed: " << rs << std::endl;
		
		//std::cout << propSpd << std::endl;
		
		set_motors(5, ls);
		set_motors(1, rs);
		

		hardware_exchange();
	
	}
	

}
void camera_control::goToBlueColumn()
{
	init(0);
	open_screen_stream();
	
	
		
	while (true){
		

		
		//getRedProportional();
		//getGreenProportional();
		getBlueProportional();
		

		
		double scale = 0.025;
		
		double ls = 45 + ((-coefLeft * scale)); 
		double rs = 50 + ((coefRight * scale)); 
		
		std::cout << "Left Speed: " << ls << "  Right speed: " << rs << std::endl;
		
		//std::cout << propSpd << std::endl;
		
		set_motors(5, ls);
		set_motors(1, rs);
		

		hardware_exchange();
	
	}
	

}
void camera_control::updateRedThreshold()
{

	//take_picture();
	int minR, minG, minB = 255;
	int maxR, maxG, maxB = 0;

	for (int i = 0; i < 320; i++) {
		int curPixR = get_pixel(120, i, 0);

		if (curPixR > maxR) {
			maxR = curPixR;
		}
		else if (curPixR < minR) {
			minR = curPixR;
		}

	}

	lumosity_threshhold = (maxR + minR) / 2;

}
void camera_control::updateGreenThreshold()
{

	//take_picture();
	int minG = 255;
	int maxG = 0;

	for (int i = 0; i < 320; i++) {
		int curPixG = get_pixel(120, i, 1);
		

		if (curPixG > maxG) {
			maxG = curPixG;
		}
		else if (curPixG < minG) {
			minG = curPixG;
		}

	}

	lumosity_threshhold = (maxG + minG) / 2;

}
void camera_control::updateBlueThreshold()
{

	//take_picture();
	int minB = 255;
	int maxB = 0;

	for (int i = 0; i < 320; i++) {
		int curPixB = get_pixel(120, i, 2);

		if (curPixB > maxB) {
			maxB = curPixB;
		}
		else if (curPixB < minB) {
			minB = curPixB;
		}

	}

	lumosity_threshhold = (maxB + minB) / 2;

}                                                                                                                                                                                                                                                    



int lineCentre = 0;

double camera_control::getRedProportional()
{
	int red[320];
	take_picture();
	//updateRedThreshold();
	
	int redWidth = 0;
	int redStart = 0;
	bool first = true;
	for (int i = 0; i < image_width; i++) {
		red[i] = -1;

		int intensityR = (int)get_pixel(120,i, 3);
		
		
		
		bool redPresent = intensityR < 60;
		
		
		if (redPresent ){
			if (first){
				first = false;
				redStart = i;
			}
			redWidth++;
			set_pixel(120,i, 0, 255, 255);
			red[i] = 1;
		} 
	}
	
	if (redWidth == 0){
		redStart = 320;
	}
	lineCentre = redStart + ((int)redWidth/2);
	bresenhamLine(110, lineCentre, 130, lineCentre, 0,255,255);
	//set_pixel(125, lineCentre, 255,0,0); // Identify center of red column
	
	
	
	update_screen();

	double err = 0;


	
	coefLeft = 160 - lineCentre;
	coefRight = lineCentre - 160;

	return err;

}
