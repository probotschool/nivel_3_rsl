int PWMpinI=11;  
int PWMpinD=6;  
int MI1=13;      
int MI2=12;     
int MD1=10;      
int MD2=9;      
int SI3=A0;
int SI2=A1;
int SI1=A2;
int SD1=A3;
int SD2=A4;
int SD3=A5;
int interrup = 5;
int c=5;
int CANT_LEC = 6;
int CENTRO = 2500;
float last_proportional;
float proportional;
float derivative;
float KP = 0.17;  //0.18
float KD = 0.7;  //1.56
int maxVel = 0;

int last_prop;

void setup(){
  pinMode(SD3,INPUT);
  pinMode(SD1,INPUT);
  pinMode(SD2,INPUT);
  pinMode(SI1,INPUT);
  pinMode(SI2,INPUT);
  pinMode(SI3,INPUT);
  pinMode(PWMpinI,OUTPUT); //PWM Pin 1
  pinMode(PWMpinD,OUTPUT); //PWM Pin 2
  pinMode(MI1,OUTPUT); //Left Motor Pin 1
  pinMode(MI2,OUTPUT); //Left Motor Pin 2
  pinMode(MD1,OUTPUT); //Right Motor Pin 1
  pinMode(MD2,OUTPUT);  //Right Motor Pin 2
  attachInterrupt(0,interrupcion,FALLING);    //INT 0= pin 2
  Serial.begin(9600);

}
void loop(){
  c=interrup;
  //Serial.println(c);
  if(c==0){
    maxVel = 110;
  }
  if(c==1){
    maxVel = 110;
  }
  if(c>1){
    interrup=0;
    c=0;
  }
  //  Serial.println(maxVel);
  //delay(1000);
   proportional = readLine();
   Serial.println(proportional);
   //delay(1000);
   derivative = proportional - last_proportional;
   last_proportional = proportional;

   int power_difference = ( proportional * KP ) + ( derivative * KD );

   if ( power_difference > maxVel ) power_difference = maxVel; 
  else if ( power_difference < -maxVel ) power_difference = -maxVel;
  //Adelante();
  // Asignar velocidad calculada en el poder diferencial de los motores
  ( power_difference < 0 ) ? setMotors(maxVel + power_difference, maxVel) : setMotors(maxVel, maxVel - power_difference);
    
   frenos_contorno(600);
}


void setMotors(int left, int right){
  
  setMotorLeft(left);
  setMotorRight(right);

  
}
void setMotorLeft(int left){
  if ( left >= 0 ){    
    digitalWrite(MI1,HIGH);
    digitalWrite(MI2,LOW);
  }
  else{    
    digitalWrite(MI1,LOW);
    digitalWrite(MI2,HIGH);
    left *= -1;
  } 
  analogWrite(PWMpinI,left);
}


void setMotorRight(int right){
  if ( right >= 0 ) {   
    digitalWrite(MD1,HIGH);
    digitalWrite(MD2,LOW);
  }
  else  {
    digitalWrite(MD1,LOW);
    digitalWrite(MD2,HIGH);
    right *= -1;
  }    
  analogWrite(PWMpinD,right);
}





 float   readLine(){
      int propFinal = 0.0;
      int s0acum = 0;
      int s1acum = 0;
      int s2acum = 0;
      int s3acum = 0;
      int s4acum = 0;
      int s5acum = 0;
      
      for(int i = 0; i<CANT_LEC ; i++ ){
        s0acum += analogRead(A0);
        s1acum += analogRead(A1);
        s2acum += analogRead(A2);
        s3acum += analogRead(A3);
        s4acum += analogRead(A4);
        s5acum += analogRead(A5);
      }
      
      float s0 = s0acum/CANT_LEC;
      float s1 = s1acum/CANT_LEC;
      float s2 = s2acum/CANT_LEC;
      float s3 = s3acum/CANT_LEC;
      float s4 = s4acum/CANT_LEC;
      float s5 = s5acum/CANT_LEC;
       
      propFinal = (((s1*1000)+(s2*2000)+(s3*3000)+(s4*4000)+(s5*5000))/(s0+s1+s2+s3+s4+s5)) - CENTRO;

      return propFinal;
      
  }
  
void frenos_contorno(int flanco_comparacion){
     if(proportional<=-1300) //si se salio por la parte derecha de la linea
     {
      setMotors(90,-80);  
      while(true)  
      {
       if(analogRead(A0) < flanco_comparacion ||  analogRead(A1) < flanco_comparacion )   //asegurar que esta en linea
       {
        if(digitalRead(A2)==1 || digitalRead(A3)==1){
          c=0;
          interrup=0;
          break;
        }
       }
      }
     }
     
     if(proportional>=900) //si se salio por la parte izquierda de la linea
     { 
      setMotors(-80,90);
      while(true){       
       if(analogRead(A4)<flanco_comparacion || analogRead(A5)<flanco_comparacion)   {
        if(digitalRead(A2)==1 || digitalRead(A3)==1){
          break;
        }
       }  
      }
  }
}

void interrupcion()
   {
 
   interrup = interrup + 1;
   delay(50);
    }
