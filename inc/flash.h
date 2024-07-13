#define EWRAM_CODE	__attribute__((section(".ewram"), long_call))

#define AGB_ROM  ((u8*)0x8000000)
#define AGB_SRAM ((u8*)0xE000000)
#define AGB_SRAM_SIZE 1*1024 //all we need is 1k idc about anything else
#define _FLASH_WRITE(pa, pd) { *(((u16 *)AGB_ROM)+((pa)/2)) = pd; __asm("nop"); }
extern u8 flash_type;
extern EWRAM_CODE u32 get_flash_type();
extern EWRAM_CODE void flash_write(u8 flash_type, u32 sa);
extern void save_sram_FLASH();

extern u32 total_rom_size;
extern u32 flash_size;
extern u32* flash_sram_area; //hardcode flash space to 6MB offset
extern EWRAM_CODE void flash_entrypoint();

extern void bytecopy(u8 *dst,u8 *src,int count);
