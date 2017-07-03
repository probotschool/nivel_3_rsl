          //variables globales                //SE: Sensor Extremo,  SM: Sensor Medio,  SC: Sensor Central
                                    //MD: Motor Derecho,  MI: Motor IZquierdo,  SA: Sentido A,  SB: Sentido B
const int SEDer=A5; //v. sensores
const int SMDer=A4;
const int SCDer=A3;
const int SEIzq=A0;
const int SMIzq=A1;
const int SCIzq=A2;

int blanco=300;
int negro=0;
int limite() {
  return (negro + blanco) / 2;
}



const int MDerPWM=6; //v. motores
const int SAMotD=10;
const int SBMotD=9;

const int MIzqPWM=11;
const int SAMotI=13;
const int SBMotI=12;
                          //potencia 
const int VDELALUZ=255;//para autodestruir el robot si no toma las curvas :v

const int VDEGIRO=170;
const int MAXPOT=90 ;  //255
const int ALTPOT=50;  //200
const int MEDPOT=10;  //128
const int MINPOT=6;  //70
const int ZPOT=0;     //0

const int FdeC=5;

void setup(){
  Serial.begin(9600);
  pinMode(SEDer,INPUT);
  pinMode(SMDer,INPUT);
  pinMode(SCDer,INPUT);
  pinMode(SEIzq,INPUT);
  pinMode(SMIzq,INPUT);
  pinMode(SCIzq,INPUT);

  pinMode(MIzqPWM,OUTPUT);
  pinMode(SAMotI,OUTPUT);
  pinMode(SBMotI,OUTPUT);

  pinMode(MDerPWM,OUTPUT);
  pinMode(SAMotD,OUTPUT);
  pinMode(SBMotD,OUTPUT);

  pinMode(FdeC,INPUT);

  digitalWrite(SAMotD,LOW);
  digitalWrite(SBMotD,HIGH);
  digitalWrite(SAMotI,LOW);
  digitalWrite(SBMotI,HIGH);
}
  
void loop (){
if(!digitalRead(FdeC)){
  cambiarVelocidad(ZPOT,ZPOT);
}


Serial.println(lecSens());
int controlSeguidor=lecSens(); //a la izq mot izq, a la der mot der
//en este valor cada sensor está en su linea 111111
  switch (controlSeguidor){
 case 63:
  cambiarVelocidad(MAXPOT,MAXPOT);//recta
  break;


  //GIROS A LA IZQUIERDA
  
  case   59:
  cambiarVelocidad(ALTPOT,MAXPOT);
  break; //giro minimo a la izq 110111
  
  case  53:
   cambiarVelocidad(MEDPOT,MAXPOT); 
//giro poco a la izq 101011
  break;
  
  case 48:
  cambiarVelocidad(MINPOT,VDEGIRO); 
//giro brusco a la izq 000011
  break;

  case 50: // al maximo a la izquierda sobre su eje
   cambiarVelocidad(ZPOT,VDEGIRO); 
   break;


 //GIROS A LA DERECHA
 
 case 55: //giro minimo derecha 111011
 cambiarVelocidad(MAXPOT,ALTPOT);
 break;
 
  case  43:
  cambiarVelocidad(MAXPOT,MEDPOT); 
//giro poco a la der 110101
  break;

  case 3:
   cambiarVelocidad(VDEGIRO,MINPOT); 
//giro brusco a la der 110000 ooooii
  break;

  case 19: //giro sobre su eje a la der
 cambiarVelocidad(VDEGIRO,ZPOT); 
 break;

 //case 51:  //51 todo negro 110011
   //invertVMOT();

   
    
}
 
}

void cambiarVelocidad (int PotMI,int PotMD){
    analogWrite(MIzqPWM,PotMI);
    analogWrite(MDerPWM,PotMD);
  }
  



int lecSens(){

int VSEIq=lineaNegra(SEIzq);
int VSMIq=lineaNegra(SMIzq);
int VSCIq=lineaBlanca(SCIzq);

int VSCDr=lineaBlanca(SCDer);
int VSMDr=lineaNegra(SMDer);
int VSEDr=lineaNegra(SEDer);
return (VSEIq * 1) + (VSMIq * 2) + (VSCIq * 4) + (VSCDr * 8) + (VSMDr * 16) + (VSEDr * 32);

}
int lineaNegra(int pinSensor){
if (analogRead(pinSensor) < limite()){
  return 1;
}else{
  return 0;
}
}

int lineaBlanca(int pinSensor){
if (analogRead(pinSensor) > limite()){
  return 1;
}else{
  return 0;
}
}


//función para invertir sentido de motores en case 51

//int invertirVMOT(){
  //int potMotorIzq= analogRead(MIzqPWM);
  //int potMotorDer= analogRead(MDerPWM);

//if(potMotorIzq < potMotorDer){
  //potMotorDer = 255;
  //potMotorIzq = 128;
//}
//else{
  //potMotorIzq= 255;
  //potMotorDer= 128;
//}
//analogWrite(MIzqPWM, potMotorDer);
//analogWrite(MDerPWM, potMotorIzq);

//invertirSentM();

//}


//int invertirSentM(){
  //motor derecho
//  digitalWrite(SAMotD,HIGH);
  //digitalWrite(SBMotD,LOW);

  //motor izquierdo
 // digitalWrite(SAMotI,HIGH);
  //digitalWrite(SBMotI,LOW);
//}


//void definirSentM(){
  //motor derecho
  //digitalWrite (SAMotD,LOW);
  //digitalWrite (SBMotD,HIGH);
  //motor izquierdo
  //digitalWrite(SAMotI,LOW);
  //digitalWrite(SBMotI,HIGH);
//}


  

