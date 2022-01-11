#include <tonc_bios.h>
#include <tonc_core.h>
#include <tonc_input.h>
#include <tonc_irq.h>
#include <tonc_tte.h>
#include <tonc_video.h>

#include <stdio.h>
#include <stdlib.h>

#include "core/mgba.h"

int main(void)
{
	mgba_open();

	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

	tte_init_chr4c_default(0, BG_CBB(0) | BG_SBB(31));
	tte_set_pos(32, 68);
	tte_write("mGBA -> tools -> log. Press A button!");

	irq_init(NULL);
	irq_enable(II_VBLANK);

	int previousCounter = 0;
	int counter = 0;

	mgba_printf(MGBA_LOG_DEBUG, "DEBUG - mgba_printf example");

	while (1) {
		VBlankIntrWait();

		key_poll();

		if (key_hit(KEY_A)) {
			++counter;
			mgba_printf(MGBA_LOG_INFO, "INFO - A button pressed");
		}

		if (counter != previousCounter) {
			mgba_printf(MGBA_LOG_DEBUG, "DEBUG - A button pressed %d times", counter);
			previousCounter = counter;
		}
	}

	mgba_close();

	return 1;
}
