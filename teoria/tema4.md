# Comunicaciones en sistemas empotrados

## Introduccion

Los sistemas empotrados ...

Las comunicaciones que componen un sistemas empotrados se reduce al numero de actuadores y sensores que componen. 

Sin embargo los sistemas empotrados distrivuidos son sistemas que componen multiples controladores en comunicacion.

## Buses

Los buses se usan para la comunicacion porque permiten transmitir la informacion por sistemas cableados. El problema que genera es que, complifica bastante la electronica, por lo cual solamente se usa en placas de PCB.

Ademas, los por protocolos SPI e I²C pretenden simplificar la conexion de los perifericos locales al microcontrolador.

Todos los buses que se trabajan en este tema son en serie excepto WIFI y Bluetooth

## SPI: Serial Peripheral Interface

Define cuatro señales para la comunicación:
* SCLK: Reloj de sincronismo
* MOSI: Master ouput slave input
* MISO: Master input slave output
* SSx: Slave select X

El uso de las líneas SSx permite multiplexar las restantes.

Para transmitir los datos 2 de las 3 lineas se usan para transmitir la informacion y la tercera es la señal de reloj de sincronismo.

En algunos de los dispositivos suelen ser solo transmisores y otros solamente receptores.

Para trabajar con SPI se usa un sistema de MASTER y ESCLAVO. Ademas, si nosotros no configuramos el sincronismo del reloj correctamente, el dato se puede perder.

En las configuraciones posible esta el flanco de bajada CPOL = 0 y el flanco de subida CPOL = 1, y cuando se empieza a detectar el dato, cuando empieza a haber un flanco CPHA = 0 o cuando acaba CPHA = 1.

### SPI: Ventajas

Comunicación full duplex
* Protocolo flexible sin tamaño preestablecido
* No hay necesidad de arbitraje
* Los esclavos no necesitan reloj
* Se puede implementar solo una de las dos funcionalidades (emisor – receptor)

### SPI: Inconvenientes

Usa mayor número de pines
* Una línea de selección por esclavo
* No hay control de flujo por hardware
* No hay señal de aceptación. El master puede estar enviando sin que se reciba
* No es fácil conectar varios masters a un solo bus

## I²C: Inter-Integrated Circuit

Metodo de comunicacion que unicamente empleaba dos cables, que era el `serial data SDA` y el `serial clock SCL`

El I²C tiene de cualidad que cualquier numero de dispositicaso se pueden conectar al bus usando el protocolo:
* Dirección de esclavo de 7 bits
* Bloques de datos de 8 bits
* Bits de control: start, end, direction y acknowledgement

Este metodo permite que los dispositivos se puedan conectar en paralelo, y que se puedan conectar varios dispositivos en el mismo bus.

Para poder tener una comunicacion correcta cuando hay varios dispositivos conectados a un solo bus, se necesita que cada dispositivo tenga una direccion unica. Donde la conexion de los dispositivos se ordenan por prioridad, el que este mas serca del microcontrolador tiene mas prioridad.

No he escrito todo, basarse de la diapositiva

## 1-Wire

Es un bus de comunicacion que se basa en un solo cable, que es el `data` y el `ground`. Este bus se usa para comunicar dispositivos de baja velocidad. Consiste en un master y varios esclavos.

La comunicacion se basa en el inicio de la comunicación por el master y la sincronización autónoma de los esclavos. Electricamente, el bus 1-wire presenta un pull-up y todas las salidas de los dispositivos son a colector abierto.

Cada elemento posee un identificador único de 64 bits que se emplea como dirección de red. Un subconjunto de 8 bits de la dirección se emplea como código de familia, que identifica el tipo de dispositivo.

## CAN: Computer Area Network

Es un bus de comunicacion que se usa en automocion, en la industria y en la domotica. 

Existe el Protocolo serie asincrono de tipo CSMA/CD, este bus es un medio compartido (miltiplexado). Todos pueden transmitir y deben monitorizar el bus para saber si pueden transmitir.

## RS232 (UART)
Es un bus de comunicacion que se usa en la comunicacion de dispositivos de baja velocidad. Se basa en la comunicacion de dos cables, que son el `TX` y el `RX`.

* Transmisión de señales a media distancia
* Velocidad de transmisión moderada
* Envío en serie de la información
* Estructuras complejas de transmisor y receptor (conversión serie-paralelo y viceversa)
* Solo dos conductores imprescindibles(datos y masa)

### Niveles eléctricos

* RS232: 115 Kbit/s a 25 metros.
    * Uno lógico para voltajes más negativos que -3 V
    * Cero lógico para voltajes más positivos que +3 V
* RS422: 100 Kbit/s a 1200 metros.
  * Transmisión por lazo de corriente
  * Emisor y receptor diferencial
* RS423: 3 Kbit/s a 1200 metros. Compatibilidad
  * Emisor no diferencial
  * Receptor diferencial

Cuando se trabaja con RS232, se necesita tener en cuenta que la comunicacion es full duplex, y que el microcontrolador tiene que tener un buffer para poder almacenar los datos que se reciben.

### Protocolo

* Protocolo de transmisión de una palabra:
  * Marca (HI) (línea en reposo)
  * Bit de inicio (LO) (siempre 1 solo bit)
  * Bits de datos (entre 5 y 8 bits)
  * Paridad (Par, Impar, Ninguna)
  * Bits de stop (HI) (1 ó 2 bits)
  * Marca (HI) (línea en reposo)
* Frecuencia de transmisión (Baud rate)
  * Baudios (velocidad bruta)
  * Bits por segundo (velocidad neta)

Este protocolo se basa en la transmision de una palabra, que se compone de un bit de inicio, los bits de datos, la paridad, los bits de stop y la marca.

### Cable null modem

Es un cable que se usa para conectar dos dispositivos que usan el protocolo RS232. Este cable se usa para conectar dos dispositivos que usan el protocolo RS232, y que se conectan directamente a traves de los cables TX y RX.

* Estándar RS232 diseñado para comunicar un DTE(Data Terminal Equipment) con un DCE (Data Communications Equipment).
* RS232C contempla la comunicación un DTE con otro a través de un cable “null modem”

### El harris 8250
Este tipo de controlador se usa para poder controlar la comunicacion de los dispositivos que usan el protocolo RS232.

* Controlador fabricado por Harris que cumple con las especificaciones del estándar RS232
* Algunos aspectos del estándar han sido interpretados de forma especial
* Se han añadido algunas funcionalidades
* Integrado típico en el IBM PC original
* Su evolución ha dado lugar a los 16450, 16550 (A y B), 16650 y 16750.

### Me he perdido en la clase asi que no hay mas contenido

---

## WiFi

El WIFI viene de "Wireless Fidelity" y es un metodo de comunicacion que se usa para la comunicacion de dispositivos de alta velocidad. Este metodo de comunicacion se basa en la comunicacion de dos dispositivos, que son el `router` y el `dispositivo`.

En wifi existen mejoras que fueron revisiones que se les asigno una letra, como la `a`, `b`, `g`, `n`.

La variante “a” usa la banda U-NII(Unlicensed National Information Infrastructure) que no precisa de licencia y es poco usada por otros dispositivos.

### Wifi 802.11a

Las frecuencias asignadas a la variante “a” de WiFi se encuentran alrededor de los 5 GHz, en la zona SHF (Super High Frequency) que abarca desde 3 GHz a 30 GHz.

En el rango de 5’25 a 5’35 GHz existen 12 canales de 20 MHz cada uno, de los cuales WiFi usa 8.

### Wifi 802.11b

Las frecuencias asignadas a la variante “b” de WiFi se encuentran alrededor de los 2’4 GHz, en la zona UHF (Ultra High Frequency) que abarca desde 300 MHz a 3 GHz.

En el rango de 2’4 a 2’4835 GHz existen 14 canales, de los cuales WiFi usa 11, pero solo tres de ellos simultáneamente, puesto que cada uno ocupa 25 MHz.

