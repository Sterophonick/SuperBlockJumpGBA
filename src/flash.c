typedef unsigned long u32;
typedef unsigned short u16;
typedef unsigned char u8;

#include "../inc/flash.h" //batteryless patch

u32 total_rom_size = 0;
u32 flash_size = 0;
u32 flash_sram_area = (u32 *)(0x85B8D80); //hardcode flash space to 6MB offset
u8 flash_type = 0;

#define REG_IE (*(volatile u16*)0x4000200)

__attribute__((section(".ewram")))
u32 get_flash_type() {
    u32 rom_data, data;
    u16 ie = REG_IE;
    //stop_dma_interrupts();
    REG_IE = ie & 0xFFFE;

    rom_data = *(u32 *)AGB_ROM;

    // Type 1 or 4
    _FLASH_WRITE(0, 0xFF);
    _FLASH_WRITE(0, 0x90);
    data = *(u32 *)AGB_ROM;
    _FLASH_WRITE(0, 0xFF);
    if (rom_data != data) {
        // Check if the chip is responding to this command
        // which then needs a different write command later
        _FLASH_WRITE(0x59, 0x42);
        data = *(u8 *)(AGB_ROM+0xB2);
        _FLASH_WRITE(0x59, 0x96);
        _FLASH_WRITE(0, 0xFF);
        if (data != 0x96) {
            REG_IE = ie;
            //resume_interrupts();
            return 4;
        }
        REG_IE = ie;
        //resume_interrupts();
        return 1;
    }

    // Type 2
    _FLASH_WRITE(0, 0xF0);
    _FLASH_WRITE(0xAAA, 0xA9);
    _FLASH_WRITE(0x555, 0x56);
    _FLASH_WRITE(0xAAA, 0x90);
    data = *(u32 *)AGB_ROM;
    _FLASH_WRITE(0, 0xF0);
    if (rom_data != data) {
        REG_IE = ie;
        //resume_interrupts();
        return 2;
    }

    // Type 3
    _FLASH_WRITE(0, 0xF0);
    _FLASH_WRITE(0xAAA, 0xAA);
    _FLASH_WRITE(0x555, 0x55);
    _FLASH_WRITE(0xAAA, 0x90);
    data = *(u32 *)AGB_ROM;
    _FLASH_WRITE(0, 0xF0);
    if (rom_data != data) {
        REG_IE = ie;
        //resume_interrupts();
        return 3;
    }

    REG_IE = ie;
    //resume_interrupts();
    return 0;
}

// This function will issue a flash sector erase
// operation at the given sector address and then
// write 64 kilobytes of SRAM data to Flash ROM.
// Must run in EWRAM because ROM data is
// not visible to the system while erasing/writing.
__attribute__((section(".ewram")))
void flash_write(u8 flash_type, u32 sa)
{
    if (flash_type == 0) return;
    u16 ie = REG_IE;
    //stop_dma_interrupts();
    REG_IE = ie & 0xFFFE;

    if (flash_type == 1) {
        // Erase flash sector
        _FLASH_WRITE(sa, 0xFF);
        _FLASH_WRITE(sa, 0x60);
        _FLASH_WRITE(sa, 0xD0);
        _FLASH_WRITE(sa, 0x20);
        _FLASH_WRITE(sa, 0xD0);
        while (1) {
            __asm("nop");
            if (*(((u16 *)AGB_ROM)+(sa/2)) == 0x80) {
                break;
            }
        }
        _FLASH_WRITE(sa, 0xFF);

        // Write data
        for (int i=0; i<AGB_SRAM_SIZE; i+=2) {
            _FLASH_WRITE(sa+i, 0x40);
            _FLASH_WRITE(sa+i, (*(u8 *)(AGB_SRAM+i+1)) << 8 | (*(u8 *)(AGB_SRAM+i)));
            while (1) {
                __asm("nop");
                if (*(((u16 *)AGB_ROM)+(sa/2)) == 0x80) {
                    break;
                }
            }
        }
        _FLASH_WRITE(sa, 0xFF);

    } else if (flash_type == 2) {
        // Erase flash sector
        _FLASH_WRITE(sa, 0xF0);
        _FLASH_WRITE(0xAAA, 0xA9);
        _FLASH_WRITE(0x555, 0x56);
        _FLASH_WRITE(0xAAA, 0x80);
        _FLASH_WRITE(0xAAA, 0xA9);
        _FLASH_WRITE(0x555, 0x56);
        _FLASH_WRITE(sa, 0x30);
        while (1) {
            __asm("nop");
            if (*(((u16 *)AGB_ROM)+(sa/2)) == 0xFFFF) {
                break;
            }
        }
        _FLASH_WRITE(sa, 0xF0);

        // Write data
        for (int i=0; i<AGB_SRAM_SIZE; i+=2) {
            _FLASH_WRITE(0xAAA, 0xA9);
            _FLASH_WRITE(0x555, 0x56);
            _FLASH_WRITE(0xAAA, 0xA0);
            _FLASH_WRITE(sa+i, (*(u8 *)(AGB_SRAM+i+1)) << 8 | (*(u8 *)(AGB_SRAM+i)));
            while (1) {
                __asm("nop");
                if (*(((u16 *)AGB_ROM)+((sa+i)/2)) == ((*(u8 *)(AGB_SRAM+i+1)) << 8 | (*(u8 *)(AGB_SRAM+i)))) {
                    break;
                }
            }
        }
        _FLASH_WRITE(sa, 0xF0);

    } else if (flash_type == 3) {
        // Erase flash sector
        _FLASH_WRITE(sa, 0xF0);
        _FLASH_WRITE(0xAAA, 0xAA);
        _FLASH_WRITE(0x555, 0x55);
        _FLASH_WRITE(0xAAA, 0x80);
        _FLASH_WRITE(0xAAA, 0xAA);
        _FLASH_WRITE(0x555, 0x55);
        _FLASH_WRITE(sa, 0x30);
        while (1) {
            __asm("nop");
            if (*(((u16 *)AGB_ROM)+(sa/2)) == 0xFFFF) {
                break;
            }
        }
        _FLASH_WRITE(sa, 0xF0);

        // Write data
        for (int i=0; i<AGB_SRAM_SIZE; i+=2) {
            _FLASH_WRITE(0xAAA, 0xAA);
            _FLASH_WRITE(0x555, 0x55);
            _FLASH_WRITE(0xAAA, 0xA0);
            _FLASH_WRITE(sa+i, (*(u8 *)(AGB_SRAM+i+1)) << 8 | (*(u8 *)(AGB_SRAM+i)));
            while (1) {
                __asm("nop");
                if (*(((u16 *)AGB_ROM)+((sa+i)/2)) == ((*(u8 *)(AGB_SRAM+i+1)) << 8 | (*(u8 *)(AGB_SRAM+i)))) {
                    break;
                }
            }
        }
        _FLASH_WRITE(sa, 0xF0);

    } else if (flash_type == 4) {
        // Erase flash sector
        _FLASH_WRITE(sa, 0xFF);
        _FLASH_WRITE(sa, 0x60);
        _FLASH_WRITE(sa, 0xD0);
        _FLASH_WRITE(sa, 0x20);
        _FLASH_WRITE(sa, 0xD0);
        while (1) {
            __asm("nop");
            if ((*(((u16 *)AGB_ROM)+(sa/2)) & 0x80) == 0x80) {
                break;
            }
        }
        _FLASH_WRITE(sa, 0xFF);

        // Write data
        int c = 0;
        while (c < AGB_SRAM_SIZE) {
            _FLASH_WRITE(sa+c, 0xEA);
            while (1) {
                __asm("nop");
                if ((*(((u16 *)AGB_ROM)+((sa+c)/2)) & 0x80) == 0x80) {
                    break;
                }
            }
            _FLASH_WRITE(sa+c, 0x1FF);
            for (int i=0; i<1024; i+=2) {
                _FLASH_WRITE(sa+c+i, (*(u8 *)(AGB_SRAM+c+i+1)) << 8 | (*(u8 *)(AGB_SRAM+c+i)));
            }
            _FLASH_WRITE(sa+c, 0xD0);
            while (1) {
                __asm("nop");
                if ((*(((u16 *)AGB_ROM)+((sa+c)/2)) & 0x80) == 0x80) {
                    break;
                }
            }
            _FLASH_WRITE(sa+c, 0xFF);
            c += 1024;
        }
    }

    REG_IE = ie;
    //resume_interrupts();
}

void save_sram_FLASH()
{
    if (flash_type == 0) return;
    flash_write(flash_type, flash_sram_area);
}

void flash_entrypoint()
{
    flash_type = get_flash_type();
}
