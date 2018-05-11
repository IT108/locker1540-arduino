#include <EEPROM.h>
#include <FlexiTimer2.h>

const int V_MEN_R = 55;
const int V_MEN_G = 54;
const int V_DOOR_R = 56;
const int V_DOOR_G = 57;
const int V_LOCKER_R = 58;
const int V_LOCKER_G = 59;

const int OUTSIDE_BUTTON = 31;
const int OUTSIDE_R = 44;
const int OUTSIDE_G = 45;
const int OUTSIDE_B = 46;

const int LOCKER = 12;

const int SOUND_OUTSIDE = 10;
const int SOUND_INSIDE = 11;

const int DOOR_SENSOR = 6;
const int LOCKER_SENSOR = 7;
const int EXIT_BUTTON = 8;

const int INSIDE_SENSOR_0_0 = 2;
const int INSIDE_SENSOR_0_1 = 3;
const int INSIDE_SENSOR_1_0 = 4;
const int INSIDE_SENSOR_1_1 = 5;

int Num;
int Num1;
int w[8];
int w1[8];
int R;
int G;
int B;
int n;

long long start_time;
long long last_got;
long long timer;
long long anothertimer;
long long state_buzzer;

int master[8] = {
    55, 57, 55, 57, 48, 55, 55, 57
}; //0 -> 48
  //
int badsymb[9] = {
    -1, 2, 3, 10, 13, 249, 191, 235, 0
};

int qq[3][8] = {
    {55, 53, 49, 56, 57, 65, 54, 70},
    {55, 53, 48, 56, 67, 67, 52, 70},
    {51, 55, 70, 68, 56, 48, 56, 70},
};

int q[60][8];

bool rec;

const int COUNT_NOTES = 9;

int frequences[COUNT_NOTES] = {
    392, 392, 392, 311, 466, 392, 311, 466, 392
};

int durations[COUNT_NOTES] = {
    350, 350, 350, 250, 100, 350, 250, 100, 700
};


void led(int a, int b, int c){
    analogWrite(OUTSIDE_R, a);
    analogWrite(OUTSIDE_G, b);
    analogWrite(OUTSIDE_B, c);
}

bool isAnybodyInside(){
    bool f = 0;
    for(int i = INSIDE_SENSOR_0_0; i <= INSIDE_SENSOR_1_1; i++){
        f |= digitalRead(i);
    }
    if(timer > millis()){
        timer = millis();
    }
    if(f){
        timer = millis();
    }
    if(millis() - timer > 60000){
        return 0;
    }
    return 1;
}

void Vahta(){
    if(!isAnybodyInside()){
        digitalWrite(V_MEN_G, 1);
        digitalWrite(V_MEN_R, 0);
    }
    else{
        digitalWrite(V_MEN_G, 0);
        digitalWrite(V_MEN_R, 1);
    }
    if(digitalRead(DOOR_SENSOR)){
        digitalWrite(V_DOOR_G, 1);
        digitalWrite(V_DOOR_R, 0);
    }
    else{
        digitalWrite(V_DOOR_G, 0);
        digitalWrite(V_DOOR_R, 1);
    }
    if(digitalRead(LOCKER_SENSOR)){
        digitalWrite(V_LOCKER_G, 1);
        digitalWrite(V_LOCKER_R, 0);
    }
    else{
        digitalWrite(V_LOCKER_G, 0);
        digitalWrite(V_LOCKER_R, 1);
    }
}

void setLocked(bool b) {
    digitalWrite(LOCKER, b);
}

void play(){
    if(millis() < anothertimer){
        anothertimer = millis();
        return;
    }
    if(digitalRead(OUTSIDE_BUTTON) || millis() - anothertimer < 5000) return;
    for(int i = 0; i < COUNT_NOTES; i++){
        tone(SOUND_INSIDE, frequences[i], durations[i]);
        delay(durations[i]);
    }
    noTone(SOUND_INSIDE);
    anothertimer = millis();
}

void test_button(){
    if(!digitalRead(OUTSIDE_BUTTON)){
        digitalWrite(SOUND_OUTSIDE, state_buzzer);
        state_buzzer ^= 1;
    }
    else{
        digitalWrite(SOUND_OUTSIDE, 0);
    }
}

int to8(int i, int j){
    return 8 * i + j;
}

void updN(){
    n = EEPROM[1023];
    if(n == 255){
        EEPROM[1023] = 0;
        updN();
    }
    if(n > 60){
        //alert
    }
    n = min(n, 60);
}

bool checkCard(int a[], int b[]){
    for(int i = 0; i < 8; i++){
        if(a[i] != b[i]){
            return false;
        }
    }
    return true;
}

void rewriteQ(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 8; j++){
            q[i][j] = EEPROM[to8(i, j)];
        }
    }
}

void writeQ(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 8; j++){
            Serial.write(q[i][j]);
            Serial.print(" ");
        }
        Serial.println();
    }
}

bool isvalid(int a){
    for(int i = 0; i < 9; i++){
        if(a == badsymb[i]) return 0;
    }
    return 1;
}

void checkBtn(){
    int p = digitalRead(EXIT_BUTTON);
    if(p != 0){
        setLocked(0);
        led(0, 255, 0);
        delay(5000);
        setLocked(0);
        led(0, 0, 0);
    }
}

void writeNew(int card[]){
    for(int i = 0; i < 8; i++){
        EEPROM[to8(n, i)] = card[i];
        q[n][i] = card[i];
    }
    EEPROM[1023]++;
    updN();
}

void endOfReading(){
    led(255, 255, 255);
    delay(5000);
}


void del(int idx){
    for(int i = idx; i < n - 1; i++){
        for(int j = 0; j < 8; j++){
            EEPROM[to8(i, j)] = EEPROM[to8(i + 1, j)];
        }
    }
    EEPROM[1023]--;
    rewriteQ();
    updN();
}

int _find(int a[]){
    for(int i = 0; i < n; i++){
        if(checkCard(q[i], a)){
            return i;
        }
    }
    return -1;
}

void initiation(){
    EEPROM[1023] = 0;
    updN();
    for(int i = 0; i < 3; i++){
        writeNew(qq[i]);
    }
}

void reColor(){
    if(R > 0 && B == 0){
        R--;
        G++;
    } else if(G > 0){
        G--;
        B++;
    } else if(B > 0){
        B--;
        R++;
    }
}
void webC(){
  if (Serial3.available()) {
    int a = Serial3.read();
    if (Num1 >= 1) {
      w1[Num1 - 1] = a;
      Num1++;
    }
    if (a == 126) {
      Num1 = 1;
    }
    if (Num1 == 9) {
      writeNew(w1);
      led(0,255,0);
      delay(1500);
    }
  } else {
    Num1 = 0;
  }
}

void(* reboot)(void) = 0;

void interrupt(){
    Vahta();
    reColor();
    test_button();
}

void setup(){
    Serial.begin(9600);
    Serial3.begin(115200);
    //Serial3.begin(9600);
    if(EEPROM[1023] == 255){
        initiation();
    }
    updN();
    rewriteQ();
    //writeQ();
    pinMode(DOOR_SENSOR, INPUT); // защелка
    pinMode(LOCKER_SENSOR, INPUT); // дверь
    digitalWrite(DOOR_SENSOR,1);
    digitalWrite(LOCKER_SENSOR,1);
    pinMode(EXIT_BUTTON, INPUT);
    pinMode(LOCKER, OUTPUT);
    pinMode(OUTSIDE_R, OUTPUT);
    pinMode(OUTSIDE_G, OUTPUT);
    pinMode(OUTSIDE_B, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(V_MEN_G,OUTPUT);
    pinMode(V_MEN_R,OUTPUT);
    pinMode(V_DOOR_G,OUTPUT);
    pinMode(V_DOOR_R,OUTPUT);
    pinMode(V_LOCKER_G,OUTPUT);
    pinMode(V_LOCKER_R,OUTPUT);
    pinMode(OUTSIDE_BUTTON, INPUT);
    digitalWrite(OUTSIDE_BUTTON,1);
    pinMode(SOUND_OUTSIDE,OUTPUT);
    pinMode(SOUND_INSIDE,OUTPUT);
    pinMode(INSIDE_SENSOR_0_0, INPUT);
    pinMode(INSIDE_SENSOR_0_1, INPUT);
    pinMode(INSIDE_SENSOR_1_0, INPUT);
    pinMode(INSIDE_SENSOR_1_1, INPUT);
    timer = millis();
    anothertimer = millis();
    last_got = millis();
    start_time = millis();
    state_buzzer = 0;
    R = 255;
    G = 0;
    B = 0;
    Num = 0;
    rec = 0;
    FlexiTimer2::set(2, interrupt);
    FlexiTimer2::start();
}

void loop(){
    if(millis() < start_time){
        start_time = millis();
    }
    checkBtn();
    led(R, G, B);
    setLocked(1);
    webC();
    play();
    /*if(millis() - start_time > 86400){
        led(255, 255, 255);
        asm volatile("jmp 0x00");
        //reboot();
    }*/
    delay(2);

    int a = Serial.read();
    if(!Serial.available()){
        Num = 0;
        return;
    }
    else {
        if(isvalid(a)){
            last_got = millis();
            w[Num] = a;
            Num++;
            if(Num == 8){
                if(checkCard(w, master)){
                    rec = true;
                    led(0,0,255);
                    delay(5000);
                    led(0,0,0);
                    Num = 0;
                }
                else{
                    if(rec){
                        int idx = _find(w);
                        if (idx == -1) {
                            writeNew(w);
                            led(0,255,0);
                            delay(5000);
                            //writeQ();
                        }
                        else{
                            del(idx);
                            led(255,0,0);
                            delay(5000);
                            //writeQ();
                        }
                        rec = false;
                    }
                    else{
                        bool ok = true;
                        for(int i = 0; i < n; i++){
                            ok = checkCard(q[i], w);
                            if(ok){
                                setLocked(0);
                                led(0, 255, 0);
                                delay(5000);
                                setLocked(1);
                                led(0, 0, 0);
                                break;
                            }
                        }
                        if(!ok){
                            led(255, 0, 0);
                            delay(2000);
                            led(0, 0, 0);
                        }
                    }
                    Num = 0;
                }
            }
        }
    }
}
