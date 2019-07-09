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
		if (c) {
			rev = 1;
		}
		set_mode();
		if (c == 1) {
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

struct Timer {
	long long value;
	int need_to_check;

	Timer() {}
	Timer(int x = 0) {
		need_to_check = x;
		value = millis();
	}

	void set(long long x) {
		value = x;
	}

	void update() {
		value = millis();
	}

	void check() {
		if (value > millis()) {
			update();
		}
	}

	long long get() {
		if (need_to_check) {
			check();
		}
		return value;
	}

	long long diff(long long x = -1) {
		if (x == -1) {
			x = millis();
		}
		return abs(value - x);
	}

	bool already_past() {
		return value < millis();
	}
};

namespace constant_pins {
	const int V_MEN_R = 29;
	const int V_MEN_G = 27;
	const int V_DOOR_R = 31;
	const int V_DOOR_G = 33;
	const int V_LOCKER_R = 35;
	const int V_LOCKER_G = 37;

	const int OUTSIDE_BUTTON = 53;
	const int OUTSIDE_RED = 44;
	const int OUTSIDE_GREEN = 45;
	const int OUTSIDE_BLUE = 46;

	const int LOCKER = 25;

	const int SOUND_OUTSIDE = 43;
	const int SOUND_INSIDE = 9;

	const int DOOR_SENSOR = 6;
	const int LOCKER_SENSOR = 7;
	const int EXIT_BUTTON = A0;

	const int INSIDE_SENSOR_0_0 = 2;
	const int INSIDE_SENSOR_0_1 = 3;
	const int INSIDE_SENSOR_1_0 = 4;
	const int INSIDE_SENSOR_1_1 = 5;
	const int LIGHT_BUTTON = 11;

	const int RELAY_0 = 36;
	const int RELAY_1 = 34;
	const int RELAY_2 = 32;
	const int RELAY_3 = 30;

}

namespace constant_values {
	const long long DELAY_SECOND = 1000;
	const long long DELAY_TWO_SECONDS = 2 * DELAY_SECOND;
	const long long DELAY_THREE_SECONDS = 3 * DELAY_SECOND;
	const long long DELAY_FIVE_SECONDS = 5 * DELAY_SECOND;
	const long long DELAY_MINUTE = 60000;
	const long long DELAY_FIVE_MINUTES = 5 * DELAY_MINUTE;
	const long long DELAY_HALF_AN_HOUR = DELAY_MINUTE * 30;
	const long long DELAY_HOUR = DELAY_MINUTE * 60;
	const long long DELAY_GREEN = DELAY_FIVE_SECONDS;
	const long long DELAY_RED = DELAY_TWO_SECONDS;
	const long long DELAY_BLUE = DELAY_TWO_SECONDS;
	const int CARD_SIZE = 8;
}

namespace door_bell {
	const int COUNT_NOTES = 9;
	const int WAITING_DELAY = constant_values::DELAY_FIVE_SECONDS;
	const int BEEP_FREQUENCE = 1000;
	const int BEEP_LENGTH = 150;
	const Pin OUTSIDE_BUTTON(constant_pins::OUTSIDE_BUTTON, INPUT, 1);
	const Pin SOUND_INSIDE(constant_pins::SOUND_INSIDE, OUTPUT);
	const Timer TIMER(0);

	const int FREQUENCES[COUNT_NOTES] = {
		392, 392, 392, 311, 466, 392, 311, 466, 392
	};
	const int DURATIONS[COUNT_NOTES] = {
		350, 350, 350, 250, 100, 350, 250, 100, 700
	};

	void play() {
		TIMER.check();
		if (!OUTSIDE_BUTTON.read() || TIMER.diff() < WAITING_DELAY) {
			return;
		}
		for (int i = 0; i < COUNT_NOTES; i++) {
			SOUND_INSIDE.tone(FREQUENCES[i], DURATIONS[i]);
			delay(DURATIONS[i]);
		}
		SOUND_INSIDE.no_tone();
		TIMER.update();
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
	const Timer TIMER(0);
	const Pin RED(constant_pins::OUTSIDE_RED, OUTPUT);
	const Pin GREEN(constant_pins::OUTSIDE_GREEN, OUTPUT);
	const Pin BLUE(constant_pins::OUTSIDE_BLUE, OUTPUT);

	void led(int red, int green, int blue) {
		if (!TIMER.already_past()) {
			return;
		}
		RED.analog(red);
		GREEN.analog(green);
		BLUE.analog(blue);
	}

	void add_time(long long t) {
		TIMER.set(max(TIMER.get(), millis() + t));
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
	extern const Timer TIMER;
	extern const Timer LAST_OPEN_TIMER;
	extern long long cabinet_balance;
	void decrease();
	void increase();
}

namespace inside_light {
	extern const long long DELAY_EMPTY;
	extern const long long DELAY_GAP;
	extern int is_button;
}

namespace locker {
	const int LOCK = 1;
	const int UNLOCK = 0;
	int door_closed = 0;
	const Timer TIMER(0);

	const Pin LOCKER(constant_pins::LOCKER, OUTPUT);
	const Pin DOOR_SENSOR(constant_pins::DOOR_SENSOR, INPUT, 1);
	const Pin LOCKER_SENSOR(constant_pins::LOCKER_SENSOR, INPUT, 1);

	void lock() {
		LOCKER.write(LOCK);
	}

	void unlock() {
		LOCKER.write(UNLOCK);
	}

	int locker_status() { // 1 for locker not working
		return !LOCKER_SENSOR.read();
	}

	int door_status() { // 1 for closed door
		int tmp = 1 ^ DOOR_SENSOR.read();
		if (tmp != door_closed) {
			door_closed = tmp;
			security::LAST_OPEN_TIMER.update();
		}
		return door_closed;
	}

	void add_time(long long add) {
		TIMER.set(max(TIMER.get(), millis() + add));
	}

	void update() {
		if (TIMER.already_past()) {
			lock();
		}
		else {
			unlock();
		}
	}
}

namespace exit_button {
	const Timer TIMER(0);
	int button_status = 0;
	int current_status = 0;
	const long long DELAY_WAIT = constant_values::DELAY_THREE_SECONDS;

	const Pin EXIT_BUTTON(constant_pins::EXIT_BUTTON, INPUT, 1);

	void check() {
		current_status = EXIT_BUTTON.read();
		if (current_status == 1 && button_status == 0) {
			if (door_bell::TIMER.diff() < constant_values::DELAY_MINUTE) {
				security::increase();
			}
			else {
				security::decrease();
			}
			locker::add_time(constant_values::DELAY_GREEN);
			outside_led::green();
			outside_led::add_time(constant_values::DELAY_GREEN);
			TIMER.update();
			door_bell::beep();
			button_status = 1;
			return;
		}
		if (current_status == 0 && TIMER.diff() > 100) {
			button_status = 0;
			return;
		}
		if (current_status == 1 && button_status == 1 && TIMER.diff() > DELAY_WAIT) {
			security::increase();
			outside_led::yellow();
			outside_led::add_time(constant_values::DELAY_FIVE_MINUTES);
			locker::add_time(constant_values::DELAY_FIVE_MINUTES);
			button_status = 2;
			door_bell::beep();
		}
		if (current_status == 1 && button_status == 2 && TIMER.diff() > 2 * DELAY_WAIT) {
			outside_led::yellow();
			outside_led::add_time(constant_values::DELAY_HALF_AN_HOUR);
			locker::add_time(constant_values::DELAY_HALF_AN_HOUR);
			button_status = 3;
			door_bell::beep();
		}
		if (current_status == 1 && button_status == 3 && TIMER.diff() > 3 * DELAY_WAIT) {
			outside_led::yellow();
			outside_led::add_time(constant_values::DELAY_HOUR);
			locker::add_time(constant_values::DELAY_HOUR);
			button_status = 4;
			door_bell::beep();
		}
		if (current_status == 1 && button_status == 4 && TIMER.diff() > 4 * DELAY_WAIT) {
			outside_led::TIMER.update();
			locker::TIMER.update();
			door_bell::beep();
			button_status = 0;
		}
	}
}

namespace security {
	long long cabinet_balance;
	const Timer TIMER(0);
	const Timer LAST_OPEN_TIMER(0);
	const long long DELAY_EMPTY = constant_values::DELAY_MINUTE;
	const long long DELAY_KILL = constant_values::DELAY_HALF_AN_HOUR;
	const long long DELAY_GAP = constant_values::DELAY_FIVE_SECONDS;
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
		queue.push(Event(millis() + DELAY_GAP * 2, -1));
	}

	void increase() {
		cabinet_balance++;
	}

	int cabinet_status() {
		bool status = 0;
		for (int i = 0; i < SENSORS_SIZE; i++) {
			status |= SENSORS[i].read();
		}
		TIMER.check();
		if (status) {
			TIMER.update();
		}
	}

	bool check_if_inside() {
		Timer current_timer(0);
		while (queue.count() && queue.front().timer < current_timer.get()) {
			cabinet_balance += queue.front().value;
			queue.pop();
		}
		if (cabinet_balance < 0) {
			cabinet_balance = 0;
		}
		if (TIMER.diff() < DELAY_GAP) {
			cabinet_balance = max(cabinet_balance, 1);
		}
		if (TIMER.diff() > DELAY_KILL) {
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
	const Timer TIMER(0);
	const long long DELAY_EMPTY = constant_values::DELAY_MINUTE;
	const long long DELAY_GAP = constant_values::DELAY_FIVE_SECONDS;

	const Pin LIGHT_BUTTON(constant_pins::LIGHT_BUTTON, INPUT, 2);
	const Pin EMPTY_RELAYS[] = {
		Pin(constant_pins::RELAY_0, OUTPUT),
		Pin(constant_pins::RELAY_1, OUTPUT),
		Pin(constant_pins::RELAY_2, OUTPUT),
		Pin(constant_pins::RELAY_3, OUTPUT),
	};
	const Pin INSIDE_LIGHT = EMPTY_RELAYS[1];

	void check_button() {
		if (LIGHT_BUTTON.read()) {
			is_button ^= 1;
			TIMER.update();
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
		if (TIMER.diff() < constant_values::DELAY_SECOND) {
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
	const String GREETING = "play_greet";
	const String CHECK = "check_card";

	const int RESPONSE_OPEN = 89;
	const int RESPONSE_CLOSE = 78;
	const int RESPONSE_RESET = 33;
	const int RESPONSE_LIGHT_ON = 91;
	const int RESPONSE_LIGHT_AUTO = 92;
	const int RESPONSE_LIGHT_OFF = 93;


	String make_request(String operation, int card[]) {
		String res = "[" + operation + "]";
		res += "card:";
		for (int i = 0; i < constant_values::CARD_SIZE; i++) {
			res += (char)card[i];
		}
		res += "\r\n";
		return res;
	}

	void greeting(int card[]) {
		Serial.print(make_request(GREETING, card));
	}

	void check(int card[]) {
		Serial.print(make_request(CHECK, card));
	}

	void receive() {
		if (Serial.available()) {
			int ans = Serial.read();
			if (ans == RESPONSE_OPEN) {
				security::increase();
				outside_led::green();
				outside_led::add_time(constant_values::DELAY_GREEN);
				locker::add_time(constant_values::DELAY_GREEN);
			}
			if (ans == RESPONSE_CLOSE) {
				outside_led::red();
				outside_led::add_time(constant_values::DELAY_RED);
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
	}
}

namespace logger {
	void card();
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
		logger::card();
		for (int i = 0; i < LOCAL_DB_SIZE; i++) {
			ok = check_card(DEFINED_CARDS[i], card);
			if (ok) {
				client::greeting(card);
				locker::add_time(constant_values::DELAY_GREEN);
				outside_led::green();
				outside_led::add_time(constant_values::DELAY_GREEN);
				security::increase();
				return;
			}
		}
		client::check(card);
	}

	void read() {
		int value = Serial1.read();
		if (!Serial1.available()) {
			position = 0;
			return;
		}
		if (is_valid(value)) {
			buffer[position++] = value;
			if (position == constant_values::CARD_SIZE) {
				handle_card(handler::buffer);
				position = 0;
			}
		}
	}
}

namespace radio {
	const Timer TIMER(0);
	const long long DELAY_GAP = constant_values::DELAY_THREE_SECONDS;

	void send(char x, char y) {
		if (TIMER.diff() < DELAY_GAP) {
			return;
		}
		Serial2.write(x * 10 + y);
		Serial2.write('\n');
		TIMER.update();
	}

	int receive() {
		if (!Serial2.available()) {
			return 0;
		}
		int x = Serial2.read();
		return x;
	}
};

namespace logger {
	const Timer TIMER(0);
	
	void space() {
		Serial.print(' ');
	}

	void enter() {
		Serial.println();
	}

	void led() {
		Serial.print("led R G B is_online");
		space();
		Serial.print(outside_led::current_red);
		space();
		Serial.print(outside_led::current_green);
		space();
		Serial.print(outside_led::current_blue);
		space();
		Serial.print(outside_led::TIMER.already_past());
		enter();
	}

	void sensors() {
		Serial.print("Inside sensors 1 2 3 4 cabinet_balance");
		space();
		for (int i = 0; i < 4; i++) {
			Serial.print(security::SENSORS[i].read());
			space();
		}
		Serial.print((int)security::cabinet_balance);
		enter();
	}

	void security() {
		Serial.print("Security persons locker door");
		space();
		Serial.print(!security::check_if_inside());
		space();
		Serial.print(locker::locker_status());
		space();
		Serial.print(locker::door_status());
		enter();
	}

	void light() {
		Serial.print("Light status button");
		space();
		Serial.print(inside_light::status);
		space();
		Serial.print(inside_light::LIGHT_BUTTON.read());
		enter();
	}

	void card() {
		Serial.print("New card come");
		space();
		for (int i = 0; i < handler::CARD_SIZE; i++) {
			Serial.print((char)handler::buffer[i]);
		}
		enter();
	}

	void exit_button() {
		Serial.print("Exit_button status current");
		space();
		Serial.print(exit_button::button_status);
		space();
		Serial.print(exit_button::EXIT_BUTTON.read());
		enter();
	}

	void locker() {
		Serial.print("locker status");
		space();
		Serial.print(locker::locker_status());
		enter();
	}

	void update() {
		if (!TIMER.already_past()) {
			return;
		}
		TIMER.set(millis() + constant_values::DELAY_THREE_SECONDS);
		Serial.println("============== DEBUG OUTPUT ===========");
		led();
		sensors();
		security();
		light();
		exit_button();
		locker();
	}
}



void interrupt() {
	security::update();
	inside_light::update();
	locker::update();
	logger::update();
}

void setup() {
	Serial.begin(9600);
    Serial1.begin(9600);
    Serial2.begin(9600);
	pinMode(13, OUTPUT);
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
