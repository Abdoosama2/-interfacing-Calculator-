/*
 * LCD.c
 *
 * Created: 11/13/2022 5:20:09 PM
 *  Author: Abd ElRahman Osama
 */ 
#include "StdTypes.h"
#include "Utils.h"
#include "DIO_interface.h"
#include "lcd.h"
#define F_CPU 8000000
#include <util/delay.h>

#if LCD_MODE==_8_BIT

static void WriteIns(u8 ins)
{
	
	DIO_Writepin(RS,LOW);
	DIO_Write_PORT(LCD_PORT,ins);
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
}



static void WriteData(u8 data)
{
	
	DIO_Writepin(RS,HIGH);
	DIO_Write_PORT(LCD_PORT,data);
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
}
void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0X38);
	WriteIns(0X0c);//0x0e,0x0f cursor
	WriteIns(0X01);//clear screen
	_delay_ms(1);
	WriteIns(0X06);
	
	
}

#elif LCD_MODE==_4_BIT

static void WriteData(u8 data)
{
	
	DIO_Writepin(RS_4bit,HIGH);
	DIO_Writepin(D7,READ_BIT(data,7));
	DIO_Writepin(D6,READ_BIT(data,6));
	DIO_Writepin(D5,READ_BIT(data,5));
	DIO_Writepin(D4,READ_BIT(data,4));
	DIO_Writepin(EN_4bit,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN_4bit,LOW);
	_delay_ms(1);
	DIO_Writepin(D7,READ_BIT(data,3));
	DIO_Writepin(D6,READ_BIT(data,2));
	DIO_Writepin(D5,READ_BIT(data,1));
	DIO_Writepin(D4,READ_BIT(data,0));
	DIO_Writepin(EN_4bit,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN_4bit,LOW);
	_delay_ms(1);
}
static void WriteIns(u8 ins)
{
	
	DIO_Writepin(RS_4bit,LOW);
	DIO_Writepin(D7,READ_BIT(ins,7));
	DIO_Writepin(D6,READ_BIT(ins,6));
	DIO_Writepin(D5,READ_BIT(ins,5));
	DIO_Writepin(D4,READ_BIT(ins,4));
	DIO_Writepin(EN_4bit,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN_4bit,LOW);
	_delay_ms(1);
	
	DIO_Writepin(D7,READ_BIT(ins,3));
	DIO_Writepin(D6,READ_BIT(ins,2));
	DIO_Writepin(D5,READ_BIT(ins,1));
	DIO_Writepin(D4,READ_BIT(ins,0));
	DIO_Writepin(EN_4bit,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN_4bit,LOW);
	_delay_ms(1);
}
void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0X02);
	WriteIns(0X28);
	WriteIns(0X0c);//0x0e,0x0f cursor
	WriteIns(0X01);//clear screen
	_delay_ms(1);
	WriteIns(0X06);
	
	
}
#endif


void LCD_clear(void){
	
	WriteIns(0X01);//clear screen
	_delay_ms(1);
}


void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
	
	
}
void LCD_WriteString(c8*str)
{
	
	for(u8 i=0; str[i]; i++){
		
		LCD_WriteChar(str[i]);
	}
	
}

void LCD_WriteNumber(s32 num){
	
	u8 i=0;
	u8 str[16];
	s8 j=0;
	if(num==0){
		LCD_WriteChar('0');
	}
	if(num<0){
		LCD_WriteChar('-');
		num=num*-1;
	}
	while(num){
		
		str[i]=num%10+'0';
		i++;
		num=num/10;
	}
	for(j=i-1; j>=0; j--){
		LCD_WriteChar(str[j]);
	}
	
	
}

void LCD_WriteBinary(s32 num){
	 
	u32 bin=0,digit=1; 
	c8 rem;
	while(num){
		rem=num%2;
		num=num/2;
		bin=bin+(rem*digit);
		digit=digit*10;
	
	} 
	LCD_WriteNumber(bin);
	
}

void LCD_WriteHex(s32 num){
	
	c8 hex[16];
	u8 i=0;
	u8 rem;
	while(num){
		
		rem=num%16;
		
		if(rem>=10 &&rem<=15){
		switch(rem){
			case 10:
			hex[i]='A';
			break;
			case 11:
				hex[i]='B';
			break;
			case 12:
				hex[i]='C';
			break;
			case 13:
				hex[i]='D';
			break;
			case 14:
				hex[i]='E';
			break;
			case 15:
				hex[i]='F';
			break;
			
		}	
		}
		else{
			hex[i]=rem+'0';
		}
		num=num/16;
		i++;
	}
	for(s8 j=i-1;j>=0;j--){
		LCD_WriteChar(hex[j]);
	}
	
	
}

void LCD_setCursor(u8 line,u8 cell){
	
	if(line==0){
		
	WriteIns(0x80|cell);
	
	}
	else if(line==1){
		WriteIns(0xC0|cell);
		
	}
	
	
}

void LCD_WriteNumber_4D(u16 num){
	
	
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
		

	
}
void LCD_GoToClear(u8 line,u8 cell,u8 NumOfcell){
	
	u8 i;
	LCD_setCursor(line ,cell);
	for(i=0; i<NumOfcell; i++){
		LCD_WriteChar(' ');
	}
}
void LCD_createPattern(c8*pattern,u8 location){
	
	WriteIns(0x40+(location*8));
	for(u8 i=0; i<8; i++){
		
	WriteData(pattern[i]);	
	}
	WriteIns(0x80);
	
	
}

void LCD_SetCursorString(u8 line ,u8 cell,c8*str){
LCD_setCursor(line,cell);
LCD_WriteString(str);	
	
}