# msx3d

This project is to be compiled with the excellent MSXgl library by @Aoineko.
Place the source files in a directory in the projects folder and start build to produce a 48KB rom for MSX1/2.

The code is essentially a video player: 64 frames of a 3D animation are split up in 12x12 tiles, which are displayed in VDP_MODE_GRAPHIC1. 
In this mode, chars have just two colors, defined by the color map, which holds a foreground and background color for 32 groups of 8 chars.
The 144 tiles are reduced to an average of 51 unique tiles per frame. Tiles are also reused between frames, resulting in about 2400 unique
tiles for the entire animation. After 64 frames, red and green colors are swapped for the next 64 frames, to produce one full revolution.

In this animation, some tiles have three colors. In this case, the third color is drawn using a sprite. This way, the cube can be drawn
artifact-free on MSX1, using the default palette.

The playback idea is borrowed from @ARTRAG. Adding sprites is my idea, but surely has been done before.

Rapid VDP code has been borrowed from MSXgl, and optimized for this particular use case to minimize frame time.

Greets to everyone on MSX.ORG - it's good to be back doing some sweet MSX coding again. :)