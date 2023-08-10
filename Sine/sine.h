/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cordic.h
 * Author: Vidda
 *
 * Created on August 6, 2023, 6:58 PM
 */

#ifndef CORDIC_H
#define CORDIC_H





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



int sine(int angle);
int cosine(int angle);



#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* CORDIC_H */

