// Define the pins
const int sensorPin = A0;
const int ledCool = 4; // Left LED
const int ledWarm = 3; // Middle LED
const int ledHot = 2;  // Right LED

void setup() {
  // Start the serial connection to the computer
  Serial.begin(9600);
  
  // Set the LED pins as outputs
  pinMode(ledCool, OUTPUT);
  pinMode(ledWarm, OUTPUT);
  pinMode(ledHot, OUTPUT);
}

void loop() {
  // 1. Read the analog value from the sensor (0-1023)
  int sensorVal = analogRead(sensorPin);
  
  // 2. Convert the reading to voltage
  float voltage = (sensorVal / 1024.0) * 5.0;
  
  // 3. Convert the voltage to temperature in Celsius
  // The TMP36 has a 500mV offset and 10mV/degree scale
  float temperatureC = (voltage - 0.5) * 100;
  
  // 4. Convert Celsius to Fahrenheit
  float temperatureF = (temperatureC * 9.0) / 5.0 + 32.0;
  
  // 5. Print the results to the Serial Monitor
  // Formatting to match the lab document: "25 C, 77 F"
  Serial.print(temperatureC, 0); // Print without decimals
  Serial.print(" C, ");
  Serial.print(temperatureF, 0);
  Serial.println(" F");
  
  // 6. Control the LEDs based on the temperature
  if (temperatureC >= 60.0) {
    // HOT: 60 C and above -> Turn on all 3 LEDs
    digitalWrite(ledCool, HIGH);
    digitalWrite(ledWarm, HIGH);
    digitalWrite(ledHot, HIGH);
  } 
  else if (temperatureC >= 50.0) {
    // WARM: 50 C to 59 C -> Turn on 2 LEDs
    digitalWrite(ledCool, HIGH);
    digitalWrite(ledWarm, HIGH);
    digitalWrite(ledHot, LOW);
  } 
  else {
    // COOL: 49 C and below -> Turn on 1 LED
    digitalWrite(ledCool, HIGH);
    digitalWrite(ledWarm, LOW);
    digitalWrite(ledHot, LOW);
  }
  
  // Wait a second before the next reading
  delay(1000);
}
