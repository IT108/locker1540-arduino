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

	const int INSIDE_LIGHT = 9;

	const int SERVER_RESET = 30; 

	const int LIGHT_BUTTON = 28;
}

namespace constant_values {
	const int TIMER_GREEN = 5000;
	const int TIMER_RED = 2000;
	const int TIMER_BLUE = 2000;
	const int CARD_SIZE = 8;
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
	int current_red;
	int current_green;
	int current_blue;

	void led(int red, int green, int blue) {
		analogWrite(constant_pins::OUTSIDE_RED, red);
		analogWrite(constant_pins::OUTSIDE_GREEN, green);
		analogWrite(constant_pins::OUTSIDE_BLUE, blue);
	}

	void led_current() {
		led(current_red, current_green, current_blue);
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
	}
}

namespace security {
	extern long long timer;
	extern long long last_open_timer;
}

namespace inside_light {
	extern const long long TIMER_EMPTY;
	extern const long long TIMER_GAP;
 extern int is_button;
}

namespace locker {
	const int LOCK = 1;
	const int UNLOCK = 0;
	int door_closed = 0;

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
		int tmp = digitalRead(constant_pins::DOOR_SENSOR);
		if (tmp != door_closed) {
			door_closed = tmp;
			security::last_open_timer = millis();
		  inside_light::is_button = 0;
    }
		return door_closed;
	}
}

namespace exit_button {
	void check() {
		int status = digitalRead(constant_pins::EXIT_BUTTON);
		if (status != 0) {
			locker::unlock();
			outside_led::green();
			delay(constant_values::TIMER_GREEN);
			locker::lock();
		}
	}
}


namespace security {
	long long timer;
	long long last_open_timer;
	const long long TIMER_EMPTY = 60000LL;

	int cabinet_status() {
		bool status = 0;
		for (int i = constant_pins::INSIDE_SENSOR_0_0; i <= constant_pins::INSIDE_SENSOR_1_1; i++) {
			status |= digitalRead(i);
		}
		if (timer > millis()) {
			timer = millis();
		}
		if (status) {
			timer = millis();
		}
	}

	bool check_if_inside() {
		long long cur = millis();
		return cur < last_open_timer + inside_light::TIMER_EMPTY || timer > last_open_timer + inside_light::TIMER_GAP;
	}

	void update() {
		cabinet_status();
		if (!check_if_inside()) {
			digitalWrite(constant_pins::V_MEN_G, 1);
			digitalWrite(constant_pins::V_MEN_R, 0);
		}
		else {
			digitalWrite(constant_pins::V_MEN_G, 0);
			digitalWrite(constant_pins::V_MEN_R, 1);
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
	long long reset_time = millis();
	String make_request(String type, int card[]) {
		String res = type;
		for (int i = 0; i < constant_values::CARD_SIZE; i++) {
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
				delay(constant_values::TIMER_GREEN);
				locker::lock();
			}
			if (ans == 78) {
				outside_led::red();
				delay(constant_values::TIMER_RED);
			}
			if (ans == 33) {
				digitalWrite(constant_pins::SERVER_RESET, 0); 
				reset_time = millis();
				return;
			}
		}
		if (millis() - reset_time > 5000){
			digitalWrite(constant_pins::SERVER_RESET, 1);
		} 
	}
}

namespace handler {
	const int CARD_SIZE = 8;
	const int MASTER_CARD[CARD_SIZE] = {
		55, 57, 55, 57, 48, 55, 55, 57
	}; //0 -> 48
	const int BAD_SYMBOLS_SIZE = 9;
	const int BAD_SYMBOLS[BAD_SYMBOLS_SIZE] = {
		-1, 2, 3, 10, 13, 249, 191, 235, 0
	};
	const int LOCAL_DB_SIZE = 4;
	const int DEFINED_CARDS[LOCAL_DB_SIZE][CARD_SIZE] = {
		{66, 66, 57, 53, 65, 53, 66, 54},  // Vahta
		{69, 54, 57, 55, 49, 69, 70, 57},  // Paramonov
		{68, 57, 53, 52, 48, 57, 52, 57},  // Amelichev
		{68, 57, 52, 49, 69, 51, 52, 57}   // Filippov
	};

	int position;
	int buffer[CARD_SIZE];
	bool edit_query;


	bool check_card(int a[], int b[]) {
		for (int i = 0; i < constant_values::CARD_SIZE; i++) {
			if (a[i] != b[i]) {
				return false;
			}
		}
		return true;
	}

	bool is_valid(int a) {
		for (int i = 0; i < BAD_SYMBOLS_SIZE; i++) {
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
				delay(constant_values::TIMER_GREEN);
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
			delay(constant_values::TIMER_BLUE);	
		}
		else {
			if (edit_query) {
				client::edit(card);
				edit_query = false;
			}
			else {
				handle_card(card);
			}
		}
	}

	void read() {
		int value = Serial.read();
		if (!Serial.available()) {
			position = 0;
			return;
		}
		if (is_valid(value)) {
			buffer[position++] = value;
			if (position == constant_values::CARD_SIZE) {
				handle(handler::buffer);
				position = 0;
			}
		}
	}
}

namespace inside_light {
	int is_button = 0;
	int status = 0;
	long long button_timer = 0;
	const long long TIMER_EMPTY = 60000LL;
	const long long TIMER_GAP = 5000LL;

	void check_button() {
		if (!digitalRead(constant_pins::LIGHT_BUTTON)) {
			is_button ^= 1;
			button_timer = millis();
		}
	}

	void light() {
		digitalWrite(constant_pins::INSIDE_LIGHT, 1);	
		status = 1;
	}

	void unlight() {
		digitalWrite(constant_pins::INSIDE_LIGHT, 0);
		status = 0;
	}

	void update() {
		long long current_time = millis();
		if (current_time - button_timer < 1000) {
			return;
		}
		check_button();
		if (is_button && status == 0) {
			return;
		}
		if (is_button && status == 1) {
			unlight();
			return;
		}
		if (security::check_if_inside()) {
			light();
		}
		else {
			unlight();
		}
	}
}

void interrupt() {
	security::update();
	inside_light::update();
}

void setup() {
	Serial.begin(9600);
	Serial3.begin(115200);
	pinMode(constant_pins::DOOR_SENSOR, INPUT);
	pinMode(constant_pins::LOCKER_SENSOR, INPUT);
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
	pinMode(constant_pins::INSIDE_LIGHT, OUTPUT);
	pinMode(constant_pins::SERVER_RESET, OUTPUT);
	pinMode(constant_pins::LIGHT_BUTTON, INPUT);
	digitalWrite(constant_pins::LIGHT_BUTTON, 1);
	digitalWrite(constant_pins::SERVER_RESET, 1);
	security::timer = millis();
	door_bell::timer = millis();
	inside_light::button_timer = millis();
	security::timer = millis();
	inside_light::status = 0;
	outside_led::current_red = 255;
	outside_led::current_green = 0;
	outside_led::current_blue = 0;
	handler::position = 0;
	handler::edit_query = 0;
	FlexiTimer2::set(30, interrupt);
	FlexiTimer2::start();
	locker::lock(); 
}

void loop() {
	exit_button::check();
	outside_led::recolor();
	outside_led::led_current();
	client::receive();
	door_bell::play();
	handler::read();
	delay(2);
}
