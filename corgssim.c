/*	example code for cc65, for NES
 *  move some sprites with the controllers
 *	using neslib
 *	Doug Fraker 2018
 */

/*
2/28 todo list:
[] typewritter text stuff
[] multiple text lines (automatic wrapping?)
[] interaction areas (colision detection for things, could actually use a map for this?)
*/

#include "LIB/neslib.h"
#include "LIB/nesdoug.h"
#include "Sprites.h" // holds our metasprite data
#include "Talk.h"		 // holds our talking data
#include "corgssim.h"
#include "rooms_data.c"

void main(void)
{

	ppu_off(); // screen off
	// comment

	// load the palettes
	pal_bg(title_palette);
	pal_spr(palette_sp);

	set_vram_buffer(); // do at least once, sets a pointer to a buffer
	// use the second set of tiles for sprites
	// both bg and sprites are set to 0 by default
	bank_spr(1);
	set_scroll_y(0xff); // shift the bg down 1 pixel

	// setup title
	game_mode = MODE_TITLE;
	initialize_title_screen();
	ppu_on_all(); // turn on screen

	// game loop
	while (1)
	{
		// title screen
		while (game_mode == MODE_TITLE)
		{
			ppu_wait_nmi();

			// rotate colors
			temp1 = get_frame_count();
			temp1 = (temp1 >> 3) & 3;
			temp2 = temp1 + 1 & 3;
			// pal_col(6, title_color_rotate[temp1]);
			pal_col(5, title_color_rotate[temp2]);

			pad1 = pad_poll(0);
			pad1_new = get_pad_new(0);

			if (pad1_new & PAD_START)
			{
				// initialize game mode:
				pal_fade_to(4, 0); // fade to black
				ppu_off();

				// set defaults
				game_mode = MODE_GAME;
				player_x = 64;
				player_y = 120;

				minutes_left = 4;
				seconds_left_tens = 0;
				seconds_left_ones = 0;
				display_hud = 1;
				which_bg = 18;

				draw_bg();
				draw_hud();
				ppu_on_all();
				pal_bright(4); // back to normal brighness
			}
		}
		while (game_mode == MODE_GAME) // gameloop
		{
			ppu_wait_nmi();		 // wait till beginning of the frame
			countdown_timer(); // keep ticking the timer

			pad1 = pad_poll(0);				 // read the first controller
			pad1_new = get_pad_new(0); // newly pressed button. do pad_poll first

			movement();
			action();

			draw_sprites();

			// for debugging, the lower the line, the less processing we have
			gray_line();
		}
		while (game_mode == MODE_TALKING_TIME)
		{
			ppu_wait_nmi();		 // wait till beginning of the frame
			countdown_timer(); // keep ticking the timer

			temp1 = get_frame_count();
			temp1 = (temp1 >> 3);
			// if(temp1

			switch (text_to_use)
			{
			case TALK_ALAN:
				if (text_rendered != sizeof(alan_1) && temp1)
				{
					one_vram_buffer(alan_1[text_rendered], NTADR_A(2 + text_col, 3 + text_row));
					++text_col;
					if (text_col == 27)
					{
						++text_row;
						text_col = 0;
					}
					++text_rendered;
				}
				else
				{
					// render finished
					text_row = 0;
					text_col = 0;
					text_finished = 1;
				}
				break;
			case TALK_BRIAN:
				if (text_rendered != sizeof(brian_1) && temp1)
				{
					one_vram_buffer(brian_1[text_rendered], NTADR_A(2 + text_col, 3 + text_row));
					++text_col;
					if (text_col == 27)
					{
						++text_row;
						text_col = 0;
					}
					++text_rendered;
				}
				else
				{
					// render finished
					text_row = 0;
					text_col = 0;
					text_finished = 1;
				}
				break;
			case TALK_GUY:
				if (text_rendered != sizeof(guy_1) && temp1)
				{
					one_vram_buffer(guy_1[text_rendered], NTADR_A(2 + text_col, 3 + text_row));
					++text_col;
					if (text_col == 27)
					{
						++text_row;
						text_col = 0;
					}
					++text_rendered;
				}
				else
				{
					// render finished
					text_row = 0;
					text_col = 0;
					text_finished = 1;
				}
				break;
			case TALK_GAME:    
				if (text_rendered != sizeof(game_1) && temp1)
				{
					one_vram_buffer(game_1[text_rendered], NTADR_A(2 + text_col, 3 + text_row));
					++text_col;
					if (text_col == 27)
					{
						++text_row;
						text_col = 0;
					}
					++text_rendered;
				}
				else
				{
					// render finished
					text_row = 0;
					text_col = 0;
					text_finished = 1;
				}
				break;
			default:
				text_row = 0;
				text_col = 0;
				text_finished = 1;
				break;
			}

			pad1 = pad_poll(0);
			pad1_new = get_pad_new(0);

			if (pad1_new & PAD_B && text_finished == 1)
			{
				// back to game
				ppu_off();

				text_to_use = 0;
				text_row = 0;
				text_col = 0;
				game_mode = MODE_GAME;
				display_hud = 1;
				draw_bg();
				fade_out = 1;
				ppu_on_all();
			}
		}
		while (game_mode == MODE_END)
		{
			ppu_wait_nmi(); // wait till beginning of the frame

			pad1 = pad_poll(0);
			pad1_new = get_pad_new(0);

			if (pad1_new & PAD_START)
			{
				initialize_title_screen(); // initial title load
			}
		}
	}
}

void draw_bg(void)
{
	if (fade_out == 1)
	{
		pal_fade_to(4, 0); // fade to black
	}

	ppu_off();	 // screen off
	oam_clear(); // clear all sprites

	set_mt_pointer(room_metatile_list[which_bg - 1]);
	pal_bg(room_palette_list[which_bg - 1]);
	set_data_pointer(room_list[which_bg - 1]);
	memcpy(c_map, room_list[which_bg - 1], 240);

	// draw the tiles
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

	// draw secret game
	// if (which_bg == 2)
	// {
	// 	vram_adr(NTADR_A(8, 24)); // screen is 32 x 30 tiles
	// 	vram_put('.');
	// 	// player_x == 0x30 && player_y == 0xc0
	// }

	if (display_hud == 1)
	{
		draw_hud();
	}

	initialize_sprites();

	initialize_talk_map();

	draw_timer(); // draw timer on screen transitions

	ppu_on_all(); // turn on screen

	if (fade_out == 1)
	{
		pal_fade_to(0, 4); // fade to black
	}
}

void initialize_talk_map(void)
{
	for (index = 0; index < MAX_ROOM_TALKING; ++index)
	{
		talk_type[index] = TURN_OFF;
	}
 
	pointer = sprite_list[which_bg - 1];
	for (index = 0, index2 = 0; index < MAX_ROOM_SPRITES; ++index)
	{  
		temp1 = pointer[index2]; // get a byte of data
		if (temp1 == TURN_OFF)
			break; //<--- if we reached the end of list we break

		// otherwise we load the 3 bytes into the correct arrays
		talk_x[index] = temp1;

		++index2;
		temp1 = pointer[index2]; // get 2nd byte of data (y pos)
		talk_y[index] = temp1;

		++index2;
		temp1 = pointer[index2]; // get 3rd byte of data (type_enum)
		talk_type[index] = temp1;

		++index2; // get the next byte (either an xpos or the TURN_OFF (0xff))
	}
}

void initialize_sprites(void)
{
	// set all sprite types to off
	//  we'll check this in our rendering loop to figure it we want to display a sprite
	for (index = 0; index < MAX_ROOM_SPRITES; ++index)
	{
		sprites_type[index] = TURN_OFF;
	}

	pointer = sprite_list[which_bg - 1];
	for (index = 0, index2 = 0; index < MAX_ROOM_SPRITES; ++index)
	{

		// the bytes of data in the sprite list go:
		//  x, y, sprite_type_enum
		//  and the list ends with a 0xff

		temp1 = pointer[index2]; // get a byte of data
		if (temp1 == TURN_OFF)
			break; //<--- if we reached the end of list we break

		// otherwise we load the 3 bytes into the correct arrays
		sprites_x[index] = temp1;

		++index2;
		temp1 = pointer[index2]; // get 2nd byte of data (y pos)

		sprites_y[index] = temp1;

		++index2;
		temp1 = pointer[index2]; // get 3rd byte of data (type_enum)
		sprites_type[index] = temp1;

		++index2; // get the next byte (either an xpos or the TURN_OFF (0xff))
	}
}

void draw_sprites(void)
{

	++move_frames;
	if (move_frames > 64)
	{
		move_frames = 0;
	}
	// clear all sprites from sprite buffer
	oam_clear();

#pragma region drawplayer
	switch (player_direction)
	{
	case DOWN_MOVE:

		if (pad1 & PAD_DOWN) // only animate if the button is pressed
		{
			if (move_frames >= 56)
			{
				oam_meta_spr(player_x, player_y, PlayerSprDown);
			}
			else if (move_frames >= 48 & move_frames < 56)
			{
				oam_meta_spr(player_x, player_y, PlayerSprDownThree);
			}
			else if (move_frames >= 40 & move_frames < 48)
			{
				oam_meta_spr(player_x, player_y, PlayerSprDown);
			}
			else if (move_frames >= 32 & move_frames < 40)
			{
				oam_meta_spr(player_x, player_y, PlayerSprDownTwo);
			}
			else if (move_frames >= 24 & move_frames < 32)
			{
				oam_meta_spr(player_x, player_y, PlayerSprDown);
			}
			else if (move_frames >= 16 & move_frames < 24)
			{
				oam_meta_spr(player_x, player_y, PlayerSprDownThree);
			}
			else if (move_frames >= 8 & move_frames < 16)
			{
				oam_meta_spr(player_x, player_y, PlayerSprDown);
			}
			else if (move_frames < 8)
			{
				oam_meta_spr(player_x, player_y, PlayerSprDownTwo);
			}
		}
		else // this is the idle non-moving sprite
		{
			oam_meta_spr(player_x, player_y, PlayerSprDown);
		}

		break;
	case LEFT_MOVE:
		if (pad1 & PAD_LEFT) // only animate if the button is pressed
		{
			if (move_frames >= 56)
			{
				oam_meta_spr(player_x, player_y, PlayerSprLeft);
			}
			else if (move_frames >= 48 & move_frames < 56)
			{
				oam_meta_spr(player_x, player_y, PlayerSprLeftFour);
			}
			else if (move_frames >= 40 & move_frames < 48)
			{
				oam_meta_spr(player_x, player_y, PlayerSprLeftFive);
			}
			else if (move_frames >= 32 & move_frames < 40)
			{
				oam_meta_spr(player_x, player_y, PlayerSprLeftFour);
			}
			else if (move_frames >= 24 & move_frames < 32)
			{
				oam_meta_spr(player_x, player_y, PlayerSprLeft);
			}
			else if (move_frames >= 16 & move_frames < 24)
			{
				oam_meta_spr(player_x, player_y, PlayerSprLeftTwo);
			}
			else if (move_frames >= 8 & move_frames < 16)
			{
				oam_meta_spr(player_x, player_y, PlayerSprLeftThree);
			}
			else if (move_frames < 8)
			{
				oam_meta_spr(player_x, player_y, PlayerSprLeftTwo);
			}
		}
		else // this is the idle non-moving sprite
		{
			oam_meta_spr(player_x, player_y, PlayerSprLeft);
		}

		break;
	case UP_MOVE:
		if (pad1 & PAD_UP) // only animate if the button is pressed
		{
			if (move_frames >= 56)
			{
				oam_meta_spr(player_x, player_y, PlayerSprUp);
			}
			else if (move_frames >= 48 & move_frames < 56)
			{
				oam_meta_spr(player_x, player_y, PlayerSprUpThree);
			}
			else if (move_frames >= 40 & move_frames < 48)
			{
				oam_meta_spr(player_x, player_y, PlayerSprUp);
			}
			else if (move_frames >= 32 & move_frames < 40)
			{
				oam_meta_spr(player_x, player_y, PlayerSprUpTwo);
			}
			else if (move_frames >= 24 & move_frames < 32)
			{
				oam_meta_spr(player_x, player_y, PlayerSprUp);
			}
			else if (move_frames >= 16 & move_frames < 24)
			{
				oam_meta_spr(player_x, player_y, PlayerSprUpThree);
			}
			else if (move_frames >= 8 & move_frames < 16)
			{
				oam_meta_spr(player_x, player_y, PlayerSprUp);
			}
			else if (move_frames < 8)
			{
				oam_meta_spr(player_x, player_y, PlayerSprUpTwo);
			}
		}
		else // this is the idle non-moving sprite
		{
			oam_meta_spr(player_x, player_y, PlayerSprUp);
		}
		break;
	case RIGHT_MOVE:
		if (pad1 & PAD_RIGHT) // only animate if the button is pressed
		{
			if (move_frames >= 56)
			{
				oam_meta_spr(player_x, player_y, PlayerSprRight);
			}
			else if (move_frames >= 48 & move_frames < 56)
			{
				oam_meta_spr(player_x, player_y, PlayerSprRightFour);
			}
			else if (move_frames >= 40 & move_frames < 48)
			{
				oam_meta_spr(player_x, player_y, PlayerSprRightFive);
			}
			else if (move_frames >= 32 & move_frames < 40)
			{
				oam_meta_spr(player_x, player_y, PlayerSprRightFour);
			}
			else if (move_frames >= 24 & move_frames < 32)
			{
				oam_meta_spr(player_x, player_y, PlayerSprRight);
			}
			else if (move_frames >= 16 & move_frames < 24)
			{
				oam_meta_spr(player_x, player_y, PlayerSprRightTwo);
			}
			else if (move_frames >= 8 & move_frames < 16)
			{
				oam_meta_spr(player_x, player_y, PlayerSprRightThree);
			}
			else if (move_frames < 8)
			{
				oam_meta_spr(player_x, player_y, PlayerSprRightTwo);
			}
		}
		else // this is the idle non-moving sprite
		{
			oam_meta_spr(player_x, player_y, PlayerSprRight);
		}
		break;
	default:
		oam_meta_spr(player_x, player_y, PlayerSprUp);
		break;
	}
#pragma endregion drawplayer

	if (shot_x >= 0)
	{ // only draw the shot if it exists
		oam_meta_spr(shot_x, shot_y, Shot);
	}

#pragma region room_sprites
	// offset code is for shuffling sprites if we have more than 8
	offset = get_frame_count() & 3;
	offset = offset << 4; // * 16, the size of the shuffle array
	for (index = 0; index < MAX_ROOM_SPRITES; ++index)
	{
		index2 = shuffle_array[offset];
		++offset;
		//index2 = index; // <-- shortcut to keep the shuffling code in if we need it

		if (sprites_type[index2] == TURN_OFF)
			continue; // we found an empty spot

		temp_y = sprites_y[index2];

		temp_x = sprites_x[index2];

		// this will be inefficient, look into it if we need to
		//  the whole idea behind having sprites_type and sprites_anim is
		//  to have different anim frames, which we might want.
		if (sprites_type[index2] == SPRITE_ALAN)
		{
			sprites_anim[index2] = Alan;
		}
		if (sprites_type[index2] == SPRITE_BRIAN)
		{
			sprites_anim[index2] = Brian;
		}
		if (sprites_type[index2] == SPRITE_SHOPKEEPER)
		{
			sprites_anim[index2] = Shopkeeper;
		}
		if (sprites_type[index2] == SPRITE_GUY1)
		{
			sprites_anim[index2] = guy1;
		}

		oam_meta_spr(temp_x, temp_y, sprites_anim[index2]);
	}
#pragma endregion room_sprites
	// // draw non player sprites:
	// if (which_bg == 0)
	// {
	// 	oam_meta_spr(100, 70, Shopkeeper);
	// }

	// if (which_bg == 1)
	// {
	// 	oam_meta_spr(40, 70, ShopkeeperTwo);
	// 	oam_meta_spr(180, 160, Brian);
	// 	oam_meta_spr(200, 160, Alan);
	// }
	// if (which_bg == 18)
	// {
	// 	// oam_meta_spr(40, 70, ShopkeeperTwo);
	// 	oam_meta_spr(112, 80, Brian);
	// 	oam_meta_spr(128, 80, Alan);
	// 	//oam_meta_spr(112, 80, guy1);
	// 	// oam_meta_spr(50, 40, peopletest_2_data);
	// 	// oam_meta_spr(70, 60, peopletest_3_data);
	// 	// oam_meta_spr(90, 70, peopletest_4_data);
	// 	// oam_meta_spr(150, 150, peopletest_5_data);
	// 	// oam_meta_spr(100, 100, peopletest_5_data);
	// }
}

void action(void)
{
	// check for shots
	if (pad1_new & PAD_A)
	{
		// the shot starts where the player is and moves in the direction
		// the player was facing when they shot.
		shot_x = player_x;
		shot_y = player_y;
		shot_direction = player_direction;
	}

	// zelda push block
	//  if (push_timer > 100)
	//  {
	//  	action_collision();
	//  	if (collision_action == 2)
	//  	{
	//  		// block is at x112, y160
	//  		index = (160 & 0xf0) + (112 >> 4); // hardcoded block location
	//  		// replace block and fix c_map
	//  		c_map[index] = 0; // set it to 0
	//  		address = get_ppu_addr(0, 112, 160);
	//  		buffer_1_mt(address, 49);
	//  		push_timer = 0;
	//  		block_moved = 1;
	//  	}

	// 	// if(collision_action == 2){ // push block
	// 	// 	buffer_1_mt(NTADR_A(8,11),0);
	// 	// }
	// }

	// check for interactable
	if (pad1_new & PAD_B)
	{
		action_collision();

		if (collision_action != TURN_OFF)
		{
			text_to_use = collision_action;
			draw_talking();
		}
	}
}

void movement(void)
{
#pragma region playerMovement
	has_moved = 0;

	last_player_direction = player_direction;
	// move left/right
	if (pad1 & PAD_LEFT)
	{
		player_direction = LEFT_MOVE;
		player_x -= 1;
		has_moved = 1;
		if (player_x == SCREEN_LEFT_EDGE)
			change_room_left();
	}
	else if (pad1 & PAD_RIGHT)
	{
		player_direction = RIGHT_MOVE;
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
		player_direction = UP_MOVE;
		player_y -= 1;
		if (player_y == SCREEN_TOP_EDGE)
			change_room_up();
	}
	else if (pad1 & PAD_DOWN && !has_moved)
	{
		player_direction = DOWN_MOVE;
		player_y += 1;
		if (player_y == SCREEN_BOTTOM_EDGE)
			change_room_down();
	}

	// check collision up/down
	bg_collision();
	if (collision_D)
	{
		player_y -= 1;
	}

	if (collision_U)
	{
		player_y += 1;
	}

	if (player_direction == last_player_direction // player direction hasn't changed
			&& (pad1 & PAD_ALL_DIRECTIONS))						// one of the direction buttons is held down
	{
		++push_timer;
	}
	else
	{
		push_timer = 0;
	}

	if (block_moved &&
			player_x > 104 && player_x < 120 && player_y > 144 && player_y < 160)
	{
		which_bg = 6; // underground
		player_x = 48;
		player_y = 64;
		block_moved = 0;
		draw_bg();
	}

#pragma endregion playerMovement

#pragma region shotMovement
	if (shot_x >= 0) // if there's a shot, update it's direction
	{
		switch (shot_direction)
		{
		case 0: // down
			shot_y += 2;
			break;
		case 1: // left
			shot_x -= 2;
			break;
		case 2: // up
			shot_y -= 2;
			break;
		case 3: // right
			shot_x += 2;
			break;
		default:
			break;
		}

		// if it's offscreen, get rid of it.
		if (shot_x > 250 || shot_x < 1 ||
				shot_y > 255 || shot_y < 32)
		{
			shot_x = -4;
			shot_y = -4;
		}
	}
#pragma endregion shotMovement
}

void action_collision()
{
	collision_action = TURN_OFF;
	// this code gets where the player is
	temp1 = player_x;							 // left side
	temp2 = temp1 + player_width;	 // right side
	temp3 = player_y;							 // top side
	temp4 = temp3 + player_height; // bottom side

	// adujst the interaction box in front of the player
	// so now temp1 - 4 show where the interaction box is.
	// player_direction
	// we add a buffer to all of these so that the interaction
	// box is a little bigger
	switch (player_direction)
	{ // 0 = down, 1 = left, 2 = up, 3 = right
	case 0: 
		temp3 = temp3 + ACTION_HEIGHT + ACTION_BUFFER;
		temp4 = temp4 + ACTION_HEIGHT + ACTION_BUFFER;
		break;
	case 1:
		temp1 = temp1 - ACTION_WIDTH - ACTION_BUFFER;
		temp2 = temp2 - ACTION_WIDTH - ACTION_BUFFER;
		break;
	case 2:
		temp3 = temp3 - ACTION_HEIGHT - ACTION_BUFFER;
		temp4 = temp4 - ACTION_HEIGHT - ACTION_BUFFER;
		break;
	case 3:
		temp1 = temp1 + ACTION_WIDTH + ACTION_BUFFER;
		temp2 = temp2 + ACTION_WIDTH + ACTION_BUFFER;
		break;
	default:  
		break;
	}

	for (index = 0; index < MAX_ROOM_TALKING; ++index)
	{
		temp5 = talk_x[index];
		if(temp5 == TURN_OFF){
			break;
		}

		if (temp1 < temp5 && temp5 < temp2)
		{

			temp6 = talk_y[index];
			if (temp3 < temp6 && temp6 < temp4)
			{
				collision_action = talk_type[index];
				return;
			}
		}
	}

	// todo: see if it's interacting with anything in the current room
}

void bg_collision(void)
{
	// load the object's x,y,width,height to Generic, then call this

	collision_L = 0;
	collision_R = 0;
	collision_U = 0;
	collision_D = 0;

	if (player_y >= 0xf0)
		return;

	temp6 = temp5 = player_x;
	temp1 = temp5 & 0xff; // low byte x
	temp2 = temp5 >> 8;		// high byte x

	eject_L = temp1 | 0xf0;

	temp3 = player_y; // y top

	eject_U = temp3 | 0xf0;

	// if(L_R_switch) temp3 += 2; // fix bug, walking through walls

	bg_collision_sub();

	if (collision & COL_ALL)
	{ // find a corner in the collision map
		++collision_L;
		++collision_U;
	}

	// upper right
	temp5 += player_width;
	temp1 = temp5 & 0xff; // low byte x
	temp2 = temp5 >> 8;		// high byte x

	eject_R = (temp1 + 1) & 0x0f;

	// temp3 is unchanged
	bg_collision_sub();

	if (collision & COL_ALL)
	{ // find a corner in the collision map
		++collision_R;
		++collision_U;
	}

	// again, lower

	// bottom right, x hasn't changed

	temp3 = player_y + player_height; // y bottom
	// if(L_R_switch) temp3 -= 2; // fix bug, walking through walls
	eject_D = (temp3 + 1) & 0x0f;
	if (temp3 >= 0xf0)
		return;

	bg_collision_sub();

	if (collision & COL_ALL)
	{ // find a corner in the collision map
		++collision_R;
	}
	if (collision & COL_ALL)
	{ // find a corner in the collision map
		++collision_D;
	}

	// bottom left
	temp1 = temp6 & 0xff; // low byte x
	temp2 = temp6 >> 8;		// high byte x

	// temp3, y is unchanged

	bg_collision_sub();

	if (collision & COL_ALL)
	{ // find a corner in the collision map
		++collision_L;
	}
	if (collision & COL_ALL)
	{ // find a corner in the collision map
		++collision_D;
	}

	if ((temp3 & 0x0f) > 3)
		collision_D = 0; // for platforms, only collide with the top 3 pixels
}

void bg_collision_sub(void)
{
	coordinates = (temp1 >> 4) + (temp3 & 0xf0);

	collision = c_map[coordinates];

	// look in the colision list to see if this collision colides.
	collision = collision_list[which_bg - 1][collision];
}

/**
 * change_room_x
 *
 * the map is a big 5x10 grid with each room numbers
 *  1 2 3 4 5
 *  6 7 8 9 10 etc
 *  . . . . .
 *
 * so the movement is +1(right), -1(left), +5(up), -5(down)
 */

void change_room_right()
{
	player_x = PLAYER_LEFT_EDGE;
	++which_bg;

	draw_bg();
}

void change_room_left()
{
	player_x = PLAYER_RIGHT_EDGE;
	--which_bg;

	draw_bg();
}

void change_room_up()
{
	player_y = PLAYER_BOTTOM_EDGE;
	which_bg = which_bg - 5;
	draw_bg();

	// if (which_bg == 6) // special zelda block stuff
	// {
	// 	which_bg = 4;
	// 	player_x = 130;
	// 	player_y = 160;
	// }
}

void change_room_down()
{
	player_y = PLAYER_TOP_EDGE;
	which_bg = which_bg + 5;
	draw_bg();
}

void countdown_timer(void)
{
	++frame;

	if (frame == 60)
	{
		frame = 0;
		// nes is bad at mul and div math, so just doing counting for clock.
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

		// update the vram_buffer values only every 60 frames
		draw_timer();
	}
}

void draw_timer(void)
{
	if (game_mode == MODE_GAME)
	{
		one_vram_buffer(48 + minutes_left, NTADR_A(23, 3));
		one_vram_buffer(':', NTADR_A(24, 3));
		one_vram_buffer(48 + seconds_left_tens, NTADR_A(25, 3));
		one_vram_buffer(48 + seconds_left_ones, NTADR_A(26, 3));
	}
}

void draw_hud(void)
{
	// multi_vram_buffer_horz(items_text, sizeof(items_text), NTADR_A(2, 1));
	// multi_vram_buffer_horz(clock_text, sizeof(clock_text), NTADR_A(2, 2));

	// todo map:
	one_vram_buffer('-', NTADR_A(2, 4));
	one_vram_buffer('M', NTADR_A(3, 4));
	one_vram_buffer('A', NTADR_A(4, 4));
	one_vram_buffer('P', NTADR_A(5, 4));
	one_vram_buffer('-', NTADR_A(6, 4));

	// draw buttons B
	one_vram_buffer(0xee, NTADR_A(B_LOC, 2));
	one_vram_buffer('B', NTADR_A(B_LOC + 1, 2));
	one_vram_buffer(0xef, NTADR_A(B_LOC + 2, 2));

	one_vram_buffer(0xfd, NTADR_A(B_LOC, 3));
	one_vram_buffer(0x0, NTADR_A(B_LOC + 1, 3));
	one_vram_buffer(0xfd, NTADR_A(B_LOC + 2, 3));
	one_vram_buffer(0xfd, NTADR_A(B_LOC, 4));
	one_vram_buffer(0x0, NTADR_A(B_LOC + 1, 4));
	one_vram_buffer(0xfd, NTADR_A(B_LOC + 2, 4));
	one_vram_buffer(0xfd, NTADR_A(B_LOC, 5));
	one_vram_buffer(0x0, NTADR_A(B_LOC + 1, 5));
	one_vram_buffer(0xfd, NTADR_A(B_LOC + 2, 5));
	one_vram_buffer(0xfe, NTADR_A(B_LOC, 6));
	one_vram_buffer(0xed, NTADR_A(B_LOC + 1, 6));
	one_vram_buffer(0xff, NTADR_A(B_LOC + 2, 6));

	// draw buttons A
	one_vram_buffer(0xee, NTADR_A(A_LOC, 2));
	one_vram_buffer('A', NTADR_A(A_LOC + 1, 2));
	one_vram_buffer(0xef, NTADR_A(A_LOC + 2, 2));
	one_vram_buffer(0xfd, NTADR_A(A_LOC, 3));
	one_vram_buffer(0x0, NTADR_A(A_LOC + 1, 3));
	one_vram_buffer(0xfd, NTADR_A(A_LOC + 2, 3));
	one_vram_buffer(0xfd, NTADR_A(A_LOC, 4));
	one_vram_buffer('$', NTADR_A(A_LOC + 1, 4));
	one_vram_buffer(0xfd, NTADR_A(A_LOC + 2, 4));
	one_vram_buffer(0xfd, NTADR_A(A_LOC, 5));
	one_vram_buffer(0x0, NTADR_A(A_LOC + 1, 5));
	one_vram_buffer(0xfd, NTADR_A(A_LOC + 2, 5));
	one_vram_buffer(0xfe, NTADR_A(A_LOC, 6));
	one_vram_buffer(0xed, NTADR_A(A_LOC + 1, 6));
	one_vram_buffer(0xff, NTADR_A(A_LOC + 2, 6));

	// draw timer
	one_vram_buffer('-', NTADR_A(22, 2));
	one_vram_buffer('T', NTADR_A(23, 2));
	one_vram_buffer('I', NTADR_A(24, 2));
	one_vram_buffer('M', NTADR_A(25, 2));
	one_vram_buffer('E', NTADR_A(26, 2));
	one_vram_buffer('-', NTADR_A(27, 2));
}

void draw_talking(void)
{
	// writes to the HUD area
	ppu_off();
	display_hud = 0;
	game_mode = MODE_TALKING_TIME;
	fade_out = 0;
	draw_bg();

	multi_vram_buffer_horz(topBar, sizeof(topBar), NTADR_A(1, 2));
	multi_vram_buffer_horz(bottomBar, sizeof(bottomBar), NTADR_A(1, 6));

	one_vram_buffer(0xfd, NTADR_A(1, 3));
	one_vram_buffer(0xfd, NTADR_A(1, 4));
	one_vram_buffer(0xfd, NTADR_A(1, 5));
	one_vram_buffer(0xfd, NTADR_A(30, 3));
	one_vram_buffer(0xfd, NTADR_A(30, 4));
	one_vram_buffer(0xfd, NTADR_A(30, 5));

	text_rendered = 0;
	text_finished = 0;

	ppu_on_all();
}

void initialize_title_screen(void)
{
	game_mode = MODE_TITLE;
	which_bg = 1;

	ppu_off();
	oam_clear();
	draw_bg();

	multi_vram_buffer_horz(title_text, sizeof(title_text), NTADR_A(11, 17));
	multi_vram_buffer_horz(start_text, sizeof(start_text) - 1, NTADR_A(10, 20));

	ppu_on_all();
}

void initialize_end_screen(void)
{
	pal_fade_to(4, 0); // fade to black
	ppu_off();
	oam_clear();
	oam_hide_rest();
	// move player off screen
	player_x = -4;
	player_y = -4;
	shot_x = -4;
	shot_y = -4;
	game_mode = MODE_END;

	which_bg = 5; // set background to black
	draw_bg();

	multi_vram_buffer_horz(jeqb_text, sizeof(jeqb_text), NTADR_A(4, 14));
	multi_vram_buffer_horz(end_text2, sizeof(end_text2) - 1, NTADR_A(3, 20));

	ppu_on_all();
	pal_bright(4); // back to normal brighness
}