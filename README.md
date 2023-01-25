# ProyectoIoT2023

## Integrantes
- Itzel Alessandra Fuentes Cabrera
- Abraham Salvador Espinoza Gomez
- Alma Yesenia Martínez Aldavera
- Rodrigo Julian Vega Monotoya

## Objetivo general
Este proyecto tiene como objetivo la creación de un dispensador de alimento y de agua para mascota, ya sea un gato o un perro, 
esto con el fin de tener una forma automatizada de tener controlada la alimentación de las mascotas, además de que 
podrá ser de ayuda a tener un control sobre el alimento de nuestra mascota, donde si se termina va a terminar el alimento o el agua
de nuestra mascota, mandará una alerta a nuestro teléfono, mediante una aplicación móvil, la cual nos estará avisando
para que nosotros como los dueños de la mascota, podamos llenar el dispensador de alimento y agua.

### Objetivos específicos
- Mediante una aplicación el usuario será avisado cuando la comida o el del dispensador esta por acabarse para que pueda llenar de nuevo los dispensador.
- Mediante una aplicación el usuario podrá llenar nuevamente los platos con agua o comida.
- Mediante un sensor la mascota podrá alimentarse sola con solo acercarse.
- Poder programar los dispensadores a ciertas horas para que se llenen automaticamente.

## Tabla de Software utilizado
| Id | Software | Version | Tipo |
|----|----------|---------|------|
| 1  |Arduino   |2.0.1    |   IDE|
| 2  |Node-red  |3.0      |Servicio|
|3  |Telegram   |8.3      |App   |

## Tabla con el hardware utilizado
| Id | Componente | Descripción | Imagen | Cantidad | Costo total |
|----|------------|-------------|--------|----------|-------------|
|   1|ESP32| El módulo ESP32 es una solución de Wi-Fi/Bluetooth todo en uno, integrada y certificada que proporciona no solo la radio inalámbrica, sino también un procesador integrado con interfaces para conectarse con varios periféricos|![image](https://user-images.githubusercontent.com/104101668/214482867-90fbaa8c-7d6c-42f5-8a1c-004b815030a6.png)|1|$0|
|   2|ServoMotor| Un servomotor es un actuador rotativo o motor que permite un control preciso en términos de posición angular, aceleración y velocidad, capacidades que un motor normal no tiene. En definitiva, utiliza un motor normal y lo combina con un sensor para la retroalimentación de posición.|![image](https://user-images.githubusercontent.com/104101668/214482747-fb832e0e-00df-4c10-8796-c2203a49bea7.png)|2|$160|
|   3|Sensor ultrasónico HC-SR04|Miden la distancia mediante el uso de ondas ultrasónicas. El cabezal emite una onda ultrasónica y recibe la onda reflejada que retorna desde el objeto. Los sensores ultrasónicos miden la distancia al objeto contando el tiempo entre la emisión y la recepción.|![image](https://user-images.githubusercontent.com/104101668/214482421-9ca2aa8e-2227-464a-9980-5fbd23966cac.png)|1|$80|
|   4|Pantalla LCD|Una pantalla de cristal líquido o LCD es una pantalla delgada y plana formada por un número de píxeles en color o monocromos colocados delante de una fuente de luz o reflectora. A menudo se utiliza en dispositivos electrónicos de pilas, ya que utiliza cantidades muy pequeñas de energía eléctrica.|![image](https://user-images.githubusercontent.com/104101668/214482683-3521e097-00de-4def-a295-a9f4512dde77.png)|1|$90| 
|   5|Plato|Plato de acero Inoxidable|![image](https://user-images.githubusercontent.com/104101668/214483128-4bb5158a-52c1-4d06-b52a-f9479758ad07.png)|2|$80| 
|   6|Sensor nivel del agua|Son instrumentos que activan una alarma en el momento en que el líquido del interior del recipiente alcance el nivel marcado. Se instalan con la finalidad de conseguir la automatización del llenado de recipientes y conocer siempre en tiempo real la capacidad del interior.|![image](https://user-images.githubusercontent.com/104101668/214483265-1638c2d1-11d8-4ffc-962f-96c83813bf62.png)|1|$50| 
|   7|Botellas de plastico|Botella de 2 litros|![image](https://user-images.githubusercontent.com/104101668/214483459-1e7268f1-5bb2-4a10-8e07-40658b33970c.png)|2|$0| 
|   8|Madera| 4 pedazos de madera de diferentes medidas|![image](https://user-images.githubusercontent.com/104101668/214483514-01145c2b-edcc-4f15-8fea-c4e9ecbe881a.png)|4|$150| 


## Tabla de historias de usuario
| Id | Historia de usuario | Prioridad | Estimación | Como probarlo | Responsable |
|----|---------------------|-----------|------------|---------------|-------------|
|  1 | Como usuario quiero poder darle de comer y tomar a mi mascota cada cierto tiempo.|Alta|2-3 semanas|Se deberá esperar a que se llegue a la hora programada para ver que efectivamente funciona.|Itzel|
|  2 |Como usuario quiero que la aplicación me mande una alerta para saber que la comida o agua del dispensador se está terminando.|Alta|2-3 semanas|Esperar a que se vacié el dispensador para ver que manda la alerta a la aplicación.|Abraham|
|  3|Como usuario quiero manejar a tráves de una aplicación controlar el dispensador de alimento y agua|Media|2-3semanas|Observando que al momento de llenar presionar o mandar un mensaje se llenen los dispensadores|Rodrigo|
|  4|Como usuario quiero que mi perro se pueda alimentar en el momento en el que se acerca al dispensador.|Media|2-3semanas|Observando a la mascota acercarse al sensor y ver como este reacciona|Alma|

## Prototipo en dibujo
![image](https://user-images.githubusercontent.com/104101668/214484615-74ee57c3-b80c-44f1-90d1-d8cd39caa426.png)

