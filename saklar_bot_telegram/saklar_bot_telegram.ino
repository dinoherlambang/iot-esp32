// https://globalstudio.center
// Learning Through Passion

#include "CTBot.h"
CTBot myBot;

String ssid = "Redmi";      // Enter ssid with your WiFi Network Name
String pass = "Galang@35";   // Enter password with your WiFi Network Password
String token = "5636831270:AAFBDs6iknnZ2h2d2LqUj2L2J5WNlVVq8gc";  // Enter token created by Telegram

const int BUILTIN_LED = 2;

void setup() {
  Serial.begin(9600);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
  Serial.println("Starting TelegramBot...");

  if (myBot.wifiConnect(ssid, pass))
    Serial.println("\nOK wifi");
  else
    Serial.println("\nnot OK wifi");

  myBot.setTelegramToken(token);

  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");
}

void loop() {
  TBMessage msg;
  if (myBot.getNewMessage (msg)) {
    if (msg.text.equalsIgnoreCase("LIGHT ON")) {
      digitalWrite(BUILTIN_LED, HIGH);
      myBot.sendMessage (msg.sender.id, "Light is now ON");
    }
    else if (msg.text.equalsIgnoreCase("LIGHT OFF")) {
      digitalWrite(BUILTIN_LED, LOW);
      myBot.sendMessage(msg.sender.id, "Light is now OFF");
    }
    else {
      String reply;
      reply = (String)"Welcome " + msg.sender.username + (String)". Try LIGHT ON or LIGHT OFF.";
      myBot.sendMessage(msg.sender.id, reply); 
    }
  }
  delay(500);
}
