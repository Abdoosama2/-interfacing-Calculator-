/*
 * KeyPad.c
 *
 * Created: 12/4/2022 11:04:39 AM
 *  Author: Abd ElRahman Osama
 */ 
#define KEYPAD_PROG
#include "DIO_interface.h"
#include "StdTypes.h"
#include "KeyPad_interface.h"
#include "KeyPad_cfg.h"


void KEYPAD_init(void){
	//the output pins
	DIO_Writepin(First_output,HIGH);
	DIO_Writepin(First_output+1,HIGH);
   DIO_Writepin(First_output+2,HIGH);
    DIO_Writepin(First_output+3,HIGH);	
	
}
u8 KEYPAD_GetKey(void){
	u8 key=NO_KEY,r,c;
	
	for(r=0;r<ROWS;r++){
		DIO_Writepin(First_output+r,LOW);
		for(c=0;c<COLMS;c++){
			if(!DIO_ReadPin(first_input+c)){
				key=KEYPAD_Array[r][c];
				while(DIO_ReadPin(first_input+c)==LOW);
			}
		}
		DIO_Writepin(First_output+r,HIGH);
	}
	return key;
	
}