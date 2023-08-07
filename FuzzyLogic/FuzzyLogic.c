/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

    #include "FuzzyLogic.h"
    #include <stdio.h>


    
    #define Num_Memb_Oscillation    5
    #define Num_Memb_Response   5
    #define Num_Memb_Proportional   7
    
    int Proportion [Num_Actions][Num_Memb_Conditions][Num_Memb_Actions] ;
    int Integral [Num_Actions][Num_Memb_Conditions][Num_Memb_Actions] ;
    int Derivative [Num_Actions][Num_Memb_Conditions][Num_Memb_Actions] ;
    int * Actions_List[Num_Actions] = {&Proportion[0][0][0], &Integral[0][0][0], &Derivative[0][0][0]};
    
    
    int Proportional_Fire[7] = {0, 0, 0, 0, 0, 0, 0};
    int Integral_Fire    [7] = {0, 0, 0, 0, 0, 0, 0};
    int Derivative_Fire  [7] = {0, 0, 0, 0, 0, 0, 0};

    int * Fire_List [3] = {&Proportional_Fire[0], &Integral_Fire[0], &Derivative_Fire[0]};
    
    struct Fuzzy_Member_Trapezoid_int Osc[Num_Memb_Conditions] =
    {
        /////////////////////////////////////
        [0].Name = "None",
        [0].Point_X[0] = -500,
        [0].Point_X[1] = 0,
        [0].Point_X[2] = 0,
        [0].Point_X[3] = 500,
        
        [0].Point_Y[0] = 0,
        [0].Point_Y[1] = 1024,
        [0].Point_Y[2] = 1024,
        [0].Point_Y[3] = 0,
        /////////////////////////////////////
        [1].Name = "Low",
        [1].Point_X[0] = -400,
        [1].Point_X[1] = 100,
        [1].Point_X[2] = 100,
        [1].Point_X[3] = 600,
        
        [1].Point_Y[0] = 0,
        [1].Point_Y[1] = 1024,
        [1].Point_Y[2] = 1024,
        [1].Point_Y[3] = 0,
        /////////////////////////////////////
        [2].Name = "Moderate",
        [2].Point_X[0] = -300,
        [2].Point_X[1] = 200,
        [2].Point_X[2] = 200,
        [2].Point_X[3] = 700,
        
        [2].Point_Y[0] = 0,
        [2].Point_Y[1] = 1024,
        [2].Point_Y[2] = 1024,
        [2].Point_Y[3] = 0,
        /////////////////////////////////////
        [3].Name = "High",
        [3].Point_X[0] = -200,
        [3].Point_X[1] = 300,
        [3].Point_X[2] = 300,
        [3].Point_X[3] = 800,
        
        [3].Point_Y[0] = 0,
        [3].Point_Y[1] = 1024,
        [3].Point_Y[2] = 1024,
        [3].Point_Y[3] = 0,
        /////////////////////////////////////
        [4].Name = "Very High",
        [4].Point_X[0] = -100,
        [4].Point_X[1] = 400,
        [4].Point_X[2] = 800,
        [4].Point_X[3] = 900,
        
        [4].Point_Y[0] = 0,
        [4].Point_Y[1] = 1024,
        [4].Point_Y[2] = 1024,
        [4].Point_Y[3] = 0,
        /////////////////////////////////////
    };
    
  
    
    struct Fuzzy_Member_Trapezoid_int Resp[Num_Memb_Conditions] =
    {
        /////////////////////////////////////
        [0].Name = "None",
        [0].Point_X[0] = -500,
        [0].Point_X[1] = 0,
        [0].Point_X[2] = 0,
        [0].Point_X[3] = 500,
        
        [0].Point_Y[0] = 0,
        [0].Point_Y[1] = 1024,
        [0].Point_Y[2] = 1024,
        [0].Point_Y[3] = 0,
        /////////////////////////////////////
        [1].Name = "Low",
        [1].Point_X[0] = -400,
        [1].Point_X[1] = 100,
        [1].Point_X[2] = 100,
        [1].Point_X[3] = 600,
        
        [1].Point_Y[0] = 0,
        [1].Point_Y[1] = 1024,
        [1].Point_Y[2] = 1024,
        [1].Point_Y[3] = 0,
        /////////////////////////////////////
        [2].Name = "Moderate",
        [2].Point_X[0] = -300,
        [2].Point_X[1] = 200,
        [2].Point_X[2] = 200,
        [2].Point_X[3] = 700,
        
        [2].Point_Y[0] = 0,
        [2].Point_Y[1] = 1024,
        [2].Point_Y[2] = 1024,
        [2].Point_Y[3] = 0,
        /////////////////////////////////////
        [3].Name = "High",
        [3].Point_X[0] = -200,
        [3].Point_X[1] = 300,
        [3].Point_X[2] = 300,
        [3].Point_X[3] = 800,
        
        [3].Point_Y[0] = 0,
        [3].Point_Y[1] = 1024,
        [3].Point_Y[2] = 1024,
        [3].Point_Y[3] = 0,
        /////////////////////////////////////
        [4].Name = "Very High",
        [4].Point_X[0] = -100,
        [4].Point_X[1] = 400,
        [4].Point_X[2] = 800,
        [4].Point_X[3] = 900,
        
        [4].Point_Y[0] = 0,
        [4].Point_Y[1] = 1024,
        [4].Point_Y[2] = 1024,
        [4].Point_Y[3] = 0,
        /////////////////////////////////////
    };
  
    
    struct Fuzzy_Member_Trapezoid_int Off[Num_Memb_Conditions] =
    {
        /////////////////////////////////////
        [0].Name = "None",
        [0].Point_X[0] = -500,
        [0].Point_X[1] = 0,
        [0].Point_X[2] = 0,
        [0].Point_X[3] = 500,
        
        [0].Point_Y[0] = 0,
        [0].Point_Y[1] = 1024,
        [0].Point_Y[2] = 1024,
        [0].Point_Y[3] = 0,
        /////////////////////////////////////
        [1].Name = "Low",
        [1].Point_X[0] = -400,
        [1].Point_X[1] = 100,
        [1].Point_X[2] = 100,
        [1].Point_X[3] = 600,
        
        [1].Point_Y[0] = 0,
        [1].Point_Y[1] = 1024,
        [1].Point_Y[2] = 1024,
        [1].Point_Y[3] = 0,
        /////////////////////////////////////
        [2].Name = "Moderate",
        [2].Point_X[0] = -300,
        [2].Point_X[1] = 200,
        [2].Point_X[2] = 200,
        [2].Point_X[3] = 700,
        
        [2].Point_Y[0] = 0,
        [2].Point_Y[1] = 1024,
        [2].Point_Y[2] = 1024,
        [2].Point_Y[3] = 0,
        /////////////////////////////////////
        [3].Name = "High",
        [3].Point_X[0] = -200,
        [3].Point_X[1] = 300,
        [3].Point_X[2] = 300,
        [3].Point_X[3] = 800,
        
        [3].Point_Y[0] = 0,
        [3].Point_Y[1] = 1024,
        [3].Point_Y[2] = 1024,
        [3].Point_Y[3] = 0,
        /////////////////////////////////////
        [4].Name = "Very High",
        [4].Point_X[0] = -100,
        [4].Point_X[1] = 400,
        [4].Point_X[2] = 800,
        [4].Point_X[3] = 900,
        
        [4].Point_Y[0] = 0,
        [4].Point_Y[1] = 1024,
        [4].Point_Y[2] = 1024,
        [4].Point_Y[3] = 0,
        /////////////////////////////////////
    };
    
    
    struct Fuzzy_Member_Trapezoid_int Proportional[Num_Memb_Proportional] =
    {
        /////////////////////////////////////
        [0].Name = "Negative High",
        [0].Point_X[0] = -400,
        [0].Point_X[1] = -300,
        [0].Point_X[2] = -300,
        [0].Point_X[3] = 0,
        
        [0].Point_Y[0] = 0,
        [0].Point_Y[1] = 1024,
        [0].Point_Y[2] = 1024,
        [0].Point_Y[3] = 0,
        /////////////////////////////////////
        [1].Name = "Negative Medium",
        [1].Point_X[0] = -500,
        [1].Point_X[1] = -200,
        [1].Point_X[2] = -200,
        [1].Point_X[3] =  100,
        
        [1].Point_Y[0] = 0,
        [1].Point_Y[1] = 1024,
        [1].Point_Y[2] = 1024,
        [1].Point_Y[3] = 0,
        /////////////////////////////////////
        [2].Name = "Negative Small",
        [2].Point_X[0] = -400,
        [2].Point_X[1] = -100,
        [2].Point_X[2] = -100,
        [2].Point_X[3] =  200,
        
        [2].Point_Y[0] = 0,
        [2].Point_Y[1] = 1024,
        [2].Point_Y[2] = 1024,
        [2].Point_Y[3] = 0,
        /////////////////////////////////////
        [3].Name = "No Change",
        [3].Point_X[0] = -300,
        [3].Point_X[1] = 0,
        [3].Point_X[2] = 0,
        [3].Point_X[3] = 300,
        
        [3].Point_Y[0] = 0,
        [3].Point_Y[1] = 1024,
        [3].Point_Y[2] = 1024,
        [3].Point_Y[3] = 0,
        /////////////////////////////////////
        [4].Name = "Positive Small",
        [4].Point_X[0] = -200,
        [4].Point_X[1] = 100,
        [4].Point_X[2] = 100,
        [4].Point_X[3] = 400,
        
        [4].Point_Y[0] = 0,
        [4].Point_Y[1] = 1024,
        [4].Point_Y[2] = 1024,
        [4].Point_Y[3] = 0,
        /////////////////////////////////////
        [5].Name = "Positive Medium",
        [5].Point_X[0] = -100,
        [5].Point_X[1] = 200,
        [5].Point_X[2] = 200,
        [5].Point_X[3] = 500,
        
        [5].Point_Y[0] = 0,
        [5].Point_Y[1] = 1024,
        [5].Point_Y[2] = 1024,
        [5].Point_Y[3] = 0,
        /////////////////////////////////////
        [6].Name = "Positive High",
        [6].Point_X[0] = 0,
        [6].Point_X[1] = 300,
        [6].Point_X[2] = 300,
        [6].Point_X[3] = 400,
        
        [6].Point_Y[0] = 0,
        [6].Point_Y[1] = 1024,
        [6].Point_Y[2] = 1024,
        [6].Point_Y[3] = 0,
        /////////////////////////////////////
    };
    
    struct Fuzzy_Member_Trapezoid_int Integration[Num_Memb_Actions] =
    {
        /////////////////////////////////////
        [0].Name = "Negative High",
        [0].Point_X[0] = -400,
        [0].Point_X[1] = -300,
        [0].Point_X[2] = -300,
        [0].Point_X[3] = 0,
        
        [0].Point_Y[0] = 0,
        [0].Point_Y[1] = 1024,
        [0].Point_Y[2] = 1024,
        [0].Point_Y[3] = 0,
        /////////////////////////////////////
        [1].Name = "Negative Medium",
        [1].Point_X[0] = -500,
        [1].Point_X[1] = -200,
        [1].Point_X[2] = -200,
        [1].Point_X[3] =  100,
        
        [1].Point_Y[0] = 0,
        [1].Point_Y[1] = 1024,
        [1].Point_Y[2] = 1024,
        [1].Point_Y[3] = 0,
        /////////////////////////////////////
        [2].Name = "Negative Small",
        [2].Point_X[0] = -400,
        [2].Point_X[1] = -100,
        [2].Point_X[2] = -100,
        [2].Point_X[3] =  200,
        
        [2].Point_Y[0] = 0,
        [2].Point_Y[1] = 1024,
        [2].Point_Y[2] = 1024,
        [2].Point_Y[3] = 0,
        /////////////////////////////////////
        [3].Name = "No Change",
        [3].Point_X[0] = -300,
        [3].Point_X[1] = 0,
        [3].Point_X[2] = 0,
        [3].Point_X[3] = 300,
        
        [3].Point_Y[0] = 0,
        [3].Point_Y[1] = 1024,
        [3].Point_Y[2] = 1024,
        [3].Point_Y[3] = 0,
        /////////////////////////////////////
        [4].Name = "Positive Small",
        [4].Point_X[0] = -200,
        [4].Point_X[1] = 100,
        [4].Point_X[2] = 100,
        [4].Point_X[3] = 400,
        
        [4].Point_Y[0] = 0,
        [4].Point_Y[1] = 1024,
        [4].Point_Y[2] = 1024,
        [4].Point_Y[3] = 0,
        /////////////////////////////////////
        [5].Name = "Positive Medium",
        [5].Point_X[0] = -100,
        [5].Point_X[1] = 200,
        [5].Point_X[2] = 200,
        [5].Point_X[3] = 500,
        
        [5].Point_Y[0] = 0,
        [5].Point_Y[1] = 1024,
        [5].Point_Y[2] = 1024,
        [5].Point_Y[3] = 0,
        /////////////////////////////////////
        [6].Name = "Positive High",
        [6].Point_X[0] = 0,
        [6].Point_X[1] = 300,
        [6].Point_X[2] = 300,
        [6].Point_X[3] = 400,
        
        [6].Point_Y[0] = 0,
        [6].Point_Y[1] = 1024,
        [6].Point_Y[2] = 1024,
        [6].Point_Y[3] = 0,
        /////////////////////////////////////
    };
    
    struct Fuzzy_Member_Trapezoid_int Derivation[Num_Memb_Actions] =
    {
        /////////////////////////////////////
        [0].Name = "Negative High",
        [0].Point_X[0] = -400,
        [0].Point_X[1] = -300,
        [0].Point_X[2] = -300,
        [0].Point_X[3] = 0,
        
        [0].Point_Y[0] = 0,
        [0].Point_Y[1] = 1024,
        [0].Point_Y[2] = 1024,
        [0].Point_Y[3] = 0,
        /////////////////////////////////////
        [1].Name = "Negative Medium",
        [1].Point_X[0] = -500,
        [1].Point_X[1] = -200,
        [1].Point_X[2] = -200,
        [1].Point_X[3] =  100,
        
        [1].Point_Y[0] = 0,
        [1].Point_Y[1] = 1024,
        [1].Point_Y[2] = 1024,
        [1].Point_Y[3] = 0,
        /////////////////////////////////////
        [2].Name = "Negative Small",
        [2].Point_X[0] = -400,
        [2].Point_X[1] = -100,
        [2].Point_X[2] = -100,
        [2].Point_X[3] =  200,
        
        [2].Point_Y[0] = 0,
        [2].Point_Y[1] = 1024,
        [2].Point_Y[2] = 1024,
        [2].Point_Y[3] = 0,
        /////////////////////////////////////
        [3].Name = "No Change",
        [3].Point_X[0] = -300,
        [3].Point_X[1] = 0,
        [3].Point_X[2] = 0,
        [3].Point_X[3] = 300,
        
        [3].Point_Y[0] = 0,
        [3].Point_Y[1] = 1024,
        [3].Point_Y[2] = 1024,
        [3].Point_Y[3] = 0,
        /////////////////////////////////////
        [4].Name = "Positive Small",
        [4].Point_X[0] = -200,
        [4].Point_X[1] = 100,
        [4].Point_X[2] = 100,
        [4].Point_X[3] = 400,
        
        [4].Point_Y[0] = 0,
        [4].Point_Y[1] = 1024,
        [4].Point_Y[2] = 1024,
        [4].Point_Y[3] = 0,
        /////////////////////////////////////
        [5].Name = "Positive Medium",
        [5].Point_X[0] = -100,
        [5].Point_X[1] = 200,
        [5].Point_X[2] = 200,
        [5].Point_X[3] = 500,
        
        [5].Point_Y[0] = 0,
        [5].Point_Y[1] = 1024,
        [5].Point_Y[2] = 1024,
        [5].Point_Y[3] = 0,
        /////////////////////////////////////
        [6].Name = "Positive High",
        [6].Point_X[0] = 0,
        [6].Point_X[1] = 300,
        [6].Point_X[2] = 300,
        [6].Point_X[3] = 400,
        
        [6].Point_Y[0] = 0,
        [6].Point_Y[1] = 1024,
        [6].Point_Y[2] = 1024,
        [6].Point_Y[3] = 0,
        /////////////////////////////////////
    };

    struct Fuzzy_Member_Trapezoid_int * Members_Conditions[Num_Conditions] = {&Osc[0], &Resp[0], &Off[0]};
    struct Fuzzy_Member_Trapezoid_int * Members_Actions   [Num_Actions] = {&Proportional[0] ,&Integration[0], &Derivation[0]};

    char Conditions_Name[Num_Conditions][30] = { "Oscillation",
                                    "Response",
                                    "Offset"};
    char Actions_Name[Num_Actions][30] = { "Proportional",
                                    "Integral",
                                    "Derivative"};
    
    

    void Calculate_Trapezoid_Slope_int(struct Fuzzy_Member_Trapezoid_int * membr)
    {
        for(int equation = 0; equation < 2; equation++)
        {
        membr->Slope[equation] = (membr->Point_Y[equation*2+1] - membr->Point_Y[equation*2])/(membr->Point_X[equation*2+1] - membr->Point_X[equation*2]);
            
        membr->Y_Intercept[equation] = membr->Point_Y[equation*2 + 1] -(membr->Point_X[equation*2+1] * membr->Slope[equation]); 
        }
    }

    
    int Calculate_Membership_int(struct Fuzzy_Member_Trapezoid_int * membr, int variable)
    {
        if(variable < membr->Point_X[0])
            return 0;
        else if(variable > membr->Point_X[3])
            return 0;
        else if(variable <= membr->Point_X[1])
            return membr->Slope[0] * variable + membr->Y_Intercept[0];
        else if(variable < membr->Point_X[2])
            return membr->Point_Y[2];
        else if(variable <= membr->Point_X[3])
            return membr->Slope[1] * variable + membr->Y_Intercept[1];
    }
    
    // Since this function is using a 2D array, make the sure the number of elements 
    // of the second bracket is the same as the one that is used
    // 
    void Calculate_Min(struct Fuzzy_Member_Trapezoid_int * membr1, struct Fuzzy_Member_Trapezoid_int * membr2, int Output[][5], int num_memb1, int num_memb2)
    {
        
        
        for(int member1 = 0; member1 < num_memb1; member1++){
            
            for(int member2 = 0; member2 < num_memb2; member2++){
            
                //printf("%d  %d  %d  %d ", member1, member2, membr1[member1].Output, membr2[member2].Output);
            
                if(membr1[member1].Output < membr2[member2].Output){
                    Output[member1][member2] = membr1[member1].Output;
                }
                else{
                   Output[member1][member2] = membr2[member2].Output;
                }
            
               // printf("%d  %d  ", member1, member2);
            //    printf("%d ",Output[member1][member2]);
            //    printf("\n");
            }
        }
    }
    
    int Calculate_Min_Column(int array[][5], int num_rows_strt, int num_rows_end, int col_num)
    {
        int comp = array[num_rows_strt][col_num];
        for(int index = num_rows_strt; index < num_rows_end; index++){
            
            if(comp < array[index][col_num])
                comp = array[index][col_num];
            else;
            
        }
        return comp;
    }
    
    int Calculate_Max_Column_3D(int *array, int num_height, int num_rows, int num_col ,int col_num)
    {
        int comp[50]; 
        int Offset = num_rows*num_col;
        
        for(int indx_height = 0; indx_height < num_height; indx_height++){
        
        
            comp[indx_height] = *(array + indx_height*Offset + col_num);
            for(int index_rows = 0; index_rows < num_rows - 1; index_rows++){
            
            //printf("%d %d %d: %d \n", indx_height, index_rows, col_num, *(array + indx_height*Offset + (index_rows)*num_col + col_num));
            
            if(comp[indx_height] < *(array + indx_height*Offset + (index_rows+1)*num_col + col_num))
                comp[indx_height] = *(array + indx_height*Offset + (index_rows+1)*num_col + col_num);
            else;
        
            }
        }
        
        return Max_Array(&comp[0], 0 , num_height);
    }
    
    int Calculate_Min_Row(int array[][5], int num_col_strt, int num_col_end, int row_num)
    {
        int comp = array[row_num][num_col_strt];
        for(int index = num_col_strt; index < num_col_end; index++){
            
            if(comp < array[row_num][index])
                comp = array[row_num][index];
            else;
            
        }
        return comp;
    }
    
void Calculate_Max(struct Fuzzy_Member_Trapezoid_int * membr1, struct Fuzzy_Member_Trapezoid_int * membr2, int Output[][5], int num_memb1, int num_memb2)
    {
      
        
        for(int member1 = 0; member1 < num_memb1; member1++){
            
            for(int member2 = 0; member2 < num_memb2; member2++){
            
                if(membr1[member1].Output > membr2[member2].Output)
                    Output[member1][member2] = membr1[member1].Output;
                else
                   Output[member1][member2] = membr2[member2].Output;
            
               
            }
        }
    }
    
    
int Min_Array(int * fire, int num_strt, int num_end)
    {
      
        int comp = fire[num_strt];
        for(int index = num_strt; index < num_end - 1; index++){
            
            if(comp > fire[index + 1])
                comp = fire[index + 1];
            else;
                
        }   
        return comp;
    }    
    
int Max_Array(int * fire, int num_strt, int num_end)
    {
      
        int comp = fire[num_strt];
        for(int index = num_strt; index < num_end - 1; index++){
            
            if(comp < fire[index + 1])
                comp = fire[index + 1];
            else;
                
        }   
        return comp;
    }    
    
    int Calculate_Centroid_int(struct Fuzzy_Member_Trapezoid_int * membr, int clip)
    {
        int area = 0;
        
        area += (membr->Point_X[1] - membr->Point_X[0]) * clip / 2;
        
        area += (membr->Point_X[2] - membr->Point_X[1]) * clip;
        
        area += (membr->Point_X[3] - membr->Point_X[2]) * clip / 2;
        
        return area;
    }