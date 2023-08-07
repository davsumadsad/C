/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FuzzyLogic.h
 * Author: Vidda
 *
 * Created on February 14, 2023, 4:27 PM
 */

#ifndef FUZZYLOGIC_H
#define FUZZYLOGIC_H




    struct Fuzzy_Member_Trapezoid_int
    {
        int Point_X[4];
        int Point_Y[4];
        
        int Slope[2];
        int Y_Intercept[2];
        
        char Name[20];
        
        int Output;
    };

    // ---------------------------------------------------------
    // ---------------------------------------------------------
    // First Brackets
    // The membership functions of the Condition Value Parameter
    // 0 - No value
    // 1 - Low value
    // 2 - Moderate value
    // 3 - High value
    // 4 - Very high value
    // ---------------------------------------------------------
    // ---------------------------------------------------------
    // Second Brackets
    // The membership functions of the Action Parameter
    // 0 - Negative High
    // 1 - Negative Medium
    // 2 - Negative Low
    // 3 - No Change
    // 4 - Positive Low
    // 5 - Positive Medium
    // 6 - Positive High
    // ---------------------------------------------------------
    // ---------------------------------------------------------
    // Third Brackets
    // The Response type
    // 0 - Oscillation
    // 1 - Response speed
    // ---------------------------------------------------------
    // ---------------------------------------------------------
    #define NH 0
    #define NM 1
    #define NL 2
    #define NC 3
    #define PL 4
    #define PM 5
    #define PH 6
    
    #define Non 0
    #define Low 1
    #define Mod 2
    #define Hi  3
    #define VHi 4
    
    #define Oscil  0
    #define Rspnse 1
    #define Offst  2
    
    
    #define Num_Actions    3
    #define Num_Memb_Actions    7

    #define Num_Conditions 3
    #define Num_Memb_Conditions 5
    
    extern struct Fuzzy_Member_Trapezoid_int Osc [Num_Memb_Conditions];
    extern struct Fuzzy_Member_Trapezoid_int Resp[Num_Memb_Conditions];
    extern struct Fuzzy_Member_Trapezoid_int Off [Num_Memb_Conditions];
    extern struct Fuzzy_Member_Trapezoid_int Proportional[Num_Memb_Actions]; 
    extern struct Fuzzy_Member_Trapezoid_int Integration [Num_Memb_Actions]; 
    
    extern struct Fuzzy_Member_Trapezoid_int * Members_Conditions[Num_Conditions];
    extern struct Fuzzy_Member_Trapezoid_int * Members_Actions   [Num_Actions];
    extern char Conditions_Name[Num_Conditions][30];
    extern char Actions_Name[Num_Actions][30];
    
    #define Third_Index 3 
    extern int Proportion [Num_Actions][Num_Memb_Conditions][Num_Memb_Actions] ;
    extern int Integral   [Num_Actions][Num_Memb_Conditions][Num_Memb_Actions] ;
    extern int Derivative [Num_Actions][Num_Memb_Conditions][Num_Memb_Actions] ;
    
    extern int * Actions_List[Num_Actions];
    
    extern int Proportional_Fire[Num_Memb_Actions];
    extern int Integral_Fire[Num_Memb_Actions];
    extern int Derivative_Fire[Num_Memb_Actions];
    extern int * Fire_List[Num_Actions];

    
    void Calculate_Trapezoid_Slope_int(struct Fuzzy_Member_Trapezoid_int * membr);
    int Calculate_Membership_int(struct Fuzzy_Member_Trapezoid_int * membr, int variable);
    void Calculate_Min(struct Fuzzy_Member_Trapezoid_int * membr1, struct Fuzzy_Member_Trapezoid_int * membr2, int Output[][5], int num_memb1, int num_memb2);
    int Calculate_Min_Column(int array[][5], int num_rows_strt, int num_rows_end, int col_num);
    int Calculate_Max_Column_3D(int *array, int num_height, int num_rows, int num_col ,int col_num);
    int Calculate_Min_Row(int array[][5], int num_col_strt, int num_col_end, int row_num);
    void Calculate_Max(struct Fuzzy_Member_Trapezoid_int * membr1, struct Fuzzy_Member_Trapezoid_int * membr2, int Output[][5], int num_memb1, int num_memb2);
    int Min_Array(int * fire, int num_strt, int num_end);
    int Max_Array(int * fire, int num_strt, int num_end);
    int Calculate_Centroid_int(struct Fuzzy_Member_Trapezoid_int * membr, int clip);
    

    




#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif /* FUZZYLOGIC_H */

