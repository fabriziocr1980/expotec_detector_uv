#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//// CONFIGURACION DE SONIDO ////////
#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"
static const uint8_t PIN_MP3_TX = 8; // D7
static const uint8_t PIN_MP3_RX = 7; // D6
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
DFRobotDFPlayerMini player;


//// CONFIGURACION DE LA PANTALLA ////////
#define PANTALLA_ANCHO 128
#define PANTALLA_ALTO 64

#define OLED_MOSI 9
#define OLED_CLK 10
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13

Adafruit_SSD1306 display(PANTALLA_ANCHO, PANTALLA_ALTO,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/////////////////////////////////////////
///// CONFIGURACION DE SENSOR UV ///////
int SALIDA_DEL_SENSOR = A0; //
int REF_3V3 = A1;

/// Función para mostrar el mensaje UV en pantalla
void mostrarMensajeUV(float indice, const char* peligro) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Dibujar un rectángulo como marco
  display.drawRect(0, 0, PANTALLA_ANCHO, PANTALLA_ALTO, SSD1306_WHITE);

  // Mostrar "Indice UV"
  display.setTextSize(1);
  display.setCursor(10, 10);
  display.print("Indice UV:");

  display.setTextSize(2);
  display.setCursor(80, 5);  // Ajusta si necesitas moverlo más
  display.print(indice, 1);  // Un decimal
  // Línea divisoria horizontal
  //display.drawLine(0, 30, SCREEN_WIDTH, 30, SSD1306_WHITE);

  // Mostrar "Nivel de peligrosidad"
  display.setTextSize(1);
  display.setCursor(10, 40);
  display.print("Nivel:");

  display.setTextSize(1);
  //display.setCursor(55, 35); mesanje con letra tipo 2
  display.setCursor(48, 40);
  display.print(peligro);
  display.display();
}


void setup() {
  Serial.begin(9600);
// Inicializacion de Pantalla
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  
  // Inicializacion de modulo de Sonido
  softwareSerial.begin(9600);
  if (player.begin(softwareSerial)) 
  {
   Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(22); //30 is very loud
  } 
  else 
  {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }


  // // Puedes modificar estos valores para probar otros niveles
  // float indiceUV = 9.0;
  // const char* nivelPeligro = "Alto";

  // mostrarMensajeUV(indiceUV, nivelPeligro);  // Llamada a la función
  // pinMode(SALIDA_DEL_SENSOR, INPUT);

}

void loop()
{
  int refLevel = averageAnalogRead(REF_3V3);
  int sensorValue = analogRead(SALIDA_DEL_SENSOR);
  float voltage = 3.3 / refLevel * sensorValue;
  
  float uv_intensidad = mapfloat(voltage, 0.99, 2.8, 0.0, 15.0);
  
  // Aproximar índice UV: calibrar según tu sensor, esto es estimado
  Serial.print("---------------------------");
  Serial.println();
  Serial.print("Voltaje de Referencia: ");
  Serial.print(refLevel);
  Serial.println();
  Serial.print("Voltaje de Sensor: ");
  Serial.print(sensorValue);
  Serial.println();
  Serial.print("Voltaje de Convertido: ");
  Serial.print(voltage);
  Serial.println();
  Serial.print("UV Intensidad: ");
  Serial.print(uv_intensidad);
  delay(800);

  //const char* nivelPeligro = "Alto";
  const char* nivelPeligro = nivelPeligroUV(uv_intensidad);
  mostrarMensajeUV(uv_intensidad, nivelPeligro);  // Llamada a la función para mostrar en pantalla
  
  // Chequeo de intensidad y 
  if (uv_intensidad >= 6) {
     player.volume(28);
     player.play(1);
     delay(6000);
  }
  else {
    Serial.print(" No emitir sonido ");
  }

  Serial.println();
}

//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);  
}

//The Arduino Map function but for floats
//From: http://forum.arduino.cc/index.php?topic=3922.0
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Rangos de UV de acuerdo a tabla de la OMS
const char* nivelPeligroUV(float index) {
  if (index < 3) return "Bajo";
  else if (index < 6) return "Moderado";
  else if (index < 8) return "Alto";
  else if (index < 11) return "Muy Alto";
  else return "Extremo";
}
