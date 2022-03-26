/*	example code for cc65, for NES
 *  move some sprites with the controllers
 *	using neslib
 *	Doug Fraker 2018
 */

/*
todo list:
[] fix char size/aligning
[] add in sounds
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
				which_bg = STARTING_ROOM;

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
			// the following code draws 1 char per frame.
			ppu_wait_nmi();		 // wait till beginning of the frame
			countdown_timer(); // keep ticking the timer

			// temp1 = get_frame_count();
			// temp1 = (temp1 >> 3);

			// draw text
			if (text_rendered != text_length && text_row < 3)
			{
				one_vram_buffer(pointer[text_rendered], NTADR_A(2 + text_col, 3 + text_row));
				++text_col;

				if (text_col == 27) // wrap to next row
				{
					++text_row;
					text_col = 0;
				}
				++text_rendered;
			}
			if (text_row == 3)
			{
				// draw last character as down arrow
				//'&' is used in the chr as the down caret
				one_vram_buffer('&', NTADR_A(15, 6));
			}

			pad1 = pad_poll(0);
			pad1_new = get_pad_new(0);

			if (pad1_new & PAD_B)
			{

				if (text_row == 3)
				{
					// clear the old text
					draw_talking();
					draw_sprites();
					// set text_row to 0
					text_row = 0;
				}

				if ((text_rendered == text_length)) // text finished, go back to game
				{
					ppu_off();

					// reset values
					text_rendered = 0;
					text_row = 0;
					text_col = 0;
					game_mode = MODE_GAME;

					display_hud = 1; // draw the hud
					draw_bg();
					fade_out = 1; // turn back on room fading
					ppu_on_all();
				}
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

	set_mt_pointer(room_metatile_list[which_bg]);
	pal_bg(room_palette_list[which_bg]);
	set_data_pointer(room_list[which_bg]);
	memcpy(c_map, room_list[which_bg], 240);

	// dungeon only
	if (which_bg == 5)
	{
		// I figure I can change the palette here to get
		// gray bricks, but I can't figure it out.
		// block 19 use bg palette 1, so it should be 4,5,6,7
		//pal_col(4, 0x2d);//<-- not changes for bg tile
		//0x0f,0x2d,0x00,0x20,//
		pal_col(5, 0x00);
		pal_col(6, 0x30);
		pal_col(7, 0x20);
	}

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

	pointer = talk_list[which_bg];
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

	pointer = sprite_list[which_bg];
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
		// index2 = index; // <-- shortcut to keep the shuffling code in if we need it

		if (sprites_type[index2] == TURN_OFF)
			continue; // we found an empty spot

		temp1 = sprites_x[index2]; // temp_x value
		temp2 = sprites_y[index2]; // temp_y value

		//  the whole idea behind having sprites_type and sprites_anim is
		//  to have different anim frames, which we might want.
		switch (sprites_type[index2])
		{
		case SPRITE_ALAN92:
			// we could do somethign here like:
			//  if frame 1 - 8 use AlanAnim1
			//  else use AlanAnim2
			sprites_anim[index2] = Alan92;
			break;
		case SPRITE_BRIAN93:
			sprites_anim[index2] = Brian93;
			break;
		case SPRITE_PlayerSprUp:
			sprites_anim[index2] = PlayerSprUp;
			break;
		case SPRITE_PunchoutMan112:
			sprites_anim[index2] = PunchoutMan112;
			break;
		case SPRITE_PunchOutMat113:
			sprites_anim[index2] = PunchOutMat113;
			break;
		case SPRITE_LunchLadyHead36:
			sprites_anim[index2] = LunchLadyHead36;
			break;
		case SPRITE_BaldRight22:
			sprites_anim[index2] = BaldRight22;
			break;
		case SPRITE_HairForward114:
			sprites_anim[index2] = HairForward114;
			break;
		case SPRITE_Banner99:
			sprites_anim[index2] = Banner99;
			break;
		case SPRITE_BoyKid42:
			sprites_anim[index2] = BoyKid42;
			break;
		case SPRITE_BaldBehind7:
			sprites_anim[index2] = BaldBehind7;
			break;
		case SPRITE_SkirtLady39:
			sprites_anim[index2] = SkirtLady39;
			break;
		case SPRITE_HairBehind10:
			sprites_anim[index2] = HairBehind10;
			break;
		case SPRITE_HatForward17:
			sprites_anim[index2] = HatForward17;
			break;
		case SPRITE_PrettyGirlBehindStand109:
			sprites_anim[index2] = PrettyGirlBehindStand109;
			break;
		case SPRITE_SideLadyRight86:
			sprites_anim[index2] = SideLadyRight86;
			break;
		case SPRITE_WideBoyBehind120:
			sprites_anim[index2] = WideBoyBehind120;
			break;
		case SPRITE_SleepyGuyBehind123:
			sprites_anim[index2] = SleepyGuyBehind123;
			break;
		case SPRITE_BackTV101:
			sprites_anim[index2] = BackTV101;
			break;
		case SPRITE_HairRight27:
			sprites_anim[index2] = HairRight27;
			break;
		case SPRITE_BigNoseLeft84:
			sprites_anim[index2] = BigNoseLeft84;
			break;
		case SPRITE_Wizard53:
			sprites_anim[index2] = Wizard53;
			break;
		case SPRITE_Car95:
			sprites_anim[index2] = Car95;
			break;
		case SPRITE_Car96:
			sprites_anim[index2] = Car96;
			break;
		default:
			break;
		}

		oam_meta_spr(temp1, temp2, sprites_anim[index2]);
	}
#pragma endregion room_sprites
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

	// dungeon push block
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
			// draw the talking dialog
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

	// if (block_moved &&
	// 		player_x > 104 && player_x < 120 && player_y > 144 && player_y < 160)
	// {
	// 	which_bg = 6; // underground
	// 	player_x = 48;
	// 	player_y = 64;
	// 	block_moved = 0;
	// 	draw_bg();
	// }

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

#pragma region specialCases

	// dungeon block
	if ( // block_moved &&
			which_bg == DUNGEON_BLOCK_ROOM && player_x > DUNGEON_BLOCK_X - 4 && player_x < DUNGEON_BLOCK_X + 4 && player_y > DUNGEON_BLOCK_Y - 4 && player_y < DUNGEON_BLOCK_Y + 4)
	{
		which_bg = 5; // underground
		player_x = 48;
		player_y = 64;
		block_moved = 0;
		draw_bg();
	}
	// index = (DUNGEON_BLOCK_Y & 0xf0) + (DUNGEON_BLOCK_X >> 4);
	// temp1 = (player_y & 0xf0 + player_x >> 4);
	// if (which_bg == DUNGEON_BLOCK_ROOM && temp1 == index)
	// {
	// 	// dungeon block
	// 	which_bg = 5;
	// 	draw_bg();
	// }
#pragma endregion
}

void action_collision()
{
	// by default, no action
	collision_action = TURN_OFF;

	// temp1 - 4 define the interaction box, based on
	// where the player currently is, and then expanding on it.
	temp1 = player_x;							 // x- left side
	temp2 = temp1 + PLAYER_WIDTH;	 // x- right side
	temp3 = player_y;							 // y- top side
	temp4 = temp3 + PLAYER_HEIGHT; // y- bottom side 

	// make the whole box a little bigger.
	temp1 = temp1 - ACTION_BUFFER;
	temp2 = temp2 + ACTION_BUFFER;
	temp3 = temp3 - ACTION_BUFFER;
	temp4 = temp4 + ACTION_BUFFER;

	// extend the action box in front of the player

	switch (player_direction)
	{ // 0 = down, 1 = left, 2 = up, 3 = right
	case DOWN_MOVE:
		temp4 = temp4 + ACTION_HEIGHT;
		break;
	case LEFT_MOVE:
		temp1 = temp1 - ACTION_WIDTH;
		break;
	case UP_MOVE:
		temp3 = temp3 - ACTION_HEIGHT;
		break;
	case RIGHT_MOVE:
		temp2 = temp2 + ACTION_WIDTH;
		break;
	default:
		break;
	}

	// did out action box push too far out
	if (temp1 > temp2)
	{
		temp1 = SCREEN_LEFT_EDGE;
	}
	if (temp2 < temp1)
	{
		temp2 = SCREEN_RIGHT_EDGE;
	}
	if (temp3 > temp4)
	{
		temp3 = SCREEN_TOP_EDGE;
	}
	if (temp4 < temp3)
	{
		temp4 = SCREEN_BOTTOM_EDGE;
	}

	// now we've got a big action box (temp1-4)
	// lets see if any of the talking map points are
	// inside the box
	for (index = 0; index < MAX_ROOM_TALKING; ++index)
	{
		temp5 = talk_x[index];
		if (temp5 == TURN_OFF)
		{
			break; // end of list, exit loop
		}

		if (temp1 <= temp5 && temp5 < temp2)
		{

			temp6 = talk_y[index];
			if (temp3 <= temp6 && temp6 < temp4)
			{
				collision_action = talk_type[index];
				return;
			}
		}
	}
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

	temp6 = temp5 = player_x + PLAYER_OFFSET; // upper left (temp6 = save for reuse)
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
	temp5 += PLAYER_WIDTH - PLAYER_OFFSET;
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

	temp3 = player_y + PLAYER_HEIGHT + PLAYER_OFFSET; // y bottom
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
	collision = collision_list[which_bg][collision];
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

	if (which_bg == 41)
	{								 // going up from the back door area
		which_bg = 11; // teleport to the top outdoors
	}

	if (which_bg == 0)
	{ // going up from the dungeon
		which_bg = DUNGEON_BLOCK_ROOM;
		// put the player near the dungeon block
		player_x = 130;
		player_y = 160;
	}

	draw_bg();
}

void change_room_down()
{
	player_y = PLAYER_TOP_EDGE;
	which_bg = which_bg + 5;
	draw_bg();

	if (which_bg == 47) // the back door
	{
		collision_action = TALK_LOCKED_DOORS;
		draw_talking();
	}
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
	// todo map:
	one_vram_buffer('*', NTADR_A(2, 4));
	one_vram_buffer('M', NTADR_A(3, 4));
	one_vram_buffer('A', NTADR_A(4, 4));
	one_vram_buffer('P', NTADR_A(5, 4));
	one_vram_buffer('*', NTADR_A(6, 4));

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
	one_vram_buffer('*', NTADR_A(22, 2));
	one_vram_buffer('T', NTADR_A(23, 2));
	one_vram_buffer('I', NTADR_A(24, 2));
	one_vram_buffer('M', NTADR_A(25, 2));
	one_vram_buffer('E', NTADR_A(26, 2));
	one_vram_buffer('*', NTADR_A(27, 2));
}

void draw_talking(void)
{
	// writes to the HUD area, then starts the talking mode
	// which writes 1 char a frame.
	ppu_off();
	game_mode = MODE_TALKING_TIME;

	fade_out = 0;		 // don't fade bg for draw_bg for talking
	display_hud = 0; // don't draw hud for draw_bg for talking
	draw_bg();

	multi_vram_buffer_horz(topBar, sizeof(topBar), NTADR_A(1, 2));
	multi_vram_buffer_horz(bottomBar, sizeof(bottomBar), NTADR_A(1, 6));

	one_vram_buffer(0xfd, NTADR_A(1, 3));
	one_vram_buffer(0xfd, NTADR_A(1, 4));
	one_vram_buffer(0xfd, NTADR_A(1, 5));
	one_vram_buffer(0xfd, NTADR_A(30, 3));
	one_vram_buffer(0xfd, NTADR_A(30, 4));
	one_vram_buffer(0xfd, NTADR_A(30, 5));

	// set the pointer to the right dialog
	switch (collision_action)
	{
	case TALK_ALAN:
		pointer = alan_1;
		text_length = sizeof(alan_1);
		break;
	case TALK_BRIAN:
		pointer = brian_1;
		text_length = sizeof(brian_1);
		break;
	case TALK_GUY:
		pointer = guy_1;
		text_length = sizeof(guy_1);
		break;
	case TALK_PLAY_GAME:
		pointer = play_game_text;
		text_length = sizeof(play_game_text);
		break;
	case TALK_GAME:
		pointer = game_1;
		text_length = sizeof(game_1);
		break;
	case TALK_LOCKED_DOORS:
		pointer = locked_doors;
		text_length = sizeof(locked_doors);
		break;
	default:
		pointer = blank_1;
		text_length = sizeof(blank_1);
		break;
	}

	ppu_on_all();
}

void initialize_title_screen(void)
{
	game_mode = MODE_TITLE;
	which_bg = 0;

	ppu_off();
	oam_clear();
	draw_bg();
	multi_vram_buffer_horz(start_text, sizeof(start_text) - 1, NTADR_A(10, 19));

	multi_vram_buffer_horz(credits_1, sizeof(credits_1), NTADR_A(7, 24));
	multi_vram_buffer_horz(credits_2, sizeof(credits_2), NTADR_A(3, 25));
	multi_vram_buffer_horz(credits_3, sizeof(credits_3), NTADR_A(13, 26));

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

	which_bg = 4; // set background to black
	draw_bg();

	multi_vram_buffer_horz(end_text2, sizeof(end_text2) - 1, NTADR_A(3, 20));

	ppu_on_all();
	pal_bright(4); // back to normal brighness
}