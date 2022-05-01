/*
need for launch:
[x] bug:character clipping left and right oddly, maybe make him smaller vertically too
[x] add more talking, lots of talking
[] add run out of time ending
[x] warp toliets (make sprite walkable + changeroom code)
[x] add dungeon pushblock
[x] special overlay sprites that you walk behind
[x] actual music and sfx

space saving:
[x] clean up collision lists (just explicity add it in bg_collision_sub)

mini games: 
[x] fetch quest
[x] do reps with the brahs
[x] add robineete message and . on screen?
[x] add pipe level / jumping
[] rpg battle
[x] battle with game jobbies

fun list:
[x] king of video games says somethign if you've collected everything?
[] add guys to title screen
[] infinite hallway
[x] more yes/no actions
[x] money sprite explodes on things
[x] add intro screen (in the year 20XX, with custom names?)
[x] bug: remove money sprite when changing rooms

music:
[x] title tune
[x] indoor/outdoor music
[x] king of video games tune

sfx:
[x] contra theme
[x] jump sound
[x] zelda block
[x] mario noise
[x] toliet warp noise
[x] coin noise
[x] money hitting things

cleanup:
[] lots of ppu_off misused
[] clean up vars
[x] clean up sprites

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
	ppu_off();
	pal_bg(title_palette);
	pal_spr(palette_sp);
	set_vram_buffer();	// do at least once, sets a pointer to a buffer
	bank_spr(1);				// use the second set of tiles for sprites
	set_scroll_y(0xff); // shift the bg down 1 pixel

	initialize_title_screen();

	while (1) // game loop
	{
		while (game_mode == MODE_TITLE)
		{
			ppu_wait_nmi();

			// rotate colors this can be cleaned up
			temp1 = (get_frame_count() >> 3) & 3;
			// pal_col(6, title_color_rotate[temp1]);
			pal_col(5, title_color_rotate[temp1]);

			read_controller();

			// ALAN - space saving, I think this is duped gg code
			//  if (game_genie == 0xBB)
			//  {
			//  	multi_vram_buffer_horz(game_genie_text, sizeof(game_genie_text), NTADR_A(1, 18));
			//  }

			if (pad1_new & PAD_START)
			{
				initialize_intro_screen();
			}

			if (pad1_new & (PAD_ALL_DIRECTIONS + PAD_A + PAD_B))
			{
				if (pad1_new & code[index])
				{
					++index; // the next item in the code is pressed
				}
				else
				{
					index = 0; // reset the code
				}
			}
			if (index == 10 && code_active != 1) // 10 correct inputs
			{
				// alan, I bet we want this music_pause pattern everywhere.
				//  probably adds to the game
				music_pause(1);
				delay(15);
				sfx_play(SFX_CONTRA, 0);
				delay(450);
				music_pause(0);
				code_active = 1;
			}
		}
		while (game_mode == MODE_INTRO)
		{
			ppu_wait_nmi();

			read_controller();

			if (pad1_new & PAD_START)
			{
				song = SONG_INSIDE;
				set_music_speed(5);
				music_play(song);

				// set defaults
				game_mode = MODE_GAME;
				which_bg = STARTING_ROOM;
				player_x = 0x80;
				player_y = 0x80;

				minutes_left_tens = 0;
				minutes_left_ones = 0;
				seconds_left_tens = 0;
				seconds_left_ones = 0;

				bg_display_hud = 1;
				bg_fade_out = 1;

				draw_bg();
			}
		}
		while (game_mode == MODE_GAME) // gameloop
		{
			// can we appreciate for a moment at least how tight this
			//  game loop is? so easy to read, I'm proud of you alan

			ppu_wait_nmi();	 // wait till beginning of the frame
			countup_timer(); // keep ticking the timer

			read_controller();

			movement();
			action();

			draw_sprites();

			// for debugging, the lower the line, the less processing we have
			// gray_line();
		}
		while (game_mode == MODE_TALKING_TIME)
		{
			ppu_wait_nmi();
			countup_timer(); // keep ticking the game timer

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
					// this could be more typerwritery if we wanted to add a delay and sound
					// todo add delay and sfx
					one_vram_buffer(pointer[text_rendered], NTADR_A(2 + text_col, 3 + text_row));
					delay(1);
					++text_col;

					if (text_col == 27) // wrap to next row
					{
						++text_row;
						text_col = 0;
					}
				}
				++text_rendered;
			}

			read_controller();

			if (text_row == 3 && text_rendered != text_length) // if there's more than 1 page of
			{
				one_vram_buffer('&', NTADR_A(15, 6)); //& = down caret
				if (pad1_new & PAD_B)
				{
					// clear the old text
					draw_talking();
					// set text_row to 0
					text_row = 0;
				}
			}

			// section that deals with the text being fully rendered.
			if (text_rendered == text_length)
			{

				if (text_decision != TURN_OFF && text_action != CHOICE_FINISH_REPS && text_action != CHOICE_FINISH_FETCH) // if there's a text decision
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

					multi_vram_buffer_horz(no, sizeof(no) - 1, NTADR_A(11, 6));
					multi_vram_buffer_horz(yes, sizeof(yes) - 1, NTADR_A(18, 6));

					if (pad1_new & PAD_RIGHT)
					{
						text_decision = 1;
					}
					if (pad1_new & PAD_LEFT)
					{
						text_decision = 0;
					}
				}

				if (pad1_new & PAD_B)
				{
					temp1 = 0;
					// the user presses B at the completed screen to move on.
					reset_text_values();

					if (text_decision == 1) // if the text_decision was yes
					{
						// handle talking actions
						switch (text_action)
						{
						case CHOICE_PLAY_GAME:
							temp1 = 1;
							initialize_title_screen(); // turns on screen at end
							break;
						case CHOICE_FETCH_QUEST:
							on_fetchquest = 1;
							item_found = ITEM_BURGER_GAME;
							collision_action = TALK_FETCHQUEST_1;
							find_item();
							break;
						case CHOICE_BUY_FOOD:
							on_fetchquest = 2;
							item_found = ITEM_BURGER_GAME;
							collision_action = TALK_FETCHTWO;
							find_item();
							break;
						case CHOICE_DO_REPS_1:
							collision_action = TALK_DO_REPS;
							draw_talking();
							break;
						case CHOICE_DO_REPS_2:
							player_x = 0x70;
							player_y = 0x70;
							set_music_speed(2);
							rep_count = 0;
							rep_timer = REP_TIMER_MAX; // this is all based off rep_timer being set
							break;
						case CHOICE_FINISH_REPS:
							item_found = ITEM_KETTLEBELL_GAME;
							collision_action = TALK_ITEM_5;
							find_item();
							break;
						case CHOICE_FINISH_FETCH:
							on_fetchquest = 4;
							item_found = ITEM_BURGER_GAME;
							collision_action = TALK_ITEM_4;
							find_item();
							break;
						default:
							break;
						}
					}
				}
			}

			if (temp1 == 0)
			{
				// text finished, go back to game
				bg_display_hud = 1; // draw the hud
				game_mode = MODE_GAME;
				draw_bg();
				bg_fade_out = 1;				 // turn back on room fading
				display_hud_sprites = 1; // turn back on hud sprites
				item_found = 0;					 // reset item found (in case we were in the item found mode)
			}
		}
		while (game_mode == MODE_END)
		{

			if (temp6 < 6)
			{
				temp5 = get_frame_count();
				if ((temp5 & 100) == 100)
				{
					ppu_wait_nmi(); // wait till beginning of the frame
					oam_clear();		// clear the sprites
					// every 40 frames draw the next item
					// temp1 = 1; 							 // temp1 is the item number, gets shifted
					// temp2 = 0;							 // temp2 is the items displayed in the ending so far
					// temp3 = 0;							 // temp3 is the current item, from temp1&itemscollected
					// temp6 = 0 // this counts the ending steps.
					temp3 = items_collected & temp1;

					if (temp3)
					{
						draw_ending_special(); // special player and game
						draw_ending_sprites(); // draw games where they go
						temp2 += temp3;				 // if we got that item, add it to the displayed list
						delay(45);
					}
					temp1 = temp1 << 1; // shift the item up for the next time.
					++temp6;						// add one more step.
				}
				else
				{
					ppu_wait_nmi();
					draw_ending_sprites();
					oam_meta_spr(0x78, 0xB0, PlayerSprDown);
				}
			}

			// draw_ending_sprites(); // these sprites are always here (king and games)

			if (temp6 == 6)
			{
				oam_clear();
				draw_ending_sprites();
				oam_meta_spr(0x78, 0xB0, PlayerSprDown);
				ppu_wait_nmi();
				delay(40);
				draw_ending_text();
				ppu_wait_nmi();
				++temp6;
			}

			if (temp6 > 6)
			{
				read_controller();

				if (pad1_new & PAD_START)
				{
					initialize_title_screen(); // initial title load
				}
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
	// reset block move for dungeon room
	if (which_bg == DUNGEON_BLOCK_ROOM)
	{
		block_moved = 0;
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
			if (index > 63 && index < 224)
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

	if (which_bg == INTRO_ROOM)
	{
		ppu_mask(0x16);
	}

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

	if (which_bg == 20)
	{
		music_stop();
		sfx_play(SFX_KING, 0);
		delay(100);
		song = SONG_KING;
		set_music_speed(10);
		music_play(song);
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

	if (which_bg == COIN_GAME_ROOM && (items_collected & ITEM_COIN_GAME))
	{
		// will load blank sprites if they've collected thegame
		pointer = sprite_list[0];
	}
	else
	{
		pointer = sprite_list[which_bg];
	}

	temp3 = jobbies_map[which_bg];
	temp2 = 0; // if we're out of sprites
	for (index = 0, index2 = 0; index < MAX_ROOM_SPRITES; ++index)
	{
		if (temp2 == 1 && temp3 > 0)
		{
			sprites_type[index] = SPRITE_Jobbie;

			temp1 = rand8();
			temp2 = rand8();
			while (temp2 < 0x60 || temp2 > 0xb0)
			{
				temp2 = rand8();
			}
			if(temp1 < 0x10)
			{
				temp1 += 0x20;
			}
			if(temp1 > 0xe0)
			{
				temp1 -= 0x20;
			}
	

			sprites_x[index] = temp1;
			sprites_y[index] = temp2;
			--temp3;
		}
		else
		{

			temp1 = pointer[index2]; // get a byte of data
			if (temp1 == TURN_OFF)	 // we reached the end of the list
			{
				temp2 = 1;
				continue;
			}

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
}

void draw_sprites(void)
{
	if (collision_action == TALK_KING)
	{
		return;
	}

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
	if (which_bg == 23)
	{
		// forgroundtv
		// 80, 160, SPRITE_BackTV101,
		oam_meta_spr(80, 160, BackTV101);
	}
#pragma endregion

	draw_player_sprite();
	if (shot_x >= 0)
	{ // only draw the shot if it exists
		if (shot_hit > 0)
		{
			if (shot_hit > 3)
			{
				oam_meta_spr(shot_x, shot_y, ShotHit);
			}
			else
			{
				oam_meta_spr(shot_x, shot_y, ShotHitTwo);
			}

			--shot_hit;
			if (shot_hit == 0)
			{
				shot_x = -4;
				shot_y = -4;
			}
		}
		else
		{
			oam_meta_spr(shot_x, shot_y, Shot);
		}
	}

#pragma region room_sprites
	// offset code is for shuffling sprites if we have more than 8
	offset = get_frame_count() & 3; // returns 0,1,2,3
	offset = offset << 4;						// * 16, the size of the shuffle array
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
			oam_meta_spr(temp1, temp2, Alan92);
			break;
		case SPRITE_BRIAN93:
			oam_meta_spr(temp1, temp2, Brian93);
			break;
		case SPRITE_PlayerSprUp:
			oam_meta_spr(temp1, temp2, PlayerSprUp);
			break;
		case SPRITE_PunchoutMan112:
			oam_meta_spr(temp1, temp2, PunchoutMan112);
			break;
		case SPRITE_PunchOutMat113:
			oam_meta_spr(temp1, temp2, PunchOutMat113);
			break;
		case SPRITE_LunchLadyHead36:
			oam_meta_spr(temp1, temp2, LunchLadyHead36);
			break;
		case SPRITE_BaldRight22:
			oam_meta_spr(temp1, temp2, BaldRight22);
			break;
		case SPRITE_HairForward114:
			oam_meta_spr(temp1, temp2, HairForward114);
			break;
		case SPRITE_Banner99:
			oam_meta_spr(temp1, temp2, Banner99);
			break;
		case SPRITE_BoyKid44:
			oam_meta_spr(temp1, temp2, BoyKid44);
			break;
		case SPRITE_BaldBehind7:
			oam_meta_spr(temp1, temp2, BaldBehind7);
			break;
		case SPRITE_SkirtLady39:
			oam_meta_spr(temp1, temp2, SkirtLady39);
			break;
		case SPRITE_HairBehind10:
			oam_meta_spr(temp1, temp2, HairBehind10);
			break;
		case SPRITE_HatForward17:
			oam_meta_spr(temp1, temp2, HatForward17);
			break;
		case SPRITE_PrettyGirlBehindStand109:
			oam_meta_spr(temp1, temp2, PrettyGirlBehindStand109);
			break;
		case SPRITE_SideLadyRight86:
			oam_meta_spr(temp1, temp2, SideLadyRight86);
			break;
		case SPRITE_WideBoyBehind120:
			oam_meta_spr(temp1, temp2, WideBoyBehind120);
			break;
		case SPRITE_SleepyGuyBehind123:
			oam_meta_spr(temp1, temp2, SleepyGuyBehind123);
			break;
		case SPRITE_HairRight27:
			oam_meta_spr(temp1, temp2, HairRight27);
			break;
		case SPRITE_BigNoseLeft84:
			oam_meta_spr(temp1, temp2, BigNoseLeft84);
			break;
		case SPRITE_Wizard53:
			oam_meta_spr(temp1, temp2, Wizard53);
			break;
		case SPRITE_Car95:
			oam_meta_spr(temp1, temp2, Car95);
			break;
		case SPRITE_Car952:
			oam_meta_spr(temp1, temp2, Car952);
			break;
		case SPRITE_Car96:
			oam_meta_spr(temp1, temp2, Car96);
			break;
		case SPRITE_Car962:
			oam_meta_spr(temp1, temp2, Car962);
			break;
		case SPRITE_SkinnyHatMan49:
			oam_meta_spr(temp1, temp2, SkinnyHatMan49);
			break;
		case SPRITE_GlassesLeft31:
			oam_meta_spr(temp1, temp2, GlassesLeft31);
			break;
		case SPRITE_BaldForward13:
			oam_meta_spr(temp1, temp2, BaldForward13);
			break;
		case SPRITE_GirlKid47:
			oam_meta_spr(temp1, temp2, GirlKid47);
			break;
		case SPRITE_BlueBeard74:
			oam_meta_spr(temp1, temp2, BlueBeard74);
			break;
		case SPRITE_King75:
			oam_meta_spr(temp1, temp2, King75);
			break;
		case SPRITE_BigNoseRight83:
			oam_meta_spr(temp1, temp2, BigNoseRight83);
			break;
		case SPRITE_BaldTankBehind121:
			oam_meta_spr(temp1, temp2, BaldTankBehind121);
			break;
		case SPRITE_OldCoot63:
			oam_meta_spr(temp1, temp2, OldCoot63);
			break;
		case SPRITE_GlassesRight33:
			oam_meta_spr(temp1, temp2, GlassesRight33);
			break;
		case SPRITE_HairRight28:
			oam_meta_spr(temp1, temp2, HairRight28);
			break;
		case SPRITE_SideLadyRight87:
			oam_meta_spr(temp1, temp2, SideLadyRight87);
			break;
		case SPRITE_DressGirl61:
			oam_meta_spr(temp1, temp2, DressGirl61);
			break;
		case SPRITE_MuscleMan0:
			oam_meta_spr(temp1, temp2, MuscleMan0);
			break;
		case SPRITE_MuscleMan1:
			oam_meta_spr(temp1, temp2, MuscleMan1);
			break;
		case SPRITE_MuscleMan2:
			oam_meta_spr(temp1, temp2, MuscleMan2);
			break;
		case SPRITE_Girl4:
			oam_meta_spr(temp1, temp2, Girl4);
			break;
		case SPRITE_FroGuy55:
			oam_meta_spr(temp1, temp2, FroGuy55);
			break;
		case SPRITE_WideBoy69:
			oam_meta_spr(temp1, temp2, WideBoy69);
			break;
		case SPRITE_HatBehind117:
			oam_meta_spr(temp1, temp2, HatBehind117);
			break;
		case SPRITE_Ghost65:
			oam_meta_spr(temp1, temp2, Ghost65);
			break;
		case SPRITE_CostumeMan58:
			oam_meta_spr(temp1, temp2, CostumeMan58);
			break;
		case SPRITE_Wizard52:
			oam_meta_spr(temp1, temp2, Wizard52);
			break;
		case SPRITE_SideLadyLeft90:
			oam_meta_spr(temp1, temp2, SideLadyLeft90);
			break;
		case SPRITE_BeardSideManLeft79:
			oam_meta_spr(temp1, temp2, BeardSideManLeft79);
			break;
		case SPRITE_HairBehind9:
			oam_meta_spr(temp1, temp2, HairBehind9);
			break;
		case SPRITE_BaldBehind6:
			oam_meta_spr(temp1, temp2, BaldBehind6);
			break;
		case SPRITE_HairLeft24:
			oam_meta_spr(temp1, temp2, HairLeft24);
			break;
		case SPRITE_Ghost66:
			oam_meta_spr(temp1, temp2, Ghost66);
			break;
		case SPRITE_HairBehind11:
			oam_meta_spr(temp1, temp2, HairBehind11);
			break;
		case SPRITE_DressGirl60:
			oam_meta_spr(temp1, temp2, DressGirl60);
			break;
		case SPRITE_GlassesRight35:
			oam_meta_spr(temp1, temp2, GlassesRight35);
			break;
		case SPRITE_SkirtLady40:
			oam_meta_spr(temp1, temp2, SkirtLady40);
			break;
		case SPRITE_HairFront129:
			oam_meta_spr(temp1, temp2, HairFront129);
			break;
		case SPRITE_Girl3:
			oam_meta_spr(temp1, temp2, Girl3);
			break;
		case SPRITE_BaldBehind8:
			oam_meta_spr(temp1, temp2, BaldBehind8);
			break;
		case SPRITE_BaldLeft18:
			oam_meta_spr(temp1, temp2, BaldLeft18);
			break;
		case SPRITE_BaldTank73:
			oam_meta_spr(temp1, temp2, BaldTank73);
			break;
		case SPRITE_COIN:
			oam_meta_spr(temp1, temp2, Coin);
			break;
		case SPRITE_DungeonBlock:
			oam_meta_spr(temp1, temp2, DungeonBlock);
			break;
		case SPRITE_Jobbie:
			if ((get_frame_count() & 0x0f) > 0x08)
			{
				oam_meta_spr(temp1, temp2, Jobbie);
			}
			else
			{
				oam_meta_spr(temp1, temp2, JobbieTwo);
			}

		default:
			break;
		}
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
		if (items_collected & ITEM_KETTLEBELL_GAME)
		{
			oam_meta_spr(0x34, 0x20, KettleBell);
		}
		if (items_collected & ITEM_JOBBIES_GAME)
		{
			one_vram_buffer(5, NTADR_A(2, 4));
			one_vram_buffer(10, NTADR_A(3, 4));
			one_vram_buffer(8, NTADR_A(2, 5));
			one_vram_buffer(3, NTADR_A(3, 5));
		}

		oam_meta_spr(0xC0, 0x20, JobbieSmall);
		one_vram_buffer('x', NTADR_A(25, 4));
		one_vram_buffer(48 + player_jobbies_tens, NTADR_A(26, 4));
		one_vram_buffer(48 + player_jobbies_ones, NTADR_A(27, 4));

		if (code_active == 1)
		{
			oam_meta_spr(0xBA, 0x30, PlayerHead);
			multi_vram_buffer_horz(thirty_lives, sizeof(thirty_lives), NTADR_A(25, 6));
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
		if (!(items_collected & ITEM_COIN_GAME) && player_coins >= MAX_COINS)
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
		if (item_found == ITEM_KETTLEBELL_GAME)
		{
			oam_meta_spr(player_x, player_y - 16, KettleBell);
		}
		if (item_found == ITEM_JOBBIES_GAME)
		{
			oam_meta_spr(player_x, player_y - 16, Jobbie);
		}
	}

#pragma endregion
}

void draw_player_sprite(void)
{
	if (item_found) // special player sprite used if item found
	{
		oam_meta_spr(player_x, player_y, PrizeGuy94);
		return;
	}
	if (rep_timer > 0)
	{
		if ((rep_count & 1) == 0)
		{ // this should be like %2
			oam_meta_spr(player_x, player_y, PlayerSprDown);
		}
		else
		{
			oam_meta_spr(player_x, player_y, PrizeGuy94);
		}
		return;
	}

	switch (player_direction)
	{
	case DOWN_MOVE:

		if (!(pad1 & PAD_DOWN))
		{
			oam_meta_spr(player_x, player_y, PlayerSprDown);
			break;
		}

		if ((move_frames >= 24 && move_frames < 28) || (move_frames >= 8 && move_frames < 12))
		{
			oam_meta_spr(player_x, player_y, PlayerSprDownThree);
		}
		else if ((move_frames >= 16 && move_frames < 20) || (move_frames < 4))
		{
			oam_meta_spr(player_x, player_y, PlayerSprDownTwo);
		}
		else
		{
			oam_meta_spr(player_x, player_y, PlayerSprDown);
		}

		break;
	case LEFT_MOVE:

		// if the button's not pressed, display idle animation
		if (!(pad1 & PAD_LEFT))
		{
			oam_meta_spr(player_x, player_y, PlayerSprLeft);
			break;
		}
		// animation frames
		if (move_frames > 23)
		{
			oam_meta_spr(player_x, player_y, PlayerSprLeftFour);
			break;
		}
		if (move_frames > 19)
		{
			oam_meta_spr(player_x, player_y, PlayerSprLeftFive);
			break;
		}
		if (move_frames > 15)
		{
			oam_meta_spr(player_x, player_y, PlayerSprLeftFour);
			break;
		}
		if (move_frames > 7)
		{
			oam_meta_spr(player_x, player_y, PlayerSprLeftTwo);
			break;
		}
		if (move_frames > 3)
		{
			oam_meta_spr(player_x, player_y, PlayerSprLeftThree);
			break;
		}

		oam_meta_spr(player_x, player_y, PlayerSprLeft);

		break;
	case UP_MOVE:
		if (!(pad1 & PAD_UP))
		{
			oam_meta_spr(player_x, player_y, PlayerSprUp);
			break;
		}

		if ((move_frames >= 24 && move_frames < 28) || (move_frames >= 8 && move_frames < 12))
		{
			oam_meta_spr(player_x, player_y, PlayerSprUpThree);
		}
		else if ((move_frames >= 16 && move_frames < 20) || (move_frames < 4))
		{
			oam_meta_spr(player_x, player_y, PlayerSprUpTwo);
		}
		else
		{
			oam_meta_spr(player_x, player_y, PlayerSprUp);
		}

		break;
	case RIGHT_MOVE:

		// if the button's not pressed, display idle animation
		if (!(pad1 & PAD_RIGHT))
		{
			oam_meta_spr(player_x, player_y, PlayerSprRight);
			break;
		}
		// animation frames
		if (move_frames > 23)
		{
			oam_meta_spr(player_x, player_y, PlayerSprRightFour);
			break;
		}
		if (move_frames > 19)
		{
			oam_meta_spr(player_x, player_y, PlayerSprRightFive);
			break;
		}
		if (move_frames > 15)
		{
			oam_meta_spr(player_x, player_y, PlayerSprRightFour);
			break;
		}
		if (move_frames > 7)
		{
			oam_meta_spr(player_x, player_y, PlayerSprRightTwo);
			break;
		}
		if (move_frames > 3)
		{
			oam_meta_spr(player_x, player_y, PlayerSprRightThree);
			break;
		}

		oam_meta_spr(player_x, player_y, PlayerSprRight);

		break;
	default:
		oam_meta_spr(player_x, player_y, PlayerSprUp);
		break;
	}
}

void action(void)
{
	// check for shots
	if (pad1_new & PAD_A)
	{
		if (rep_timer > 0)
		{
			++rep_count;
			if ((rep_count & 1) == 0)
			{
				sfx_play(SFX_REP, 0);
			}
		}
		else
		{
			// the shot starts where the player is and moves in the direction
			// the player was facing when they shot.
			shot_x = player_x;
			shot_y = player_y;
			shot_direction = player_direction;
			sfx_play(SFX_SHOT, 0);
		}
	}
	if (rep_timer == 0 && rep_count > 0)
	{
		if (rep_count > MAX_REPS)
		{
			rep_count = 0;
			collision_action = TALK_REPS_FINISHED;
			draw_talking();
			return;
		}
		else
		{
			rep_count = 0;
			collision_action = TALK_MORE_REPS;
			draw_talking();
			return;
		}
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
				item_found = ITEM_ADVENTURE_GAME;
				collision_action = TALK_ITEM_3;
				find_item();
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
				move_block();
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
				move_block();
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
		--player_x;
		has_moved = 1;
		if (player_x == SCREEN_LEFT_EDGE)
			change_room_left();
	}
	else if (pad1 & PAD_RIGHT)
	{
		player_direction = RIGHT_MOVE;
		++player_x;
		has_moved = 1;
		if (player_x == SCREEN_RIGHT_EDGE)
			change_room_right();
	}

	// check left/right collisions
	bg_collision();
	sprite_collisions();
	// ejection
	if (collision_R)
	{
		--player_x;
		has_moved = 0;
	}
	if (collision_L)
	{
		++player_x;
		has_moved = 0;
	}

	// sprite movement
	for (index = 0; index < MAX_ROOM_SPRITES; ++index)
	{
		if (sprites_type[index] == SPRITE_Jobbie)
		{

			//  randomly move a sprite.

			temp1 = rand8(); // 0 - 255
			if (temp1 < 64)	 // only move 1/4th(ish)
			{

				// x movement for numbers like 0bXXXX XXX1
				if ((temp1 & 1) == 1)
				{
					if (sprites_x[index] < SCREEN_RIGHT_EDGE - 1)
					{
						++sprites_x[index];
					}
				}
				else
				{
					if (sprites_x[index] > SCREEN_LEFT_EDGE + 1)
					{
						--sprites_x[index];
					}
				}
				// y movement for numbers like 0bXXXX XX1X
				if ((temp1 & 2) >= 2)
				{
					if (sprites_y[index] < SCREEN_BOTTOM_EDGE + 1)
					{
						++sprites_y[index];
					}
				}
				else
				{
					if (sprites_y[index] > SCREEN_TOP_EDGE - 1)
					{
						--sprites_y[index];
					}
				}
			}
		}
	}

	if (which_bg == COIN_GAME_ROOM)
	{
		// add to player 'velocity' if they're in jump mode
		if (player_jump > 0)
		{
			player_y -= 4;
			player_jump -= 4;
		}

		// gravity
		++player_y;
		++player_y;

		// check collision and eject
		bg_collision();
		if (collision_D)
		{
			// eject from down collision
			--player_y;
			--player_y;

			// check for jumps only if down collision
			if (pad1_new & PAD_B)
			{
				// don't allow double jumps
				player_jump = PLAYER_MAX_JUMP;
				sfx_play(SFX_JUMP, 0);
			}
		}
	}

	// move up/down
	if (pad1 & PAD_UP && !has_moved)
	{
		player_direction = UP_MOVE;
		--player_y;
		if (player_y == SCREEN_TOP_EDGE)
			change_room_up();
	}
	else if (pad1 & PAD_DOWN && !has_moved)
	{
		player_direction = DOWN_MOVE;
		++player_y;
		if (player_y == SCREEN_BOTTOM_EDGE)
			change_room_down();
	}

	// check collision up/down
	bg_collision();
	sprite_collisions();
	// ejection
	if (collision_D)
	{
		--player_y;
	}
	if (collision_U)
	{
		++player_y;
	}

	if (player_direction == last_player_direction // player direction hasn't changed
			&& (pad1 & PAD_ALL_DIRECTIONS)						// one of the direction buttons is held down
			&& has_moved == 0)												// and the player hasn't moved
	{
		++push_timer;
	}
	else
	{
		push_timer = 0;
	}

#pragma endregion playerMovement

#pragma region shotMovement
	if (shot_x >= 0 && shot_hit == 0) // if there's a shot, update it's direction
	{
		switch (shot_direction)
		{
		case 0: // down
			++shot_y;
			++shot_y;
			break;
		case 1: // left
			--shot_x;
			--shot_x;
			break;
		case 2: // up
			--shot_y;
			--shot_y;
			break;
		case 3: // right
			++shot_x;
			++shot_x;
			break;
		default:
			break;
		}

		// if it's offscreen, get rid of it.
		if (shot_x > 250 || shot_x < 1 ||
				shot_y > 216 || shot_y < 64)
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
		Generic2.x = DUNGEON_BLOCK_X+8;
		Generic2.y = DUNGEON_BLOCK_Y;
		Generic2.width = 4;
		Generic2.height = 6;
		if (check_collision(&Generic, &Generic2))
		{
			which_bg = DUNGEON_GAME_ROOM;
			player_x = 0x30;
			player_y = 0x41;
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
		if (check_collision(&Generic, &Generic2))
		{
			which_bg = TOLIET_WARP_2_ROOM;
			player_x = TOLIET_WARP_2_X - 0x10;
			player_y = TOLIET_WARP_2_Y;
			toliet_warp();
		}
	}

	if (which_bg == TOLIET_WARP_2_ROOM)
	{
		// make the block a little smaller before activating
		Generic2.x = TOLIET_WARP_2_X + 7;
		Generic2.y = TOLIET_WARP_2_Y + 7;
		Generic2.width = 4;
		Generic2.height = 4;
		if (check_collision(&Generic, &Generic2))
		{
			which_bg = TOLIET_WARP_1_ROOM;
			player_x = TOLIET_WARP_1_X - 0x10;
			player_y = TOLIET_WARP_1_Y;
			toliet_warp();
		}
		else
		{ // check other toliet warp
			Generic2.x = TOLIET_WARP_3_X + 7;
			Generic2.y = TOLIET_WARP_3_Y + 7;
			if (check_collision(&Generic, &Generic2))
			{
				which_bg = COIN_GAME_ROOM;
				player_x = 0x20;
				player_y = 0x50;
				Generic.x = 0x20;
				Generic.y = 0x50;
				toliet_warp();
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
		if (check_collision(&Generic, &Generic2))
		{
			which_bg = TOLIET_WARP_2_ROOM;
			player_x = TOLIET_WARP_3_X - 0x10;
			player_y = TOLIET_WARP_3_Y;
			toliet_warp();
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
			item_found = ITEM_DUNGEON_GAME;
			collision_action = TALK_ITEM_1;
			find_item();
		}
	}

	if (which_bg == COIN_GAME_ROOM && (!(items_collected & ITEM_COIN_GAME)) && player_coins >= MAX_COINS)
	{
		Generic2.x = COIN_GAME_X + 7;
		Generic2.y = COIN_GAME_Y + 7;
		Generic2.width = 1;
		Generic2.height = 1;
		if (check_collision(&Generic, &Generic2))
		{
			item_found = ITEM_COIN_GAME;
			collision_action = TALK_ITEM_2;
			find_item();
		}
	}

#pragma endregion
}

void sprite_collisions(void)
{

	// set the first Generic to the players attributes
	Generic.x = player_x;
	Generic.y = player_y + (PLAYER_HEIGHT / 2); // player y is halfway down their body
	Generic.width = PLAYER_WIDTH;
	Generic.height = PLAYER_HEIGHT / 2; // player height is just the lower half of the body

	if (which_bg == COIN_GAME_ROOM && !(items_collected & ITEM_COIN_GAME))
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

	// go through all the sprites in the room
	// all other sprites are 16x16 (not always true)
	// but we'll put larger sprites in unreachable places
	Generic2.width = 16;
	Generic2.height = 16;
	for (index = 0; index < MAX_ROOM_SPRITES; ++index)
	{
		if (sprites_type[index] == TURN_OFF)
		{
			continue; // run out of sprites, stop checking collisions
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
				++collision_D;
				break;
			case UP:
				++collision_U;
				break;
			case LEFT:
				++collision_L;
				break;
			case RIGHT:
				++collision_R;
				break;
			default:
				break;
			}
		}

		if (shot_x >= 0 && shot_hit == 0)
		{
			// check shot collision for each sprite
			// index is the sprite
			Generic3.x = shot_x;
			Generic3.y = shot_y;
			Generic3.width = 4;
			Generic3.height = 4;
			if (check_collision(&Generic3, &Generic2))
			{
				if (sprites_type[index] == SPRITE_Jobbie)
				{
					// remove from map
					if (jobbies_map[which_bg] > 0)
					{
						jobbies_map[which_bg] = jobbies_map[which_bg] - 1;
						++player_jobbies;
						if (player_jobbies_ones < 9)
						{
							++player_jobbies_ones;
						}
						else
						{
							++player_jobbies_tens;
							player_jobbies_ones = 0;
						}
						// did we just kill the last jobbie?
						if (player_jobbies == MAX_JOBBIES)
						{
							collision_action = TALK_ITEM_6;
							item_found = ITEM_JOBBIES_GAME;
							find_item();
						}
					}
					sprites_type[index] = TURN_OFF;
				}
				// shot hit something
				shot_hit = 6; // 6 frames of shot hit.
				sfx_play(SFX_GUNTHUD, 0);
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

	temp6 = temp5 = player_x + 2; // upper left (temp6 = save for reuse)

	// upper left
	temp1 = (temp5)&0xff; // low byte x
	// temp2 = temp5 >> 8;				// high byte x
	temp3 = player_y + PLAYER_PIXELS; // y top
	bg_collision_sub();
	if (collision)
	{
		++collision_L;
		++collision_U;
	}

	// upper right
	temp5 += PLAYER_WIDTH;
	temp1 = temp5 & 0xff; // low byte x
	// temp2 = temp5 >> 8;		// high byte x
	//  temp3 (y) is unchanged
	bg_collision_sub();
	if (collision)
	{
		++collision_R;
		++collision_U;
	}

	// bottom right,temp1(x low byte) hasn't changed
	// y bottom is temp3
	temp3 += 8; // this is a huge hack, it should be somehting like temp3 += PLAYER_HEIGHT
	// if(L_R_switch) temp3 -= 2; // fix bug, walking through walls
	// eject_D = (temp3 + 1) & 0x0f;
	if (temp3 >= 0xf0)
		return;

	bg_collision_sub();

	if (collision)
	{ // find a corner in the collision map
		++collision_R;
		++collision_D;
	}

	// bottom left
	temp1 = temp6 & 0xff; // low byte x
	// temp2 = temp6 >> 8;		// high byte x

	// temp3, y is unchanged

	bg_collision_sub();

	if (collision)
	{ // find a corner in the collision map
		++collision_L;
		++collision_D;
	}
}

void bg_collision_sub(void)
{
	coordinates = (temp1 >> 4) + (temp3 & 0xf0);

	collision = c_map[coordinates];

	// collision = collision_list[which_bg][collision];

	// const unsigned char * const outside[] = {2,3,4,7,8,9,11,12,14,21,26,27,29};
	// const unsigned char * const inside[] = {17,18,19,22,23,24,25,28};
	// const unsigned char * const trans[] = {5,10,13};
	// const unsigned char * const cliff[] = {20};

	if (which_bg == 17 || which_bg == 18 || which_bg == 19 || which_bg == 22 || which_bg == 23 || which_bg == 24 || which_bg == 25 || which_bg == 28)
	{ // inside
		if (collision == 0 || collision == 37 || collision == 50)
		{
			collision = 0;
		}
		else
		{
			collision = 1;
		}
	}
	else if (which_bg == 5 || which_bg == 10 || which_bg == 13)
	{ // trans
		if (collision < 3 || collision == 4 || collision == 5 || collision == 18)
		{
			collision = 0;
		}
		else
		{
			collision = 1;
		}
	}
	else if (which_bg == 20)
	{ // cliff
		if (collision < 16)
		{
			collision = 0;
		}
		else
		{
			collision = 1;
		}
	}
	else
	{ // outside

		if (collision < 16 || collision == 30)
		{
			collision = 0;
		}
		else
		{
			collision = 1;
		}
	}
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
		music_play(SONG_INSIDE);
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

	if (which_bg == 21)
	{
		// going up from the back door area
		which_bg = 11; // teleport to the top outdoors
	}
	else if (which_bg < 25)
	{
		which_bg = which_bg - 5;
	}
	else if (which_bg == 25) // space saving hax
	{
		which_bg = 22;
	}

	else
	{
		--which_bg;
	}

	if (which_bg == 0)
	{ // going up from the dungeon
		which_bg = DUNGEON_BLOCK_ROOM;
		// put the player near the dungeon block
		player_x = 50;
		player_y = 100;
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

	if (which_bg == 29) // the back door
	{
		collision_action = TALK_LOCKED_DOORS;
		draw_talking();
		music_pause(1);
		delay(20);
		sfx_play(SFX_GUNTHUD, 0);
		music_pause(0);
		return;
	}

	draw_bg();
}

void countup_timer(void)
{
	++frame;

	if (frame == 60)
	{
		if (rep_timer > 0)
		{
			--rep_timer;
		}

		frame = 0;
		// nes is bad at mul and div math, so just doing counting for clock.
		if (seconds_left_ones == 9)
		{
			seconds_left_ones = 0;
			if (seconds_left_tens == 5)
			{
				seconds_left_tens = 0;
				if (minutes_left_ones == 9)
				{
					++minutes_left_tens;
				}
				else
				{
					++minutes_left_ones;
				}
			}
			else
			{
				++seconds_left_tens;
			}
		}
		else
		{
			++seconds_left_ones;
		}

		// update the vram_buffer values only every 60 frames
		draw_timer();
	}
}

void draw_timer(void)
{
	if (game_mode == MODE_GAME)
	{
		if (display_hud_sprites == 1)
		{
			// multi_vram_buffer_horz(time, sizeof(time) - 1, NTADR_A(10, 6));
			one_vram_buffer(48 + minutes_left_tens, NTADR_A(23, 3));
			one_vram_buffer(48 + minutes_left_ones, NTADR_A(24, 3));
			one_vram_buffer(':', NTADR_A(25, 3));
			one_vram_buffer(48 + seconds_left_tens, NTADR_A(26, 3));
			one_vram_buffer(48 + seconds_left_ones, NTADR_A(27, 3));
		}
	}
}

void draw_hud(void)
{
	temp1 = B_LOC;
	temp2 = 'B';
	draw_hud_button();
	// draw buttons B
	temp1 = A_LOC;
	temp2 = 'A';
	draw_hud_button();
}
void draw_hud_button(void)
{
	one_vram_buffer(0xee, NTADR_A(temp1, 2));
	one_vram_buffer(temp2, NTADR_A(temp1 + 1, 2));
	one_vram_buffer(0xef, NTADR_A(temp1 + 2, 2));

	multi_vram_buffer_vert(sidebar, 3, NTADR_A(temp1, 3));
	multi_vram_buffer_vert(sidebar, 3, NTADR_A(temp1 + 2, 3));
	multi_vram_buffer_horz(bottombar, 3, NTADR_A(temp1, 6));
}

void draw_talking(void)
{
	if (collision_action == TALK_KING)
	{
		// talking with the king ends the game
		initialize_end_screen();
		return;
	}
	// writes to the HUD area, then starts the talking mode
	// which writes 1 char a frame.
	// ppu_off(); -ALAN, turned this off to save space, this should happen in draw_bg
	game_mode = MODE_TALKING_TIME;
	text_decision = TURN_OFF; // no text decisions

	bg_fade_out = 0;		// don't fade bg for draw_bg for talking
	bg_display_hud = 0; // don't draw hud for draw_bg for talking
	draw_bg();

	multi_vram_buffer_horz(topBar, sizeof(topBar), NTADR_A(1, 2));
	multi_vram_buffer_horz(bottomBar, sizeof(bottomBar), NTADR_A(1, 6));

	// sides of the box
	multi_vram_buffer_vert(sidebar, sizeof(sidebar), NTADR_A(1, 3));
	multi_vram_buffer_vert(sidebar, sizeof(sidebar), NTADR_A(30, 3));

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
	case TALK_ITEM_6:
		pointer = item_6;
		text_length = sizeof(item_6);
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
		if (!(items_collected & ITEM_KETTLEBELL_GAME))
		{
			pointer = talk_muscle1;
			text_length = sizeof(talk_muscle1);
			text_decision = 0;
			text_action = CHOICE_DO_REPS_1;
		}
		else
		{
			pointer = talk_reps_done;
			text_length = sizeof(talk_reps_done);
		}
		break;
	case TALK_MUSCLE2:
		pointer = talk_muscle2;
		text_length = sizeof(talk_muscle2);
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
	case TALK_DO_REPS:
		pointer = talk_do_reps;
		text_length = sizeof(talk_do_reps);
		text_decision = 0;
		text_action = CHOICE_DO_REPS_2;
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
			text_action = CHOICE_FINISH_FETCH;
			text_decision = 1;
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
	case TALK_REPS_FINISHED:
		set_music_speed(5);
		pointer = talk_reps_finished;
		text_length = sizeof(talk_reps_finished);
		text_action = CHOICE_FINISH_REPS;
		text_decision = 1;
		break;
	case TALK_MORE_REPS:
		set_music_speed(5);
		pointer = talk_more_reps;
		text_length = sizeof(talk_more_reps);
		break;
	case TALK_ITEM_5:
		pointer = item_5;
		text_length = sizeof(item_5);
		break;
	case TALK_DLC:
		pointer = talk_dlc;
		text_length = sizeof(talk_dlc);
		break;
	case TALK_CLIP:
		pointer = talk_clip;
		text_length = sizeof(talk_clip);
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
	collision_action = TURN_OFF;
	bg_display_hud = 0;			 // draw the hud
	bg_fade_out = 1;				 // turn back on room fading
	display_hud_sprites = 1; // turn back on hud sprites
	item_found = 0;					 // reset item found (in case we were in the item found mode)
	items_collected = 0;
	on_fetchquest = 0;
	code_active = 0;
	index = 0;
	player_coins = 0;
	player_jobbies = 0;
	player_jobbies_ones = 0;
	player_jobbies_tens = 0;
	for (temp1 = 0; temp1 < 30; ++temp1)
	{
		jobbies_map[temp1] = jobbies_map_init[temp1];
	}

	song = SONG_TITLE;
	set_music_speed(5);
	music_play(song);
	game_mode = MODE_TITLE;
	which_bg = 0;
	index = 0;

	// ppu_off();
	// oam_clear();
	draw_bg();
	multi_vram_buffer_horz(start_text, sizeof(start_text) - 1, NTADR_A(10, 20));

	multi_vram_buffer_horz(credits_1, sizeof(credits_1), NTADR_A(11, 24));
	multi_vram_buffer_horz(credits_2, sizeof(credits_2), NTADR_A(3, 25));
	multi_vram_buffer_horz(credits_3, sizeof(credits_3), NTADR_A(13, 26));

	game_genie = 0xAF;
	if (game_genie == 0xBB)
	{
		ppu_wait_nmi();
		delay(60);
		// todo: wow, play a sound if we could fit it.
		multi_vram_buffer_horz(game_genie_text, sizeof(game_genie_text), NTADR_A(1, 18));
	}

	// ppu_on_all();
}

void initialize_end_screen(void)
{
	// move player off screen
	// just doing everything here manually
	// drawing sprites, text, etc.

	game_mode = MODE_END;

	which_bg = KING_ROOM;
	display_hud_sprites = 0;
	bg_display_hud = 0;
	draw_bg();

	// game time:
	multi_vram_buffer_horz(time, sizeof(time) - 1, NTADR_A(11, 26));
	one_vram_buffer(48 + minutes_left_tens, NTADR_A(16, 26));
	one_vram_buffer(48 + minutes_left_ones, NTADR_A(17, 26));
	one_vram_buffer(':', NTADR_A(18, 26));
	one_vram_buffer(48 + seconds_left_tens, NTADR_A(19, 26));
	one_vram_buffer(48 + seconds_left_ones, NTADR_A(20, 26));

	temp1 = 1; // temp1 is the item number, gets shifted
	temp2 = 0; // temp2 is the items displayed in the ending so far
	temp3 = 0; // temp3 is the current item, from temp1&itemscollected
	temp4 = 0; // num items collected
	temp6 = 0; // this is if the ending is done, counting the steps
}

void draw_ending_special(void)
{

	sfx_play(SFX_VICTORY, 0);
	oam_meta_spr(0x78, 0xB0, PrizeGuy94);
	switch (temp3)
	{
	case ITEM_ADVENTURE_GAME:
		oam_meta_spr(0x78, 0xA0, AdventureGameBig);
		break;
	case ITEM_COIN_GAME:
		oam_meta_spr(0x78, 0xA0, GamePrize97);
		break;
	case ITEM_DUNGEON_GAME:
		oam_meta_spr(0x78, 0xA0, FloppyDisk125);
		break;
	case ITEM_BURGER_GAME:
		if (on_fetchquest == 4)
		{
			oam_meta_spr(0x78, 0xA0, BurgerGame);
		}
		else
		{
			--temp4;
			// decrement it becase we don't have this game.
			// and we're gonna inc it at the end of this.
		}

		break;
	case ITEM_KETTLEBELL_GAME:
		oam_meta_spr(0x78, 0xA0, KettleBell);
		break;
	case ITEM_JOBBIES_GAME:
		oam_meta_spr(0x78, 0xA0, Jobbie);
		break;
	default:
		break;
	}
	++temp4; // add to items collected
}

void draw_ending_text(void)
{
	if (temp4 == 0)
	{
		multi_vram_buffer_horz(ending_0, sizeof(ending_0), NTADR_A(6, 4));
	}
	else
	{
		if (temp4 == 6)
		{
			multi_vram_buffer_horz(ending_5, sizeof(ending_5), NTADR_A(1, 3));
		}
		multi_vram_buffer_horz(ending_X, sizeof(ending_X), NTADR_A(10, 4));
		multi_vram_buffer_horz(ending_Y, sizeof(ending_Y), NTADR_A(11, 5));

		// specific name
		switch (temp4)
		{
		case 1:
			multi_vram_buffer_horz(serf, 4, NTADR_A(6, 5));
			break;
		case 2:
			multi_vram_buffer_horz(vassal, 6, NTADR_A(4, 5));
			break;
		case 3:
			multi_vram_buffer_horz(squire, 6, NTADR_A(4, 5));
			break;
		case 4:
			multi_vram_buffer_horz(knight, 6, NTADR_A(4, 5));
			break;
		case 5:
			multi_vram_buffer_horz(duke, 4, NTADR_A(6, 5));
			break;
		case 6:
			multi_vram_buffer_horz(king, 4, NTADR_A(6, 5));
			break;
		default:
			break;
		}
	}
}

void draw_ending_sprites(void)
{
	// just imagine it's every frame
	// ooooh, dont clear, just draw what's in it.

	// always draw the king in the same spot.
	oam_meta_spr(0x78, 0x60, King75);

	// draw the games that are collected
	if (temp2 & ITEM_ADVENTURE_GAME)
	{
		oam_meta_spr(0x20, 0x68, AdventureGameBig);
	}
	if (temp2 & ITEM_COIN_GAME)
	{
		oam_meta_spr(0x40, 0x48, GamePrize97);
	}
	if (temp2 & ITEM_DUNGEON_GAME)
	{
		oam_meta_spr(0xCF, 0x68, FloppyDisk125);
	}
	if (temp2 & ITEM_BURGER_GAME)
	{
		if (on_fetchquest == 4)
		{
			oam_meta_spr(0xB0, 0x48, BurgerGame);
		}
	}
	if (temp2 & ITEM_KETTLEBELL_GAME)
	{
		oam_meta_spr(0x82, 0x38, KettleBell);
	}
	if (temp2 & ITEM_JOBBIES_GAME)
	{
		oam_meta_spr(0x72, 0x38, Jobbie);
		// one_vram_buffer(5, NTADR_A(14, 7));
		// one_vram_buffer(10, NTADR_A(14, 7));
		// one_vram_buffer(8, NTADR_A(15, 8));
		// one_vram_buffer(3, NTADR_A(15, 8));
	}
}

void initialize_intro_screen(void)
{
	game_mode = MODE_INTRO;
	which_bg = INTRO_ROOM;
	draw_bg();

	multi_vram_buffer_horz(intro_1, sizeof(intro_1), NTADR_A(7, 10));
	multi_vram_buffer_horz(intro_2, sizeof(intro_2), NTADR_A(6, 12));
	multi_vram_buffer_horz(intro_3, sizeof(intro_3), NTADR_A(3, 14));
	multi_vram_buffer_horz(intro_4, sizeof(intro_4), NTADR_A(4, 16));
}

void read_controller(void)
{
	pad1 = pad_poll(0);				 // read the first controller
	pad1_new = get_pad_new(0); // newly pressed button. do pad_poll first
}

void find_item(void)
{
	// item_found is set before this code
	// collision_action is set before this for the draw_talking
	sfx_play(SFX_VICTORY, 0);
	items_collected = items_collected | item_found; // pick up the item
	draw_talking();
}

void move_block(void)
{
	music_pause(1);
	sfx_play(SFX_MYSTERY, 0);
	delay(100);
	music_play(0);
	block_moved = 1; // done moving
}

void toliet_warp(void)
{
	sfx_play(SFX_WARP_TOLIET, 0);
	draw_bg();
}