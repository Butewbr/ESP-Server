#include <WiFi.h>
#include <Arduino.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char *ssid = "GIGA SERVER";
const char *password = "123quatrocincoseis";

void listenServer(void *parameter);
void printMessage(void *parameter);

// Set web server port number to 80
WiFiServer server(80);
SemaphoreHandle_t mutex;

void setup()
{
    Serial.begin(115200);
    Serial.println();

    // Setting the ESP as an access point
    Serial.print("Setting AP (Access Point)...\n");
    // Remove the password parameter, if you want the AP (Access Point) to be open
    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    Serial.print("Inicializando servidor...\n");
    server.begin();

    Serial.print("Mutex sendo criado...\n");
    mutex = xSemaphoreCreateBinary();

    Serial.print("Criando tarefa listenServer...\n");
    xTaskCreate(listenServer, "listenServer", 10000, NULL, 2, NULL);
    xTaskCreate(printMessage, "printMessage", 10000, NULL, 2, NULL);

    // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    //     Serial.print("Conexão GET recebida.\n");
    //     request->send_P(200, "text/plain", "eae bobao kakakaka");
    //     // xSemaphoreGive(mutex);
    // });

    // server.on("/", HTTP_POST, [](AsyncWebServerRequest *request){
    //     if (request->hasParam("body", true)) {
    //         AsyncWebParameter* p = request->getParam("body", true);
    //         String message = p->value();
    //         Serial.print(message); // Print the message from the POST request
    //     }
    //     Serial.print("Conexão POST recebida.\n");
    //     request->send(200, "text/plain", "RECEBI VEI!!!");
    // });
}

void listenServer(void *parameter) {
    for(;;) {
        WiFiClient client = server.available();
        Serial.print("Aguardando um cliente...\n");
        
        if(client && client.connected()) {
            char c = client.read();

            client.print(200);
            
            client.stop();
            xSemaphoreGive(mutex);
        }
        vTaskDelay(1000);
    }
}

void printMessage(void *parameter) {
    for(;;) {
        xSemaphoreTake(mutex, portMAX_DELAY);
        Serial.print("Conexão Recebida.\n");
    }
}

void loop()
{
}
