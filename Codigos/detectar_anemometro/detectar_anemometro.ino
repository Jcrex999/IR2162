#include <TimerOne.h>

// Contadores volátiles para contar los pulsos del anemómetro
volatile int contador_viento = 0;
volatile int contador_viento_rafaga = 0;

// Función de interrupción para contar pulsos (cada pulso equivale a media vuelta)
void countPulse() {
  contador_viento++;
  contador_viento_rafaga++;
}

// Clase para calcular la velocidad del viento y las ráfagas
class VelocidadViento {
  public:
    float vel_med = 0; // Velocidad media del viento
    static float vel_max_racha_comparar;
    float vel_max_racha = 0;
    static int contador_num_rafagas;

    // Constructor: Inicializa TimerOne para medir ráfagas cada 5 segundos
    VelocidadViento() {
      Timer1.initialize(5000000); // 5 segundos en microsegundos
      Timer1.attachInterrupt(medir_rafaga);
    }

    // Rutina de interrupción que se ejecuta cada 5 segundos
    static void medir_rafaga() {
      // Usar una instancia temporal para llamar a calcular_velocidad
      VelocidadViento obj;
      // Calcular velocidad en km/h de la ráfaga actual (2 pulsos = una vuelta)
      float vel_rafaga = obj.calcular_velocidad(contador_viento_rafaga, 5);
      if (vel_rafaga > vel_max_racha_comparar) {
        vel_max_racha_comparar = vel_rafaga;
      }
      // Reinicia el contador de ráfagas
      contador_viento_rafaga = 0;
      // Incrementa número de ciclos medidos
      contador_num_rafagas++;
    }

    // Calcula la velocidad (km/h) a partir del contador de pulsos y el intervalo (segundos)
    float calcular_velocidad(int contador, int intervalo) {
      float circunferencia_cm = (2 * 3.14159) * 9.0; // Circunferencia en cm (radio = 9 cm)
      float rotaciones = contador / 2.0;             // 2 pulsos equivalen a una vuelta
      float dist_km = (circunferencia_cm * rotaciones) / 100000.0; // de cm a km
      float velocidad = (dist_km / intervalo) * 3600.0; // de km/s a km/h
      return velocidad * 1.18;                        // Factor de corrección
    }

    // Calcula la velocidad media del viento sobre todo el tiempo medido
    void calcular_velocidad_media() {
      int tiempo = contador_num_rafagas * 5;
      if (tiempo != 0)
        vel_med = calcular_velocidad(contador_viento, tiempo);
      else
        vel_med = 0;
    }

    // Reinicia contadores y actualiza la ráfaga máxima
    void reiniciar_valores() {
      contador_viento = 0;
      contador_num_rafagas = 0;
      vel_max_racha = vel_max_racha_comparar;
      vel_max_racha_comparar = 0;
    }

    // Devuelve la velocidad media formateada
    String get_vel_media() {
      return String(round(vel_med));
    }

    // Devuelve la velocidad máxima de ráfaga formateada
    String get_vel_max_racha() {
      return String(round(vel_max_racha));
    }
};

// Inicialización de miembros estáticos de la clase VelocidadViento
float VelocidadViento::vel_max_racha_comparar = 0;
int VelocidadViento::contador_num_rafagas = 0;

// Instancia global para el cálculo de velocidades
VelocidadViento vw;

void setup() {
  Serial.begin(2000000);
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), countPulse, RISING);
}

void loop() {
  // Calcula la velocidad media con base en los pulsos contados hasta el momento.
  vw.calcular_velocidad_media();

  // Envía por el Serial Monitor la velocidad media y la máxima ráfaga.
  Serial.print("Viento medio: ");
  Serial.print(vw.get_vel_media());
  Serial.print(" km/h, Racha máxima: ");
  Serial.print(vw.get_vel_max_racha());
  Serial.println(" km/h");

  delay(100);
}