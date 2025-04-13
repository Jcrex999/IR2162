#include <TimerOne.h>

// Global counters to count wind pulses
volatile int contador_viento = 0;
volatile int contador_viento_rafaga = 0;

// Class to calculate wind speed and gusts
class VelocidadViento {
  public:
    float vel_med = 0;      // Wind average speed
    static float vel_max_racha_comparar;  // Used to compare and store maximum gust speed
    float vel_max_racha = 0;              // Maximum gust speed
    static int contador_num_rafagas;      // Number of 5-second cycles

    // Constructor: initializes TimerOne to measure gusts every 5 seconds
    VelocidadViento() {
      Timer1.initialize(5000000); // 5 seconds in microseconds
      Timer1.attachInterrupt(medir_rafaga); // Attach the interrupt to medir_rafaga()
    }

    // Interrupt routine called every 5 seconds
    static void medir_rafaga() {
      // Create temporary instance to use non-static method calcular_velocidad
      VelocidadViento obj;
      // Calculate gust speed for the current 5-second interval
      float vel_rafaga = obj.calcular_velocidad(contador_viento_rafaga, 5);
      // Update maximum gust speed if current gust is higher
      if (vel_rafaga > vel_max_racha_comparar) {
        vel_max_racha_comparar = vel_rafaga;
      }
      // Reset the gust counter
      contador_viento_rafaga = 0;
      // Increment the cycle counter
      contador_num_rafagas++;
    }

    // Calculate wind speed (km/h) given pulse count and interval (seconds)
    float calcular_velocidad(int contador, int intervalo) {
      float circunferencia_cm = (2 * 3.14159) * 9.0;  // Circle circumference in cm (with sensor radius = 9 cm)
      float rotaciones = contador / 2.0;              // Two pulses equal one full rotation
      float dist_km = (circunferencia_cm * rotaciones) / 100000.0;  // Convert distance to km
      float velocidad = (dist_km / intervalo) * 3600.0; // Convert km/s to km/h
      float velocidad_real = velocidad * 1.18;          // Apply correction factor
      return velocidad_real;
    }

    // Calculate the overall average wind speed using all pulses and cycles
    void calcular_velocidad_media() {
      int tiempo = contador_num_rafagas * 5;  // Total measured time in seconds
      if (tiempo != 0)
        vel_med = calcular_velocidad(contador_viento, tiempo);
      else
        vel_med = 0;
    }

    // Reset values after a measurement cycle; also updates the maximum gust speed
    void reiniciar_valores() {
      contador_viento = 0;
      contador_num_rafagas = 0;
      vel_max_racha = vel_max_racha_comparar;
      vel_max_racha_comparar = 0;
    }

    // Return the formatted average wind speed
    String get_vel_media() {
      return String(round(vel_med));
    }

    // Return the formatted maximum gust speed
    String get_vel_max_racha() {
      return String(round(vel_max_racha));
    }
};

// Initialize static class members
float VelocidadViento::vel_max_racha_comparar = 0;
int VelocidadViento::contador_num_rafagas = 0;

// Create an instance of the wind speed class
VelocidadViento vw;

// Global flag to track the previous state of the sensor
bool lastState = false; // false means not currently in impulse range

void setup() {
  Serial.begin(2000000);         // Initialize serial communication
  pinMode(A4, INPUT);             // Configure analog pin A4 for anemometer data
}

void loop() {
  int sensorValue = analogRead(A4);  // Read analog value from the anemometer sensor

  // Detect transition: only count pulse when going from no impulse to impulse state.
  // If the sensor reading is 250 or above, assume an impulse.
  if (sensorValue >= 250) {
    if (!lastState) {
      // Rising edge detected: increment both total and gust pulse counters
      contador_viento++;
      contador_viento_rafaga++;
      lastState = true;  // Set flag to indicate impulse state is active
    }
  } else {
    // Sensor value below threshold, reset state to allow new impulses
    lastState = false;
  }

  // Calculate the average wind speed based on counted pulses and elapsed time
  vw.calcular_velocidad_media();

  // Send the sensor reading, average wind speed, and gust speed to the Serial Plotter
  Serial.print("Anemometer: ");
  Serial.print(sensorValue);
  Serial.print("\tWind Avg: ");
  Serial.print(vw.get_vel_media());
  Serial.print(" km/h, Gust: ");
  Serial.print(vw.get_vel_max_racha());
  Serial.println(" km/h");

  delay(100); // 100ms delay between readings
}