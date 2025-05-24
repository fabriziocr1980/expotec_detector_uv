## Expotec Sensor de Luz Ultravioleta UVision


El proyecto de detección de luz ultravioleta UVision consiste en la elaboración de un circuito electrónico usando un Arduino Nano, un sensor UV ML8511, una pantalla tipo OLED LCD 128x64 y un módulo de sonido DFPLayer, todos conectados mediante cables de cobre en una placa protoboard para prototipos de electrónica. 

## Problemática actual

Los deportistas que entrenan o compiten al aire libre enfrentan un grave riesgo de daño por radiación ultravioleta (UV), especialmente por la falta de alertas adecuadas en sus lugares de actividad.
Los riesgos  incluyen mayor riesgo de cáncer de piel (melanoma), envejecimiento prematuro, y daños oculares como cataratas y la exposición prolongada debilita el sistema inmune de la piel.   

Muchos deportistas y entrenadores subestiman la intensidad del UV, que está presente incluso en días nublados y la ausencia de alertas hace que la población deportiva sea subceptible ya que no hay suficientes sistemas visibles (como el Índice UV en tiempo real) en estadios, parques o rutas de entrenamiento para recordar la necesidad de protección.


## Componentes del Sistema

1.  Arduino Nano:
2.  Sensor UV ML8511
3.  Pantala OLED 128x64
4.  Módulo de Sonido DF-Player
5.  Parlante
6.  Placa Protoboard y accessorios como caja, chasiss de protección
7.  Bateria externa USB
8.  LEDs de notificación 

## Descripción de la solución:

La solución propuesta hace uso de dispositivos de electrónica para hacer detecciones de la luz UV en diferentes escenarios deportivos al aire libre como es el caso del atletismo, para lo cual se plantea un diseño de un circuito portátil el cual puede ser llevado a diferentes sitios y poder notificar mediante altertas sonoras y visuales las condiciones actuales de la intensidad de la luz UV, la cual es dañina según diversas organizaciones mundiales de salud como la OMS o la Sociedad Americana del Cáncer.

Uno de los elementos centrales del proyecto es el sensor UV ML8511, que es un dispositivo que permite medir la intensidad de la luz ultravioleta (UV) y el cual es muy utilizado en proyectos de electrónica que necesitan detectar los niveles de radiación UV, como estaciones meteorológicas, monitores de índice UV o dispositivos que alertan sobre quemaduras solares.


![image](https://github.com/user-attachments/assets/1fbef57b-d9c9-41c5-a716-51c71ee3cc81)



El sensor dispone de un fotosensor sensible a la luz ultravioleta y cuando la luz UV incide sobre este fotosensor, se genera una corriente eléctrica que es transformada por un amplificador interno en una señal de voltaje analógica.  
La clave de su funcionamiento es que este voltaje de salida es **directamente proporcional** a la intensidad de la luz UV detectada. Es decir, a mayor intensidad UV, mayor será el voltaje que entregará el sensor.

El proyecto UVision de detección de luz ultravioleta incluye un sensor de este tipo conectado a un Arduino a una de sus entradas analógicas. De esta forma, se puede hacer una lectura mediante programación de los voltajes generados por la salida del sensor y detectada por el Arduino y por consiguiente ser mostrada en pantalla.  

La variación del voltaje respecto a la intensidad de luz varía en forma **lineal** y puede ser expresada mediante una ecuación, para lo cual es necesario realizar un cálculo aproximado con los datos del fabricante.

# Función aproximada del ML8511

Según la hoja del fabricante del ML8511 (https://cdn.sparkfun.com/datasheets/Sensors/LightImaging/ML8511_3-8-13.pdf) y documentación de ejemplos prácticos (como los de SparkFun), la relación típica es la siguiente:

  ![image](https://github.com/user-attachments/assets/cfa875eb-fabc-41e8-9c68-04eb4f507986)


**Donde:**

- `Vout`: Voltaje de salida del sensor (medido).
- `Vdark`: Voltaje de salida del sensor cuando no hay luz UV (~1.0 V típico).
- `S`: Sensibilidad del sensor, alrededor de 0.1 V por unidad de índice UV (valor típico).

### 🧪 Ejemplo práctico

Supongamos:

- Medimos `Vout = 1.8 V`
- `Vdark = 1.0 V`
- `S = 0.1 V/UV Index`

Entonces:

           1.8 V − 1.0 V 
           -------------   = 8 ( intensidad de UV) 
                0.1 

Este nivel corresponde a la escala de intensidad definida por la OMS, para lo cual la programación lógica del Arduino Nano contempla una condición de alerta en cuyo caso se detecten niveles peligros a como están mostrados en la siguiente escala:
![image](https://github.com/user-attachments/assets/b4cc2aec-41af-4855-a354-113c0a6284c4)

## Emision de las Alertas :

Nival 1-1 Bajo:  Se emite una alerta temporal sonora en el parlante sobre 

