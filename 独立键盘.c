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
  
	while(1){
	   if(key_s2==0){
			 delay(20);
			 if(key_s2 == 0){
						 num++;
						 while(!key_s2);
				      beep=~beep;
				      delay(100);
				      beep=~beep;
		   }
		 }
		 if(key_s3==0){
			 delay(20);
			 if(key_s3 == 0){
						 if(num!=0)
							 num--;
						 while(!key_s3);
				      beep=~beep;
				      delay(100);
				      beep=~beep;
		   }
		 }
		 if(key_s4==0){
			 delay(20);
			 if(key_s4 == 0){
				      while(!key_s4);
				      beep=~beep;
		   }
		 }
		 display(num);
	}
	
}

