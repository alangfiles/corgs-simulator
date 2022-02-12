/*	example code for cc65, for NES
 *  move some sprites with the controllers
 *	using neslib
 *	Doug Fraker 2018
 */

#include "LIB/neslib.h"
#include "LIB/nesdoug.h"
#include "Sprites.h" // holds our metasprite data
#include "corgssim.h"
#include "Room1.h"

void main(void)
{

	ppu_off(); // screen off
	//comment

	// load the palettes
	pal_bg(palette_bg);
	pal_spr(palette_sp);

	set_vram_buffer(); // do at least once, sets a pointer to a buffer
	// use the second set of tiles for sprites
	// both bg and sprites are set to 0 by default
	bank_spr(1);

	set_scroll_y(0xff); //shift the bg down 1 pixel
	game_mode = MODE_TITLE;
	load_title(); // initial title load
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
				initialize_game();
				pal_bright(4); // back to normal brighness
			}
		}
		while (game_mode == MODE_GAME) //gameloop
		{
			++frame;
			ppu_wait_nmi(); // wait till beginning of the frame
			// the sprites are pushed from a buffer to the OAM during nmi

			pad1 = pad_poll(0);				 // read the first controller
			pad1_new = get_pad_new(0); // newly pressed button. do pad_poll first

			movement();
			item_detection();
			draw_sprites();
			if (frame == 60)
			{
				draw_timer();
				frame = 0;

				if (seconds_left_ones == 0)
				{
					seconds_left_ones = 9;
					if (seconds_left_tens == 0)
					{
						seconds_left_tens = 5;
						minutes_left -= 1;
					}
					else
					{
						seconds_left_tens -= 1;
					}
				}
				else
				{
					seconds_left_ones -= 1;
				}
			}
		}
		while (game_mode == MODE_END)
		{
			ppu_wait_nmi();			// wait till beginning of the frame
			pad1 = pad_poll(0); // read the first controller
			pad1_new = get_pad_new(0);
			if (pad1_new & PAD_START)
			{
				pal_fade_to(4, 0); // fade to black
				clear_end();
				draw_bg(); 

				game_mode = MODE_TITLE;
				load_title(); // initial title load
				which_bg = 0;
				player_x = 64;
				player_y = 80;

				pal_bright(4); // back to normal brighness
			}
		}  
	}
}

void draw_bg(void)
{

	oam_clear();
	ppu_off(); // screen off

	// p_maps = All_Collision_Maps[which_bg];
	// // copy the collision map to c_map
	// memcpy(c_map, p_maps, 240);

	switch (which_bg)
	{
	case 0:
		set_data_pointer(c1);
		memcpy(c_map, c1, 240);
		break;
	case 1:
		set_data_pointer(c2);
		memcpy(c_map, c2, 240);
		break;
	case 2:
		set_data_pointer(c3);
		memcpy(c_map, c3, 240);
		break;
	case 3:
		set_data_pointer(c4);
		memcpy(c_map, c4, 240);
		break;
	case 4:
		set_data_pointer(c5);
		memcpy(c_map, c5, 240);
		break;
	default:
		set_data_pointer(c5);
		memcpy(c_map, c5, 240);
		break;
	}
	set_mt_pointer(metatiles1);

	//draw the tiles
	for (y = 0;; y += 0x20)
	{
		for (x = 0;; x += 0x20)
		{
			address = get_ppu_addr(0, x, y);
			index = (y & 0xf0) + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			flush_vram_update2();
			if (x == 0xe0)
				break;
		}
		if (y == 0xe0)
			break;
	}

	//draw secret game
	if (which_bg == 1)
	{
		vram_adr(NTADR_A(8, 24)); // screen is 32 x 30 tiles
		vram_put('.');
		//player_x == 0x30 && player_y == 0xc0
	}
	else
	{
		vram_adr(NTADR_A(8, 24)); // screen is 32 x 30 tiles
		vram_put(' ');
	}
	draw_timer();
	ppu_on_all(); // turn on screen
}

void draw_sprites(void)
{
	++move_frames;
	if (move_frames > 16)
	{
		move_frames = 0;
	}
	// clear all sprites from sprite buffer
	oam_clear();

	// draw 1 metasprite

	switch (last_direction)
	{
	case DOWN_MOVE:

		if (pad1 & PAD_DOWN) //only animate if the button is pressed
		{
			if (move_frames > 8)
			{
				oam_meta_spr(player_x, player_y, PlayerSprDownTwo);
			}
			else
			{
				oam_meta_spr(player_x, player_y, PlayerSprDown);
			}
		}
		else //this is the idle non-moving sprite
		{
			oam_meta_spr(player_x, player_y, PlayerSprDown);
		}

		break;
	case LEFT_MOVE:
		if (pad1 & PAD_LEFT) //only animate if the button is pressed
		{
			if (move_frames > 8)
			{
				oam_meta_spr(player_x, player_y, PlayerSprLeftTwo);
			}
			else
			{
				oam_meta_spr(player_x, player_y, PlayerSprLeft);
			}
		}
		else //this is the idle non-moving sprite
		{
			oam_meta_spr(player_x, player_y, PlayerSprLeft);
		}

		break;
	case UP_MOVE:
		if (pad1 & PAD_UP) //only animate if the button is pressed
		{
			if (move_frames > 8)
			{
				oam_meta_spr(player_x, player_y, PlayerSprUpTwo);
			}
			else
			{
				oam_meta_spr(player_x, player_y, PlayerSprUp);
			}
		}
		else //this is the idle non-moving sprite
		{
			oam_meta_spr(player_x, player_y, PlayerSprUp);
		}
		break;
	case RIGHT_MOVE:
		if (pad1 & PAD_RIGHT) //only animate if the button is pressed
		{
			if (move_frames > 8)
			{
				oam_meta_spr(player_x, player_y, PlayerSprRightTwo);
			}
			else
			{
				oam_meta_spr(player_x, player_y, PlayerSprRight);
			}
		}
		else //this is the idle non-moving sprite
		{
			oam_meta_spr(player_x, player_y, PlayerSprRight);
		}
		break;
	default:
		oam_meta_spr(player_x, player_y, PlayerSprUp);
		break;
	}

	// // draw the x and y as sprites
	// oam_spr(24, 28, 0xfe, 1); // 0xfe = X
	// temp1 = (player_x & 0xff) >> 4;
	// // oam_spr(unsigned char x,unsigned char y,unsigned char chrnum,unsigned char attr);
	// oam_spr(32, 28, temp1, 1);
	// temp1 = (player_x & 0x0f);
	// oam_spr(32, 28, temp1, 1);

	// oam_spr(50, 28, 0xff, 1); // 0xff = Y
	// temp1 = (player_y & 0xff) >> 4;
	// oam_spr(58, 28, temp1, 1);
	// temp1 = (player_y & 0x0f);
	// oam_spr(62, 28, temp1, 1);

	// draw the x and y as sprites
	// oam_spr(20,20,0xfe,1); // 0xfe = X
	// temp1 = (scroll_x & 0xff) >> 4;
	// //oam_spr(unsigned char x,unsigned char y,unsigned char chrnum,unsigned char attr);
	// oam_spr(28,20,temp1,1);
	// temp1 = (scroll_x & 0x0f);
	// oam_spr(36,20,temp1,1);

	// oam_spr(50,20,0xff,1); // 0xff = Y
	// temp1 = (scroll_y & 0xff) >> 4;

	// oam_spr(58,20,temp1,1);
	// temp1 = (scroll_y & 0x0f);
	// oam_spr(66,20,temp1,1);
}

void item_detection(void)
{

	if (which_bg == 1 && player_y < 0xb8 + 0x08 && player_y >= 0xb8 - 0x08 && player_x < 0x3a + 0x08 && player_x >= 0x3a - 0x08 && ((pad1 & PAD_A) || (pad1 & PAD_B)))
	{
		load_end();
		game_mode = MODE_END;
	}
}

void movement(void)
{
	has_moved = 0;

	// move left/right
	if (pad1 & PAD_LEFT)
	{
		last_direction = LEFT_MOVE;
		player_x -= 1;
		has_moved = 1;
		if (player_x == SCREEN_LEFT_EDGE)
			change_room_left();
	}
	else if (pad1 & PAD_RIGHT)
	{
		last_direction = RIGHT_MOVE;
		player_x += 1;
		has_moved = 1;
		if (player_x == SCREEN_RIGHT_EDGE)
			change_room_right();
	}

	// check left/right collisions
	bg_collision();
	if (collision_R)
	{
		player_x -= 1;
	}

	if (collision_L)
	{
		player_x += 1;
	}

	// move up/down
	if (pad1 & PAD_UP && !has_moved)
	{
		last_direction = UP_MOVE;
		player_y -= 1;
		if (player_y == SCREEN_TOP_EDGE)
			change_room_up();
	}
	else if (pad1 & PAD_DOWN && !has_moved)
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
	if (c_map[coordinates] && c_map[coordinates] != 5)
	{ // find a corner in the collision map
		++collision_L;
		++collision_U;
	}

	coordinates = (temp2 >> 4) + (temp3 & 0xf0); // upper right
	if (c_map[coordinates] && c_map[coordinates] != 5)
	{
		++collision_R;
		++collision_U;
	}

	if (temp4 >= 0xf0)
		return;
	// y out of range

	coordinates = (temp1 >> 4) + (temp4 & 0xf0); // bottom left
	if (c_map[coordinates] && c_map[coordinates] != 5)
	{
		++collision_L;
		++collision_D;
	}

	coordinates = (temp2 >> 4) + (temp4 & 0xf0); // bottom right
	if (c_map[coordinates] && c_map[coordinates] != 5)
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
	player_x = PLAYER_LEFT_EDGE;
	if (which_bg == 3)
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
	player_x = PLAYER_RIGHT_EDGE;
	if (which_bg == 2)
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

	player_y = PLAYER_BOTTOM_EDGE;
	if (which_bg == 0)
	{
		which_bg = 3;
	}
	if (which_bg == 1)
	{
		which_bg = 2;
	}
	draw_bg();
}

void change_room_down()
{
	player_y = PLAYER_TOP_EDGE;
	if (which_bg == 3)
	{
		which_bg = 0;
	}
	if (which_bg == 2)
	{
		which_bg = 1;
	}
	draw_bg();
}

void initialize_game(void)
{
	player_x = 64;
	player_y = 80;

	minutes_left = 4;
	seconds_left_tens = 0;
	seconds_left_ones = 0;
}

void draw_timer(void)
{
	multi_vram_buffer_horz(items_text, sizeof(items_text), NTADR_A(2, 1));

	multi_vram_buffer_horz(clock_text, sizeof(clock_text), NTADR_A(2, 2));

	one_vram_buffer(48 + minutes_left, NTADR_A(23, 2));
	one_vram_buffer(':', NTADR_A(24, 2));
	one_vram_buffer(48 + seconds_left_tens, NTADR_A(25, 2));
	one_vram_buffer(48 + seconds_left_ones, NTADR_A(26, 2));
	//ppu_on_all();
}

void load_title(void)
{
	oam_clear();
	ppu_off();
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
	ppu_on_all();
}

void load_end(void)
{
	//move player off screen
	player_x = -4;
	player_y = -4;
	which_bg = 5; //set background to black
	draw_bg();
	oam_clear();
	ppu_off();
	// vram_adr(NTADR_A(x,y));
	vram_adr(NTADR_A(4, 14)); // screen is 32 x 30 tiles
	i = 0;
	while (end_text[i])
	{
		vram_put(end_text[i]); // this pushes 1 char to the screen
		++i;
	}

	i = 0;
	vram_adr(NTADR_A(3, 20)); // screen is 32 x 30 tiles
	i = 0;
	while (end_text2[i])
	{
		vram_put(end_text2[i]); // this pushes 1 char to the screen
		++i;
	}
	ppu_on_all();
}

void clear_end(void)
{
	vram_adr(NTADR_A(8, 14)); // screen is 32 x 30 tiles
	i = 0;
	while (end_text[i])
	{
		vram_put(' '); // this pushes 1 char to the screen
		++i;
	}

	i = 0;
	vram_adr(NTADR_A(10, 20)); // screen is 32 x 30 tiles
	i = 0;
	while (end_text2[i])
	{
		vram_put(' '); // this pushes 1 char to the screen
		++i;
	}
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
