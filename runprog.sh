ssh pi@10.140.233.164
cd Desktop/ENGR101_AVC_GIT/ENGR101_AVC
git pull
cd code/code/
c++ -c core.cpp camera_control.cpp gate_control.cpp
c++ -o core core.o camera_control.o gate_control.o -le101
