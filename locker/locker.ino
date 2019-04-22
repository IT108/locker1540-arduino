#include <FlexiTimer2.h>
#include <QueueArray.h>

struct Event {
	long long timer;
	int value;
	Event() {
		timer = 0;
		value = 0;
	}
	Event(long long a, int b) {
		timer = a, value = b;
	}
};

struct Pin {
	int pin = -1;
	int type = -1;
	int rev = 0;

	Pin() {
		pin = -1;
		type = -1;
		rev = 0;
	}

	Pin(int a, int b, int c = 0) {
		pin = a, type = b;
		// rev = c;
		set_mode();
		if (c) {
			write(1, 'f');
		}
	}

	void set_mode() {
		pinMode(pin, type);
	}

	int read() {
		if (type != INPUT) {
			return 0;
		}
		return digitalRead(pin) ^ rev;
	}

	void write(int x, char c = 'x') {
		if (type != OUTPUT && c != 'f') {
			return;
		}
		return digitalWrite(pin, x);
	}

	void analog(int x) {
		if (type != OUTPUT) {
			return;
		}
		return analogWrite(pin, x);		
	}

	void tone(int a, int b) {
		::tone(pin, a, b);
	}

	void no_tone() {
		noTone(pin);
	}
};

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
	const long long TIMER_SECOND = 1000;
	const long long TIMER_TWO_SECONDS = 2 * TIMER_SECOND;
	const long long TIMER_THREE_SECONDS = 3 * TIMER_SECOND;
	const long long TIMER_FIVE_SECONDS = 5 * TIMER_SECOND;
	const long long TIMER_MINUTE = 60000;
	const long long TIMER_FIVE_MINUTES = 5 * TIMER_MINUTE;
	const long long TIMER_HALF_AN_HOUR = TIMER_MINUTE * 30;
	const long long TIMER_HOUR = TIMER_MINUTE * 60;
	const long long TIMER_GREEN = TIMER_FIVE_SECONDS;
	const long long TIMER_RED = TIMER_TWO_SECONDS;
	const long long TIMER_BLUE = TIMER_TWO_SECONDS;
	const int CARD_SIZE = 8;
}

namespace door_bell {
	long long timer;
	const int COUNT_NOTES = 9;
	const int WAITING_TIME = constant_values::TIMER_FIVE_SECONDS;
	const int BEEP_FREQUENCE = 1000;
	const int BEEP_LENGTH = 150;
	const Pin OUTSIDE_BUTTON(constant_pins::OUTSIDE_BUTTON, INPUT, 1);
	const Pin SOUND_INSIDE(constant_pins::SOUND_INSIDE, OUTPUT);

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
		if (OUTSIDE_BUTTON.read() || millis() - timer < WAITING_TIME) {
			return;
		}
		for (int i = 0; i < COUNT_NOTES; i++) {
			SOUND_INSIDE.tone(FREQUENCES[i], DURATIONS[i]);
			delay(DURATIONS[i]);
		}
		SOUND_INSIDE.no_tone();
		timer = millis();
	}

	void beep() {
		SOUND_INSIDE.tone(BEEP_FREQUENCE, BEEP_LENGTH);
		delay(BEEP_LENGTH);
		SOUND_INSIDE.no_tone();
	}
}

namespace outside_led {
	const int RED_COLORS[] = {255, 0, 0};
	const int GREEN_COLORS[] = {0, 255, 0};
	const int BLUE_COLORS[] = {0, 0, 255};
	const int YELLOW_COLORS[] = {255, 255, 0};
	int current_red = 255;
	int current_green = 0;
	int current_blue = 0;
	long long timer = 0;

	const Pin RED(constant_pins::OUTSIDE_RED, OUTPUT);
	const Pin GREEN(constant_pins::OUTSIDE_GREEN, OUTPUT);
	const Pin BLUE(constant_pins::OUTSIDE_BLUE, OUTPUT);

	void led(int red, int green, int blue) {
		if (millis() < timer) {
			return;
		}
		RED.analog(red);
		GREEN.analog(green);
		BLUE.analog(blue);
	}

	void add_time(long long t) {
		timer = max(timer, millis() + t);
	}

	void led_current() {
		led(current_red, current_green, current_blue);
	}

	void red() {
		led(RED_COLORS[0], RED_COLORS[1], RED_COLORS[2]);
	}
 
	void green() {
		led(GREEN_COLORS[0], GREEN_COLORS[1], GREEN_COLORS[2]);
	}

	void yellow() {
		led(YELLOW_COLORS[0], YELLOW_COLORS[1], YELLOW_COLORS[2]);
	}

	void blue() {
		led(BLUE_COLORS[0], BLUE_COLORS[1], BLUE_COLORS[2]);
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
	extern long long cabinet_balance;
	extern long long last_open_timer;
	void decrease();
	void increase();
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
	long long timer = 0;

	const Pin LOCKER(constant_pins::LOCKER, OUTPUT);
	const Pin DOOR_SENSOR(constant_pins::DOOR_SENSOR, INPUT, 1);
	const Pin LOCKER_SENSOR(constant_pins::LOCKER_SENSOR, INPUT, 1);

	void lock() {
		LOCKER.write(LOCK);
	}

	void unlock() {
		LOCKER.write(UNLOCK);
	}

	int locker_status() {
		return LOCKER_SENSOR.read();
	}

	int door_status() {
		int tmp = DOOR_SENSOR.read();
		if (tmp != door_closed) {
			door_closed = tmp;
			security::last_open_timer = millis();
		}
		return door_closed;
	}

	void add_time(long long add) {
		timer = max(timer, millis() + add);
	}

	void update() {
		if (millis() < timer) {
			unlock();
		}
		else {
			lock();
		}
	}
}

namespace exit_button {
	long long timer = 0;
	int button_status = 0;
	const long long TIMER_WAIT = constant_values::TIMER_THREE_SECONDS;

	const Pin EXIT_BUTTON(constant_pins::EXIT_BUTTON, INPUT);

	void check() {
		int current_status = EXIT_BUTTON.read();
		if (current_status == 1 && button_status == 0) {
			if (door_bell::timer + constant_values::TIMER_MINUTE > millis()) {
				security::increase();
			}
			else {
				security::decrease();
			}
			locker::add_time(constant_values::TIMER_GREEN);
			outside_led::green();
			outside_led::add_time(constant_values::TIMER_GREEN);
			timer = millis();
			door_bell::beep();
			button_status = 1;
			return;
		}
		if (current_status == 0 && millis() - timer > 100) {
			button_status = 0;
			return;
		}
		if (current_status == 1 && button_status == 1 && millis() - timer > TIMER_WAIT) {
			outside_led::yellow();
			outside_led::add_time(constant_values::TIMER_FIVE_MINUTES);
			locker::add_time(constant_values::TIMER_FIVE_MINUTES);
			button_status = 2;
			door_bell::beep();
		}
		if (current_status == 1 && button_status == 2 && millis() - timer > 2 * TIMER_WAIT) {
			outside_led::yellow();
			outside_led::add_time(constant_values::TIMER_HALF_AN_HOUR);
			locker::add_time(constant_values::TIMER_HALF_AN_HOUR);
			button_status = 3;
			door_bell::beep();
		}
		if (current_status == 1 && button_status == 3 && millis() - timer > 3 * TIMER_WAIT) {
			outside_led::yellow();
			outside_led::add_time(constant_values::TIMER_HOUR);
			locker::add_time(constant_values::TIMER_HOUR);
			button_status = 4;
			door_bell::beep();
		}
		if (current_status == 1 && button_status == 4 && millis() - timer > 4 * TIMER_WAIT) {
			outside_led::timer = millis();
			locker::timer = millis();
			door_bell::beep();
			button_status = 5;
		}
	}
}

namespace security {
	long long timer;
	long long last_open_timer;
	long long cabinet_balance;
	const long long TIMER_EMPTY = constant_values::TIMER_MINUTE;
	const long long TIMER_KILL = constant_values::TIMER_HALF_AN_HOUR;
	const long long TIMER_GAP = constant_values::TIMER_FIVE_SECONDS;
	QueueArray <Event> queue;

	const Pin MEN_R(constant_pins::V_MEN_R, OUTPUT);
	const Pin MEN_G(constant_pins::V_MEN_G, OUTPUT);
	const Pin DOOR_R(constant_pins::V_DOOR_R, OUTPUT);
	const Pin DOOR_G(constant_pins::V_DOOR_G, OUTPUT);
	const Pin LOCKER_R(constant_pins::V_LOCKER_R, OUTPUT);
	const Pin LOCKER_G(constant_pins::V_LOCKER_G, OUTPUT);

	const int SENSORS_SIZE = 4;
	const Pin SENSORS[SENSORS_SIZE] = {
		Pin(constant_pins::INSIDE_SENSOR_0_0, INPUT),
		Pin(constant_pins::INSIDE_SENSOR_0_1, INPUT),
		Pin(constant_pins::INSIDE_SENSOR_1_0, INPUT),
		Pin(constant_pins::INSIDE_SENSOR_1_1, INPUT)
	};


	void decrease() {
		queue.push(Event(millis() + TIMER_GAP * 2, -1));
	}

	void increase() {
		queue.push(Event(millis() + TIMER_GAP * 2, 1));
	}

	int cabinet_status() {
		bool status = 0;
		for (int i = 0; i < SENSORS_SIZE; i++) {
			status |= SENSORS[i].read();
		}
		if (timer > millis()) {
			timer = millis();
		}
		if (status) {
			timer = millis();
		}
	}

	bool check_if_inside() {
		long long current_timer = millis();
		while (queue.count() && queue.front().timer < current_timer) {
			cabinet_balance += queue.front().value;
			queue.pop();
		}
		if (cabinet_balance < 0) {
			cabinet_balance = 0;
		}
		if (current_timer < timer + TIMER_GAP) {
			cabinet_balance = max(cabinet_balance, 1);
		}
		if (current_timer > timer + TIMER_KILL) {
			cabinet_balance = 0;
			while (queue.count()) {
				queue.pop();
			}
		}
		return cabinet_balance > 0;
	}

	void red(Pin R, Pin G) {
		R.write(1);
		G.write(0);
	}

	void green(Pin R, Pin G) {
		R.write(0);
		G.write(1);
	}

	void update() {
		cabinet_status();
		if (!check_if_inside()) {
			green(MEN_R, MEN_G);
		}
		else {
			red(MEN_R, MEN_G);
		}
		if (locker::door_status()) {
			green(DOOR_R, DOOR_G);
		}
		else {
			red(DOOR_R, DOOR_G);
		}
		if (locker::locker_status()) {
			green(LOCKER_R, LOCKER_G);
		}
		else {
			red(LOCKER_R, LOCKER_G);
		}
	}
}

namespace inside_light {
	bool automatic_mode = true;
	int is_button = 0;
	int status = 0;
	long long timer = 0;
	const long long TIMER_EMPTY = constant_values::TIMER_MINUTE;
	const long long TIMER_GAP = constant_values::TIMER_FIVE_SECONDS;

	const Pin LIGHT_BUTTON(constant_pins::LIGHT_BUTTON, INPUT, 1);
	const Pin INSIDE_LIGHT(constant_pins::INSIDE_LIGHT, OUTPUT);

	void check_button() {
		if (!LIGHT_BUTTON.read()) {
			is_button ^= 1;
			timer = millis();
		}
	}

	void light() {
		if (status == 1) {
			return;
		}
		if (!automatic_mode) {
			return;
		}
		INSIDE_LIGHT.write(1);
		status = 1;
	}

	void unlight() {
		if (status == 0) {
			return;
		}
		if (!automatic_mode) {
			return;
		}
		INSIDE_LIGHT.write(0);
		status = 0;
	}

	void update() {
		long long current_timer = millis();
		if (current_timer - timer < constant_values::TIMER_SECOND) {
			return;
		}
		check_button();
		if (is_button) {
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

namespace client {
	long long reset_time = millis();
	const Pin SERVER_RESET(constant_pins::SERVER_RESET, OUTPUT, 1);
	const String GREETING = "}";
	const String EDIT = "~";
	const String CHECK = "|";

	const int RESPONSE_OPEN = 89;
	const int RESPONSE_CLOSE = 78;
	const int RESPONSE_RESET = 33;
	const int RESPONSE_LIGHT_ON = 91;
	const int RESPONSE_LIGHT_AUTO = 92;
	const int RESPONSE_LIGHT_OFF = 93;


	String make_request(String type, int card[]) {
		String res = type;
		for (int i = 0; i < constant_values::CARD_SIZE; i++) {
			res += (char)card[i];
		}
		return res;
	}

	void greeting(int card[]) {
		Serial3.print(make_request(GREETING, card));
	}

	void edit(int card[]) {
		Serial3.print(make_request(EDIT, card));
	}

	void check(int card[]) {
		Serial3.print(make_request(CHECK, card));
	}

	void receive() {
		if (Serial3.available()) {
			int ans = Serial3.read();
			if (ans == RESPONSE_OPEN) {
				security::increase();
				outside_led::green();
				outside_led::add_time(constant_values::TIMER_GREEN);
				locker::add_time(constant_values::TIMER_GREEN);
			}
			if (ans == RESPONSE_CLOSE) {
				outside_led::red();
				outside_led::add_time(constant_values::TIMER_RED);
			}
			if (ans == RESPONSE_RESET) {
				digitalWrite(constant_pins::SERVER_RESET, 0); 
				reset_time = millis();
				return;
			}
			if (ans == RESPONSE_LIGHT_ON) {
				inside_light::light();
				inside_light::automatic_mode = false;
			}
			if (ans == RESPONSE_LIGHT_AUTO) {
				inside_light::automatic_mode = true;
				inside_light::unlight();
			}
			if (ans == RESPONSE_LIGHT_OFF) {
				inside_light::unlight();
				inside_light::automatic_mode = false;
			}
		}
		if (millis() - reset_time > constant_values::TIMER_FIVE_SECONDS){
			SERVER_RESET.write(1);
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

	int position = 0;
	int buffer[CARD_SIZE];
	bool edit_query = 0;


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
				locker::add_time(constant_values::TIMER_GREEN);
				outside_led::green();
				outside_led::add_time(constant_values::TIMER_GREEN);
				security::increase();
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

namespace radio {

	long long timer;
	const long long TIMER_GAP = 3000;

	void send(char x, char y) {
		if (millis() - timer < TIMER_GAP) {
			return;
		}
		Serial2.write(x * 10 + y);
		Serial2.write('\n');
		timer = millis();
	}

	int receive() {
		if (!Serial2.available()) {
			return 0;
		}
		int x = Serial2.read();
		return x;
	}

};



void interrupt() {
	security::update();
	inside_light::update();
	locker::update();
}

void setup() {
	Serial.begin(9600);
	Serial3.begin(115200);
	Serial2.begin(9600);
	pinMode(13, OUTPUT);
	
	security::timer = millis();
	door_bell::timer = millis();
	inside_light::timer = millis();
	security::last_open_timer = millis();
	security::timer = millis();
	outside_led::timer = millis();
	exit_button::timer = millis();
	locker::timer = millis();
	radio::timer = millis();
	FlexiTimer2::set(20, interrupt);
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
	radio::send(0, security::cabinet_balance);
	delay(2);
}

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::::^\.*+=%=%===================%%%=*-\^:::::::::::::::::::::::::::::::::
::::::::::::::::::::::::^%.*=%=========+=====*:-=++::=+:*==+=+===%======%=+-\^::::::::::::::::::::::::
:::::::::::::::::::%.*========*=+*=======+*=\\.+-:.\^*--=**+=+*:::%%% -*+=======+-\:::::::::::::::::::
:::::::::::::::\*====%===+.::::::^*==+*+=+:==++*+:+*+*+*^:::::::::::::::::::\+=+====%* ^::::::::::::::
:::::::::::^:===%==.\*:%^*\:::::::-=.\\+%:::\-::%==**:* :::::::&::::::&&:::::-+=*  *=====*%:::::::::::
::::::::^-=====.^:.*%:^* :::::::::::\%*%:::^%^::::*::: ::.=+^:::::::::::::::::::-:+*^:\+%===*^::::::::
::::::%=====\:::*-:::.-::::::::::*:^^=^:::: .:::\:%%.%==*=::^:::::::::::::::::%%%= %=*^::%===== ::::::
::::^+%+=*^:::\:::::::::::::::::^^:::^:::::::::::::::::::::::::::::::::::::::::::::::::::::: ====\::::
:::-%==::::::::::::::==========::::::::::::::::===========::::::::::::=================:::%^^^.===*^::
::*===%::::^+^:::::===============:::::::: .:::===============::: ::::=================::^-:::::*===^:
::==+^::::::::::::=================::::::::: ::======:::=======:::\*::=================:::-\::::::===:
%===%:::::\:::::======:::::::=======::::::+%:::======::::======:::^+^::::::=======::::::::^*:::::^*==:
+==*::::::. ::::=====:::::::::======::::::*%:::===============::::^+^::::::=======:::::::^:*^:::::-==:
+==+::::::. ::::=====:::::::::======:::\ :*%:::============::::::::=:::::::=======::::::::==^:::::-==:
^==%\:::::%*::::======:::::::=======:::::*+%:::======:=====:::::::^+:::::::=======::::::::==.::::^+==:
:-==+^:::::-\::::=================:::::::-- :::=====:::======:::::\::::::::=======::::::::%%:::::*==+:
:::===\:::::*\::::.==============:::::: :::::::======:::======:::::%:::::::=======::::::::.%:-%^+==+^:
:::.%==::::::::::::::=========:::::::::::::::::======::::=======::^:::::-::=======:::::::^=--.*%==::::
::::^*===*%:::^*%::::::::::::::::*^:.+\::::-::::::::::::::::::::::::::::^::::::::::::::-*\:-+===+%::::
::::::^*=%==::::%+%::::* :::::=\:::::+ :::: ::::::-^:::::^%^::::-\:::::..:::::*\:::^+*^ *======^::::::
::::::::: =====*^::+-::::+ ::::.*:^*=.: ::::=%::::-^:::::. :::::.::::%=%::::+ :::\+\:^-==+%=::::::::::
:::::::::::: +====%:\%*:%::.+%::::-:.++ -:::^:::::-^::::^*::::*%:::^+ ::: =\:^.+ %-======-::::::::::::
:::::::::::::::%-+=========+- -=: \.=-   *:  -+  \:    .+   *:   ** \.+* .*%=========:\:::::::::::::::
::::::::::::::::::::\-+%=======+::++.%-*.-+= :\:%.*-.::*:-^%%%%..\ *============: ^:::::::::::::::::::
:::::::::::::::::::::::::^\.*==============+====+******+++============%==+-\%:::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::^%\.:*==%%%==========%%%%===+*- %^^:::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/