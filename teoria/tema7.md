# Diseño de sotfware

## Introduccion

En este tema trabajaremos con el sistema operativo de los microcontroladores

## Device drivers

El hardware empotrado requiere de inicializacion y administracion de los dispositivos. Para ello se utilizan los controladores de dispositivo (device drivers). 
Los controladores de dispositivo son responsables de la inicializacion, configuracion y administracion de los dispositivos y permiten la comunicacion entre el sistema operativo y el hardware. 

Los device driver suelen ser necesarios en diversos puntos del sistema:

* Funciones especificas del procesador
* Memoria: Puede llegar a ser un gestor de memoria
* Inicializacion y transaccion del bus
* Inicializacion y transaccion de E/S
  * Redes
  * Graficos

Los device driver pueden ser:
* Especificos de un la aqrchitectura (procesador):
  * On-chip memory
  * Gestores de memoria integrados (MMUs)
  * Unidades en coma flotante
* Genericos: Dispositivos ubicados en la placa priincipal y no en el procesador
  * Buses: I2C, SPI, PCI, etc.
  * Off-chip memory

Los device driver soportan:
* Hardware startup / shutdown
* Hardware enable / disable
* Hardware acquire / release
* Hardware read / write
* Hardware install / uninstall

Estas funciones se basan en la percepcion que el software tiene del hardware. Puede estar:
* Inactivo: Desconectado, sin alimentacion, o desactivado
* Ocupado: Procesando informacion
* Finalizado: Reposo (acepta peticiones)

## Device drivers: Interrupciones
Las interrupciones son una forma de comunicacion entre el hardware y el software. Permiten al hardware notificar al software que ha ocurrido un evento.

Al menos las siguientes acciones son gestionadas por el device driver de interrupciones:
* Startup: Inicializa el hardware y lo prepara para recibir interrupciones
* Shutdown: Desactiva el hardware y lo prepara para ser desconectado
* Disable: Desactiva las interrupciones del hardware
* Enable: Activa las interrupciones del hardware
* Atencion: Gestiona la interrupcion y notifica al sistema operativo

La for en que las acciones del device driver se llevan a cabo depende de:
* El tipo, numero y prioridades de las interrupciones disponibles.
* El metodo de activacion de las interrupciones
* La estrategia de interrupcion de los componentes que las generan y los servicios que la CPU proporciona.

Hay tres tipos basicos de interrupciones:
* Software: Producidas internamente mediante la ejecucion de una instruccion (traps)
* Hardware internas: Producidas por un problema en la ejecucion del programa:
  * Operaciones matematicas ilegales (division por cero)
  * Depuracion
  * Opcodes incorrectos
  * Accesos ilegales a memoria
* Hardware externas: Producidas por dispositivos externos al CPU:
  * Dispositivos de E/S
  * Temporizadores
  * Errores de hardware
  * Fallos de alimentacion
  * Errores de memoria
  * Errores de bus
  * Errores de software

Para administrar la importancia de las interrupciones se suele emplear un esquema de prioridades.

Mientras se atiende una interrupcion de cierto nivel de prioridad, se enmascaran las de prioridad igual o inferior.

Existe un nivel de maxima prioridad, denominado Non Maskable Interrupt (NMI), que no puede ser enmascarado. Este nivel de interrupcion es utilizado para errores de hardware, como fallos de alimentacion o errores de memoria.

Aunque se suele implementar por hardware, la gestion de prioridades se realiza por software.

### Se me quedo algo por escribir y no lo guarde.

## Decive drivers: Memoria

Muchos microcontroladores tienen un controlador de memoria integrado (MMU) que permite acceder a la memoria de forma mas eficiente. La MMU se encarga de traducir las direcciones virtuales a fisicas y de gestionar la memoria virtual (mapa de memoria.

Mientras fisicamente la memoria consiste en una matriz bidimensional de celdas direccionadas por fila y columna, la MMU presenta una vista unidimensional de la memoria al software.

Cada celda del mapa de memoria contiene una fila de bytes cuyo número depende del tamaño del bus.

Cuando se referencia desde el software, lamemoria se conoce como memoria logica y su unidad es un byte.

El software debe proveer los mecanismos para que el procesador pueda acceder a cualquier elemento de la memoria.

Los device drivers se encargan de la coordinacion de las aciones entre el procesador y el hardware citado.

## Device drivers: Buses
Cada bus posee una serie de propiedades que hay que gestionar:
* Arbitraje: Protocolo que define como los dispositivos ganan acceso al bus.
* Handshaking: Protocolo a seguir para establecer comunicacion entre dispositivos.
* Sincronizacion: Protocolo para sincronizar la comunicacion entre dispositivos. Trasferencia de datos.

Las acciones que debe gestionar el driver son:
* Startup: Inicializa el bus y lo prepara para su uso
* Shutdown: Desactiva el bus y lo prepara para ser desconectado
* Enable: Activa el bus y lo prepara para su uso
* Disable: Desactiva el bus y lo prepara para ser desconectado
* Read: Lee datos del bus
* Write: Escribe datos en el bus
* Install: Instala el bus y lo prepara para su uso
* Uninstall: Desinstala el bus y lo prepara para ser desconectado

### Otra vez se me quedo algo por escribir y no lo guarde.

# Sistema operativo

El sistema operatovo es una parte opcional de la estructura del software de un sistema empotrado

Dependiendo de la complejidad, o implementacion, el SO puede sustentarse:
* Directamente en el hardware
* En la capa de device drivers
* En la capa BSP (Board Support Package)

Todo SO posee, al menos, un kernel que realiza las siguientes funciones:
* Administracion de procesos: Selecciona el proceso que despone de la CPU en cada instante.
* Administracion de memoria: Asigna y libera memoria a los procesos.

Atendiendo a su estructura, los OS se clasifican habitualmente en:
* Monoliticos: Todo el sistema operativo se ejecuta en modo kernel. 
  * Ventajas: Rapidez y eficiencia
  * Desventajas: Dificultad de mantenimiento y desarrollo
* Por capas: El sistema operativo se divide en capas, cada una de las cuales se encarga de una parte del sistema.
  * Ventajas: Facilidad de mantenimiento y desarrollo
  * Desventajas: Lentitud y complejidad
* Microkernel: El sistema operativo se divide en microkernels, cada uno de los cuales se encarga de una parte del sistema.
  * Ventajas: Facilidad de mantenimiento y desarrollo
  * Desventajas: Lentitud y complejidad

## Sistemas operativos Monoliticos
Son complicados de modificar y mantener, ya que cualquier cambio en una parte del sistema puede afectar a otras partes.

Una subcategoria son los monoliticos modularizados, compuestos de modulos mas facilmente modificables.

## Sistemas operativos por capas
Son mas faciles de modificar y mantener, ya que cada capa es independiente de las demas. Sin embargo, son menos eficientes y rapidos que los monoliticos.

Un solo ejecutable que incluye drivers y middleware.

En esta estructura entre mas acendemos en la jerarquia, mas general es el software.

## Sistemas operativos Microkernel
Son los mas faciles de modificar y mantener, ya que cada microkernel es independiente de los demas. Sin embargo, son los menos eficientes y rapidos.

Si solo implentan la gestion de procesos se denominan nanokernel.

## Sistemas operativos para sistemas empotrados

## Gestion de memoria
* El kernel administra la ejecución de los
procesos
* Debe ser capaz de cargar los procesos
* Como la memoria es compartida por los
procesos y el propio kernel, hay que
establecer mecanismos de protección
* Estos mecanismos son responsabilidad
del sistema de gestión de la memoria

### Gestion de memoria: Funciones
El sistema de gestion de memoria tiene varios puntos de vistaas:
* Desde el puno de vista del hardware:
  * Direccionamiento
  * Acceso a memoria
  * Proteccion
* Desde el punto de vista del software:

Algunas de las funciones pueden ser:
* Convertir entre direcciones de memoria física y direcciones de las tareas
* Determinar qué procesos cargar en el espacio
de memoria disponible
* Reservar y liberar memoria para los procesos: Son variaciones de las palabras
  * Alloc: Reservar memoria
  * Dealloc: Liberar memoria
* Soportar reserva y liberación de memoria dentro de los procesos (alloc y dealloc)
* Seguimiento del uso de la memoria
* Asegurar la coherencia de la cache
* Asegurar la protección de la memoria de los procesos: la cache determina el rendimiento del sistema
* Suelen establecerse dos niveles de ejecución en memoria dependiendo de las rutinas que se ejecuten:
  * Modo kernel: Tiene acceso a la memoria
  protegida. Es el sudo de linux
  * Modo usuario: Solo puede acceder a la
  memoria protegida mediante system calls,
  las rutinas de interfaz con niveles superiores
  del kernel. En este nivel se ejecutan el
  middleware y el software de aplicación

### Memoria de usuario
* El SO gestiona y realiza el swapping de
los procesos en memoria física
* Los fragmentos de memoria sustituidos
suelen ser
  * Segmentos: Porción de memoria ocupada
  por un proceso
  * Páginas: Porción de memoria de tamaño fijo
* Este esquema permite sentar la base de
la gestión de la memoria virtual

### Memoria de usario: Segmentacion
* Un proceso encapsula toda la información
involucrada en la ejecución de un programa
(código fuente, pila, datos, etc.)
* Cada una de esas porciones se denomina
segmento
* Cada dirección de un elemento en un segmento
tiene una dirección base (número de segmento) y
un offset interno (offset del segmento)
* Los segmentos poseen una propiedad de
accesibilidad:
  * Compartido: Otros procesos pueden acceder a él
  * Lectura/escritura
  * Solo lectura
* Los segmentos suelen dividirse en cinco tipos:
  * text: Contiene código fuente
  * data: Contiene variables inicializadas
  * bss (block started by symbol): Contiene variables sin
  inicializar
  * stack: Pila de datos del proceso
  * heap: Zona de reserva de memoria
* Los ejecutables suelen contener una cabecera
con información sobre los segmentos que los
componen
* El SO carga el proceso en memoria según la
estructura de la cabecera del ejecutable
* Los segmentos stack y heap son dinámicos (no
  se determinan en tiempo de compilación y
  pueden cambiar durante la ejecución)
* Un stack (pila) consta de direcciones contiguas
  donde se puede apilar (push) y desapilar (pop)
  información. Se usa para guardar información
  local y paso de parámetros a subrutinas
* Un heap consiste en bloques de memoria
  reservados en tiempo de ejecución y sirve para
  almacenar mayores cantidades de datos
* Los métodos típicos de reserva de memoria
  son:
  * FF (First Fit): Se busca desde el principio de la
  memoria el primer espacio suficientemente grande. En el primer hueco que encuentra es donde asigna la memoria
  * NF (Next Fit): A partir de la última reserva, se busca
  el siguiente espacio suficiente. 
  * BF (Best Fit): Se busca el espacio que más se
  adapta al solicitado en toda la memoria.
  * WF (Worst Fit): Se reserva en el hueco más grande.
  * QF (Quick Fit): Se mantiene una lista de espacios y
  se reserva el más ajustado al solicitado
  * Buddy System: Se reservan espacios que son
  potencias de 2 y luego se concatenan al liberarse. Esto permite que los bloques creados se puedan juntar entre si cuando se libere la memoria.
* Para la liberación de memoria se
  emplean dos estrategias:
  * Liberación por parte del proceso: El proceso
  es responsable de liberar la memoria
  reservada
  * Recolector de basura (garbage collector): El
  SO se encarga de revisar la memoria
  reservada por los procesos y liberar la que
  ya no está en uso
* La reserva y liberación de memoria puede ocasionar fragmentación.
* Hay tres tipos básicos de recolectores de
  basura:
  * Copying: Redistribuye la memoria reservada para
  evitar la fragmentación. Bloquea el sistema, ya que limpia la memoria y reorganiza los bloques
  * Mark and sweep: Marca los espacios reservados y
  libera el resto. No compacta. No bloqueante. Se
  puede combinar con un compactador (Mark and
  compact)
  * Generational: Organiza las zonas reservadas en
  generaciones, obviando la compactación de las más
  antiguas. Se combina con los anteriores para liberar
  y compactar.

### Memoria de usuario: Paginacion
* La paginación es un método de gestión de
  memoria que divide la memoria en páginas
  de tamaño fijo
* Algunos SO dividen la memoria lógica en
  páginas mapeadas sobre la memoria
  física dividida en frames
* La dirección de memoria lógica se
  compone entonces de un número de
  página y un offset
* Las páginas de un proceso pueden
  ubicarse en memoria en posiciones no
  consecutivas
* El SO mantiene una tabla de páginas
  que relaciona las páginas lógicas con las
  físicas

* Cuando una instrucción hace referencia a
  una posición de memoria no cargada, se
  produce un fallo de página
* El SO se encarga de localizar la página,
  actualizar las tablas y reejecutar la
  instrucción que causó el fallo de página.
  Esta operación se denomina swapping
* Para determinar qué páginas se expulsan
  al cargar las solicitadas existen varios
  algoritmos
  * Optimal: Páginas que no van a ser usadas en el futuro
  * Least recently used (LRU): Páginas menos usadas
  recientemente
  * FIFO: Páginas que hace más tiempo que se cargaron,
  independientemente del uso que tengan. Más simple que
  LRU pero menos eficiente
  * Not Recently Used (NRU): No usadas durante un
  determinado periodo de tiempo
  * Second Chance: Un bit se establece a “1” cada vez que
  se usa la página y a “0” si no se ha usado desde la última
  comprobación. Se expulsan las páginas marcadas con un
  “0”
  * Clock Paging: Igual que el anterior pero con una
  referencia temporal. Se expulsa la página que hace más
  tiempo que no se usa
* Se intenta reducir la posibilidad de que se
  produzca el **thrashing** (paliza) en que el sistema
  invierte más recursos en swapping que en la
  ejecución de los procesos
* Para evitarlo, el kernel confecciona un **working
  set** de cada proceso, conjunto de páginas que
  se mantienen siempre en memoria
* El grupo de páginas elegido depende del SO,
  pero suelen ser las más utilizadas
* Para prepaginar un proceso, el kernel debe
  poseer un modelo previo.

### Memoria de usuario: Memoria virtual
  * La paginación da lugar a la memoria
    virtual
  * Los procesos ven la memoria como un
    recurso continuo
  * Para el kernel la memoria se compone de
    fragmentos que pueden estar
    segmentados y paginados, segmentados
    y no paginados, no segmentados y
    paginados o no segmentados y no
    paginados

### Memoria de sistema: Kernel
* El espacio de memoria del kernel es la porción
  de memoria donde reside el código y datos del
  kernel
* Es accesible desde los niveles superiores a
  través de las **llamadas del sistema (system
  calls)**
* El código en esta zona de memoria se ejecuta
  en modo kernel o supervisor, frente al modo
  usuario en que se ejecuta el software de
  aplicación y algunos tipos de software del
  sistema
* En la zona del kernel se almacenan:
  * Estructuras de datos para el paso de
  mensajes entre procesos
  * Información de interrelaciones de ejecución
  entre procesos (fork, exec, spawn)
  * Process Control Block: Información para la
  administración de la ejecución de los
  procesos
  * Contexto de CPU de los procesos: Para
  permitir el swap

## Sistema de ficheros
* Algunos SO proporcionan soporte para un
  sistema de ficheros temporal o permanente en
  diversos dispositivos de memoria como Flash,
  RAM o disco duro.
* Un sistema de ficheros es un conjunto de
archivos junto con sus protocolos de gestión
* Los sistemas de ficheros son middleware y/o
software de aplicación que está montado
(instalado) en un punto de montaje (ubicación)
del dispositivo de almacenamiento
* Un kernel proporciona soporte a un sistema de
  ficheros para, como mínimo:
  * Mapear ficheros en el soporte
  * Primitivas para manipulación de ficheros y
  directorios:
    * Definiciones y atributos: Nombre, tipo (ejecutable, objeto,
    fuente, multimedia, etc.), tamaño, protección de acceso
    (lectura, escritura, ejecución, etc.), propiedad, etc.
    * Operaciones sobre ficheros: Crear, leer, escribir, abrir,
    cerrar, etc.
    * Modos de acceso: Secuencial, directo
    * Directorios: Creación, acceso, borrado
* En sistemas empotrados existe una capa de
  abstracción adicional que suministra acceso al
  hardware tanto al kernel como al software de
  alto nivel
* De esta forma, el usuario no puede acceder
  directamente a E/S, sino que debe hacerlo a
  través de las system calls, de la misma forma
  que al kernel
* El acceso a E/S es controlado por un driver
  genérico común a device drivers y a
  aplicaciones del usuario

### Rendimiento
* Los dos subsistemas que más afectan al
  rendimiento de un SO son el sistema de
  memoria (en particular la estrategia de
  swapping implementada) y el scheduler
* El rendimiento de la estrategia de
  swapping se mide contabilizando el
  número de fallos de página para un
  conjunto dado de referencias a memoria
* Los algoritmos se prueban con diferentes
  conjuntos de referencias
* Los indicadores del rendimiento del
  scheduler son:
  * Throughput: Número de procesos en
  ejecución en un momento dado
  * Execution time: Tiempo promedio que se
  tarda en ejecutar un proceso
  * Wait time: Tiempo total que un proceso debe
  esperar para ejecutarse
* Consiste en una capa de abstracción
  entre el SO y los device drivers
* Facilita la migración del SO a diferentes
  plataformas hardware
* Proporciona portabilidad run-time para el
  código compilado
* Contiene rutinas de inicialización y
  acceso a device drivers genéricos que
  ofrecen un API para niveles superiores de
  software (incluido el SO)

## Middleware y software de aplicación
* El middleware es un software que se
  encuentra entre el sistema operativo y el
  software de aplicación
* Es difícil diferenciar **middleware** de
  **software de aplicación**
* Middleware suele ser software de
  aplicación que se ha abstraído para pasar
  a formar parte de la capa superior del SO
* Se suele definir como el software que no
  está en el SO, drivers, kernel o software
  de aplicación
* Suele ser una capa que proporciona
  enlace entre el software de aplicación y el
  kernel o los drivers
* Evita repetir infraestructura que
  incrementaría el coste y la complejidad
  del software de aplicación
* En contrapartida se incrementa la carga
  de gestión, afecta a la escalabilidad y al
  rendimiento
* Adicionalmente, el middleware puede
  clasificarse en:
  * Propietario: Sujeto a una licencia que concede la
  entidad desarrolladora
  * Abierto (libre): Estandarizado por algún comité
  industrial y disponible para ser utilizado/licenciado
  por todos aquellos que lo deseen
* Algunos sistemas empotrados complejos
  contienen más de un producto middleware. En
  este caso se seleccionan a partir de su
  interoperabilidad.
* Aunque existen multitud de tipos de
  middleware, suelen agruparse en dos
  categorías:
  * Propósito general: Implementados en
  dispositivos genéricos. Networking, sistemas
  de ficheros, máquinas virtuales (JVM), etc.
  * Específicos: Implementados en
  determinados tipos de sistemas empotrados.
  Digital TV, comunicaciones, GPS, etc
* El software de aplicación se encuentra en la
  cúspide de la estructura de capas software del
  sistema
* Es dependiente de, administrado y ejecutado
por el software del sistema
* Contiene la(s) funcionalidad(es) que define(n)
el propósito del sistema empotrado
* Lleva a cabo la mayor parte de la interacción
con usuarios y administradores
* Al igual que el middleware, el software de
aplicación puede clasificarse en propósito
general y específico

## Implementacion y test
* Las últimas fases de producción de un
  sistema empotrado son la
  implementación y la prueba del mismo
* Normalmente, los sistemas empotrados
  requieren dos computadores para
  implementarse.
  * Target: Sistema a producir
  * Host: Computador de programación y
  prueba
* Las herramientas software presentes en
  el host se clasifican en:
   Utilidades: Editores de texto, gestores de
  versiones, grabadores de EPROM, etc.
  * Traducción: Preprocesadores, intérpretes,
  compiladores y linkers compatibles con el
  procesador del sistema target
  * Depuración: Herramientas de comprobación
  para monitorizar el funcionamiento del
  sistema target y corregir errores (bugs)
* Para el desarrollo del software del sistema
  empotrado se suele emplear un IDE (Integrated
  Development Environment) que consta de
  editor, compilador y depurador para la
  arquitectura elegida
* Para el hardware se emplea una aplicación de
  CAD (Computer Aided Design)
* También se usan simuladores como SPICE
  (Simulation Program with Integrated Circuits
  Emphasis) para poner a prueba el diseño sin
  coste en el espacio virtual antes de su
  implementación
* Muchos compiladores no proporcionan
  información suficiente al desarrollador sobre
  cómo se implementa el código de alto nivel en
  ensamblador
* Esto dificulta la toma de decisiones sobre la
  forma de programar para obtener código
  compacto y eficiente
* El compilador debe proporcionar:
  * Lista de tiempos estimados de ejecución de cada
  línea de código de alto nivel
  * Herramienta que muestre cada línea de código en
  su forma compilada (ensamblador producido)
  * Información sobre el espacio ocupado por el código
  y la memoria consumida por las subrutinas
* La fase de prueba consiste en someter al
  sistema a condiciones de uso normal
  para confirmar su fiabilidad y extremo
  para determinar sus límites
* Es similar a la fase de depuración
* Las pruebas se clasifican en:
  * Caja negra estática: 
  * Caja negra dinámica
  * Caja blanca estática
  * Caja blanca dinámica
* Las pruebas estáticas se llevan a cabo
  cuando el sistema no está en
  funcionamiento; las dinámicas cuando sí
  que lo está
* En las pruebas de caja negra (black box)
  el probador no tiene acceso al interior del
  sistema, mientras que en las pruebas de
  caja blanca (white box, clear box, glass
  box) sí lo tiene
* Determinados procedimientos en lo que a
  pruebas se refiere han sido desarrollados
  por estándares de pruebas y garantía de
  calidad, como ISO9000, CMM (Capability
  Maturity Model) o ANSI/IEEE 829
  Preparation, Running and Completion of
  Testing