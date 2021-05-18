#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
 
const char* ssid = "ilelio"; // SSID use the name of your network
const char* password = "lab@homepax55"; // password of your network
 
ESP8266WebServer server(80); // port of the server  
void setup(void)

{
 Serial.begin(115200);
 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password);
 Serial.println("");
 
 // Wait for connection
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
 
 server.on("/inline", []() {
 server.send(200, "text/plain", "this works as well");
 });
 
 server.onNotFound(handleNotFound);
 
 server.begin();
 Serial.println("HTTP server started");
}
 
void loop(void) 
{
 server.handleClient();
 
}
 
 
 
void handleRoot() 
{
 
 server.send(200, "", "<h1 style=\"color: #0099e5;\">Gretting from ESP8266 Yeaah!!</h1>\n<hr style=\"border: 1px solid #ff4c4c;\">\n<p>Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod\ntempor incididunt ut labore et dolore magna aliqua. </p>");
 
}
 
void handleNotFound()
{
 
 String message = "File Not Found\n\n";
 message += "URI: ";
 message += server.uri();
 message += "\nMethod: ";
 message += (server.method() == HTTP_GET) ? "GET" : "POST";
 message += "\nArguments: ";
 message += server.args();
 message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
 message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
 }
 server.send(404, "text/plain", message);
 
}
