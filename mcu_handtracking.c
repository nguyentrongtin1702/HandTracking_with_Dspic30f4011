#include <30F4011.h>
#include <stdlib.h>
#include <math.h>
#fuses nowdt,put4,hs,noprotect
#use delay(clock = 20000000)
#use rs232 (UART1,baud = 9600)
CONST UNSIGNED CHAR MA7DOAN[10]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90};

unsigned int8 rma;
unsigned int8 ma_ch, ma_dv;
int1 tt_nhan = 0;
unsigned int8 rdata = 0;

#int_rda
void interrupt_uart2()
{
   if(kbhit() == 1)
   {
      rma  = getch();
      tt_nhan = 1;
   }
}

void giai_ma(unsigned int8 data)
{
   
   ma_dv = ma7doan[data%10];
   ma_ch = ma7doan[data/10%10];
   if(ma_ch == 0xc0)
   {
      ma_ch = 0xff;
   }
}

void hien_thi()
{
   output_b(ma_dv);
   output_low(pin_e1);
   delay_ms(5);
   output_high(pin_e1);
   
   output_b(ma_ch);
   output_low(pin_e0);
   delay_ms(5);
   output_high(pin_e0);
}

void nhan_du_lieu()
{
   if(tt_nhan == 1)
   {
      switch(rma)
      {
         case 0x30: 
         rdata = 0;
         break;
         
         case 0x31:
         rdata = 1;
         break;
         
         case 0x32:
         rdata = 2;
         break;
         
         case 0x33:
         rdata = 3;
         break;
         
         case 0x34:
         rdata = 4;
         break;
         
         case 0x35:
         rdata = 5;
         break;
         
         default:
         break;
      }
   }
   tt_nhan = 0;
}

void main()
{
   set_tris_e(0x00);
   set_tris_b(0x00);
   set_tris_d(0xff);
   
   enable_interrupts(global);
   enable_interrupts(int_rda);
   
   output_high(pin_e2);
   output_high(pin_e3);
   

   
   
   while(true)
   {
      nhan_du_lieu();
      giai_ma(rdata);
      hien_thi();
   }
   
}

