#include<SPI.h>
#include<SD.h>

const int PIN_CHIP_SELECT = 10;

int q[60][8];
int w[8];
int Num;
int n;
int Main;
bool debug = false;
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
    renameC(idx, idx + 1);
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

void setup(){
  Serial.begin(115200);
  if (!SD.begin(PIN_CHIP_SELECT)) {
      if (debug) Serial.println("Card failed, or not present");
      // Если что-то пошло не так, завершаем работу:
      return;
    }
    if (debug) Serial.println("card initialized.");
    initCards();
}

void loop(){
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
