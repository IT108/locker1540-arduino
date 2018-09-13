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
QueueList<int> greeting_buffer;
int bufferSize;
char buffer[bufferMax];
String readString = String(128);
char post;
boolean sys = false;
String sysStatus = "";

namespace fullDB {
    File CardsDB;
    unsigned int pointer = 0;
    String _name;
    String _card;
    String _greet;
    String FileAppend;
    String currentData;

    String getValue(String val){
        pointer = currentData.indexOf("&",pointer);
        return currentData.substring(currentData.indexOf(val) + val.length() + 1, pointer);
    }

    void appendFile(){
        for (int i = 0; i < FileAppend.length(); i++) {
            byte q;
            q = FileAppend[i];
            CardsDB.write(q);
        }
    }

    String getTrivialCard(){
        String res;
        res = "{\r\n_card=";
        res += _card;
        res += "$\r\n_name=";
        res += _name;
        res += "$\r\n}\r\n";
        return res;
    }
    String getGreetCard(){
        String res;
        res = "{\r\n_card=";
        res += _card;
        res += "$\r\n_name=";
        res += _name;
        res += "$\r\n_greeting=";
        res += _greet;
        res += "$\r\n}\r\n";
        return res;
    }

    String getGreet(int card[8]){
        String needCard = "";
        String currentCard = "";
        String greet = "null";
        for (size_t i = 0; i < 8; i++) {
            char f = card[i];
            needCard += f;
        }
        CardsDB = SD.open(fullDBFileName);
        if (CardsDB){
            while (CardsDB.available()) {
                char a = CardsDB.read();
                if (a == '{') {
                    currentCard = "";
                } else if (a == '}') {
                    currentData = currentCard;
                    String cardNum = getValue("card");
                    if (cardNum == needCard) {
                        greet = getValue("greeting");
                        return greet;
                    }
                }
            }
            CardsDB.close();
        }
        return greet;
    }

    void write(int card[8], String name, String greet) {
        CardsDB = SD.open(fullDBFileName, FILE_WRITE);
        String needCard = "";
        String res;
        if (CardsDB) {
            for (size_t i = 0; i < 8; i++) {
                char f = card[i];
                needCard += f;
            }
            if (greet == "-1"){
                _name = name;
                _card = needCard;
                res = getTrivialCard();
            } else {
                _name = name;
                _card = needCard;
                _greet = greet;
                res = getGreetCard();
            }
            FileAppend = res;
            appendFile();
        }
        CardsDB.close();
    }


    void del(int card[8]) {
        String needCard = "";
        String currentCard = "";
        String res = "";
        for (size_t i = 0; i < 8; i++) {
            char q = card[i];
            needCard += q;
        }
        DebugSerial.println(needCard);
        CardsDB = SD.open(fullDBFileName);
        if (CardsDB) {
            while (CardsDB.available()) {
                char a = CardsDB.read();
                if (a == '{') {
                    currentCard = "";
                } else if (a == '}') {
                    currentData = currentCard;
                    String cardNum = getValue("card");
                    if (cardNum != needCard) {
                        res += currentCard;
                        res += "\r\n";
                    }
                }
            }
            CardsDB.close();
            SD.remove(fullDBFileName);
            CardsDB = SD.open(fullDBFileName, FILE_WRITE);
            FileAppend = res;
            appendFile();
            CardsDB.close();
        }
    }

    void initMiniDB(){
        CardsDB = SD.open(fullDBFileName);
        String res = "";
        String currentCard = "";
        if (CardsDB){
            while (CardsDB.available()){
                char a = CardsDB.read();
                if (a == '{') {
                    currentCard = "";
                } else if (a == '}') {
                    currentData = currentCard;
                    String cardNum = getValue("card");
                        res += cardNum;
                        res += "\r\n";
                }
            }
            CardsDB.close();
            SD.remove(cardsFileName);
            CardsDB = SD.open(cardsFileName, FILE_WRITE);
            FileAppend = res;
            appendFile();
            CardsDB.close();
        }
    }
}

namespace DB {
    String _name = "";
    String _greet = "-1";
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
        fullDB::write(w, _name, _greet);
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


namespace greeting {
    String get_track_number(int card[]) {
        return fullDB::getGreet(card);
    }


    void play_greeting() {
        String greeting_number = get_track_number(w);
        greeting_buffer.push(random(1, 6));
        if (greeting_number != "null") {
            int x = greeting_number.toInt();
            greeting_buffer.push(x);
        }
        delay(2000);
    }

    void process_greetings() {
        if (digitalRead(PIN_DFPLAYER_BUSY) && greeting_buffer.count()) {
            mp3_play(greeting_buffer.pop());
            delay(100);
        }
    }
}

namespace commands{
    String addCard(String freq) {
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
        int status = DB::checkFind(fmas);
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
        int status = DB::checkFind(fmas);
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
                char temp = (char)q[j][p];
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

    String getAllCardsBytes() {
        sys = true;
        sysStatus = "200 ";
        String sysresp = "";
        sysresp += ";";
        for (int j = 0; j < 60; j++) {
            if (q[j][0] == 0) break;
            for (int p = 0; p < 8; p++) {
                sysresp += q[j][p];
                sysresp += " ";
            }
            sysresp += ";";
        }
        return sysresp;
    }

    String login(String key) {
        sysStatus = "200 ";
        if (key != pass){
          sysStatus = "403 ";
        }
        String sysresp = "";
        sys = true;
        randomSeed(analogRead(0));
        for (int i = 0; i < keyLength; i++) {
            sysresp += String(random(10));
        }
        token = sysresp;
        return sysresp;
    }
}

namespace net{

    EthernetClient client;
    String response = "";

    void sendResponse(){
        client.flush();
        String res = "";
        if (sys){
            res = HTTPSysHead;
            res += sysStatus;
            res += "OK \r\n\r\n";
            res += response;
        } else {
            res = HTTPHead;
            res += response;
            res += HTTPEnd;
        }
        client.print(res);
        delay(1);
        client.stop();
        if (debug) DebugSerial.println("Client disonnected");
    }

    String getVal(String key){
        readString = buffer;
        if (readString.indexOf(key) == -1)
            return "-1";
        return readString.substring(readString.indexOf(key) + key.length() + 1,
                                    readString.indexOf("&",readString.indexOf(key) + key.length() + 1));
    }

    void PerformRequestedCommands() {
        readString = buffer;
        String tmpId = getVal("id");
        int id = tmpId.toInt();
        String key = getVal("key");
        response = "<h5>INVALID REQUEST</h5>";
        String card = getVal("card");
        String name = getVal("name");
        String greet = getVal("greet");
        response = "";
        if (key != pass){
            sys = true;
            sysStatus = "403 ";
            response = "";
        } else {
            switch (id) {
                case 1:
                    DB::_name = name;
                    DB::_greet = greet;
                    response = commands::addCard(card);
                    break;
                case 2:
                    response = commands::removeCard(card);
                    break;
                case 3:
                    response = commands::getAllCards();
                    break;
                case 4:
                    response = commands::getAllCardsBytes();
                    break;
                case 5:
                    response = commands::login(key);
                    break;

            }
        }
        sendResponse();
    }

    void getPostRequest() {
        client = server.available();
        // если клиент подключен....
        if (client) {
            Serial.println("Client connected");
            boolean currentLineIsBlank = true;
            bufferSize = 0;
            readString = String(128);
            for (int i = 0; i < bufferSize; i++) {
                buffer[i] = ' ';
            }
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
                        buffer[bufferSize] = '&';
                        Serial.println("Received POST request:");
                        DebugSerial.print(buffer);
                        // Выполнение команд
                        PerformRequestedCommands();
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
    int mode, position;

    void webServer() {
        sys = false;
        String sysresp = "";
        net::getPostRequest();
    }

    void handle_locker() {
        if (!LockerSerial.available()) {
            position = -1;
            mode = -1;
            return;
        } 
        else {
            int value = LockerSerial.read();
            if (124 <= value && value <= 126) {
                mode = value;
                position = 0;
                return;
            }
            if (position > -1) {
                w[position++] = value;
            }
            if (position == 8) {
                if (mode == 126) {
                    int status = DB::checkFind(w);
                    if (status == symbolNotExist){
                        DB::writeNew(w);
                    } 
                    else {
                        DB::del(w);
                    }
                }   
                else if (mode == 124) {
                    if (DB::_find(w) != -1) {
                        LockerSerial.print("Y");
                        greeting::play_greeting();
                    }
                    else {
                        LockerSerial.print("N");
                    }
                } 
                else if (mode == 125) {
                    greeting::play_greeting();
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
    fullDB::initMiniDB();
    DB::initCards();
    DebugSerial.print("eth beg");
    Ethernet.begin(mac);
    DebugSerial.print("eth end");
    server.begin();
    DebugSerial.print("server is at ");
    DebugSerial.println(Ethernet.localIP());
    manage::position = -1;
    manage::mode = -1;
}

void loop() {
    greeting::process_greetings();
    manage::handle_locker();
    manage::webServer();
}
