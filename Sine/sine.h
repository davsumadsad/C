/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sine.h
 * Author: Vidda
 *
 * Created on August 6, 2023, 6:58 PM
 */

#ifndef SINE_H
#define SINE_H

#define SINE 0
#define COSINE 1
#define TAN 2

#define MX_Iterte 15

struct XY{
    int X;
    int Y;
};

struct XY_Prime{
    int X_Prime;
    int Y_Prime;
};

extern int sine_table[256];
extern struct XY xy;
extern struct XY_Prime xy_prime;

extern int inv_tan;
extern int rot_angle;
extern int cur_angle;
extern int total_angle;
extern int iteration;
extern int x[50];
extern int y[50];


struct XY CORDIC(int angle);
int    CORDIC_aTan(int x_comp, int y_comp);
int    sine(int angle);
int    cosine(int angle);
float  conv_fp(int angle);


#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* CORDIC_H */

