#include<stdio.h>
/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
**********************************************************
Mapping Relationship

Right Eyebrow Inner ---- S1 ---- Right_Eyebrow_WriteCompare1
Right Eyebrow Outer ---- S3 ---- Right_Eyebrow_WriteCompare2
Left Eyebrow Inner ----- S2 ---- Left_Eyebrow_WriteCompare1
Left Eyebrow Outer ----- S4 ---- Left_Eyebrow_WriteCompare2
Right Eyeball H(inner)-- S5 ---- EyeballVertical_WriteCompare1
Right Eyeball V(outer)-- S7 ---- EyeballVertical_WriteCompare1
Left Eyeball H(inner) -- S6 ---- EyeballVertical_WriteCompare2
Left Eyeball V(outer) -- S8 ---- EyeballVertical_WriteCompare2
Eyelid V    ------------ S9 ---- Eyelid_WriteCompare1
Eyelid Open/Close ------ S10 --- Eyelid_WriteCompare2 
Jaw -------------------- S11 --- BaseAndJaw_WriteCompare1
Right Lip -------------- S12 --- Lips_WriteCompare1
Left Lip --------------- S13 --- Lips_WriteCompare2
Right Neck ------------- S14 --- Neck_WriteCompare1
Left Neck -------------- S15 --- Neck_WriteCompare2
Base ------------------- S16 --- BaseAndJaw_WriteCompare2

**********************************************************/

#include "project.h"
void left_eyebrow_lift(){
     Left_Eyebrow_WriteCompare1(5000); // Inner 
     Left_Eyebrow_WriteCompare2(3000);  // Outer
}
void right_eyebrow_lift(){
     Right_Eyebrow_WriteCompare1(3000);  // Inner 
     Right_Eyebrow_WriteCompare2(5000);   // Outer
}
void left_eyebrow_down(){
     Left_Eyebrow_WriteCompare1(3000);
     Left_Eyebrow_WriteCompare2(5000);
}
void right_eyebrow_down(){
     Right_Eyebrow_WriteCompare1(5000);
     Right_Eyebrow_WriteCompare2(3000);
}
void reset_left(){
     Left_Eyebrow_WriteCompare1(2000);
     Left_Eyebrow_WriteCompare2(2000);
}
void reset_right(){
     Right_Eyebrow_WriteCompare1(2000);
     Right_Eyebrow_WriteCompare2(2000);
}

void eyebrow_init(){
    
       /* Right_Eyebrow_WriteCompare1(4000);
        Right_Eyebrow_WriteCompare2(4000);
        
        Left_Eyebrow_WriteCompare1(4000);
        Left_Eyebrow_WriteCompare2(4000);
        
        BaseAndJaw_WriteCompare2(4000);
        
        Eyelid_WriteCompare2(4000);
        
        Lips_WriteCompare1(4000);
        Lips_WriteCompare2(4000);*/
        
       // Neck_WriteCompare1(4000);
        //Neck_WriteCompare2(4000);
        BaseAndJaw_WriteCompare1(4000);
}
void jawopen(){
    BaseAndJaw_Start();
    for(int i=0;i<2;i++)
    {
        
        BaseAndJaw_WriteCompare2(1500);
        CyDelay(2000);
        BaseAndJaw_WriteCompare2(2200);
        CyDelay(2000);
    }
    
    eyebrow_init();
}
void baseturn(){
    BaseAndJaw_Start();
    for(int i=0;i<5;i++)
    {
        BaseAndJaw_WriteCompare1(1500);
        
        CyDelay(1000);
        BaseAndJaw_WriteCompare1(3000);
        CyDelay(1000);
    }
    
    eyebrow_init();
}
void nod(){
    Neck_Start();
    for(int i=0;i<1;i++)
    {
        
        
        Neck_WriteCompare1(2500);
        Neck_WriteCompare2(2500);
        CyDelay(1000);
        Neck_WriteCompare1(2550);
        Neck_WriteCompare2(2550);
        CyDelay(1000);
    }
    
    eyebrow_init();
}
void lipmovement(){
    Lips_Start();
    eyebrow_init();
    for(int i=0;i<5;i++)
    {
        Lips_WriteCompare1(3500);
        Lips_WriteCompare2(5500);
        CyDelay(1000);
        Lips_WriteCompare1(5500);
        Lips_WriteCompare2(3500);
        CyDelay(1000);
    }
}
void eyelid_openclose(){
    eyebrow_init();
for(int i=0;i<10;i++)
    {
        BaseAndJaw_WriteCompare1(1500);
        Eyelid_WriteCompare2(3700);
        CyDelay(1000);
        Eyelid_WriteCompare2(4300);
        CyDelay(1000);
    }
    eyebrow_init();
}

void eyemovement(){
    
    Left_Eyeball_Start();
    Right_Eyeball_Start();
    
    Left_Eyeball_WriteCompare1(4000);
    Right_Eyeball_WriteCompare1(4000);
    
    Left_Eyeball_WriteCompare2(4000);
    Right_Eyeball_WriteCompare2(4000);
    
    for(int i=0;i<3;i++)
    {
       // BaseAndJaw_WriteCompare1(1500);
        Left_Eyeball_WriteCompare1(3000); // Inner 
        Left_Eyeball_WriteCompare2(5000);  // Outer
        CyDelay(1000);
        
        Left_Eyeball_WriteCompare1(5000); // Inner 
        Left_Eyeball_WriteCompare2(3000);
       // Right_Eyeball_WriteCompare1(5000); // Inner 
       // Right_Eyeball_WriteCompare2(3000);  // Outer
        CyDelay(1000);
    }
    Left_Eyeball_WriteCompare1(4000);
    Right_Eyeball_WriteCompare1(4000);
    Left_Eyeball_WriteCompare2(4000);
    Right_Eyeball_WriteCompare2(4000);
}
int main(void)
{
    

    
     Right_Eyebrow_Start();
    eyebrow_init();
   /* Left_Eyebrow_Start();
    eyebrow_init();
      CyDelay(1000);
    for(int i=0;i<3;i++)
    {  
        
      right_eyebrow_lift();
      left_eyebrow_lift();
      CyDelay(1000);
      //  reset_right();
      //  reset_left();
       // CyDelay(1000);
       right_eyebrow_down();
        left_eyebrow_down();
         CyDelay(2000);
    }*/
   // CyDelay(15000);
    
    eyebrow_init();
    //Eyelid_Start();
    //eyemovement();
    //lipmovement();
    
   /* for(int i=0;i<5;i++)
    {
       // BaseAndJaw_WriteCompare1(1500);
        Eyelid_WriteCompare2(3950);
        CyDelay(1000);
        Eyelid_WriteCompare2(4050);
        CyDelay(1000);
    }*/
   // nod();
    //eyelid_openclose();
     //jawopen();
    baseturn();
    eyebrow_init();
}


/* [] END OF FILE */
