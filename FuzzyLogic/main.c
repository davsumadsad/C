/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Vidda
 *
 * Created on February 14, 2023, 4:53 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuzzyLogic.h"
/*
 * 
 */
int main(int argc, char** argv) {

    // Write C code here
    
    int Weights[7] = {-40, -25, -12, 0, 12, 25, -40};    
    
    

    int defuzz_num   = 0;
    int defuzz_denom = 0;

    for(int height = 0; height < 2; height++){
        for(int row = 0; row < Num_Memb_Conditions; row++){
            for(int column = 0; column < Num_Memb_Actions; column++){
            //printf("%d %d %d ", row, column, height);
            
            Proportion[row][column][height] = 0;
            }
        printf(" \n");
        }
    }
    
    

    int Input[3] = {0, 0, 100}; 
    int Output_Centroid[7]; // Array to store area values
    
  
    
    
    //#define Show_Memb
    //#define Show_Memb_Degree
    //#define Show_Output_Memb
    //#define Show_Single_Crisps
    //#define Show_Output_Memb_Array
    #define DoALoop
    #define LoopNum 52
    #define LoopRes 10
    #define Show_Excel
     
    
    float Excel[Num_Actions][LoopNum][LoopNum];    

    int indexx1 = 0;
    int indexx2 = 0;
    
    for(int height = 0; height < Num_Actions; height++)
        for(int row = 0; row < LoopNum; row++)
            for(int column = 0; column < LoopNum; column++)
            Excel[height][row][column] = 0;
        
    
// Calculate Membership slope and y-intercept values  
// in the shape of a trapezoid
    for(int condition = 0; condition < Num_Conditions; condition++)
    {
        for(int member = 0; member < Num_Memb_Conditions; member++){
           Calculate_Trapezoid_Slope_int(&Members_Conditions[condition][member]);          
        }
    }
    
    
  
#ifdef Show_Memb
    
    
    for(int condition = 0; condition < Num_Conditions; condition++)
    {
        printf("%s Membership functions \n", Conditions_Name[condition]);
        for(int member = 0; member < Num_Memb_Conditions; member++){
            
            
            printf("%s \n", Members_Conditions[condition][member].Name);
            for(int equation = 0; equation < 2; equation++){
                
                printf("Slope is %d \n", Members_Conditions[condition][member].Slope[equation]);
                printf("Y-Intercepy is %d \n", Members_Conditions[condition][member].Y_Intercept[equation]);
                
            }   
            printf("\n");
        }
        printf("\n\n");
    }
    
#endif
    

#ifdef DoALoop

    //for(int w = 0; w < 7; w++)
    //    printf("%d " , Weights[w]);
    //        printf("\n");

    int Parameter = 2;
    int Cond0 = 0;
    int Cond1 = 0;
    
    switch(Parameter){
        case(0):
            Cond0 = 0;
            Cond1 = 1;
            Input[2] = 10;
        break;
        case(1):
            
            Cond0 = 0;
            Cond1 = 2;
            Input[2] = 0;
            
        break;
        case(2):
            Cond0 = 0;
            Cond1 = 1;
            Input[2] = 0;
            
        break;
        
        default:
        break;
    }
    
    
    for(Input[Cond0] = 0; Input[Cond0] < LoopNum; Input[Cond0] ++){
        
        indexx2 = 0;
        for(Input[Cond1] = 0; Input[Cond1] < LoopNum; Input[Cond1] ++){
#endif    
        //printf("%d %d %d \n", Input[0], Input[1], Input[2]);
    
    // Calculate the the degree of membership for temperature

    
    for(int condition = 0; condition < Num_Conditions; condition++)
    {
        for(int member = 0; member < Num_Memb_Conditions; member++){
            
            Members_Conditions[condition][member].Output = Calculate_Membership_int(&Members_Conditions[condition][member], Input[condition]*LoopRes);
             
        }
    }
    
    
    
    #ifdef Show_Memb_Degree

    
    for(int condition = 0; condition < Num_Conditions; condition++)
    {
        printf("Membership Value %s for %d \n", Conditions_Name[condition], Input[condition]);
        for(int member = 0; member < Num_Memb_Conditions; member++){
            
            printf("%s : %d\n", Members_Conditions[condition][member].Name, Members_Conditions[condition][member].Output);
            
        }
        printf("\n");
    }
    
    
    
    
    
    #endif
    
    // Compare the degree of memberships of temperature with pressure
    // Record and save the smaller value in the 2D array Output_Min
    // Since there are 3 members for temperature and pressure
    // There should be a total of 9 membership comparisons
    // Example: 
    // Compare degree of Cold Temperature with degree of Low Pressure
    // Compare degree of Cold Temperature with degree of Medium Pressure
    // Compare degree of Cold Temperature with degree of High Pressure
    // Compare degree of Warm Temperature with degree of Low Pressure
    // Compare degree of Warm Temperature with degree of Medium Pressure
    // Compare degree of Warm Temperature with degree of High Pressure
    // ...And so on
   


    
    //////////////////////////////////////////////////////////////
    //                              Pressure
    //                      Low     |  Medium   | High      |
    //                  |---------- |---------- |---------- |  
    //              Cold|  Full On  |Partial On |Partial On |
    //                  |---------- |---------- |---------- |
    //  Temperature Warm|Partial On |  Half On  |Partial Off|
    //                  |---------- |---------- |---------- |
    //              Hot |Partial Off|Partial Off| Full Off  |
    //                  |-----------|-----------|-----------|
    // 
    //  For this section you'll need to design a rule table as shown
    //  above. The table decides how the Output should respond.
    // 
    //  For example, if the Temperature is Warm and Pressure is Medium
    //  then the Output should be Half On.
    //  However, since it's possible that the pressure can be either 
    //  Medium or High, then the Output should either be Half On or
    //  Partial Off
    //
    // For this section take the smaller values that were saved from the
    // previous sections and assign the value to its Output 
    // Example:
    // The smaller value saved when comparing the degree of Cold Temperature 
    // with degree of Low Pressure is now assigned to the Full On Output square
    // 
    // Note:
    // As far as I can tell this is the only section where the user
    // would need to intervene and hard code the behavior as opposed 
    // to some recursive methid that would be used, simply being
    // the rule table being based on is up to the user/designer 
    // and may be unique from system to system. Guess that's 
    // human reasoning for you
    //
    
    Proportion[Oscil][Non][NC] = Osc[Non].Output;
    Proportion[Oscil][Low][NL] = Osc[Low].Output;
    Proportion[Oscil][Mod][NM] = Osc[Mod].Output;
    Proportion[Oscil][Hi][NH]  = Osc[Hi].Output;
    Proportion[Oscil][VHi][NH] = Osc[VHi].Output;
    
    Proportion[Rspnse][Non][PM] = Resp[Non].Output;
    Proportion[Rspnse][Low][PM] = Resp[Low].Output;
    Proportion[Rspnse][Mod][PL] = Resp[Mod].Output;
    Proportion[Rspnse][Hi][NL]  = Resp[Hi].Output;
    Proportion[Rspnse][VHi][NM] = Resp[VHi].Output;
     
    Proportion[Offst][Non][NC] = Off[Non].Output;
    Proportion[Offst][Low][PL] = Off[Low].Output;
    Proportion[Offst][Mod][PL] = Off[Mod].Output;
    Proportion[Offst][Hi][PL]  = Off[Hi].Output;
    Proportion[Offst][VHi][PM] = Off[VHi].Output;   
    /////////////////////////////////////////////////////////
    Integral[Oscil][Non][NC] = Osc[Non].Output;
    Integral[Oscil][Low][NC] = Osc[Low].Output;
    Integral[Oscil][Mod][NL] = Osc[Mod].Output;
    Integral[Oscil][Hi][NM]  = Osc[Hi].Output;
    Integral[Oscil][VHi][NM] = Osc[VHi].Output;
    
    Integral[Rspnse][Non][NC] = 0;
    Integral[Rspnse][Low][NC] = 0;
    Integral[Rspnse][Mod][NL] = 0;
    Integral[Rspnse][Hi][NL]  = 0;
    Integral[Rspnse][VHi][NL] = 0;
    
    Integral[Offst][Non][NC] = Off[Non].Output;
    Integral[Offst][Low][NC] = Off[Low].Output;
    Integral[Offst][Mod][PL] = Off[Mod].Output;
    Integral[Offst][Hi][PM]  = Off[Hi].Output;
    Integral[Offst][VHi][PH] = Off[VHi].Output;
    /////////////////////////////////////////////////////////
    Derivative[Oscil][Non][NC] = Osc[Non].Output;
    Derivative[Oscil][Low][PL] = Osc[Low].Output;
    Derivative[Oscil][Mod][PM] = Osc[Mod].Output;
    Derivative[Oscil][Hi][PH]  = Osc[Hi].Output;
    Derivative[Oscil][VHi][PH] = Osc[VHi].Output;
    
    Derivative[Rspnse][Non][NC] = Resp[Non].Output;
    Derivative[Rspnse][Low][PL] = Resp[Low].Output;
    Derivative[Rspnse][Mod][PL] = Resp[Mod].Output;
    Derivative[Rspnse][Hi][PL]  = Resp[Hi].Output;
    Derivative[Rspnse][VHi][PH] = Resp[VHi].Output;
    
    Derivative[Offst][Non][NC] = 0;
    Derivative[Offst][Low][NC] = 0;
    Derivative[Offst][Mod][PL] = 0;
    Derivative[Offst][Hi][PM]  = 0;
    Derivative[Offst][VHi][PH] = 0;
    
    
    
    
    
    
    
    
    
    #ifdef Show_Output_Memb_Array    
     // actions*Num_Memb_Conditions*Num_Memb_Actions
    for(int act = 0; act < Num_Actions; act++){
        printf("%s \n", Actions_Name[act]);
    for(int con = 0; con < Num_Conditions; con++){
        printf("%s \n", Conditions_Name[con]);
        for(int memb_con = 0; memb_con < Num_Memb_Conditions; memb_con++){
            for(int memb_act = 0; memb_act < Num_Memb_Actions; memb_act++){
            
            
            printf("%d ",*(Actions_List[act] + con*Num_Memb_Conditions*Num_Memb_Actions+ memb_con*Num_Memb_Actions  + memb_act));
        }
        printf(" \n");
    }
     printf("\n");
    }
    }
#endif
    
    
    for(int act = 0; act < Num_Actions; act++){
    for(int member = 0; member < Num_Memb_Actions; member++ )
    {
        Fire_List[act][member] = Calculate_Max_Column_3D(Actions_List[act], Num_Actions, Num_Memb_Conditions, Num_Memb_Actions, member); // Saves all Proportional
        //Integral_Fire[member] = Calculate_Max_Column_3D(Integral, 0, 5, member, Third_Index); // Saves all Proportional
        //Derivative_Fire [member] = Calculate_Max_Column_3D(Derivative, 0, 5, member, Third_Index); // Saves all Proportional
        
    }
    }
    
    
        
#ifdef Show_Output_Memb    
  
    
        for(int act = 0; act < Num_Actions; act++)
    {
        printf("%s Membership functions \n", Actions_Name[act]);
        for(int member = 0; member < Num_Memb_Actions; member++){
            printf("%s Degree for %s: %d \n",  Actions_Name[act],Members_Actions[act][member].Name, Fire_List[act][member]);
      
        }
        printf("\n\n");
    }
    
#endif
    
    #ifdef Show_Single_Crisps
    printf("For Oscillation:%d\n", Input[0]*LoopRes);
    printf("For Response:%d \n", Input[1]*LoopRes);
    printf("For Offset:%d \n", Input[2]*LoopRes);
#endif
   
   
    // This section converts all the Output degree values 
    // to one Output. 
    // The method used in this code is the Center of Sums.
    // Here's the process...
    // 1. Using the Output values assigned from the last 
    //    section, clip the height of the respective 
    //    membership Output
    //    Example:
    //    The Output membership shape of Partial On/Off is a triangle 
    //    If the assigned value is between 0 or 255, after being clipped
    //    the shape will be a trapezoid
    // 2. After clipping calculate the area of each membership Output function
    // 3. Multiply each area with a weight 
    // 4. Take the sum off all products
    // 5. Divide the sum of products by the sum off all weights
    // 6. Obtain the Output
    // 
    for(int act = 0; act < Num_Actions; act++){
    defuzz_num = 0;   // Clear and reset the values for the
    defuzz_denom = 0; // numerator and denominator

    // In this for loop, a function is used to calculate the area of each 
    // membership function, the value of the Output is passed to clip
    // the shape
    for(int memb_act = 0; memb_act < Num_Memb_Actions; memb_act++)
    {
        Output_Centroid[memb_act] = Calculate_Centroid_int((Members_Actions[act] + memb_act), Fire_List[act][memb_act]);
        //printf("%d ", Output_Centroid[memb_act]);
    
    //printf("\n");
    
    // This for loop multiplies the area with the weight
    // and takes the sum of the product with the variable
    // defuzz_num
        defuzz_num += Output_Centroid[memb_act] * Weights[memb_act]; 
    
    // This for loop adds the Weight to the variable  
    // defuzz_denom
    // (In Hindsight this doesn't need to be recalculated
    // everytime)
        defuzz_denom += Output_Centroid[memb_act]; 
    }

#ifdef Show_Single_Crisps
    if(defuzz_denom == 0)
    printf("%s: %d / %d = %f\n", Actions_Name[act], defuzz_num, defuzz_denom, 0.00);
    else
        printf("%s: %d / %d = %f\n", Actions_Name[act], defuzz_num, defuzz_denom, (float)defuzz_num / defuzz_denom);
    
#endif
    
    
    
#ifdef DoALoop
    if(defuzz_denom == 0)
        Excel[act][indexx1][indexx2] = 0;
    else
        Excel[act][indexx1][indexx2] = (float) defuzz_num / defuzz_denom;
    
#endif
    }
           
            
#ifdef DoALoop
    indexx2++;
        }
        indexx1++;
}
#endif

#ifdef Show_Excel
for(int member = 0; member < LoopNum; member++){
        for(int member1 = 0; member1 < LoopNum; member1++){
     
            //printf("%d %d %d ", Parameter, member*LoopRes, member1*LoopRes);
            printf("%f ", Excel[Parameter][member][member1]);
        }
        printf(" \n");
    }
#endif
    
    
    
    
    
    
    
    
    return (EXIT_SUCCESS);
}

