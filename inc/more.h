u16 sbj_GetPixel(u8 x, u8 y)
{
    return VRAM[y * 240 + x]; //returns the pixel color at the position given
}

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
	if (achdata[id] == 0)
	{
		achdata[id] = 1;
		hrt_SetOBJXY(&sprites[50], 232, 152);
		unreadchieves = 1;
		if (level == 103)
		{
			mm_sound_effect fez = {
				{ SFX_SECRETSOLVED},			// id
				(int)(1.0f * (1 << 10)),	// rate
				0,		// handle
				255,	// volume
				0,	// panning
			};
			mm_sfxhand fezc = 0;
			fezc = mmEffectEx(&fez);
		}
		else
		{
			mm_sound_effect ach = {
				{ SFX_ACHIEVEMENT },			// id
				(int)(1.0f * (1 << 10)),	// rate
				0,		// handle
				255,	// volume
				0,	// panning
			};
			mm_sfxhand achi = 0;
			achi = mmEffectEx(&ach);
		}
	}
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
    if ((sbj_GetPixel(bx + 1, by + 24 + y) == color)OR(sbj_GetPixel(bx + 1, by + 22 + y) == color)OR(sbj_GetPixel(bx + 2, by + 24 + y) == color)OR(sbj_GetPixel(bx + 2, by + 23 + y) == color)OR(sbj_GetPixel(bx + 3, by + 24 + y) == color)OR(sbj_GetPixel(bx + 3, by + 23 + y) == color)OR(sbj_GetPixel(bx + 3, by + 22 + y) == color)OR(sbj_GetPixel(bx + 4, by + 24 + y) == color)OR(sbj_GetPixel(bx + 4, by + 23 + y) == color)OR(sbj_GetPixel(bx + 4, by + 22 + y) == color)OR(sbj_GetPixel(bx + 5, by + 24 + y) == color)OR(sbj_GetPixel(bx + 5, by + 23 + y) == color)OR(sbj_GetPixel(bx + 5, by + 22 + y) == color)OR(sbj_GetPixel(bx + 6, by + 24 + y) == color)OR(sbj_GetPixel(bx + 6, by + 23 + y) == color)OR(sbj_GetPixel(bx + 6, by + 22 + y) == color)OR(sbj_GetPixel(bx + 7, by + 24 + y) == color)OR(sbj_GetPixel(bx + 7, by + 23 + y) == color)OR(sbj_GetPixel(bx + 7, by + 22 + y) == color)OR(sbj_GetPixel(bx + 8, by + 24 + y) == color)OR(sbj_GetPixel(bx + 8, by + 23 + y) == color)OR(sbj_GetPixel(bx + 8, by + 22 + y) == color)OR(sbj_GetPixel(bx + 9, by + 24 + y) == color)OR(sbj_GetPixel(bx + 9, by + 23 + y) == color)OR(sbj_GetPixel(bx + 9, by + 22 + y) == color)OR(sbj_GetPixel(bx + 10, by + 24 + y) == color)OR(sbj_GetPixel(bx + 10, by + 23 + y) == color)OR(sbj_GetPixel(bx + 10, by + 22 + y) == color)OR(sbj_GetPixel(bx + 11, by + 24 + y) == color)OR(sbj_GetPixel(bx + 12, by + 23 + y) == color)OR(sbj_GetPixel(bx + 12, by + 22 + y) == color)OR(sbj_GetPixel(bx + 13, by + 24 + y) == color)OR(sbj_GetPixel(bx + 13, by + 23 + y) == color)OR(sbj_GetPixel(bx + 13, by + 22 + y) == color)OR(sbj_GetPixel(bx + 14, by + 24 + y) == color)OR(sbj_GetPixel(bx + 14, by + 23 + y) == color)OR(sbj_GetPixel(bx + 14, by + 22 + y) == color)OR(sbj_GetPixel(bx + 15, by + 24 + y) == color)OR(sbj_GetPixel(bx + 16, by + 23 + y) == color)OR(sbj_GetPixel(bx + 17, by + 22 + y) == color)OR(sbj_GetPixel(bx + 18, by + 24 + y) == color)OR(sbj_GetPixel(bx + 19, by + 23 + y) == color)OR(sbj_GetPixel(bx + 20, by + 22 + y) == color)) {
        return 1;
    }
    else if ((sbj_GetPixel(bx + 24 + x, by + 22) == color)OR(sbj_GetPixel(bx + 24 + x, by + 21) == color)OR(sbj_GetPixel(bx + 24 + x, by + 20) == color)OR(sbj_GetPixel(bx + 24 + x, by + 19) == color)OR(sbj_GetPixel(bx + 24 + x, by + 18) == color)OR(sbj_GetPixel(bx + 24 + x, by + 17) == color)OR(sbj_GetPixel(bx + 24 + x, by + 16) == color)OR(sbj_GetPixel(bx + 24 + x, by + 15) == color)OR(sbj_GetPixel(bx + 24 + x, by + 14) == color)OR(sbj_GetPixel(bx + 24 + x, by + 13) == color)OR(sbj_GetPixel(bx + 24 + x, by + 12) == color)OR(sbj_GetPixel(bx + 24 + x, by + 11) == color)OR(sbj_GetPixel(bx + 24 + x, by + 10) == color)OR(sbj_GetPixel(bx + 24 + x, by + 9) == color)OR(sbj_GetPixel(bx + 24 + x, by + 8) == color)OR(sbj_GetPixel(bx + 24 + x, by + 7) == color)OR(sbj_GetPixel(bx + 24 + x, by + 6) == color)OR(sbj_GetPixel(bx + 24 + x, by + 5) == color)OR(sbj_GetPixel(bx + 24 + x, by + 4) == color)OR(sbj_GetPixel(bx + 24 + x, by + 3) == color)OR(sbj_GetPixel(bx + 24 + x, by + 2) == color)OR(sbj_GetPixel(bx + 24 + x, by + 1) == color)OR(sbj_GetPixel(bx + 23 + x, by + 22) == color)OR(sbj_GetPixel(bx + 23 + x, by + 21) == color)OR(sbj_GetPixel(bx + 23 + x, by + 20) == color)OR(sbj_GetPixel(bx + 23 + x, by + 19) == color)OR(sbj_GetPixel(bx + 23 + x, by + 18) == color)OR(sbj_GetPixel(bx + 23 + x, by + 17) == color)OR(sbj_GetPixel(bx + 23 + x, by + 16) == color)OR(sbj_GetPixel(bx + 23 + x, by + 15) == color)OR(sbj_GetPixel(bx + 23 + x, by + 14) == color)OR(sbj_GetPixel(bx + 23 + x, by + 13) == color)OR(sbj_GetPixel(bx + 23 + x, by + 12) == color)OR(sbj_GetPixel(bx + 23 + x, by + 11) == color)OR(sbj_GetPixel(bx + 23 + x, by + 10) == color)OR(sbj_GetPixel(bx + 23 + x, by + 9) == color)OR(sbj_GetPixel(bx + 23 + x, by + 8) == color)OR(sbj_GetPixel(bx + 23 + x, by + 7) == color)OR(sbj_GetPixel(bx + 23 + x, by + 6) == color)OR(sbj_GetPixel(bx + 23 + x, by + 5) == color)OR(sbj_GetPixel(bx + 23 + x, by + 4) == color)OR(sbj_GetPixel(bx + 23 + x, by + 3) == color)OR(sbj_GetPixel(bx + 23 + x, by + 2) == color)OR(sbj_GetPixel(bx + 23 + x, by + 1) == color)) {
        return 1;
    }
    else if ((sbj_GetPixel(bx + x, by + 22) == color)OR(sbj_GetPixel(bx + x, by + 21) == color)OR(sbj_GetPixel(bx + x, by + 20) == color)OR(sbj_GetPixel(bx + x, by + 19) == color)OR(sbj_GetPixel(bx + x, by + 18) == color)OR(sbj_GetPixel(bx + x, by + 17) == color)OR(sbj_GetPixel(bx + x, by + 16) == color)OR(sbj_GetPixel(bx + x, by + 15) == color)OR(sbj_GetPixel(bx + x, by + 14) == color)OR(sbj_GetPixel(bx + x, by + 13) == color)OR(sbj_GetPixel(bx + x, by + 12) == color)OR(sbj_GetPixel(bx + x, by + 11) == color)OR(sbj_GetPixel(bx + x, by + 10) == color)OR(sbj_GetPixel(bx + x, by + 9) == color)OR(sbj_GetPixel(bx + x, by + 8) == color)OR(sbj_GetPixel(bx + x, by + 7) == color)OR(sbj_GetPixel(bx + x, by + 6) == color)OR(sbj_GetPixel(bx + x, by + 5) == color)OR(sbj_GetPixel(bx + x, by + 4) == color)OR(sbj_GetPixel(bx + x, by + 3) == color)OR(sbj_GetPixel(bx + x, by + 2) == color)OR(sbj_GetPixel(bx + x, by + 1) == color)OR(sbj_GetPixel(bx + 1 + x, by + 22) == color)OR(sbj_GetPixel(bx + 1 + x, by + 21) == color)OR(sbj_GetPixel(bx + 1 + x, by + 20) == color)OR(sbj_GetPixel(bx + 1 + x, by + 19) == color)OR(sbj_GetPixel(bx + 1 + x, by + 18) == color)OR(sbj_GetPixel(bx + 1 + x, by + 17) == color)OR(sbj_GetPixel(bx + 1 + x, by + 16) == color)OR(sbj_GetPixel(bx + 1 + x, by + 15) == color)OR(sbj_GetPixel(bx + 1 + x, by + 14) == color)OR(sbj_GetPixel(bx + 1 + x, by + 13) == color)OR(sbj_GetPixel(bx + 1 + x, by + 12) == color)OR(sbj_GetPixel(bx + 1 + x, by + 11) == color)OR(sbj_GetPixel(bx + 1 + x, by + 10) == color)OR(sbj_GetPixel(bx + 1 + x, by + 9) == color)OR(sbj_GetPixel(bx + 1 + x, by + 8) == color)OR(sbj_GetPixel(bx + 1 + x, by + 7) == color)OR(sbj_GetPixel(bx + 1 + x, by + 6) == color)OR(sbj_GetPixel(bx + 1 + x, by + 5) == color)OR(sbj_GetPixel(bx + 1 + x, by + 4) == color)OR(sbj_GetPixel(bx + 1 + x, by + 3) == color)OR(sbj_GetPixel(bx + 1 + x, by + 2) == color)OR(sbj_GetPixel(bx + 1 + x, by + 1) == color)OR(sbj_GetPixel(bx + 2 + x, by + 22) == color)OR(sbj_GetPixel(bx + 2 + x, by + 21) == color)OR(sbj_GetPixel(bx + 2 + x, by + 20) == color)OR(sbj_GetPixel(bx + 2 + x, by + 19) == color)OR(sbj_GetPixel(bx + 2 + x, by + 18) == color)OR(sbj_GetPixel(bx + 2 + x, by + 17) == color)OR(sbj_GetPixel(bx + 2 + x, by + 16) == color)OR(sbj_GetPixel(bx + 2 + x, by + 15) == color)OR(sbj_GetPixel(bx + 2 + x, by + 14) == color)OR(sbj_GetPixel(bx + 2 + x, by + 13) == color)OR(sbj_GetPixel(bx + 2 + x, by + 12) == color)OR(sbj_GetPixel(bx + 2 + x, by + 11) == color)OR(sbj_GetPixel(bx + 2 + x, by + 10) == color)OR(sbj_GetPixel(bx + 2 + x, by + 9) == color)OR(sbj_GetPixel(bx + 2 + x, by + 8) == color)OR(sbj_GetPixel(bx + 2 + x, by + 7) == color)OR(sbj_GetPixel(bx + 2 + x, by + 6) == color)OR(sbj_GetPixel(bx + 2 + x, by + 5) == color)OR(sbj_GetPixel(bx + 2 + x, by + 4) == color)OR(sbj_GetPixel(bx + 2 + x, by + 3) == color)OR(sbj_GetPixel(bx + 2 + x, by + 2) == color)OR(sbj_GetPixel(bx + 2 + x, by + 1) == color)) {
        return 1;
    }
    else if ((sbj_GetPixel(bx + 1, by) == color)OR(sbj_GetPixel(bx + 2, by) == color)OR(sbj_GetPixel(bx + 3, by) == color)OR(sbj_GetPixel(bx + 4, by) == color)OR(sbj_GetPixel(bx + 5, by) == color)OR(sbj_GetPixel(bx + 6, by) == color)OR(sbj_GetPixel(bx + 7, by) == color)OR(sbj_GetPixel(bx + 8, by) == color)OR(sbj_GetPixel(bx + 9, by) == color)OR(sbj_GetPixel(bx + 10, by) == color)OR(sbj_GetPixel(bx + 11, by) == color)OR(sbj_GetPixel(bx + 12, by) == color)OR(sbj_GetPixel(bx + 13, by) == color)OR(sbj_GetPixel(bx + 14, by + 9) == color)OR(sbj_GetPixel(bx + 15, by + 8) == color)OR(sbj_GetPixel(bx + 16, by + 7) == color)OR(sbj_GetPixel(bx + 17, by + 6) == color)OR(sbj_GetPixel(bx + 18, by) == color)OR(sbj_GetPixel(bx + 19, by) == color)OR(sbj_GetPixel(bx + 20, by) == color)OR(sbj_GetPixel(bx + 21, by) == color)OR(sbj_GetPixel(bx + 22, by) == color)OR(sbj_GetPixel(bx + 23, by) == color)) {
        return 1;
    }
    else {
        return 0;
    }
}

void bottomcol()
{
    if ((sbj_GetPixel(bx + 1, by + 24 + y) == 0x64c0)OR(sbj_GetPixel(bx + 1, by + 22 + y) == 0x64c0)OR(sbj_GetPixel(bx + 2, by + 24 + y) == 0x64c0)OR(sbj_GetPixel(bx + 2, by + 23 + y) == 0x64c0)OR(sbj_GetPixel(bx + 3, by + 24 + y) == 0x64c0)OR(sbj_GetPixel(bx + 3, by + 23 + y) == 0x64c0)OR(sbj_GetPixel(bx + 3, by + 22 + y) == 0x64c0)OR(sbj_GetPixel(bx + 4, by + 24 + y) == 0x64c0)OR(sbj_GetPixel(bx + 4, by + 23 + y) == 0x64c0)OR(sbj_GetPixel(bx + 4, by + 22 + y) == 0x64c0)OR(sbj_GetPixel(bx + 5, by + 24 + y) == 0x64c0)OR(sbj_GetPixel(bx + 5, by + 23 + y) == 0x64c0)OR(sbj_GetPixel(bx + 5, by + 22 + y) == 0x64c0)OR(sbj_GetPixel(bx + 6, by + 24 + y) == 0x64c0)OR(sbj_GetPixel(bx + 6, by + 23 + y) == 0x64c0)OR(sbj_GetPixel(bx + 6, by + 22 + y) == 0x64c0)OR(sbj_GetPixel(bx + 7, by + 24 + y) == 0x64c0)OR(sbj_GetPixel(bx + 7, by + 23 + y) == 0x64c0)OR(sbj_GetPixel(bx + 7, by + 22 + y) == 0x64c0)OR(sbj_GetPixel(bx + 8, by + 24 + y) == 0x64c0)OR(sbj_GetPixel(bx + 8, by + 23 + y) == 0x64c0)OR(sbj_GetPixel(bx + 8, by + 22 + y) == 0x64c0)OR(sbj_GetPixel(bx + 9, by + 24 + y) == 0x64c0)OR(sbj_GetPixel(bx + 9, by + 23 + y) == 0x64c0)OR(sbj_GetPixel(bx + 9, by + 22 + y) == 0x64c0)OR(sbj_GetPixel(bx + 10, by + 24 + y) == 0x64c0)OR(sbj_GetPixel(bx + 10, by + 23 + y) == 0x64c0)OR(sbj_GetPixel(bx + 10, by + 22 + y) == 0x64c0)OR(sbj_GetPixel(bx + 11, by + 24 + y) == 0x64c0)OR(sbj_GetPixel(bx + 12, by + 23 + y) == 0x64c0)OR(sbj_GetPixel(bx + 12, by + 22 + y) == 0x64c0)OR(sbj_GetPixel(bx + 13, by + 24 + y) == 0x64c0)OR(sbj_GetPixel(bx + 13, by + 23 + y) == 0x64c0)OR(sbj_GetPixel(bx + 13, by + 22 + y) == 0x64c0)OR(sbj_GetPixel(bx + 14, by + 24 + y) == 0x64c0)OR(sbj_GetPixel(bx + 14, by + 23 + y) == 0x64c0)OR(sbj_GetPixel(bx + 14, by + 22 + y) == 0x64c0)OR(sbj_GetPixel(bx + 15, by + 24 + y) == 0x64c0)OR(sbj_GetPixel(bx + 16, by + 23 + y) == 0x64c0)OR(sbj_GetPixel(bx + 17, by + 22 + y) == 0x64c0)OR(sbj_GetPixel(bx + 18, by + 24 + y) == 0x64c0)OR(sbj_GetPixel(bx + 19, by + 23 + y) == 0x64c0)OR(sbj_GetPixel(bx + 20, by + 22 + y) == 0x64c0)OR((sbj_GetPixel(bx, by + 24) == 0x64c0))OR(sbj_GetPixel(bx + 24, by + 24) == 0x64c0)OR(sbj_GetPixel(bx + 22, by + 24 + y) == 0x64c0)OR(sbj_GetPixel(bx + 21, by + 23 + y) == 0x64c0)) {
        by -= 1;
        y = 0;
        if ((keyDown(KEY_A))AND(gravity == 0)) {
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
            jumps++;
        }
    }
}

void rightcol()
{
    if ((sbj_GetPixel(bx + 24 + x, by + 22) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 21) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 20) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 19) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 18) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 17) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 16) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 15) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 14) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 13) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 12) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 11) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 10) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 9) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 8) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 7) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 6) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 5) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 4) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 3) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 2) == 0x64c0)OR(sbj_GetPixel(bx + 24 + x, by + 1) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 22) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 21) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 20) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 19) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 18) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 17) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 16) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 15) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 14) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 13) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 12) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 11) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 10) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 9) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 8) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 7) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 6) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 5) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 4) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 3) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 2) == 0x64c0)OR(sbj_GetPixel(bx + 23 + x, by + 1) == 0x64c0)) {
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
            if (gravity == 0) {
                y = -4.05;
            }
            else {
                y = 4.05;
            }
            x = -5;
            jumps++;
        }
        else {
            x = 0;
            bx -= 1;
        }
    }
}

void leftcol()
{
    if ((sbj_GetPixel(bx + x, by + 22) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 21) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 20) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 19) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 18) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 17) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 16) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 15) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 14) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 13) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 12) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 11) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 10) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 9) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 8) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 7) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 6) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 5) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 4) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 3) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 2) == 0x64c0)OR(sbj_GetPixel(bx + x, by + 1) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 22) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 21) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 20) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 19) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 18) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 17) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 16) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 15) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 14) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 13) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 12) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 11) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 10) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 9) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 8) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 7) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 6) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 5) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 4) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 3) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 2) == 0x64c0)OR(sbj_GetPixel(bx + 1 + x, by + 1) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 22) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 21) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 20) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 19) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 18) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 17) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 16) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 15) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 14) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 13) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 12) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 11) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 10) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 9) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 8) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 7) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 6) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 5) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 4) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 3) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 2) == 0x64c0)OR(sbj_GetPixel(bx + 2 + x, by + 1) == 0x64c0)) {
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
            if (gravity == 0) {
                y = -4.05;
            }
            else {
                y = 4.05;
            }
            x = 5;
            jumps++;
        }
        else {
            x = 0;
            bx += 1;
        }
    }
}

void topcol()
{
    if ((sbj_GetPixel(bx + 1, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 2, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 3, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 4, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 5, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 6, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 7, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 8, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 9, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 10, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 11, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 12, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 13, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 14, by + y + 9) == 0x64c0)OR(sbj_GetPixel(bx + 15, by + y + 8) == 0x64c0)OR(sbj_GetPixel(bx + 16, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 17, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 18, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 19, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 20, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 21, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 22, by + y) == 0x64c0)OR(sbj_GetPixel(bx + 23, by + y) == 0x64c0)) {
        if (gravity == 0) {
            by += 3;
            by -= y;
            y = 0;
            y += 0.24;
            jumps++;
            hrt_SetOBJXY(&sprites[1], bx, by);
        }
        else {
            y = 0;
            by += 1;
            if ((sbj_GetPixel(bx + 1, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 2, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 3, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 4, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 5, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 6, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 7, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 8, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 9, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 10, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 11, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 12, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 13, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 14, by + y + 1 + 9) == 0x64c0)OR(sbj_GetPixel(bx + 15, by + y + 1 + 8) == 0x64c0)OR(sbj_GetPixel(bx + 16, by + y + 1 + 7) == 0x64c0)OR(sbj_GetPixel(bx + 17, by + y + 1 + 6) == 0x64c0)OR(sbj_GetPixel(bx + 18, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 19, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 20, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 21, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 22, by + y + 1) == 0x64c0)OR(sbj_GetPixel(bx + 23, by + y + 1) == 0x64c0)) {
                y = 0;
                by += 1;
                if ((sbj_GetPixel(bx + 1, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 2, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 3, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 4, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 5, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 6, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 7, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 8, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 9, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 10, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 11, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 12, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 13, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 14, by + y + 2 + 9) == 0x64c0)OR(sbj_GetPixel(bx + 15, by + y + 2 + 8) == 0x64c0)OR(sbj_GetPixel(bx + 16, by + y + 2 + 7) == 0x64c0)OR(sbj_GetPixel(bx + 17, by + y + 2 + 6) == 0x64c0)OR(sbj_GetPixel(bx + 18, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 19, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 20, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 21, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 22, by + y + 2) == 0x64c0)OR(sbj_GetPixel(bx + 23, by + y + 2) == 0x64c0)) {
                    y = 0;
                    by += 1;
                    if ((sbj_GetPixel(bx + 1, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 2, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 3, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 4, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 5, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 6, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 7, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 8, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 9, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 10, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 11, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 12, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 13, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 14, by + y + 3 + 9) == 0x64c0)OR(sbj_GetPixel(bx + 15, by + y + 3 + 8) == 0x64c0)OR(sbj_GetPixel(bx + 16, by + y + 3 + 7) == 0x64c0)OR(sbj_GetPixel(bx + 17, by + y + 3 + 6) == 0x64c0)OR(sbj_GetPixel(bx + 18, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 19, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 20, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 21, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 22, by + y + 3) == 0x64c0)OR(sbj_GetPixel(bx + 23, by + y + 3) == 0x64c0)) {
                        y = 0;
                        by += 1;
                        if ((sbj_GetPixel(bx + 1, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 2, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 3, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 4, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 5, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 6, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 7, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 8, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 9, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 10, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 11, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 12, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 13, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 14, by + y + 4 + 9) == 0x64c0)OR(sbj_GetPixel(bx + 15, by + y + 4 + 8) == 0x64c0)OR(sbj_GetPixel(bx + 16, by + y + 4 + 7) == 0x64c0)OR(sbj_GetPixel(bx + 17, by + y + 4 + 6) == 0x64c0)OR(sbj_GetPixel(bx + 18, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 19, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 20, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 21, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 22, by + y + 4) == 0x64c0)OR(sbj_GetPixel(bx + 23, by + y + 4) == 0x64c0)) {
                            y = 0;
                            by += 1;
                            if ((sbj_GetPixel(bx + 1, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 2, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 3, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 4, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 5, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 6, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 7, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 8, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 9, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 10, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 11, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 12, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 13, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 14, by + (y * 2) + 5 + 9) == 0x64c0)OR(sbj_GetPixel(bx + 15, by + (y * 2) + 5 + 8) == 0x64c0)OR(sbj_GetPixel(bx + 16, by + (y * 2) + 5 + 7) == 0x64c0)OR(sbj_GetPixel(bx + 17, by + (y * 2) + 5 + 6) == 0x64c0)OR(sbj_GetPixel(bx + 18, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 19, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 20, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 21, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 22, by + (y * 2) + 5) == 0x64c0)OR(sbj_GetPixel(bx + 23, by + (y * 2) + 5) == 0x64c0)) {
                                y = 0;
                                by += 1;
                                if ((sbj_GetPixel(bx + 1, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 2, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 3, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 4, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 5, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 6, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 7, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 8, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 9, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 10, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 11, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 12, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 13, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 14, by + y + 6 + 9) == 0x64c0)OR(sbj_GetPixel(bx + 15, by + y + 6 + 8) == 0x64c0)OR(sbj_GetPixel(bx + 16, by + y + 6 + 7) == 0x64c0)OR(sbj_GetPixel(bx + 17, by + y + 6 + 6) == 0x64c0)OR(sbj_GetPixel(bx + 18, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 19, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 20, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 21, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 22, by + y + 6) == 0x64c0)OR(sbj_GetPixel(bx + 23, by + y + 6) == 0x64c0)OR((sbj_GetPixel(bx + 1, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 2, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 3, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 4, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 5, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 6, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 7, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 8, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 9, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 10, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 11, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 12, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 13, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 14, by + y + 7 + 9) == 0x64c0)OR(sbj_GetPixel(bx + 15, by + y + 7 + 8) == 0x64c0)OR(sbj_GetPixel(bx + 16, by + y + 7 + 7) == 0x64c0)OR(sbj_GetPixel(bx + 17, by + y + 7 + 6) == 0x64c0)OR(sbj_GetPixel(bx + 18, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 19, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 20, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 21, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 22, by + y + 7) == 0x64c0)OR(sbj_GetPixel(bx + 23, by + y + 7) == 0x64c0)OR((sbj_GetPixel(bx + 1, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 2, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 3, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 4, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 5, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 6, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 7, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 8, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 9, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 10, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 11, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 12, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 13, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 14, by + y + 10 + 9) == 0x64c0)OR(sbj_GetPixel(bx + 15, by + y + 10 + 8) == 0x64c0)OR(sbj_GetPixel(bx + 16, by + y + 10 + 7) == 0x64c0)OR(sbj_GetPixel(bx + 17, by + y + 10 + 6) == 0x64c0)OR(sbj_GetPixel(bx + 18, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 19, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 20, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 21, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 22, by + y + 10) == 0x64c0)OR(sbj_GetPixel(bx + 23, by + y + 10) == 0x64c0)))) {
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
                y = 4.05;
                jumps++;
            }
        }
    }
}

void die()
{
    x = 0;
    y = 0;
    restart = 0;
    gravity = 0;
    deaths++;
	deathstate = 1;
	deathframe = 0;
    if(level==18) {
        creepdeaths++;
    }
	mm_sound_effect ded = {
		{ SFX_DEATH },			// id
		(int)(1.0f * (1 << 10)),	// rate
		0,		// handle
		255,	// volume
		0,	// panning
	};
	mm_sfxhand death = 0;
	death = mmEffectEx(&ded);
}
void physics()
{
	if ((bx < 0)OR(bx > 216)OR(by < 0)OR(by > 136)) {
		die();
	}
    if (gravity == 0) {
        y += 0.24;
    }
    else {
        y -= 0.24;
    }
    if (keyDown(KEY_LEFT)) {
        x -= 0.5;
        dir = 1;
    }
    if (keyDown(KEY_RIGHT)) {
        x += 0.5;
        dir = 0;
    }
    x *= 0.9;
    if ((dir == 1)AND(NOT(x>0))AND(NOT(keyDown(KEY_LEFT)))) {
        x += 0.08;
        if (x>0) {
            x = 0;
        }
    }
    bx += x;
    by += y;
    bottomcol();
    leftcol();
    rightcol();
    topcol();
    if ((bx > 199)AND(by > 104)) {
        level++;
        if ((level == 59)AND(g == 0)) {
            level--;
        }
        if (level == levelmax++) {
            level--;
        }
        levels();
        varreset();
        musici+=8;
        if(level==2) {
            achievement(17);
        }
        if(level==8) {
            achievement(0);
        }
        if(level==19) {
            if(creepdeaths==0) {
                achievement(14);
            }
        }
        if(level==37) {
            achievement(15);
        }
        if(level==49) {
            achievement(9);
        }
        if(level==52) {
            achievement(19);
        }
        if(level==100) {
            achievement(1);
        }
        if(level==134) {
            achievement(13);
        }
    }
}


void levels()
{
    const GBFS_FILE *dat = find_first_gbfs_file(find_first_gbfs_file);
    sprintf(buf, "l%d.lz", level);
    if(level==140) {
        hrt_LZ77UnCompVRAM((unsigned long)gbfs_get_obj(dat, "end.lz", 0), (unsigned long)VRAM);
    }
    else {
        hrt_LZ77UnCompVRAM((unsigned long)gbfs_get_obj(dat, (char*)buf, 0), (unsigned long)VRAM);
    }
	if (pause == 0)
	{
		if (rand1 == 1)
		{
			mm_sound_effect cp1 = {
				{ SFX_COMPLETE },			// id
				(int)(1.0f * (1 << 10)),	// rate
				0,		// handle
				255,	// volume
				0,	// panning
			};
			mm_sfxhand complete1 = 0;
			complete1 = mmEffectEx(&cp1);
		}
		else {
			mm_sound_effect cp2 = {
				{ SFX_COMPLETE2 },			// id
				(int)(1.0f * (1 << 10)),	// rate
				0,		// handle
				255,	// volume
				0,	// panning
			};
			mm_sfxhand complete2 = 0;
			complete2 = mmEffectEx(&cp2);
		}
	}
}
void setbg2(u16* image, u16* pal)
{
    hrt_VblankIntrWait();
    REG_DMA3SAD = (unsigned long)image;
    hrt_LoadBGPal(pal, 255);
    hrt_offsetBGPal = 0;
    REG_DMA3DAD = (unsigned long)VRAM;
    REG_DMA3CNT = 0x80000000 | 120 * 160;
}

void setbg2novb(u16* image, u16* pal)
{
    REG_DMA3SAD = (unsigned long)image;
    hrt_LoadBGPal(pal, 255);
    hrt_offsetBGPal = 0;
    REG_DMA3DAD = (unsigned long)VRAM;
    REG_DMA3CNT = 0x80000000 | 120 * 160;
}
