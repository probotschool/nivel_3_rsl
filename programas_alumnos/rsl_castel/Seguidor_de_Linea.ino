//Sensores
int SensorExtD = A0;                          //DIRA=DIRECCION A                            
int SensorCenD = A1;                           //DIRB=DIRECCION B
int SensorD = A2;
int SensorI = A3;
int SensorCenI = A4;
int SensorExtI = A5;

//Motor Derecho
int MDerechoPWM = 6;
int MDerechoDIRA = 10;
int MDerechoDIRB = 9;

//Motor Izquierdo
int MIzquierdoPWM = 11;
int MIzquierdoDIRA = 13;
int MIzquierdoDIRB = 12;
//Potencias
const int POTENCIA_MAXIMA=255;
const int POTENCIA_MEDIA=80;
const int POTENCIA_MINIMA=35;
const int POTENCIA_59=170;
const int POTENCIA_53=130;
const int STOP=0;
const int TODO_BLANCO=80;
const int GIRO= 255;
const int MarshaTra = 230;
const int POTENCIA_MINIMAMINIMA = 15;
const int POTENCIA_MEDIAMINIMA = 60;
// Fin de Carrera
const int finDeCarrera = 5;

void setup() {
Serial.begin(9600);
//Sensores
pinMode(SensorExtD,INPUT);
pinMode(SensorCenD,INPUT);
pinMode(SensorD,INPUT);
pinMode(SensorI,INPUT);
pinMode(SensorCenI,INPUT);
pinMode(SensorExtI,INPUT);
//Motor Derecho
pinMode(MDerechoPWM,OUTPUT);
pinMode(MDerechoDIRA,OUTPUT);
pinMode(MDerechoDIRB,OUTPUT);

//Motor Izquierdo
pinMode(MDerechoPWM,OUTPUT);
pinMode(MDerechoDIRA,OUTPUT);
pinMode(MDerechoDIRB,OUTPUT);

//Fin de Carrera
pinMode(finDeCarrera,INPUT);

definirSentidoMotores();


}


void loop() {
  int valorDecision = obtenerLecturaDeSensores();
  Serial.println(valorDecision);
  switch (valorDecision){
    case 63:
    //Motores 100%
    cambiarVelocidad(POTENCIA_MAXIMA, POTENCIA_MAXIMA);
    break;
    
    case 62:
    //Motores 100%
    cambiarVelocidad(POTENCIA_MAXIMA, POTENCIA_MAXIMA);
    break;
    
    case 43:
    cambiarVelocidad(GIRO, POTENCIA_MINIMA);
    break;
    
    case 3:
    cambiarVelocidad(GIRO, POTENCIA_MINIMA);
    break;
    
    case 19:
    cambiarVelocidad(GIRO, POTENCIA_MINIMA);
    break;
    
    case 50: 
    cambiarVelocidad(POTENCIA_MINIMA, GIRO);
    break;
    
    case 48:   
    cambiarVelocidad(POTENCIA_MINIMA, GIRO);
    break;
    
    case 53:   
    cambiarVelocidad(POTENCIA_53, POTENCIA_MAXIMA);
    break;
    
    case 59:   
    cambiarVelocidad(POTENCIA_59, POTENCIA_MAXIMA);
    break;
    case 1: 
    cambiarVelocidad(POTENCIA_MINIMA,POTENCIA_MAXIMA);
    break;
    
    case 52:
    cambiarVelocidad(POTENCIA_MINIMA, GIRO);
    break;
    
    case 54:
    cambiarVelocidad(POTENCIA_MEDIA, POTENCIA_MAXIMA);
    break;

    case 49:
    cambiarVelocidad(STOP, POTENCIA_MAXIMA);
    break;
    
    case 35:
    cambiarVelocidad(GIRO, POTENCIA_MINIMA);
    break;
    
    case 20:
    cambiarVelocidad(POTENCIA_MINIMA,POTENCIA_MAXIMA);
    break;
    
    case 51:
    invertirVelocidadMotores();
    break;
    
    case 41:
    cambiarVelocidad(POTENCIA_MAXIMA, POTENCIA_MEDIA);
    break;
      
    case 9:
    cambiarVelocidad(POTENCIA_MINIMA, POTENCIA_MAXIMA);
    break;

    case 46:
    cambiarVelocidad(POTENCIA_MAXIMA, POTENCIA_MEDIA);
    break;

    case 11:
    cambiarVelocidad(POTENCIA_MAXIMA, POTENCIA_MINIMA);
    break;

    case 12:
    cambiarVelocidad(TODO_BLANCO, TODO_BLANCO);
    break;

    case 60:
    cambiarVelocidad(POTENCIA_MINIMA, POTENCIA_MAXIMA);
    break;
    
    
  } 
}

void cambiarVelocidad(int pwmMotorIzquierdo, int pwmMotorDerecho){
  definirSentidoMotores();
  analogWrite(MIzquierdoPWM, pwmMotorIzquierdo);
  analogWrite(MDerechoPWM, pwmMotorDerecho); 
}

int obtenerLecturaDeSensores(){
   
   int valorSensorCenI = estaEnLineaNegra(SensorCenI);
   int valorSensorExtI = estaEnLineaNegra(SensorI);
   int valorSensorI = estaEnLineaBlanca(SensorI);
   
   int valorSensorD = estaEnLineaBlanca(SensorD);
   int valorSensorCenD = estaEnLineaNegra(SensorCenD);
   int valorSensorExtD = estaEnLineaNegra(SensorExtD);
    
   return (valorSensorExtI * 1) + (valorSensorCenI * 2) + (valorSensorI * 4) + (valorSensorD * 8) + (valorSensorCenD * 16) + (valorSensorExtD * 32);
}

int estaEnLineaNegra(int pinSensor){
  if(analogRead(pinSensor) < 500){
    return 1;
  }else{
    return 0;
  }
}
int estaEnLineaBlanca(int pinSensor){
  if(analogRead(pinSensor) > 500){
    return 1;
  }else{
    return 0;
  }
}

int invertirVelocidadMotores(){
  int potenciaMotorIzquierdo = analogRead(MIzquierdoPWM);
  int potenciaMotorDerecho = analogRead(MDerechoPWM);

  if(potenciaMotorIzquierdo < potenciaMotorDerecho){
    potenciaMotorDerecho = MarshaTra;
    potenciaMotorIzquierdo = POTENCIA_MEDIA;
  }else{
    potenciaMotorIzquierdo = MarshaTra;
    potenciaMotorDerecho = POTENCIA_MEDIA;
  }
  analogWrite(MIzquierdoPWM, potenciaMotorDerecho);
  analogWrite(MDerechoPWM, potenciaMotorIzquierdo);
  
  invertirSentidoMotores();

}

int invertirSentidoMotores(){
    //Motor derecho HIGH/LOW
  digitalWrite(MDerechoDIRA,LOW);
  digitalWrite(MDerechoDIRB,HIGH);
  
  //Motor izquierdo HIGH/LOW
  digitalWrite(MIzquierdoDIRA,LOW);
  digitalWrite(MIzquierdoDIRB,HIGH);

  
}

void definirSentidoMotores(){
  //Motor derecho HIGH/LOWq

  digitalWrite(MDerechoDIRA,HIGH);
  digitalWrite(MDerechoDIRB,LOW);
  
  //Motor izquierdo HIGH/LOW
  digitalWrite(MIzquierdoDIRA,HIGH);
  digitalWrite(MIzquierdoDIRB,LOW); 
}


