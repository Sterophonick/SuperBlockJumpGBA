/* Main source file for Super Block Jump Game Boy Advance Edition. Feel free to edit and recompile the source if you want. If you are to recompile the game, You will need DevKit Advance and place it in C:\devkitadv\*/
void vblfunc();
#include "..\inc\agb_lib.h" //main function library (that I made)
u16* ExtWRAM = (u16*)0x02000000;
#include <string.h> //main function library (that I made)
#include "..\inc\defs.h" //external definitions, variables
#include "..\inc\gbfs.h" //gbfs
#include "..\inc\more.h" //other functions

#define startpressed keyDown(KEY_START)
#define selectpressed keyDown(KEY_SELECT)
/*
	GBA HARDWARE
	CPU: 32-bit arm7tdmi RISC 16.78MHz
	RAM: 32kb internal, 256kb external, 96kb VRAM
	DSP: TFT LCD, 15-bit 240x160
	ROM: 32MB
	SRAM/EEPROM: 32-64kb
	OAM: 128 Sprites
	BIOS: 16kb
*/
//The lowest amount of sprites that I want on screen is 6.
/*
SRAM Slots:
1. Crash Variable
2. File 1
3. File 2
4. File 3 
5.  RNG Seed (For random number generation)
*/

#define BLOCK_OAM 0
#define GOAL_OAM 48
#define GEM_OAM 296
#define FIREBALL_OAM 32
#define VERSION_OAM 280
#define JUMPREFRESHER_OAM 56
#define PLAY_OAM 88
#define PONG_OAM 120
#define RESTART_OAM 152
#define SPIKE_OAM 184
#define TINFOIL_OAM 120
#define ENEMY_OAM 360

void playSound(int s) //Sound play Function
{
    REG_SOUNDCNT1_H = 0x0B04;                                                       //REG_SOUNDCNT_H = 0000 1011 0000 0100, volume = 100, sound goes to the left, sound goes to the right, timer 0 is used, FIFO buffer reset
    REG_SOUNDCNT1_X = 0x0080;                                                       //REG_SOUNDCNT_X = 0000 0000 1000 0000, enable the sound system, DMA 1
    REG_SD1SAD = (unsigned long)sound[s].song;                                //REG_DM1SAD = NAME, address of DMA source is the digitized music sample
    REG_SD1DAD = 0x040000A0;                                                   //REG_DM1DAD = REG_SGFIFOA, address of DMA destination is FIFO buffer for direct sound A
    REG_SD1CNT_H = 0xB640;                                                       //REG_DM1CNT_H = 1011 0110 0100 0000, DMA destination is fixed, repeat transfer of 4 bytes when FIFO , buffer is empty, enable DMA 1 (number of DMA transfers is ignored), INTERRUPT
    REG_TM0SD = 65536 - (16777216 / sound[s].frequency);                          //REG_TM0D = 65536-(16777216/frequency);, play sample every 16777216/frequency CPU cycles
    REG_TMSDCNT = 0x00C0;
}

int main() //Entry Point
{
	if ((keyDown(KEY_A))AND(keyDown(KEY_B))) { //SRAM Clear Function
		FadeOut(0); //Quick fade out
		while (((keyDown(KEY_A))OR(keyDown(KEY_B)))); //waits until a or b is not pressed
		SetMode(MODE_3 | BG2_ENABLE); //Mode 3, Bg2 on
		Print(-1, 0, "ERASE SAVE DATA?", RED, BLACK); //draws text
		FadeIn(2); //Fade In
		while (!(((keyDown(KEY_A))OR(keyDown(KEY_B))))); //waits until a or b is pressed
		if (keyDown(KEY_A)) {
			fillscreen3(0x0000); //makes whole screen black
			Print(-1, 0, "ARE YOU SURE?", RED, BLACK); //draws text
			Print(-1, 9, "ALL DATA WILL BE ERASED.", RED, BLACK); //draws text
			while (((keyDown(KEY_A))OR(keyDown(KEY_B)))); //waits until a or b is not pressed
			while (!(((keyDown(KEY_A))OR(keyDown(KEY_B))))); //waits until a or b is pressed
			if (keyDown(KEY_A)) { 
				while (((keyDown(KEY_A))OR(keyDown(KEY_B)))); //waits until a or b is not pressed
				fillscreen3(0x0000); //makes screen black
				Print(-1, 0, "ERASING.....", RED, BLACK); //draws text
				memcpy(SRAM, 0x06000ED0, 65536); //clears SRAM
				Sleep(240); //Sleeps for 4 seconds
				Print(-1, 0, "THE SYSTEM WILL NOW RESTART.", RED, BLACK); //draw text
				while (!(KEY_ANY_PRESSED)); //waits until any key is pressed
				asm volatile("swi 0x26"::); //resets console
			}
			else {
				fillscreen3(0x0000); //clears screen
				Print(-1, 0, "THE PROCESS WAS ABORTED.", RED, BLACK); //draws text
				Print(-1, 9, "THE SYSTEM WILL NOW RESTART.", RED, BLACK); //draws text
				while (!(KEY_ANY_PRESSED)); //waits until any key is pressed
				asm volatile("swi 0x26"::); //resets console
			}
		}
		else {
			fillscreen3(0x0000);
			Print(-1, 0, "THE PROCESS WAS ABORTED.", RED, BLACK); //draws text
			Print(-1, 9, "THE SYSTEM WILL NOW RESTART.", RED, BLACK); //draws text
			while (!(KEY_ANY_PRESSED)); //waits until any key pressed
			asm volatile("swi 0x26"::); //resets console
		}
	}
	const GBFS_FILE *dat = find_first_gbfs_file(find_first_gbfs_file); //defines GBFS file
    crash = LoadInt(0); //Crash //crash variable
    saveone = LoadInt(16); //Save one
    savetwo = LoadInt(32); //Save two
    savethree = LoadInt(48); //Save Three
    RNGSeed = LoadInt(64); //RNG
    if (crash == 2) { //Crash 2
        SetMode(MODE_3 | BG2_ENABLE); //Mode 3, BG2 On
        memcpy(VRAM, 0x0000, 38400); //Glitchy Screen
        FadeIn(0); //Quick Fade
        Sleep(60); //Waits 1 Second
        SaveInt(0, 0); //Resets crash variable
        Print(8, 8, "HAHAHAHAHAHAHAHAHAHAH!", GREEN, BLACK); //Draws text
        while (!(KEY_ANY_PRESSED)); //Waits until any button is pressed
        vsync //WaitforVblank();
        asm volatile("swi 0x26"::); //resets console
    }
    if ((!((crash == 0)OR(crash == 1)))AND(!((saveone > 0)AND(saveone < levelmax)))AND(!((savetwo > 0)AND(savetwo < levelmax)))AND(!((savethree > 0)AND(savethree < levelmax)))) {
        Initialize(); //Start Fade
	LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "sramc.img.lz", NULL), (u32)videoBuffer); //LZ77 decompresses file "sramc.img.lz" to VRAM
	LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "sramc.pal.lz", NULL), (u32)BGPaletteMem); //LZ77 decompresses file "sramc.pal.lz" to BGPaletteMem
        memcpy(SRAM, 0x06000ED0, 65536); //Erases SRAM
        while (1); //Forever
    }
    if ((crash == 0)AND(saveone == 0)AND(savetwo == 0)AND(savethree == 0)AND(RNGSeed == 0)) {
        empty = 1; //empty
    }
    if (empty == 1) { //SRAM Empty Screen
        Initialize(); //fade out from bios
	LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "srame.img.lz", NULL), (u32)videoBuffer); //LZ77 decompresses file "srame.img.lz" to VRAM
	LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "srame.pal.lz", NULL), (u32)BGPaletteMem); //LZ77 decompresses file "sramc.pal.lz" to BGPaletteMem
        FadeIn(1); //Fade in 
        while (!(KEY_ANY_PRESSED)); //waits until any key is pressed
        empty2 = 1; //empty2
        FadeOut(1); //FadeOut
    }
    // RNGRSeed = (RNGSeed + REG_VCOUNT + x +y - bx + (by\3) + (level\3) + savetwo - saveone + (savethree\GetPixel(14, 4))) ;
    crash = LoadInt(0); //crash variable
    saveone = LoadInt(16); //save data 1
    savetwo = LoadInt(32); //save data 2
    savethree = LoadInt(48); //save data 3
    RNGSeed = LoadInt(64); //RNG Seed
    hello = "//cart//data//allobjs.h: no newline at end of file       C:\\devkitadv\\bin\\objcopy -O binary main.elf main.gba       C:\\devkitadv\\bin\\gcc -marm -mthumb-interwork -o main.elf main.o      C:\\devkitadv\\bin\\gcc -c -O3 -mthumb-interwork main.c Hello. You have just found an eAsTeR eGg.";
    int s;
    initsound8(1, 22050, 2801, (void*)logotheme); //SOund
    initsound8(2, 22050, 2801, (void*)punch);
    initsound8(3, 22050, 2801, (void*)music);
    if (empty2 == 0) {
        WaitForVblank();
        fillscreen3(0xFFFF); //makes screen white
        SetMode(MODE_3 | BG2_ENABLE); //mode 3, bg2 on
        scanlines3(0x0000, 0.5); //scanlines wipe
        fillscreen3(0x0000); //makes screne black
        FadeOut(0); //quick fade out
    }
    SetMode(MODE_4 | BG2_ENABLE); //Mode 4, BG2 On
	LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "discliamer.img.lz", NULL), (u32)videoBuffer); //LZ77 decompresses disclaimer img
	LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "discliamer.pal.lz", NULL), (u32)BGPaletteMem);   //LZ77 decompresses disclaimer pal

    FadeIn(1); //fade in
    time = 0; //timer for credits
    while (!(time == 255 | keyDown(KEY_A))) {
        time++;
        SetBGPalPoint(2, (void*)GetBGPalPoint(2) + 3); //Color Changing text
		Sleep(1); //Waits one frame
    }
    FadeOut(1); //fade out
		LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "thx.img.lz", NULL), (u32)videoBuffer);
		LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "thx.pal.lz", NULL), (u32)BGPaletteMem); 
		 
    FadeIn(1); //fade in
    time = 0; //timer
    while (!(time == 255| keyDown(KEY_A))) {
        time++; //timer
        Sleep(1); //waits on frame
    }
    FadeOut(1); //fade out
	LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "scratch.img.lz", NULL), (u32)videoBuffer);
	LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "scratch.pal.lz", NULL), (u32)BGPaletteMem); 

    FadeIn(1); //fade in
    time = 0; //timer
    while (!(time == 255 | keyDown(KEY_A))) {
        time++; //timer
        Sleep(1); //waits one frame
    }
    FadeOut(1); //fade out
	LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "gbadev.img.lz", NULL), (u32)videoBuffer);
	LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "gbadev.pal.lz", NULL), (u32)BGPaletteMem);  

    FadeIn(1); //fade in
    time = 0;
    while (!(time == 255 | keyDown(KEY_A))) {
        time++;
        Sleep(1);
    }
    FadeOut(1); //fade out
	LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "imadog.img.lz", NULL), (u32)videoBuffer);
	LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "imadog.pal.lz", NULL), (u32)BGPaletteMem); 

    FadeIn(1); //fade in
    time = 0;
    while (!(time == 255 | keyDown(KEY_A))) {
        time++;
		Sleep(1);
    }
    FadeOut(1); //fade out
	LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "slyangel.img.lz", NULL), (u32)videoBuffer);
	LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "slyangel.pal.lz", NULL), (u32)BGPaletteMem); 

    FadeIn(1); //fade in
    time = 0;
    while (!(time == 255 | keyDown(KEY_A))) {
        time++;
		Sleep(1);
    }
    FadeOut(1); //Quick Fade Out
	SetMode(MODE_3 | BG2_ENABLE); //Mode 3, BG2 On
   LZ77UnCompVRAM((u32) gbfs_get_obj(dat, "titlescreen.lz", NULL), (u32)videoBuffer);  //Titlescreen
    FadeIn(1);  //Quick Fade In
	while (!(keyDown(KEY_START)));
    if (crash == 1) { //Crash
        vsync
        SetMode(MODE_4 | BG2_ENABLE);
        for (i = 0; i<30; i++) {
            vsync
			LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "stat1.img.lz", NULL), (u32)videoBuffer);
			LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "stat1.pal.lz", NULL), (u32)BGPaletteMem);  
            Sleep(2);
            vsync
			LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "stat2.img.lz", NULL), (u32)videoBuffer);
			LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "stat2.pal.lz", NULL), (u32)BGPaletteMem);  	

            Sleep(2);
        }
		LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "bsod.img.lz", NULL), (u32)videoBuffer);
		LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "bsod.pal.lz", NULL), (u32)BGPaletteMem);
        SaveInt(0, 2);
        while (1);
    }
    vsync
    SetMode(MODE_4 | BG2_ENABLE);
    setbg2novb((void*)roto0Bitmap, (void*)roto0Palette); //logospin
    sound[1].tic = 1;
    s = 1;
    playSound(1); //play logotheme.wav
	setbg2((void*)roto0Bitmap, (void*)roto0Palette); //logospin

	setbg2((void*)roto1Bitmap, (void*)roto1Palette);

	setbg2((void*)roto2Bitmap, (void*)roto2Palette);

	setbg2((void*)roto3Bitmap, (void*)roto3Palette);

	setbg2((void*)roto4Bitmap, (void*)roto4Palette);

	setbg2((void*)roto5Bitmap, (void*)roto5Palette);

	setbg2((void*)roto6Bitmap, (void*)roto6Palette);

	setbg2((void*)roto7Bitmap, (void*)roto7Palette);

	setbg2((void*)roto8Bitmap, (void*)roto8Palette);

	setbg2((void*)roto9Bitmap, (void*)roto9Palette);

	setbg2((void*)roto10Bitmap, (void*)roto10Palette);

	setbg2((void*)roto11Bitmap, (void*)roto11Palette);

	setbg2((void*)roto12Bitmap, (void*)roto12Palette);

	setbg2((void*)roto13Bitmap, (void*)roto13Palette);

	setbg2((void*)roto14Bitmap, (void*)roto14Palette);

	setbg2((void*)roto15Bitmap, (void*)roto15Palette);

	setbg2((void*)roto16Bitmap, (void*)roto16Palette);

	setbg2((void*)roto17Bitmap, (void*)roto17Palette);

	setbg2((void*)roto18Bitmap, (void*)roto18Palette);

	setbg2((void*)roto19Bitmap, (void*)roto19Palette);

	setbg2((void*)roto20Bitmap, (void*)roto20Palette);

	setbg2((void*)roto21Bitmap, (void*)roto21Palette);

	setbg2((void*)roto22Bitmap, (void*)roto22Palette);

	setbg2((void*)roto23Bitmap, (void*)roto23Palette);

	setbg2((void*)roto24Bitmap, (void*)roto24Palette);

	setbg2((void*)roto25Bitmap, (void*)roto25Palette);

	setbg2((void*)roto26Bitmap, (void*)roto26Palette);

	setbg2((void*)roto27Bitmap, (void*)roto27Palette);

	setbg2((void*)roto28Bitmap, (void*)roto28Palette);

	setbg2((void*)roto29Bitmap, (void*)roto29Palette);

	setbg2((void*)roto30Bitmap, (void*)roto30Palette);

	setbg2((void*)roto31Bitmap, (void*)roto31Palette);

	setbg2((void*)roto32Bitmap, (void*)roto32Palette);

	setbg2((void*)roto33Bitmap, (void*)roto33Palette);

	setbg2((void*)roto34Bitmap, (void*)roto34Palette);

	setbg2((void*)roto35Bitmap, (void*)roto35Palette);

	setbg2((void*)roto36Bitmap, (void*)roto36Palette);

	setbg2((void*)roto37Bitmap, (void*)roto37Palette);

	setbg2((void*)roto38Bitmap, (void*)roto38Palette);

	setbg2((void*)roto39Bitmap, (void*)roto39Palette);

	setbg2((void*)roto40Bitmap, (void*)roto40Palette);

	setbg2((void*)roto41Bitmap, (void*)roto41Palette);

	setbg2((void*)roto42Bitmap, (void*)roto42Palette);

	setbg2((void*)roto43Bitmap, (void*)roto43Palette);

	setbg2((void*)roto44Bitmap, (void*)roto44Palette);

	setbg2((void*)roto45Bitmap, (void*)roto45Palette);

	setbg2((void*)roto46Bitmap, (void*)roto46Palette);

	setbg2((void*)roto47Bitmap, (void*)roto47Palette);

	setbg2((void*)roto48Bitmap, (void*)roto48Palette);

	setbg2((void*)roto49Bitmap, (void*)roto49Palette);

	setbg2((void*)roto0Bitmap, (void*)roto0Palette);

	setbg2((void*)roto1Bitmap, (void*)roto1Palette);

	setbg2((void*)roto2Bitmap, (void*)roto2Palette);

	setbg2((void*)roto3Bitmap, (void*)roto3Palette);

	setbg2((void*)roto4Bitmap, (void*)roto4Palette);

	setbg2((void*)roto5Bitmap, (void*)roto5Palette);

	setbg2((void*)roto6Bitmap, (void*)roto6Palette);

	setbg2((void*)roto7Bitmap, (void*)roto7Palette);

	setbg2((void*)roto8Bitmap, (void*)roto8Palette);

	setbg2((void*)roto9Bitmap, (void*)roto9Palette);

	setbg2((void*)roto10Bitmap, (void*)roto10Palette);

	setbg2((void*)roto11Bitmap, (void*)roto11Palette);

	setbg2((void*)roto12Bitmap, (void*)roto12Palette);

	setbg2((void*)roto13Bitmap, (void*)roto13Palette);

	setbg2((void*)roto14Bitmap, (void*)roto14Palette);

	setbg2((void*)roto15Bitmap, (void*)roto15Palette);

	setbg2((void*)roto16Bitmap, (void*)roto16Palette);

	setbg2((void*)roto17Bitmap, (void*)roto17Palette);

	setbg2((void*)roto18Bitmap, (void*)roto18Palette);

	setbg2((void*)roto19Bitmap, (void*)roto19Palette);

	setbg2((void*)roto20Bitmap, (void*)roto20Palette);

	setbg2((void*)roto21Bitmap, (void*)roto21Palette);

	setbg2((void*)roto22Bitmap, (void*)roto22Palette);

	setbg2((void*)roto23Bitmap, (void*)roto23Palette);

	setbg2((void*)roto24Bitmap, (void*)roto24Palette);

	setbg2((void*)roto25Bitmap, (void*)roto25Palette);

	setbg2((void*)roto26Bitmap, (void*)roto26Palette);

	setbg2((void*)roto27Bitmap, (void*)roto27Palette);

	setbg2((void*)roto28Bitmap, (void*)roto28Palette);

	setbg2((void*)roto29Bitmap, (void*)roto29Palette);

	setbg2((void*)roto30Bitmap, (void*)roto30Palette);

	setbg2((void*)roto31Bitmap, (void*)roto31Palette);

	setbg2((void*)roto32Bitmap, (void*)roto32Palette);

	setbg2((void*)roto33Bitmap, (void*)roto33Palette);

	setbg2((void*)roto34Bitmap, (void*)roto34Palette);

	setbg2((void*)roto35Bitmap, (void*)roto35Palette);

	setbg2((void*)roto36Bitmap, (void*)roto36Palette);

	setbg2((void*)roto37Bitmap, (void*)roto37Palette);

	setbg2((void*)roto38Bitmap, (void*)roto38Palette);

	setbg2((void*)roto39Bitmap, (void*)roto39Palette);

	setbg2((void*)roto40Bitmap, (void*)roto40Palette);

	setbg2((void*)roto41Bitmap, (void*)roto41Palette);

	setbg2((void*)roto42Bitmap, (void*)roto42Palette);

	setbg2((void*)roto43Bitmap, (void*)roto43Palette);

	setbg2((void*)roto44Bitmap, (void*)roto44Palette);

	setbg2((void*)roto45Bitmap, (void*)roto45Palette);

	setbg2((void*)roto46Bitmap, (void*)roto46Palette);

	setbg2((void*)roto47Bitmap, (void*)roto47Palette);

	setbg2((void*)roto48Bitmap, (void*)roto48Palette);

	setbg2((void*)roto49Bitmap, (void*)roto49Palette);

	setbg2((void*)roto0Bitmap, (void*)roto0Palette);

	setbg2((void*)roto1Bitmap, (void*)roto1Palette);

	setbg2((void*)roto2Bitmap, (void*)roto2Palette);

	setbg2((void*)roto3Bitmap, (void*)roto3Palette);

	setbg2((void*)roto4Bitmap, (void*)roto4Palette);

	setbg2((void*)roto5Bitmap, (void*)roto5Palette);

	setbg2((void*)roto6Bitmap, (void*)roto6Palette);

	setbg2((void*)roto7Bitmap, (void*)roto7Palette);

	setbg2((void*)roto8Bitmap, (void*)roto8Palette);

	setbg2((void*)roto9Bitmap, (void*)roto9Palette);

	setbg2((void*)roto10Bitmap, (void*)roto10Palette);

	setbg2((void*)roto11Bitmap, (void*)roto11Palette);

	setbg2((void*)roto12Bitmap, (void*)roto12Palette);

	setbg2((void*)roto13Bitmap, (void*)roto13Palette);

	setbg2((void*)roto14Bitmap, (void*)roto14Palette);

	setbg2((void*)roto15Bitmap, (void*)roto15Palette);

	setbg2((void*)roto16Bitmap, (void*)roto16Palette);

	setbg2((void*)roto17Bitmap, (void*)roto17Palette);

	setbg2((void*)roto18Bitmap, (void*)roto18Palette);

	setbg2((void*)roto19Bitmap, (void*)roto19Palette);

	setbg2((void*)roto20Bitmap, (void*)roto20Palette);

	setbg2((void*)roto21Bitmap, (void*)roto21Palette);

	setbg2((void*)roto22Bitmap, (void*)roto22Palette);

	setbg2((void*)roto23Bitmap, (void*)roto23Palette);

	setbg2((void*)roto24Bitmap, (void*)roto24Palette);

	setbg2((void*)roto25Bitmap, (void*)roto25Palette);

	setbg2((void*)roto26Bitmap, (void*)roto26Palette);

	setbg2((void*)roto27Bitmap, (void*)roto27Palette);

	setbg2((void*)roto28Bitmap, (void*)roto28Palette);

	setbg2((void*)roto29Bitmap, (void*)roto29Palette);

	setbg2((void*)roto30Bitmap, (void*)roto30Palette);

	setbg2((void*)roto31Bitmap, (void*)roto31Palette);

	setbg2((void*)roto32Bitmap, (void*)roto32Palette);

	setbg2((void*)roto33Bitmap, (void*)roto33Palette);

	setbg2((void*)roto34Bitmap, (void*)roto34Palette);

	setbg2((void*)roto35Bitmap, (void*)roto35Palette);

	setbg2((void*)roto36Bitmap, (void*)roto36Palette);

	setbg2((void*)roto37Bitmap, (void*)roto37Palette);

	setbg2((void*)roto38Bitmap, (void*)roto38Palette);

	setbg2((void*)roto39Bitmap, (void*)roto39Palette);

	setbg2((void*)roto40Bitmap, (void*)roto40Palette);

	setbg2((void*)roto41Bitmap, (void*)roto41Palette);

	setbg2((void*)roto42Bitmap, (void*)roto42Palette);

	setbg2((void*)roto43Bitmap, (void*)roto43Palette);

	setbg2((void*)roto44Bitmap, (void*)roto44Palette);

	setbg2((void*)roto45Bitmap, (void*)roto45Palette);

	setbg2((void*)roto46Bitmap, (void*)roto46Palette);

	setbg2((void*)roto47Bitmap, (void*)roto47Palette);

	setbg2((void*)roto48Bitmap, (void*)roto48Palette);

	setbg2((void*)roto49Bitmap, (void*)roto49Palette);

	setbg2((void*)roto0Bitmap, (void*)roto0Palette);

	setbg2((void*)roto1Bitmap, (void*)roto1Palette);

	setbg2((void*)roto2Bitmap, (void*)roto2Palette);

	setbg2((void*)roto3Bitmap, (void*)roto3Palette);

	setbg2((void*)roto4Bitmap, (void*)roto4Palette);

	setbg2((void*)roto5Bitmap, (void*)roto5Palette);

	setbg2((void*)roto6Bitmap, (void*)roto6Palette);

	setbg2((void*)roto7Bitmap, (void*)roto7Palette);

	setbg2((void*)roto8Bitmap, (void*)roto8Palette);

	setbg2((void*)roto9Bitmap, (void*)roto9Palette);

	setbg2((void*)roto10Bitmap, (void*)roto10Palette);

	setbg2((void*)roto11Bitmap, (void*)roto11Palette);

	setbg2((void*)roto12Bitmap, (void*)roto12Palette);

	setbg2((void*)roto13Bitmap, (void*)roto13Palette);

	setbg2((void*)roto14Bitmap, (void*)roto14Palette);

	setbg2((void*)roto15Bitmap, (void*)roto15Palette);

	setbg2((void*)roto16Bitmap, (void*)roto16Palette);

	setbg2((void*)roto17Bitmap, (void*)roto17Palette);

	setbg2((void*)roto18Bitmap, (void*)roto18Palette);

	setbg2((void*)roto19Bitmap, (void*)roto19Palette);

	setbg2((void*)roto20Bitmap, (void*)roto20Palette);

	setbg2((void*)roto21Bitmap, (void*)roto21Palette);

	setbg2((void*)roto22Bitmap, (void*)roto22Palette);

	setbg2((void*)roto23Bitmap, (void*)roto23Palette);

	setbg2((void*)roto24Bitmap, (void*)roto24Palette);

	setbg2((void*)roto25Bitmap, (void*)roto25Palette);

	setbg2((void*)roto26Bitmap, (void*)roto26Palette);

	setbg2((void*)roto27Bitmap, (void*)roto27Palette);

	setbg2((void*)roto28Bitmap, (void*)roto28Palette);

	setbg2((void*)roto29Bitmap, (void*)roto29Palette);

	setbg2((void*)roto30Bitmap, (void*)roto30Palette);

	setbg2((void*)roto31Bitmap, (void*)roto31Palette);

	setbg2((void*)roto32Bitmap, (void*)roto32Palette);

	setbg2((void*)roto33Bitmap, (void*)roto33Palette);

	setbg2((void*)roto34Bitmap, (void*)roto34Palette);

	setbg2((void*)roto35Bitmap, (void*)roto35Palette);

	setbg2((void*)roto36Bitmap, (void*)roto36Palette);

	setbg2((void*)roto37Bitmap, (void*)roto37Palette);

	setbg2((void*)roto38Bitmap, (void*)roto38Palette);

	setbg2((void*)roto39Bitmap, (void*)roto39Palette);

	setbg2((void*)roto40Bitmap, (void*)roto40Palette);

	setbg2((void*)roto41Bitmap, (void*)roto41Palette);

	setbg2((void*)roto42Bitmap, (void*)roto42Palette);

	setbg2((void*)roto43Bitmap, (void*)roto43Palette);

	setbg2((void*)roto44Bitmap, (void*)roto44Palette);

	setbg2((void*)roto45Bitmap, (void*)roto45Palette);

	setbg2((void*)roto46Bitmap, (void*)roto46Palette);

	setbg2((void*)roto47Bitmap, (void*)roto47Palette);

	setbg2((void*)roto48Bitmap, (void*)roto48Palette);

	setbg2((void*)roto49Bitmap, (void*)roto49Palette);

	setbg2((void*)roto0Bitmap, (void*)roto0Palette);

	setbg2((void*)roto1Bitmap, (void*)roto1Palette);

	setbg2((void*)roto2Bitmap, (void*)roto2Palette);

	setbg2((void*)roto3Bitmap, (void*)roto3Palette);

	setbg2((void*)roto4Bitmap, (void*)roto4Palette);

	setbg2((void*)roto5Bitmap, (void*)roto5Palette);

	setbg2((void*)roto6Bitmap, (void*)roto6Palette);

	setbg2((void*)roto7Bitmap, (void*)roto7Palette);

	setbg2((void*)roto8Bitmap, (void*)roto8Palette);

	setbg2((void*)roto9Bitmap, (void*)roto9Palette);

	setbg2((void*)roto10Bitmap, (void*)roto10Palette);

	setbg2((void*)roto11Bitmap, (void*)roto11Palette);

	setbg2((void*)roto12Bitmap, (void*)roto12Palette);

	setbg2((void*)roto13Bitmap, (void*)roto13Palette);

	setbg2((void*)roto14Bitmap, (void*)roto14Palette);

	setbg2((void*)roto15Bitmap, (void*)roto15Palette);

	setbg2((void*)roto16Bitmap, (void*)roto16Palette);

	setbg2((void*)roto17Bitmap, (void*)roto17Palette);

	setbg2((void*)roto18Bitmap, (void*)roto18Palette);

	setbg2((void*)roto19Bitmap, (void*)roto19Palette);

	setbg2((void*)roto20Bitmap, (void*)roto20Palette);

	setbg2((void*)roto21Bitmap, (void*)roto21Palette);

	setbg2((void*)roto22Bitmap, (void*)roto22Palette);

	setbg2((void*)roto23Bitmap, (void*)roto23Palette);

	setbg2((void*)roto24Bitmap, (void*)roto24Palette);

	setbg2((void*)roto25Bitmap, (void*)roto25Palette);

	setbg2((void*)roto26Bitmap, (void*)roto26Palette);

	setbg2((void*)roto27Bitmap, (void*)roto27Palette);

	setbg2((void*)roto28Bitmap, (void*)roto28Palette);

	setbg2((void*)roto29Bitmap, (void*)roto29Palette);

	setbg2((void*)roto30Bitmap, (void*)roto30Palette);

	setbg2((void*)roto31Bitmap, (void*)roto31Palette);

	setbg2((void*)roto32Bitmap, (void*)roto32Palette);

	setbg2((void*)roto33Bitmap, (void*)roto33Palette);

	setbg2((void*)roto34Bitmap, (void*)roto34Palette);

	setbg2((void*)roto35Bitmap, (void*)roto35Palette);

	setbg2((void*)roto36Bitmap, (void*)roto36Palette);

	setbg2((void*)roto37Bitmap, (void*)roto37Palette);

	setbg2((void*)roto38Bitmap, (void*)roto38Palette);

	setbg2((void*)roto39Bitmap, (void*)roto39Palette);

	setbg2((void*)roto40Bitmap, (void*)roto40Palette);

	setbg2((void*)roto41Bitmap, (void*)roto41Palette);

	setbg2((void*)roto42Bitmap, (void*)roto42Palette);

	setbg2((void*)roto43Bitmap, (void*)roto43Palette);

	setbg2((void*)roto44Bitmap, (void*)roto44Palette);

	setbg2((void*)roto45Bitmap, (void*)roto45Palette);

	setbg2((void*)roto46Bitmap, (void*)roto46Palette);

	setbg2((void*)roto47Bitmap, (void*)roto47Palette);

	setbg2((void*)roto48Bitmap, (void*)roto48Palette);

	setbg2((void*)roto49Bitmap, (void*)roto49Palette);

	setbg2((void*)roto0Bitmap, (void*)roto0Palette);

	setbg2((void*)roto1Bitmap, (void*)roto1Palette);

	setbg2((void*)roto2Bitmap, (void*)roto2Palette);

	setbg2((void*)roto3Bitmap, (void*)roto3Palette);

	setbg2((void*)roto4Bitmap, (void*)roto4Palette);

	setbg2((void*)roto5Bitmap, (void*)roto5Palette);

	setbg2((void*)roto6Bitmap, (void*)roto6Palette);

	setbg2((void*)roto7Bitmap, (void*)roto7Palette);

	setbg2((void*)roto8Bitmap, (void*)roto8Palette);

	setbg2((void*)roto9Bitmap, (void*)roto9Palette);

	setbg2((void*)roto10Bitmap, (void*)roto10Palette);

	setbg2((void*)roto11Bitmap, (void*)roto11Palette);

	setbg2((void*)roto12Bitmap, (void*)roto12Palette);

	setbg2((void*)roto13Bitmap, (void*)roto13Palette);

	setbg2((void*)roto14Bitmap, (void*)roto14Palette);

	setbg2((void*)roto15Bitmap, (void*)roto15Palette);

	setbg2((void*)roto16Bitmap, (void*)roto16Palette);

	setbg2((void*)roto17Bitmap, (void*)roto17Palette);

	setbg2((void*)roto18Bitmap, (void*)roto18Palette);

	setbg2((void*)roto19Bitmap, (void*)roto19Palette);

	setbg2((void*)roto20Bitmap, (void*)roto20Palette);

	setbg2((void*)roto21Bitmap, (void*)roto21Palette);

	setbg2((void*)roto22Bitmap, (void*)roto22Palette);

	setbg2((void*)roto23Bitmap, (void*)roto23Palette);

	setbg2((void*)roto24Bitmap, (void*)roto24Palette);

	setbg2((void*)roto25Bitmap, (void*)roto25Palette);

	setbg2((void*)roto26Bitmap, (void*)roto26Palette);

	setbg2((void*)roto27Bitmap, (void*)roto27Palette);

	setbg2((void*)roto28Bitmap, (void*)roto28Palette);

	setbg2((void*)roto29Bitmap, (void*)roto29Palette);

	setbg2((void*)roto30Bitmap, (void*)roto30Palette);

	setbg2((void*)roto31Bitmap, (void*)roto31Palette);

	setbg2((void*)roto32Bitmap, (void*)roto32Palette);

	setbg2((void*)roto33Bitmap, (void*)roto33Palette);

	setbg2((void*)roto34Bitmap, (void*)roto34Palette);

	setbg2((void*)roto35Bitmap, (void*)roto35Palette);

	setbg2((void*)roto36Bitmap, (void*)roto36Palette);

	setbg2((void*)roto37Bitmap, (void*)roto37Palette);

	setbg2((void*)roto38Bitmap, (void*)roto38Palette);

	setbg2((void*)roto39Bitmap, (void*)roto39Palette);

	setbg2((void*)roto40Bitmap, (void*)roto40Palette);

	setbg2((void*)roto41Bitmap, (void*)roto41Palette);

	setbg2((void*)roto42Bitmap, (void*)roto42Palette);

	setbg2((void*)roto43Bitmap, (void*)roto43Palette);

	setbg2((void*)roto44Bitmap, (void*)roto44Palette);

	setbg2((void*)roto45Bitmap, (void*)roto45Palette);

	setbg2((void*)roto46Bitmap, (void*)roto46Palette);

	setbg2((void*)roto47Bitmap, (void*)roto47Palette);

	setbg2((void*)roto48Bitmap, (void*)roto48Palette);

	setbg2((void*)roto49Bitmap, (void*)roto49Palette);

	setbg2((void*)roto0Bitmap, (void*)roto0Palette);

	setbg2((void*)roto1Bitmap, (void*)roto1Palette);

	setbg2((void*)roto2Bitmap, (void*)roto2Palette);

	setbg2((void*)roto3Bitmap, (void*)roto3Palette);

	setbg2((void*)roto4Bitmap, (void*)roto4Palette);

	setbg2((void*)roto5Bitmap, (void*)roto5Palette);

	setbg2((void*)roto6Bitmap, (void*)roto6Palette);

	setbg2((void*)roto7Bitmap, (void*)roto7Palette);

	setbg2((void*)roto8Bitmap, (void*)roto8Palette);

	setbg2((void*)roto9Bitmap, (void*)roto9Palette);

	setbg2((void*)roto10Bitmap, (void*)roto10Palette);

	setbg2((void*)roto11Bitmap, (void*)roto11Palette);

	setbg2((void*)roto12Bitmap, (void*)roto12Palette);

	setbg2((void*)roto13Bitmap, (void*)roto13Palette);

	setbg2((void*)roto14Bitmap, (void*)roto14Palette);

	setbg2((void*)roto15Bitmap, (void*)roto15Palette);

	setbg2((void*)roto16Bitmap, (void*)roto16Palette);

	setbg2((void*)roto17Bitmap, (void*)roto17Palette);

	setbg2((void*)roto18Bitmap, (void*)roto18Palette);

	setbg2((void*)roto19Bitmap, (void*)roto19Palette);

	setbg2((void*)roto20Bitmap, (void*)roto20Palette);

	setbg2((void*)roto21Bitmap, (void*)roto21Palette);

	setbg2((void*)roto22Bitmap, (void*)roto22Palette);

	setbg2((void*)roto23Bitmap, (void*)roto23Palette);

	setbg2((void*)roto24Bitmap, (void*)roto24Palette);

	setbg2((void*)roto25Bitmap, (void*)roto25Palette);

	setbg2((void*)roto26Bitmap, (void*)roto26Palette);

	setbg2((void*)roto27Bitmap, (void*)roto27Palette);

	setbg2((void*)roto28Bitmap, (void*)roto28Palette);

	setbg2((void*)roto29Bitmap, (void*)roto29Palette);

	setbg2((void*)roto30Bitmap, (void*)roto30Palette);

	setbg2((void*)roto31Bitmap, (void*)roto31Palette);

	setbg2((void*)roto32Bitmap, (void*)roto32Palette);

	setbg2((void*)roto33Bitmap, (void*)roto33Palette);

	setbg2((void*)roto34Bitmap, (void*)roto34Palette);

	setbg2((void*)roto35Bitmap, (void*)roto35Palette);

	setbg2((void*)roto36Bitmap, (void*)roto36Palette);

	setbg2((void*)roto37Bitmap, (void*)roto37Palette);

	setbg2((void*)roto38Bitmap, (void*)roto38Palette);

	setbg2((void*)roto39Bitmap, (void*)roto39Palette);

	setbg2((void*)roto40Bitmap, (void*)roto40Palette);

	setbg2((void*)roto41Bitmap, (void*)roto41Palette);

	setbg2((void*)roto42Bitmap, (void*)roto42Palette);

	setbg2((void*)roto43Bitmap, (void*)roto43Palette);

	setbg2((void*)roto44Bitmap, (void*)roto44Palette);

	setbg2((void*)roto45Bitmap, (void*)roto45Palette);

	setbg2((void*)roto46Bitmap, (void*)roto46Palette);

	setbg2((void*)roto47Bitmap, (void*)roto47Palette);

	setbg2((void*)roto48Bitmap, (void*)roto48Palette);

	playSound(2);
	setbg2novb((void*)roto49Bitmap, (void*)roto49Palette);
	vsync
	setbg2novb((void*)bgtwoBitmap, (void*)bgtwoPalette);
    Sleep(15);
    while (1) { //main loop for menu
        REG_SOUNDCNT_H = 0;                                                      //REG_SOUNDCNT_H = 0000 1011 0000 0100, volume = 100, sound goes to the left, sound goes to the right, timer 0 is used, FIFO buffer reset
        REG_SOUNDCNT_X = 0;                                                       //REG_SOUNDCNT_X = 0000 0000 1000 0000, enable the sound system, DMA 1
        REG_DM1SAD = 0;                               //REG_DM1SAD = NAME, address of DMA source is the digitized music sample
        REG_DM1DAD = 0;                                                   //REG_DM1DAD = REG_SGFIFOA, address of DMA destination is FIFO buffer for direct sound A
        REG_DM1CNT_H = 0;                                                    //REG_DM1CNT_H = 1011 0110 0100 0000, DMA destination is fixed, repeat transfer of 4 bytes when FIFO , buffer is empty, enable DMA 1 (number of DMA transfers is ignored), INTERRUPT
        REG_TM0D = 0;                         //REG_TM0D = 65536-(16777216/frequency);, play sample every 16777216/frequency CPU cycles
        REG_TM0CNT = 0;
        if (keyDown(KEY_SELECT)) {
            FadeOut(1);
			LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "controlspage1.img.lz", NULL), (u32)videoBuffer);
			LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "controlspage1.pal.lz", NULL), (u32)BGPaletteMem);  	
			FadeIn(1);
            while (!(keyDown(KEY_A))) {
                wait = 0;
            }
            while (keyDown(KEY_A)) {
                wait = 0;
            }
            FadeOut(1);
			LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "controlspage2.img.lz", NULL), (u32)videoBuffer);
			LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "controlspage2.pal.lz", NULL), (u32)BGPaletteMem);
            FadeIn(1);
            while (!(keyDown(KEY_A))) {
                wait = 0;
            }
            while (keyDown(KEY_A)) {
                wait = 0;
            }
            FadeOut(1);
			setbg2novb((void*)bgtwoBitmap, (void*)bgtwoPalette);
            FadeIn(1);
        }
        if (keyDown(KEY_START)) {
		FadeOutWhite(8);
		loadSpriteGraphics((void*)sprs, 11904); //loads the bitmap data for all of the objects, so that I don't have to go throught the hassle of making a palette for each individual object.
		loadSpritePal((void*)sprsPalette); //Copies the specified palette data into memory address 0x5000200, which is the location of the palette of the objects in OAM.
		level = 1;
		levels();
		SetMode(MODE_3 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D);
            fillpal("bg", 0x0000);
            initSprite(1, SIZE_32, 0); //Slot 1: Block (32x32)
            initSprite(2, SIZE_8, 48); //Slot 2: Goal (8x8)
            sprites[3].attribute0 = COLOR_256 | WIDE | 240; //Slot 3: Fireball (32x16)
            sprites[3].attribute1 = SIZE_32 | 160;
            sprites[3].attribute2 = 512 + 32;
            sprites[4].attribute0 = COLOR_256 | WIDE | 240; //Slot 4: Version Counter (64x32)
            sprites[4].attribute1 = SIZE_64 |160;
            sprites[4].attribute2 = 512 + 280;
            sprites[5].attribute0 = COLOR_256 | SQUARE | 160; //Slot 5: Level Object#1 (32 -- 64)
            sprites[5].attribute1 = SIZE_8 | 240;
            sprites[5].attribute2 = 512 + 56;
            sprites[6].attribute0 = COLOR_256 | SQUARE | 240; //Slot 6: Level Object#2 (32 -- 64)
            sprites[6].attribute1 = SIZE_8 | 160;
            sprites[6].attribute2 = 512 + 56;
			FadeInWhite(8);
            varreset();
            MoveSprite(&sprites[4], 0, 152);
            MoveSprite(&sprites[2], 223, 128);
            playSound(3);
			while (1) {
				for (i = 0; i != 11000; i++) {
					temp = 0;
				}
				WaitForVblank();
						u16 loop;
						u16* temp;
						temp = (u16*)sprites;
						for (loop = 0; loop < 6 * 4; loop++)
						{
							OAM[loop] = temp[loop];
						}
                    physics();
                    if ((BlockTouchingColor(0x001F) == 1)OR(bx < 0)OR(bx > 216)OR(by < 0)OR(by > 136)) {
                        die();
                    }else if (BlockTouchingColor((void*)0x7ED3) == 1) {
						if (gravity == 1) {
							y = 6;
						}
						else {
							y = -6;
						}
					}
                    if (level == 49) {
                        sprites[5].attribute0 = COLOR_256 | SQUARE | 240;
                        sprites[5].attribute1 = SIZE_32 | 160;
                        sprites[5].attribute2 = 512 + 248; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
						sprites[6].attribute0 = COLOR_256 | SQUARE | 240;
						sprites[6].attribute1 = SIZE_32 | 160;
						sprites[6].attribute2 =760; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd

                        if (td == 1) {
                            MoveSprite(&sprites[5], 128, ty);
                            if (NOT(ty < 0)) {
                                ty -= 4;
                            }
                            else {
                                td = 0;
                            }
                        }
                        else {

                            MoveSprite(&sprites[5], 128, ty);
                            if (NOT(ty > 113)) {
                                ty += 4;
                            }
                            else {
                                td = 1;
                            }
                        }
                        if (td2 == 1) {
                            MoveSprite(&sprites[6], 64, ty2);
                            if (NOT(ty2 < 0)) {
                                ty2 -= 3;
                            }
                            else {
                                td2 = 0;
                            }
                        }
                        else {
                            MoveSprite(&sprites[6], 64, ty2);
                            if (NOT(ty2 > 113)) {
                                ty2 += 3;
                            }
                            else {
                                td2 = 1;
                            }
                        }
                        if (((bx > 104)AND(bx < 160)AND(by < ty + 32))OR((bx > 40)AND(bx < 96)AND(by < ty2 + 32))) {
                            bx = 8;
                            by = 108;
                            y = 0;
                            x = 0;
                        }
                    }
                    else if ((level == 50)OR(level == 51)) {
                        sprites[5].attribute0 = COLOR_256 | TALL | 240;
                        sprites[5].attribute1 = SIZE_64 | 160;
                        sprites[5].attribute2 = 512 + 184; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
                        MoveSprite(&sprites[6], 240, 160);
                        if (sd == 1) {
                            MoveSprite(&sprites[5], 128, sy);
                            if (NOT(sy < 0)) {
                                sy -= 4;
                            }
                            else {
                                sd = 0;
                            }
                        }
                        else {
                            MoveSprite(&sprites[5], 128, sy);
                            if (NOT(sy > 81)) {
                                sy += 4;
                            }
                            else {
                                sd = 1;
                            }
                        }
                        if ((bx > 104)AND(bx < 160)AND(by < sy + 64)) {
                            die();
                        }
                    }
                    else if (level == 52) {
                        sprites[5].attribute0 = COLOR_256 | SQUARE | 240;
                        sprites[5].attribute1 = SIZE_8 | 160;

                        sprites[5].attribute2 = 512 + 56;
                    }
                    else if (level == 58) {
                        if (gemv == 0) {
                            sprites[5].attribute0 = COLOR_256 | WIDE | 240;
                            sprites[5].attribute1 = SIZE_64 | 160;
                            sprites[5].attribute2 = 512 + 296; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
                            MoveSprite(&sprites[5], 98, 66);
                            if (g == 1) {
                                sprites[5].attribute0 = COLOR_256 | SQUARE | 240;
                                sprites[5].attribute1 = SIZE_8 | 160;
                                sprites[5].attribute2 = 512 + 56;
                                gemv = 1;
                            }
                        }
                        if ((bx > 74)AND(by < 94)AND(bx < 141)AND(by > 42)) {
                            sprites[5].attribute0 = COLOR_256 | SQUARE | 240;
                            sprites[5].attribute1 = SIZE_8 | 160;

                            sprites[5].attribute2 = 512 + 56;
                            g = 1;
                            gemv = 1;
                        }
                    }
                    else if (level == 61) {
                        if ((es == 0)AND(!(ed==3))) {
                            sprites[5].attribute0 = COLOR_256 | SQUARE | 64;
                            sprites[5].attribute1 = SIZE_64 | 81;
                            sprites[5].attribute2 = 512 + 360; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
                            es = 1;
							ex = 64;
                            MoveSprite(&sprites[5], 64, 81);
                        }
                        if (ed == 1) {
                            sprites[5].attribute1 = SIZE_64 | 81;
                            MoveSprite(&sprites[5], ex, 81);
                            if (NOT(ex < 64)) {
                                ex -= 3;
                            }
                            else {
                                ed = 0;
                            }
                        }
                      if (ed == 0) {
                            sprites[5].attribute1 = SIZE_64 | HORIZONTAL_FLIP | ex;
                            MoveSprite(&sprites[5], ex, 81);
                            if (NOT(ex > 160)) {
                                ex += 3;
                            }
                            else {
                                ed = 1;
                            }
                        }
                        if ((bx > ex - 24)AND(!(ed==3))) {
							die();
                        }
                        if ((fx > ex - 32)AND(NOT(ea == 1))) {
                            fb = 0;
							ed = 3;
                            fx = 0;
                            MoveSprite(&sprites[3], 240, 160);
                            MoveSprite(&sprites[5], 240, 160);
                        }
                    }
                    else if (level == 62) {
                        sprites[5].attribute0 = COLOR_256 | SQUARE | 240;
                        sprites[5].attribute1 = SIZE_8 | 160;

                        sprites[5].attribute2 = 512 + 56;
                    }
                    else if (((level >= 43)AND(level <= 47))OR(level == 137)OR(level==127)) {
                        if ((keyDown(KEY_SELECT))AND(sellock == 0)) {
                            gravity++;
                            if (gravity == 2) {
                                gravity = 0;
                            }
                            sellock = 1;
                        }
                        if (NOT(keyDown(KEY_SELECT))) {
                            sellock = 0;
                        }
                    }
                    else if ((level == 55)OR(level == 56)) {
                        initSprite(5, SIZE_32, 56);
                        MoveSprite(&sprites[5], 104, 64);
                        if ((bx > 80)AND(by > 40)AND(bx < 136)AND(by < 96)) {
                            if (keyDown(KEY_A)) {
                                y = -4.05;
                            }
                        }
                    }
                    else if (level == 57) {
                        sprites[5].attribute0 = COLOR_256 | SQUARE | 240;
                        sprites[5].attribute1 = SIZE_8 | 160;
                        sprites[5].attribute2 = 512 + 56;
                    }
                    else if (((level > 31)AND(level < 40))OR(level == 42)OR(level == 54)) {
                        if (BlockTouchingColor(0x7E8C) == 1) {
                            if (level == 32) {
                                bx = 159;
                                by = 3;
                            }
                            else if (level == 33) {
                                bx = 136;
                                by = 3;
                            }
                            else if (level == 34) {
                                bx = 195;
                                by = 4;
                            }
                            else if (level == 35) {
                                bx = 139;
                                by = 97;
                            }
                            else if (level == 36) {
                                bx = 6;
                                by = 31;
                            }
                            else if (level == 37) {
                                bx = 173;
                                by = 5;
                            }
                            else if (level == 38) {
                                bx = 16;
                                by = 3;
                            }
                            else if (level == 39) {
                                bx = 124;
                                by = 5;
                            }
                            else if (level == 42) {
                                bx = 196;
                                by = 101;
                            }
                            else if (level == 54) {
                                bx = 119;
                                by = 111;
                                y = -3.5;
                            }
                            else {
                                bx = 0;
                                by = 0;
                            }
                        }
                    }
                    else if (level == 85) {
						if ((bx > 90 - 24)AND(by > 81 - 24)AND(gcd==0))
						{
							die();
						}
						int gcbt,gcbx,gcby,gctx;
						if (gci == 0)
						{
							initSprite(&sprites[5], SIZE_8, 74);
						}
                        if ((fx > 45)AND(NOT(gcd == 1))) {
                            sprites[3].attribute0 = COLOR_256 | WIDE  | 160;
                            sprites[3].attribute1 = SIZE_32 | 240;
                            sprites[3].attribute2 = 512 + 32; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd

							LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "l85b.lz", NULL), (u32)videoBuffer);
                            MoveSprite(&sprites[3], 240, 160);
                            fb = 0;
                            gcd = 1;
                        }
						if ((gcbt == 0)AND(gcd==0))
						{
							if (gcbx == 0)
							{
								MoveSprite(&sprites[5], 80, by);
								gcbx = 1;
								gctx = 80;
								gcby = by;
							}
							if (gcbx == 1)
							{
								MoveSprite(&sprites[5], gctx, gcby);
								if(gctx < 0)
								{
									gctx -= 4;
									if ((bx - 24 > gctx)AND(bx > gctx + 8)AND(by + 24 > gcby)AND(by < gcby + 8))
									{
										die();
										gcbx = 0;
										MoveSprite(&sprites[5], 240, 160);
									}

								}
								else {
									gctx = 0;
									MoveSprite(&sprites[5], 240,160);
								}
							}
						}
                    }
                    else if (level == 84) {
                        if (pi == 0) {
                            initSprite(5, SIZE_16, 120);
                            pi = 1;
                        }
                        px += psx;
                        py += psy;
                        if (py >= 128) {
                            psy = -4;
                        }
                        if (py <= 0) {
                            psy = 4;
                        }

                        if (px >= 224) {
                            psx = -4;
                        }
                        if (px <= 0) {
                            psx = 4;
                        }
                        MoveSprite(&sprites[5], px, py);
						if ((bx > px - 24)AND(bx < px + 16)AND(by > py - 24)AND(by < py + 16))
						{
							die();
						}
                    }
					else if (level == 85)
					{
						initSprite(5, SIZE_8, 0);
					}
                    else if ((level > 9)AND(level < 13)) {
                        if (BlockTouchingColor(0x6300) == 1) {
                            die();
                        }
                    }
                    if ((keyDown(KEY_B))AND(g == 1)) {
                        fb = 1;
                        fy = by + 4;
                        fx = bx;
                        block = 1;
                    }
                    if ((fb == 1)AND(NOT(fx > 240))) {
                        fx += 5;
                        MoveSprite(&sprites[3], fx, fy);
                    }
                    else {
                        fx = 0;
                        fb = 0;
                        MoveSprite(&sprites[3], 0, 160);
                    }
                    MoveSprite(&sprites[1], bx, by);
                    if (level == 103) {
                        if (fl == 0) {
                            CopyOAM();
                            while (!(keyDown(KEY_UP)));
                            while ((keyDown(KEY_UP)));
                            while (!(keyDown(KEY_UP)));
                            while ((keyDown(KEY_UP)));
                            while (!(keyDown(KEY_DOWN)));
                            while ((keyDown(KEY_DOWN)));
                            while (!(keyDown(KEY_DOWN)));
                            while ((keyDown(KEY_DOWN)));
                            while (!(keyDown(KEY_LEFT)));
                            while ((keyDown(KEY_LEFT)));
                            while (!(keyDown(KEY_RIGHT)));
                            while ((keyDown(KEY_RIGHT)));
                            while (!(keyDown(KEY_LEFT)));
                            while ((keyDown(KEY_LEFT)));
                            while (!(keyDown(KEY_RIGHT)));
                            while ((keyDown(KEY_RIGHT)));
                            while (!(keyDown(KEY_B)));
                            while ((keyDown(KEY_B)));
                            while (!(keyDown(KEY_A)));
                            while ((keyDown(KEY_A)));
                            while (!(keyDown(KEY_START)));
                            while ((keyDown(KEY_START)));
							LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "l103b.lz", NULL), (u32)videoBuffer);
                            fl = 1;
                        }
                    }
                    if (musici > 1320) {
                        REG_SOUNDCNT_H = 0;                                                      //REG_SOUNDCNT_H = 0000 1011 0000 0100, volume = 100, sound goes to the left, sound goes to the right, timer 0 is used, FIFO buffer reset
                        REG_SOUNDCNT_X = 0;                                                       //REG_SOUNDCNT_X = 0000 0000 1000 0000, enable the sound system, DMA 1
                        REG_DM1SAD = 0;                               //REG_DM1SAD = NAME, address of DMA source is the digitized music sample
                        REG_DM1DAD = 0;                                                   //REG_DM1DAD = REG_SGFIFOA, address of DMA destination is FIFO buffer for direct sound A
                        REG_DM1CNT_H = 0;                                                    //REG_DM1CNT_H = 1011 0110 0100 0000, DMA destination is fixed, repeat transfer of 4 bytes when FIFO , buffer is empty, enable DMA 1 (number of DMA transfers is ignored), INTERRUPT
                        REG_TM0D = 0;                         //REG_TM0D = 65536-(16777216/frequency);, play sample every 16777216/frequency CPU cycles
                        REG_TM0CNT = 0;
                        playSound(3);
                        musici = 0;
					}
					else {
						musici++;
					}
                    if (level == 137) { //////////////////////////////////////////////////////////////////////////////////////////////////////////
                        if ((by < 45)AND(bx > 130)AND(bx < 149)) {
                            if (gravity == 1) {
                                REG_SOUNDCNT_H = 0;                                                      //REG_SOUNDCNT_H = 0000 1011 0000 0100, volume = 100, sound goes to the left, sound goes to the right, timer 0 is used, FIFO buffer reset
                                REG_SOUNDCNT_X = 0;                                                       //REG_SOUNDCNT_X = 0000 0000 1000 0000, enable the sound system, DMA 1
                                REG_DM1SAD = 0;                               //REG_DM1SAD = NAME, address of DMA source is the digitized music sample
                                REG_DM1DAD = 0;                                                   //REG_DM1DAD = REG_SGFIFOA, address of DMA destination is FIFO buffer for direct sound A
                                REG_DM1CNT_H = 0;                                                    //REG_DM1CNT_H = 1011 0110 0100 0000, DMA destination is fixed, repeat transfer of 4 bytes when FIFO , buffer is empty, enable DMA 1 (number of DMA transfers is ignored), INTERRUPT
                                REG_TM0D = 0;                         //REG_TM0D = 65536-(16777216/frequency);, play sample every 16777216/frequency CPU cycles
                                REG_TM0CNT = 0;
                                vsync
                                fillscreen3(0x0000);
                                SetMode(MODE_4 | BG2_ENABLE);
				LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "killscreen.img.lz", NULL), (u32)videoBuffer);
				LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "killscreen.pal.lz", NULL), (u32)BGPaletteMem);
                                Sleep(120);
                                fillpal("bg",0x0000);
                                Sleep(60);
				LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "black_final.img.lz", NULL), (u32)videoBuffer);
				LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "black_final.pal.lz", NULL), (u32)BGPaletteMem);
                                Sleep(180);
                                SaveInt(0, 1);
                                vsync
                                asm volatile("swi 0x26"::);
                            }
                            if (end == 0) {
				LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "ende.lz", NULL), (u32)videoBuffer);

                                end = 1;
                            }
                        }
                    }
			if(level>137)
			{
				level=137;
			}
                    if (keyDown(KEY_START)) {
                        REG_SOUNDCNT_H = 0;                                                      //REG_SOUNDCNT_H = 0000 1011 0000 0100, volume = 100, sound goes to the left, sound goes to the right, timer 0 is used, FIFO buffer reset
                        REG_SOUNDCNT_X = 0;                                                       //REG_SOUNDCNT_X = 0000 0000 1000 0000, enable the sound system, DMA 1
                        REG_DM1SAD = 0;                               //REG_DM1SAD = NAME, address of DMA source is the digitized music sample
                        REG_DM1DAD = 0;                                                   //REG_DM1DAD = REG_SGFIFOA, address of DMA destination is FIFO buffer for direct sound A
                        REG_DM1CNT_H = 0;                                                    //REG_DM1CNT_H = 1011 0110 0100 0000, DMA destination is fixed, repeat transfer of 4 bytes when FIFO , buffer is empty, enable DMA 1 (number of DMA transfers is ignored), INTERRUPT
                        REG_TM0D = 0;                         //REG_TM0D = 65536-(16777216/frequency);, play sample every 16777216/frequency CPU cycles
                        REG_TM0CNT = 0;
                        s1o = sprites[1].attribute2;
                        s2o = sprites[2].attribute2;
                        s3o = sprites[3].attribute2;
                        s4o = sprites[4].attribute2;
                        s5o = sprites[5].attribute2;
                        s6o = sprites[6].attribute2;
                        pause = 1;
                        while (pause == 1) {
				WaitForVblank();
                            SetMode(MODE_4 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D);
				LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "pause.img.lz", NULL), (u32)videoBuffer);
				LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "pause.pal.lz", NULL), (u32)BGPaletteMem);

                            MoveSprite(&sprites[1], 240, 160);
                            MoveSprite(&sprites[2], 240, 160);
                            MoveSprite(&sprites[3], 240, 160);
                            MoveSprite(&sprites[4], 240, 160);
                            initSprite(6, SIZE_32, RESTART_OAM);
                            initSprite(5, SIZE_32, PLAY_OAM);
                            MoveSprite(&sprites[5], 61, 66);
                            MoveSprite(&sprites[6], 121, 66);
                            CopyOAM();
                            while (!(keyDown(KEY_B))) {
                                if (keyDown(KEY_A)) {
					die();
                                }
                                if (keyDown(KEY_UP)) {
					FadeOutWhite(8); //White fade
                                    vsync //WaitForVblank();
                                    vsync //WaitForVblank();
                                    vsync //WaitForVblank();
                                    REG_DISPCNT = FORCE_BLANK; //Force White screen
                                    while (!((startpressed)AND(selectpressed))); //Waits until Sel+Start are pressed
                                    FadeIn(0); //Instant Fade In
									SetMode(MODE_4 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D); //Mode 4, BG2 ON, Linear OBJ Tile mapping, OBJ On
                                    REG_IE = 0; //Disables Interrupts
                                    REG_INTERUPT = INT_ALL; // Enables all interrupts
                                    REG_IE = 1; //enables interrupts
                                }
                                if ((keyDown(KEY_L))OR(keyDown(KEY_R))) { //Save Management
                                    int arpos; //Arrow Position
                                    FadeOutWhite(1); //Quick Fade Out
									LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "sramm.img.lz", NULL), (u32)videoBuffer);
									LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "sramm.pal.lz", NULL), (u32)BGPaletteMem);
									initSprite(5, SIZE_8, 50); //Arrow Sprite
                                    MoveSprite(&sprites[5], 15, 112); //Move Arrow
                                    MoveSprite(&sprites[6], 240, 160); //Moves Sprite 6 offscreen
                                    CopyOAM(); //Copies Object Attributes
									FadeInWhite(2); //Quick Fade In
                                    SetMode(MODE_4 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D); //Mode 4, BG2 on, Linear OBJ Tile mapping, OBJ On
                                    while (!(keyDown(KEY_B))) { // B pressed
                                        if (keyDown(KEY_LEFT)) { //Arrow Positions
                                            while (keyDown(KEY_LEFT));
                                            arpos--;
                                        }
                                        if (keyDown(KEY_RIGHT)) {
                                            while (keyDown(KEY_RIGHT));
                                            arpos++;
                                        }
                                        if (arpos < 0) {
                                            arpos = 0;
                                        }
                                        if (arpos > 2) {
                                            arpos = 2;
                                        }
                                        if (arpos == 0) {
                                            MoveSprite(&sprites[5], 15, 112);
                                            if (keyDown(KEY_A)) {
                                                arpos = 0;
                                                FadeOutWhite(1); //Quick Fade Out
												LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "save.img.lz", NULL), (u32)videoBuffer);
												LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "save.pal.lz", NULL), (u32)BGPaletteMem);
												MoveSprite(&sprites[5], 25, 32); //Arrow
                                                CopyOAM(); //Copies OBJ Attrib
												FadeInWhite(1); //Quick Fade In
                                                SetMode(MODE_4 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D); //Mode 4, BG2 on, Linear OBJ Tile mapping, OBJ On
                                                while (!(keyDown(KEY_B))) {
                                                    if (keyDown(KEY_UP)) {
                                                        while (keyDown(KEY_UP));
                                                        arpos--;
                                                    }
                                                    if (keyDown(KEY_DOWN)) {
                                                        while (keyDown(KEY_DOWN));
                                                        arpos++;
                                                    }
                                                    if (arpos < 0) {
                                                        arpos = 0;
                                                    }
                                                    if (arpos > 2) {
                                                        arpos = 2;
                                                    }
                                                    if (arpos == 0) {
                                                        MoveSprite(&sprites[5], 25, 32);
                                                        if (keyDown(KEY_A)) {
                                                            for (i = 0; i != 16; i++) {
                                                                memcpy(SRAM + 0x10 + i, 0xFF, 1);
                                                            }
                                                            SaveInt(0x10, level); //Saves
                                                            SaveInt(0x14, g);
                                                            SaveInt(0x16, gcd);
                                                            SaveInt(0x18, fl);
															SaveInt(0x1A, ed);
                                                        }
                                                    }
                                                    if (arpos == 1) {
                                                        MoveSprite(&sprites[5], 25, 45);
                                                        if (keyDown(KEY_A)) {
                                                            for (i = 0; i != 16; i++) { //saves
                                                                memcpy(SRAM + 0x20 + i, 0xFF, 1);
                                                            }
                                                            SaveInt(0x20, level);
                                                            SaveInt(0x24, g);
                                                            SaveInt(0x26, gcd);
                                                            SaveInt(0x28, fl);
															SaveInt(0x2A, ed);
                                                        }
                                                    }
                                                    if (arpos == 2) {
                                                        MoveSprite(&sprites[5], 25, 58); //Arrow Position
                                                        if (keyDown(KEY_A)) {
                                                            for (i = 0; i != 16; i++) {
                                                                memcpy(SRAM + 0x30 + i, 0xFF, 1); //Saves
                                                            }
                                                            SaveInt(0x30, level); //Saves
                                                            SaveInt(0x34, g);
                                                            SaveInt(0x36, gcd);
                                                            SaveInt(0x38, fl);
															SaveInt(0x3A, ed);
                                                        }
                                                    }
                                                    CopyOAM(); //COpies OBJ Attrib
                                                }
                                            }
                                        }
                                        if (arpos == 1) { //Load
                                            MoveSprite(&sprites[5], 94, 112);
                                            if (keyDown(KEY_A)) {
                                                arpos = 0;
                                                FadeOutWhite(1);
												LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "load.img.lz", NULL), (u32)videoBuffer);
												LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "load.pal.lz", NULL), (u32)BGPaletteMem);

												MoveSprite(&sprites[5], 25, 32);
												CopyOAM();
                                                FadeInWhite(1);
                                                SetMode(MODE_4 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D);
                                                while (!(keyDown(KEY_B))) {
                                                    if (keyDown(KEY_UP)) {
                                                        while (keyDown(KEY_UP));
                                                        arpos--;
                                                    }
                                                    if (keyDown(KEY_DOWN)) {
                                                        while (keyDown(KEY_DOWN));
                                                        arpos++;
                                                    }
                                                    if (arpos < 0) {
                                                        arpos = 0;
                                                    }
                                                    if (arpos > 2) {
                                                        arpos = 2;
                                                    }
                                                    if (arpos == 0) {
                                                        MoveSprite(&sprites[5], 25, 32);
                                                        if (keyDown(KEY_A)) {
                                                            g2 = g;
                                                            gcd2 = gcd;
                                                            fl2 = fl;
                                                            lv2 = level;
															ea2 = ed;
                                                            level = LoadInt(0x10);
                                                            g = LoadInt(0x14);
                                                            gcd = LoadInt(0x16);
                                                            fl = LoadInt(0x18);
															ed = LoadInt(0x1A);
                                                            if (level == 0) {
                                                                level = lv2;
                                                                fl = fl2;
                                                                gcd = gcd2;
                                                                g = g2;
																ed = ea2;
                                                            }
                                                            varreset();
                                                        }
                                                    }
                                                    if (arpos == 1) {
                                                        MoveSprite(&sprites[5], 25, 45);
                                                        if (keyDown(KEY_A)) {
                                                            g2 = g;
                                                            gcd2 = gcd;
                                                            fl2 = fl;
                                                            lv2 = level;
															ea2 = ed;
                                                            level = LoadInt(0x20);
                                                            g = LoadInt(0x24);
                                                            gcd = LoadInt(0x26);
                                                            fl = LoadInt(0x28);
															ed = LoadInt(0x2A);
                                                            if (level == 0) {
																level = lv2;
																fl = fl2;
																gcd = gcd2;
																g = g2;
																ed = ea2;
                                                            }
                                                            varreset();
                                                        }
                                                    }
                                                    if (arpos == 2) {
                                                        MoveSprite(&sprites[5], 25, 58);
                                                        if (keyDown(KEY_A)) {
															g2 = g;
															gcd2 = gcd;
															fl2 = fl;
															lv2 = level;
															ea2 = ed;
															level = LoadInt(0x30);
															g = LoadInt(0x34);
															gcd = LoadInt(0x36);
															fl = LoadInt(0x38);
															ed = LoadInt(0x3A);
															if (level == 0) {
																level = lv2;
																fl = fl2;
																gcd = gcd2;
																g = g2;
																ed = ea2;
															}
                                                            varreset();
                                                        }
                                                    }
                                                    CopyOAM();
                                                }
                                            }
                                        }
                                        if (arpos == 2) { //Erase
                                            MoveSprite(&sprites[5], 173, 112);
                                            if (keyDown(KEY_A)) {
                                                arpos = 0;
                                                FadeOutWhite(1);
												LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "erase.img.lz", NULL), (u32)videoBuffer);
												LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "erase.pal.lz", NULL), (u32)BGPaletteMem);

												MoveSprite(&sprites[5], 25, 32);
												CopyOAM();
                                                FadeInWhite(1);
                                                SetMode(MODE_4 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D);
                                                while (!(keyDown(KEY_B))) {
                                                    if (keyDown(KEY_UP)) {
                                                        while (keyDown(KEY_UP));
                                                        arpos--;
                                                    }
                                                    if (keyDown(KEY_DOWN)) {
                                                        while (keyDown(KEY_DOWN));
                                                        arpos++;
                                                    }
                                                    if (arpos < 0) {
                                                        arpos = 0;
                                                    }
                                                    if (arpos > 2) {
                                                        arpos = 2;
                                                    }
                                                    if (arpos == 0) {
                                                        MoveSprite(&sprites[5], 25, 32);
                                                        if (keyDown(KEY_A)) {
                                                            for (i = 0; i != 16; i++) {
                                                                memcpy(SRAM + 0x10, 0x06000ED0, 16);
                                                            }
                                                        }
                                                    }
                                                    if (arpos == 1) {
                                                        MoveSprite(&sprites[5], 25, 45);
                                                        if (keyDown(KEY_A)) {
                                                            for (i = 0; i != 16; i++) {
                                                                memcpy(SRAM + 0x20, 0x06000ED0, 16);
                                                            }
                                                        }
                                                    }
                                                    if (arpos == 2) {
                                                        MoveSprite(&sprites[5], 25, 58);
                                                        if (keyDown(KEY_A)) {
                                                            memcpy(SRAM + 0x30, 0x06000ED0, 16);

                                                        }
                                                    }
                                                    CopyOAM(); //Copies OBJ Attrib
                                                }
                                            }
                                        }
                                        CopyOAM(); //Copies OBJ Attrib
                                    }
                                }
                            }
                            pause = 0; //Exits Pause
			    SetMode(MODE_4 | BG2_ENABLE); //Mode 4, BG2 On
                            sprites[4].attribute0 = COLOR_256 | WIDE | 240; //Slot 4: Version Counter (64x32)
                            sprites[4].attribute1 = SIZE_64 | 160;
                            sprites[4].attribute2 = 512 + 280;
                            MoveSprite(&sprites[4], 0, 152); //Version pos
                            MoveSprite(&sprites[2], 223, 128); //Goal Pos
			    MoveSprite(&sprites[5],240,160); //Spr5 Offscreen
			    MoveSprite(&sprites[6], 240,160); //Spr6 Offscreen
                            updateSprite(1, 0, SIZE_32, 1); //Block
                            updateSprite(2, 48, SIZE_8, 1); //Goal
                            sprites[3].attribute0 = COLOR_256 | WIDE | 240; //Slot 3: Fireball (32x16)
                            sprites[3].attribute1 = SIZE_32 | 160;
                            sprites[3].attribute2 = 512 + 32;
                            sprites[4].attribute0 = COLOR_256 | WIDE | 240; //Slot 4: Version Counter (64x32)
                            sprites[4].attribute1 = SIZE_64 | 160;
                            sprites[4].attribute2 = 512 + 280;
                            updateSprite(5, s5o, SIZE_8, 1); //Spr5
                            updateSprite(6, s6o, SIZE_8, 1); //Spr6
                            MoveSprite(&sprites[4], 0, 152);
                            FadeOut(1); //Quick Fade In
							levels();
                            if (level == 103) {
                                if (fl == 1) {
									LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "l103b.img.lz", NULL), (u32)videoBuffer);

                                }
                            }
                            else if (level == 85) {
                                if (gcd == 1) {
									LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "l85b.lz", NULL), (u32)videoBuffer);

                                }
                            }
                            else if (level == 137) {
                                if (end == 1) {
									LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "ende.lz", NULL), (u32)videoBuffer);

                                }
                            }
			    CopyOAM();
			    SetMode(MODE_3 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D); //Mode 3, BG2 on, Linear OBJ Tile mapping, OBJ On
                            FadeIn(1);
                            musici = 0;
                            playSound(3);
                        }
                    }
             }
        }
    }
    return 0;
}