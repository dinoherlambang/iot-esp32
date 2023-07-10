// https://globalstudio.center
// Learning Through Passion

void setup() {
    Serial.begin(115200);
    delay(1000); // Delay to launch the serial monitor
    Serial.println("ESP32 Touch Demo");
}

void loop() {
    Serial.println(touchRead(4));
    delay(500);
}
