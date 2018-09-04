#include <stdint.h>
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
#include <WString.h>
//Serial defines
#define LockerSerial Serial3
#define DebugSerial Serial
#define bufferMax 128
//Server variables
String pass = "12345";
byte mac[] = {0xA0, 0x20, 0xA6, 0x21, 0xBB, 0xF5};
IPAddress ip(192, 168, 1, 38);
EthernetServer server(80);
int keyLength = 6;
String token;
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
int bufferSize;
char buffer[bufferMax];
String readString = String(128);
char post;
boolean sys = false;
String sysStatus = "";

namespace fullDB {

    void write(int card[8], String name) {
        File cards = SD.open(fullDBFileName, FILE_WRITE);
        byte f;
        if (cards) {
            for (size_t i = 0; i < 8; i++) {
                f = card[i];
                cards.write(f);
            }
            f = '/';
            cards.write(f);
            for (size_t i = 0; i < name.length(); i++) {
                f = name.charAt(i);
                cards.write(f);
            }
            f = ';';
            cards.write(f);
        }
        cards.close();
    }


    void del(int card[8]) {
        String needCard = "";
        for (size_t i = 0; i < 8; i++) {
            char q = card[i];
            needCard += q;
        }
        DebugSerial.println(needCard);
        File cards = SD.open(fullDBFileName);
        String res = "";
        if (cards) {
            int i = 1;
            String _name = "";
            String cardNum = "";
            String music = "";
            res = ";";
            while (cards.available()) {
                int a = 0;
                while (a != cardsSeparator) {
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
                    if (needCard != cardNum) {
                        DebugSerial.println(" OK");
                        res += cardNum;
                        res += "/";
                        res += _name;
                        res += "/";
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
        cards = SD.open(fullDBFileName, FILE_WRITE);
        if (cards) {
            for (int i = 0; i < res.length(); i++) {
                byte f = res[i];
                cards.write(f);
            }
        }
        cards.close();
    }
}

namespace DB {

    void renameC(int idx1, int idx2) {
        for (size_t i = 0; i < 8; i++) {
            q[idx1][i] = q[idx2][i];
        }
    }

    bool checkCard(int a[], int b[]) {
        for (int i = 0; i < 8; i++) {
            if (a[i] != b[i]) {
                return false;
            }
        }
        return true;
    }

    int _find(int a[]) {
        for (int i = 0; i < 60; i++) {
            if (checkCard(q[i], a)) {
                return i;
            }
        }
        return -1;
    }

    bool is_good(int a) {
        return (int) '0' <= a && (int) '9' >= a || (int) 'A' <= a && (int) 'F' >= a;
    }

    int checkFind(int w[]) {
        int res = 0;
        int idx = _find(w);
        if (idx == -1) {
            if (debug) DebugSerial.println("not exist");
            res = symbolNotExist;
        } else {
            if (debug) DebugSerial.println("exist");
            res = symbolExist;
        }
        if (debug) DebugSerial.print(" OK");
        return res;
    }

    void initCards() {
        int i = 0;
        int j = 0;
        int a;
        File cards = SD.open(cardsFileName);
        if (cards) {
            while (cards.available()) {
                for (int f = 0; f < 8; f++) {
                    a = cards.read();
                    q[i][f] = a;

                    if (debug) {
                        DebugSerial.print(q[i][f]);
                        DebugSerial.print(" ");
                    }
                }
                i++;
                cards.seek(i * 10);
                if (debug) DebugSerial.println();
            }
            n = i;
        }
        cards.close();
    }


    void writeNew(int w[8]) {
        for (int i = 0; i < 8; i++) {
            q[n][i] = w[i];
        }
        n++;
        SD.remove(cardsFileName);
        File cards = SD.open(cardsFileName, FILE_WRITE);
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
        //fullDB::write(w);
    }

    void del(int card[8]) {
        int idx = _find(card);
        for (size_t i = idx; i < n; i++) {
            renameC(i, i + 1);
        }
        n--;
        SD.remove(cardsFileName);
        File cards = SD.open(cardsFileName, FILE_WRITE);
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
        fullDB::del(card);
    }
}


namespace music {

    String getMusicNum(int needCardi[]) {
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
                if (a != nameSeparator && a != cardsSeparator && is_good(a)) {
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
                    if (i == 3) {
                        DebugSerial.println(cardNum);
                        DebugSerial.println(cardNum.substring(0, 8));
                        DebugSerial.println(cardNum.length());
                        if (needCard == cardNum) {
                            DebugSerial.println(music);
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

        melody_buffer.push(random(1, 6));
        if (musicNum != "null") {
            int x = musicNum.toInt();
            DebugSerial.println(x);
            melody_buffer.push(x);
        }
        DebugSerial.println(melody_buffer.count());
        delay(2000);
    }


}

namespace commands{
    String addCard(String freq, String name) {
        String resp = "";
        resp = "Request type - add card. Card is: " + freq;
        int fmas[8];
        if (debug) DebugSerial.print("card ");
        for (size_t i = 0; i < 8; i++) {
            fmas[i] = freq.charAt(i);
            if (debug) {
                DebugSerial.print(fmas[i]);
                DebugSerial.print(" ");
            }
        }
        int status = checkFind(fmas);
        int newCard[8];
        switch (status) {
            case symbolNotExist:
                for (int i = 0; i < 8; i++) {
                    newCard[i] = fmas[i];
                }
                DB::writeNew(newCard);
                resp += HTTPNextLine;
                resp += "Card successfully added!";
                break;
            case symbolExist:
                resp += HTTPNextLine;
                resp += "Card already exist!";
                break;
        }
        return resp;
    }

    String removeCard(String freq) {
        String resp = "";
        resp = "Request type - remove card. Card is: " + freq;
        int fmas[8];
        if (debug) DebugSerial.print("card ");
        for (size_t i = 0; i < 8; i++) {
            fmas[i] = freq.charAt(i);
            if (debug) {
                DebugSerial.print(fmas[i]);
                DebugSerial.print(" ");
            }
        }
        int status = checkFind(fmas);
        int reqCard[8];
        switch (status) {
            case symbolNotExist:
                resp += HTTPNextLine;
                resp += "Card is not present in database!";
                break;
            case symbolExist:
                for (int i = 0; i < 8; i++) {
                    reqCard[i] = fmas[i];
                }
                DB::del(reqCard);
                resp += HTTPNextLine;
                resp += "Card successfully deleted!";
                break;
        }
        return resp;
    }

    String showCardsBytes() {
        String resp = "";
        resp = "<h3>Request type - show cards</h3>\r\n";
        resp += "<br />\r\n<h2>Cards:</h2>\r\n<br />\r\n";
        resp += HTTPOpenTable;
        for (int j = 0; j < 60; j++) {
            if (q[j][0] == 0) break;
            resp += j + 1;
            resp += ".  ";
            resp += HTTPNextTableCell;
            for (int p = 0; p < 8; p++) {
                resp += q[j][p];
                resp += " ";
            }
            resp += HTTPNextTableRow;
        }
        resp += HTTPCloseTable;
        return resp;
    }

    String showCards() {
        String resp = "";
        resp = "<h3>Request type - show cards</h3>\r\n<br />\r\n<h2>Cards:</h2>\r\n<br />\r\n";
        resp += HTTPOpenTable;
        for (int j = 0; j < 60; j++) {
            if (q[j][0] == 0) break;
            resp += j + 1;
            resp += ".  ";
            resp += HTTPNextTableCell;
            for (int p = 0; p < 8; p++) {
                char temp = q[j][p];
                resp += temp;
            }
            resp += HTTPNextTableRow;
        }
        resp += HTTPCloseTable;
        return resp;
    }

    String getAllCards() {
        sys = true;
        sysStatus = "200 ";
        String sysresp = "";
        sysresp += ";";
        for (int j = 0; j < 60; j++) {
            if (q[j][0] == 0) break;
            for (int p = 0; p < 8; p++) {
                char temp = q[j][p];
                sysresp += temp;
            }
            sysresp += ";";
        }
        return sysresp;
    }

    String login() {
        String sysresp = "";
        sys = true;
        sysStatus = "200 ";
        randomSeed(analogRead(0));
        for (int i = 0; i < keyLength; i++) {
            sysresp += String(random(10));
        }
        token = sysresp;
        return sysresp;
    }
}

namespace net{
    String getVal(String req, String key){
        return req.substring(req.indexOf(key) + key.length() + 1,
                                    req.indexOf("&",req.indexOf(key) + key.length() + 1));
    }

    void PerformRequestedCommands() {
        readString = buffer;
        String tmpId = getVal(readString, "id");
        int id = tmpId.toInt();
        String key = getVal(readString, String("key"));
        switch (id){
            case 1:
                String card = getVal(readString, String("card"));
                String name = getVal(readString, String("name"));
                commands::addCard(card, name);
        }
    }

    void getPostRequest() {
        // если клиент подключен....
        if (client) {
            Serial.println("Client connected");
            boolean currentLineIsBlank = true;
            bufferSize = 0;
            while (client.connected()) {
                if (client.available()) {
                    char c = client.read();
                    // если вы получили символ новой строки
                    // и символ пустой строки, то POST запрос закончился
                    // и вы можете отправить ответ
                    if (c == '\n' && currentLineIsBlank) {
                        // Здесь содержатся данные POST запроса
                        while (client.available()) {
                            post = client.read();
                            if (bufferSize < bufferMax)
                                buffer[bufferSize++] = post;  // сохраняем новый символ в буфере и создаем приращение bufferSize
                        }
                        Serial.println("Received POST request:");
                        // Выполнение команд
                        PerformRequestedCommands();
                        // Отправка ответа
                        sendResponse();
                    } else if (c == '\n') {
                        currentLineIsBlank = true;
                    } else if (c != '\r') {
                        currentLineIsBlank = false;
                    }
                }
            }
            Serial.println("Port closed");
        }
    }
}

namespace manage {

    void webServer() {
        bool sys = false;
        String sysresp = "";
        // Check if a client has connected
        net::getPostRequest();
        // The client will actually be disconnected
        // when the function returns and 'client' object is detroyed
    }

    void process_melody() {
        if (digitalRead(PIN_DFPLAYER_BUSY) && melody_buffer.count()) {
            mp3_play(melody_buffer.pop());
            delay(100);
        }
    }

    void checkDB() {
        if (!LockerSerial.available()) {
            Num = -1;
            Main = -1;
            return;
        } else {
            int a = LockerSerial.read();
            //LockerSerial.println(a);
            if (a == 126 || a == 124 || a == 125) {
                Main = a;
                Num = 0;
                if (debug) DebugSerial.println(Main);
            }
            if (Main == 126) {
                if (Num > -1 && a != Main) {
                    if (debug) {
                        DebugSerial.print(a);
                        DebugSerial.print(" ");
                    }
                    w[Num] = a;
                    Num++;

                    if (Num == 8) {
                        checkFind(w);
                    }
                }
            } else if (Main == 124) {
                if (Num > -1 && a != Main) {
                    w[Num] = a;
                    if (debug) {
                        DebugSerial.print(w[Num]);
                        DebugSerial.print(" ");
                    }
                    Num++;
                    if (Num == 8) {
                        if (_find(w) != -1) {
                            LockerSerial.print("Y");
                            play_melody();
                        } else {
                            LockerSerial.print("N");
                        }
                    }
                }
            } else if (Main == 125) {
                if (Num > -1 && a != Main) {
                    w[Num] = a;
                    if (debug) {
                        DebugSerial.print(w[Num]);
                        DebugSerial.print(" ");
                    }
                    Num++;
                    if (Num == 8) {
                        play_melody();
                    }
                }
            }
        }
    }
}



void setup() {
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
    DB::initCards();
    Ethernet.begin(mac);
    server.begin();
    DebugSerial.print("server is at ");
    DebugSerial.println(Ethernet.localIP());
}

void loop() {
    manage::process_melody();
    manage::checkDB();
    manage::webServer();
}