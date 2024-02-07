


#include "Utils.h"
#include "DIO_interface.h"
#include "lcd.h"
#include "StdTypes.h"
#include "KeyPad_interface.h"

int main(){
	
	



  DIO_INIT();
	LCD_Init();
	KEYPAD_init();
	
c8 flag=0,flag1=0,flag2=0,flag3=0,flag4=0;
c8 key;
c8 op_key,op_key1;
s32 num1=0,num2=0,num3=0,result=0;

	while(1){
		
		key=KEYPAD_GetKey();
		if(key!=NO_KEY){
		
		if(key>='0'&&key<='9'){
			
			
			if(flag3==1){
				LCD_WriteChar(key);
				num3=num3*10+(key-'0');
				flag4=1;	
			}
			else{
			
			if(flag1==1){
				LCD_GoToClear(0,0,15);
				LCD_setCursor(0,0);
				num1=0;
				num2=0;
				flag1=0;
				flag4=0;
			}
			if(flag==1){
			LCD_WriteChar(key);
			num2=num2*10+(key-'0');
			
			}
				if(flag==0){
			LCD_WriteChar(key);
			num1=num1*10+(key-'0');
			flag2=0;
				}
			}
		}
		else if(key=='+'||key=='/'||key=='*'||key=='-'){
			
			if(flag2==1){
				LCD_GoToClear(0,0,15);
				LCD_setCursor(0,0);
				LCD_WriteNumber(result);
				LCD_WriteChar(key);
				op_key1=key;
				flag3=1;
				num3=0;
			}
			else{
			
			LCD_WriteChar(key);
			op_key=key;
			flag=1;
			}
		}
		else if (key=='=')
		{
			
			flag3=0;
			
			if(flag4==1){
				LCD_GoToClear(1,0,15);
				LCD_setCursor(1,0);
				
				switch(op_key1){
					case '+':
					result=result+num3;
					LCD_WriteNumber(result);
					break;
					case '-':
					result=result-num3;
					LCD_WriteNumber(result);
					break;
					case '*':
					result=result*num3;
					LCD_WriteNumber(result);
					break;
					case '/':
					if(result==0){
						LCD_WriteString("EROR!");
						break;
					}else{
					result=result/num3;
					LCD_WriteNumber(result);
					break;
					}
				}
				
			}
			else{
			LCD_GoToClear(1,0,15);
			LCD_setCursor(1,0);
			flag1=1;
			flag=0;
			flag2=1;
			result=0;
			switch(op_key){
				case '+':
				result=num1+num2;
				LCD_WriteNumber(result);
				break;
				case '-':
				result=num1-num2;
				LCD_WriteNumber(result);
				break;
				case '*':
				result=num1*num2;
				LCD_WriteNumber(result);
				break;
				case '/':
				if(num2==0){
					LCD_WriteString("EROR!");
					break;
				}else{
				result=num1/num2;
				LCD_WriteNumber(result);
				break;
				}
	}	
			}
			}
			else if(key=='c'){
				LCD_clear();
				LCD_WriteString("RESTATRING");
				_delay_ms(500);
				LCD_clear();
				LCD_setCursor(0,0);
				flag1=1;
				flag3=0;
				flag4=0;
				
				
			}
		}
		}
	}
			
	}