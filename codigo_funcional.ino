#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



//// CONFIGURACION DE LA PANTALLA ////////
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI 9
#define OLED_CLK 10
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/////////////////////////////////////////
///// CONFIGURACION DE SENSOR UV ///////
int UVOUT = A0; //
int REF_3V3 = A1;

// Función para mostrar el mensaje UV en pantalla
void mostrarMensajeUV(float indice, const char* peligro) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Dibujar un rectángulo como marco
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);

  // Mostrar "UV Index"
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

  display.setTextSize(2);
  display.setCursor(65, 35);
  display.print(peligro);

  display.display();
}


void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  // Puedes modificar estos valores para probar otros niveles
  float indiceUV = 0.0;
  const char* nivelPeligro = "Init";

  mostrarMensajeUV(indiceUV, nivelPeligro);  // Llamada a la función
  pinMode(UVOUT, INPUT);

}

void loop()
{
  int refLevel = averageAnalogRead(REF_3V3);
  int sensorValue = analogRead(UVOUT);
  float voltage = 3.3 / refLevel * sensorValue;
  float uvIntensity = mapfloat(voltage, 0.99, 2.8, 0.0, 15.0);
  
  // Salidas en pantalla serial para pruebas iniciales
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
  Serial.print(uvIntensity);
  delay(3000);

  //const char* nivelPeligro = "Alto";
  const char* nivelPeligro = nivelPeligroUV(uvIntensity);
  mostrarMensajeUV(uvIntensity, nivelPeligro);  // Llamada a la función para mostrar en pantalla
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

const char* nivelPeligroUV(float index) {
  if (index < 3) return "Bajo";
  else if (index < 6) return "Moderado";
  else if (index < 8) return "Alto";
  else if (index < 11) return "Muy Alto";
  else return "Extremo";
}
