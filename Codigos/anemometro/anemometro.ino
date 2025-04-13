volatile unsigned long pulseCount = 0;

void setup() {
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), countPulse, RISING); // Flanco de subida
  Serial.begin(9600);
}

void loop() {
  Serial.print("Pulsos detectados: ");
  Serial.println(pulseCount);
  //delay(500); // Muestra cada 0.5 segundos
}

void countPulse() {
  pulseCount++;
}
