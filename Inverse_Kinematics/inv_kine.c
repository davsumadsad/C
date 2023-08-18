



#include "sine.h"
#include "stdbool.h"
#include <stdio.h>







int theta1(int px, int py){

    return CORDIC_aTan(px, py);
}


int theta2(int nx, int ny, int nz, int theta1, int theta3){

int x_vect = nx + ny;
int y_vect = nz;

return CORDIC_aTan(x_vect, y_vect) + theta3;

}

int theta3(int px, int py, int pz, int theta1){

int x_vect1 = 0;
int y_vect1 = 0;


int x_vect3 = (((px + py)*(px + py)) + ((pz-3)*(pz-3)) - 36 -121 ) / 132;
int y_vect3 = sqrt(1-(x_vect3*x_vect3));

return CORDIC_aTan(x_vect, y_vect);

}