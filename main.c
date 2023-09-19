//define, include
#include <PBL4vdk.h>

#define LCD_RS_PIN     	PIN_E0
#define LCD_RW_PIN     	PIN_E1
#define LCD_ENABLE_PIN 	PIN_E2
#define LCD_DATA4     		PIN_C0
#define LCD_DATA5      	PIN_C1
#define LCD_DATA6      	PIN_C2
#define LCD_DATA7      	PIN_C3
#include <lcd.c>

#use rs232(baud=9600, parity=N, xmit=PIN_C6, rcv=PIN_C7, bits=8)

char c;
int MALED[10]={0xC0, 0xF9, 0xA4, 0xB0,0x99, 0x92,0x82, 0xF8, 0x80,0x90};
int LED =0x01;
int16 angle=450;
float Nhietdo=0;
int a,b;
signed int8 i=0;

// Servo control program

void control_servo(int16 time){
output_high(PIN_A1);
delay_us(time);
output_low(PIN_A1);
delay_us(20000-time);
}

void dcservo(){     
 //quay thuan
 c = getch();
      if(c=='5'){
    
      while(angle  < 2450 ){
      
      control_servo(angle);
      delay_ms(100);
       angle = angle + 50 ;       } 
}
    //quay nghich
       if(c=='6'){
     
       while(angle > 450){
       control_servo(angle);
       delay_ms(100);
       angle = angle - 50;    }   
  } 
  }  
// Main program

void main(){

   set_tris_a(1);
   lcd_init();
   setup_ADC(ADC_clock_div_8);
   setup_ADC_ports(AN0);
   set_ADC_channel(0);
   delay_us(1000);

set_tris_b(0x00);
output_b(0x00); 
set_tris_d(0);
set_tris_c(0x80);


   while(TRUE)
   {
  if(kbhit()) 
  {  
   if(c == '0') output_b(0b00010101);
   else if(c == '1') 
   {
   for ( int j=0; j<6; j++)
   {
   output_B(LED);
   delay_ms(200);
   LED =LED <<1;
   }
   LED=0x01;
   }
   
   else if(c == '2') output_b(0);
   ///
   else if(c == '3')
   {
     i++;
     if(i>9)
     {
            i=0;
     }
     delay_ms(50);
     output_d(MALED [i]);
   }
   else if(c=='4')
   {
     i--;
     if(i<0)
     {
            i=9;
     }
     delay_ms(50);
     output_d(MALED [i]);
   }
  else if(c=='5') dcservo();
   else if(c=='6') dcservo();
  }
 Nhietdo = read_adc();
 Nhietdo = Nhietdo/2.046;
 a =(int)Nhietdo/10;
 b = (int)Nhietdo%10;
   lcd_gotoxy(1,1);
   lcd_putc("Nhiet do bay gio ");
   lcd_gotoxy(2,2);
   printf(lcd_putc, " T:%.2f do C", Nhietdo);
   delay_ms(300);
  
   //chuyen dl len visual
   putc(a+48);
   putc(b+48);
   }
}
