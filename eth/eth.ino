#include <stdint.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <DFPlayer_Mini_Mp3.h>
#include <QueueList.h>
#include <FlexiTimer2.h>

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
//System variables
const int PIN_DFPLAYER_BUSY = 24; // warning
bool debug = true;
int q[60][8];
int w[8];
int n;
int w2[8];
const int PIN_CHIP_SELECT = 22;
String cardsFileName = "CARDS.txt";
QueueList<int> greeting_buffer;
char buffer[bufferMax];

namespace local_db {

    void clear_db() {
        for (int i = 0; i < 60;i++) {
            for (int j = 0; j < 8; j++) {
                q[i][j] = 0;
            }
        }
    }

    void parse_cards_from_file() {
        int i = 0;
        int a;
        File cards = SD.open(cardsFileName);
        DebugSerial.println("Parsing cards...");
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

    bool check_card(int a[], int b[]) {
        for (int i = 0; i < 8; i++) {
            if (a[i] != b[i]) {
                return false;
            }
        }
        return true;
    }

    bool check_guest(int a[]) {
        for (int i = 0; i < 60; i++) {
            if (check_card(q[i], a)) {
                return true;
            }
        }
        return false;
    }
}


namespace DB {
    String server_answer = "";
    String guest_authorization = "";
    String request = "";
    String request_args = "";
    String request_page = "";
    byte db_server[] = {217, 61, 106, 178};
    String personal_greeting = "-1";
    String common_greeting = "-1";
    String post_data = "";

    void build_request() {
        String res = "POST /";
        res += request_page;
        res += " HTTP/1.1\r\nHost: 217.61.106.178\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: ";
        res += String(request_args.length());
        res += "\r\n\r\n";
        res += request_args;
        request = res;

    }

    void get_post_data(){
        int data_start = server_answer.indexOf("\r\n\r\n") + 4;
        post_data = server_answer.substring(data_start);

    }


    void parse_guest_answer() {
        int data_start = server_answer.indexOf("\r\n\r\n") + 4;
        guest_authorization = server_answer.substring(data_start, 4);
        int common_greeting_start = server_answer.indexOf(";", data_start) + 1;
        int personal_greeting_start = server_answer.indexOf(";", common_greeting_start) + 1;
        int data_end = server_answer.indexOf(";", personal_greeting_start);
        guest_authorization = server_answer.substring(data_start, common_greeting_start - 1);
        common_greeting = server_answer.substring(common_greeting_start, personal_greeting_start - 1);
        personal_greeting = server_answer.substring(personal_greeting_start, data_end);
    }

    void parse_greeting_answer() {
        int data_start = server_answer.indexOf("\r\n\r\n") + 4;
        int personal_greeting_start = server_answer.indexOf(";", data_start) + 1;
        int data_end = server_answer.indexOf(";", personal_greeting_start);
        common_greeting = server_answer.substring(data_start, personal_greeting_start - 1);
        personal_greeting = server_answer.substring(personal_greeting_start, data_end);

    }


    bool check_guest(int a[]) {
        String c = "";
        DebugSerial.println("checking guest...");
        for (int i = 0; i < 8; i++) {
            c += (char) a[i];
        }
        request_args = "card=";
        request_page = "card";
        request_args += c;
        build_request();
        String req = request;
        DebugSerial.println(req);
        EthernetClient client;
        if (client.connect(db_server, 80)) {
            client.print(req);
            String ans = "";
            while (!client.available()) {}
            while (client.available()) {
                char q = client.read();
                //DebugSerial.print(q);
                ans += q;
            }
            server_answer = ans;
            DebugSerial.print(server_answer);
            parse_guest_answer();
            if (guest_authorization == "True")
                return true;
            else
                return false;
        } else {
          DebugSerial.println("Unable to connect to server!");
        }
        return local_db::check_guest(a);
    }


    void request_greetings(int a[]) {
        DebugSerial.println("requesting greetings...");
        String c = "";
        for (int i = 0; i < 8; i++) {
            c += (char) a[i];
        }
        request_page = "greet";
        request_args = "card=";
        request_args += c;
        build_request();
        EthernetClient client;
        String req = request;
        server_answer = "-1";
        if (client.connect(db_server, 80)) {
            //DebugSerial.println(req);
            client.print(req);
            String ans = "";
            while (!client.available()) {}
            while (client.available()) {
                char q = client.read();
                //DebugSerial.print(q);
                ans += q;
            }
            server_answer = ans;
            parse_greeting_answer();
            DebugSerial.print(common_greeting + " " + personal_greeting);
        }
    }

    void write_cards(){
        DebugSerial.println("writing local database...");
        String res = "";
        SD.remove(cardsFileName);
        File CardsDB = SD.open(cardsFileName, FILE_WRITE);
        //DebugSerial.println(res);
        if (!CardsDB)
            return;
        int start = post_data.indexOf(";") + 1, finish = post_data.indexOf(";", start);
        while (finish != -1){
            String card = post_data.substring(start,finish);
            DebugSerial.println(card);
            for (int i = 0; i < card.length(); i++) {
                byte q = card[i];
                CardsDB.write(q);
            }
            start = finish + 1;
            finish = post_data.indexOf(";", start);
        }
        CardsDB.close();
        local_db::clear_db();
        local_db::parse_cards_from_file();
    }

    void local_sync(){
        DebugSerial.println("syncing database...");
        request_page = "sync";
        request_args = "";
        build_request();
        EthernetClient client;
        String req = request;
        server_answer = "";
        if (client.connect(db_server, 80)) {
            //DebugSerial.println(req);
            client.print(req);
            String ans = "";
            while (!client.available()) {}
            while (client.available()) {
                char q = client.read();
                //DebugSerial.print(q);
                ans += q;
            }
            server_answer = ans;
            get_post_data();
            DebugSerial.print(post_data);
            write_cards();
        }
    }


}


namespace greeting {


    void play_greeting() {
        int greeting_number = DB::personal_greeting.toInt();
        greeting_buffer.push(DB::common_greeting.toInt());
        if (greeting_number != -1) {
            greeting_buffer.push(greeting_number);
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


namespace manage {
    int mode, position;


    void handle_locker() {
        if (!LockerSerial.available()) {
            position = -1;
            mode = -1;
            return;
        } else {
            int value = LockerSerial.read();
            if (124 <= value && value <= 125) {
                mode = value;
                DebugSerial.println(mode);
                position = 0;
                return;
            }
            if (position > -1) {
                delay(1);
                w[position++] = value;
            }
            if (position == 8) {
                if (mode == 124) {
                    if (DB::check_guest(w)) {
                        LockerSerial.print("Y");
                        greeting::play_greeting();
                    } else {
                        LockerSerial.print("N");
                    }
                } else if (mode == 125) {
                    DB::request_greetings(w);
                    greeting::play_greeting();
                }
            }
        }
    }
}

void interrupt() {
    DB::local_sync();
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
    local_db::parse_cards_from_file();
    DebugSerial.print("eth beg");
    Ethernet.begin(mac);
    DebugSerial.print("eth end");
    server.begin();
    DebugSerial.print("server is at ");
    DebugSerial.println(Ethernet.localIP());
    manage::position = -1;
    manage::mode = -1;
    FlexiTimer2::set(300000, interrupt);
    FlexiTimer2::start();
}

void loop() {
    greeting::process_greetings();
    manage::handle_locker();
}
