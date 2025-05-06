// Configuración global para contar pulsos (cada 2 pulsos = 1 vuelta)
volatile unsigned long pulseCount = 0;

// Función de interrupción para incrementar los pulsos
void countPulse() {
  pulseCount++;
}

class Viento {
  private:
    unsigned long sampleInterval;   // Intervalo de muestreo en milisegundos
    unsigned long gustInterval;     // Intervalo para calcular ráfaga máxima
    unsigned long lastSampleTime;   // Último tiempo de muestreo
    unsigned long lastGustTime;     // Último tiempo de ráfaga máxima
    float maxGustSpeed;             // Velocidad m\\'axima registrada en el intervalo

  public:
    // Constructor: recibe el tiempo de muestreo y el intervalo para ráfagas
    Viento(unsigned long sampleInt, unsigned long gustInt)
      : sampleInterval(sampleInt), gustInterval(gustInt),
        lastSampleTime(0), lastGustTime(0), maxGustSpeed(0) {}

    // Calcula la velocidad del viento a partir de un número de pulsos
    float calcularVelocidad(unsigned long pulses) {
      float circ_cm = 2 * 3.14159 * 9.0;            // Circunferencia del anemómetro (radio = 9 cm)
      float rotations = pulses / 2.0;                // Cada 2 pulsos equivale a una vuelta
      float distance_km = (circ_cm * rotations) / 100000.0;  // De cm a km
      float interval_sec = sampleInterval / 1000.0;   // Convertir intervalo a segundos
      float speed = (distance_km / interval_sec) * 3600.0;  // De km/s a km/h
      return speed * 1.18;                           // Factor de correcci\\'on
    }

    // Actualiza y muestra la velocidad en cada muestreo y la racha máxima en cada intervalo
    void actualizar() {
      unsigned long currentTime = millis();

      // Cada sampleInterval calcula la velocidad actual
      if (currentTime - lastSampleTime >= sampleInterval) {
        noInterrupts();
        unsigned long pulses = pulseCount;
        pulseCount = 0;
        interrupts();

        float speed = calcularVelocidad(pulses);
        Serial.print("Viento: ");
        Serial.print(speed);
        Serial.println(" km/h");

        // Actualiza la racha m\\'axima si corresponde
        if (speed > maxGustSpeed) {
          maxGustSpeed = speed;
        }
        lastSampleTime = currentTime;  
      }

      // Cada gustInterval muestra la racha m\\'axima y la reinicia
      if (currentTime - lastGustTime >= gustInterval) {
        Serial.print("Racha maxima: ");
        Serial.print(maxGustSpeed);
        Serial.println(" km/h");
        maxGustSpeed = 0;
        lastGustTime = currentTime;
      }
    }
};

Viento viento(5000, 60000);   // Tiempo de muestreo: 5000 ms, Intervalo de r\\'afaga: 60000 ms

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), countPulse, RISING);
}

void loop() {
  viento.actualizar();
}