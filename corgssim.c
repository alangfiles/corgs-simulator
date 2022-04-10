/*
need for launch:
[] bug:character clipping left and right oddly, maybe make him smaller vertically too
[x] add more talking, lots of talking
[] add run out of time ending
[x] warp toliets (make sprite walkable + changeroom code)
[x] add dungeon pushblock
[x] special overlay sprites that you walk behind
[] actual music and sfx

mini games:
[x] fetch quest
[] do reps with the brahs
[x] add robineete message and . on screen?
[x] add pipe level / jumping
[] rpg battle
[] battle with game jobbies

fun list:
[] king of video games says somethign if you've collected everything?
[] add guys to title screen
[] infinite hallway
[] more yes/no actions
[] money sprite explodes on things
[] add intro screen (in the year 20XX)
[] clean up vars
[] clean up sprites
[x] bug: remove money sprite when changing rooms

music:
[] main game music
[] title tune
[] king of video games tune

sfx:
[] contra theme
[] jump sound
[] zelda block
[] mario noise
[] toliet warp noise
[] coin noise
[] money hitting things

*/

#include "LIB/neslib.h"
#include "LIB/nesdoug.h"
#include "Sprites.h" // holds our metasprite data
#include "Talk.h"		 // holds our talking data
#include "corgssim.h"
#include "special_rooms.h"
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
				song = SONG_GAME;
				music_play(song);

				if (code_active == 1)
				{
					// play sound
				}
				// initialize game mode:
				pal_fade_to(4, 0); // fade to black
				ppu_off();

				// set defaults
				game_mode = MODE_GAME;
				player_x = 0x80;
				player_y = 0x80;

				minutes_left = 4;
				seconds_left_tens = 0;
				seconds_left_ones = 0;
				bg_display_hud = 1;
				which_bg = STARTING_ROOM;

				draw_bg();
				draw_hud();
				ppu_on_all();
				pal_bright(4); // back to normal brighness
			}

			if (pad1_new & (PAD_ALL_DIRECTIONS + PAD_A + PAD_B))
			{
				if (pad1_new & code[index])
				{ // the next item in the code is pressed
					++index;
				}
				else
				{
					index = 0; // reset the code
				}
			}
			if (index == 10) // 10 correct inputs
			{
				code_active = 1;
				// maybe flash the screen?
				sfx_play(SFX_MYSTERY, 0);
			}
		}
		while (game_mode == MODE_GAME) // gameloop
		{
			set_music_speed(5);
			ppu_wait_nmi();		 // wait till beginning of the frame
			countdown_timer(); // keep ticking the timer

			pad1 = pad_poll(0);				 // read the first controller
			pad1_new = get_pad_new(0); // newly pressed button. do pad_poll first

			movement();
			sprite_collisions();
			action();

			draw_sprites();

			// for debugging, the lower the line, the less processing we have
			gray_line();
		}
		while (game_mode == MODE_TALKING_TIME)
		{
			// todo: we can definitely clean up this `text_decision` code.
			//  into it's own logical blocks

			ppu_wait_nmi();
			countdown_timer(); // keep ticking the game timer

			// temp1 = get_frame_count();
			// temp1 = (temp1 >> 3);

			// draw text
			if (text_rendered != text_length && text_row < 3)
			{
				if (pointer[text_rendered] == '\n')
				{
					// auto-wrap to next row
					++text_row;
					text_col = 0;
				}
				else
				{
					one_vram_buffer(pointer[text_rendered], NTADR_A(2 + text_col, 3 + text_row));
					++text_col;

					if (text_col == 27) // wrap to next row
					{
						++text_row;
						text_col = 0;
					}
				}

				++text_rendered;
			}
			if (text_row == 3) // if there's more than 1 page of
			{
				one_vram_buffer('&', NTADR_A(15, 6)); //& = down caret
			}

			pad1 = pad_poll(0);
			pad1_new = get_pad_new(0);

			if ((pad1_new & PAD_B) && text_row == 3)
			{
				// clear the old text
				draw_talking();
				// set text_row to 0
				text_row = 0;
			}

			if ((text_rendered == text_length) && text_decision != TURN_OFF) // if there's a text decision
			{
				// draw the last row as yes/no
				// 0xed is bottom bar
				// 0x60 is arrow
				if (text_decision == 0)
				{
					one_vram_buffer(0x60, NTADR_A(10, 6));
					one_vram_buffer(0xed, NTADR_A(17, 6));
				}
				else
				{
					one_vram_buffer(0xed, NTADR_A(10, 6));
					one_vram_buffer(0x60, NTADR_A(17, 6));
				}

				one_vram_buffer('N', NTADR_A(11, 6));
				one_vram_buffer('O', NTADR_A(12, 6));

				one_vram_buffer('Y', NTADR_A(18, 6));
				one_vram_buffer('E', NTADR_A(19, 6));
				one_vram_buffer('S', NTADR_A(20, 6));
			}

			if (text_decision != TURN_OFF)
			{
				if (pad1_new & PAD_RIGHT)
				{
					text_decision = 1;
				}
				if (pad1_new & PAD_LEFT)
				{
					text_decision = 0;
				}
			}

			if ((pad1_new & PAD_B) && (text_rendered == text_length))
			{
				temp1 = 0; // using this to help handle actions

				if (text_decision != TURN_OFF)
				{
					// handle talking actions
					switch (text_action)
					{
					case CHOICE_PLAY_GAME:
						if (text_decision == 1) // yes
						{
							// reset talking variables
							reset_text_values();
							bg_display_hud = 0;			 // draw the hud
							bg_fade_out = 1;				 // turn back on room fading
							display_hud_sprites = 1; // turn back on hud sprites
							item_found = 0;					 // reset item found (in case we were in the item found mode)
							temp1 = 1;
							game_mode = MODE_TITLE;
							initialize_title_screen();
							ppu_on_all(); // turn on screen
						}
						break;
					case CHOICE_FETCH_QUEST:
						if (text_decision == 1)
						{
							reset_text_values();
							on_fetchquest = 1;
							items_collected = items_collected | ITEM_BURGER_GAME;
							item_found = ITEM_BURGER_GAME;
							collision_action = TALK_FETCHQUEST_1;
							draw_talking();
						}
						break;
					case CHOICE_BUY_FOOD:
						ppu_off();
						if (text_decision == 1)
						{
							reset_text_values();
							ppu_off();
							on_fetchquest = 2;
							item_found = ITEM_BURGER_GAME;
							collision_action = TALK_FETCHTWO;
							draw_talking();
						}
						break;
					default:
						break;
					}
				}

				// if the guy just gave us the game, play the text for it
				if ((text_rendered == text_length) && on_fetchquest == 3)
				{
					reset_text_values();
					on_fetchquest = 4;
					item_found = ITEM_BURGER_GAME;
					collision_action = TALK_ITEM_4;
					draw_talking();
				}

				// text finished, go back to game

				if (temp1 == 0) // we didn't exit before
				{
					// reset talking variables
					reset_text_values();
					bg_display_hud = 1; // draw the hud

					game_mode = MODE_GAME;

					draw_bg();
					bg_fade_out = 1;				 // turn back on room fading
					display_hud_sprites = 1; // turn back on hud sprites
					item_found = 0;					 // reset item found (in case we were in the item found mode)
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

void reset_text_values(void)
{
	text_rendered = 0;
	text_row = 0;
	text_col = 0;
}

void draw_bg(void)
{
	if (bg_fade_out == 1)
	{
		pal_fade_to(4, 0); // fade to black
	}

	ppu_off();	 // screen off
	oam_clear(); // clear all sprites
	// remove money sprite
	shot_x = -4;
	shot_y = -4;

	set_mt_pointer(room_metatile_list[which_bg]);
	pal_bg(room_palette_list[which_bg]);

	// dungeon only
	if (which_bg == DUNGEON_GAME_ROOM)
	{
		// I figure I can change the palette here to get
		// gray bricks, but I can't figure it out.
		// block 19 use bg palette 1, so it should be 4,5,6,7
		// pal_col(4, 0x2d);//<-- not changes for bg tile
		// 0x0f,0x2d,0x00,0x20,//
		pal_col(5, 0x00);
		pal_col(6, 0x30);
		pal_col(7, 0x20);
	}

	// to save space, the room files just have the room data, not the hud or bottom line
	// so we memcopy those in now to cost more rendering time in draw_bg, but save
	// some bites in the rom.
	if (which_bg == 0 || which_bg == CLIFF_ROOM) // title screen and cliff
	{
		set_data_pointer(room_list[which_bg]);
		memcpy(c_map, room_list[which_bg], 240);
	}
	else
	{
		// shortcut drawing the HUD spaces and the bottom line with this code
		for (index = 0; index < 240; ++index)
		{
			if (index < 64)
			{
				if (room_metatile_list[which_bg] == outside_metatiles)
				{
					tile_map[index] = 13;
				}
				else
				{
					tile_map[index] = 0;
				}
			}
			else if (index < 224)
			{
				tile_map[index] = room_list[which_bg][index - 64];
			}
			else
			{
				if (room_metatile_list[which_bg] == outside_metatiles)
				{
					tile_map[index] = 13;
				}
				else
				{
					tile_map[index] = 0;
				}
			}
		}
		set_data_pointer(tile_map);
		memcpy(c_map, tile_map, 240);
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

	if (bg_display_hud == 1)
	{
		draw_hud();
	}

	initialize_sprites();

	initialize_talk_map();

	draw_timer(); // draw timer on screen transitions

	ppu_on_all(); // turn on screen

	if (bg_fade_out == 1)
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
	if (move_frames > 32)
	{
		move_frames = 0;
	}

	// if the player is jumping, we use the first move frame for the jump duration
	if (player_jump > 0)
	{
		move_frames = 0;
	}
	// clear all sprites from sprite buffer
	oam_clear();

// draw one time srpites
#pragma region foregroundSprites
	if (which_bg == 13)
	{
		oam_meta_spr(108, 160, Banner99);
	}
#pragma endregion

#pragma region drawplayer
	if (item_found) // special player sprite used if item found
	{
		oam_meta_spr(player_x, player_y, PrizeGuy94);
	}
	else
	{
		switch (player_direction)
		{
		case DOWN_MOVE:

			if (pad1 & PAD_DOWN) // only animate if the button is pressed
			{
				if (move_frames >= 24 && move_frames < 28)
				{
					oam_meta_spr(player_x, player_y, PlayerSprDownThree);
				}
				else if (move_frames >= 16 && move_frames < 20)
				{
					oam_meta_spr(player_x, player_y, PlayerSprDownTwo);
				}
				else if (move_frames >= 8 && move_frames < 12)
				{
					oam_meta_spr(player_x, player_y, PlayerSprDownThree);
				}
				else if (move_frames < 4)
				{
					oam_meta_spr(player_x, player_y, PlayerSprDownTwo);
				}
				else
				{
					oam_meta_spr(player_x, player_y, PlayerSprDown);
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

				if (move_frames >= 24 && move_frames < 28)
				{
					oam_meta_spr(player_x, player_y, PlayerSprLeftFour);
				}
				else if (move_frames >= 20 && move_frames < 24)
				{
					oam_meta_spr(player_x, player_y, PlayerSprLeftFive);
				}
				else if (move_frames >= 16 && move_frames < 20)
				{
					oam_meta_spr(player_x, player_y, PlayerSprLeftFour);
				}
				else if (move_frames >= 8 && move_frames < 12)
				{
					oam_meta_spr(player_x, player_y, PlayerSprLeftTwo);
				}
				else if (move_frames >= 4 && move_frames < 8)
				{
					oam_meta_spr(player_x, player_y, PlayerSprLeftThree);
				}
				else if (move_frames < 4)
				{
					oam_meta_spr(player_x, player_y, PlayerSprLeftTwo);
				}
				else
				{
					oam_meta_spr(player_x, player_y, PlayerSprLeft);
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
				if (move_frames >= 24 && move_frames < 28)
				{
					oam_meta_spr(player_x, player_y, PlayerSprUpThree);
				}
				else if (move_frames >= 16 && move_frames < 20)
				{
					oam_meta_spr(player_x, player_y, PlayerSprUpTwo);
				}
				else if (move_frames >= 8 && move_frames < 12)
				{
					oam_meta_spr(player_x, player_y, PlayerSprUpThree);
				}
				else if (move_frames < 4)
				{
					oam_meta_spr(player_x, player_y, PlayerSprUpTwo);
				}
				else
				{
					oam_meta_spr(player_x, player_y, PlayerSprUp);
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

				if (move_frames >= 24 && move_frames < 28)
				{
					oam_meta_spr(player_x, player_y, PlayerSprRightFour);
				}
				else if (move_frames >= 20 && move_frames < 24)
				{
					oam_meta_spr(player_x, player_y, PlayerSprRightFive);
				}
				else if (move_frames >= 16 && move_frames < 20)
				{
					oam_meta_spr(player_x, player_y, PlayerSprRightFour);
				}
				else if (move_frames >= 8 && move_frames < 12)
				{
					oam_meta_spr(player_x, player_y, PlayerSprRightTwo);
				}
				else if (move_frames >= 4 && move_frames < 8)
				{
					oam_meta_spr(player_x, player_y, PlayerSprRightThree);
				}
				else if (move_frames < 4)
				{
					oam_meta_spr(player_x, player_y, PlayerSprRightTwo);
				}
				else
				{
					oam_meta_spr(player_x, player_y, PlayerSprRight);
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
		case SPRITE_BoyKid44:
			sprites_anim[index2] = BoyKid44;
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
		case SPRITE_SkinnyHatMan49:
			sprites_anim[index2] = SkinnyHatMan49;
			break;
		case SPRITE_GlassesLeft31:
			sprites_anim[index2] = GlassesLeft31;
			break;
		case SPRITE_BaldForward13:
			sprites_anim[index2] = BaldForward13;
			break;
		case SPRITE_GirlKid47:
			sprites_anim[index2] = GirlKid47;
			break;
		case SPRITE_BlueBeard74:
			sprites_anim[index2] = BlueBeard74;
			break;
		case SPRITE_King75:
			sprites_anim[index2] = King75;
			break;
		case SPRITE_BigNoseRight83:
			sprites_anim[index2] = BigNoseRight83;
			break;
		case SPRITE_BaldTankBehind121:
			sprites_anim[index2] = BaldTankBehind121;
			break;
		case SPRITE_OldCoot63:
			sprites_anim[index2] = OldCoot63;
			break;
		case SPRITE_GlassesRight33:
			sprites_anim[index2] = GlassesRight33;
			break;
		case SPRITE_HairRight28:
			sprites_anim[index2] = HairRight28;
			break;
		case SPRITE_SideLadyRight87:
			sprites_anim[index2] = SideLadyRight87;
			break;
		case SPRITE_DressGirl61:
			sprites_anim[index2] = DressGirl61;
			break;
		case SPRITE_MuscleMan0:
			sprites_anim[index2] = MuscleMan0;
			break;
		case SPRITE_MuscleMan1:
			sprites_anim[index2] = MuscleMan1;
			break;
		case SPRITE_MuscleMan2:
			sprites_anim[index2] = MuscleMan2;
			break;
		case SPRITE_Girl4:
			sprites_anim[index2] = Girl4;
			break;
		case SPRITE_FroGuy55:
			sprites_anim[index2] = FroGuy55;
			break;
		case SPRITE_WideBoy69:
			sprites_anim[index2] = WideBoy69;
			break;
		case SPRITE_HatBehind117:
			sprites_anim[index2] = HatBehind117;
			break;
		case SPRITE_Ghost65:
			sprites_anim[index2] = Ghost65;
			break;
		case SPRITE_CostumeMan58:
			sprites_anim[index2] = CostumeMan58;
			break;
		case SPRITE_Wizard52:
			sprites_anim[index2] = Wizard52;
			break;
		case SPRITE_SideLadyLeft90:
			sprites_anim[index2] = SideLadyLeft90;
			break;
		case SPRITE_BeardSideManLeft79:
			sprites_anim[index2] = BeardSideManLeft79;
			break;
		case SPRITE_HairBehind9:
			sprites_anim[index2] = HairBehind9;
			break;
		case SPRITE_BaldBehind6:
			sprites_anim[index2] = BaldBehind6;
			break;
		case SPRITE_HairLeft24:
			sprites_anim[index2] = HairLeft24;
			break;
		case SPRITE_Ghost66:
			sprites_anim[index2] = Ghost66;
			break;
		case SPRITE_HairBehind11:
			sprites_anim[index2] = HairBehind11;
			break;
		case SPRITE_DressGirl60:
			sprites_anim[index2] = DressGirl60;
			break;
		case SPRITE_GlassesRight35:
			sprites_anim[index2] = GlassesRight35;
			break;
		case SPRITE_SkirtLady40:
			sprites_anim[index2] = SkirtLady40;
			break;
		case SPRITE_LunchLady37:
			sprites_anim[index2] = LunchLady37;
			break;
		case SPRITE_HairFront129:
			sprites_anim[index2] = HairFront129;
			break;
		case SPRITE_Girl3:
			sprites_anim[index2] = Girl3;
			break;
		case SPRITE_BaldBehind8:
			sprites_anim[index2] = BaldBehind8;
			break;
		case SPRITE_BaldLeft18:
			sprites_anim[index2] = BaldLeft18;
			break;
		case SPRITE_BaldTank73:
			sprites_anim[index2] = BaldTank73;
			break;
		case SPRITE_COIN:
			sprites_anim[index2] = Coin;
			break;
		case SPRITE_DungeonBlock:
			sprites_anim[index2] = DungeonBlock;
		default:
			break;
		}
		oam_meta_spr(temp1, temp2, sprites_anim[index2]);
	}
#pragma endregion room_sprites

#pragma region hud_sprites
	if (display_hud_sprites)
	{
		oam_meta_spr(0x68, 0x1D, Question128);
		oam_meta_spr(0x88, 0x1D, Dollars127);

		if (items_collected & ITEM_DUNGEON_GAME)
		{
			oam_meta_spr(0x10, 0x10, FloppyDisk125);
		}
		if (items_collected & ITEM_COIN_GAME)
		{
			oam_meta_spr(0x22, 0x10, GamePrize97);
		}
		if (items_collected & ITEM_ADVENTURE_GAME)
		{
			oam_meta_spr(0x34, 0x10, AdventureGameBig);
		}
		if (items_collected & ITEM_BURGER_GAME)
		{
			switch (on_fetchquest)
			{
			case 1:
				oam_meta_spr(0x24, 0x20, FetchMoney);
				break;
			case 2:
				oam_meta_spr(0x24, 0x20, FetchFood);
				break;
			case 4:
				oam_meta_spr(0x24, 0x20, BurgerGame);
				break;
			default:
				break;
			}
		}

		if (code_active == 1)
		{
			oam_meta_spr(0xBA, 0x30, PlayerHead);
			one_vram_buffer('x', NTADR_A(25, 6));
			one_vram_buffer('3', NTADR_A(26, 6));
			one_vram_buffer('0', NTADR_A(27, 6));
		}
	}
#pragma endregion

#pragma region special_sprites

	if (which_bg == DUNGEON_GAME_ROOM)
	{
		// if the dungeon game isn't collected
		if (!(items_collected & ITEM_DUNGEON_GAME))
		{
			oam_meta_spr(DUNGEON_GAME_X, DUNGEON_GAME_Y, FloppyDisk125);
		}
	}

	if (which_bg == COIN_GAME_ROOM)
	{
		if (!(items_collected & ITEM_COIN_GAME) && player_coins == MAX_COINS)
		{
			oam_meta_spr(COIN_GAME_X, COIN_GAME_Y, GamePrize97);
		}
	}

	if (which_bg == ADVENTURE_GAME_ROOM)
	{

		if (!(items_collected & ITEM_ADVENTURE_GAME))
		{
			oam_meta_spr(ADVENTURE_GAME_X, ADVENTURE_GAME_Y, AdventureGame);
		}
	}

	// display holding item status
	if (item_found)
	{
		if (item_found == ITEM_DUNGEON_GAME)
		{
			// draw the sprite above the players head
			oam_meta_spr(player_x, player_y - 16, FloppyDisk125);
		}
		if (item_found == ITEM_COIN_GAME)
		{
			oam_meta_spr(player_x, player_y - 16, GamePrize97);
		}
		if (item_found == ITEM_ADVENTURE_GAME)
		{
			oam_meta_spr(player_x, player_y - 16, AdventureGameBig);
		}

		if (item_found == ITEM_BURGER_GAME)
		{
			switch (on_fetchquest)
			{
			case 1:
				oam_meta_spr(player_x, player_y - 16, FetchMoney);
				break;
			case 2:
				oam_meta_spr(player_x, player_y - 16, FetchFood);
				break;
			case 4:
				oam_meta_spr(player_x, player_y - 16, BurgerGame);
				break;
			default:
				break;
			}
		}
	}

#pragma endregion
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
		sfx_play(SFX_SHOT, 0);
	}

	// check for interactable
	if (pad1_new & PAD_B)
	{
		action_collision();

		if (collision_action != TURN_OFF)
		{
			// draw the talking dialog
			draw_talking();
		}

		if (which_bg == ADVENTURE_GAME_ROOM && (!(items_collected & ITEM_ADVENTURE_GAME)))
		{
			Generic2.x = ADVENTURE_GAME_X;
			Generic2.y = ADVENTURE_GAME_Y;
			Generic2.width = 8;
			Generic2.height = 8;
			if (check_collision(&Generic, &Generic2))
			{
				items_collected = items_collected | ITEM_ADVENTURE_GAME; // pick up the item
				item_found = ITEM_ADVENTURE_GAME;
				collision_action = TALK_ITEM_3;
				draw_talking();
			}
		}
	}
}

void movement(void)
{
	// dungeon push block
	if (which_bg == DUNGEON_BLOCK_ROOM && push_timer > 100 && block_moved == 0)
	{
		if (player_direction == LEFT)
		{
			if (sprites_x[0] > (DUNGEON_BLOCK_X - 0x10))
			{
				--sprites_x[0];
			}
			else
			{
				block_moved = 1; // done moving
			}
			return;
		}

		if (player_direction == RIGHT)
		{
			if (sprites_x[0] < (DUNGEON_BLOCK_X + 0x10))
			{
				++sprites_x[0];
			}
			else
			{
				block_moved = 1;
			}
			return;
		}
	}
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

	if (which_bg == COIN_GAME_ROOM)
	{
		// add to player 'velocity' if they're in jump mode
		if (player_jump > 0)
		{
			player_y -= 4;
			player_jump -= 4;
		}

		// check for jumps
		if (pad1_new & PAD_B)
		{
			if (player_jump == 0) // don't allow double jumps
			{
				player_jump = PLAYER_MAX_JUMP;
			}
			sfx_play(SFX_JUMP, 0);
		}
		// gravity
		player_y += 2;

		// check collision and eject
		bg_collision();
		if (collision_D)
		{
			player_y -= 2;
		}
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
			&& (pad1 & PAD_ALL_DIRECTIONS)						// one of the direction buttons is held down
			&& has_moved == 1)												// and the player hasn't moved
	{
		++push_timer;
	}
	else
	{
		push_timer = 0;
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

#pragma region specialCases

	// dungeon block
	Generic.x = player_x;
	Generic.y = player_y;
	Generic.width = PLAYER_WIDTH;
	Generic.height = PLAYER_HEIGHT;

	if (which_bg == DUNGEON_BLOCK_ROOM)
	{
		// make the block a little smaller before activating
		Generic2.x = DUNGEON_BLOCK_X + 7;
		Generic2.y = DUNGEON_BLOCK_Y + 7;
		Generic2.width = 4;
		Generic2.height = 4;
		if ( // block_moved &&
				check_collision(&Generic, &Generic2))
		{
			which_bg = DUNGEON_GAME_ROOM;
			player_x = 0x30;
			player_y = 0x41;
			block_moved = 0;
			draw_bg();
		}
	}

	if (which_bg == TOLIET_WARP_1_ROOM)
	{
		// make the block a little smaller before activating
		Generic2.x = TOLIET_WARP_1_X + 7;
		Generic2.y = TOLIET_WARP_1_Y + 7;
		Generic2.width = 4;
		Generic2.height = 4;
		if ( // block_moved &&
				check_collision(&Generic, &Generic2))
		{
			sfx_play(SFX_WARP_TOLIET, 0);
			which_bg = TOLIET_WARP_2_ROOM;
			player_x = TOLIET_WARP_2_X - 0x10;
			player_y = TOLIET_WARP_2_Y;
			draw_bg();
		}
	}

	if (which_bg == TOLIET_WARP_2_ROOM)
	{
		// make the block a little smaller before activating
		Generic2.x = TOLIET_WARP_2_X + 7;
		Generic2.y = TOLIET_WARP_2_Y + 7;
		Generic2.width = 4;
		Generic2.height = 4;
		if ( // block_moved &&
				check_collision(&Generic, &Generic2))
		{
			sfx_play(SFX_WARP_TOLIET, 0);
			which_bg = TOLIET_WARP_1_ROOM;
			player_x = TOLIET_WARP_1_X - 0x10;
			player_y = TOLIET_WARP_1_Y;
			draw_bg();
		}
		else
		{ // check other toliet warp
			Generic2.x = TOLIET_WARP_3_X + 7;
			Generic2.y = TOLIET_WARP_3_Y + 7;
			if ( // block_moved &&
					check_collision(&Generic, &Generic2))
			{
				sfx_play(SFX_WARP_TOLIET, 0);
				which_bg = COIN_GAME_ROOM;
				player_x = 0x20;
				player_y = 0x50;
				Generic.x = 0x20;
				Generic.y = 0x50;
				draw_bg();
			}
		}
	}

	if (which_bg == COIN_GAME_ROOM)
	{
		// make the block a little smaller before activating
		Generic2.x = COIN_ROOM_WARP_X + 7;
		Generic2.y = COIN_ROOM_WARP_Y + 7;
		Generic2.width = 4;
		Generic2.height = 4;
		if ( // block_moved &&
				check_collision(&Generic, &Generic2))
		{
			sfx_play(SFX_WARP_TOLIET, 0);
			which_bg = TOLIET_WARP_2_ROOM;
			player_x = TOLIET_WARP_3_X - 0x10;
			player_y = TOLIET_WARP_3_Y;
			draw_bg();
		}
	}

	if (which_bg == DUNGEON_GAME_ROOM && (!(items_collected & ITEM_DUNGEON_GAME)))
	{
		Generic2.x = DUNGEON_GAME_X + 7;
		Generic2.y = DUNGEON_GAME_Y + 7;
		Generic2.width = 1;
		Generic2.height = 1;
		if (check_collision(&Generic, &Generic2))
		{
			items_collected = items_collected | ITEM_DUNGEON_GAME; // pick up the item
			item_found = ITEM_DUNGEON_GAME;
			collision_action = TALK_ITEM_1;
			draw_talking();
		}
	}

	if (which_bg == COIN_GAME_ROOM && (!(items_collected & ITEM_COIN_GAME)) && player_coins == MAX_COINS)
	{
		Generic2.x = COIN_GAME_X + 7;
		Generic2.y = COIN_GAME_Y + 7;
		Generic2.width = 1;
		Generic2.height = 1;
		if (check_collision(&Generic, &Generic2))
		{
			items_collected = items_collected | ITEM_COIN_GAME; // pick up the item
			item_found = ITEM_COIN_GAME;
			collision_action = TALK_ITEM_2;
			draw_talking();
		}
	}

#pragma endregion
}

void sprite_collisions(void)
{
	if (which_bg == COIN_GAME_ROOM)
	{
		for (index = 0; index < MAX_COINS; ++index)
		{

			Generic2.width = 8;
			Generic2.height = 8;

			Generic2.x = sprites_x[index];
			Generic2.y = sprites_y[index];
			if (check_collision(&Generic, &Generic2))
			{
				sprites_y[index] = TURN_OFF;
				sfx_play(SFX_COIN, 0);
				++player_coins;
			}
		}
	}
	// set the first Generic to the players attributes
	Generic.x = player_x;
	Generic.y = player_y;
	Generic.width = PLAYER_WIDTH;
	Generic.height = PLAYER_HEIGHT;

	// go through all the sprites in the room
	// all other sprites are 16x16 (not always true)
	// but we'll put larger sprites in unreachable places
	Generic2.width = 16;
	Generic2.height = 16;
	for (index = 0; index < MAX_ROOM_SPRITES; ++index)
	{
		if (sprites_type[index] == TURN_OFF)
		{
			break; // run out of sprites, stop checking collisions
		}

		Generic2.x = sprites_x[index];
		Generic2.y = sprites_y[index];
		if (check_collision(&Generic, &Generic2))
		{
			// player is coliding with sprite,
			// lets just move the player back 1 px
			switch (player_direction)
			{
			case DOWN:
				// they're moving down and ran into something
				// so push them back up
				--player_y;
				break;
			case UP:
				++player_y;
				break;
			case LEFT:
				++player_x;
				break;
			case RIGHT:
				--player_x;
				break;
			default:
				break;
			}
		}
	}
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

	// we shouldn't need this code cause it can wrap around and that's fine
	// but if we see oddities we can bring this back
	//  // did out action box push too far out
	//  if (temp1 > temp2)
	//  {
	//  	temp1 = SCREEN_LEFT_EDGE;
	//  }
	//  if (temp2 < temp1)
	//  {
	//  	temp2 = SCREEN_RIGHT_EDGE;
	//  }
	//  if (temp3 > temp4)
	//  {
	//  	temp3 = SCREEN_TOP_EDGE;
	//  }
	//  if (temp4 < temp3)
	//  {
	//  	temp4 = SCREEN_BOTTOM_EDGE;
	//  }

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

	temp6 = temp5 = player_x; // upper left (temp6 = save for reuse)
	temp1 = temp5 & 0xff;			// low byte x
	temp2 = temp5 >> 8;				// high byte x

	// eject_L = temp1 | 0xf0;

	temp3 = player_y + PLAYER_PIXELS; // y top

	// eject_U = temp3 | 0xf0;

	// if(L_R_switch) temp3 += 2; // fix bug, walking through walls

	bg_collision_sub();

	if (collision & COL_ALL)
	{ // find a corner in the collision map
		++collision_L;
		++collision_U;
	}

	// upper right
	temp5 += PLAYER_WIDTH;
	temp1 = temp5 & 0xff; // low byte x
	temp2 = temp5 >> 8;		// high byte x

	// eject_R = (temp1 + 1) & 0x0f;

	// temp3 is unchanged
	bg_collision_sub();

	if (collision & COL_ALL)
	{ // find a corner in the collision map
		++collision_R;
		++collision_U;
	}

	// again, lower

	// bottom right, x hasn't changed

	temp3 = player_y + PLAYER_HEIGHT + PLAYER_PIXELS; // y bottom
	// if(L_R_switch) temp3 -= 2; // fix bug, walking through walls
	// eject_D = (temp3 + 1) & 0x0f;
	if (temp3 >= 0xf0)
		return;

	bg_collision_sub();

	if (collision & COL_ALL)
	{ // find a corner in the collision map
		++collision_R;
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
		++collision_D;
	}
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

	// space saving hacks, ignoring the 5x10 grid for bigger numbers
	if (which_bg == 21)
	{ // exit cliffs right
		bg_display_hud = 1;
		display_hud_sprites = 1;
	}
	if (which_bg == 22)
	{
		which_bg = 29;
	}
 
	draw_bg();
}

void change_room_left()
{
	player_x = PLAYER_RIGHT_EDGE;
	--which_bg;

	// if youre in room 29, go to room 22. if 22 got to 21 and turn off stuff
	// also, number is already decremented
	// space saving hacks, ignoring the 5x10 grid for bigger numbers
	if (which_bg == 28)
	{
		which_bg = 21;
	}
	if (which_bg == 20)
	{
		bg_display_hud = 0;
		display_hud_sprites = 0;
	}

	draw_bg();
}

void change_room_up()
{
	player_y = PLAYER_BOTTOM_EDGE;

	if (which_bg < 25)
	{
		which_bg = which_bg - 5;
	}
	else if (which_bg == 25) //space saving hax
	{
		which_bg = 22;
	}
	else if(which_bg == 21)
	{
		// going up from the back door area
		which_bg = 11; // teleport to the top outdoors
	}
	else
	{
		--which_bg;
	}

	if (which_bg == DUNGEON_BLOCK_ROOM)
	{
		block_moved = 0;
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

	if (which_bg < 20)
	{
		which_bg = which_bg + 5;
	} // space saving map hax
	else if (which_bg == 22)
	{
		which_bg = 25;
	}
	else
	{
		++which_bg;
	}

	if (which_bg == DUNGEON_BLOCK_ROOM)
	{
		block_moved = 0;
	}

	if (which_bg == 29) // the back door
	{
		collision_action = TALK_LOCKED_DOORS;
		draw_talking();
		return;
	}

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
	if (game_mode == MODE_GAME) // todo: probably don't need this check?
	{
		if (display_hud_sprites == 1)
		{
			one_vram_buffer(48 + minutes_left, NTADR_A(23, 3));
			one_vram_buffer(':', NTADR_A(24, 3));
			one_vram_buffer(48 + seconds_left_tens, NTADR_A(25, 3));
			one_vram_buffer(48 + seconds_left_ones, NTADR_A(26, 3));
		}
	}
}

void draw_hud(void)
{

	// draw buttons B
	one_vram_buffer(0xee, NTADR_A(B_LOC, 2));
	one_vram_buffer('B', NTADR_A(B_LOC + 1, 2));
	one_vram_buffer(0xef, NTADR_A(B_LOC + 2, 2));

	one_vram_buffer(0xfd, NTADR_A(B_LOC, 3));
	// one_vram_buffer(' ', NTADR_A(B_LOC + 1, 3));
	one_vram_buffer(0xfd, NTADR_A(B_LOC + 2, 3));
	one_vram_buffer(0xfd, NTADR_A(B_LOC, 4));
	// one_vram_buffer(' ', NTADR_A(B_LOC + 1, 4));
	one_vram_buffer(0xfd, NTADR_A(B_LOC + 2, 4));
	one_vram_buffer(0xfd, NTADR_A(B_LOC, 5));
	// one_vram_buffer(' ', NTADR_A(B_LOC + 1, 5));
	one_vram_buffer(0xfd, NTADR_A(B_LOC + 2, 5));
	one_vram_buffer(0xfe, NTADR_A(B_LOC, 6));
	one_vram_buffer(0xed, NTADR_A(B_LOC + 1, 6));
	one_vram_buffer(0xff, NTADR_A(B_LOC + 2, 6));

	// draw buttons A
	one_vram_buffer(0xee, NTADR_A(A_LOC, 2));
	one_vram_buffer('A', NTADR_A(A_LOC + 1, 2));
	one_vram_buffer(0xef, NTADR_A(A_LOC + 2, 2));
	one_vram_buffer(0xfd, NTADR_A(A_LOC, 3));
	// one_vram_buffer(' ', NTADR_A(A_LOC + 1, 3));
	one_vram_buffer(0xfd, NTADR_A(A_LOC + 2, 3));
	one_vram_buffer(0xfd, NTADR_A(A_LOC, 4));
	// one_vram_buffer(' ', NTADR_A(A_LOC + 1, 4));
	one_vram_buffer(0xfd, NTADR_A(A_LOC + 2, 4));
	one_vram_buffer(0xfd, NTADR_A(A_LOC, 5));
	// one_vram_buffer(' ', NTADR_A(A_LOC + 1, 5));
	one_vram_buffer(0xfd, NTADR_A(A_LOC + 2, 5));
	one_vram_buffer(0xfe, NTADR_A(A_LOC, 6));
	one_vram_buffer(0xed, NTADR_A(A_LOC + 1, 6));
	one_vram_buffer(0xff, NTADR_A(A_LOC + 2, 6));

	// draw timer
	one_vram_buffer('T', NTADR_A(23, 2));
	one_vram_buffer('I', NTADR_A(24, 2));
	one_vram_buffer('M', NTADR_A(25, 2));
	one_vram_buffer('E', NTADR_A(26, 2));
}

void draw_talking(void)
{
	// writes to the HUD area, then starts the talking mode
	// which writes 1 char a frame.
	ppu_off();
	game_mode = MODE_TALKING_TIME;
	text_decision = TURN_OFF; // no text decisions

	bg_fade_out = 0;		// don't fade bg for draw_bg for talking
	bg_display_hud = 0; // don't draw hud for draw_bg for talking
	draw_bg();

	multi_vram_buffer_horz(topBar, sizeof(topBar), NTADR_A(1, 2));
	multi_vram_buffer_horz(bottomBar, sizeof(bottomBar), NTADR_A(1, 6));

	// side bar of talking box
	one_vram_buffer(0xfd, NTADR_A(1, 3));
	one_vram_buffer(0xfd, NTADR_A(1, 4));
	one_vram_buffer(0xfd, NTADR_A(1, 5));
	// other size bar of talking box
	one_vram_buffer(0xfd, NTADR_A(30, 3));
	one_vram_buffer(0xfd, NTADR_A(30, 4));
	one_vram_buffer(0xfd, NTADR_A(30, 5));

	display_hud_sprites = 0;
	draw_sprites();

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
		text_decision = 0;
		text_action = CHOICE_PLAY_GAME;
		break;
	case TALK_LOCKED_DOORS:
		pointer = locked_doors;
		text_length = sizeof(locked_doors);
		break;
	case TALK_ITEM_1:
		pointer = item_1;
		text_length = sizeof(item_1);
		break;
	case TALK_ITEM_2:
		pointer = item_2;
		text_length = sizeof(item_2);
		break;
	case TALK_ITEM_3:
		pointer = item_3;
		text_length = sizeof(item_3);
		break;
	case TALK_ITEM_4:
		pointer = item_4;
		text_length = sizeof(item_4);
		break;
	case TALK_KING:
		pointer = talk_king;
		text_length = sizeof(talk_king);
		break;
	case TALK_SMOKE:
		pointer = talk_smoke;
		text_length = sizeof(talk_smoke);
		break;
	case TALK_BATHROOM:
		pointer = talk_bathroom;
		text_length = sizeof(talk_bathroom);
		break;
	case TALK_HOTDOG:
		if (on_fetchquest == 1)
		{
			pointer = talk_hotdog2;
			text_length = sizeof(talk_hotdog2);
			text_action = CHOICE_BUY_FOOD;
			text_decision = 0;
		}
		else
		{
			pointer = talk_hotdog;
			text_length = sizeof(talk_hotdog);
		}
		break;
	case TALK_FOOD:
		pointer = talk_food;
		text_length = sizeof(talk_food);
		break;
	case TALK_BUSH:
		pointer = talk_bush;
		text_length = sizeof(talk_bush);
		break;
	case TALK_NINTENDO:
		pointer = talk_nintendo;
		text_length = sizeof(talk_nintendo);
		break;
	case TALK_BUY:
		pointer = talk_buy;
		text_length = sizeof(talk_buy);
		break;
	case TALK_PRINCESS:
		pointer = talk_princess;
		text_length = sizeof(talk_princess);
		break;
	case TALK_PLUMBER:
		pointer = talk_plumber;
		text_length = sizeof(talk_plumber);
		break;
	case TALK_LOCATION:
		pointer = talk_location;
		text_length = sizeof(talk_location);
		break;
	case TALK_EBAY:
		pointer = talk_ebay;
		text_length = sizeof(talk_ebay);
		break;
	case TALK_ADMISSION:
		pointer = talk_admission;
		text_length = sizeof(talk_admission);
		break;
	case TALK_DOORPRIZE:
		pointer = talk_doorprize;
		text_length = sizeof(talk_doorprize);
		break;
	case TALK_GUYNEXT1:
		pointer = talk_guynext1;
		text_length = sizeof(talk_guynext1);
		break;
	case TALK_GUYNEXT2:
		pointer = talk_guynext2;
		text_length = sizeof(talk_guynext2);
		break;
	case TALK_THINGYOUWANT:
		pointer = talk_thingyouwant;
		text_length = sizeof(talk_thingyouwant);
		break;
	case TALK_GRADED:
		pointer = talk_graded;
		text_length = sizeof(talk_graded);
		break;
	case TALK_MYWIFE:
		pointer = talk_mywife;
		text_length = sizeof(talk_mywife);
		break;
	case TALK_MUSCLE1:
		pointer = talk_muscle1;
		text_length = sizeof(talk_muscle1);
		break;
	case TALK_MUSCLE2:
		pointer = talk_muscle2;
		text_length = sizeof(talk_muscle2);
		break;
	case TALK_LADYONBREAK:
		pointer = talk_ladyonbreak;
		text_length = sizeof(talk_ladyonbreak);
		break;
	case TALK_STICK:
		pointer = talk_stick;
		text_length = sizeof(talk_stick);
		break;
	case TALK_ARCADE:
		pointer = talk_arcade;
		text_length = sizeof(talk_arcade);
		break;
	case TALK_PINBALL:
		pointer = talk_pinball;
		text_length = sizeof(talk_pinball);
		break;
	case TALK_DRUGS:
		pointer = talk_drugs;
		text_length = sizeof(talk_drugs);
		break;
	case TALK_SPEAKER:
		pointer = talk_speaker;
		text_length = sizeof(talk_speaker);
		break;
	case TALK_CROWD:
		pointer = talk_crowd;
		text_length = sizeof(talk_crowd);
		break;
	case TALK_KICK:
		pointer = talk_kick;
		text_length = sizeof(talk_kick);
		break;
	case TALK_COPIES:
		pointer = talk_copies;
		text_length = sizeof(talk_copies);
		break;
	case TALK_YOUTUBE:
		pointer = talk_youtube;
		text_length = sizeof(talk_youtube);
		break;
	case TALK_KINGCHAT:
		pointer = talk_kingchat;
		text_length = sizeof(talk_kingchat);
		break;
	case TALK_OUTSIDE:
		pointer = talk_outside;
		text_length = sizeof(talk_outside);
		break;
	case TALK_NEWGAMES:
		pointer = talk_newgames;
		text_length = sizeof(talk_newgames);
		break;
	case TALK_JEALOUS:
		pointer = talk_jealous;
		text_length = sizeof(talk_jealous);
		break;
	case TALK_JUDGE:
		pointer = talk_judge;
		text_length = sizeof(talk_judge);
		break;
	case TALK_CHARACTER:
		pointer = talk_character;
		text_length = sizeof(talk_character);
		break;
	case TALK_PACMAN:
		pointer = talk_pacman;
		text_length = sizeof(talk_pacman);
		break;
	case TALK_PACMAN2:
		pointer = talk_pacman2;
		text_length = sizeof(talk_pacman2);
		break;
	case TALK_WIZARD:
		pointer = talk_wizard;
		text_length = sizeof(talk_wizard);
		break;
	case TALK_GENIE:
		pointer = talk_genie;
		text_length = sizeof(talk_genie);
		break;
	case TALK_SPRITES:
		pointer = talk_sprites;
		text_length = sizeof(talk_sprites);
		break;
	case TALK_GARY:
		pointer = talk_gary;
		text_length = sizeof(talk_gary);
		break;
	case TALK_FLIP:
		pointer = talk_flip;
		text_length = sizeof(talk_flip);
		break;
	case TALK_INYOURWAY:
		pointer = talk_inyourway;
		text_length = sizeof(talk_inyourway);
		break;
	case TALK_CLEVER:
		pointer = talk_clever;
		text_length = sizeof(talk_clever);
		break;
	case TALK_ERIC:
		pointer = talk_eric;
		text_length = sizeof(talk_eric);
		break;
	case TALK_COMPLAIN:
		pointer = talk_complain;
		text_length = sizeof(talk_complain);
		break;
	case TALK_FETCHQUEST:
		// this is the guy who starts you on the quest
		switch (on_fetchquest)
		{
		case 0:
			pointer = fetch_quest_1;
			text_length = sizeof(fetch_quest_1);
			text_decision = 0;
			text_action = CHOICE_FETCH_QUEST;
			break;
		// case 1:
		// 	// grumble
		// 	break;
		case 2:
			pointer = fetch_quest_2;
			text_length = sizeof(fetch_quest_2);
			on_fetchquest = 3;
			break;
		// case 3:
		// 	// munch munch
		// 	break;
		default:
			pointer = blank_1;
			text_length = sizeof(blank_1);
			break;
		}

		break;
	case TALK_FOODTRUCK:
		if (on_fetchquest > 0)
		{
			pointer = talk_foodtruck2;
			text_length = sizeof(talk_foodtruck2);
		}
		else
		{
			pointer = talk_foodtruck;
			text_length = sizeof(talk_foodtruck);
		}
		break;
	case TALK_KING2:
		pointer = talk_king2;
		text_length = sizeof(talk_king2);
		break;
	case TALK_SPACE:
		pointer = talk_space;
		text_length = sizeof(talk_space);
		break;
	case TALK_FETCHQUEST_1:
		pointer = fetch_1;
		text_length = sizeof(fetch_1);
		break;
	case TALK_FETCHTWO:
		pointer = fetch_2;
		text_length = sizeof(fetch_2);
		break;
	default:
		pointer = blank_1;
		text_length = sizeof(blank_1);
		break;
	}

	--text_length;

	ppu_on_all();
}

void initialize_title_screen(void)
{
	game_mode = MODE_TITLE;
	which_bg = 0;
	index = 0;

	ppu_off();
	oam_clear();
	draw_bg();
	multi_vram_buffer_horz(start_text, sizeof(start_text) - 1, NTADR_A(10, 19));

	multi_vram_buffer_horz(credits_1, sizeof(credits_1), NTADR_A(11, 24));
	multi_vram_buffer_horz(credits_2, sizeof(credits_2), NTADR_A(3, 25));
	multi_vram_buffer_horz(credits_3, sizeof(credits_3), NTADR_A(13, 26));

	ppu_on_all();
}

// void initialize_end_screen(void)
// {
// 	pal_fade_to(4, 0); // fade to black
// 	ppu_off();
// 	oam_clear();
// 	oam_hide_rest();
// 	// move player off screen
// 	player_x = -4;
// 	player_y = -4;
// 	shot_x = -4;
// 	shot_y = -4;
// 	game_mode = MODE_END;

// 	which_bg = 4; // set background to black
// 	draw_bg();

// 	multi_vram_buffer_horz(end_text2, sizeof(end_text2) - 1, NTADR_A(3, 20));

// 	ppu_on_all();
// 	pal_bright(4); // back to normal brighness
// }