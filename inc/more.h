char achdata[] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

const char achdatax[] = {
	10,10,10,10,10,10,10,10,108,108,108,108,108,108,108,108,108,108,108,186
};

const char achdatay[] = {
	20,33,46,59,72,85,98,111,20,33,46,59,72,85,98,111,124,137,150,20
};
void achievement(int id)
{
	achdata[id] = 1;
	MoveSprite(&sprites[50], 232, 152);
	unreadchieves = 1;
}

// UnCompress LZ77 Data to WRAM
void LZ77UnCompWRAM(unsigned long source, unsigned long dest) {
asm("mov r0, %0\n"
"mov r1, %1\n"
"swi 0x11\n"
:
:"r" (source), "r" (dest)
:"r0", "r1" );
}


// UnCompress LZ77 Data to VRAM
void LZ77UnCompVRAM(unsigned long source, unsigned long dest) {
asm("mov r0, %0\n"
"mov r1, %1\n"
"swi 0x12\n"
:
:"r" (source), "r" (dest)
:"r0", "r1" );
}
void varreset()
{
	bx = 8;
	by = 108;
	x = 0;
	y = 0;
	gravity = 0;
	restart = 0;
}

int BlockTouchingColor(u16* color)
{
	if ((GetPixel3(bx + 1, by + 24 + y) == color)OR(GetPixel3(bx + 1, by + 22 + y) == color)OR(GetPixel3(bx + 2, by + 24 + y) == color)OR(GetPixel3(bx + 2, by + 23 + y) == color)OR(GetPixel3(bx + 3, by + 24 + y) == color)OR(GetPixel3(bx + 3, by + 23 + y) == color)OR(GetPixel3(bx + 3, by + 22 + y) == color)OR(GetPixel3(bx + 4, by + 24 + y) == color)OR(GetPixel3(bx + 4, by + 23 + y) == color)OR(GetPixel3(bx + 4, by + 22 + y) == color)OR(GetPixel3(bx + 5, by + 24 + y) == color)OR(GetPixel3(bx + 5, by + 23 + y) == color)OR(GetPixel3(bx + 5, by + 22 + y) == color)OR(GetPixel3(bx + 6, by + 24 + y) == color)OR(GetPixel3(bx + 6, by + 23 + y) == color)OR(GetPixel3(bx + 6, by + 22 + y) == color)OR(GetPixel3(bx + 7, by + 24 + y) == color)OR(GetPixel3(bx + 7, by + 23 + y) == color)OR(GetPixel3(bx + 7, by + 22 + y) == color)OR(GetPixel3(bx + 8, by + 24 + y) == color)OR(GetPixel3(bx + 8, by + 23 + y) == color)OR(GetPixel3(bx + 8, by + 22 + y) == color)OR(GetPixel3(bx + 9, by + 24 + y) == color)OR(GetPixel3(bx + 9, by + 23 + y) == color)OR(GetPixel3(bx + 9, by + 22 + y) == color)OR(GetPixel3(bx + 10, by + 24 + y) == color)OR(GetPixel3(bx + 10, by + 23 + y) == color)OR(GetPixel3(bx + 10, by + 22 + y) == color)OR(GetPixel3(bx + 11, by + 24 + y) == color)OR(GetPixel3(bx + 12, by + 23 + y) == color)OR(GetPixel3(bx + 12, by + 22 + y) == color)OR(GetPixel3(bx + 13, by + 24 + y) == color)OR(GetPixel3(bx + 13, by + 23 + y) == color)OR(GetPixel3(bx + 13, by + 22 + y) == color)OR(GetPixel3(bx + 14, by + 24 + y) == color)OR(GetPixel3(bx + 14, by + 23 + y) == color)OR(GetPixel3(bx + 14, by + 22 + y) == color)OR(GetPixel3(bx + 15, by + 24 + y) == color)OR(GetPixel3(bx + 16, by + 23 + y) == color)OR(GetPixel3(bx + 17, by + 22 + y) == color)OR(GetPixel3(bx + 18, by + 24 + y) == color)OR(GetPixel3(bx + 19, by + 23 + y) == color)OR(GetPixel3(bx + 20, by + 22 + y) == color))
	{
		return 1;
	}
	else if ((GetPixel3(bx + 24 + x, by + 22) == color)OR(GetPixel3(bx + 24 + x, by + 21) == color)OR(GetPixel3(bx + 24 + x, by + 20) == color)OR(GetPixel3(bx + 24 + x, by + 19) == color)OR(GetPixel3(bx + 24 + x, by + 18) == color)OR(GetPixel3(bx + 24 + x, by + 17) == color)OR(GetPixel3(bx + 24 + x, by + 16) == color)OR(GetPixel3(bx + 24 + x, by + 15) == color)OR(GetPixel3(bx + 24 + x, by + 14) == color)OR(GetPixel3(bx + 24 + x, by + 13) == color)OR(GetPixel3(bx + 24 + x, by + 12) == color)OR(GetPixel3(bx + 24 + x, by + 11) == color)OR(GetPixel3(bx + 24 + x, by + 10) == color)OR(GetPixel3(bx + 24 + x, by + 9) == color)OR(GetPixel3(bx + 24 + x, by + 8) == color)OR(GetPixel3(bx + 24 + x, by + 7) == color)OR(GetPixel3(bx + 24 + x, by + 6) == color)OR(GetPixel3(bx + 24 + x, by + 5) == color)OR(GetPixel3(bx + 24 + x, by + 4) == color)OR(GetPixel3(bx + 24 + x, by + 3) == color)OR(GetPixel3(bx + 24 + x, by + 2) == color)OR(GetPixel3(bx + 24 + x, by + 1) == color)OR(GetPixel3(bx + 23 + x, by + 22) == color)OR(GetPixel3(bx + 23 + x, by + 21) == color)OR(GetPixel3(bx + 23 + x, by + 20) == color)OR(GetPixel3(bx + 23 + x, by + 19) == color)OR(GetPixel3(bx + 23 + x, by + 18) == color)OR(GetPixel3(bx + 23 + x, by + 17) == color)OR(GetPixel3(bx + 23 + x, by + 16) == color)OR(GetPixel3(bx + 23 + x, by + 15) == color)OR(GetPixel3(bx + 23 + x, by + 14) == color)OR(GetPixel3(bx + 23 + x, by + 13) == color)OR(GetPixel3(bx + 23 + x, by + 12) == color)OR(GetPixel3(bx + 23 + x, by + 11) == color)OR(GetPixel3(bx + 23 + x, by + 10) == color)OR(GetPixel3(bx + 23 + x, by + 9) == color)OR(GetPixel3(bx + 23 + x, by + 8) == color)OR(GetPixel3(bx + 23 + x, by + 7) == color)OR(GetPixel3(bx + 23 + x, by + 6) == color)OR(GetPixel3(bx + 23 + x, by + 5) == color)OR(GetPixel3(bx + 23 + x, by + 4) == color)OR(GetPixel3(bx + 23 + x, by + 3) == color)OR(GetPixel3(bx + 23 + x, by + 2) == color)OR(GetPixel3(bx + 23 + x, by + 1) == color))
	{
		return 1;
	}
	else if ((GetPixel3(bx + x, by + 22) == color)OR(GetPixel3(bx + x, by + 21) == color)OR(GetPixel3(bx + x, by + 20) == color)OR(GetPixel3(bx + x, by + 19) == color)OR(GetPixel3(bx + x, by + 18) == color)OR(GetPixel3(bx + x, by + 17) == color)OR(GetPixel3(bx + x, by + 16) == color)OR(GetPixel3(bx + x, by + 15) == color)OR(GetPixel3(bx + x, by + 14) == color)OR(GetPixel3(bx + x, by + 13) == color)OR(GetPixel3(bx + x, by + 12) == color)OR(GetPixel3(bx + x, by + 11) == color)OR(GetPixel3(bx + x, by + 10) == color)OR(GetPixel3(bx + x, by + 9) == color)OR(GetPixel3(bx + x, by + 8) == color)OR(GetPixel3(bx + x, by + 7) == color)OR(GetPixel3(bx + x, by + 6) == color)OR(GetPixel3(bx + x, by + 5) == color)OR(GetPixel3(bx + x, by + 4) == color)OR(GetPixel3(bx + x, by + 3) == color)OR(GetPixel3(bx + x, by + 2) == color)OR(GetPixel3(bx + x, by + 1) == color)OR(GetPixel3(bx + 1 + x, by + 22) == color)OR(GetPixel3(bx + 1 + x, by + 21) == color)OR(GetPixel3(bx + 1 + x, by + 20) == color)OR(GetPixel3(bx + 1 + x, by + 19) == color)OR(GetPixel3(bx + 1 + x, by + 18) == color)OR(GetPixel3(bx + 1 + x, by + 17) == color)OR(GetPixel3(bx + 1 + x, by + 16) == color)OR(GetPixel3(bx + 1 + x, by + 15) == color)OR(GetPixel3(bx + 1 + x, by + 14) == color)OR(GetPixel3(bx + 1 + x, by + 13) == color)OR(GetPixel3(bx + 1 + x, by + 12) == color)OR(GetPixel3(bx + 1 + x, by + 11) == color)OR(GetPixel3(bx + 1 + x, by + 10) == color)OR(GetPixel3(bx + 1 + x, by + 9) == color)OR(GetPixel3(bx + 1 + x, by + 8) == color)OR(GetPixel3(bx + 1 + x, by + 7) == color)OR(GetPixel3(bx + 1 + x, by + 6) == color)OR(GetPixel3(bx + 1 + x, by + 5) == color)OR(GetPixel3(bx + 1 + x, by + 4) == color)OR(GetPixel3(bx + 1 + x, by + 3) == color)OR(GetPixel3(bx + 1 + x, by + 2) == color)OR(GetPixel3(bx + 1 + x, by + 1) == color)OR(GetPixel3(bx + 2 + x, by + 22) == color)OR(GetPixel3(bx + 2 + x, by + 21) == color)OR(GetPixel3(bx + 2 + x, by + 20) == color)OR(GetPixel3(bx + 2 + x, by + 19) == color)OR(GetPixel3(bx + 2 + x, by + 18) == color)OR(GetPixel3(bx + 2 + x, by + 17) == color)OR(GetPixel3(bx + 2 + x, by + 16) == color)OR(GetPixel3(bx + 2 + x, by + 15) == color)OR(GetPixel3(bx + 2 + x, by + 14) == color)OR(GetPixel3(bx + 2 + x, by + 13) == color)OR(GetPixel3(bx + 2 + x, by + 12) == color)OR(GetPixel3(bx + 2 + x, by + 11) == color)OR(GetPixel3(bx + 2 + x, by + 10) == color)OR(GetPixel3(bx + 2 + x, by + 9) == color)OR(GetPixel3(bx + 2 + x, by + 8) == color)OR(GetPixel3(bx + 2 + x, by + 7) == color)OR(GetPixel3(bx + 2 + x, by + 6) == color)OR(GetPixel3(bx + 2 + x, by + 5) == color)OR(GetPixel3(bx + 2 + x, by + 4) == color)OR(GetPixel3(bx + 2 + x, by + 3) == color)OR(GetPixel3(bx + 2 + x, by + 2) == color)OR(GetPixel3(bx + 2 + x, by + 1) == color))
	{
		return 1;
	}
	else if ((GetPixel3(bx + 1, by) == color)OR(GetPixel3(bx + 2, by) == color)OR(GetPixel3(bx + 3, by) == color)OR(GetPixel3(bx + 4, by) == color)OR(GetPixel3(bx + 5, by) == color)OR(GetPixel3(bx + 6, by) == color)OR(GetPixel3(bx + 7, by) == color)OR(GetPixel3(bx + 8, by) == color)OR(GetPixel3(bx + 9, by) == color)OR(GetPixel3(bx + 10, by) == color)OR(GetPixel3(bx + 11, by) == color)OR(GetPixel3(bx + 12, by) == color)OR(GetPixel3(bx + 13, by) == color)OR(GetPixel3(bx + 14, by + 9) == color)OR(GetPixel3(bx + 15, by + 8) == color)OR(GetPixel3(bx + 16, by + 7) == color)OR(GetPixel3(bx + 17, by + 6) == color)OR(GetPixel3(bx + 18, by) == color)OR(GetPixel3(bx + 19, by) == color)OR(GetPixel3(bx + 20, by) == color)OR(GetPixel3(bx + 21, by) == color)OR(GetPixel3(bx + 22, by) == color)OR(GetPixel3(bx + 23, by) == color))
	{
		return 1;
	}
	else {
		return 0;
	}
}

void bottomcol()
{
	if ((GetPixel3(bx + 1, by + 24 + y) == 0x64c0)OR(GetPixel3(bx + 1, by + 22 + y) == 0x64c0)OR(GetPixel3(bx + 2, by + 24 + y) == 0x64c0)OR(GetPixel3(bx + 2, by + 23 + y) == 0x64c0)OR(GetPixel3(bx + 3, by + 24 + y) == 0x64c0)OR(GetPixel3(bx + 3, by + 23 + y) == 0x64c0)OR(GetPixel3(bx + 3, by + 22 + y) == 0x64c0)OR(GetPixel3(bx + 4, by + 24 + y) == 0x64c0)OR(GetPixel3(bx + 4, by + 23 + y) == 0x64c0)OR(GetPixel3(bx + 4, by + 22 + y) == 0x64c0)OR(GetPixel3(bx + 5, by + 24 + y) == 0x64c0)OR(GetPixel3(bx + 5, by + 23 + y) == 0x64c0)OR(GetPixel3(bx + 5, by + 22 + y) == 0x64c0)OR(GetPixel3(bx + 6, by + 24 + y) == 0x64c0)OR(GetPixel3(bx + 6, by + 23 + y) == 0x64c0)OR(GetPixel3(bx + 6, by + 22 + y) == 0x64c0)OR(GetPixel3(bx + 7, by + 24 + y) == 0x64c0)OR(GetPixel3(bx + 7, by + 23 + y) == 0x64c0)OR(GetPixel3(bx + 7, by + 22 + y) == 0x64c0)OR(GetPixel3(bx + 8, by + 24 + y) == 0x64c0)OR(GetPixel3(bx + 8, by + 23 + y) == 0x64c0)OR(GetPixel3(bx + 8, by + 22 + y) == 0x64c0)OR(GetPixel3(bx + 9, by + 24 + y) == 0x64c0)OR(GetPixel3(bx + 9, by + 23 + y) == 0x64c0)OR(GetPixel3(bx + 9, by + 22 + y) == 0x64c0)OR(GetPixel3(bx + 10, by + 24 + y) == 0x64c0)OR(GetPixel3(bx + 10, by + 23 + y) == 0x64c0)OR(GetPixel3(bx + 10, by + 22 + y) == 0x64c0)OR(GetPixel3(bx + 11, by + 24 + y) == 0x64c0)OR(GetPixel3(bx + 12, by + 23 + y) == 0x64c0)OR(GetPixel3(bx + 12, by + 22 + y) == 0x64c0)OR(GetPixel3(bx + 13, by + 24 + y) == 0x64c0)OR(GetPixel3(bx + 13, by + 23 + y) == 0x64c0)OR(GetPixel3(bx + 13, by + 22 + y) == 0x64c0)OR(GetPixel3(bx + 14, by + 24 + y) == 0x64c0)OR(GetPixel3(bx + 14, by + 23 + y) == 0x64c0)OR(GetPixel3(bx + 14, by + 22 + y) == 0x64c0)OR(GetPixel3(bx + 15, by + 24 + y) == 0x64c0)OR(GetPixel3(bx + 16, by + 23 + y) == 0x64c0)OR(GetPixel3(bx + 17, by + 22 + y) == 0x64c0)OR(GetPixel3(bx + 18, by + 24 + y) == 0x64c0)OR(GetPixel3(bx + 19, by + 23 + y) == 0x64c0)OR(GetPixel3(bx + 20, by + 22 + y) == 0x64c0)OR((GetPixel3(bx, by + 24) == 0x64c0))OR(GetPixel3(bx + 24, by + 24) == 0x64c0)OR(GetPixel3(bx + 22, by + 24 + y) == 0x64c0)OR(GetPixel3(bx + 21, by + 23 + y) == 0x64c0))
	{
		by -= 1;
		y = 0;
		if ((keyDown(KEY_A))AND(gravity == 0))
		{
			y = -4.05;
				jumps++;
		}
	}
}

void rightcol()
{
	if ((GetPixel3(bx + 24 + x, by + 22) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 21) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 20) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 19) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 18) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 17) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 16) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 15) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 14) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 13) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 12) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 11) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 10) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 9) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 8) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 7) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 6) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 5) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 4) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 3) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 2) == 0x64c0)OR(GetPixel3(bx + 24 + x, by + 1) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 22) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 21) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 20) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 19) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 18) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 17) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 16) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 15) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 14) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 13) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 12) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 11) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 10) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 9) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 8) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 7) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 6) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 5) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 4) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 3) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 2) == 0x64c0)OR(GetPixel3(bx + 23 + x, by + 1) == 0x64c0))
	{
		if (keyDown(KEY_A))
		{
			if (gravity == 0)
			{
				y = -4.05;
			}
			else {
				y = 4.05;
			}
			x = -5;
				jumps++;
		}
		else
		{
			x = 0;
			bx -= 1;
		}
	}
}

void leftcol()
{
	if ((GetPixel3(bx + x, by + 22) == 0x64c0)OR(GetPixel3(bx + x, by + 21) == 0x64c0)OR(GetPixel3(bx + x, by + 20) == 0x64c0)OR(GetPixel3(bx + x, by + 19) == 0x64c0)OR(GetPixel3(bx + x, by + 18) == 0x64c0)OR(GetPixel3(bx + x, by + 17) == 0x64c0)OR(GetPixel3(bx + x, by + 16) == 0x64c0)OR(GetPixel3(bx + x, by + 15) == 0x64c0)OR(GetPixel3(bx + x, by + 14) == 0x64c0)OR(GetPixel3(bx + x, by + 13) == 0x64c0)OR(GetPixel3(bx + x, by + 12) == 0x64c0)OR(GetPixel3(bx + x, by + 11) == 0x64c0)OR(GetPixel3(bx + x, by + 10) == 0x64c0)OR(GetPixel3(bx + x, by + 9) == 0x64c0)OR(GetPixel3(bx + x, by + 8) == 0x64c0)OR(GetPixel3(bx + x, by + 7) == 0x64c0)OR(GetPixel3(bx + x, by + 6) == 0x64c0)OR(GetPixel3(bx + x, by + 5) == 0x64c0)OR(GetPixel3(bx + x, by + 4) == 0x64c0)OR(GetPixel3(bx + x, by + 3) == 0x64c0)OR(GetPixel3(bx + x, by + 2) == 0x64c0)OR(GetPixel3(bx + x, by + 1) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 22) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 21) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 20) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 19) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 18) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 17) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 16) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 15) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 14) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 13) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 12) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 11) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 10) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 9) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 8) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 7) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 6) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 5) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 4) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 3) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 2) == 0x64c0)OR(GetPixel3(bx + 1 + x, by + 1) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 22) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 21) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 20) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 19) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 18) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 17) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 16) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 15) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 14) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 13) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 12) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 11) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 10) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 9) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 8) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 7) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 6) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 5) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 4) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 3) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 2) == 0x64c0)OR(GetPixel3(bx + 2 + x, by + 1) == 0x64c0))
	{
		if (keyDown(KEY_A))
		{

			if (gravity == 0)
			{
				y = -4.05;
			}
			else {
				y = 4.05;
			}
			x = 5;
				jumps++;
		}
		else
		{
			x = 0;
			bx += 1;
		}
	}
}

void topcol()
{
	if ((GetPixel3(bx + 1, by + y) == 0x64c0)OR(GetPixel3(bx + 2, by + y) == 0x64c0)OR(GetPixel3(bx + 3, by + y) == 0x64c0)OR(GetPixel3(bx + 4, by + y) == 0x64c0)OR(GetPixel3(bx + 5, by + y) == 0x64c0)OR(GetPixel3(bx + 6, by + y) == 0x64c0)OR(GetPixel3(bx + 7, by + y) == 0x64c0)OR(GetPixel3(bx + 8, by + y) == 0x64c0)OR(GetPixel3(bx + 9, by + y) == 0x64c0)OR(GetPixel3(bx + 10, by + y) == 0x64c0)OR(GetPixel3(bx + 11, by + y) == 0x64c0)OR(GetPixel3(bx + 12, by + y) == 0x64c0)OR(GetPixel3(bx + 13, by + y) == 0x64c0)OR(GetPixel3(bx + 14, by + y + 9) == 0x64c0)OR(GetPixel3(bx + 15, by + y + 8) == 0x64c0)OR(GetPixel3(bx + 16, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 17, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 18, by + y) == 0x64c0)OR(GetPixel3(bx + 19, by + y) == 0x64c0)OR(GetPixel3(bx + 20, by + y) == 0x64c0)OR(GetPixel3(bx + 21, by + y) == 0x64c0)OR(GetPixel3(bx + 22, by + y) == 0x64c0)OR(GetPixel3(bx + 23, by + y) == 0x64c0))
	{
		if (gravity == 0)
		{
			by += 3;
			by -= y;
			y = 0;
			y += 0.24;
				jumps++;
			MoveSprite(&sprites[1], bx, by);
		}
		else {
			y = 0;
			by += 1;
			if ((GetPixel3(bx + 1, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 2, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 3, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 4, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 5, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 6, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 7, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 8, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 9, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 10, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 11, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 12, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 13, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 14, by + y + 1 + 9) == 0x64c0)OR(GetPixel3(bx + 15, by + y + 1 + 8) == 0x64c0)OR(GetPixel3(bx + 16, by + y + 1 + 7) == 0x64c0)OR(GetPixel3(bx + 17, by + y + 1 + 6) == 0x64c0)OR(GetPixel3(bx + 18, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 19, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 20, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 21, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 22, by + y + 1) == 0x64c0)OR(GetPixel3(bx + 23, by + y + 1) == 0x64c0))
			{
				y = 0;
				by += 1;
				if ((GetPixel3(bx + 1, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 2, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 3, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 4, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 5, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 6, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 7, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 8, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 9, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 10, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 11, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 12, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 13, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 14, by + y + 2 + 9) == 0x64c0)OR(GetPixel3(bx + 15, by + y + 2 + 8) == 0x64c0)OR(GetPixel3(bx + 16, by + y + 2 + 7) == 0x64c0)OR(GetPixel3(bx + 17, by + y + 2 + 6) == 0x64c0)OR(GetPixel3(bx + 18, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 19, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 20, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 21, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 22, by + y + 2) == 0x64c0)OR(GetPixel3(bx + 23, by + y + 2) == 0x64c0))
				{
					y = 0;
					by += 1;
					if ((GetPixel3(bx + 1, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 2, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 3, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 4, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 5, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 6, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 7, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 8, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 9, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 10, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 11, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 12, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 13, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 14, by + y + 3 + 9) == 0x64c0)OR(GetPixel3(bx + 15, by + y + 3 + 8) == 0x64c0)OR(GetPixel3(bx + 16, by + y + 3 + 7) == 0x64c0)OR(GetPixel3(bx + 17, by + y + 3 + 6) == 0x64c0)OR(GetPixel3(bx + 18, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 19, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 20, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 21, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 22, by + y + 3) == 0x64c0)OR(GetPixel3(bx + 23, by + y + 3) == 0x64c0))
					{
						y = 0;
						by += 1;
						if ((GetPixel3(bx + 1, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 2, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 3, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 4, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 5, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 6, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 7, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 8, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 9, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 10, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 11, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 12, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 13, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 14, by + y + 4 + 9) == 0x64c0)OR(GetPixel3(bx + 15, by + y + 4 + 8) == 0x64c0)OR(GetPixel3(bx + 16, by + y + 4 + 7) == 0x64c0)OR(GetPixel3(bx + 17, by + y + 4 + 6) == 0x64c0)OR(GetPixel3(bx + 18, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 19, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 20, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 21, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 22, by + y + 4) == 0x64c0)OR(GetPixel3(bx + 23, by + y + 4) == 0x64c0))
						{
							y = 0;
							by += 1;
							if ((GetPixel3(bx + 1, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 2, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 3, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 4, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 5, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 6, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 7, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 8, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 9, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 10, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 11, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 12, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 13, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 14, by + (y * 2) + 5 + 9) == 0x64c0)OR(GetPixel3(bx + 15, by + (y * 2) + 5 + 8) == 0x64c0)OR(GetPixel3(bx + 16, by + (y * 2) + 5 + 7) == 0x64c0)OR(GetPixel3(bx + 17, by + (y * 2) + 5 + 6) == 0x64c0)OR(GetPixel3(bx + 18, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 19, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 20, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 21, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 22, by + (y * 2) + 5) == 0x64c0)OR(GetPixel3(bx + 23, by + (y * 2) + 5) == 0x64c0))
							{
								y = 0;
								by += 1;
								if ((GetPixel3(bx + 1, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 2, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 3, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 4, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 5, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 6, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 7, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 8, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 9, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 10, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 11, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 12, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 13, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 14, by + y + 6 + 9) == 0x64c0)OR(GetPixel3(bx + 15, by + y + 6 + 8) == 0x64c0)OR(GetPixel3(bx + 16, by + y + 6 + 7) == 0x64c0)OR(GetPixel3(bx + 17, by + y + 6 + 6) == 0x64c0)OR(GetPixel3(bx + 18, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 19, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 20, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 21, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 22, by + y + 6) == 0x64c0)OR(GetPixel3(bx + 23, by + y + 6) == 0x64c0)OR((GetPixel3(bx + 1, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 2, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 3, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 4, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 5, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 6, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 7, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 8, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 9, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 10, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 11, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 12, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 13, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 14, by + y + 7 + 9) == 0x64c0)OR(GetPixel3(bx + 15, by + y + 7 + 8) == 0x64c0)OR(GetPixel3(bx + 16, by + y + 7 + 7) == 0x64c0)OR(GetPixel3(bx + 17, by + y + 7 + 6) == 0x64c0)OR(GetPixel3(bx + 18, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 19, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 20, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 21, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 22, by + y + 7) == 0x64c0)OR(GetPixel3(bx + 23, by + y + 7) == 0x64c0)OR((GetPixel3(bx + 1, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 2, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 3, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 4, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 5, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 6, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 7, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 8, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 9, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 10, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 11, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 12, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 13, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 14, by + y + 10 + 9) == 0x64c0)OR(GetPixel3(bx + 15, by + y + 10 + 8) == 0x64c0)OR(GetPixel3(bx + 16, by + y + 10 + 7) == 0x64c0)OR(GetPixel3(bx + 17, by + y + 10 + 6) == 0x64c0)OR(GetPixel3(bx + 18, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 19, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 20, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 21, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 22, by + y + 10) == 0x64c0)OR(GetPixel3(bx + 23, by + y + 10) == 0x64c0))))
								{
									by -= 3;
									by -= y;
									y = 0;
									y -= 0.24;
								}
							}
						}
					}
				}
			}
			if (keyDown(KEY_A))
			{
				y = 4.05;
				jumps++;
			}
		}
	}
}

void die()
{
	bx = 8;
	by = 108;
	x = 0;
	y = 0;
	restart = 0;
	gravity = 0;
	deaths++;
	if(level==18)
	{
		creepdeaths++;
	}
}
void physics()
{
	if (gravity == 0)
	{
		y += 0.24;
	}
	else {
		y -= 0.24;
	}
	if (keyDown(KEY_LEFT))
	{
		x -= 0.5;
		dir = 1;
	}
	if (keyDown(KEY_RIGHT))
	{
		x += 0.5;
		dir = 0;
	}
	x *= 0.9;
	if ((dir == 1)AND(NOT(x>0))AND(NOT(keyDown(KEY_LEFT))))
	{
		x += 0.08;
		if (x>0)
		{
			x = 0;
		}
	}
	bx += x;
	by += y;
	bottomcol();
	leftcol();
	rightcol();
	topcol();
	if ((bx > 199)AND(by > 104))
	{
		level++;
		if ((level == 59)AND(g == 0))
		{
			level--;
		}
		if (level == levelmax++)
		{
			level--;
		}
		levels();
		varreset();
		musici+=8;
		if(level==2)
		{
			achievement(17);
		}
		if(level==8)
		{
			achievement(0);
		}
		if(level==19)
		{
			if(creepdeaths==0)
			{
				achievement(14);
			}
		}
		if(level==37)
		{
			achievement(15);
		}
		if(level==49)
		{
			achievement(9);
		}
		if(level==52)
		{
			achievement(19);
		}
		if(level==100)
		{
			achievement(1);
		}
		if(level==134)
		{
			achievement(13);
		}
	}
}

	
/* libgbfs.c
   access object in a GBFS file

Copyright 2002 Damian Yerrick

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.

*/


/* This code assumes a LITTLE ENDIAN target.  It'll need a boatload
   of itohs and itohl calls if converted to run on Sega Genesis.  It
   also assumes that the target uses 16-bit short and 32-bit longs.
*/

#include <stdlib.h>
#include <string.h>

/* change this to the end of your ROM, or to 0x02040000 for multiboot */
#define GBFS_SEARCH_LIMIT ((const unsigned long *)0x0a000000)

/* a power of two, less than or equal to the argument passed to
   padbin */
#define GBFS_ALIGNMENT  256

const GBFS_FILE *find_first_gbfs_file(const void *start)
{
  /* align the pointer */
  const unsigned long *here = (const unsigned long *)
                      ((unsigned long)start & (-GBFS_ALIGNMENT));
  const char rest_of_magic[] = "ightGBFS\r\n\032\n";

  /* while we haven't yet reached the end of the ROM space */
  while(here < GBFS_SEARCH_LIMIT)
  {
    /* We have to keep the magic code in two pieces; otherwise,
       this function will find itself and think it's a GBFS file.
       This obviously won't work if your compiler stores this
       numeric literal just before the literal string, but Devkit
       Advance seems to keep numeric constant pools separate enough
       from string pools for this to work.
    */
    if(*here == 0x456e6950)  /* ASCII code for "PinE" */
    {
      /* we're already after here;
         if the rest of the magic matches, then we're through */
      if(!memcmp(here + 1, rest_of_magic, 12))
        return (const GBFS_FILE *)here;
    }
    here += GBFS_ALIGNMENT / sizeof(*here);
  }
  return 0;
}


const void *skip_gbfs_file(const GBFS_FILE *file)
{
  return ((char *)file + file->total_len);
}


static int namecmp(const void *a, const void *b)
{
  return memcmp(a, b, 24);
}


const void *gbfs_get_obj(const GBFS_FILE *file,
                         const char *name,
                         unsigned long *len)
{
  char key[24] = {0};

  GBFS_ENTRY *dirbase = (GBFS_ENTRY *)((char *)file + file->dir_off);
  size_t n_entries = file->dir_nmemb;
  GBFS_ENTRY *here;

  strncpy(key, name, 24);

  here = bsearch(key, dirbase,
                 n_entries, sizeof(GBFS_ENTRY),
                 namecmp);
  if(!here)
    return 0;

  if(len)
    *len = here->len;
  return (char *)file + here->data_offset;
}


void *gbfs_copy_obj(void *dst,
                    const GBFS_FILE *file,
                    const char *name)
{
  unsigned long len;
  const void *src = gbfs_get_obj(file, name, &len);

  if(!src)
    return 0;

  memcpy(dst, src, len);
  return dst;
}


void levels() {
	const GBFS_FILE *dat = find_first_gbfs_file(find_first_gbfs_file);
	sprintf(buf, "l%d.lz", level);
	if(level==138)
	{
		LZ77UnCompVRAM((unsigned long)gbfs_get_obj(dat, "end.lz", 0), (unsigned long)videoBuffer);
	}else{
		LZ77UnCompVRAM((unsigned long)gbfs_get_obj(dat, (char*)buf, 0), (unsigned long)videoBuffer);
	}
}