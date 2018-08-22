#include <FlexiTimer2.h>

namespace constant_pins {
	const int V_MEN_R = 55;
	const int V_MEN_G = 54;
	const int V_DOOR_R = 56;
	const int V_DOOR_G = 57;
	const int V_LOCKER_R = 58;
	const int V_LOCKER_G = 59;

	const int OUTSIDE_BUTTON = 31;
	const int OUTSIDE_RED = 44;
	const int OUTSIDE_GREEN = 45;
	const int OUTSIDE_BLUE = 46;

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
}

namespace door_bell {
	long long timer;
	const int COUNT_NOTES = 9;
	const int WAITING_TIME = 5000;

	const int FREQUENCES[COUNT_NOTES] = {
	    392, 392, 392, 311, 466, 392, 311, 466, 392
	};
	const int DURATIONS[COUNT_NOTES] = {
	    350, 350, 350, 250, 100, 350, 250, 100, 700
	};

	void play() {
	    if (millis() < timer) {
	        timer = millis();
	        return;
	    }
	    if (digitalRead(constant_pins::OUTSIDE_BUTTON) || millis() - timer < WAITING_TIME) {
	    	return;
	    }
	    for (int i = 0; i < COUNT_NOTES; i++) {
	        tone(constant_pins::SOUND_INSIDE, FREQUENCES[i], DURATIONS[i]);
	        delay(DURATIONS[i]);
	    }
	    noTone(constant_pins::SOUND_INSIDE);
	    timer = millis();
	}
}

namespace outside_led {
	const int RED[] = {255, 0, 0};
	const int GREEN[] = {0, 255, 0};
	const int BLUE[] = {0, 0, 255};
	volatile int current_red;
	volatile int current_green;
	volatile int current_blue;

	void led(int red, int green, int blue) {
	    analogWrite(constant_pins::OUTSIDE_RED, red);
	    analogWrite(constant_pins::OUTSIDE_GREEN, green);
	    analogWrite(constant_pins::OUTSIDE_BLUE, blue);
	}

  void setCurrentColor() {
      //Serial.println("CurrentColor");
      analogWrite(constant_pins::OUTSIDE_RED, current_red);
      analogWrite(constant_pins::OUTSIDE_GREEN, current_green);
      analogWrite(constant_pins::OUTSIDE_BLUE, current_blue);
  }

	void red() {
		led(RED[0], RED[1], RED[2]);
	}
 
	void green() {
		led(GREEN[0], GREEN[1], GREEN[2]);
	}

	void blue() {
		led(BLUE[0], BLUE[1], BLUE[2]);
	}

	void recolor() {
		if (current_red > 0 && current_blue == 0) {
		    current_red--;
		    current_green++;
		} 
		else if (current_green > 0) {
		    current_green--;
		    current_blue++;
		} 
		else if (current_blue > 0) {
		    current_blue--;
		    current_red++;
		}
//   Serial.print(current_red);
//   Serial.print(" ");
//   Serial.print(current_green);
//   Serial.print(" ");
//   Serial.print(current_blue);
//   Serial.println(" ");
   
   //led(current_red, current_green, current_blue);
	}
}

namespace locker {
	const int LOCK = 1;
	const int UNLOCK = 0;

	void lock() {
		digitalWrite(constant_pins::LOCKER, LOCK);
	}

	void unlock() {
		digitalWrite(constant_pins::LOCKER, UNLOCK);
	}

	int locker_status() {
		return digitalRead(constant_pins::LOCKER_SENSOR);
	}

	int door_status() {
		return digitalRead(constant_pins::DOOR_SENSOR);
	}
}

namespace exit_button {
	void check() {
	    int status = digitalRead(constant_pins::EXIT_BUTTON);
	    if (status != 0) {
          //Serial.println("Check");
	       	locker::unlock();
	        outside_led::green();
	        delay(5000);
	        locker::lock();
	    }
	}
}


namespace security {
	long long timer = millis();

	int cabinet_status() {
		bool status = 0;
		for (int i = constant_pins::INSIDE_SENSOR_0_0; i <= constant_pins::INSIDE_SENSOR_1_1; i++) {
		    status |= digitalRead(i);
		}
   //Serial.println(status);
		if (timer > millis()) {
		    timer = millis();
		}
		if (status) {
		    timer = millis();
		}
		if (millis() - timer > 60000) {
		    return 1;
		}
		return 0;
	}

	void _update() {
	    if (cabinet_status()) {
	        digitalWrite(constant_pins::V_MEN_G, 1);
	        digitalWrite(constant_pins::V_MEN_R, 0);
	    }
	    else {
	        digitalWrite(constant_pins::V_MEN_G, 0);
	        digitalWrite(constant_pins::V_MEN_R, 1);
          //Serial.print("NOPE");
	    }
	    if (locker::door_status()) {
	        digitalWrite(constant_pins::V_DOOR_G, 1);
	        digitalWrite(constant_pins::V_DOOR_R, 0);
	    }
	    else {
	        digitalWrite(constant_pins::V_DOOR_G, 0);
	        digitalWrite(constant_pins::V_DOOR_R, 1);
	    }
	    if (locker::locker_status()) {
	        digitalWrite(constant_pins::V_LOCKER_G, 1);
	        digitalWrite(constant_pins::V_LOCKER_R, 0);
	    }
	    else {
	        digitalWrite(constant_pins::V_LOCKER_G, 0);
	        digitalWrite(constant_pins::V_LOCKER_R, 1);
	    }
	}
}

namespace client {
	String make_request(String type, int card[]) {
		String res = type;
		for (int i = 0; i < 8; i++) {
	        res += (char)card[i];
	    }
	    return res;
	}

	void greeting(int card[]) {
	    Serial3.print(make_request("}", card));
	}

	void edit(int card[]) {
	    Serial3.print(make_request("~", card));
	}

	void check(int card[]) {
		Serial3.print(make_request("|", card));
	}

	void receive() {
	    if (Serial3.available()) {
	        int ans = Serial3.read();
	        if (ans == 89) {
	            locker::unlock();
	            outside_led::green();
	            delay(5000);
	            locker::lock();
	        }
	        if (ans == 78) {
	            outside_led::red();
	            delay(2000);
	        }
	    }
	}
}

namespace handler {
	int _position;
	int _buffer[8];
	bool edit_query;

	const int MASTER_CARD[8] = {
	    55, 57, 55, 57, 48, 55, 55, 57
	}; //0 -> 48
	const int BAD_SYMBOLS_CNT = 9;
	const int BAD_SYMBOLS[9] = {
	    -1, 2, 3, 10, 13, 249, 191, 235, 0
	};
	const int LOCAL_DB_SIZE = 4;
	const int DEFINED_CARDS[4][8] = {
	    {66, 66, 57, 53, 65, 53, 66, 54},  //Vahta
	    {69, 54, 57, 55, 49, 69, 70, 57},  //Paramonov
	    {68, 57, 53, 52, 48, 57, 52, 57},  //Amelichev
	    {68, 57, 52, 49, 69, 51, 52, 57}   //Filippov
	};

	bool check_card(int a[], int b[]) {
	    for (int i = 0; i < 8; i++) {
	        if (a[i] != b[i]) {
	            return false;
	        }
	    }
	    return true;
	}

	bool is_valid(int a) {
	    for (int i = 0; i < BAD_SYMBOLS_CNT; i++) {
	        if (a == BAD_SYMBOLS[i]) {
	        	return false;
	    	}
	    }
	    return true;
	}

	void handle_card(int card[]) {
	    bool ok = false;
	    for (int i = 0; i < LOCAL_DB_SIZE; i++) {
	        ok = check_card(DEFINED_CARDS[i], card);
	        if (ok) {
	        	client::greeting(card);
	            locker::unlock();
	            outside_led::green();
	            delay(5000);
	            locker::lock();
	            return;
	        }
	    }
	    client::check(card);
	}

	void handle(int card[]) {
		if (check_card(card, MASTER_CARD)) {
			edit_query = true;
			outside_led::blue();
			delay(5000);	
		}
		else {
			if (edit_query) {
				//TODO: WebServer request
				client::edit(card);
				edit_query = false;
			}
			else {
				handle_card(card);
			}
		}
	}

	void _read() {
		int value = Serial.read();
	    if (!Serial.available()) {
	        _position = 0;
	        return;
	    }
		if (is_valid(value)) {
			_buffer[_position++] = value;
			if (_position == 8) {
        handle(_buffer);
				_position = 0;
			}
		}
	}
}

void interrupt() {
    security::_update();
}

void setup() {
    Serial.begin(9600);
    Serial3.begin(115200);
    pinMode(constant_pins::DOOR_SENSOR, INPUT); // защелка
    pinMode(constant_pins::LOCKER_SENSOR, INPUT); // дверь
    digitalWrite(constant_pins::DOOR_SENSOR, 1);
    digitalWrite(constant_pins::LOCKER_SENSOR, 1);
    pinMode(constant_pins::EXIT_BUTTON, INPUT);
    pinMode(constant_pins::LOCKER, OUTPUT);
    pinMode(constant_pins::OUTSIDE_RED, OUTPUT);
    pinMode(constant_pins::OUTSIDE_GREEN, OUTPUT);
    pinMode(constant_pins::OUTSIDE_BLUE, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(constant_pins::V_MEN_G,OUTPUT);
    pinMode(constant_pins::V_MEN_R,OUTPUT);
    pinMode(constant_pins::V_DOOR_G,OUTPUT);
    pinMode(constant_pins::V_DOOR_R,OUTPUT);
    pinMode(constant_pins::V_LOCKER_G,OUTPUT);
    pinMode(constant_pins::V_LOCKER_R,OUTPUT);
    pinMode(constant_pins::OUTSIDE_BUTTON, INPUT);
    digitalWrite(constant_pins::OUTSIDE_BUTTON, 1);
    pinMode(constant_pins::SOUND_OUTSIDE,OUTPUT);
    pinMode(constant_pins::SOUND_INSIDE,OUTPUT);
    pinMode(constant_pins::INSIDE_SENSOR_0_0, INPUT);
    pinMode(constant_pins::INSIDE_SENSOR_0_1, INPUT);
    pinMode(constant_pins::INSIDE_SENSOR_1_0, INPUT);
    pinMode(constant_pins::INSIDE_SENSOR_1_1, INPUT);
    security::timer = millis();
    door_bell::timer = millis();
    outside_led::current_red = 255;
    outside_led::current_green = 0;
    outside_led::current_blue = 0;
    handler::_position = 0;
    handler::edit_query = 0;
    FlexiTimer2::set(5, interrupt);
    FlexiTimer2::start();
    locker::lock();
}

void loop() {
    exit_button::check();
    outside_led::setCurrentColor();
    outside_led::recolor();
    client::receive();
    door_bell::play();
    handler::_read();
    delay(2);
}
