// jack from friday

#include <iostream>
#include <string>
#include "gate_control.h"
#include "camera_control.h"
#include "E101.h"

using namespace std;

const int IMG_WIDTH = 320;
const int IMG_HEIGHT = 240;
	
const int ROW = IMG_HEIGHT - 50;
const int ROW_AHEAD = 50;


int lum_threshold; //Weather black is white or white is black



int main() {
	int err;
 
	err = init(0);


	//60 = max forward
	//30 = max blackward
	set_motors(1,60);//right wheel, pin 1

	set_motors(5,30);//left wheel, pin 5

	
	 hardware_exchange();
	 take_picture();
	 update_screen();
	 
	 //char fname[5]={'r','r','r','r','r'};
	 //save_picture(fname);
	 //display_picture(0,200000);
	 	
	 //sleep1(1,200);
     
    
    //save_picture("file1");
  
	
	return 0;
		
	
}
