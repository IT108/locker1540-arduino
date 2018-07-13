#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>

#include<SPI.h>
#include<SD.h>
#include<Ethernet.h>
//Serial defines
#define LockerSerial Serial3
#define DebugSerial Serial
//Server variables
String pass = "12345";
byte mac[] = { 0xA0, 0x20, 0xA6, 0x21, 0xBB, 0xF5 };
IPAddress ip(192, 168, 1, 38);
EthernetServer server(80);
String showCardsReq = "/O";
String showCardsBytesReq = "/B";
String addRemoveCardReq = "/A";
String getAllCards = "/GC";
String HTTPHead = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
String HTTPEnd = "\r\n</html>\n";
String HTTPNextLine = "\r\n<br />\r\n";
String HTTPOpenTable = "\r\n<table border=1 align=\"left\" cellpadding=0 cellspacing=0>\r\n<tr><td>";
String HTTPNextTableCell = "</td><td>";
String HTTPNextTableRow = "</td></tr>\r\n<tr><td>";
String HTTPCloseTable = "</td></tr>\r\n</table>";
//System variables
bool debug = true;
int q[60][8];
int w[8];
int Num;
int n;
int Main;
int w2[8];
int Num2;
int Main2;
const int PIN_CHIP_SELECT = 22;
const int symbolWrite = 1;
const int symbolDel = 2;
String cardsFileName = "CARDS.txt";

void initCards(){
  int i = 0;
  int j = 0;
  int a;
  File cards = SD.open(cardsFileName);
    if (cards) {
      while (cards.available()) {
        for (int f = 0; f < 8; f++){
          a = cards.read();
          q[i][f] = a;

          if (debug){
            DebugSerial.print(q[i][f]);
            DebugSerial.print(" ");
          }
        }
        i++;
        cards.seek(i*10);
        if (debug) DebugSerial.println();
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
  SD.remove(cardsFileName);
  File cards = SD.open(cardsFileName,FILE_WRITE);
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
  SD.remove(cardsFileName);
  File cards = SD.open(cardsFileName,FILE_WRITE);
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

int checkFind(int w[]){
  int res = 0;
  int idx = _find(w);
  if(idx == -1){
    if (debug) DebugSerial.println("write");
    res = symbolWrite;
    writeNew(w);
  } else {
    if (debug) DebugSerial.println("del");
    res = symbolDel;
    del(idx);
  }
   if (debug) DebugSerial.print(" OK");
   return res;
}

void checkDB(){
  if (!LockerSerial.available()) {
    Num = -1;
    Main = -1;
    return;
  } else {
    int a = LockerSerial.read();
    //LockerSerial.println(a);
    if (a == 126 || a == 124){
      Main = a;
      Num = 0;
      if (debug) DebugSerial.println(Main);
    }
    if (Main == 126){
      if (Num > -1 && a != Main) {
        if (debug){
          DebugSerial.print(a);
          DebugSerial.print(" ");
        }
        w[Num] = a;
        Num++;

        if (Num == 8) {
          checkFind(w);
        }
      }
    } else if (Main == 124){
      if (Num > -1 && a != Main) {
        w[Num] = a;
        if (debug) {
        DebugSerial.print(w[Num]);
        DebugSerial.print(" ");
      }
        Num++;
        if (Num == 8){
          if (_find(w) != -1) {
            LockerSerial.print("Y");
          } else {
            LockerSerial.print("N");
          }
        }
      }
    }
  }
}

void webServer(){ 
  bool sys = false;
  String sysresp = "";
    // Check if a client has connected
  EthernetClient client = server.available();
  if (!client) {
    return;
  }
    if (debug) DebugSerial.println("new client");
  while(!client.available()){
    delay(1);
    }
  // Wait until the client sends some dat


  // Read the first line of the request
  String req = client.readStringUntil('\r');
  if (debug) DebugSerial.println(req);
  client.flush();

  // Match the request
  String freq;
  String resp;
  if (req.indexOf(pass + addRemoveCardReq) != -1){
    freq = req.substring(req.indexOf(pass + addRemoveCardReq)+ pass.length() + 2, req.indexOf(pass + addRemoveCardReq)+ pass.length() + 10);
    resp = "Request type - add|remove. Card is: " + freq;
     int fmas[8];
    if (debug) Serial.print("card ");
    for (size_t i = 0; i < 8; i++) {
      fmas[i] = freq.charAt(i);
      if (debug) {
        Serial.print(fmas[i]);
        Serial.print(" ");
      }
    }
      int status = checkFind(fmas);
      switch (status) {
        case symbolWrite:
        resp += HTTPNextLine;
        resp += "Card successfully added!";
        break;
        case symbolDel:
        resp += HTTPNextLine;
        resp += "Card successfully removed!";
        break;
      }
  }else if(req.indexOf(pass + showCardsBytesReq) != -1){
    resp = "<h3>Request type - show cards</h3>\r\n";
    resp += "<br />\r\n<h2>Cards:</h2>\r\n<br />\r\n";
    resp += HTTPOpenTable;
    for(int j = 0; j < 60; j++){
      if (q[j][0] == 0) break;
      resp += j + 1;
      resp += ".  ";
      resp += HTTPNextTableCell;
      for(int p = 0; p < 8; p++){
        resp += q[j][p];
        resp += " ";
      }
      resp += HTTPNextTableRow;
    }
    resp += HTTPCloseTable;
  } else if(req.indexOf(pass + showCardsReq) != -1){
    resp = "<h3>Request type - show cards</h3>\r\n<br />\r\n<h2>Cards:</h2>\r\n<br />\r\n";
    resp += HTTPOpenTable;
    for(int j = 0; j < 60; j++){
      if (q[j][0] == 0) break;
      resp += j + 1;
      resp += ".  ";
      resp += HTTPNextTableCell;
      for(int p = 0; p < 8; p++){
        char temp = q[j][p];
        resp += temp;
      }
      resp += HTTPNextTableRow;
    }
    resp += HTTPCloseTable;
  } else if (req.indexOf(pass + getAllCards) != -1){
    sys = true;
    for (int j = 0; j < 60; j++){
      if (q[j][0] == 0) break;
      for (int p = 0; p < 8; p++){
        char temp = q[j][p];
          sysresp += temp;
        }
        sysresp += ";";
      }
  } else {
    if (debug) Serial.println("invalid request");
    resp = "<h5>INVALID REQUEST</h5>";
  }
  // Set GPIO2 according to the reques
  client.flush();

  // Prepare the response
  String s = HTTPHead;
  if (sys) s += sysresp;
  else s += resp;
  s += HTTPEnd;

  // Send the response to the client
  client.print(s);
  delay(1);
  client.stop();
  if (debug) Serial.println("Client disonnected");

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed

}


void setup(){
    DebugSerial.begin(115200);
    LockerSerial.begin(115200);
    delay(20);
    if (!SD.begin(PIN_CHIP_SELECT)) {
        if (debug) DebugSerial.println("Card failed, or not present");
        //return;
      }
    if (debug) DebugSerial.println("card initialized.");
    initCards();
    Ethernet.begin(mac);
    server.begin();
    DebugSerial.print("server is at ");
    DebugSerial.println(Ethernet.localIP());
}

void loop(){
    checkDB();
    webServer();
}

