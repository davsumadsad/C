/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Vidda
 *
 * Created on August 6, 2023, 6:52 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include "sine.h"
/*
 * 
 */

int angle = 12800;
int xvect = 0;
int yvect = 0;

struct XY vectorz;


int ang   = 0;
float deg = 90;
int main(int argc, char** argv) {

// #ifdef Test_CORDIC_Sine


printf("Angle in degrees Floating: %f \n", deg);

ang = conv_ang_fx(deg);
printf("Angle in degrees Fixed   : %d \n", ang);

vectorz = CORDIC(ang);

printf("Sine of %d is %d \n"    , angle, vectorz.X_fx);
printf("Cosine of %d is %d\n"    , angle, vectorz.Y_fx);
// printf("TAN of %d is %d \n"    , angle, CORDIC(TAN, angle));
// #endif

ang = CORDIC_aTan(-3, 255);

printf("Tan of x:%d y:%d %d \n", vectorz.X_fx, vectorz.Y_fx, ang);
printf("Fixed Point angle: %d in floating point is %f \n\n", ang, conv_ang_fp(ang));

printf("%d",SHIFT);
    
    return (EXIT_SUCCESS);
}

