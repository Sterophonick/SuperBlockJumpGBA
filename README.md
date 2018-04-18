# Super Block Jump: Game Boy Advance Edition
An official Game Boy Advance Port of Super Block Jump made by the same creator of the scratch game.

# Controls:
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
    
# Changes from the Scratch version are:
	No Extras
	No Vector graphics (GBA can't handle it.)
	Only one music track
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
	Removed Enemy death animation
	Sonic instead of springtrap in BSOD (because reasons)
	Lower quality audio
	Lower quality graphics/textures
	Only two frames for kernel panic
	Only two frames for red static
	Slightly different physics
	Minor changes to levels
	Black background for killscreen
	Reduced color palette in sprites
	Black background for pause
	Block freezes until Konami code is entered on the FEZ Level (easier).
	More levels + levels of Super Block Jump 2
	Three slots of Saving
	SRAM Clear at startup, holding A and B.
	Save Manager in pause menu.
	Compressed Backgrounds and levels using the LZ77 Compression method.

# Tools used to make this game:
	Microsoft Visual Studio Community 2017 (Code)
	MS Paint (GFX)
	RealWorld Paint (GFX)
	Usenti (Sprite GFX)
	mmutil (Sound)
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

Written in C with HeartLib, compiled with DevKitARM.

I'm surprised that this game is only about 4.8 Megabytes, which is tiny, compared to the 45.9 MB needed for the Scratch version.