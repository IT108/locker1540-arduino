/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>

const char* ssid = "it";
const char* password = "itchurch";
String pass = "12345";
bool debug = false;

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
  
  // Connect to WiFi network
  if(debug)Serial.println();
  if(debug)Serial.println();
  if (debug) Serial.print("Connecting to ");
  if (debug) Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (debug) Serial.print(".");
  }
  if (debug) Serial.println("");
  if (debug) Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  if (debug) Serial.println("Server started");

  // Print the IP address
  if (debug) Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  if (debug) Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  if (debug) Serial.println(req);
  client.flush();
  
  // Match the request
  int val;
  String megaReq;
  if (req.indexOf(pass + "/A") != -1 && req.indexOf("/E") != -1){
    val = 0;
    megaReq = req.substring(req.indexOf(pass + "/A")+ pass.length() + 1, req.indexOf("/E"));
  }
  else if (req.indexOf(pass + "/R") != -1){
    val = 1;
    megaReq =pass + "/O";
  }
  else {
    if (debug) Serial.println("invalid request");
    val = -1;
    //client.stop();
    //return;
  }
  // Set GPIO2 according to the request
  digitalWrite(2, val);
  Serial.print("~" + megaReq);
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nRequest status - ";
  s += val;
  s += " Generated message - " + megaReq;
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  if (debug) Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

