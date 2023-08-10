/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "sine.h"
#include "stdbool.h"
#include <stdio.h>
int sine_table [256] = {0, 2, 3, 5, 6, 8, 9, 11, 13, 14, 16, 17, 19, 20, 22, 24, 25, 27, 28, 30, 31, 33, 34, 36, 38, 39, 41, 42, 44, 45, 47, 48, 50, 51, 53, 55, 56, 58, 59, 61, 62, 64, 65, 67, 68, 70, 71, 73, 74, 76, 77, 79, 80, 82, 83, 85, 86, 88, 89, 91, 92, 94, 95, 96, 98, 99, 101, 102, 104, 105, 107, 108, 109, 111, 112, 114, 115, 116, 118, 119, 121, 122, 123, 125, 126, 128, 129, 130, 132, 133, 134, 136, 137, 138, 140, 141, 142, 143, 145, 146, 147, 149, 150, 151, 152, 154, 155, 156, 157, 159, 160, 161, 162, 164, 165, 166, 167, 168, 169, 171, 172, 173, 174, 175, 176, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 213, 214, 215, 216, 217, 218, 218, 219, 220, 221, 222, 222, 223, 224, 225, 225, 226, 227, 228, 228, 229, 230, 230, 231, 232, 232, 233, 234, 234, 235, 235, 236, 237, 237, 238, 238, 239, 239, 240, 241, 241, 242, 242, 243, 243, 243, 244, 244, 245, 245, 246, 246, 247, 247, 247, 248, 248, 248, 249, 249, 249, 250, 250, 250, 251, 251, 251, 251, 252, 252, 252, 252, 253, 253, 253, 253, 253, 254, 254, 254, 254, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};

struct XY xy = {255 , 0};
struct XY_Prime xy_prime = {0 , 0};

struct XY_Prime CORDIC(int angle){
    
    
    
}


int sine(int angle){
    int loc_angle = angle;
    int index = angle & 0x3fffffff;
    bool neg = loc_angle >> 31; 
    bool rev = loc_angle >> 30 & 0x01; 
    
    
    if(rev){
        index = (~index) & 0xff;
        printf("Yes reverse %d\n", index);//angle = ~angle;
    }
    
    if(neg){
        printf("Yes negative %d\n", -sine_table[index]);//angle = ~angle;
        //return -sine_table[index];
    }
    else
        return 1; //sine_table[index];
    
    return 0;
}

int cosine(int angle){
    //if(angle)
    
    
    
    
    
}




