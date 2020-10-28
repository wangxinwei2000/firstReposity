#include<reg52.h>
#include<intrins.h>
sbit DU =P2^6;//段选
sbit WE =P2^7;//位选
sbit beep=P2^3;
sbit key_s2=P3^0; 
sbit key_s3=P3^1;
sbit key_s4=P3^2;
sbit key_s5=P3^3;
unsigned char num=0;
unsigned char keyValue=20;//按键值
unsigned code tabel[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
	0x77,0x7c,0x39,0x5e,0x79,0x71,0x76,0x38,
// A   B   C   D   E   F   H    L
  0x37,0x3e,0x40,0x00
//n    u     -   熄灭	
};//共阴极数码管0-9
unsigned char pwd[8],n=0;

void delay( unsigned int z){
    unsigned int x,y;
	  for(x=z;x>0;x--)
	      for(y=114;y>0;y--);

}

void keyScan(){
    P3 = 0xf0;//列扫描
	  delay(10);//软件消抖
	  if (P3!=0xf0){
			  switch(P3){
					case 0xe0: keyValue = 0; break;
					case 0xd0: keyValue = 1; break;
					case 0xb0: keyValue = 2; break;
					case 0x70: keyValue = 3; break;
					
				} 
				P3 = 0x0f;//行扫描
				 switch(P3){
					case 0x0e: keyValue = keyValue; break;
					case 0x0d: keyValue = keyValue+4; break;
					case 0x0b: keyValue = keyValue+8; break;
					case 0x07: keyValue = keyValue+12; break;
				}
        while(P3!=0x0f);//松手检测
        beep=~beep;
			  delay(100);
			  beep=~beep;	
        pwd[n++]=	keyValue;			
		}
		P3 = 0xff;
		if(P3!=0xff){
			delay(10);
			if(P3!=0xff){
			    switch(P3){
					case 0xfe: keyValue = 16; break;
					case 0xfd: keyValue = 17; break;
					case 0xfb: keyValue = 18; break;
					case 0xf7: keyValue = 19; break;
				}
        while(P3!=0xff);
			beep=~beep;
			delay(100);
			beep=~beep;				
			}
  		
		}
}
void display(unsigned int i){
	    unsigned number,decade,unit;
	    number = i/100;
	    decade = (i%100)/10;
	    unit =i%10;
	
      P0 = 0xff;//清除段码
      WE =1;//   打开锁存器
	    P0 =0xfe;// 
	    WE =0;//   关闭锁存器
		
	    DU =1;
	    P0 =tabel[number];// 
	    DU =0;//
		  delay(5);
		  //============================2
		  P0 = 0xff;//清除段码
		  WE =1;//   打开锁存器
	    P0 =0xfd;// 
	    WE =0;//   关闭锁存器
		
	    DU =1;
	    P0 =tabel[decade];// 
	    DU =0;//
		  delay(5);
		  //==========================3
		  P0 = 0xff;//清除段码
		  WE =1;//   打开锁存器
	    P0 =0xfb;// 
	    WE =0;//   关闭锁存器
		 
	    DU =1;
	    P0 =tabel[unit];// 
	    DU =0;//
		  delay(5);
		 
}
void main(){
	unsigned char Pwd[8]={0,1,2,3,4,5,6,7},i;
  WE = 1;
	P0 = 0xfe;
	WE = 0;
	 while(1){
		  if(n>8)
				break;
		  KeyScan();
	    DU = 1;
		  P0 = tabel[keyValue];
		  DU = 0;
	 }
	 for( i=0;i<8;i++){
	    if(pwd[i]!=Pwd[i]){
				  beep=~beep;
				  while(1);
			}
	 }
	 while(1){
		    delay(500);
	     beep=~beep;
		   delay(500);
		   beep=~beep;
	 }
}

