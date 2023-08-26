


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include "sine.h"
#include "inv_kine.h"

int   angle_fx  = 0;
float angle_flt = 0;

int   angle3_fx  = 0;
float angle3_flt = 0;

struct XY     vectors ;
struct XY_flt vectors_flt;

struct XY     vectors1;

struct XY     vectors3 ;
struct XY_flt vectors3_flt;

int main(int argc, char** argv) {

    p[X] = 7.77  ;
    p[Y] = 7.77  ;
    p[Z] = 9     ;
    n[X] = 0.707 ;
    n[Y] = 0.707 ;
    n[Z] = 0     ;

    

    angle_fx = theta1(p[X], p[Y]);
    angle_flt = conv_ang_fp(angle_fx);

    vectors     = CORDIC(angle_fx);
    vectors_flt = conv_vect_fp(vectors);

    printf("For px and py values: %f %f\n", p[X], p[Y]);
    printf("Angle 1 in Fixed point is: %d\n", angle_fx);    
    printf("Angle 1 in Float point is: %f\n", angle_flt);    
    printf("Angle 1 components in Fixed X and Y: %d %d \n", vectors.X_fx, vectors.Y_fx); 
    printf("Angle 1 components in Float X and Y: %f %f \n", vectors_flt.X_flt, vectors_flt.Y_flt);
    

    angle3_fx = theta3(p[X], p[Y], p[Z], vectors_flt.X_flt, vectors_flt.Y_flt);
    angle3_flt = conv_ang_fp(angle3_fx);

    vectors3     = CORDIC(angle3_fx);
    vectors3_flt = conv_vect_fp(vectors3);

    printf("Angle 3 in Fixed point is: %d\n", angle3_fx);    
    printf("Angle 3 in Float point is: %f\n", angle3_flt);    
    printf("Angle 3 components in Fixed X and Y: %d %d \n", vectors3.X_fx, vectors3.Y_fx); 
    printf("Angle 3 components in Float X and Y: %f %f \n", vectors3_flt.X_flt, vectors3_flt.Y_flt);

    printf("%d bit shift right %d", -55, -55 >> 1);


    return 1;
}
