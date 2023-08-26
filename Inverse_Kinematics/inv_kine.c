



#include "sine.h"
#include "stdbool.h"
#include <stdio.h>
#include <math.h>

float n[3];
float o[3];
float a[3];
float p[3];


int theta1(float px, float py){
    
    return CORDIC_aTan( (int)px << 8, (int) py << 8);
}


int theta2(float nx, float ny, float nz, float theta1_x, float theta1_y, int theta3){


int x_vect = nx*theta1_x + ny*theta1_y;
int y_vect = nz;

return CORDIC_aTan(x_vect, y_vect) + theta3;

}

int theta3(float px, float py, float pz, float theta1_x, float theta1_y){

float x_vect1 = 0;
float y_vect1 = 0;


float x_vect3 = (((px*theta1_x + py*theta1_y)*(px*theta1_x + py*theta1_y)) + ((pz-3)*(pz-3)) - 157 ) / 132;
float y_vect3 = sqrt(1-(x_vect3*x_vect3));


printf("X Vector: %f\n",x_vect3);
printf("Y Vector: %f\n",y_vect3);

printf("X Vector: %f\n",x_vect3*CONV);
printf("Y Vector: %f\n",y_vect3*CONV);

return CORDIC_aTan( (int) (x_vect3 * CONV) , (int) (y_vect3 * CONV));

}
