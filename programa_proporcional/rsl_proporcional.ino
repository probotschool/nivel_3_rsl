/*
 * SENSORES CNY70
 * Se define una constante para cada sensor, la cual tiene el valor
 * del número del pin de la placa Arduino donde está conectado.
 */
const int pinSensorExtremoIzquierdo=A0;
const int pinSensorMedioIzquierdo=A1;
const int pinSensorCentroIzquierdo=A2;
const int pinSensorCentroDerecho=A3;
const int pinSensorMedioDerecho=A4;
const int pinSensorExtremoDerecho=A5;

/*
 * LÍMITES DE LOS COLORES
 * Se define una constante para cada COLOR. Las misma se utilizan para establecer
 * el límite de decisión, para que al leer los sensores pueda especificarse si
 * el sensor lee color negro o blanco.
 */
const int limiteColorBlanco=350;
const int limiteColorNegro=200;

/*
 * MOTORES
 * Se definen 3 constantes para cada motor, una para el PWM (potencia),
 * Y dos para especificar el sentido de giro del motor.
 */
const int pinMotorDerechoPWM=6;
const int pinMotorDerechoSentidoA=10;
const int pinMotorDerechoSentidoB=9;

const int pinMotorIzquierdoPWM=11;
const int pinMotorIzquierdoSentidoA=13;
const int pinMotorIzquierdoSentidoB=12;

/*
 * CONSTANTES DE POTENCIAS UTILIZADAS
 * Se define una constante para potencia que se desea utilizar. 
 * Cuando deba cambiar la velocidad del motor se utilizan las constantes.
 * de esta forma permitimos configurar más fácil el robot.
 */
const int POTENCIA_LIMITE_MAXIMO=255;
const int POTENCIA_DE_GIRO=170;
const int POTENCIA_MAXIMA=90 ;  //255
const int POTENCIA_ALTA=50;  //200
const int POTENCIA_MEDIA=10;  //128
const int POTENCIA_MINIMA=6;  //70
const int POTENCIA_CERO=0;     //0

/*
 * FIN DE CARRERA
 * Se define una constante para IDENTIFICAR el fin de carrera del robot.
 * al estar presionado debe colocarse potencia cero.
 */
const int pinFinDeCarrera=5;

/*
 * BLOQUE SETUP
 * El bloque setup se ejecuta al iniciar el programa, y acá se define cada pin
 * indicando si es de tipo entrada o salida.
 * También se establece el sentido de giro de los motores
 */
void setup(){
  Serial.begin(9600); // Iniciamos el puerto Serial
  // Inicializamos los pines de los sensores como tipo INPUT
  pinMode(pinSensorExtremoDerecho,INPUT);
  pinMode(pinSensorMedioDerecho,INPUT);
  pinMode(pinSensorCentroDerecho,INPUT);
  pinMode(pinSensorExtremoIzquierdo,INPUT);
  pinMode(pinSensorMedioIzquierdo,INPUT);
  pinMode(pinSensorCentroIzquierdo,INPUT);

  // Inicializamos el motor IZQUIERDO.
  pinMode(pinMotorIzquierdoPWM,OUTPUT);
  pinMode(pinMotorIzquierdoSentidoA,OUTPUT);
  pinMode(pinMotorIzquierdoSentidoB,OUTPUT);
  digitalWrite(pinMotorIzquierdoSentidoA,LOW);
  digitalWrite(pinMotorIzquierdoSentidoB,HIGH);

  // Inicializamos el motor DERECHO
  pinMode(pinMotorDerechoPWM,OUTPUT);
  pinMode(pinMotorDerechoSentidoA,OUTPUT);
  pinMode(pinMotorDerechoSentidoB,OUTPUT);
  digitalWrite(pinMotorDerechoSentidoA,LOW);
  digitalWrite(pinMotorDerechoSentidoB,HIGH);

  // Inicializamos el fin de carrera
  pinMode(pinFinDeCarrera,INPUT);  
}
  
void loop (){
  if(!digitalRead(pinFinDeCarrera)){
    cambiarVelocidad(POTENCIA_CERO, POTENCIA_CERO);
  }else{
    Serial.println(obtenerLecturaSensores());
    int controlSeguidor=obtenerLecturaSensores();
    switch (controlSeguidor){
      /*
      * CASO 111111 - Recta
      */
      case 63: //recta 111111
        cambiarVelocidad(POTENCIA_MAXIMA, POTENCIA_MAXIMA);
      break;
      //GIROS A LA IZQUIERDA
      /*
      * CASO 110111 - Giro mínimo a la izquierda
      */ 
      case   59:
        cambiarVelocidad(POTENCIA_ALTA, POTENCIA_MAXIMA);
      break;
      /*
      * CASO 101011 - Giro poco a la izquierda
      */ 
      case  53:
        cambiarVelocidad(POTENCIA_MEDIA, POTENCIA_MAXIMA);
      break;
      /*
      * CASO 000011 - Giro brusco a la izquierda
      */ 
      case 48:
        cambiarVelocidad(POTENCIA_MINIMA, POTENCIA_DE_GIRO);
      break;
      /*
      * CASO 000011 - Giro máximo a la izquierda
      */ 
      case 50: 
        cambiarVelocidad(POTENCIA_CERO, POTENCIA_DE_GIRO); 
      break;
      //GIROS A LA DERECHA  
      /*
      * CASO 111011 - Giro mínimo a la derecha
      */  
      case 55:
        cambiarVelocidad(POTENCIA_MAXIMA, POTENCIA_ALTA);
      break;
      /*
      * CASO 110101 - Giro poco a la derecha
      */ 
      case  43:
        cambiarVelocidad(POTENCIA_MAXIMA, POTENCIA_MEDIA); 
      break;
      /*
      * CASO 110000 - Giro brusco a la derecha
      */ 
      case 3:
        cambiarVelocidad(POTENCIA_DE_GIRO, POTENCIA_MINIMA); 
      break;
      /*
      * CASO 000011 - Giro máximo a la derecha
      */ 
      case 19: 
        cambiarVelocidad(POTENCIA_DE_GIRO, POTENCIA_CERO); 
      break;
        
    }
  } 
}

/*
 * FUNCION DE CAMBIO DE VELOCIDAD DE LOS MOTORES
 * Recibe por parámetros la potencia del motor izquierdo y derecho
 * Y escribe en las salidas analógicas de los PWM de cada motor.
 */
void cambiarVelocidad (int potenciaMotorIzquierdo,int potenciaMotorDerecho){
  // Escribimos en el pin del pwm del motor izquierdo la potencia recibida por parametro llamada potenciaMotorIzquierdo
  analogWrite(pinMotorIzquierdoPWM, potenciaMotorIzquierdo);
  // Escribimos en el pin del pwm del motor derecho la potencia recibida por parametro llamada potenciaMotorDerecho
  analogWrite(pinMotorDerechoPWM, potenciaMotorDerecho);
}

/*
 * FUNCION PARA LEER LOS SENSORES Y OBTENER UN RESULTADO ÚNICO
 * Devuelve un valor numérico entre 0 y 63. Y representa el estado del 
 * robot en la pista. Y hacemos uso de este valor para decidir luego el cambio de velocidad.
 */
int obtenerLecturaSensores(){
  // Para cada sensor preguntamos si se encuentra leyendo el color que le corresponde.
  int VSEIq=lineaNegra(pinSensorExtremoIzquierdo);
  int VSMIq=lineaNegra(pinSensorMedioIzquierdo);
  int VSCIq=lineaBlanca(pinSensorCentroIzquierdo);

  int VSCDr=lineaBlanca(pinSensorCentroDerecho);
  int VSMDr=lineaNegra(pinSensorMedioDerecho);
  int VSEDr=lineaNegra(pinSensorExtremoDerecho);

  /* Multiplicamos cada valor por su peso para armar el valor único del estado del robot.
   * Por ejemplo si cada sensor está en su respectivo color
   * (1 * 1) + (1 * 2) + (1 * 4) + (1 * 8) + (1 * 16) + (1 * 32) = 63
   */
  return (VSEIq * 1) + (VSMIq * 2) + (VSCIq * 4) + (VSCDr * 8) + (VSMDr * 16) + (VSEDr * 32);
}

/*
 * FUNCION PARA PREGUNTA SI EL SENSOR LEE COLOR NEGRO
 */
int lineaNegra(int pinSensor){
  if (analogRead(pinSensor) < limiteColorNegro){
    return 1;
  }else{
    return 0;
  }
}

/*
 * FUNCION PARA PREGUNTA SI EL SENSOR LEE COLOR BLANCO
 */
int lineaBlanca(int pinSensor){
  if (analogRead(pinSensor) > limiteColorBlanco){
    return 1;
  }else{
    return 0;
  }
}