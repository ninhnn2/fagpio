#include <stdio.h>
#include "fagpio.h"

int main(void) {

	fagpio_setup();

	pinMode(3, 0);
	pinMode(4, 0);
	pinMode(5, 0);

	while(1) {

		digitalWrite(3, 1);
		digitalWrite(4, 1);
		digitalWrite(5, 1);

		usleep(118);

		digitalWrite(3, 0);
		digitalWrite(4, 0);
		digitalWrite(5, 0);

		usleep(118);
	}

	fagpio_free();

	return 0;
}
