/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>
#include<SPI.h>
#include<SD.h>

const char* ssid = "it108";
const char* password = "ITCHURCH";
String pass = "12345";
bool debug = false;
int q[60][8];
int w[8];
int Num;
int n;
int Main = 0;
long last_got = 0;
const int PIN_CHIP_SELECT = 10;

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void listenCards(){
    if (!Serial.available() && millis() - last_got > 1000) {
        Num = 0;
        n = 0;
        if (Main == 1){
            Serial.print("!");
        }
        Main = 0;
        return;
    } else {
        Main = 1;
        int a = Serial.read();
        q[n][Num] = a;
        Num++;
        if (Num == 8) {
            n++;
            Num = 0;
        }
        last_got = millis();
    }
}

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
  if (debug){
    Serial.println("WiFi connected");
    //Serial.println(WiFi.macAddress());
  }

  // Start the server
  server.begin();
  if (debug) Serial.println("Server started");

  // Print the IP address
  if (debug){
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.macAddress());
  }
}

void loop() {
    listenCards();
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  // Wait until the client sends some data
  if (debug) Serial.println("new client");


  // Read the first line of the request
  String req = client.readStringUntil('\r');
  if (debug) Serial.println(req);
  client.flush();

  // Match the request
  int val;
  String megaReq;
  String freq;
  String resp;
  if (req.indexOf(pass + "/A") != -1 && req.indexOf("/E") != -1){
    val = 0;
    megaReq = req.substring(req.indexOf(pass + "/A")+ pass.length() + 2, req.indexOf("/E"));
    freq = megaReq;
    resp = "Request type - add|remove. Card is: " + freq;
     int fmas[8];
    if (debug) Serial.print("card ");
    String mReq = "~" + freq;
    Serial.print(mReq);
  }
  else if (req.indexOf(pass + "/R") != -1){
    resp = "/R... but i don't now what is it";
  }else if(req.indexOf(pass + "/B") != -1){
    resp = "<h3>Request type - show cards</h3>\r\n<br />\r\n<h2>Cards:</h2>\r\n<br />\r\n";
    for(int j = 0; j < 60; j++){
      if (q[j][0] == 0) break;
      for(int p = 0; p < 8; p++){
        resp += q[j][p];
        resp += " ";
      }
      resp += "\r\n<br />\r\n";
    }
  } else if(req.indexOf(pass + "/O") != -1){
    resp = "<h3>Request type - show cards</h3>\r\n<br />\r\n<h2>Cards:</h2>\r\n<br />\r\n";
    for(int j = 0; j < 60; j++){
      if (q[j][0] == 0) break;
      for(int p = 0; p < 8; p++){
        char temp = q[j][p];
        resp += temp;
      }
      resp += "\r\n<br />\r\n";
    }
  }
  else {
    if (debug) Serial.println("invalid request");
    val = -1;
    //client.stop();
    //return;
  }
  // Set GPIO2 according to the request
  digitalWrite(2, val);


  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  s += resp;
  s += "\r\n</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  if (debug) Serial.println("Client disonnected");

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed

}
