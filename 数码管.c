#include<reg52.h>
#include<intrins.h>
sbit DU =P2^6;//段选
sbit WE =P2^7;//位选
sbit beep=P2^3;
unsigned code tabel[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//共阴极数码管0-9

void delay( unsigned int z){
    unsigned int x,y;
	  for(x=z;x>0;x--)
	      for(y=114;y>0;y--);

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
  int i;
	unsigned char n=0,k=0;
	for(i=50;i>=0;i--){
		 n=0;
	   while(1){
			 display(i);
			 n++;
			 if(n>10){
				 beep=~beep;
				 break;
			 }
	  }
	}
	while(1){
	}
}

