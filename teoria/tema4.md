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


