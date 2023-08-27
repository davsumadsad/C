/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "sine.h"
#include "stdbool.h"
#include <stdio.h>

//#define CORDIC_approx
#define CORDIC_tan_lut
//#define Print_CORDIC_sine
//#define Print_CORDIC_tan


int sine_table [256] = {0, 2, 3, 5, 6, 8, 9, 11, 13, 14, 16, 17, 19, 20, 22, 24, 25, 27, 28, 30, 31, 33, 34, 36, 38, 39, 41, 42, 44, 45, 47, 48, 50, 51, 53, 55, 56, 58, 59, 61, 62, 64, 65, 67, 68, 70, 71, 73, 74, 76, 77, 79, 80, 82, 83, 85, 86, 88, 89, 91, 92, 94, 95, 96, 98, 99, 101, 102, 104, 105, 107, 108, 109, 111, 112, 114, 115, 116, 118, 119, 121, 122, 123, 125, 126, 128, 129, 130, 132, 133, 134, 136, 137, 138, 140, 141, 142, 143, 145, 146, 147, 149, 150, 151, 152, 154, 155, 156, 157, 159, 160, 161, 162, 164, 165, 166, 167, 168, 169, 171, 172, 173, 174, 175, 176, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 213, 214, 215, 216, 217, 218, 218, 219, 220, 221, 222, 222, 223, 224, 225, 225, 226, 227, 228, 228, 229, 230, 230, 231, 232, 232, 233, 234, 234, 235, 235, 236, 237, 237, 238, 238, 239, 239, 240, 241, 241, 242, 242, 243, 243, 243, 244, 244, 245, 245, 246, 246, 247, 247, 247, 248, 248, 248, 249, 249, 249, 250, 250, 250, 251, 251, 251, 251, 252, 252, 252, 252, 253, 253, 253, 253, 253, 254, 254, 254, 254, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};

int tan_lut[15] = {11520, 6912, 3584, 1792, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1};


int inv_tan = 45 << SHIFT;   // These values represent 45 degrees, in fixed point using 8 bits
int rot_angle = 45 << SHIFT; // so the decimal value 45 is shifted to the left 8 times
int cur_angle = 0;       // The current angle after each rotation
int iteration = 0;       // The number of iterations or calculations to make for CORDIC
int x[50] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int y[50] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Mmmm... CORDIC, this was a fun function to work with
// References:
// https://en.wikipedia.org/wiki/CORDIC        Wiki info dump
// https://www.youtube.com/watch?v=bre7MVlxq7o Explained like math lecture
// https://www.youtube.com/watch?v=4HxdV5xEe9k By Texas Instrument, more applications based, go to timestamp 7:27 for
//                                             equation this function was based off from
// https://www.eit.lth.se/fileadmin/eit/courses/eitf35/2017/CORDIC_For_Dummies.pdf Explains how to inverse tan from a set of x and y values
// CORDIC is a clever algorithm, basically you can approximate Sine and Cosine
// values, by doing bit shifts and additions, the more you shift and add,
// the better the approximations. Obviously since this uses fixed-point
// notation you're limited in the number of shifts you can do
//

#ifdef CORDIC_approx
struct XY CORDIC(int angle){
    struct XY vect;
    x[0] = CONV;
    y[0] = 0;
    iteration = 0;
    cur_angle = 0;
    while(iteration < MX_Iterte){

        // if the target angle is greater than the current angle
        // rotate in the positive or negative direction.
        // The step size for each iteration is halved everytime
        // beginning with 45 degrees. 45 degrees is in fixed
        // point format 
        if(angle > cur_angle) rot_angle = (inv_tan >> iteration);      // Rotate in the positive direction
        else                  rot_angle = ~(inv_tan >> iteration) + 1; // Rotate in the negative direction, (using 2's complement)
        
        #ifdef Print_CORDIC_sine
        printf("Iteration:%d\n", iteration); 
        printf("Target angle:%d\n",angle); 
        printf("Current angle:%d\n",cur_angle);
        printf("Rotate angle by:%d\n",rot_angle);

        printf("x[%d]: %d\n", iteration, x[iteration]);
        printf("y[%d]: %d\n", iteration, y[iteration]);
        printf("-------------\n");
        #endif

        // Depending on the direction of rotation, calculate
        // the x[iteration+1] and y[iteration+1] vectors differently. 
        // To determine the direction, shift the rotation value then 
        // check the sign bit
        if(!(rot_angle >> 31)){
            x[iteration+1] = x[iteration] + (~(y[iteration] >> iteration) +1); 
            y[iteration+1] = ((x[iteration] >> iteration)) + y[iteration];
        }
        else{
            x[iteration+1] = x[iteration] + ((y[iteration] >> iteration)); 
            y[iteration+1] = ((~(x[iteration] >> iteration))+1) + y[iteration];
        }

        cur_angle += rot_angle; // add rotation angle to the current angle

        iteration++;  // go to the next iteration
    }

    vect.X_fx = (x[MX_Iterte-1]*155) >> SHIFT;
    vect.Y_fx = (y[MX_Iterte-1]*155) >> SHIFT;

    return vect;


}

int CORDIC_aTan(int x_comp, int y_comp){

    x[0] = x_comp;
    y[0] = y_comp;
    iteration = 0;
    cur_angle = 0;
    while(iteration < MX_Iterte){

        // if the current y[iteration] is greater than 0
        // rotate in the positive.
        // The step size for each iteration is halved everytime
        // beginning with 45 degrees. 45 degrees is in fixed
        // point format 
        if(y[iteration] > 0) rot_angle = (inv_tan >> iteration);      // Rotate in the positive direction
        else                  rot_angle = ~(inv_tan >> iteration) + 1; // Rotate in the negative direction, (using 2's complement)
        
        #ifdef Print_CORDIC_tan
        printf("Iteration:%d\n", iteration); 
        printf("Current angle:%d\n",cur_angle);
        printf("Rotate angle by:%d\n",rot_angle);

        printf("x[%d]: %d\n", iteration, x[iteration]);
        printf("y[%d]: %d\n", iteration, y[iteration]);
        printf("-------------\n");
        #endif

        // Depending on the sign of y[iteration], calculate
        // the x[iteration+1] and y[iteration+1] vectors differently. 
        // if y[iteration] is 0 return the cur_angle value
        if(y[iteration] < 0){
            x[iteration+1] = x[iteration] + (~(y[iteration] >> iteration) +1); 
            y[iteration+1] = ((x[iteration] >> iteration)) + y[iteration];
        }
        else if(y[iteration] > 0) {
            x[iteration+1] = x[iteration] + ((y[iteration] >> iteration)); 
            y[iteration+1] = ((~(x[iteration] >> iteration))+1) + y[iteration];
        }
        else return cur_angle;

        cur_angle += rot_angle; // add rotation angle to the current angle

        iteration++;  // go to the next iteration
    }

    return cur_angle;
}
#endif

#ifdef CORDIC_tan_lut
struct XY CORDIC(int angle){
    struct XY vect;
    x[0] = CONV;
    y[0] = 0;
    iteration = 0;
    cur_angle = 0;
    while(iteration < MX_Iterte){

        // if the target angle is greater than the current angle
        // rotate in the positive or negative direction.
        // The step size for each iteration is halved everytime
        // beginning with 45 degrees. 45 degrees is in fixed
        // point format 
        if(angle > cur_angle) rot_angle = tan_lut[iteration];      // Rotate in the positive direction
        else                  rot_angle = ~(tan_lut[iteration]) + 1; // Rotate in the negative direction, (using 2's complement)
        
        #ifdef Print_CORDIC_sine
        printf("Iteration:%d\n", iteration); 
        printf("Target angle:%d\n",angle); 
        printf("Current angle:%d\n",cur_angle);
        printf("Rotate angle by:%d\n",rot_angle);

        printf("x[%d]: %d\n", iteration, x[iteration]);
        printf("y[%d]: %d\n", iteration, y[iteration]);
        printf("-------------\n");
        #endif

        // Depending on the direction of rotation, calculate
        // the x[iteration+1] and y[iteration+1] vectors differently. 
        // To determine the direction, shift the rotation value then 
        // check the sign bit
        if(!(rot_angle >> 31)){
            x[iteration+1] = x[iteration] + (~(y[iteration] >> iteration) +1); 
            y[iteration+1] = ((x[iteration] >> iteration)) + y[iteration];
        }
        else{
            x[iteration+1] = x[iteration] + ((y[iteration] >> iteration)); 
            y[iteration+1] = ((~(x[iteration] >> iteration))+1) + y[iteration];
        }

        cur_angle += rot_angle; // add rotation angle to the current angle

        iteration++;  // go to the next iteration
    }

    vect.X_fx = (x[MX_Iterte-1]*155) >> SHIFT;
    vect.Y_fx = (y[MX_Iterte-1]*155) >> SHIFT;

    return vect;


}

int CORDIC_aTan(int x_comp, int y_comp){

    x[0] = x_comp;
    y[0] = y_comp;
    iteration = 0;
    cur_angle = 0;
    while(iteration < MX_Iterte){

        // if the current y[iteration] is greater than 0
        // rotate in the positive.
        // The step size for each iteration is halved everytime
        // beginning with 45 degrees. 45 degrees is in fixed
        // point format 
        if(y[iteration] > 0) rot_angle = (tan_lut[iteration]);      // Rotate in the positive direction
        else                  rot_angle = ~(tan_lut[iteration]) + 1; // Rotate in the negative direction, (using 2's complement)
        
        #ifdef Print_CORDIC_tan
        printf("Iteration:%d\n", iteration); 
        printf("Current angle:%d\n",cur_angle);
        printf("Rotate angle by:%d\n",rot_angle);

        printf("x[%d]: %d\n", iteration, x[iteration]);
        printf("y[%d]: %d\n", iteration, y[iteration]);
        printf("-------------\n");
        #endif

        // Depending on the sign of y[iteration], calculate
        // the x[iteration+1] and y[iteration+1] vectors differently. 
        // if y[iteration] is 0 return the cur_angle value
        if(y[iteration] < 0){
            x[iteration+1] = x[iteration] + (~(y[iteration] >> iteration) +1); 
            y[iteration+1] = ((x[iteration] >> iteration)) + y[iteration];
        }
        else if(y[iteration] > 0) {
            x[iteration+1] = x[iteration] + ((y[iteration] >> iteration)); 
            y[iteration+1] = ((~(x[iteration] >> iteration))+1) + y[iteration];
        }
        else return cur_angle;

        cur_angle += rot_angle; // add rotation angle to the current angle

        iteration++;  // go to the next iteration
    }

    return cur_angle;
}

#endif




float  conv_ang_fp(int angle){
    return (float) angle / (1<<SHIFT);
}

int    conv_ang_fx(float angle){
    return ((int) angle) << SHIFT;
}


struct XY_flt conv_vect_fp(struct XY vctrs){
    struct XY_flt xy_loc;    
    xy_loc.X_flt = ((float) vctrs.X_fx) / CONV ;
    xy_loc.Y_flt = ((float) vctrs.Y_fx) / CONV ;

    return xy_loc;
}

struct XY    conv_vect_fx(struct XY_flt vctrs){
    struct XY xy_loc;
    xy_loc.X_fx = (int) (vctrs.X_flt * CONV );
    xy_loc.Y_fx = (int) (vctrs.Y_flt * CONV );

    
    return xy_loc;

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
         printf("Sine of %d, is %d,", angle, sine_table[index]);
    
    return 0;
}

int cosine(int angle){
    int loc_angle = angle;
    int index = angle & 0x3fffffff;
    bool neg = loc_angle >> 31; 
    bool rev = loc_angle >> 30 & 0x01; 
    
    
    if(rev){
    index = (index) & 0xff;
    printf("Yes reverse %d\n", index);//angle = ~angle;
    }
    
    if(neg){
        printf("Yes negative %d\n", -sine_table[index]);//angle = ~angle;
        //return -sine_table[index];
    }
    else
         printf("Cosine of %d, is %d,", angle, sine_table[~index & 0xff]);
    
    return 0;
    
    
}

/*
* Change log
*

  Rev      By                Date           Comments
  0.01     David Sumadsad    06Aug2023      -Initial build
  0.02     David Sumadsad    15Aug2023      -Fully functioning CORDIC function
  0.03     David Sumadsad    25Aug2023      -Added a... 
                                              -Angled Fixed point to floating point
                                              -Floating Point (Deg) point to fixed point
  0.04     David Sumadsad    26Aug2023      -Added a... 
                                              -Angled Fixed point to floating point for vector components
                                              -Floating Point (Deg) point to fixed point for vector components
                                            -FOR THE FUTURE
                                              -Think about adding a copy of CORDIC and CORDIC_aTan, instead
                                               of doing bit shifts which approximate the value, multiply
                                               using an array with pre loaded Tan values. 
                                              -This idea came up because CORDIC_aTan(0,xxx) returns 83 deg
                                               NOT 90 deg
*/



