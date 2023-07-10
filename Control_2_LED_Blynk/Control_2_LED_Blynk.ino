// https://globalstudio.center
// Learning Through Passion


// Declaration
// -----

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
#define BLYNK_TEMPLATE_ID "TMPL6STWmjAON"
#define BLYNK_TEMPLATE_NAME "Control 2 LED"
#define BLYNK_AUTH_TOKEN "EpFR_7p-YFfKoumXF6vMrkKD9VFY3f04"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
char ssid[] = "PIDI 4.0";
char pass[] = "@industridigital4.0_oke";

int D5 = 16;
int D6 = 17;


// Algoritm
// -----

BLYNK_WRITE(V0)
{
  int value1 = param.asInt();
  digitalWrite(D5,value1);
}

BLYNK_WRITE(V1)
{
  int value2 = param.asInt();
  digitalWrite(D6,value2);
}

void setup()
{
  Serial.begin(9600);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  delay(1000);
  Blynk.begin(auth,ssid,pass);
}

void loop()
{
  Blynk.run();
}
