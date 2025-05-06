# Tema 3
Proque se me ha borrar lo que he hecho, voy a saltarme parte de momento

## Entradas digitales
Las entradas digitales son señales que pueden tener dos valores: 0 o 1. Estas señales se pueden leer con el microcontrolador y se pueden utilizar para tomar decisiones en el programa.

Usamos pulsadores e interruptores para generar señales digitales. Los pulsadores son dispositivos que se accionan con la presión de un dedo y los interruptores son dispositivos que se accionan con un movimiento de palanca.

Para evitar rebotes se usa resistencias pull-op o pull-down. Las resistencias pull-up conectan la entrada digital a 5V y las resistencias pull-down conectan la entrada digital a GND.

Tambien usamos divisiores de tension para reducir la tension de entrada.

La ecuacion del divisor de tension es:
$$V_{out} = V_{in} \cdot \frac{R2}{R1+R2}$$

## Entradas analógicas

Las entradas analógicas son señales que pueden tener un rango de valores. Estas señales se pueden leer con el microcontrolador usando un conversor analógico-digital (ADC).

Para leer una señal analógica se usa la función `analogRead(pin)`. Esta función devuelve un valor entre 0 y 1023, que corresponde a un valor entre 0V y 5V.

### RAS

RAS: Conversor integrado por completo en el microcontrolador. Registros de configuración y conversión. Se puede configurar la resolución, la referencia y la velocidad de conversión.

Internamente se usa un sample hold el cual permite que la señal analógica se mantenga constante mientras se convierte a digital.

# Salidas
## Cargas resistivas e inductivas
Cuando tenenmos una carga y necesitamos controlarla con un microcontrolador, debemos tener en cuenta si es resistiva o inductiva.
Pocas cargas pueden conectarse directamente a un microcontrolador, ya que la corriente que pueden suministrar es muy baja. Por lo que necesitamos amplicarla.

Por lo cual se usa un transistor para controlar la carga. Los transistores son dispositivos que permiten controlar la corriente que circula por un circuito. Tambien llamado estructura Darlington.

Intrincicamente son dos transistores NPN en cascada (es decir la salida del primer transistor controla el segundo transistor). El transistor de la base es el que controla la corriente que circula por el circuito. Esto genera que las betas internamente se multipliquen dando lugar a que:
$$ I_{C_2} = \beta_2 (\beta_1 I_{b_1}) = \beta_1 \beta_2 I_{b_1}$$

## Cargas inductivas: Relé

Los relés son dispositivos que permiten controlar cargas inductivas. Un relé es un interruptor controlado por un electroimán. Cuando circula corriente por la bobina del relé, se genera un campo magnético que atrae una palanca que cierra el circuito.

* La bobina del relé pasa a ser la carga a controlar 
* Un diodo rectificador inversamente polarizado absorbe la fuerza contraelectromotriz
* El relé actúa como interruptor para activar y desactivar la carga
* No se puede usar PWM con un relé


### Ejemplo

Deseamos una corriente de 4mA en un circuito con una entrada de 4,9V seguido de una resistencia desconocidad en serie con una fuente de tension de 0.6V y en el final esta conectado a tierra.
¿Cual es la resistencia desconocida?

$$V_{in} = 4,9V $$
$$V_{out} = 0,6V$$
$$I = 4mA$$
$$V=IR$$
$$R = \frac{V}{I}=\frac{4,9v-0,6v}{4mA} = 1075 \Omega$$
Como queremos la menor corriente posible elegimos R = 1k

