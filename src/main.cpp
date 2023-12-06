#include <WiFi.h>

#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "GIGA SERVER";
const char* password = "123quatrocincoseis";

// Set web server port number to 80
AsyncWebServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output26State = "off";
String output27State = "off";

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  Serial.println();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.print("LETS GET IT, CONEXÃO ACONTECEU!!\n");
    request->send_P(200, "text/plain", "eae bobao kakakaka");
  });

  server.begin();
}

void loop(){

}

