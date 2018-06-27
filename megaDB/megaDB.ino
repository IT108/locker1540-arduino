#include<SPI.h>
#include<SD.h>
#include <FlexiTimer2.h>

bool debug = true;
int q[60][8];
int w[8];
int Num;
int n;
int Main;
int w2[8];
int Num2;
int Main2;
const int PIN_CHIP_SELECT = 10;

void sendCards(){
    for (size_t i = 0; i < 60; i++){
      if(q[i][0] == 0) return;
      String card = "";
        for (size_t j = 0; j < 8; j++) {
            char f = q[i][j];
            Serial2.print(f);
        }
    }
}

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
  if (!Serial3.available()) {
    Num = -1;
    Main = -1;
    return;
  } else {
    int a = Serial3.read();
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
      if (Num > -1 && a != Main) {
        w[Num] = a;
        if (debug) {
        Serial.print(w[Num]);
        Serial.print(" ");
      }
        Num++;
        if (Num == 8){
          if (_find(w) != -1) {
            Serial3.print("Y");
          } else {
            Serial3.print("N");
          }
        }
      }
    }
  }
}

void checkDB2(){
  if (!Serial2.available()) {
    Num2 = -1;
    Main2 = -1;
    return;
  } else {
    int a = Serial2.read();
    //Serial.println(a);
    if (a == 126 || a == 124){
      Main2 = a;
      Num2 = 0;
      if (debug) Serial.println(Main2);
    }
    if (Main2 == 126){
      if (Num2 > -1 && a != Main2) {
        if (debug){
          Serial.print(a);
          Serial.print(" ");
        }
        w2[Num] = a;
        Num2++;

        if (Num2 == 8) {
          checkFind(w2);
        }
      }
  } else if (Main2 == 124){
      if (debug) {
        Serial.print(a);
        Serial.print(" ");
      }
      if (Num2 > -1 && a != Main2) {
        w2[Num] = a;
        Num2++;
        if (Num2 == 8){
          if (_find(w2) != -1) {
            Serial2.print("Y");
          } else {
            Serial2.print("N");
          }
        }
      }
    }
  }
}


void setup(){
    Serial.begin(115200);
    Serial3.begin(115200);
    Serial2.begin(115200);
    delay(10);

    if (!SD.begin(PIN_CHIP_SELECT)) {
        if (debug) Serial.println("Card failed, or not present");
        // Если что-то пошло не так, завершаем работу:
        //return;
      }
      if (debug) Serial.println("card initialized.");
      initCards();
      FlexiTimer2::set(10000, sendCards);
      FlexiTimer2::start();
}

void loop(){
    checkDB();
    checkDB2();
}
