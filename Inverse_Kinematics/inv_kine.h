


#ifndef INV_KINE_H 
#define INV_KINE_H

#include "sine.h"


#define X 0
#define Y 1
#define Z 2

extern int n[3];
extern int o[3];
extern int a[3];
extern int p[3];


int theta1(int px, int py);
int theta2(int nx, int ny, int nz, int theta1_x, int theta1_y);
int theta3(int px, int py, int pz);



#endif