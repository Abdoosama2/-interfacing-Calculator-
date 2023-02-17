/*
 * lcd.h
 *
 * Created: 11/13/2022 5:19:59 PM
 *  Author: Abd ElRahman Osama
 */ 


#ifndef LCD_H_
#define LCD_H_

#define _4_BIT  1
#define  _8_BIT 2


/*****************lcd configration**********/
#define LCD_MODE _4_BIT

#define RS PINB0
#define EN PINB1

#define RS_4bit PINA1
#define EN_4bit PINA2
#define D4 PINA3
#define D5 PINA4
#define D6 PINA5
#define D7 PINA6

#define LCD_PORT PA



void LCD_Init(void);
void LCD_WriteNumber(s32 num);
void LCD_WriteString(c8*str);
void LCD_WriteChar(u8 ch);	
void LCD_clear(void);
void LCD_WriteBinary(s32 num);
void LCD_WriteHex(s32 num);
void LCD_setCursor(u8 line,u8 cell);
void LCD_WriteNumber_4D(u16 num);
void LCD_GoToClear(u8 line,u8 cell,u8 NumOfcell);
void LCD_createPattern(c8*pattern,u8 location);
void LCD_SetCursorString(u8 line ,u8 cell,c8*str);
	
	
	








#endif /* LCD_H_ */