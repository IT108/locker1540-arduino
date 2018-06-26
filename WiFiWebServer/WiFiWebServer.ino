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
bool debug = true;
int q[60][8];
int w[8];
int Num;
int n;
int Main;
const int PIN_CHIP_SELECT = 10;

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void initCards(){
  int i = 0;
  int j = 0;
  int a;
  File cards = SD.open("CARDS.txt");
    if (cards) {
      while (cards.available()) {
        for (int f = 0; f < 8; f++){
          a = cards.read();
          q[i][f] = a;

          if (debug){
            Serial.print(q[i][f]);
            Serial.print(" ");
          }
        }
        i++;
        cards.seek(i*10);
        if (debug) Serial.println();
      }
      n = i;
    }
    cards.close();
}

void writeNew(int w[]){
  for (int i = 0; i < 8; i++){
    q[n][i] = w[i];
  }
  n++;
  SD.remove("CARDS.txt");
  File cards = SD.open("CARDS.txt",FILE_WRITE);
  if (cards) {
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < 8; j++) {
        byte f = q[i][j];
        cards.write(f);
      }
      cards.println();
    }
  }
  cards.close();
  initCards();
}

void del(int idx){
  for (size_t i = idx; i < n; i++) {
    renameC(i, i + 1);
  }     
  n--;
  SD.remove("CARDS.txt");
  File cards = SD.open("CARDS.txt",FILE_WRITE);
  if (cards) {
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < 8; j++) {
        byte f = q[i][j];
        cards.write(f);
      }
      cards.println();
    }
  }
  cards.close();
  initCards();
}

void renameC(int idx1, int idx2){
  for (size_t i = 0; i < 8; i++) {
    q[idx1][i] = q[idx2][i];
  }
}

bool checkCard(int a[], int b[]){
    for(int i = 0; i < 8; i++){
        if(a[i] != b[i]){
            return false;
        }
    }
    return true;
}

int _find(int a[]){
    for(int i = 0; i < 60; i++){
        if(checkCard(q[i], a)){
            return i;
        }
    }
    return -1;
}

void checkFind(int w[]){
  int idx = _find(w);
  if(idx == -1){
    if (debug) Serial.println("write");
    writeNew(w);
  } else {
    if (debug) Serial.println("del");
    del(idx);
  }
   if (debug) Serial.print(" OK");
}

void checkDB(){
  if (!Serial.available()) {
    Num = -1;
    Main = -1;
    return;
  } else {
    int a = Serial.read();
    //Serial.println(a);
    if (a == 126 || a == 124){
      Main = a;
      Num = 0;
      if (debug) Serial.println(Main);
    }
    if (Main == 126){
      if (Num > -1 && a != Main) {
        if (debug){
          Serial.print(a);
          Serial.print(" ");
        }
        w[Num] = a;
        Num++;

        if (Num == 8) {
          checkFind(w);
        }
      }
    } else if (Main == 124){
      if (debug) {
        Serial.print(a);
        Serial.print(" ");
      }
      if (Num > -1 && a != Main) {
        w[Num] = a;
        Num++;
        if (Num == 8){
          if (_find(w) != -1) {
            Serial.print("Y");
          } else {
            Serial.print("N");
          }
        }
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);
  if (!SD.begin(PIN_CHIP_SELECT)) {
      if (debug) Serial.println("Card failed, or not present");
      // Если что-то пошло не так, завершаем работу:
      //return;
    }
    if (debug) Serial.println("card initialized.");
    initCards();
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
    checkDB();
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
    Serial.print("card ");
    for (size_t i = 0; i < 8; i++) {
      fmas[i] = freq.charAt(i);
      if (debug) {
        Serial.print(fmas[i]);
        Serial.print(" ");
      }
    }
    checkFind(fmas);
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
