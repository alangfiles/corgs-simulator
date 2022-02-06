/*	example code for cc65, for NES
 *  move some sprites with the controllers
 *	using neslib
 *	Doug Fraker 2018
 */

#include "LIB/neslib.h"
#include "LIB/nesdoug.h"
#include "Sprites.h" // holds our metasprite data
#include "corgssim.h"

void main(void)
{

	ppu_off(); // screen off

	// load the palettes
	pal_bg(palette_bg);
	pal_spr(palette_sp);

	// use the second set of tiles for sprites
	// both bg and sprites are set to 0 by default
	bank_spr(1);

	set_scroll_y(0xff); //shift the bg down 1 pixel
	load_title();
	ppu_on_all(); // turn on screen

	// game loop
	while (1)
	{
		// title screen
		while (game_mode == MODE_TITLE)
		{
			ppu_wait_nmi();

			pad1 = pad_poll(0); // read the first controller
			pad1_new = get_pad_new(0);
			if (pad1_new & PAD_START)
			{
				pal_fade_to(4, 0); // fade to black
				clear_title();
				draw_bg();

				game_mode = MODE_GAME;
				pal_bright(4); // back to normal brighness
			}
		}

		ppu_wait_nmi(); // wait till beginning of the frame
		// the sprites are pushed from a buffer to the OAM during nmi

		pad1 = pad_poll(0);				 // read the first controller
		pad1_new = get_pad_new(0); // newly pressed button. do pad_poll first

		movement();
		draw_sprites();
		
	}
}

void draw_bg(void)
{
	oam_clear();
	ppu_off(); // screen off

	p_maps = All_Collision_Maps[which_bg];
	// copy the collision map to c_map
	memcpy(c_map, p_maps, 240);

	// this sets a start position on the BG, top left of screen
	vram_adr(NAMETABLE_A);

	// draw the tiles
	for (temp_y = 0; temp_y < 15; ++temp_y)
	{
		for (temp_x = 0; temp_x < 16; ++temp_x)
		{
			temp1 = (temp_y << 4) + temp_x;

			if (c_map[temp1])
			{
				if(c_map[temp1]==3)
				{
					vram_put(0x07); // water
					vram_put(0x07);	
				}
				if(c_map[temp1]==2)
				{
					vram_put(0x08); // wall2
					vram_put(0x08);	
				}
				if(c_map[temp1]==1)
				{
					vram_put(0x10); // wall
					vram_put(0x10);
				}
				
			}
			else
			{
				vram_put(0); // blank
				vram_put(0);
			}
		}

		// do twice
		for (temp_x = 0; temp_x < 16; ++temp_x)
		{
			temp1 = (temp_y << 4) + temp_x;

			if (c_map[temp1])
			{
				if(c_map[temp1]==3)
				{
					vram_put(0x07); // water
					vram_put(0x07);	
				}
				if(c_map[temp1]==2)
				{
					vram_put(0x08); // wall2
					vram_put(0x08);	
				}
				if(c_map[temp1]==1)
				{
					vram_put(0x10); // wall
					vram_put(0x10);
				}
				
			}
			else
			{
				vram_put(0); // blank
				vram_put(0);
			}
		}
	}

	ppu_on_all(); // turn on screen
}

void draw_sprites(void)
{
	++move_frames;
	if(move_frames > 16)
	{
		move_frames = 0;
	}
	// clear all sprites from sprite buffer
	oam_clear();

	// draw 1 metasprite

	switch(last_direction){
		case DOWN_MOVE:

			if(pad1 & PAD_DOWN) {
				if(move_frames < 8) {
					oam_meta_spr(player_x, player_y, PlayerSprDown);
				} else {
					oam_meta_spr(player_x, player_y, PlayerSprDownTwo);
				}	
			}
			oam_meta_spr(player_x, player_y, PlayerSprDown);
			
			break;
		case LEFT_MOVE:
			oam_meta_spr(player_x, player_y, PlayerSprLeft);
			break;
		case UP_MOVE:
			oam_meta_spr(player_x, player_y, PlayerSprUp);
			break;
		case RIGHT_MOVE:
			oam_meta_spr(player_x, player_y, PlayerSprRight);
			break;
		default:
			oam_meta_spr(player_x, player_y, PlayerSprUp);	
			break;
	}
	

	// // draw the x and y as sprites
	// oam_spr(20, 20, 0xfe, 1); // 0xfe = X
	// temp1 = (player_x & 0xff) >> 4;
	// // oam_spr(unsigned char x,unsigned char y,unsigned char chrnum,unsigned char attr);
	// oam_spr(28, 20, temp1, 1);
	// temp1 = (player_x & 0x0f);
	// oam_spr(30, 20, temp1, 1);

	// oam_spr(50, 20, 0xff, 1); // 0xff = Y
	// temp1 = (player_y & 0xff) >> 4;
	// oam_spr(58, 20, temp1, 1);
	// temp1 = (player_y & 0x0f);
	// oam_spr(62, 20, temp1, 1);
}

void movement(void)
{

	// move left/right
	if (pad1 & PAD_LEFT)
	{
		last_direction = LEFT_MOVE;
		player_x -= 1;
	}
	else if (pad1 & PAD_RIGHT)
	{
		last_direction = RIGHT_MOVE;
		player_x += 1;
	}

	// check left/right collisions
	bg_collision();
	if (collision_R)
	{
		player_x -= 1;
		if (player_x == SCREEN_RIGHT_EDGE)
			change_room_right();
	}

	if (collision_L)
	{
		player_x += 1;
		if (player_x == SCREEN_LEFT_EDGE)
			change_room_left();
	}

	// move up/down
	if (pad1 & PAD_UP)
	{
		last_direction = UP_MOVE;
		player_y -= 1;
		if (player_y == SCREEN_TOP_EDGE)
			change_room_up();
	}
	else if (pad1 & PAD_DOWN)
	{
		last_direction = DOWN_MOVE;
		player_y += 1;
		if (player_y == SCREEN_BOTTOM_EDGE)
			change_room_down();
	}

	//check collision up/down
	bg_collision();
	if (collision_D)
	{
		player_y -= 1;
		// if (player_y == SCREEN_BOTTOM_EDGE)
		// 	change_room_down();

		
	}
		
	if (collision_U)
	{
		player_y += 1;
		// if (player_y == SCREEN_TOP_EDGE)
		// 	change_room_up();

		
		
	}
		
}

void bg_collision()
{
	// sprite collision with backgrounds
	// object expected to have first 4 bytes as x,y,width,height
	// casting to char* so this function could work for any sized structs
	collision_L = 0;
	collision_R = 0;
	collision_U = 0;
	collision_D = 0;

	temp1 = player_x;							 // left side
	temp2 = temp1 + player_width;	 // right side
	temp3 = player_y;							 // top side
	temp4 = temp3 + player_height; // bottom side

	if (temp3 >= 0xf0)
		return;
	// y out of range

	coordinates = (temp1 >> 4) + (temp3 & 0xf0); // upper left
	if (c_map[coordinates])
	{ // find a corner in the collision map
		++collision_L;
		++collision_U;
	}

	coordinates = (temp2 >> 4) + (temp3 & 0xf0); // upper right
	if (c_map[coordinates])
	{
		++collision_R;
		++collision_U;
	}

	if (temp4 >= 0xf0)
		return;
	// y out of range

	coordinates = (temp1 >> 4) + (temp4 & 0xf0); // bottom left
	if (c_map[coordinates])
	{
		++collision_L;
		++collision_D;
	}

	coordinates = (temp2 >> 4) + (temp4 & 0xf0); // bottom right
	if (c_map[coordinates])
	{
		++collision_R;
		++collision_D;
	}
}

// rooms like:
//  c4  c3
//  c1  c2
// which_bg is 0 index, sorry

void change_room_right()
{
	player_x = SCREEN_LEFT_EDGE;
	if(which_bg == 3)
	{
		which_bg = 2;
	}
	if (which_bg == 0)
	{
		which_bg = 1;
	}
	
	draw_bg();
}

void change_room_left()
{
	player_x = SCREEN_RIGHT_EDGE;
	if(which_bg == 2)
	{
		which_bg = 3;
	}
	if (which_bg == 1)
	{
		which_bg = 0;
	}
	draw_bg();
}

void change_room_up()
{
	
	player_y = SCREEN_BOTTOM_EDGE;
	if(which_bg == 0)
	{
		which_bg = 3;
	}
	if(which_bg == 1)
	{
		which_bg = 2;
	}
	draw_bg();
}

void change_room_down()
{
	player_y = SCREEN_TOP_EDGE;
	if(which_bg == 3)
	{
		which_bg = 0;
	}
	if(which_bg == 2)
	{
		which_bg = 1;
	}
	draw_bg();
}

void load_title(void)
{
	// vram_adr(NTADR_A(x,y));
	vram_adr(NTADR_A(8, 14)); // screen is 32 x 30 tiles
	i = 0;
	while (title_text[i])
	{
		vram_put(title_text[i]); // this pushes 1 char to the screen
		++i;
	}

	i = 0;
	vram_adr(NTADR_A(10, 20)); // screen is 32 x 30 tiles
	i = 0;
	while (start_text[i])
	{
		vram_put(start_text[i]); // this pushes 1 char to the screen
		++i;
	}

	game_mode = MODE_TITLE;
}

void clear_title(void)
{
	vram_adr(NTADR_A(8, 14)); // screen is 32 x 30 tiles
	i = 0;
	while (title_text[i])
	{
		vram_put(' '); // this pushes 1 char to the screen
		++i;
	}
	i = 0;
	vram_adr(NTADR_A(10, 20)); // screen is 32 x 30 tiles
	i = 0;
	while (start_text[i])
	{
		vram_put(' '); // this pushes 1 char to the screen
		++i;
	}
}
