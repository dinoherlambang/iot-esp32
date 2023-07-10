// https://globalstudio.center
// Learning Through Passion

#include <WiFi.h>
const char* ssid     = "PIDI 4.0";    // Enter ssid here
const char* password = "@industridigital4.0_oke";    // Enter password here      
WiFiServer server(80);                       // Web server port is set to 80
 
String header;                               // Variable to store the HTTP request
bool state=true;
String output5State = "off";                 // Auxiliar variables to store the current output state
const int output5 = 5;                       // Assign an Output variable to declare GPIO pins
int s1=0;
void setup() 
{
  Serial.begin(115200);
  pinMode(output5, OUTPUT);                   // Initialize the output variables as output
  digitalWrite(output5, LOW);                 // Set output pin to LOW
  Serial.print("Connecting to ");             // Connect to Wi-Fi network with SSID and password
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");                         // Print local IP address and start web server to Serial Monitor
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop()
{
  WiFiClient client = server.available();             // Listen for any incoming client
  s1=touchRead(T0);                                   // Read the touch GPIO state and save it to variable s1
  if(s1<30)                                           // then check the LED state to toggle LED
    {
      state=!state;                                   // Toggle LED state
      Serial.print("State: ");
      Serial.println(state);
      delay(500);
      digitalWrite(output5,state);                    // Write the state to the LED
    }
  if (client) 
  {                                                   // If a new client connects,
    Serial.println("New Client.");                    // print the message in the serial port
    String currentLine = "";                          // make a String to hold incoming data from the client
    while (client.connected())                        // loop while the client's connected
    {            
      if (client.available())                         // if there's bytes to read from the client,
      {             
        char c = client.read();                       // read a byte, then
        Serial.write(c);                              // print it out the serial monitor
        header += c;
        if (c == '\n')                                // if the byte is a newline character
        {                                                                                  
          if (currentLine.length() == 0)              // if the current line is blank, you got two newline characters in a row.
          {                                           // that's the end of the client HTTP request, so send a response:
            client.println("HTTP/1.1 200 OK");        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            client.println("Content-type:text/html"); // and a content-type so the client knows what's coming, then a blank line:
            client.println("Connection: close");
            client.println(); 
            if (header.indexOf("GET /H") >= 0)        // turns the GPIOs on and off
            {
              state=!state;
              digitalWrite(output5, state);
              if(state==true)
              {
                Serial.println("GPIO 5 on");
                output5State = "on";
              }
              else if(state==false)
              {
                Serial.println("GPIO 5 off");
                output5State = "off";
              }
            }
            client.println("<!DOCTYPE html><html>");                                                                                     // Display the HTML web page
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");       // CSS to style the on/off buttons 
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            client.println("<body><h1>ESP32 with Touch</h1>");                                                 // Web Page Heading  
            client.println("<p>Light is " + output5State + "</p>");                                            // Display current state, and ON/OFF buttons for GPIO 5       
            if (output5State=="off")                                                                           // If the output5State is off, it displays the ON button
            {  
              client.println("<p><a href=\"/H\"><button class=\"button\">ON</button></a></p>");
            } 
            else 
            {
              client.println("<p><a href=\"/H\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            client.println();                                                  // The HTTP response ends with another blank line
            break;                                                             // Break out of the while loop
          } 
          else 
          { 
            currentLine = "";                                                  // if you got a newline, then clear currentLine
          }
        } 
        else if (c != '\r')                                                    // if you got anything else but a carriage return character,
        {  
          currentLine += c;                                                    // add it to the end of the currentLine
        }
      }
    }
    header = "";                                                               // Clear the header variable
    client.stop();                                                             // Close the connection
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
