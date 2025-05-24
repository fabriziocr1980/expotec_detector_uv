## Expotec Sensor de Luz Ultravioleta UVision


El proyecto de detección de luz ultravioleta UVision consiste en la elaboración de un circuito electrónico usando un Arduino Nano, un sensor UV ML8511, una pantalla tipo OLED LCD 128x64 y un módulo de sonido DFPLayer, todos conectados mediante cables de cobre en una placa protoboard para prototipos de electrónica. 

## Descripción de la solución:


El sensor UV ML8511 es un dispositivo que permite medir la intensidad de la luz ultravioleta (UV) para circuitos de electrónica. Es muy útil para proyectos que necesitan detectar los niveles de radiación UV, como estaciones meteorológicas, monitores de índice UV o dispositivos que alertan sobre quemaduras solares.

El sensor dispone de un fotosensor sensible a la luz ultravioleta. Cuando la luz UV incide sobre este fotosensor, se genera una corriente eléctrica que es transformada por un amplificador interno en una señal de voltaje analógica.  
La clave de su funcionamiento es que este voltaje de salida es **directamente proporcional** a la intensidad de la luz UV detectada. Es decir, a mayor intensidad UV, mayor será el voltaje que entregará el sensor.

El proyecto UVision de detección de luz ultravioleta incluye un sensor de este tipo conectado a un Arduino a una de sus entradas analógicas. De esta forma, podemos hacer una lectura mediante programación de los voltajes generados por la salida del sensor.  

La variación del voltaje respecto a la intensidad de luz varía en forma **lineal** y puede ser expresada mediante una ecuación, para lo cual es necesario realizar un cálculo aproximado con los datos del fabricante.

## Función aproximada del ML8511

Según la hoja del fabricante del ML8511 y documentación de ejemplos prácticos (como los de SparkFun), la relación típica es la siguiente:

  ![image](https://github.com/user-attachments/assets/cfa875eb-fabc-41e8-9c68-04eb4f507986)


**Donde:**

- `Vout`: Voltaje de salida del sensor (medido).
- `Vdark`: Voltaje de salida del sensor cuando no hay luz UV (~1.0 V típico).
- `S`: Sensibilidad del sensor, alrededor de 0.1 V por unidad de índice UV (valor típico, puede variar entre sensores).

### 🧪 Ejemplo práctico

Supongamos:

- Medimos `Vout = 1.8 V`
- `Vdark = 1.0 V`
- `S = 0.1 V/UV Index`

Entonces:

