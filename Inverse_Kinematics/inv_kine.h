


#ifndef INV_KINE_H 
#define INV_KINE_H

#include "sine.h"


#define X 0
#define Y 1
#define Z 2

extern float n[3];
extern float o[3];
extern float a[3];
extern float p[3];


int theta1(float px, float py);
int theta2(float nx, float ny, float nz, float theta1_x, float theta1_y);
int theta3(float px, float py, float pz, float theta1_x, float theta1_y);



#endif
