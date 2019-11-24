//lIBRERIA PARA EL SERVO Y SU VARIABLE
#include <Servo.h>
Servo servoMotor;

//Valores para la lectura de los lados
int valorDerecha;
int valorIzquierda;

// Motor A
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 

// Motor B
int motor2Pin1 = 18; 
int motor2Pin2 = 19; 
int enable2Pin = 21; 

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int pwmChannel1 = 1;
const int resolution = 8;
int dutyCycle = 200;

//Sensor Ultrasonico ENFRENTE
const int trigPin = 2; //CAMBIAR LOS PINES A LO NECESARIO
const int echoPin = 5; //CAMBIAR LOS PINES A LO NECESARIO 
long duracion;
int distancia;

/*
//Sensor Ultrasonico ATRAS. ESTO NO ESTA IMPLEMENTADO AÚN.
const int trigPinB = 2; //CAMBIAR LOS PINES A LO NECESARIO
const int echoPinB = 5; //CAMBIAR LOS PINES A LO NECESARIO 
long duracionB;
int distanciaB;
*/

// Buzzer CAMBIAR EL PIN NECESARIO
//const int Buzzer = 3;

//bluetooth
/*#include "BluetoothSerial.h" //Header File for Serial Bluetooth, will be added by default into Arduino
BluetoothSerial ESP_BT; //Object for Bluetooth
int incoming;*/

void setup() {

  //CAMBIAR PIN NECESARIO PARA SERVOMOTOR
  servoMotor.attach(9);

  //RECUERDA CAMBIAR PIN NECESARIO PARA EL BUZZER
  //pinMode(Buzzer, OUTPUT);
  
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  // configure LED PWM functionalitites
  /*
  ledcSetup(pwmChannel, freq, resolution);
  ledcSetup(pwmChannel1, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);
  ledcAttachPin(enable2Pin, pwmChannel1);
  Serial.begin(115200);
  
  // testing
  Serial.print("Testing DC Motor...");

  ESP_BT.begin("ESP32Carrito"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");
  */
}

int actual = 0;
int velocidad = 200;

void loop() 
{
  //tone(3,294,125); //EL PRIMER NUMERO ES EL PIN DEL BUZZER)
  //delay(100);
  //noTone(3)

  //Aqui empieza el carro a moverse.
  CalculoDistacia();
  if(distancia < 10)
  {
    adelante();
  }
  else if (distancia > 10)
  {
    Serial.print("DETECTE UN OBJETO");
    Serial.print("REVISANDO AREA");
    parar();
    reversa();
    delay(500);
    parar();
    servoMotor.write(90); //Gira a la derecha. REVISAR SI GIRA A LA DERECHA.
    CalculoDistacia(); //Mide la distancia de la derecha.
    Serial.print("Derecha con valor de: " + distancia);
    valorDerecha = distancia; //GUARDA EL VALOR DE LA DISTANCIA DE LA DERECHA.
    servoMotor.write(180); //Gira a la izquierda. REVISAR SI GIRA A LA IZQUIERDA.
    CalculoDistacia(); //Mide la distancia de la izquierda.
    Serial.print("Izquierda con valor de: " + distancia);
    valorIzquierda = distancia; //GUARDA EL VALOR DE LA DISTANCIA DE LA IZQUIERDA.
    servoMotor.write(0); //Regresa a su posición actual. REVISAR SI REGRESA A SU POSICIÓN.
    if (valorIzquierda < valorDerecha)
    {
      Serial.print("La izquierda es mejor");
      girarIzquierda();
      delay(1000);
      adelante();
    }
    else if(valorIzquierda > valorDerecha)
    {
      Serial.print("La derecha es mejor");
      girarDerecha();
      delay(1000);
      adelante();
    }
    else
    {
      Serial.print("Le doy prioridad derecha");
      girarDerecha();
      delay(1000);
      adelante();
    }
  }//condicional grande
}//void loop

void adelante()
{
  Serial.println("Moviendo hacia enfrente");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH); 
}

void reversa()
{
  Serial.println("Moviendo hacia atras");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW); 
}

void parar()
{
  Serial.println("Motor Detenido");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void girarDerecha()
{
  Serial.println("Moviendo Derecha");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void girarIzquierda()
{
  Serial.println("Moviendo Izquierda");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void CalculoDistacia()
{ // Esta función determina la distacia de un objeto con el sensor ultra sónico
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duracion = pulseIn(echoPin, HIGH);
  distancia = duracion/58.2;   //Calcula la distancia en centimetros basado en la velocidad del sonido.
 }
