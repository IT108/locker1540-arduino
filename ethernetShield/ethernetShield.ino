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
String addCardReq = "/A";
String removeCardReq = "/R";
String nameSymbol = "/N";
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
const int symbolExist = 1;
const int symbolNotExist = -1;
const int cardsSeparator = 59;
const int nameSeparator = 47;
String cardsFileName = "CARDS.txt";
String fullDBFileName = "CardsDB.txt";
String tmpFileName = "TmpFile.txt";

class card_pair{
public:
    int card[8];
    String name;
};

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

void writeNew(card_pair w){
  for (int i = 0; i < 8; i++){
    q[n][i] = w.card[i];
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
  writeToFullDB(w);
}

void writeToFullDB(card_pair card){
    File cards = SD.open(fullDBFileName,FILE_WRITE);
    byte f;
    if (cards) {
      for (size_t i = 0; i < 8; i++) {
          f = card.card[i];
          cards.write(f);
      }
      f = '/';
      cards.write(f);
      for (size_t i = 0; i < card.name.length(); i++) {
          f = card.name.charAt(i);
          cards.write(f);
      }
      f = ';';
      cards.write(f);
    }
    cards.close();
}

void delFromFullDB(card_pair card){
    File DB = SD.open(fullDBFileName);
    File tmpFile = SD.open(tmpFileName, FILE_WRITE);
    if(DB){
        bool found = false;
        while (DB.available()) {
            int a = DB.read();
            if (a == cardsSeparator){
                if (DB.available()) {
                    int tmpCard[8];
                    for (size_t i = 0; i < 8; i++) {
                        tmpCard[i] = DB.read();
                    }
                    if (checkCard(tmpCard, card.card)) {
                        found = true;
                    } else {
                        byte f;
                        for (size_t i = 0; i < 8; i++) {
                            f = tmpCard[i];
                            tmpFile.write(f);
                        }
                        f = nameSeparator;
                        tmpFile.write(f);
                    }
                }
            } else if (a == nameSeparator && found){
                int temp = DB.read();
                while (temp != cardsSeparator) {
                    temp = DB.read();
                }
                found = false;
            } else if (a == nameSeparator){
                int temp = DB.read();
                byte f;
                while (temp != cardsSeparator) {
                    f = temp;
                    tmpFile.write(f);
                    temp = DB.read();
                }
                f = cardsSeparator;
                tmpFile.write(f);
            }
        }
        DB.close();
        tmpFile.close();
        copyTmpToDB();
    }
}

void copyTmpToDB(){
    SD.remove(fullDBFileName);
    File DB = SD.open(fullDBFileName,FILE_WRITE);
    File tmpFile = SD.open(tmpFileName);
    if (tmpFile) {
        while (tmpFile.available()) {
            byte f = tmpFile.read();
            DB.write(f);
        }
    }
    DB.close();
    tmpFile.close();
    SD.remove(tmpFileName);
}

void del(card_pair card){
    int idx = _find(card.card);
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
    delFromFullDB(card);
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
    if (debug) DebugSerial.println("not exist");
    res = symbolNotExist;
  } else {
    if (debug) DebugSerial.println("exist");
    res = symbolExist;
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
  if (req.indexOf(pass + addCardReq) != -1){
    if (req.indexOf(nameSymbol) != -1){
      freq = req.substring(req.indexOf(pass + addCardReq) + pass.length() + addCardReq.length(), req.indexOf(pass + addCardReq)+ pass.length() + addCardReq.length() + 8);
      resp = "Request type - add card. Card is: " + freq;
      int fmas[8];
      if (debug) Serial.print("card ");
      for (size_t i = 0; i < 8; i++) {
        fmas[i] = freq.charAt(i);
        if (debug) {
          Serial.print(fmas[i]);
          Serial.print(" ");
        }
      }
      String name = req.substring(req.indexOf(nameSymbol) + nameSymbol.length());
      int status = checkFind(fmas);
      card_pair newCard;
      switch (status) {
        case symbolNotExist:
        newCard.name = name;
        for (int i = 0; i < 8; i++){
          newCard.card[i] = fmas[i];
        }
        writeNew(newCard);
        resp += HTTPNextLine;
        resp += "Card successfully added!";
        break;
        case symbolExist:
        resp += HTTPNextLine;
        resp += "Card already exist!";
        break;
      }
    } else {
      resp += "Enter cardholder's name";
    }
} else if(req.indexOf(pass + removeCardReq) != -1){
    freq = req.substring(req.indexOf(pass + removeCardReq) + pass.length() + removeCardReq.length(), req.indexOf(pass + removeCardReq) + pass.length() + removeCardReq.length() + 8);
    resp = "Request type - remove card. Card is: " + freq;
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
    card_pair reqCard;
    switch (status) {
      case symbolNotExist:
      resp += HTTPNextLine;
      resp += "Card is not present in database!";
      break;
      case symbolExist:
      for (int i = 0; i < 8; i++){
          reqCard.card[i] = fmas[i];
        }
      del(reqCard);
      resp += HTTPNextLine;
      resp += "Card already exist!";
      break;
    }
} else if(req.indexOf(pass + showCardsBytesReq) != -1){
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
    sysresp += ";";
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
