/*
 * KeyPad_cfg.h
 *
 * Created: 12/4/2022 11:05:09 AM
 *  Author: Abd ElRahman Osama
 */ 


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_



#define  First_output PINB4
#define first_input PIND2

#define NO_KEY 'q'  
 
#define ROWS 4
#define COLMS 4
 

static const u8 KEYPAD_Array[ROWS][COLMS]={
	{'7','8','9','A'},
	{'4','5','6','B'},
	{'1','2','3','C'},
	{'c','0','=','D'},
	};
	
	









#endif /* KEYPAD_CFG_H_ */