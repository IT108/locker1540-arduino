#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <DFPlayer_Mini_Mp3.h>
#include <QueueList.h>

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
int keyLength = 6;
String token;
String showCardsReq = "/O";
String showCardsBytesReq = "/B";
String addCardReq = "/A";
String removeCardReq = "/R";
String nameSymbol = "/N";
String HTTPFullDB = "/FD";
String getAllCards = "/GC";
String HTTPLoginURL = "LA/";
String HTTPMusic = "MUSIC/";
String HTTPHead = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
String HTTPSysHead = "HTTP/1.1 ";
String HTTPEnd = "\r\n</html>\n";
String HTTPNextLine = "\r\n<br />\r\n";
String HTTPOpenTable = "\r\n<table border=1 align=\"left\" cellpadding=0 cellspacing=0>\r\n<tr><td>";
String HTTPNextTableCell = "</td><td>";
String HTTPNextTableRow = "</td></tr>\r\n<tr><td>";
String HTTPCloseTable = "</td></tr>\r\n</table>";
//System variables
const int PIN_DFPLAYER_BUSY = 24; // warning
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
String fullDBFileName = "CARDSDB.TXT";
String tmpFileName = "TmpFile.txt";
QueueList<int> melody_buffer;


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
  //writeToFullDB(w);
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

void writebyte(File &f, String s) {
    for (int i = 0; i < s.length(); i++) {
        byte cur = (byte)s[i];
        f.write(cur);
    }
}

void copyTmpToDB(){
    SD.remove(fullDBFileName);
    File DB = SD.open(fullDBFileName,FILE_WRITE);
    File tmpFile = SD.open(tmpFileName);
    if (tmpFile) {
        while (tmpFile.available()) {
            int a = tmpFile.read();
            byte f = a;
            DB.write(f);
        }
    }
    DB.close();
    tmpFile.close();
    SD.remove(tmpFileName);
}

void delFromFullDB(card_pair card){
    String needCard = "";
    for (size_t i = 0; i < 8; i++) {
        char q = card.card[i];
        needCard += q;
    } 
    DebugSerial.println(needCard);
    File cards = SD.open(fullDBFileName);
      if (cards) {
        int i = 1;
        String _name = "";
        String cardNum = "";
        String music = "";
        String res = ";";
        while (cards.available()) {
            int a = 0;
            while (a != cardsSeparator){
              a = cards.read();
            }
            a = cards.read();
            if (a != nameSeparator && a != cardsSeparator) {
                char q = a;
                switch (i) {
                    case 2:
                      _name += q;
                      break;
                    case 1:
                      cardNum += q;
                      break;
                    case 3:
                      music += q;
                      break;
                }
            }
            if (a == cardsSeparator) {
                DebugSerial.print(cardNum);
                if (needCard != cardNum){
                    DebugSerial.println(" OK");
                    res += cardNum;
                    res += "/";
                    res += _name;
                    res +=  "/";
                    res += music;
                    res += ";";
                } else {
                  DebugSerial.println("");
                }
                i = 1;
                _name = "";
                cardNum = "";
                music = "";
            }
            if (a == nameSeparator)
                i++;
        }
        cards.close();
      }
      cards.close();
      SD.remove(fullDBFileName);
      cards = SD.open(fullDBFileName,FILE_WRITE);
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

String getMusicNum(int needCardi[]){
    String needCard = "";
    for (size_t i = 0; i < 8; i++) {
        char q = needCardi[i];
        needCard += q;
    }
    DebugSerial.println(needCard);
    File cards = SD.open(fullDBFileName);
      if (cards) {
        int i = 1;
        String _name = "";
        String cardNum = "";
        String music = "";
        while (cards.available()) {
            int a = cards.read();
           // Serial.print(a);
           // Serial.print(" ");
           // Serial.println((char)a);
            if (a != nameSeparator && a != cardsSeparator) {
                char q = a;
                switch (i) {
                    case 2:
                      _name += q;
                      break;
                    case 1:
                      cardNum += q;
                      break;
                    case 3:
                      music += q;
                      break;
                }
            }
            if (a == cardsSeparator) {
                if (i == 3){
                  Serial.println(cardNum);
                  Serial.println(cardNum.substring(0, 8));
                  Serial.println(cardNum.length());
                      if (needCard == cardNum){
                        Serial.println(music);
                        cards.close();
                        return music;
                      }
                }
                i = 1;
                _name = "";
                cardNum = "";
                music = "";
            }
            if (a == nameSeparator)
                i++;
        }
        cards.close();
        return "null";
      }
      cards.close();
}


void play_melody() {
    String musicNum = getMusicNum(w);
    DebugSerial.println(musicNum);
    randomSeed(analogRead(0));

    melody_buffer.push(random(6));
    if (musicNum != "null") {
        int x = musicNum.toInt();
        DebugSerial.println(x);
        melody_buffer.push(x);
    }
    DebugSerial.println(melody_buffer.count());
    delay(2000);
}

void checkDB(){
  if (!LockerSerial.available()) {
    Num = -1;
    Main = -1;
    return;
  } else {
    int a = LockerSerial.read();
    //LockerSerial.println(a);
    if (a == 126 || a == 124 || a == 125){
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
            play_melody();
	  } else {
            LockerSerial.print("N");
          }
        }
      }
    }
    else if (Main == 125) {
      if (Num > -1 && a != Main) {
        w[Num] = a;
        if (debug) {
        DebugSerial.print(w[Num]);
        DebugSerial.print(" ");
      }
        Num++;
        if (Num == 8){
          if (_find(w) != -1) {
            play_melody();
          }
        }
      }
    }
  }
}

void process_melody() {
  if (digitalRead(PIN_DFPLAYER_BUSY) && melody_buffer.count()) {
	    mp3_play(melody_buffer.pop());
      delay(100);
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
  String sysStatus;
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
      resp += "Card successfully deleted!";
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
    sysStatus = "200 ";
    sysresp += ";";
    for (int j = 0; j < 60; j++){
      if (q[j][0] == 0) break;
      for (int p = 0; p < 8; p++){
        char temp = q[j][p];
          sysresp += temp;
        }
        sysresp += ";";
      }
  } else if(req.indexOf(HTTPLoginURL + pass) != -1) {
      sys = true;
      sysStatus = "200 ";
      randomSeed(analogRead(0));
      for (int i = 0; i < keyLength; i++){
          sysresp += String(random(10));
      }
      token = sysresp;

  } else if(req.indexOf(HTTPLoginURL) != -1){
      sys = true;
      sysStatus = "401 ";
  }else if (req.indexOf(HTTPMusic + pass + "/1") != -1){
      mp3_next();
      delay(100);
  }else if (req.indexOf(HTTPMusic + pass + "/2") != -1){
      mp3_random_play();
      delay(100);
  } else if (req.indexOf(HTTPMusic + pass) != -1){
      resp = "<h3>Request type - musicPlay</h3>\r\n";
      resp += "<br />\r\n<h2>Cards:</h2>\r\n<br />\r\n";
      resp += HTTPOpenTable;
      resp += "<p><a href=""http://192.168.1.38/MUSIC/";
      resp += pass;
      resp += "/1""><button>next composition</button></a></p>";
      resp += HTTPNextTableCell;
      resp += "<p><a href=""http://192.168.1.38/MUSIC/";
      resp += pass;
      resp += "/2""><button>random composition</button></a></p>";
      resp += HTTPCloseTable;
  } else if(req.indexOf(pass + HTTPFullDB) != -1){
      sys = true;
      sysStatus = "200 ";
      File cards = SD.open(fullDBFileName);
      if (cards){
          while (cards.available()) {
              int a = cards.read();
              char q = a;
              sysresp += q;
          }
      }

  } else {
    if (debug) Serial.println("invalid request");
    resp = "<h5>INVALID REQUEST</h5>";
  }
  // Set GPIO2 according to the reques
  client.flush();

  // Prepare the response
  String s = HTTPHead;
  s += resp;
  s += HTTPEnd;
  if (sys){
      s = HTTPSysHead;
      s += sysStatus;
      s += "OK \r\n\r\n";
      s += sysresp;
  }

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
    Serial2.begin(9600);
    mp3_set_serial(Serial2);
    mp3_set_volume(25);
    delay(100);
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
    process_melody();
    checkDB();
    webServer();
}
