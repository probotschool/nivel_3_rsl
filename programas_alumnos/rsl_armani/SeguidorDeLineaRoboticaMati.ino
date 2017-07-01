const bool atrasActivado = false;

const int sensorExtremoDerecho = A5;
const int sensorExtremoIzquierdo = A0;
const int sensorMedioDerecho = A4;
const int sensorMedioIzquierdo = A1;
const int sensorCentralDerecho = A3;
const int sensorCentralIzquierdo = A2;

const int finDeCarrera = 5;

const int blanco = 700;
const int negro = 100;
const int limite = (negro + blanco)/2;

const int motorDerecho = 6;
const int sAMotorDerecho = 10;     //sentidos necesitados para puente H.
const int sBMotorDerecho = 9;

const int motorIzquierdo = 11;
const int sAMotorIzquierdo = 13;   //sentidos necesitados para puente H.
const int sBMotorIzquierdo = 12;

const int potenciaMax = 200;  //niveles de potencias.
const int potenciaMed = 100;
const int potenciaMin = 50;
const int potenciaNul = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sensorExtremoDerecho, INPUT);
  pinMode(sensorExtremoIzquierdo, INPUT);
  pinMode(sensorMedioDerecho, INPUT);
  pinMode(sensorMedioIzquierdo, INPUT);
  pinMode(sensorCentralDerecho, INPUT);
  pinMode(sensorCentralIzquierdo, INPUT);

  pinMode(motorDerecho, OUTPUT);
  pinMode(sAMotorDerecho, OUTPUT);
  pinMode(sBMotorDerecho, OUTPUT);

  pinMode(motorIzquierdo, OUTPUT);
  pinMode(sAMotorIzquierdo, OUTPUT);
  pinMode(sBMotorIzquierdo, OUTPUT);

  digitalWrite(sAMotorDerecho, HIGH);
  digitalWrite(sBMotorDerecho, LOW);
  digitalWrite(sAMotorIzquierdo, HIGH);
  digitalWrite(sBMotorIzquierdo, LOW);
}

void loop() {

  if(digitalRead(finDeCarrera)){
  
  int valorDecision = obtenerLecturaDeSensores();
  
  switch(valorDecision){
    case 63: //OO11OO
      Serial.println(valorDecision);
      Serial.print("DERECHO ");
      derecho();
      break;

    case 53: //O11OOO
      Serial.println(valorDecision);
      Serial.print("GIRAR IZQUIRDA ");
      girarIzquierda();
      break;
      
    case 43: //OOO11O
      Serial.println(valorDecision);
      Serial.print("GIRAR DERECHA ");
      girarDerecha();
      break;

    case 48: //11OOOO
     Serial.println(valorDecision);
     Serial.print("GIRAR IZQUIERDA EXTREMO ");
     girarIzquierdaExtremo();
     break;

    case 3:  //OOOO11
     Serial.println(valorDecision);
     Serial.print("GIRAR EXTREMO DERECHA ");
     girarDerechaExtremo();
     break;

    case 19:  //OOOOO1
     Serial.println(valorDecision);
     Serial.print("GIRAR MEGA EXTREMO DERECHA ");
     girarDerechaMegaExtremo();
     break;

    case 50:  //1OOOOO
     Serial.println(valorDecision);
     Serial.print("GIRAR MEGA EXTREMO IZQUIERDA ");
     girarIzquierdaMegaExtremo();
     break;

    case 51: //OOOOOO
     Serial.println(valorDecision);
     Serial.print("ATRAS ");
     atras();
     break;
   }
  }else{
    parar();
  }
}
int obtenerLecturaDeSensores(){
  int valorSensorExtremoDerecho = estaEnLineaNegra(analogRead(sensorExtremoDerecho));
  int valorSensorExtremoIzquierdo = estaEnLineaNegra(analogRead(sensorExtremoIzquierdo));
  int valorSensorMedioDerecho = estaEnLineaNegra(analogRead(sensorMedioDerecho));
  int valorSensorMedioIzquierdo = estaEnLineaNegra(analogRead(sensorMedioIzquierdo));
  int valorSensorCentralDerecho = estaEnLineaBlanca(analogRead(sensorCentralDerecho));
  int valorSensorCentralIzquierdo = estaEnLineaBlanca(analogRead(sensorCentralIzquierdo));

  return (valorSensorExtremoIzquierdo * 1) + (valorSensorMedioIzquierdo * 2) + (valorSensorCentralIzquierdo * 4) + (valorSensorCentralDerecho * 8) + (valorSensorMedioDerecho * 16) + (valorSensorExtremoDerecho * 32);
}
int estaEnLineaNegra(int valorSensor){
  if(valorSensor < limite){
    return 1;
  }else{
    return 0;
  }
}
int estaEnLineaBlanca(int valorSensor){
  if(valorSensor > limite){
    return 1;
  }else{
    return 0;
  }
}
void derecho(){
  definirMotoresAdelante();
  analogWrite(motorDerecho, potenciaMax);
  analogWrite(motorIzquierdo, potenciaMax);
}
void girarDerecha(){
  definirMotoresAdelante();
  analogWrite(motorDerecho, potenciaMed);
  analogWrite(motorIzquierdo, potenciaMax);
}
void girarIzquierda(){
  definirMotoresAdelante();
  analogWrite(motorDerecho, potenciaMax);
  analogWrite(motorIzquierdo, potenciaMed);
}
void girarDerechaExtremo(){
  definirMotoresAdelante();
  analogWrite(motorDerecho, potenciaMin);
  analogWrite(motorIzquierdo, potenciaMax);
}
void girarIzquierdaExtremo(){
  definirMotoresAdelante();
  analogWrite(motorDerecho, potenciaMax);
  analogWrite(motorIzquierdo, potenciaMin);
}
void girarDerechaMegaExtremo(){
  definirMotoresAdelante();
  analogWrite(motorDerecho, potenciaNul);
  analogWrite(motorIzquierdo, potenciaMax);
}
void girarIzquierdaMegaExtremo(){
  definirMotoresAdelante();
  analogWrite(motorDerecho, potenciaMax);
  analogWrite(motorIzquierdo, potenciaNul);
}
void parar(){
  analogWrite(motorDerecho, potenciaNul);
  analogWrite(motorIzquierdo, potenciaNul);
}
void atras(){
  if(atrasActivado){
  definirMotoresAtras();
  analogWrite(motorDerecho, potenciaMax);
  analogWrite(motorIzquierdo, potenciaMax);
  }
}
void definirMotoresAtras(){
  digitalWrite(sAMotorDerecho, LOW);
  digitalWrite(sBMotorDerecho, HIGH);
  digitalWrite(sAMotorIzquierdo, LOW);
  digitalWrite(sBMotorIzquierdo, HIGH);
}
void definirMotoresAdelante(){
  digitalWrite(sAMotorDerecho, HIGH);
  digitalWrite(sBMotorDerecho, LOW);
  digitalWrite(sAMotorIzquierdo, HIGH);
  digitalWrite(sBMotorIzquierdo, LOW);
}

