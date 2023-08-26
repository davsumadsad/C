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

int main(int argc, char** argv) {

// #ifdef Test_CORDIC_Sine


vectorz = CORDIC(angle);

printf("Sine of %d is %d \n"    , angle, vectorz.X);
printf("Cosine of %d is %d\n"    , angle, vectorz.Y);
// printf("TAN of %d is %d \n"    , angle, CORDIC(TAN, angle));
// #endif

ang = CORDIC_aTan(vectorz.X, vectorz.Y);

printf("Tan of x:%d y:%d %d \n", vectorz.X, vectorz.Y, ang);
printf("Fixed Point angle: %d in floating point is %f \n\n", ang, conv_fp(ang));


    
    return (EXIT_SUCCESS);
}

