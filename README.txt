THIS GAME REQUIRES HEARTLIB. github.com/Sterophonick/HeartLib. 
libheart.a needs to be placed in C:\Devkitpro\devkitARM\lib
*.h need to be placed in any valid include directory


NOTE: IF YOU HAVE PAID MONEY FOR THIS GAME, I SUGGEST YOU GET A REFUND IMMEDIATELY. THIS PRODUCT IS FREEWARE. 
ANY SORT OF SELLING ANY HOMEBREW OR BOOTLEG VIDEO GAME IS PUNISHABLE BY LAW.

Compilation time from clean: around 5-7 minutes


Controls:
	Gameplay:
		A - Jump
		B - Fire
		Start - Pause
		Select - reverse gravity when accessible
	Pause:
		Start/A: Unpause
		Select/B: Restart level
	Menu:
		Start: begin game
		Start: Show controls
	Titlescreen:
		Start: Begin

This is a Game Boy Advance homebrew port of Super Block Jump. The features that were removed are:
achievements (for now...)
Extras
very high resolution graphics.
Vector graphics (GBA can't handle it.)
Some music (only 1 track now, due to file size. (Max 32 MB:( )
Most sounds (only 2 now)
Removed block color changing
Removed Debug Mode
removed snow
removed pause options, replaced with save menu.
removed FPS counter
removed achievements button
removed timer mode
removed Touchscreen
removed stereoscopy
removed intro, and replaced it with some startup credits like in most games
Replaced some levels
Removed lifts
Removed size change from death.
Removed raise animation from FEZ level
Removed go-crew bullet
Removed go crew movement
Removed explosion
Removed jump refresher whirl, and replaced it with a cool bevel effect.
Removed some tranistions
Removed Jump Height Control
Enemy death animation

Changes are:
lower resolution (originally 480x360, and here it is 240x160)
lower quality audio (hardware)
lower quality graphics/textures (hardware)
smaller textures (cut down by less than half :( )
no clicking (hardware)
Only two frames for kernel panic (save space)
Only two frames for red static (save space)
Slightly different physics (Because of C coding)
Possible Bugginess(This is my first GBA game ever.)
Minor changes to levels (extra / changed text, etc.)
Sonic instead of springtrap in BSOD (because reasons)
Black background for killscreen (can't do both tiled and full 15-bit bitmap at same time.
less colors in sprites (palette limitations)
black screen for pause
Optimizations so that this demake will work well with the GBA and/or first time players.
Block freezes until Konami code is entered on the FEZ Level. (easier).
minor lag when Go-Crew is beaten (because gameplay is in Mode 3, and I can't use the normal DMA transfer for this display mode, so I have to completely redraw the screen, while using the BIOS' LZ77 decompression function.)

Additions:
More levels + levels of Super Block Jump 2
Three slots of Saving (Only Saves the level and some other necessary data, and not your position)
SRAM Clear at startup, holding A and B.
Save Manager in pause menu. (save, load, and delete)
Compressed Backgrounds and levels using the LZ77 Compression method.

About the missing levels:
The reason why there are some missing levels is because those levels require something that the GBA doesn't have, 
such as a mouse, or it is too much work. However, I have made up for that with 130+ levels! The ROM size is way smaller than the Scratch Project Size, due to the reduced size of the graphics, and the fact that they are bitmaps, and not vector images, and they have been compressed. This conserves the Final ROM Size of the game.

Recommended Programs to use: (program, platform, downsides)
Basically, you will need to use an emulator that has BIOS emulation, or an emulator that has an option to use the BIOS (use the final BIOS, not the debug one. The debug BIOS breaks the game.), or you can use an actual Game Boy Advance. I tested this and it works great.

Nesbox Emulator (Windows) No vsync, sound problems.
no$gba (Windows, Mac) Desaturation, hard to use
VisualBoyAdvance (Windows, Mac, Linux) Too fast, music too short.
mGBA (Windows, Mac, Linux, Libretro) Sometimes crashes, however, it is the most accurate emulator I've tested.

Used to brew port:
Microsoft Visual Studio Community 2017 (Code)
MS Paint (GFX)
RealWorld Paint (GFX)
Columniser (GFX)
mid2s3m (Sound)
Scratch 2 (Original)
Various image converters
Windows 10
GNU make (compilation)
mGBA (Game Testing, Emulation)
DevKitARM (Compiler)
Nesbox Emulator (Game Testing, Emulation)
ImageMagick (GFX)
EZ-Flash IV (Game Testing)
gbfs, padbin, grit, bmp2bin, GBACrusher (GFX Compression)
Bimbo (GFX)
HeartLib (Game Engine)

Written in C, compiled with DevKitARM.

Special Thanks:
MIT
The Scratch Community
Jay Van Hutten for inspiring me to make homebrew GBA games, and for Making GBA Flappy Bird.
3DSage
gbadev.org
DevKit Advance
Nintendo for making a great console to homebrew.
EZTeam
A+Start for his videos on Super Mario World orb/cloud glitch, which taught me about sprite slots (this gave me a basic idea on how sprites load and unload).
YouTube
SourceForge
GitHub
GCC
GNU
Open Source Movement
Me
Bullet Proof Software
SimonB
krom
Dwedit
FluBBa
TheCrimsonOrror for giving me the Game Boy Advance he had no use for.
(More on Special thanks page in the ROM).

Those who want a GB/GBC port, well, it's not likely, for these reasons:
1. RAM limitations
2. Color limitations (GB: 4 shades of grey, GBC: 64 colors at a time. GBA: 1-32,000 colors at a time.)
3. Sound output limitations
4. Screen resolution (WAYYYY too small, GB/GBC is 160x144, whereas the GBA is 240x160, which is... okay, I guess. It'd be better if it was 240x180, as it would make positioning and resizing MUCH, MUCH easier.)

Sounds from:
Original SBJ/2/Dark world
Yoshi's Cookie

Do you know what will be awesome? If I could show this at E3 or SpaceWorld.

Things you might not notice:
The block is actually 32x32 internally, but as it looks, it is 24x24. This same trick is pulled off on other sprites, too.
No enemy death animation
Different collision engine. (Sprites: hitboxes | Levels: Pixel color)
Slightly different physics.
Fix for rosetta stone texture being incorrect.
Some sprites are internally a bigger texture than they actually appear.
The Go-Crew is a background image and not a sprite.
No block death animation.

Dis Version is better cause:
More levels
Advanced features
Saving (Due to the game being played locally, and not online.)
Portable (Can be played basically anywhere, tablets, computers, Game Boys, Consoles, smartphones, and basically any device with a GBA Emulator)
Compact (small file size)
Open-Source
The game can "sleep" to save battery.
Compressed levels and backgrounds.
Fast, no slowdown.

Stuff I hope to add:
Local Multiplayer via link cable (That might not be possible... but it's worth a shot! :D)
Stronger Physics
150+ levels

Known issues:
Sometimes the block will clip into walls and floors if you go into them at the right angle.
Sometimes sprites will show up when their not supposed to.

Devlog:
5/11/17 v1.00a
Initial Release

5/11/17 v1.01a
Minor Bugfix update

5/12/17 v1.02c
Fixed Some Minor Fading issues with Sprites
Better VSync method
Faster level rendering method.
Slow fade with Sleeping.
Reenabled the Monster level and Pong level, and added some save data for it.

5/25/17 v1.02d
Changed Game start fade from black to white.
3 new levels
Changed sleep fade from black to white.

7/24/17 v1.03a
Minor Level changes
Minor Pause Bugfixes
Shortend music, removed unused backgrounds and sounds, total size: 13.4 MB

9/1/17 v1.05a
Compressed bgs and levels, extended music, total size: roughly 6.6 MB
Added levels from Scratch Super Block Jump 2.

12/25/2017 v1.06a
Merry Christmas!
One new level (lol)
Tweaked Killscreen img
Changed my name to "Sterophonick" in all uses of the word "imadog54." (imadog54 was my Scratch name. :P)

1/03/2018 v1.08a
Happy New Year!
Added Soft-Reset Code to gameplay.
3 New Levels
Fixed Unpause level rerendering issues.

4/18/2018 v1.09a
Made using HeartLib to showcase the abilities of this library.
Changed Sound Engine to MaxMod, which is built in to HeartLib. This allows me to add all of the sounds from the scratch version.
Added all missing sound effects.
Reduced Battery usage in most areas.
Made the block reduce its size when you die.
