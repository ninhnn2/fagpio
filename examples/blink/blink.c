#include <stdio.h>
#include "fagpio.h"

int main(void) {

	fagpio_setup();

	pinMode(4, 1);
	pinMode(5, 1);
	pinMode(6, 1);
	pinMode(7, 1);

	while(1) {

		digitalWrite(4, 1);
		digitalWrite(5, 1);
		digitalWrite(6, 1);
		digitalWrite(7, 1);
		usleep(500);
		digitalWrite(4, 0);
		digitalWrite(5, 0);
		digitalWrite(6, 0);
		digitalWrite(7, 0);
		usleep(500);
	}

	fagpio_free();

	return 0;
}
