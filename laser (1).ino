// Biblioteca para comunicação serial
#include <Arduino.h>

// Define os pinos para os LEDs RGB (led1 e led2), o diodo laser e o buzzer
const int led1R = 4;
const int led1G = 3;
const int led1B = 2;
const int led2R = 7;
const int led2G = 6;
const int led2B = 5;
const int laserPin = 10;
const int buzzerPin = 11;

// Define os pinos para os switches
const int switch1Pin = 8;
const int switch2Pin = 9;

// Define a variável para monitorar a bateria e os valores para os resistores do divisor de tensão
const int batteryPin = A0;
const float R1 = 3000.0;
const float R2 = 5000.0;

// Variável booleana para controle do disparo
bool em_disparo = false;

//float onTime = 12.5; //valor real

float onTime = 7.1; // valor para a simulação



void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);

  // Configura os pinos dos LEDs RGB como saída
  pinMode(led1R, OUTPUT);
  pinMode(led1G, OUTPUT);
  pinMode(led1B, OUTPUT);
  pinMode(led2R, OUTPUT);
  pinMode(led2G, OUTPUT);
  pinMode(led2B, OUTPUT);

  // Configura os pinos dos switches como entrada com pull-up interno ativado
  pinMode(switch1Pin, INPUT_PULLUP);
  pinMode(switch2Pin, INPUT_PULLUP);

  // Configura os pinos do diodo laser e do buzzer como saída
  pinMode(laserPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Inicialmente, o led1 deve acender vermelho
  setColorRGB(led1R, led1G, led1B, 255, 0, 0);

  // Mostra as informações iniciais no monitor serial
  Serial.println("Sistema iniciado.");
  Serial.println("Led1 ligado em vermelho.");


  // Mostra as informações iniciais no monitor serial

  Serial.print("On time: ");
  Serial.println(onTime);

}

void loop() {
  // Leitura da tensão da bateria
  float voltage = readBatteryVoltage();

  // Mostra a tensão da bateria no monitor serial
  Serial.print("Tensao da bateria: ");
  Serial.print(voltage);
  Serial.println("V");

  // Verifica a tensão lida e controla o LED RGB led1
  if (voltage >= 8.0) {
    setColorRGB(led1R, led1G, led1B, 0, 255, 0); // Verde
  } else if (voltage >= 7.0) {
    setColorRGB(led1R, led1G, led1B, 255, 255, 0); // Amarelo
  } else if (voltage >= 6.0) {
    setColorRGB(led1R, led1G, led1B, 255, 165, 0); // Laranja
  } else if (voltage >= 5.0) {
    setColorRGB(led1R, led1G, led1B, 255, 0, 0); // Vermelho
  }

  // Verifica se o Switch1 foi pressionado e a variável em_disparo é false
  if (digitalRead(switch1Pin) == LOW && !em_disparo) {
    // Nada deve acontecer neste caso
  }
  // Verifica se o Switch1 foi pressionado e a variável em_disparo é true
  else if (digitalRead(switch1Pin) == LOW && em_disparo) {
    

    delay(6); //Delay de 6 millisegundos entre a leitura do microswitch e o disparo do laser
    uIPMSignal();

    em_disparo = false; // Reseta a variável em_disparo
    // Aciona o buzzer simulando um tiro
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    setColorRGB(led2R, led2G, led2B, 255, 0, 0); // led2 fica em vermelho
    // Mostra o resultado do disparo no monitor serial
    Serial.println("Disparo concluido.");
    Serial.println("Led2 ligado em vermelho.");
  }

  // Verifica se o Switch2 foi acionado e a variável em_disparo é false
  if (digitalRead(switch2Pin) == LOW && !em_disparo) {
    em_disparo = true; // Define a variável em_disparo como true
    setColorRGB(led2R, led2G, led2B, 0, 255, 0); // led2 fica em verde

    // Mostra o resultado do acionamento do Switch2 no monitor serial
    Serial.println("Switch2 acionado.");
    Serial.println("Led2 ligado em verde.");
  }
}

// Função para definir as cores dos LEDs RGB
void setColorRGB(int pinR, int pinG, int pinB, int redValue, int greenValue, int blueValue) {
  analogWrite(pinR, redValue);
  analogWrite(pinG, greenValue);
  analogWrite(pinB, blueValue);
}

// Função para ler a tensão da bateria
float readBatteryVoltage() {
  int sensorValue = analogRead(batteryPin);
  float voltage = sensorValue * (8.0 / 1023.0) * (R1 + R2) / R2;
  return voltage;
}


void uIPMSignal() {
  //S-11010111 - 15.6ms
  sequenciaInicial(); //2.4ms + 0.6ms = 3ms

  umLogico(true); //1.2ms + 0.6ms = 1.8ms
  umLogico(true); //1.2ms + 0.6ms = 1.8ms
  zeroLogico();  //0.6ms + 0.6ms = 1.2ms
  umLogico(true); //1.2ms + 0.6ms = 1.8ms
  zeroLogico();  //0.6ms + 0.6ms = 1.2ms
  umLogico(true); //1.2ms + 0.6ms = 1.8ms
  umLogico(true); //1.2ms + 0.6ms = 1.8ms
  umLogico(false); //1.2ms = 1.2ms

  //TOTAL: 15.6ms
}

void sequenciaInicial() {

  for (int x = 0; x <= 96; x++) { //duracao 2.4ms
    // Gera o sinal de onda quadrada por 25 ms (12,5 us em HIGH e 12,5 us em LOW)
    digitalWrite(laserPin, HIGH);
    delayMicroseconds(onTime);
    digitalWrite(laserPin, LOW);
    delayMicroseconds(onTime);
  }

  //intervalo
  delayMicroseconds(600);//0.6ms


}


void umLogico(boolean atraso) {

  for (int x = 0; x <= 48; x++) { //duracao 1.2ms
    // Gera o sinal de onda quadrada por 25 ms (12,5 us em HIGH e 12,5 us em LOW)
    digitalWrite(laserPin, HIGH);
    delayMicroseconds(onTime);
    digitalWrite(laserPin, LOW);
    delayMicroseconds(onTime);
  }

  //intervalo
  if (atraso)
    delayMicroseconds(600);//0.6ms


}

void zeroLogico() {

  for (int x = 0; x <= 24; x++) { //duracao 0.6ms
    // Gera o sinal de onda quadrada por 25 ms (12,5 us em HIGH e 12,5 us em LOW)
    digitalWrite(laserPin, HIGH);
    delayMicroseconds(onTime);
    digitalWrite(laserPin, LOW);
    delayMicroseconds(onTime);
  }

  //intervalo
  delayMicroseconds(600);//0.6ms


}


void constante(int repeticoes) {
  for (int x = 0; x <= repeticoes; x++) {
    // Gera o sinal de onda quadrada por 25 ms (12,5 us em HIGH e 12,5 us em LOW)
    digitalWrite(laserPin, HIGH);
    delayMicroseconds(onTime);
    digitalWrite(laserPin, LOW);
    delayMicroseconds(onTime);
  }
}
