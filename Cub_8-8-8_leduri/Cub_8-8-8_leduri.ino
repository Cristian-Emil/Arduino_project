// vizualizarea este aici: https://www.youtube.com/watch?v=xmScytz9y0M
//  www.keindarrak.com

/*
Cub din leduri 8x8x8
*/

// Aici avem parte de initializare

#include <SPI.h>  
// utilizam libraria SPY

#define latch_pin 2   
// definim pinii unde se conecteaza ledurile
#define blank_pin 4   
//
#define data_pin 11   
// utilizat de biblioteca SPI, trebuie sa fie pinul 11
#define clock_pin 13  
// utilizat de biblioteca SPI, trebuie sa fie pinul 13

// Se definesc variabilele de care avem nevoie mai tarziu
int shift_out; 
// pentru interatie de tip for(i=0, i<=8; i++)
byte anode[8]; 
// byte necesar la anod sa scriem depalsarea de la 0 la 8

// Scriem "stralucirea" fioecarui led si o stocam, avem o rerzolutie de 4 byte
byte red0[64], red1[64], red2[64], red3[64];
byte blue0[64], blue1[64], blue2[64], blue3[64];
byte green0[64], green1[64], green2[64], green3[64];

int level=0; 
// tine cont in ce nivel am stocat datele
int anodelevel=0; 
// acesta incrementeaza nivelul anodului
int BAM_Bit = 0, BAM_Counter = 0; 
//Bitul care mentine unghiul de modulare

// Variabilele se pot utiliza si pentru alte functii
unsigned long start;

void setup() {
SPI.setBitOrder(MSBFIRST); 
// Cel ami important BIT primul
SPI.setDataMode(SPI_MODE0); 
// Setam modulul 0 margine ascendentă a datelor
SPI.setClockDivider(SPI_CLOCK_DIV2); 
// rulam datele in 8 MHz = 16Mhz/2 

// serial.begin(115200); 
// daca avem nevoie de el , altfel se comenteaza
noInterrupts(); 
// opreste intreruperile pana in momentuil incare toate sunt configurate corect.

// Utilizam contorul de timp de 1 pana se reseteaza intreg cubul
TCCR1A = B00000000; // Inregistram A tooate cu zero
TCCR1B = B00001011; // bitul 3 il punem in modul CTC 
// bitii 0 si 1 sunt stati sa se divida cu 16Mhz si ceasul cu 64 => 16000Hz/64 = 250Hz  
TIMSK1 = B00000010; 
// bitul 1 cheama sa opreasca perechea 0CR1A
OCR1A = 30; 
// acesta se poate modifica dar e setat ca 30 , adica 1/250Hz = 4us; 
// deci e chemat la fiecare 124us si are frecventa 8kHz

// setam matricea anozilor 
anode[0]=B00000001;
anode[1]=B00000010;
anode[2]=B00000100;
anode[3]=B00001000;
anode[4]=B00010000;
anode[5]=B00100000;
anode[6]=B01000000;
anode[7]=B1000000;

// aici setam output-ul final
pinMode(latch_pin, OUTPUT); 
// Latch
pinMode(data_pin, OUTPUT); 
// MOSI DATA
pinMode(clock_pin, OUTPUT); 
// SPI Clock
pinMode(blank_pin, OUTPUT); 
// Output Enable 
SPI.begin(); 
// initializam libraria SPI
interrupts(); 
// cu aceasta incepe circuitul sa lucreze

// aici se incheie setarea cubului cu leduri 

}

void loop() {

  // int i, j, k

  // for (i = 0, i < 8, i++) 
  // for (j = 0, j < 8, j++) 
  // for (k = 0, k < 8, k++) 
  // LED(0, 0, 0, 15, 0, 0);  // red
  // delay(2000)

  // for (i = 0, i < 8, i++) 
  // for (j = 0, j < 8, j++) 
  // for (k = 0, k < 8, k++)
  // LED(0, 0, 0, 0, 15, 0);  // green
  // delay(2000)

  // for (i = 0, i < 8, i++) 
  // for (j = 0, j < 8, j++) 
  // for (k = 0, k < 8, k++)
  // LED(0, 0, 0, 0, 0, 15);  // blue
  // delay(2000)

  // for (i = 0, i < 8, i++) 
  // for (j = 0, j < 8, j++) 
  // for (k = 0, k < 8, k++)
  // LED(0, 0, 0, 15, 15, 0);
  // delay(2000)

  // for (i = 0, i < 8, i++) 
  // for (j = 0, j < 8, j++) 
  // for (k = 0, k < 8, k++)
  // LED(0, 0, 0, 15, 0, 15);
  // delay(2000)

  // for (i = 0, i < 8, i++) 
  // for (j = 0, j < 8, j++) 
  // for (k = 0, k < 8, k++)
  // LED(0, 0, 0, 0, 15, 15);
  // delay(2000)
}


void LED(int level, int row, int column, byte red, byte green , byte blue){
// verificam si scriem ca totul sa fie intre limite

  if(level<0) 
  level=0;
  if(level>7) 
  level=7;
  if(row<0)
  row=0;
  if(row>7)
  row=7;
  if(column<0)
  column=0;
  if(column>7)
  column=7;
  if(red<0)
  red=0;
  if(red>15)
  red=15;
  if(green<0)
  green=0;
  if(green>15)
  green=15;
  if(blue<0)
  blue=0;
  if(blue>15)
  blue=15;

int whichbyte = int(((level*64)+(row*8)+column)/8);

int wholebyte = (level*64)+(row*8)+column ;

bitWrite(red0[whichbyte],wholebyte-(8*whichbyte), bitRead(red,0));
bitWrite(red1[whichbyte],wholebyte-(8*whichbyte), bitRead(red,1));
bitWrite(red2[whichbyte],wholebyte-(8*whichbyte), bitRead(red,2));
bitWrite(red3[whichbyte],wholebyte-(8*whichbyte), bitRead(red,3));

bitWrite(green0[whichbyte],wholebyte-(8*whichbyte), bitRead(green,0));
bitWrite(green1[whichbyte],wholebyte-(8*whichbyte), bitRead(green,1));
bitWrite(green2[whichbyte],wholebyte-(8*whichbyte), bitRead(green,2));
bitWrite(green3[whichbyte],wholebyte-(8*whichbyte), bitRead(green,3));

bitWrite(blue0[whichbyte],wholebyte-(8*whichbyte), bitRead(blue,0));
bitWrite(blue1[whichbyte],wholebyte-(8*whichbyte), bitRead(blue,1));
bitWrite(blue2[whichbyte],wholebyte-(8*whichbyte), bitRead(blue,2));
bitWrite(blue3[whichbyte],wholebyte-(8*whichbyte), bitRead(blue,3));

}
// rutina modului de functionare a ledurilor se opreste aici

ISR(TIMER1_COMPA_vect){

  PORTD |= 1<<blank_pin;

if(BAM_Counter==8)
BAM_Bit++;
if(BAM_Counter==16)
BAM_Bit++;
if(BAM_Counter==32)
BAM_Bit++;

BAM_Counter++; 


switch (BAM_Bit){
case 0:
for(shift_out=level; shift_out<level+8; shift_out++ )
SPI.transfer(red0[shift_out]);
for(shift_out=level; shift_out<level+8; shift_out++ )
SPI.transfer(green0[shift_out]);
for(shift_out=level; shift_out<level+8; shift_out++ )
SPI.transfer(blue0[shift_out]);
  break;
case 1:
for(shift_out=level; shift_out<level+8; shift_out++ )
SPI.transfer(red1[shift_out]);
for(shift_out=level; shift_out<level+8; shift_out++ )
SPI.transfer(green1[shift_out]);
for(shift_out=level; shift_out<level+8; shift_out++ )
SPI.transfer(blue1[shift_out]);
  break;
case 2:
for(shift_out=level; shift_out<level+8; shift_out++ )
SPI.transfer(red2[shift_out]);
for(shift_out=level; shift_out<level+8; shift_out++ )
SPI.transfer(green2[shift_out]);
for(shift_out=level; shift_out<level+8; shift_out++ )
SPI.transfer(blue2[shift_out]);
break;
case 3:
for(shift_out=level; shift_out<level+8; shift_out++ )
SPI.transfer(red3[shift_out]);
for(shift_out=level; shift_out<level+8; shift_out++ )
SPI.transfer(green3[shift_out]);
for(shift_out=level; shift_out<level+8; shift_out++ )
SPI.transfer(blue3[shift_out]);
// in acest punct BAM_Counter se reseteaza la zero

  if (BAM_Counter==64){
    BAM_Counter=0;
    BAM_Bit=0;
  }
  break;
}
// aici se incheie bucla switch.

SPI.transfer(anode[anodelevel]);

PORTD |= 1<<latch_pin;
// acesta este pt latch_pin HIGH
PORTD &= 0<<latch_pin;
// acesta este pt latch_pin LOW
PORTD &= 0<<blank_pin;
// acesta este pt a intoarce blank si ledul la valoarea initiala

anodelevel++;
level = level + 8;
// se incrementeaza valoarea nivelului cu 8

if(anodelevel==8)
// acesta intoparce contorul la valoarea 0
anodelevel=0;
if(level==64)
level=0;
}
// aici se inchide codul complet

// aicic avem partea de animatie
void wipe_out(){
int xxx=0, yyy=0, zzz=0;
int fx=random(8), fy=random(8), fz=random(8), direct, fxo=1, fyo=1, fzo=1;
int ftx=random(8), fty=random(8), ftz=random(8), ftxo=1, ftyo=1, ftzo=1;
int select, rr, gg, bb, rrt, ggt, bbt;
for (xxx=0; xxx<8; xxx++){
for (yyy=0; yyy<8; yyy++){
for (zzz=0; zzz<8; zzz++){
LED(xxx, yyy, zzz, 0, 0, 0);
}}}

    select=random(3);
  if(select==0){
    rr=random(1,16);
    gg=random(1,16);    
    bb=0;
    }
  if(select==1){
    rr=random(1,16);
    gg=(0,0);    
    bb=random(1,16);
    }
  if(select==2){
    rr=(0,0);
    gg=random(1,16);    
    bb=random(1,16);
    }

   select=random(3);
  if(select==0){
    rrt=random(1,16);
    ggt=random(1,16);    
    bbt=0;
    }
  if(select==1){
    rrt=random(1,16);
    ggt=(0,0);    
    bbt=random(1,16);
    }
  if(select==2){
    rrt=(0,0);
    ggt=random(1,16);    
    bbt=random(1,16);
    }
    start= millis();

while(millis()-start<10000){
  LED(fxo, fyo,fzo, 0, 0, 0);
  LED(fxo, fyo, fzo+1, 0, 0, 0);
  LED(fxo, fyo, fzo-1, 0, 0, 0);
  LED(fxo+1, fyo,fzo, 0, 0, 0);
  LED(fxo-1, fyo,fzo, 0, 0, 0);
  LED(fxo, fyo+1,fzo, 0, 0, 0);
  LED(fxo, fyo-1,fzo, 0, 0, 0);

  LED(ftxo, ftyo,ftzo, 0, 0, 0);
  LED(ftxo, ftyo, ftzo+1, 0, 0, 0);
  LED(ftxo, ftyo, ftzo-1, 0, 0, 0);
  LED(ftxo+1, ftyo,ftzo, 0, 0, 0);
  LED(ftxo-1, ftyo,ftzo, 0, 0, 0);
  LED(ftxo, ftyo+1,ftzo, 0, 0, 0);
  LED(ftxo, ftyo-1,ftzo, 0, 0, 0);

  LED(fx, fy,fz, rrt, ggt, bbt);
  LED(fx, fy, fz+1, rrt, ggt, bbt);
  LED(fx, fy, fz-1, rrt, ggt, bbt);
  LED(fx+1, fy,fz, rrt, ggt, bbt);
  LED(fx-1, fy,fz, rrt, ggt, bbt);
  LED(fx, fy+1,fz, rrt, ggt, bbt);
  LED(fx, fy-1,fz, rrt, ggt, bbt);

  LED(ftxo, ftyo,ftzo, rr, gg, bb);
  LED(ftxo, ftyo, ftzo+1, 0, 0, 0);
  LED(ftxo, ftyo, ftzo-1, 0, 0, 0);
  LED(ftxo+1, ftyo,ftzo, 0, 0, 0);
  LED(ftxo-1, ftyo,ftzo, 0, 0, 0);
  LED(ftxo, ftyo+1,ftzo, 0, 0, 0);
  LED(ftxo, ftyo-1,ftzo, 0, 0, 0);

  delay(100);

fxo=fx;
fyo=fy;
fzo=fz;

}
}


