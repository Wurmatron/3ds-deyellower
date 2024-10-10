#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

PrintConsole topScreen, bottomScreen;
long timeUntilSleep = 100000;

void displayMenu() {
	consoleSelect(&bottomScreen);
	// Display "Menu":
	printf("\x1b[3;15HDeyellower");
   	printf("\x1b[13;5HSettings");
    printf("\x1b[13;30HBoth");
    printf("\x1b[8;18HTop");
    printf("\x1b[20;16HBotttom");
	printf("\x1b[28;10HPress Start to stop.");
	printf("\x1b[30;13Hby Wurmatron v0");
	consoleSelect(&topScreen);
	printf("\x1b[30;38H%ld", timeUntilSleep);
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

	bool top = false;
	bool bottom = false;
	bool menu = true;
	long untilWake = 10000;

	// Main loop
	while (aptMainLoop())
	{

		hidScanInput();
		u32 kDown = hidKeysDown();

		// Check for key input
		if (kDown & KEY_DUP) {
			top = true;
			bottom = false;
			menu = false;
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

		if(menu) {
			displayMenu();
		} else {
			if(timeUntilSleep > 0) {
				timeUntilSleep--;
				// Set top to white
				if (top) {
					consoleSelect(&topScreen);
					for (int i = 0; i < 1500;i++){
        	    		printf("\x1b[47;30m \x1b[0m");
        	  	  }
				} else {
					consoleSelect(&topScreen);
					consoleClear();
				}
				// Set bottom to white
				if (bottom) {
					consoleSelect(&bottomScreen);
         	 	  for (int i = 0; i < 1200;i++){
         			   	printf("\x1b[47;30m \x1b[0m");
         		   }
				} else {
					consoleSelect(&bottomScreen);
					consoleClear();
				}
			} else {
				clearScreen();
				consoleSelect(&bottomScreen);
				printf("\x1b[16;14HSleeping ...");
				printf("\x1b[20;12HSleep Left: %ld", untilWake);
				if(untilWake > 0) {
					untilWake--;
				} else {
					timeUntilSleep = 100000;
					untilWake = 10000;
				}	
			} 
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
