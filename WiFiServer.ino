#include <DHT.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char* ssid = "VIVOGTW-2.4";
const char* password = "MckonohatroN352";

WebServer server(80);

#define DHTPIN 28
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float umi = 0;
float temp = 0;

void setup() {
  
  Serial.begin(115200);
  dht.begin();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Espera conexão wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", handleRoot);
  server.begin();
  Serial.println ( "HTTP server started" );
  
}

void loop() {

  umi = dht.readHumidity();
  temp = dht.readTemperature();

  server.handleClient();
  /*
  if (isnan(umi) || isnan(temp)) {
    Serial.println("Falha de leitura");
  } else {
    Serial.print("Umidade: ");
    Serial.print(umi);
    Serial.print("%  Temperatura: ");
    Serial.print(temp);
    Serial.println("°C, ");
  }
  */
  delay(100);
}

void handleRoot() {
  server.send ( 200, "text/html", getPage() );
}


String getPage() {
  String page = "<html lang=en-EN><head><meta http-equiv='refresh' content='5'/>";
  page += "<title>RPI Pico W WebServer FunBots</title>";
  page += "<style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }</style>";
  page += "</head><body><h1>RPI Pico W WebServer FunBots</h1>";
  page += "<h3>Sensor DHT11</h3>";
  page += "<li>Temperaturedrga: ";
  page += analogReadTemp();
  page += "&deg;C</li></ul>";
  page += "</body></html>";
  return page;
}
