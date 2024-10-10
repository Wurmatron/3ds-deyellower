#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

PrintConsole topScreen, bottomScreen;

void displayMenu() {
	consoleSelect(&bottomScreen);
	// Display "Menu":
	printf("\x1b[3;15HDeyellower");
   	printf("\x1b[13;5HSettings");
    printf("\x1b[13;30HBoth");
    printf("\x1b[8;18HTop");
    printf("\x1b[18;16HBotttom");
	printf("\x1b[28;10HPress Start to stop.");
	printf("\x1b[30;13Hby Wurmatron v0");
}

void clearScreen() {
	consoleSelect(&topScreen);
	consoleClear();
	consoleSelect(&bottomScreen);
	consoleClear();
}

int main(int argc, char **argv)
{
	gfxInitDefault();
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);

    displayMenu();
	bool top = false;
	bool bottom = false;
	bool menu = false;

	// Main loop
	while (aptMainLoop())
	{

		hidScanInput();
		u32 kDown = hidKeysDown();

		if (kDown & KEY_DUP) {
			top = true;
			bottom = false;
			clearScreen();
		} else if(kDown & KEY_DRIGHT) {
			top = true;
			bottom = true;
			menu = false;
			clearScreen();
		} else if(kDown & KEY_DDOWN) {
			top = false;
			bottom = true;
			menu = false;
			clearScreen();
		} else if(kDown & KEY_DLEFT) {
			top = false;
			bottom = false;
			menu = true;
			clearScreen();
		}

		// Set top to white
		if (top) {
			consoleSelect(&topScreen);
			for (int i = 0; i < 1500;i++){
            	printf("\x1b[47;30m \x1b[0m");
            }
		}

		// Set bottom to white
		if (bottom) {
			consoleSelect(&bottomScreen);
            for (int i = 0; i < 1200;i++){
            	printf("\x1b[47;30m \x1b[0m");
            }
		}

		if(menu) {
			displayMenu();
		}

		// Close When Start is pushed
		if (kDown & KEY_START) break;

		gfxFlushBuffers();
		gfxSwapBuffers();

		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
