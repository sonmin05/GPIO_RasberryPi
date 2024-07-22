#include <stdio.h>  
#include <string.h>  
#include <wiringPi.h>
#include <wiringSerial.h>
#include <termio.h>
#include <softPwm.h>

#define GPIO0 0
#define GPIO3 3

#define ENA 1
#define IN1 4
#define IN2 5

#define ENB 0
#define IN3 2
#define IN4 3



#define MAX_Pwm_DUTY 100
#define baud_rate 115200
int getch(void) 
{
    int ch ;
    struct termios buf;
    struct termios save;
  
    tcgetattr(0, &save);
    buf = save;
    buf.c_lflag &= ~(ICANON|ECHO);
    buf.c_cc[VMIN]=1;
    buf.c_cc[VTIME]=0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0,TCSAFLUSH, &save);
    return ch;
     }

int main(void)
{ 
   
   int fd;
   int Pwm_a =0;
   unsigned char test,receive_char;
   
   if(wiringPiSetup() == -1)
   {
      printf("wiringPi setup error !\n");
      return -1;
   }
   
   
      
   pinMode(ENA,OUTPUT);
   pinMode(IN1,OUTPUT);
   pinMode(IN2,OUTPUT);
  
   pinMode(ENB,OUTPUT);
   pinMode(IN3,OUTPUT);
   pinMode(IN4,OUTPUT); 

   softPwmCreate(ENA,1,MAX_Pwm_DUTY);
   softPwmCreate(ENB,1,MAX_Pwm_DUTY);
   
   softPwmWrite(ENA, Pwm_a);
   softPwmWrite(ENB, 50);
   
   
   // printf("GPIO PIN3 : Low \n");
   //digitalWrite(GPIO3, LOW);
   //delay*(1000);
      test = 'B';
   
      
   while(1)
   {
      softPwmWrite(ENA, Pwm_a);
      Pwm_a +=1;
      if(Pwm_a >100) Pwm_a = 0;
      delay(500);
     
   }
   return 0;
}
