#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char *ssid = "WIFI_SSID";
const char *password = "WIFI_PASSWORD";
String serverName = "http://IP_ADDRESS/api/temphum";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
    dht.begin();
}

void loop()
{

    if ((millis() - lastTime) > timerDelay)
    {

        if (WiFi.status() == WL_CONNECTED)
        {
            WiFiClient client;
            HTTPClient http;
            float h = dht.readHumidity();

            float t = dht.readTemperature();
            String serverPath = serverName + "/" + String(t) + "/" + String(h) + "/1";

            http.begin(client, serverPath.c_str());

            int httpResponseCode = http.GET();

            if (httpResponseCode > 0)
            {
                Serial.print("HTTP Response code: ");
                Serial.println(httpResponseCode);
                String payload = http.getString();
                Serial.println(payload);
            }
            else
            {
                Serial.print("Error code: ");
                Serial.println(httpResponseCode);
            }
            http.end();
        }
        else
        {
            Serial.println("WiFi Disconnected");
        }
        lastTime = millis();
        delay(10000);
    }
}