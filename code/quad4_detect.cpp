#include <stdio.h>
#include "E101.h"
#include <unistd.h>
#include <time.h>
//#include <string>

int main()
{
int err;
printf("Quad 4 detection\n");
err = init();
int countrun = 0;


open_screen_stream();
while(countrun <10000)
	{
	take_picture();
	update_screen();
	int countr = 0;
	int countc = 0;
	int totred = 0;
	int totblue = 0;
	int totgreen = 0;
	//int totint = 0;
	//double redness;
	//double blueness;
	//double greenness;

	while(countr<240)
		{
		if(countr > 60 && countr < 180) //adjust detection area for AVC
			{
			  while(countc<320)
				{
				  if(countc > 80 && countc < 240)
					{ 
			   totred = totred + (int)get_pixel(countr, countc, 0);
			   totgreen = totgreen + (int)get_pixel(countr,countc, 1);
			   totblue = totblue + (int)get_pixel(countr,countc, 2);
			   //totint = totint + (int)get_pixel(countr, countc, 3);
			   		   
			   //redness = (float) totred/(3.0*(float)totint);
			   //blueness = (float) totblue/(3.0*(float)totint);
			   //greenness = (float) totgreen/(3.0*(float)totint);
					}
					countc++;
				}
			}
	  countr++;
		}
	 //printf("red \t%d\n",totred);
	 //printf("green \t%d\n",totgreen);
	 //printf("blue \t%d\n",totblue);
	 //printf("redness %f\n",redness);
	 //printf("blueness %f\n",blueness);
	 //printf("greenness %f\n",greenness);
	 
			 if(totred > (totblue*1.2) and totred > (totgreen*1.2)){ //comparison with a 20% variance for light intensity/specular
			   // if seeing a red thing, the AVC should move toward it but not touch it
			   
		   }
		   else if(totblue > (totred*1.2) and totblue > (totgreen*1.2)){ //comparison with a 20% variance for light intensity/specular
			   // if seeing a blue thing, the AVC should move toward it but not touch it
		   }
		   else if(totgreen > (totblue*1.2) and totgreen > (totred*1.2)){ //comparison with a 20% variance for light intensity/specular
			   // if seeing a green thing, the AVC should move toward it but not touch it
		   }
		  
		   else{
				// if not, keep looking
		   }
	 countrun++;
	}
close_screen_stream();
printf("After init() error=%d\n", err);
printf("Again\n");
return 0;
}

