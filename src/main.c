// Main source file for Super Block Jump - Game Boy Advance Edition. Feel free to edit and recompile the source if you want. If you are to recompile the game, You will need DevKitARM and HeartLib installed.
void vblfunc();
#include "../heartlib/libheart.h" //main function library (that I made)
extern const u8 soundbank_bin_end[];
extern const u8 soundbank_bin[];
extern const u32 soundbank_bin_size;
extern gba_system __hrt_system;
// u16 LevelBuffer[38400] HRT_EWRAM_DATA; // why do we have this?
#include "../inc/defs.h" //external definitions, variables
#include "../inc/soundbank.h"

#include "../inc/flash.h" //batteryless patch

#include "../inc/more.h" //other functions

#define startpressed keyDown(KEY_START)
#define selectpressed keyDown(KEY_SELECT)
/*
	GBA HARDWARE
	CPU: 32-bit arm7tdmi RISC 16.78MHz, 8-bit Z80
	RAM: 32kb internal, 256kb external, 96kb VRAM, 1kb OAM
	DSP: LCD, 15-bit BGR 240x160, Max 32768 Colors
	ROM: 32MB
	SRAM/EEPROM: 1-128kb
	OAM: 128 Sprites
	BIOS: 16kb
*/
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



void vblFunc()
{
	hrt_CopyOAM();
	mmFrame();
    if((keyDown(KEY_A))AND(keyDown(KEY_B))AND(keyDown(KEY_SELECT))AND(keyDown(KEY_START))) {
        hrt_RegisterRamReset(hrt_ConfigRegisterRamReset(0,0,0,0,0,0,0,1));
        hrt_SoftReset();
    }
}

int main()   //Entry Point
{
	//hrt_EnableRTC();

    // hrt_Init();

    __hrt_system.hrt_start = 1;
    REG_IME = 1;
    hrt_irqInit();
    hrt_irqEnable(IRQ_VBLANK);

    // FLASH PATCH
    flash_type = get_flash_type();
    bytecopy(AGB_SRAM, ((void*)AGB_ROM+(u32)flash_sram_area), AGB_SRAM_SIZE);


    //flash_entrypoint();

    mmInitDefault((mm_addr)soundbank_bin, 32);
	mmSetModuleVolume(512);
    REG_SOUNDCNT_H = 0x330E;
    mm_sound_effect logotheme = {
        { SFX_LOGOTHEME },			// id
        (int)(1.0f * (1 << 10)),	// rate
        0,		// handle
        255,	// volume
        0,	// panning
    };
    mm_sound_effect punch = {
        { SFX_PUNCH },			// id
        (int)(1.0f * (1 << 10)),	// rate
        0,		// handle
        255,	// volume
        0,	// panning
    };
    mm_sound_effect bgm = {
        { SFX_MUSIC },			// id
        (int)((1.0f * (1 << 10))),	// rate
        0,		// handle
        255,	// volume
        0,	// panning
    };
    mm_sound_effect pka = {
        { SFX_POOKA },			// id
        (int)(1.0f * (1 << 10)),	// rate
        0,		// handle
        255,	// volume
        0,	// panning
    };
    mm_sound_effect trp = {
        { SFX_TRAMPOLINE },			// id
        (int)(1.0f * (1 << 10)),	// rate
        0,		// handle
        255,	// volume
        0,	// panning
    };
    mm_sound_effect prt = {
        { SFX_PORTAL },			// id
        (int)(1.0f * (1 << 10)),	// rate
        0,		// handle
        255,	// volume
        0,	// panning
    };
    mm_sfxhand portal = 0;
    mm_sound_effect png = {
        { SFX_PONG },			// id
        (int)(1.0f * (1 << 10)),	// rate
        0,		// handle
        255,	// volume
        0,	// panning
    };
    mm_sound_effect buzz = {
        { SFX_BUZZ },			// id
        (int)(1.0f * (1 << 10)),	// rate
        0,		// handle
        255,	// volume
        0,	// panning
    };
    mm_sound_effect reboot = {
        { SFX_REBOOTDISC },			// id
        (int)(1.0f * (1 << 10)),	// rate
        0,		// handle
        255,	// volume
        0,	// panning
    };
    mm_sound_effect stat = {
        { SFX_STATIC },			// id
        (int)(1.0f * (1 << 10)),	// rate
        0,		// handle
        255,	// volume
        0,	// panning
    };
    mm_sound_effect die2 = {
        { SFX_DEATH },			// id
        (int)(1.0f * (1 << 10)),	// rate
        0,		// handle
        255,	// volume
        0,	// panning
    };
    mm_sound_effect eneded = {
        { SFX_ENEDEATH },			// id
        (int)(1.0f * (1 << 10)),	// rate
        0,		// handle
        255,	// volume
        0,	// panning
    };
    mm_sfxhand enedeth = 0;
    mm_sfxhand deth = 0;
    mm_sfxhand statt = 0;
    mm_sfxhand rbds = 0;
    mm_sfxhand bzz = 0;
    mm_sfxhand pong = 0;
    mm_sfxhand tramp = 0;
    mm_sfxhand pook = 0;
    mm_sfxhand lgthme = 0;
    mm_sfxhand pnch = 0;
    mm_sfxhand music = 0;
	mmSetVBlankHandler(vblFunc);
    if(!((hrt_GetBiosChecksum()==0xBAAE187F)||(hrt_GetBiosChecksum()==0xBAAE1880))) {
        hrt_SetDSPMode(3, //Mode
                       0,								  //CGB Mode
                       0,								  //Frame Select
                       0,                               //Unlocked HBlank
                       0,                               //Linear OBJ Tile Mapping
                       0,                               //Force Blank
                       0,                               //BG 0
                       0,                               //BG 1
                       1,                               //BG 2
                       0,                               //BG 3
                       0,                               //OBJ
                       0,                               //Win 0
                       0,                               //Win 1
                       0);							  //OBJWin
        hrt_PrintOnBitmap(0, 0, "Error. BIOS Invalid. Abort."); //draws text
        while (1) {
            hrt_VblankIntrWait();
        }
    }
    if ((keyDown(KEY_A))AND(keyDown(KEY_B))) { //SRAM Clear Function
        hrt_SetFXMode(1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0);
        hrt_SetFXLevel(0);
        while (((keyDown(KEY_A))OR(keyDown(KEY_B)))) {
            hrt_VblankIntrWait();
        } //waits until a or b is not pressed
        hrt_SetDSPMode(3, //Mode
                       0,								  //CGB Mode
                       0,								  //Frame Select
                       0,                               //Unlocked HBlank
                       0,                               //Linear OBJ Tile Mapping
                       0,                               //Force Blank
                       0,                               //BG 0
                       0,                               //BG 1
                       1,                               //BG 2
                       0,                               //BG 3
                       0,                               //OBJ
                       0,                               //Win 0
                       0,                               //Win 1
                       0);							  //OBJWin
        hrt_PrintOnBitmap(-1, 0, "ERASE SAVE DATA?"); //draws text
        for (i = 0; i < 17; i++) {
            hrt_SetFXLevel(16 - i);
            hrt_SleepF(2);
        }
        while (!(((keyDown(KEY_A))OR(keyDown(KEY_B))))); //waits until a or b is pressed
        if (keyDown(KEY_A)) {
            hrt_FillScreen(0x0000); //makes whole screen black
            hrt_PrintOnBitmap(0, 0, "ARE YOU SURE?"); //draws text
            hrt_PrintOnBitmap(0, 9, "ALL DATA WILL BE ERASED."); //draws text
            while (((keyDown(KEY_A))OR(keyDown(KEY_B)))) {
                hrt_VblankIntrWait();
            } //waits until a or b is not pressed
            while (!(((keyDown(KEY_A))OR(keyDown(KEY_B))))) {
                hrt_VblankIntrWait();
            } //waits until a or b is pressed
            if (keyDown(KEY_A)) {
                while (((keyDown(KEY_A))OR(keyDown(KEY_B)))) {
                    hrt_VblankIntrWait();
                } //waits until a or b is not pressed
                hrt_FillScreen(0x0000); //makes screen black
                hrt_PrintOnBitmap(-1, 0, "ERASING....."); //draws text
                for(int i = 0; i < 0xFF; i++)
                {
                    SRAM[i] = (u8)0;
                }
                //hrt_SleepF(240); //Sleeps for 4 seconds

                // FLASH PATCH

                copyToFlash();

                hrt_PrintOnBitmap(-1, 0, "THE SYSTEM WILL NOW RESTART."); //draw text
                while (!(KEY_ANY_PRESSED)) {
                    hrt_VblankIntrWait();
                }//waits until any key is pressed
                asm volatile("swi 0x260000"::); //resets console
            }
            else {
                hrt_FillScreen(0x0000); //clears screen
                hrt_PrintOnBitmap(-1, 0, "THE PROCESS WAS ABORTED."); //draws text
                hrt_PrintOnBitmap(-1, 9, "THE SYSTEM WILL NOW RESTART."); //draws text
                while (!(KEY_ANY_PRESSED)) {
                    hrt_VblankIntrWait();
                } //waits until any key is pressed
                asm volatile("swi 0x260000"::); //resets console
            }
        }
        else {
            hrt_FillScreen(0x0000);
            hrt_PrintOnBitmap(-1, 0, "THE PROCESS WAS ABORTED."); //draws text
            hrt_PrintOnBitmap(-1, 9, "THE SYSTEM WILL NOW RESTART."); //draws text
            while (!(KEY_ANY_PRESSED)) {
                hrt_VblankIntrWait();
            } //waits until any key pressed
            asm volatile("swi 0x260000"::); //resets console
        }
    }
    const GBFS_FILE *dat = find_first_gbfs_file(find_first_gbfs_file); //defines GBFS file
    crash = hrt_LoadByte(0); //Crash //crash variable
    saveone = hrt_LoadByte(1); //Save one
    savetwo = hrt_LoadByte(6); //Save two
    savethree = hrt_LoadByte(0xb); //Save Three
	rand1 = hrt_LoadByte(0x60);
    //RNGSeed = hrt_LoadByte(0); //RNG
    if (crash == 2) { //Crash 2
        hrt_SetDSPMode(3, //Mode
                       0,								  //CGB Mode
                       0,								  //Frame Select
                       0,                               //Unlocked HBlank
                       0,                               //Linear OBJ Tile Mapping
                       0,                               //Force Blank
                       0,                               //BG 0
                       0,                               //BG 1
                       1,                               //BG 2
                       0,                               //BG 3
                       0,                               //OBJ
                       0,                               //Win 0
                       0,                               //Win 1
                       0);							  //OBJWin
        hrt_Memcpy(VRAM, 0x0000, 38400); //Glitchy Screen
        hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
        for (i = 0; i < 17; i++) {
            hrt_SetFXLevel(16 - i);
            hrt_SleepF(1);
        }
        hrt_SleepF(60); //Waits 1 Second
        hrt_SaveByte(0, 0); //Resets crash variable
        hrt_PrintOnBitmap(8, 8, "HAHAHAHAHAHAHAHAHAHAH!"); //Draws text

        //FLASH PATCH

        copyToFlash();

        while (!(KEY_ANY_PRESSED)) {
            hrt_VblankIntrWait();
        } //Waits until any button is pressed
        asm volatile("swi 0x260000"::); //resets console
    }

    if ((crash == 0)AND(saveone == 0)AND(savetwo == 0)AND(savethree == 0)AND(RNGSeed == 0)) {
        empty = 1; //empty
    }
    if (empty == 1) { //SRAM Empty Screen
        hrt_SetDSPMode(4, //Mode
                       0,								  //CGB Mode
                       0,								  //Frame Select
                       0,                               //Unlocked HBlank
                       0,                               //Linear OBJ Tile Mapping
                       0,                               //Force Blank
                       0,                               //BG 0
                       0,                               //BG 1
                       1,                               //BG 2
                       0,                               //BG 3
                       0,                               //OBJ
                       0,                               //Win 0
                       0,                               //Win 1
                       0);							  //OBJWin
        hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "srame.img.lz", NULL), (u32)VRAM); //hrt_LZ77 decompresses file "srame.img.lz" to VRAM
        hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "srame.pal.lz", NULL), (u32)BGPaletteMem); //hrt_LZ77 decompresses file "sramc.pal.lz" to BGPaletteMem
        hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
        for (i = 0; i < 17; i++) {
            hrt_SetFXLevel(16-i);
            hrt_SleepF(1);
        }
        while (!(KEY_ANY_PRESSED)); //waits until any key is pressed
        empty2 = 1; //empty2
        hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
        for (i = 0; i < 17; i++) {
            hrt_SetFXLevel(i);
            hrt_SleepF(1);
        }
    }
    // RNGRSeed = (RNGSeed + REG_VCOUNT + x +y - bx + (by\3) + (level\3) + savetwo - saveone + (savethree\GetPixel(14, 4))) ;
	crash = hrt_LoadByte(0); //Crash //crash variable
	saveone = hrt_LoadByte(1); //Save one
	savetwo = hrt_LoadByte(6); //Save two
	savethree = hrt_LoadByte(0xb); //Save Three
	rand1 = hrt_LoadByte(0x60);
    hello = "//cart//data//allobjs.h: no newline at end of file       C:\\devkitadv\\bin\\objcopy -O binary main.elf main.gba       C:\\devkitadv\\bin\\gcc -marm -mthumb-interwork -o main.elf main.o      C:\\devkitadv\\bin\\gcc -c -O3 -mthumb-interwork main.c Hello. You have just found an eAsTeR eGg.";
    if (empty2 == 0) {
        hrt_VblankIntrWait();
        hrt_SetDSPMode(3, //Mode
                       0,								  //CGB Mode
                       0,								  //Frame Select
                       0,                               //Unlocked HBlank
                       0,                               //Linear OBJ Tile Mapping
                       0,                               //Force Blank
                       0,                               //BG 0
                       0,                               //BG 1
                       1,                               //BG 2
                       0,                               //BG 3
                       0,                               //OBJ
                       0,                               //Win 0
                       0,                               //Win 1
                       0);							  //OBJWin
        hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
        hrt_SetFXLevel(17);
        for (i = 0; i < 38400; i++) {
            VRAM[i] = 0xFFFF;
        }
        hrt_SetFXLevel(0);
		hrt_SeedRNG(rand1);
		wipe = hrt_CreateRNG() % 10;
		if (wipe == 0)
		{
			hrt_ScanLines(0x0000, 1, 3); //scanlines wipe
		}
		if (wipe == 6)
		{
			hrt_ScanLines(0x0000, 1, 3); //scanlines wipe
		}
		if (wipe == 7)
		{
			hrt_ScanLines(0x0000, 1, 3); //scanlines wipe
		}
		if (wipe == 1)
		{
			hrt_LineWipe(0x0000, 0, 3); //scanlines wipe
		}
		if (wipe == 8)
		{
			hrt_LineWipe(0x0000, 0, 3); //scanlines wipe
		}
		if (wipe == 9)
		{
			hrt_LineWipe(0x0000, 0, 3); //scanlines wipe
		}
		if (wipe == 2)
		{
			hrt_LeftWipe(0x0000, 1, 3); //scanlines wipe
		}
		if (wipe == 3)
		{
			hrt_RightWipe(0x0000, 1, 3); //scanlines wipe
		}
		if (wipe == 4)
		{
			hrt_TopWipe(0x0000, 1, 3); //scanlines wipe
		}
		if (wipe == 5)
		{
			hrt_BottomWipe(0x0000, 1, 3); //scanlines wipe
		}
		hrt_SaveByte(0x60, (u8)hrt_CreateRNG());
        hrt_FillScreen(0x0000); //makes screne black
        hrt_SetFXMode(1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0);
        for (i = 0; i < 17; i++) {
            hrt_SetFXLevel(i);
            hrt_SleepF(1);
        }
    }
    hrt_SetFXMode(1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0);
    hrt_SetDSPMode(4, //Mode
                   0,								  //CGB Mode
                   0,								  //Frame Select
                   0,                               //Unlocked HBlank
                   0,                               //Linear OBJ Tile Mapping
                   0,                               //Force Blank
                   0,                               //BG 0
                   0,                               //BG 1
                   1,                               //BG 2
                   0,                               //BG 3
                   0,                               //OBJ
                   0,                               //Win 0
                   0,                               //Win 1
                   0);							  //OBJWin
    hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "discliamer.img.lz", NULL), (u32)VRAM); //hrt_LZ77 decompresses disclaimer img
    hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "discliamer.pal.lz", NULL), (u32)BGPaletteMem);   //hrt_LZ77 decompresses disclaimer pal
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(16-i);
        hrt_SleepF(1);
    }
    time2 = 0; //time2r for credits
    while (!(time2 == 255 | keyDown(KEY_A))) {
        time2++;
        hrt_SetBGPalEntry(2, hrt_GetBGPalEntry(2) + 3); //Color Changing text
        hrt_SleepF(1); //Waits one frame
    }
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(i);
        hrt_SleepF(1);
    }
    hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "thx.img.lz", NULL), (u32)VRAM);
    hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "thx.pal.lz", NULL), (u32)BGPaletteMem);
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(16-i);
        hrt_SleepF(1);
    }
    time2 = 0; //time2r
    while (!((time2 == 255) | (keyDown(KEY_A)))) {
        time2++; //time2r
        hrt_SleepF(1); //waits on frame
    }
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(i);
        hrt_SleepF(1);
    }
    hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "scratch.img.lz", NULL), (u32)VRAM);
    hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "scratch.pal.lz", NULL), (u32)BGPaletteMem);
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(16-i);
        hrt_SleepF(1);
    }
    time2 = 0; //time2r
    while (!((time2 == 255) | (keyDown(KEY_A)))) {
        time2++; //time2r
        hrt_SleepF(1); //waits one frame
    }
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(i);
        hrt_SleepF(1);
    }
    hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "gbadev.img.lz", NULL), (u32)VRAM);
    hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "gbadev.pal.lz", NULL), (u32)BGPaletteMem);
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(16-i);
        hrt_SleepF(1);
    }
    time2 = 0;
    while (!((time2 == 255) | (keyDown(KEY_A)))) {
        time2++;
        hrt_SleepF(1);
    }
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(i);
        hrt_SleepF(1);
    }
    hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "imadog.img.lz", NULL), (u32)VRAM);
    hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "imadog.pal.lz", NULL), (u32)BGPaletteMem);
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(16-i);
        hrt_SleepF(1);
    }
    time2 = 0;
    while (!((time2 == 255) | (keyDown(KEY_A)))) {
        time2++;
        hrt_SleepF(1);
    }
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(i);
        hrt_SleepF(1);
    }
    hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "slyangel.img.lz", NULL), (u32)VRAM);
    hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "slyangel.pal.lz", NULL), (u32)BGPaletteMem);
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(16-i);
        hrt_SleepF(1);
    }
    time2 = 0;
    while (!((time2 == 255) | (keyDown(KEY_A)))) {
        time2++;
        hrt_SleepF(1);
    }
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(i);
        hrt_SleepF(1);
    }
    hrt_SetDSPMode(3, //Mode
                   0,								  //CGB Mode
                   0,								  //Frame Select
                   0,                               //Unlocked HBlank
                   0,                               //Linear OBJ Tile Mapping
                   0,                               //Force Blank
                   0,                               //BG 0
                   0,                               //BG 1
                   1,                               //BG 2
                   0,                               //BG 3
                   0,                               //OBJ
                   0,                               //Win 0
                   0,                               //Win 1
                   0);							  //OBJWin
    hrt_LZ77UnCompVRAM((u32) gbfs_get_obj(dat, "titlescreen.lz", NULL), (u32)VRAM);  //Titlescreen
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(16-i);
        hrt_SleepF(1);
    }
    while (!(keyDown(KEY_START))) {
        hrt_VblankIntrWait();
    }

    // TEST: make sure we are are we are on a goofy ahh cartridge
    //if(flash_type) crash = 1;

    if (crash == 1) { //Crash
        hrt_VblankIntrWait();
        hrt_SetDSPMode(4, //Mode
                       0,								  //CGB Mode
                       0,								  //Frame Select
                       0,                               //Unlocked HBlank
                       0,                               //Linear OBJ Tile Mapping
                       0,                               //Force Blank
                       0,                               //BG 0
                       0,                               //BG 1
                       1,                               //BG 2
                       0,                               //BG 3
                       0,                               //OBJ
                       0,                               //Win 0
                       0,                               //Win 1
                       0);							  //OBJWin
        statt = mmEffectEx(&stat);
        for (i = 0; i<30; i++) {
            hrt_VblankIntrWait();
            hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "stat1.img.lz", NULL), (u32)VRAM);
            hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "stat1.pal.lz", NULL), (u32)BGPaletteMem);
            hrt_SleepF(2);
            hrt_VblankIntrWait();
            hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "stat2.img.lz", NULL), (u32)VRAM);
            hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "stat2.pal.lz", NULL), (u32)BGPaletteMem);
            hrt_VblankIntrWait();
        }
        mmEffectCancel(statt);
        hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "bsod.img.lz", NULL), (u32)VRAM);
        hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "bsod.pal.lz", NULL), (u32)BGPaletteMem);
        hrt_SaveByte(0, 2);

        // FLASH PATCH
         copyToFlash();

        while (1) {
            hrt_VblankIntrWait();
        }
    }
    hrt_VblankIntrWait();
    hrt_SetDSPMode(4, //Mode
                   0,								  //CGB Mode
                   0,								  //Frame Select
                   0,                               //Unlocked HBlank
                   0,                               //Linear OBJ Tile Mapping
                   0,                               //Force Blank
                   0,                               //BG 0
                   0,                               //BG 1
                   1,                               //BG 2
                   0,                               //BG 3
                   0,                               //OBJ
                   0,                               //Win 0
                   0,                               //Win 1
                   0);							  //OBJWin
    lgthme = mmEffectEx(&logotheme);
    setbg2novb((void*)roto0Bitmap, (void*)roto0Palette); //logospin
	for (i = 0; i < 7; i++)
	{
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
	}
	setbg2novb((void*)roto49Bitmap, (void*)roto49Palette);
    hrt_VblankIntrWait();
    mmEffectCancel(lgthme);
    mmEffectEx(&punch);
    setbg2novb((void*)bgtwoBitmap, (void*)bgtwoPalette);
    hrt_SleepF(15);
    while (1) { //main loop for menu
        hrt_VblankIntrWait();
        if (keyDown(KEY_SELECT)) {
            for (i = 0; i < 17; i++) {
                hrt_SetFXLevel(i);
                hrt_SleepF(1);
            }
            hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "controlspage1.img.lz", NULL), (u32)VRAM);
            hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "controlspage1.pal.lz", NULL), (u32)BGPaletteMem);
            for (i = 0; i < 17; i++) {
                hrt_SetFXLevel(16-i);
                hrt_SleepF(1);
            }
            while (!(keyDown(KEY_A))) {
                hrt_VblankIntrWait();
            }
            while (keyDown(KEY_A)) {
                hrt_VblankIntrWait();
            }
            for (i = 0; i < 17; i++) {
                hrt_SetFXLevel(i);
                hrt_SleepF(1);
            }
            hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "controlspage2.img.lz", NULL), (u32)VRAM);
            hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "controlspage2.pal.lz", NULL), (u32)BGPaletteMem);
            for (i = 0; i < 17; i++) {
                hrt_SetFXLevel(16-i);
                hrt_SleepF(1);
            }
            while (!(keyDown(KEY_A))) {
                hrt_VblankIntrWait();
            }
            while (keyDown(KEY_A)) {
                hrt_VblankIntrWait();
            }
            for (i = 0; i < 17; i++) {
                hrt_SetFXLevel(i);
                hrt_SleepF(1);
            }
            setbg2novb((void*)bgtwoBitmap, (void*)bgtwoPalette);
            for (i = 0; i < 17; i++) {
                hrt_SetFXLevel(16-i);
                hrt_SleepF(1);
            }
        }
        if (keyDown(KEY_START)) {
            hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
            for (i = 0; i < 17; i++) {
                hrt_SetFXLevel(i);
                hrt_SleepF(8);
            }
            hrt_LoadOBJGFX((void*)sprsTiles, 11904); //loads the bitmap data for all of the objects, so that I don't have to go throught the hassle of making a palette for each individual object.
            hrt_LoadOBJPal((void*)sprsPal, 255); //Copies the specified palette data into memory address 0x5000200, which is the location of the palette of the objects in OAM.
            level = 1;
            pause2 = 1;
            levels();
            pause2 = 0;
            hrt_SetDSPMode(3, //Mode
                           0,								  //CGB Mode
                           0,								  //Frame Select
                           0,                               //Unlocked HBlank
                           1,                               //Linear OBJ Tile Mapping
                           0,                               //Force Blank
                           0,                               //BG 0
                           0,                               //BG 1
                           1,                               //BG 2
                           0,                               //BG 3
                           1,                               //OBJ
                           0,                               //Win 0
                           0,                               //Win 1
                           0);							  //OBJWin
            hrt_FillPalette(0, 0x0000);
            hrt_CreateOBJ(1,   //Sprite ID
                          240,							     //Start X
                          160,							     //Start Y
                          2,							     //Size
                          0,							     //Affine
                          0,							     //Horizontal Flip
                          0,							     //Vertical Flip
                          0,							     //Shape
                          0,							     //Double Size
                          0,							     //Mosaic
                          0,							     //Palette (16-Color only)
                          1,							     //Color setting
                          0,							     //Mode
                          0,								 //Priority
                          0);							 //Offset
            hrt_CreateOBJ(2,   //Sprite ID
                          240,							     //Start X
                          160,							     //Start Y
                          0,							     //Size
                          0,							     //Affine
                          0,							     //Horizontal Flip
                          0,							     //Vertical Flip
                          0,							     //Shape
                          0,							     //Double Size
                          0,							     //Mosaic
                          0,							     //Palette (16-Color only)
                          1,							     //Color setting
                          0,							     //Mode
                          0,								 //Priority
                          48);							 //Offset
            hrt_CreateOBJ(3,   //Sprite ID
                          240,							     //Start X
                          160,							     //Start Y
                          2,							     //Size
                          0,							     //Affine
                          0,							     //Horizontal Flip
                          0,							     //Vertical Flip
                          1,							     //Shape
                          0,							     //Double Size
                          0,							     //Mosaic
                          0,							     //Palette (16-Color only)
                          1,							     //Color setting
                          0,							     //Mode
                          0,								 //Priority
                          32);			 				 //Offset
            hrt_CreateOBJ(4,   //Sprite ID
                          240,							     //Start X
                          160,							     //Start Y
                          3,							     //Size
                          0,							     //Affine
                          0,							     //Horizontal Flip
                          0,							     //Vertical Flip
                          1,							     //Shape
                          0,			 				     //Double Size
                          0,							     //Mosaic
                          0,							     //Palette (16-Color only)
                          1,							     //Color setting
                          0,							     //Mode
                          0,			 					 //Priority
                          280);							 //Offset
            hrt_CreateOBJ(5,   //Sprite ID
                          240,							     //Start X
                          160,							     //Start Y
                          0,							     //Size
                          0,							     //Affine
                          0,							     //Horizontal Flip
                          0,							     //Vertical Flip
                          0,							     //Shape
                          0,							     //Double Size
                          0,							     //Mosaic
                          0,							     //Palette (16-Color only)
                          1,							     //Color setting
                          0,							     //Mode
                          0,								 //Priority
                          56);							 //Offset
            hrt_CreateOBJ(6,   //Sprite ID
                          240,							     //Start X
                          160,							     //Start Y
                          2,							     //Size
                          0,							     //Affine
                          0,							     //Horizontal Flip
                          0,							     //Vertical Flip
                          0,							     //Shape
                          0,							     //Double Size
                          0,							     //Mosaic
                          0,							     //Palette (16-Color only)
                          1,							     //Color setting
                          0,							     //Mode
                          0,								 //Priority
                          56);							 //Offset
            hrt_CreateOBJ(50,   //Sprite ID
                          240,							     //Start X
                          160,							     //Start Y
                          2,							     //Size
                          0,							     //Affine
                          0,							     //Horizontal Flip
                          0,							     //Vertical Flip
                          0,							     //Shape
                          0,							     //Double Size
                          0,							     //Mosaic
                          0,							     //Palette (16-Color only)
                          1,							     //Color setting
                          0,							     //Mode
                          0,								 //Priority
                          488);							 //Offset
            for (i = 0; i < 17; i++) {
                hrt_SetFXLevel(16-i);
                hrt_SleepF(8);
            }
			musicno = hrt_CreateRNG() % 7;
			switch(musicno)
			{
				case 0:
				    music = mmEffectEx(&bgm);
					break;
				case 1:
					mmStart(MOD_SONG2, MM_PLAY_LOOP);
					break; 
				case 2:
					mmStart(MOD_SONG3, MM_PLAY_LOOP);
					break;
				case 3:
					mmStart(MOD_SONG4, MM_PLAY_LOOP);
					break;
				case 4:
					mmStart(MOD_SONG5, MM_PLAY_LOOP);
					break;
				case 5:
					mmSetModuleVolume(768);
					mmStart(MOD_SONG6, MM_PLAY_LOOP);
					break;
				case 6:
					mmSetModuleVolume(1024);
					mmStart(MOD_SONG7, MM_PLAY_LOOP);
					break;
			}
            varreset();
            hrt_SetOBJXY(4, 0, 152);
            hrt_SetOBJXY(2, 223, 128);
            while (1) {
				if (achiup == 1)
				{
					if (achii == 0)
					{
						achieffa = 0;
						achii = 0;
					}
					achitimer++;
					hrt_SetFXMode(0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0);
					hrt_CreateOBJ(7, 240, 160, 3, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 120);
					hrt_SetOBJXY(7, 0, 0);
					hrt_CopyOAM();
					if (achiphase == 0)
					{
						if (!(achiframe == 16))
						{
							achiframe++;
							hrt_SetFXAlphaLevel(16-achiframe,             // Source intensity
								achiframe);
						}
						else
						{
							achiframe = 0;
							achiphase = 1;
							achitimer = 0;
						}
					}
					if (achiphase == 1)
					{
						if (achitimer == 90)
						{
							achitimer = 0;
							achiphase = 2;
							achieffa = 16;
							achieffb = 0;
							achiframe = 16;
						}
					}
					if (achiphase == 2)
					{
						if (!(achiframe == 0))
						{
							achiframe--;
							hrt_SetFXAlphaLevel(16-achiframe,             // Source intensity
								achiframe);
						}
						else
						{
							achiframe = 0;
							achiphase = 0;
							achiup = 0;
							achieffa = 0;
							achieffb = 16;
						}
					}
				}
                if(deathstate == 0) {
                    physics();
                }
                rand1 = hrt_CreateRNG() % 3;

                // Batteryless patch note: random seed is constantly updated
                // but only saved upon hitting the save function
                hrt_SaveByte(0x60, (u8)hrt_CreateRNG());


                hrt_SetOBJPalEntry(notificationcolor, hrt_GetOBJPalEntry(notificationcolor) + 10); //Color Changing text
				hrt_CopyOAM(); 
                hrt_VblankIntrWait();
				frames++;
				rand1 = hrt_CreateRNG() % 3;
                hrt_VblankIntrWait();
				frames++;
				goalanim();
                if (deathstate == 1) {
                    if (!(deathframe == 10)) {
                        deathframe++;
                        if (deathframe == 1) {
                            hrt_SetOffset(0, 0);
                            hrt_LoadOBJGFX((void*)shrink1Tiles, 512);
                        }
                        if (deathframe == 2) {
                            hrt_SetOffset(0, 0);
                            hrt_LoadOBJGFX((void*)shrink2Tiles, 512);
                        }
                        if (deathframe == 3) {
                            hrt_SetOffset(0, 0);
                            hrt_LoadOBJGFX((void*)shrink3Tiles, 512);
                        }
                        if (deathframe == 4) {
                            hrt_SetOffset(0, 0);
                            hrt_LoadOBJGFX((void*)shrink4Tiles, 512);
                        }
                        if (deathframe == 5) {
                            hrt_SetOffset(0, 0);
                            hrt_LoadOBJGFX((void*)shrink5Tiles, 512);
                        }
                        if (deathframe == 6) {
                            hrt_SetOffset(0, 0);
                            hrt_LoadOBJGFX((void*)shrink6Tiles, 512);
                        }
                        if (deathframe == 7) {
                            hrt_SetOffset(0, 0);
                            hrt_LoadOBJGFX((void*)shrink7Tiles, 512);
                        }
                        if (deathframe == 8) {
                            hrt_SetOffset(0, 0);
                            hrt_LoadOBJGFX((void*)shrink8Tiles, 512);
                        }
						if (deathframe == 9) {
							hrt_SetOffset(0, 0);
							hrt_LoadOBJGFX((void*)shrink9Tiles, 512);
						}
						if (deathframe == 10) {
							hrt_SetOffset(0, 0);
							hrt_LoadOBJGFX((void*)shrinkaTiles, 512);
						}
                    }
                    else {
                        deathstate = 0;
                        bx = 8;
                        by = 108;
						hrt_SetOffset(0, 0);
                        hrt_LoadOBJGFX((void*)sprsTiles, 512);
                    }
                }
				if(musicno == 0) {
                if (musici > 1320) {
                    music = mmEffectEx(&bgm);
                    musici = 0;
                }
                else {
                    musici++;
                }
			}
                if ((BlockTouchingColor(0x001F) == 1)) {
                    if (deathstate == 0) {
                        die();
                    }
                    if (level == 17) {
                        if (burnchieve == 0) {
                            burnchieve = 1;
                            achievement(8);
							achiframe = 0;
							achiup = 1;
                        }
                    }
                    if (level == 14) {
                        if (pookachieve == 0) {
                            pookachieve = 1;
                            achievement(6);
							achiframe = 0;
							achiup = 1;
                            pook = mmEffectEx(&pka);
                        }
                    }
                    if (level == 15) {
                        if (pookachieve == 0) {
                            pookachieve = 1;
                            achievement(6);
							achiframe = 0;
							achiup = 1;
                            pook = mmEffectEx(&pka);
                        }
                    }
                }
                else if (BlockTouchingColor(0x7ED3) == 1) {
                    if (gravity == 1) {
                        tramp = mmEffectEx(&trp);
                        y = 6;
                    }
                    else {
                        tramp = mmEffectEx(&trp);
                        y = -6;
                    }
                }
                if (level == 49) {
                    hrt_CreateOBJ(5,   //Sprite ID
                                  240,							     //Start X
                                  160,							     //Start Y
                                  2,							     //Size
                                  0,							     //Affine
                                  0,							     //Horizontal Flip
                                  0,							     //Vertical Flip
                                  0,							     //Shape
                                  0,							     //Double Size
                                  0,							     //Mosaic
                                  0,							     //Palette (16-Color only)
                                  1,							     //Color setting
                                  0,							     //Mode
                                  0,								 //Priority
                                  248);							 //Offset
                    hrt_CreateOBJ(6,   //Sprite ID
                                  240,							     //Start X
                                  160,							     //Start Y
                                  2,							     //Size
                                  0,							     //Affine
                                  0,							     //Horizontal Flip
                                  0,							     //Vertical Flip
                                  0,							     //Shape
                                  0,							     //Double Size
                                  0,							     //Mosaic
                                  0,							     //Palette (16-Color only)
                                  1,							     //Color setting
                                  0,							     //Mode
                                  0,								 //Priority
                                  248);							 //Offset
                    if (td == 1) {
                        hrt_SetOBJXY(5, 128, ty);
                        if (NOT(ty < 0)) {
                            ty -= 4;
                        }
                        else {
                            td = 0;
                        }
                    }
                    else {
                        hrt_SetOBJXY(5, 128, ty);
                        if (NOT(ty > 113)) {
                            ty += 4;
                        }
                        else {
                            td = 1;
                        }
                    }
                    if (td2 == 1) {
                        hrt_SetOBJXY(6, 64, ty2);
                        if (NOT(ty2 < 0)) {
                            ty2 -= 3;
                        }
                        else {
                            td2 = 0;
                        }
                    }
                    else {
                        hrt_SetOBJXY(6, 64, ty2);
                        if (NOT(ty2 > 113)) {
                            ty2 += 3;
                        }
                        else {
                            td2 = 1;
                        }
                    }
                    if (((bx > 104)AND(bx < 160)AND(by < ty + 32))OR((bx > 40)AND(bx < 96)AND(by < ty2 + 32))) {		
						if (deathstate == 0) {
							die();
						}
                    }
                }
                else if ((level == 50)OR(level == 51)) {
                    hrt_CreateOBJ(6,   //Sprite ID
                                  240,							     //Start X
                                  160,							     //Start Y
                                  3,							     //Size
                                  0,							     //Affine
                                  0,							     //Horizontal Flip
                                  0,							     //Vertical Flip
                                  2,							     //Shape
                                  0,							     //Double Size
                                  0,							     //Mosaic
                                  0,							     //Palette (16-Color only)
                                  1,							     //Color setting
                                  0,							     //Mode
                                  0,								 //Priority
                                  184);							 //Offset
                    hrt_SetOBJXY(5, 240, 160);
                    if (sd == 1) {
                        hrt_SetOBJXY(6, 128, sy);
                        if (NOT(sy < 0)) {
                            sy -= 4;
                        }
                        else {
                            sd = 0;
                        }
                    }
                    else {
                        hrt_SetOBJXY(6, 128, sy);
                        if (NOT(sy > 81)) {
                            sy += 4;
                        }
                        else {
                            sd = 1;
                        }
                    }
                    if (deathstate == 0) {
                        if ((bx > 104)AND(bx < 160)AND(by < sy + 64)) {
                            if (deathstate == 0) {
                                die();
                            }
                        }
                    }
                }
                else if (level == 52) {
                    hrt_CreateOBJ(6,   //Sprite ID
                                  240,							     //Start X
                                  160,							     //Start Y
                                  0,							     //Size
                                  0,							     //Affine
                                  0,							     //Horizontal Flip
                                  0,							     //Vertical Flip
                                  0,							     //Shape
                                  0,							     //Double Size
                                  0,							     //Mosaic
                                  0,							     //Palette (16-Color only)
                                  1,							     //Color setting
                                  0,							     //Mode
                                  0,								 //Priority
                                  56);							 //Offset
                }
                else if (level == 58) {
                    if (gemv == 0) {
                        hrt_CreateOBJ(5,   //Sprite ID
                                      240,							     //Start X
                                      160,							     //Start Y
                                      3,							     //Size
                                      0,							     //Affine
                                      0,							     //Horizontal Flip
                                      0,							     //Vertical Flip
                                      1,							     //Shape
                                      0,							     //Double Size
                                      0,							     //Mosaic
                                      0,							     //Palette (16-Color only)
                                      1,							     //Color setting
                                      0,							     //Mode
                                      0,								 //Priority
                                      296);							 //Offset
                        hrt_SetOBJXY(5, 98, 66);
                        if (g == 1) {
                            hrt_CreateOBJ(5,   //Sprite ID
                                          240,							     //Start X
                                          160,							     //Start Y
                                          0,							     //Size
                                          0,							     //Affine
                                          0,							     //Horizontal Flip
                                          0,							     //Vertical Flip
                                          0,							     //Shape
                                          0,							     //Double Size
                                          0,							     //Mosaic
                                          0,							     //Palette (16-Color only)
                                          1,							     //Color setting
                                          0,							     //Mode
                                          0,								 //Priority
                                          56);							 //Offset
                            gemv = 1;
                        }
                    }
                    if ((bx > 74)AND(by < 94)AND(bx < LEVEL_MAX )AND(by > 42)) {
                        hrt_CreateOBJ(5,   //Sprite ID
                                      240,							     //Start X
                                      160,							     //Start Y
                                      0,							     //Size
                                      0,							     //Affine
                                      0,							     //Horizontal Flip
                                      0,							     //Vertical Flip
                                      0,							     //Shape
                                      0,							     //Double Size
                                      0,							     //Mosaic
                                      0,							     //Palette (16-Color only)
                                      1,							     //Color setting
                                      0,							     //Mode
                                      0,								 //Priority
                                      56);							 //Offset
                        g = 1;
                        gemv = 1;
                        if(gemchieve==0) {
                            achievement(11);
							achiframe = 0;
							achiup = 1;
                            gemchieve=1;
                        }
                    }
                }
                else if (level == 61) {
                    if ((es == 0)AND(!(ed==3))) {
                        hrt_CreateOBJ(5,   //Sprite ID
                                      240,							     //Start X
                                      160,							     //Start Y
                                      3,							     //Size
                                      0,							     //Affine
                                      0,							     //Horizontal Flip
                                      0,							     //Vertical Flip
                                      0,							     //Shape
                                      0,							     //Double Size
                                      0,							     //Mosaic
                                      0,							     //Palette (16-Color only)
                                      1,							     //Color setting
                                      0,							     //Mode
                                      0,								 //Priority
                                      360);							 //Offset
                        es = 1;
                        ex = 64;
                        hrt_SetOBJXY(5, 64, 81);
                    }
                    if (ed == 1) {
                        sprites[5].attribute1 = 3 * 16384 | 81;
                        hrt_SetOBJXY(5, ex, 81);
                        if (NOT(ex < 64)) {
                            ex -= 3;
                        }
                        else {
                            ed = 0;
                        }
                    }
                    if (ed == 0) {
                        sprites[5].attribute1 = 3 * 16384 | 4096 | 81;
                        hrt_SetOBJXY(5, ex, 81);
                        if (NOT(ex > 160)) {
                            ex += 3;
                        }
                        else {
                            ed = 1;
                        }
                    }
                    if (deathstate == 0) {
                        if ((bx > ex - 24)AND(!(ed == 3))) {
                            die();
                        }
                    }
                    if ((fx > ex - 32)AND(NOT(ea == 1))) {
                        fb = 0;
                        ed = 3;
                        fx = 0;
                        enedeth = mmEffectEx(&eneded);
                        hrt_SetOBJXY(3, 240, 160);
                        hrt_SetOBJXY(5, 240, 160);
                        if(monsterchieve==0) {
                            achievement(10);
							achiframe = 0;
							achiup = 1;
                            monsterchieve=1;
                        }
                    }
                }
                else if (level == 62) {
                    hrt_CreateOBJ(5,   //Sprite ID
                                  240,							     //Start X
                                  160,							     //Start Y
                                  0,							     //Size
                                  0,							     //Affine
                                  0,							     //Horizontal Flip
                                  0,							     //Vertical Flip
                                  0,							     //Shape
                                  0,							     //Double Size
                                  0,							     //Mosaic
                                  0,							     //Palette (16-Color only)
                                  1,							     //Color setting
                                  0,							     //Mode
                                  0,								 //Priority
                                  360);							 //Offset
                }
                else if (((level >= 43)AND(level <= 47))OR(level == LEVEL_MAX)OR(level==127)) {
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
                    if(captainchieve==0) {
                        achievement(2);
						achiframe = 0;
						achiup = 1;
                        captainchieve=1;
                    }
                }
                else if ((level == 55)OR(level == 56)) {
                    hrt_CreateOBJ(5,   //Sprite ID
                                  240,							     //Start X
                                  160,							     //Start Y
                                  2,							     //Size
                                  0,							     //Affine
                                  0,							     //Horizontal Flip
                                  0,							     //Vertical Flip
                                  0,							     //Shape
                                  0,							     //Double Size
                                  0,							     //Mosaic
                                  0,							     //Palette (16-Color only)
                                  1,							     //Color setting
                                  0,							     //Mode
                                  0,								 //Priority
                                  56);							 //Offset
                    hrt_SetOBJXY(5, 104, 64);
                    if ((bx > 80)AND(by > 40)AND(bx < 136)AND(by < 96)) {
                        if (keyDown(KEY_A)) {
                            mm_sound_effect jmp = {
                                { SFX_JUMP },			// id
                                (int)(1.0f * (1 << 10)),	// rate
                                0,		// handle
                                255,	// volume
                                0,	// panning
                            };
                            mm_sfxhand jump = 0;
                            jump = mmEffectEx(&jmp);
                            y = -4.05;
                            if(gdashchieve == 0) {
                                achievement(7);
								achiframe = 0;
								achiup = 1;
                                gdashchieve = 1;
                            }
                        }
                    }
                }
                else if (level == 57) {
                    hrt_CreateOBJ(5,   //Sprite ID
                                  240,							     //Start X
                                  160,							     //Start Y
                                  0,							     //Size
                                  0,							     //Affine
                                  0,							     //Horizontal Flip
                                  0,							     //Vertical Flip
                                  0,							     //Shape
                                  0,							     //Double Size
                                  0,							     //Mosaic
                                  0,							     //Palette (16-Color only)
                                  1,							     //Color setting
                                  0,							     //Mode
                                  0,								 //Priority
                                  56);							 //Offset
                }
                else if (((level > 31)AND(level < 40))OR(level == 42)OR(level == 54)) {
                    if (BlockTouchingColor(0x7E8C) == 1) {
                        portal = mmEffectEx(&prt);
                        if(portalchieve==0) {
                            achievement(16);
							achiframe = 0;
							achiup = 1;
                            portalchieve=1;
                        }
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
							y = abs(y);
                        }
                        else if (level == 35) {
                            bx = 140;
                            by = 97;
							x = y;
							y = 0;
                        }
                        else if (level == 36) {
                            bx = 6;
                            by = 31;
							x = y;
							y = 0;
                        }
                        else if (level == 37) {
                            bx = 173;
                            by = 5;
							y = x;
							x = 0;
                        }
                        else if (level == 38) {
                            bx = 16;
                            by = 3;
                        }
                        else if (level == 39) {
                            bx = 124;
                            by = 5;
							x = abs(x);
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
                    if (deathstate == 0) {
                        if ((bx > 90 - 24)AND(by > 81 - 24)AND(gcd == 0)) {
                            if (deathstate == 0) {
                                die();
                            }
                        }
                    }
                    if (gci == 0) {
                        hrt_CreateOBJ(5,   //Sprite ID
                                      240,							     //Start X
                                      160,							     //Start Y
                                      0,							     //Size
                                      0,							     //Affine
                                      0,							     //Horizontal Flip
                                      0,							     //Vertical Flip
                                      0,							     //Shape
                                      0,							     //Double Size
                                      0,							     //Mosaic
                                      0,							     //Palette (16-Color only)
                                      1,							     //Color setting
                                      0,							     //Mode
                                      0,								 //Priority
                                      74);							 //Offset
                    }
                    if ((fx > 45)AND(NOT(gcd == 1))) {
                        hrt_CreateOBJ(3,   //Sprite ID
                                      240,							     //Start X
                                      160,							     //Start Y
                                      2,							     //Size
                                      0,							     //Affine
                                      0,							     //Horizontal Flip
                                      0,							     //Vertical Flip
                                      1,							     //Shape
                                      0,							     //Double Size
                                      0,							     //Mosaic
                                      0,							     //Palette (16-Color only)
                                      1,							     //Color setting
                                      0,							     //Mode
                                      0,								 //Priority
                                      32);							 //Offset
                        hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "l85b.lz", NULL), (u32)VRAM);
                        hrt_SetOBJXY(3, 240, 160);
                        fb = 0;
                        gcd = 1;
                    }
                    if ((gcbt == 0)AND(gcd==0)) {
                        if (gcbx == 0) {
                            hrt_SetOBJXY(5, 80, by);
                            gcbx = 1;
                            gctx = 80;
                            gcby = by;
                        }
                        if (gcbx == 1) {
                            hrt_SetOBJXY(5, gctx, gcby);
                            if(gctx < 0) {
                                gctx -= 4;
                                if ((bx - 24 > gctx)AND(bx > gctx + 8)AND(by + 24 > gcby)AND(by < gcby + 8)) {
                                    if (deathstate == 0) {
                                        die();
                                    }
                                    gcbx = 0;
                                    hrt_SetOBJXY(5, 240, 160);
                                }
                            }
                            else {
                                gctx = 0;
                                hrt_SetOBJXY(5, 240,160);
                            }
                        }
                    }
                }
                else if (level == 84) {
                    if (pi == 0) {
                        hrt_CreateOBJ(5,   //Sprite ID
                                      240,							     //Start X
                                      160,							     //Start Y
                                      1,							     //Size
                                      0,							     //Affine
                                      0,							     //Horizontal Flip
                                      0,							     //Vertical Flip
                                      0,							     //Shape
                                      0,							     //Double Size
                                      0,							     //Mosaic
                                      0,							     //Palette (16-Color only)
                                      1,							     //Color setting
                                      0,							     //Mode
                                      0,								 //Priority
                                      100);							 //Offset
                        pi = 1;
                    }
                    px += psx;
                    py += psy;
                    if (py >= 128) {
                        psy = -4;
                        pong = mmEffectEx(&png);
                    }
                    if (py <= 0) {
                        psy = 4;
                        pong = mmEffectEx(&png);
                    }
                    if (px >= 224) {
                        psx = -4;
                        pong = mmEffectEx(&png);
                    }
                    if (px <= 0) {
                        psx = 4;
                        pong = mmEffectEx(&png);
                    }
                    hrt_SetOBJXY(5, px, py);
                    if ((bx > px - 24)AND(bx < px + 16)AND(by > py - 24)AND(by < py + 16)) {
                        if (deathstate == 0) {
                            die();
                        }
                        if(pongchieve==0) {
                            achievement(12);
							achiframe = 0;
							achiup = 1;
                            pongchieve=1;
                        }
                    }
                }
                else if (level == 85) {
                    hrt_CreateOBJ(5,   //Sprite ID
                                  240,							     //Start X
                                  160,							     //Start Y
                                  0,							     //Size
                                  0,							     //Affine
                                  0,							     //Horizontal Flip
                                  0,							     //Vertical Flip
                                  0,							     //Shape
                                  0,							     //Double Size
                                  0,							     //Mosaic
                                  0,							     //Palette (16-Color only)
                                  1,							     //Color setting
                                  0,							     //Mode
                                  0,								 //Priority
                                  0);							 //Offset
                }
                else if ((level > 9)AND(level < 13)) {
                    if (BlockTouchingColor(0x6300) == 1) {
                        if (deathstate == 0) {
                            die();
                        }
                    }
                }
                if ((keyDown(KEY_B))AND(g == 1)AND(block == 0)) {
                    fb = 1;
                    fy = by + 4;
                    fx = bx;
                    block = 1;
                }
                if ((fb == 1)AND(NOT(fx > 240))) {
                    fx += 5;
                    hrt_SetOBJXY(3, fx, fy);
                }
                else {
                    fx = 0;
                    fb = 0;
                    hrt_SetOBJXY(3, 0, 160);
                }
				hrt_SetOBJXY(1, bx, by);
                if (level == 103) {
                    if (fl == 0) {
                        hrt_CopyOAM();
                        while (!(keyDown(KEY_UP))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while ((keyDown(KEY_UP))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while (!(keyDown(KEY_UP))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while ((keyDown(KEY_UP))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while (!(keyDown(KEY_DOWN))) {
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
                        }
                        while ((keyDown(KEY_DOWN))) {
                           if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
						   }
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
                        }
                        while (!(keyDown(KEY_DOWN))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while ((keyDown(KEY_DOWN))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while (!(keyDown(KEY_LEFT))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while ((keyDown(KEY_LEFT))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while (!(keyDown(KEY_RIGHT))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while ((keyDown(KEY_RIGHT))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while (!(keyDown(KEY_LEFT))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while ((keyDown(KEY_LEFT))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while (!(keyDown(KEY_RIGHT))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while ((keyDown(KEY_RIGHT))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while (!(keyDown(KEY_B))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while ((keyDown(KEY_B))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while (!(keyDown(KEY_A))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while ((keyDown(KEY_A))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while (!(keyDown(KEY_START))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        while ((keyDown(KEY_START))) {
                            hrt_VblankIntrWait();
                            hrt_VblankIntrWait();
							if(musicno == 0) {
                            if (musici > 1320) {
                                music = mmEffectEx(&bgm);
                                musici = 0;
                            }
                            else {
                                musici++;
                            }
							}
                        }
                        hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "l103b.lz", NULL), (u32)VRAM);
                        fl = 1;
                        achievement(5);
						achiframe = 0;
						achiup = 1;
                    }
                }
                if((deaths==25)AND(deathchieve==0)) {
                    achievement(3);
					achiframe = 0;
					achiup = 1;
                    deathchieve=1;
                }
				if (NOT(keyDown(KEY_A))) {
					alock = 0;
				}
				if (NOT(keyDown(KEY_B))) {
					block = 0;
				}
                if (level == LEVEL_MAX) { //////////////////////////////////////////////////////////////////////////////////////////////////////////
                    if ((by < 45)AND(bx > 130)AND(bx < 149)) {
                        if (gravity == 1) {
                            hrt_VblankIntrWait();
                            hrt_FillScreen(0x0000);
                            hrt_SetDSPMode(4, //Mode
                                           0,								  //CGB Mode
                                           0,								  //Frame Select
                                           0,                               //Unlocked HBlank
                                           0,                               //Linear OBJ Tile Mapping
                                           0,                               //Force Blank
                                           0,                               //BG 0
                                           0,                               //BG 1
                                           1,                               //BG 2
                                           0,                               //BG 3
                                           0,                               //OBJ
                                           0,                               //Win 0
                                           0,                               //Win 1
                                           0);							  //OBJWin
                            mmEffectCancel(music);
                            mmStop();
                            mmEffectCancel(music);
                            bzz = mmEffectEx(&buzz);
                            hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "killscreen.img.lz", NULL), (u32)VRAM);
                            hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "killscreen.pal.lz", NULL), (u32)BGPaletteMem);
                            hrt_SleepF(120);
                            hrt_FillPalette(0,0x0000);
                            hrt_SleepF(60);
                            rbds = mmEffectEx(&reboot);
                            hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "black_final.img.lz", NULL), (u32)VRAM);
                            hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "black_final.pal.lz", NULL), (u32)BGPaletteMem);
                            hrt_SleepF(250);
                            hrt_SaveByte(0, 1);
                            hrt_VblankIntrWait();

                            // FLASH PATCH
                            copyToFlash();
							asm("swi 0x260000"::);
                        }
                        if (end == 0) {
                            hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "ende.lz", NULL), (u32)VRAM);
                            achievement(18);
							achiframe = 0;
							achiup = 1;
                            end = 1;
                        }
                    }
                }
                if(level>LEVEL_MAX) {
                    level=LEVEL_MAX;
                }
                if((jumpchieve==0)AND(jumps==100)) {
                    achievement(4);
					achiframe = 0;
					achiup = 1;
                    jumpchieve=1;
                }
                if(unreadchieves==1) {
                    hrt_SetOBJXY(50, 232, 152);
                }
                else {
                    hrt_SetOBJXY(50, 240, 160);
                }
                if (keyDown(KEY_START)) {
                    mmStop();
                    mmEffectCancel(music);
                    mmEffectCancel(portal);
                    s1o = sprites[1].attribute2;
                    s2o = sprites[2].attribute2;
                    s3o = sprites[3].attribute2;
                    s4o = sprites[4].attribute2;
                    s5o = sprites[5].attribute2;
                    s6o = sprites[6].attribute2;
                    pause2 = 1;
					arpos = 0;
                    while (pause2 == 1) {
						hrt_CreateOBJ(7, 240, 160, 3, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 120);
                        hrt_VblankIntrWait();
                        hrt_SetDSPMode(4, //Mode
                                       0,								  //CGB Mode
                                       0,								  //Frame Select
                                       0,                               //Unlocked HBlank
                                       1,                               //Linear OBJ Tile Mapping
                                       0,                               //Force Blank
                                       0,                               //BG 0
                                       0,                               //BG 1
                                       1,                               //BG 2
                                       0,                               //BG 3
                                       1,                               //OBJ
                                       0,                               //Win 0
                                       0,                               //Win 1
                                       0);							  //OBJWin
                        hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "pause.img.lz", NULL), (u32)VRAM);
                        hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "pause.pal.lz", NULL), (u32)BGPaletteMem);
                        hrt_SetOBJXY(1, 240, 160);
                        hrt_SetOBJXY(2, 240, 160);
                        hrt_SetOBJXY(3, 240, 160);
                        hrt_SetOBJXY(4, 240, 160);
                        hrt_CreateOBJ(5,   //Sprite ID
                                      1,							     //Start X
                                      16,							     //Start Y
                                      0,							     //Size
                                      0,							     //Affine
                                      0,							     //Horizontal Flip
                                      0,							     //Vertical Flip
                                      0,							     //Shape
                                      0,							     //Double Size
                                      0,							     //Mosaic
                                      0,							     //Palette (16-Color only)
                                      1,							     //Color setting
                                      0,							     //Mode
                                      0,								 //Priority
                                      50);							 //Offset
                        hrt_CopyOAM();
                        while (!((keyDown(KEY_B))OR(unpause == 1))) {
                            hrt_VblankIntrWait();
                            hrt_SetOBJPalEntry(notificationcolor, hrt_GetOBJPalEntry(notificationcolor) + 5); //Color Changing text
							if (keyDown(KEY_UP)) { //Arrow Positions
								while (keyDown(KEY_UP))
								{
									hrt_SetOBJPalEntry(notificationcolor, hrt_GetOBJPalEntry(notificationcolor) + 5);
									hrt_VblankIntrWait();
								}
								arpos--;
							}
							if (keyDown(KEY_DOWN)) { //Arrow Positions
								while (keyDown(KEY_DOWN))
								{
									hrt_SetOBJPalEntry(notificationcolor, hrt_GetOBJPalEntry(notificationcolor) + 5);
									hrt_VblankIntrWait();
								}
								arpos++;
							}
							if (arpos < 0) {
								arpos = 0;
							}
							if (arpos > 4) {
								arpos = 4;
							}
							hrt_CreateOBJ(5,   //Sprite ID
								1,							     //Start X
								(13 * arpos) + 16,							     //Start Y
								0,							     //Size
								0,							     //Affine
								0,							     //Horizontal Flip
								0,							     //Vertical Flip
								0,							     //Shape
								0,							     //Double Size
								0,							     //Mosaic
								0,							     //Palette (16-Color only)
								1,							     //Color setting
								0,							     //Mode
								0,								 //Priority
								50);							 //Offset
							if(keyDown(KEY_A)){
								if (arpos == 3) {
									hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
									for (i = 0; i < 17; i++) {
										hrt_SetFXLevel(i);
										hrt_SleepF(1);
									}
									hrt_SetOBJXY(5, 240, 160);
									hrt_SetOBJXY(6, 240, 160);
									unreadchieves = 0;
									hrt_SetOBJXY(50, 240, 160);
									hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "achievements.img.lz", NULL), (u32)VRAM);
									hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "achievements.pal.lz", NULL), (u32)BGPaletteMem);
									if (achdata[0] == 1) {
										hrt_CreateOBJ(0,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(0, achdatax[0], achdatay[0]);
									}
									if (achdata[1] == 1) {
										hrt_CreateOBJ(1,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(1, achdatax[1], achdatay[1]);
									}
									if (achdata[2] == 1) {
										hrt_CreateOBJ(2,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(3, achdatax[2], achdatay[2]);
									}
									if (achdata[3] == 1) {
										hrt_CreateOBJ(3,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(3, achdatax[3], achdatay[3]);
									}
									i = 4;
									if (achdata[i] == 1) {
										hrt_CreateOBJ(i,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(i, achdatax[i], achdatay[i]);
									}
									i = 5;
									if (achdata[i] == 1) {
										hrt_CreateOBJ(i,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(i, achdatax[i], achdatay[i]);
									}
									i = 6;
									if (achdata[i] == 1) {
										hrt_CreateOBJ(i,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(i, achdatax[i], achdatay[i]);
									}
									i = 7;
									if (achdata[i] == 1) {
										hrt_CreateOBJ(i,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(i, achdatax[i], achdatay[i]);
									}
									i = 8;
									if (achdata[i] == 1) {
										hrt_CreateOBJ(i,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(i, achdatax[i], achdatay[i]);
									}
									i = 9;
									if (achdata[i] == 1) {
										hrt_CreateOBJ(i,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(i, achdatax[i], achdatay[i]);
									}
									i = 10;
									if (achdata[i] == 1) {
										hrt_CreateOBJ(i,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(i, achdatax[i], achdatay[i]);
									}
									i = 11;
									if (achdata[i] == 1) {
										hrt_CreateOBJ(i,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(i, achdatax[i], achdatay[i]);
									}
									i = 12;
									if (achdata[i] == 1) {
										hrt_CreateOBJ(i,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(i, achdatax[i], achdatay[i]);
									}
									i = 13;
									if (achdata[i] == 1) {
										hrt_CreateOBJ(i,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(i, achdatax[i], achdatay[i]);
									}
									i = 14;
									if (achdata[i] == 1) {
										hrt_CreateOBJ(i,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(i, achdatax[i], achdatay[i]);
									}
									i = 15;
									if (achdata[i] == 1) {
										hrt_CreateOBJ(i,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(i, achdatax[i], achdatay[i]);
									}
									i = 16;
									if (achdata[i] == 1) {
										hrt_CreateOBJ(i,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(i, achdatax[i], achdatay[i]);
									}
									i = 17;
									if (achdata[i] == 1) {
										hrt_CreateOBJ(i,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(i, achdatax[i], achdatay[i]);
									}
									i = 18;
									if (achdata[i] == 1) {
										hrt_CreateOBJ(i,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(i, achdatax[i], achdatay[i]);
									}
									i = 19;
									if (achdata[i] == 1) {
										hrt_CreateOBJ(i,   //Sprite ID
											240,							     //Start X
											160,							     //Start Y
											0,							     //Size
											0,							     //Affine
											0,							     //Horizontal Flip
											0,							     //Vertical Flip
											0,							     //Shape
											0,							     //Double Size
											0,							     //Mosaic
											0,							     //Palette (16-Color only)
											1,							     //Color setting
											0,							     //Mode
											0,								 //Priority
											492);                       //Offset
										hrt_SetOBJXY(i, achdatax[i], achdatay[i]);
									}
									hrt_CopyOAM();
									hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
									for (i = 0; i < 17; i++) {
										hrt_SetFXLevel(16 - i);
										hrt_SleepF(1);
									}
									while (!(keyDown(KEY_B))) {
										hrt_VblankIntrWait();
									}
									i = 0;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									i++;
									hrt_SetOBJXY(i, 240, 160);
									hrt_CopyOAM();
									pause2 = 0; //Exits Pause
									hrt_SetDSPMode(4, //Mode
										0,								  //CGB Mode
										0,								  //Frame Select
										0,                               //Unlocked HBlank
										1,                               //Linear OBJ Tile Mapping
										0,                               //Force Blank
										0,                               //BG 0
										0,                               //BG 1
										0,                               //BG 2
										0,                               //BG 3
										0,                               //OBJ
										0,                               //Win 0
										0,                               //Win 1
										0);							  //OBJWin
									hrt_CreateOBJ(4,   //Sprite ID
										240,							     //Start X
										160,							     //Start Y
										3,							     //Size
										0,							     //Affine
										0,							     //Horizontal Flip
										0,							     //Vertical Flip
										1,							     //Shape
										0,							     //Double Size
										0,							     //Mosaic
										0,							     //Palette (16-Color only)
										1,							     //Color setting
										0,							     //Mode
										0,								 //Priority
										280);							 //Offset
									hrt_SetOBJXY(4, 0, 152); //Version pos
									hrt_SetOBJXY(2, 223, 128); //Goal Pos
									hrt_SetOBJXY(5, 240, 160); //Spr5 Offscreen
									hrt_SetOBJXY(6, 240, 160); //Spr6 Offscreen
									hrt_CreateOBJ(3,   //Sprite ID
										240,							     //Start X
										160,							     //Start Y
										2,							     //Size
										0,							     //Affine
										0,							     //Horizontal Flip
										0,							     //Vertical Flip
										1,							     //Shape
										0,							     //Double Size
										0,							     //Mosaic
										0,							     //Palette (16-Color only)
										1,							     //Color setting
										0,							     //Mode
										0,								 //Priority
										32);							 //Offset
									hrt_SetOBJXY(4, 0, 152);
									hrt_CreateOBJ(1,   //Sprite ID
										240,							     //Start X
										160,							     //Start Y
										2,							     //Size
										0,							     //Affine
										0,							     //Horizontal Flip
										0,							     //Vertical Flip
										0,							     //Shape
										0,							     //Double Size
										0,							     //Mosaic
										0,							     //Palette (16-Color only)
										1,							     //Color setting
										0,							     //Mode
										0,								 //Priority
										0);							 //Offset
									break;
									hrt_SetFXMode(1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0);
									for (i = 0; i < 17; i++) {
										hrt_SetFXLevel(i);
										hrt_SleepF(1);
									}
									pause2 = 1;
									levels();
									pause2 = 0;
									if (level == 103) {
										if (fl == 1) {
											hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "l103b.img.lz", NULL), (u32)VRAM);
										}
									}
									else if (level == 85) {
										if (gcd == 1) {
											hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "l85b.lz", NULL), (u32)VRAM);
										}
									}
									else if (level == LEVEL_MAX) {
										if (end == 1) {
											hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "ende.lz", NULL), (u32)VRAM);
										}
									}
									hrt_CopyOAM();
									hrt_SetDSPMode(3, //Mode
										0,								  //CGB Mode
										0,								  //Frame Select
										0,                               //Unlocked HBlank
										1,                               //Linear OBJ Tile Mapping
										0,                               //Force Blank
										0,                               //BG 0
										0,                               //BG 1
										1,                               //BG 2
										0,                               //BG 3
										1,                               //OBJ
										0,                               //Win 0
										0,                               //Win 1
										0);							  //OBJWin
									hrt_SetFXMode(1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0);
									for (i = 0; i < 17; i++) {
										hrt_SetFXLevel(16 - i);
										hrt_SleepF(1);
									}
								}
								if (arpos == 1) {
									if (deathstate == 0) {
										die();
									}
								}
								if (arpos == 2) {
									hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "pauses.img.lz", NULL), (u32)VRAM);
									hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "pauses.pal.lz", NULL), (u32)BGPaletteMem);
									while (keyDown(KEY_A));
									while (!(keyDown(KEY_A)));
									hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
									for (i = 0; i < 17; i++) {
										hrt_SetFXLevel(i);
										hrt_SleepF(8);
									}
									hrt_VblankIntrWait(); //WaitForVblank();
									hrt_VblankIntrWait();
									hrt_VblankIntrWait();
									REG_DISPCNT = 0x80; //Force White screen
									hrt_Suspend();
									hrt_SetFXLevel(0);
									hrt_SetDSPMode(4, //Mode
										0,								  //CGB Mode
										0,								  //Frame Select
										0,                               //Unlocked HBlank
										1,                               //Linear OBJ Tile Mapping
										0,                               //Force Blank
										0,                               //BG 0
										0,                               //BG 1
										1,                               //BG 2
										0,                               //BG 3
										1,                               //OBJ
										0,                               //Win 0
										0,                               //Win 1
										0);							  //OBJWin
								}
								if (arpos == 4) { //Save Management
									hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
									for (i = 0; i < 17; i++) {
										hrt_SetFXLevel(i);
										hrt_SleepF(1);
									}
									hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "sramm.img.lz", NULL), (u32)VRAM);
									hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "sramm.pal.lz", NULL), (u32)BGPaletteMem);
									hrt_CreateOBJ(5,   //Sprite ID
										240,							     //Start X
										160,							     //Start Y
										0,							     //Size
										0,							     //Affine
										0,							     //Horizontal Flip
										0,							     //Vertical Flip
										0,							     //Shape
										0,							     //Double Size
										0,							     //Mosaic
										0,							     //Palette (16-Color only)
										1,							     //Color setting
										0,							     //Mode
										0,								 //Priority
										50);							 //Offset
									hrt_SetOBJXY(5, 15, 112); //Move Arrow
									hrt_SetOBJXY(6, 240, 160); //Moves Sprite 6 offscreen
									hrt_CopyOAM(); //Copies Object Attributes
									hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
									for (i = 0; i < 17; i++) {
										hrt_SetFXLevel(16 - i);
										hrt_SleepF(1);
									}
									hrt_SetDSPMode(4, //Mode
										0,								  //CGB Mode
										0,								  //Frame Select
										0,                               //Unlocked HBlank
										1,                               //Linear OBJ Tile Mapping
										0,                               //Force Blank
										0,                               //BG 0
										0,                               //BG 1
										1,                               //BG 2
										0,                               //BG 3
										1,                               //OBJ
										0,                               //Win 0
										0,                               //Win 1
										0);							  //OBJWin
									while (!(keyDown(KEY_B))) { // B pressed
										hrt_VblankIntrWait();
										hrt_SetOBJPalEntry(notificationcolor, hrt_GetOBJPalEntry(notificationcolor) + 5); //Color Changing text
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
											hrt_SetOBJXY(5, 15, 112);
											if (keyDown(KEY_A)) {
												arpos = 0;
												hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
												for (i = 0; i < 17; i++) {
													hrt_SetFXLevel(i);
													hrt_SleepF(1);
												}
												hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "save.img.lz", NULL), (u32)VRAM);
												hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "save.pal.lz", NULL), (u32)BGPaletteMem);
												hrt_SetOBJXY(5, 25, 32); //Arrow
												hrt_CopyOAM(); //Copies OBJ Attrib
												hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
												for (i = 0; i < 17; i++) {
													hrt_SetFXLevel(16 - i);
													hrt_SleepF(1);
												}
												hrt_SetDSPMode(4, //Mode
													0,								  //CGB Mode
													0,								  //Frame Select
													0,                               //Unlocked HBlank
													1,                               //Linear OBJ Tile Mapping
													0,                               //Force Blank
													0,                               //BG 0
													0,                               //BG 1
													1,                               //BG 2
													0,                               //BG 3
													1,                               //OBJ
													0,                               //Win 0
													0,                               //Win 1
													0);							  //OBJWin
												while (!(keyDown(KEY_B))) {
													hrt_VblankIntrWait();
													hrt_SetOBJPalEntry(notificationcolor, hrt_GetOBJPalEntry(notificationcolor) + 5); //Color Changing text
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
														hrt_SetOBJXY(5, 25, 32);
														if (keyDown(KEY_A)) {
															hrt_SaveByte(0x01, level); //Saves
															hrt_SaveByte(0x02, g);
															hrt_SaveByte(0x03, gcd);
															hrt_SaveByte(0x04, fl);
															hrt_SaveByte(0x05, ed);
															i = 0;
															hrt_SaveByte(0x10, achdata[i]);
															i++;
															hrt_SaveByte(0x11, achdata[i]);
															i++;
															hrt_SaveByte(0x12, achdata[i]);
															i++;
															hrt_SaveByte(0x13, achdata[i]);
															i++;
															hrt_SaveByte(0x14, achdata[i]);
															i++;
															hrt_SaveByte(0x15, achdata[i]);
															i++;
															hrt_SaveByte(0x16, achdata[i]);
															i++;
															hrt_SaveByte(0x17, achdata[i]);
															i++;
															hrt_SaveByte(0x18, achdata[i]);
															i++;
															hrt_SaveByte(0x19, achdata[i]);
															i++;
															hrt_SaveByte(0x1A, achdata[i]);
															i++;
															hrt_SaveByte(0x1B, achdata[i]);
															i++;
															hrt_SaveByte(0x1C, achdata[i]);
															i++;
															hrt_SaveByte(0x1D, achdata[i]);
															i++;
															hrt_SaveByte(0x1E, achdata[i]);
															i++;
															hrt_SaveByte(0x1F, achdata[i]);
															i++;
															hrt_SaveByte(0x20, achdata[i]);
															i++;
															hrt_SaveByte(0x21, achdata[i]);
															i++;
															hrt_SaveByte(0x22, achdata[i]);
															i++;
															hrt_SaveByte(0x23, achdata[i]);

                                                            copyToFlash();
														}
													}
													if (arpos == 1) {
														hrt_SetOBJXY(5, 25, 45);
														if (keyDown(KEY_A)) {
															hrt_SaveByte(0x06, level);
															hrt_SaveByte(0x07, g);
															hrt_SaveByte(0x08, gcd);
															hrt_SaveByte(0x09, fl);
															hrt_SaveByte(0x0A, ed);
															i = 0;
															hrt_SaveByte(0x24, achdata[i]);
															i++;
															hrt_SaveByte(0x25, achdata[i]);
															i++;
															hrt_SaveByte(0x26, achdata[i]);
															i++;
															hrt_SaveByte(0x27, achdata[i]);
															i++;
															hrt_SaveByte(0x28, achdata[i]);
															i++;
															hrt_SaveByte(0x29, achdata[i]);
															i++;
															hrt_SaveByte(0x2A, achdata[i]);
															i++;
															hrt_SaveByte(0x2B, achdata[i]);
															i++;
															hrt_SaveByte(0x2C, achdata[i]);
															i++;
															hrt_SaveByte(0x2D, achdata[i]);
															i++;
															hrt_SaveByte(0x2E, achdata[i]);
															i++;
															hrt_SaveByte(0x2F, achdata[i]);
															i++;
															hrt_SaveByte(0x30, achdata[i]);
															i++;
															hrt_SaveByte(0x31, achdata[i]);
															i++;
															hrt_SaveByte(0x32, achdata[i]);
															i++;
															hrt_SaveByte(0x33, achdata[i]);
															i++;
															hrt_SaveByte(0x34, achdata[i]);
															i++;
															hrt_SaveByte(0x35, achdata[i]);
															i++;
															hrt_SaveByte(0x36, achdata[i]);
															i++;
															hrt_SaveByte(0x37, achdata[i]);

                                                            copyToFlash();
														}
													}
													if (arpos == 2) {
														hrt_SetOBJXY(5, 25, 58); //Arrow Position
														if (keyDown(KEY_A)) {
															hrt_SaveByte(0x0B, level); //Saves
															hrt_SaveByte(0x0C, g);
															hrt_SaveByte(0x0D, gcd);
															hrt_SaveByte(0x0E, fl);
															hrt_SaveByte(0x0F, ed);
															i = 0;
															hrt_SaveByte(0x38, achdata[i]);
															i++;
															hrt_SaveByte(0x39, achdata[i]);
															i++;
															hrt_SaveByte(0x3a, achdata[i]);
															i++;
															hrt_SaveByte(0x3b, achdata[i]);
															i++;
															hrt_SaveByte(0x3c, achdata[i]);
															i++;
															hrt_SaveByte(0x3d, achdata[i]);
															i++;
															hrt_SaveByte(0x3e, achdata[i]);
															i++;
															hrt_SaveByte(0x3f, achdata[i]);
															i++;
															hrt_SaveByte(0x40, achdata[i]);
															i++;
															hrt_SaveByte(0x41, achdata[i]);
															i++;
															hrt_SaveByte(0x42, achdata[i]);
															i++;
															hrt_SaveByte(0x43, achdata[i]);
															i++;
															hrt_SaveByte(0x44, achdata[i]);
															i++;
															hrt_SaveByte(0x45, achdata[i]);
															i++;
															hrt_SaveByte(0x46, achdata[i]);
															i++;
															hrt_SaveByte(0x47, achdata[i]);
															i++;
															hrt_SaveByte(0x48, achdata[i]);
															i++;
															hrt_SaveByte(0x49, achdata[i]);
															i++;
															hrt_SaveByte(0x4a, achdata[i]);
															i++;
															hrt_SaveByte(0x4b, achdata[i]);

                                                            copyToFlash();
														}
													}
													hrt_CopyOAM(); //COpies OBJ Attrib
												}
											}
										}
										if (arpos == 1) { //Load
											hrt_SetOBJXY(5, 94, 112);
											if (keyDown(KEY_A)) {
												arpos = 0;
												hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
												for (i = 0; i < 17; i++) {
													hrt_SetFXLevel(i);
													hrt_SleepF(1);
												}
												hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "load.img.lz", NULL), (u32)VRAM);
												hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "load.pal.lz", NULL), (u32)BGPaletteMem);
												hrt_SetOBJXY(5, 25, 32);
												hrt_CopyOAM();
												hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
												for (i = 0; i < 17; i++) {
													hrt_SetFXLevel(16 - i);
													hrt_SleepF(1);
												}
												hrt_SetDSPMode(4, //Mode
													0,								  //CGB Mode
													0,								  //Frame Select
													0,                               //Unlocked HBlank
													1,                               //Linear OBJ Tile Mapping
													0,                               //Force Blank
													0,                               //BG 0
													0,                               //BG 1
													1,                               //BG 2
													0,                               //BG 3
													1,                               //OBJ
													0,                               //Win 0
													0,                               //Win 1
													0);							  //OBJWin
												while (!(keyDown(KEY_B))) {
													hrt_VblankIntrWait();
													hrt_SetOBJPalEntry(notificationcolor, hrt_GetOBJPalEntry(notificationcolor) + 5); //Color Changing text
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
														hrt_SetOBJXY(5, 25, 32);
														if (keyDown(KEY_A)) {
															g2 = g;
															gcd2 = gcd;
															fl2 = fl;
															lv2 = level;
															ea2 = ed;
															level = hrt_LoadByte(0x01);
															g = hrt_LoadByte(0x02);
															gcd = hrt_LoadByte(0x03);
															fl = hrt_LoadByte(0x04);
															ed = hrt_LoadByte(0x05);
															if (level == 0) {
																level = lv2;
																fl = fl2;
																gcd = gcd2;
																g = g2;
																ed = ea2;
															}
															i = 0;
															achdata[i] = hrt_LoadByte(0x10);
															i++;
															achdata[i] = hrt_LoadByte(0x11);
															i++;
															achdata[i] = hrt_LoadByte(0x12);
															i++;
															achdata[i] = hrt_LoadByte(0x13);
															i++;
															achdata[i] = hrt_LoadByte(0x14);
															i++;
															achdata[i] = hrt_LoadByte(0x15);
															i++;
															achdata[i] = hrt_LoadByte(0x16);
															i++;
															achdata[i] = hrt_LoadByte(0x17);
															i++;
															achdata[i] = hrt_LoadByte(0x18);
															i++;
															achdata[i] = hrt_LoadByte(0x19);
															i++;
															achdata[i] = hrt_LoadByte(0x1a);
															i++;
															achdata[i] = hrt_LoadByte(0x1b);
															i++;
															achdata[i] = hrt_LoadByte(0x1c);
															i++;
															achdata[i] = hrt_LoadByte(0x1d);
															i++;
															achdata[i] = hrt_LoadByte(0x1e);
															i++;
															achdata[i] = hrt_LoadByte(0x1f);
															i++;
															achdata[i] = hrt_LoadByte(0x20);
															i++;
															achdata[i] = hrt_LoadByte(0x21);
															i++;
															achdata[i] = hrt_LoadByte(0x22);
															i++;
															achdata[i] = hrt_LoadByte(0x23);
															varreset();
															deathchieve = achdata[3];
															jumpchieve = achdata[4];
															pookachieve = achdata[6];
															gdashchieve = achdata[7];
															burnchieve = achdata[8];
															monsterchieve = achdata[10];
															gemchieve = achdata[11];
															pongchieve = achdata[12];
														}
													}
													if (arpos == 1) {
														hrt_SetOBJXY(5, 25, 45);
														if (keyDown(KEY_A)) {
															g2 = g;
															gcd2 = gcd;
															fl2 = fl;
															lv2 = level;
															ea2 = ed;
															level = hrt_LoadByte(0x06);
															g = hrt_LoadByte(0x07);
															gcd = hrt_LoadByte(0x08);
															fl = hrt_LoadByte(0x09);
															ed = hrt_LoadByte(0x0A);
															if (level == 0) {
																level = lv2;
																fl = fl2;
																gcd = gcd2;
																g = g2;
																ed = ea2;
															}
															varreset();
															i = 0;
															achdata[i] = hrt_LoadByte(0x24);
															i++;
															achdata[i] = hrt_LoadByte(0x25);
															i++;
															achdata[i] = hrt_LoadByte(0x26);
															i++;
															achdata[i] = hrt_LoadByte(0x27);
															i++;
															achdata[i] = hrt_LoadByte(0x28);
															i++;
															achdata[i] = hrt_LoadByte(0x29);
															i++;
															achdata[i] = hrt_LoadByte(0x2a);
															i++;
															achdata[i] = hrt_LoadByte(0x2b);
															i++;
															achdata[i] = hrt_LoadByte(0x2c);
															i++;
															achdata[i] = hrt_LoadByte(0x2d);
															i++;
															achdata[i] = hrt_LoadByte(0x2e);
															i++;
															achdata[i] = hrt_LoadByte(0x2f);
															i++;
															achdata[i] = hrt_LoadByte(0x30);
															i++;
															achdata[i] = hrt_LoadByte(0x31);
															i++;
															achdata[i] = hrt_LoadByte(0x32);
															i++;
															achdata[i] = hrt_LoadByte(0x33);
															i++;
															achdata[i] = hrt_LoadByte(0x34);
															i++;
															achdata[i] = hrt_LoadByte(0x35);
															i++;
															achdata[i] = hrt_LoadByte(0x36);
															i++;
															achdata[i] = hrt_LoadByte(0x37);
															deathchieve = achdata[3];
															jumpchieve = achdata[4];
															pookachieve = achdata[6];
															gdashchieve = achdata[7];
															burnchieve = achdata[8];
															monsterchieve = achdata[10];
															gemchieve = achdata[11];
															pongchieve = achdata[12];
														}
													}
													if (arpos == 2) {
														hrt_SetOBJXY(5, 25, 58);
														if (keyDown(KEY_A)) {
															g2 = g;
															gcd2 = gcd;
															fl2 = fl;
															lv2 = level;
															ea2 = ed;
															level = hrt_LoadByte(0x0B);
															g = hrt_LoadByte(0x0C);
															gcd = hrt_LoadByte(0x0D);
															fl = hrt_LoadByte(0x0E);
															ed = hrt_LoadByte(0x0F);
															if (level == 0) {
																level = lv2;
																fl = fl2;
																gcd = gcd2;
																g = g2;
																ed = ea2;
															}
															if (!(level == 0)) {
																i = 0;
																achdata[i] = hrt_LoadByte(0x38);
																i++;
																achdata[i] = hrt_LoadByte(0x39);
																i++;
																achdata[i] = hrt_LoadByte(0x3a);
																i++;
																achdata[i] = hrt_LoadByte(0x3b);
																i++;
																achdata[i] = hrt_LoadByte(0x3c);
																i++;
																achdata[i] = hrt_LoadByte(0x3d);
																i++;
																achdata[i] = hrt_LoadByte(0x3e);
																i++;
																achdata[i] = hrt_LoadByte(0x3f);
																i++;
																achdata[i] = hrt_LoadByte(0x40);
																i++;
																achdata[i] = hrt_LoadByte(0x41);
																i++;
																achdata[i] = hrt_LoadByte(0x42);
																i++;
																achdata[i] = hrt_LoadByte(0x43);
																i++;
																achdata[i] = hrt_LoadByte(0x44);
																i++;
																achdata[i] = hrt_LoadByte(0x45);
																i++;
																achdata[i] = hrt_LoadByte(0x46);
																i++;
																achdata[i] = hrt_LoadByte(0x47);
																i++;
																achdata[i] = hrt_LoadByte(0x48);
																i++;
																achdata[i] = hrt_LoadByte(0x49);
																i++;
																achdata[i] = hrt_LoadByte(0x4a);
																i++;
																achdata[i] = hrt_LoadByte(0x4b);
																deathchieve = achdata[3];
																jumpchieve = achdata[4];
																pookachieve = achdata[6];
																gdashchieve = achdata[7];
																burnchieve = achdata[8];
																monsterchieve = achdata[10];
																gemchieve = achdata[11];
																pongchieve = achdata[12];
																varreset();
															}
														}
													}
													hrt_CopyOAM();
												}
											}
										}
										if (arpos == 2) { //Erase
											hrt_SetOBJXY(5, 173, 112);
											if (keyDown(KEY_A)) {
												hrt_VblankIntrWait();
												hrt_SetOBJPalEntry(notificationcolor, hrt_GetOBJPalEntry(notificationcolor) + 5); //Color Changing text
												arpos = 0;
												hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
												for (i = 0; i < 17; i++) {
													hrt_SetFXLevel(i);
													hrt_SleepF(1);
												}
												hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "erase.img.lz", NULL), (u32)VRAM);
												hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "erase.pal.lz", NULL), (u32)BGPaletteMem);
												hrt_SetOBJXY(5, 25, 32);
												hrt_CopyOAM();
												hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
												for (i = 0; i < 17; i++) {
													hrt_SetFXLevel(16 - i);
													hrt_SleepF(1);
												}
												hrt_SetDSPMode(4, //Mode
													0,								  //CGB Mode
													0,								  //Frame Select
													0,                               //Unlocked HBlank
													1,                               //Linear OBJ Tile Mapping
													0,                               //Force Blank
													0,                               //BG 0
													0,                               //BG 1
													1,                               //BG 2
													0,                               //BG 3
													1,                               //OBJ
													0,                               //Win 0
													0,                               //Win 1
													0);							  //OBJWin
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
														hrt_SetOBJXY(5, 25, 32);
														if (keyDown(KEY_A)) {
															for (i = 0; i != 16; i++) {
																hrt_Memcpy(&SRAM[0x01], (u8*)0x02001000 + 0xffff, 5);
																hrt_Memcpy(&SRAM[0x10], (u8*)0x02001000 + 0xffff, 20);
															}

															//FLASH PATCH
															copyToFlash();
														}
													}
													if (arpos == 1) {
														hrt_SetOBJXY(5, 25, 45);
														if (keyDown(KEY_A)) {
															for (i = 0; i != 16; i++) {
																hrt_Memcpy(&SRAM[0x06], (u8*)0x02001000, 5);
																hrt_Memcpy(&SRAM[0x24], (u8*)0x02001000, 20);
                                                            }
                                                            //FLASH PATCH
                                                            copyToFlash();
														}
													}
													if (arpos == 2) {
														hrt_SetOBJXY(5, 25, 58);
														if (keyDown(KEY_A)) {
															hrt_Memcpy(&SRAM[0x0B], (u8*)0x02001000, 5);
															hrt_Memcpy(&SRAM[0x38], (u8*)0x02001000, 20);
                                                            //FLASH PATCH
                                                            copyToFlash();
                                                        }
													}
													hrt_CopyOAM(); //Copies OBJ Attrib
												}
											}
										}
										hrt_CopyOAM(); //Copies OBJ Attrib
									}
								}
								if (arpos == 0)
								{
									unpause = 1;
								}
							}
                        }
                        hrt_SetDSPMode(4, //Mode
                                       0,								  //CGB Mode
                                       0,								  //Frame Select
                                       0,                               //Unlocked HBlank
                                       0,                               //Linear OBJ Tile Mapping
                                       0,                               //Force Blank
                                       0,                               //BG 0
                                       0,                               //BG 1
                                       1,                               //BG 2
                                       0,                               //BG 3
                                       0,                               //OBJ
                                       0,                               //Win 0
                                       0,                               //Win 1
                                       0);							  //OBJWin
                        hrt_CreateOBJ(4,   //Sprite ID
                                      240,							     //Start X
                                      160,							     //Start Y
                                      3,							     //Size
                                      0,							     //Affine
                                      0,							     //Horizontal Flip
                                      0,							     //Vertical Flip
                                      1,							     //Shape
                                      0,							     //Double Size
                                      0,							     //Mosaic
                                      0,							     //Palette (16-Color only)
                                      1,							     //Color setting
                                      0,							     //Mode
                                      0,								 //Priority
                                      28);							 //Offset
                        hrt_CreateOBJ(1,   //Sprite ID
                                      240,							     //Start X
                                      160,							     //Start Y
                                      2,							     //Size
                                      0,							     //Affine
                                      0,							     //Horizontal Flip
                                      0,							     //Vertical Flip
                                      0,							     //Shape
                                      0,							     //Double Size
                                      0,							     //Mosaic
                                      0,							     //Palette (16-Color only)
                                      1,							     //Color setting
                                      0,							     //Mode
                                      0,								 //Priority
                                      0);							 //Offset
                        hrt_CreateOBJ(2,   //Sprite ID
                                      240,							     //Start X
                                      160,							     //Start Y
                                      0,							     //Size
                                      0,							     //Affine
                                      0,							     //Horizontal Flip
                                      0,							     //Vertical Flip
                                      0,							     //Shape
                                      0,							     //Double Size
                                      0,							     //Mosaic
                                      0,							     //Palette (16-Color only)
                                      1,							     //Color setting
                                      0,							     //Mode
                                      0,								 //Priority
                                      48);							 //Offset
                        hrt_CreateOBJ(3,   //Sprite ID
                                      240,							     //Start X
                                      160,							     //Start Y
                                      2,							     //Size
                                      0,							     //Affine
                                      0,							     //Horizontal Flip
                                      0,							     //Vertical Flip
                                      1,							     //Shape
                                      0,							     //Double Size
                                      0,							     //Mosaic
                                      0,							     //Palette (16-Color only)
                                      1,							     //Color setting
                                      0,							     //Mode
                                      0,								 //Priority
                                      32);							 //Offset
                        hrt_CreateOBJ(4,   //Sprite ID
                                      240,							     //Start X
                                      160,							     //Start Y
                                      3,							     //Size
                                      0,							     //Affine
                                      0,							     //Horizontal Flip
                                      0,							     //Vertical Flip
                                      1,							     //Shape
                                      0,							     //Double Size
                                      0,							     //Mosaic
                                      0,							     //Palette (16-Color only)
                                      1,							     //Color setting
                                      0,							     //Mode
                                      0,								 //Priority
                                      280);							 //Offset
                        hrt_CreateOBJ(5,   //Sprite ID
                                      240,							     //Start X
                                      160,							     //Start Y
                                      0,							     //Size
                                      0,							     //Affine
                                      0,							     //Horizontal Flip
                                      0,							     //Vertical Flip
                                      0,							     //Shape
                                      0,							     //Double Size
                                      0,							     //Mosaic
                                      0,							     //Palette (16-Color only)
                                      1,							     //Color setting
                                      0,							     //Mode
                                      0,								 //Priority
                                      s5o);							 //Offset
                        hrt_CreateOBJ(6,   //Sprite ID
                                      240,							     //Start X
                                      160,							     //Start Y
                                      0,							     //Size
                                      0,							     //Affine
                                      0,							     //Horizontal Flip
                                      0,							     //Vertical Flip
                                      0,							     //Shape
                                      0,							     //Double Size
                                      0,							     //Mosaic
                                      0,							     //Palette (16-Color only)
                                      1,							     //Color setting
                                      0,							     //Mode
                                      0,								 //Priority
                                      s6o);							 //Offset
                        hrt_SetOBJXY(4, 0, 152);
                        hrt_SetFXMode(1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0);
                        for (i = 0; i < 17; i++) {
                            hrt_SetFXLevel(i);
                            hrt_SleepF(1);
                        }
                        pause2 = 1;
                        levels();
			unpause = 0;
                        pause2 = 0; //Exits Pause
                        if (level == 103) {
                            if (fl == 1) {
                                hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "l103b.img.lz", NULL), (u32)VRAM);
                            }
                        }
                        else if (level == 85) {
                            if (gcd == 1) {
                                hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "l85b.lz", NULL), (u32)VRAM);
                            }
                        }
                        else if (level == LEVEL_MAX) {
                            if (end == 1) {
                                hrt_LZ77UnCompVRAM((u32)gbfs_get_obj(dat, "ende.lz", NULL), (u32)VRAM);
                            }
                        }
                        hrt_CopyOAM();
                        hrt_SetDSPMode(3, //Mode
                                       0,								  //CGB Mode
                                       0,								  //Frame Select
                                       0,                               //Unlocked HBlank
                                       1,                               //Linear OBJ Tile Mapping
                                       0,                               //Force Blank
                                       0,                               //BG 0
                                       0,                               //BG 1
                                       1,                               //BG 2
                                       0,                               //BG 3
                                       1,                               //OBJ
                                       0,                               //Win 0
                                       0,                               //Win 1
                                       0);							  //OBJWin
                        hrt_SetOBJXY(4, 0, 152); //Version pos
                        hrt_SetOBJXY(2, 223, 128); //Goal Pos
                        hrt_SetOBJXY(5, 240, 160); //Spr5 Offscreen
                        hrt_SetOBJXY(6, 240, 160); //Spr6 Offscreen
						if (achiup == 1)
						{
							hrt_SetOBJXY(7, 0, 0);
						}
                        hrt_SetFXMode(1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0);
                        for (i = 0; i < 17; i++) {
                            hrt_SetFXLevel(16 - i);
                            hrt_SleepF(1);
                        }
                        musici = 0;
						musicno = hrt_CreateRNG() % 7;
			switch(musicno)
			{
				case 0:
				    music = mmEffectEx(&bgm);
					break;
				case 1:
					mmStart(MOD_SONG2, MM_PLAY_LOOP);
					break; 
				case 2:
					mmStart(MOD_SONG3, MM_PLAY_LOOP);
					break;
				case 3:
					mmStart(MOD_SONG4, MM_PLAY_LOOP);
					break;
				case 4:
					mmStart(MOD_SONG5, MM_PLAY_LOOP);
					break;
				case 5:
					mmStart(MOD_SONG6, MM_PLAY_LOOP);
					break;
				case 6:
					mmStart(MOD_SONG7, MM_PLAY_LOOP);
					break;
			}
						gci = 0;
						pi = 0;
                    }
                }
            }
        }
    }
    return 0;
}

void vblfunc()
{
	mmFrame();
	if ((keyDown(KEY_A))AND(keyDown(KEY_B))AND(keyDown(KEY_SELECT))AND(keyDown(KEY_START))) {
		asm volatile("swi 0x00"::);
	}
}
