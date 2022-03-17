#define SCREEN_LEFT_EDGE 0x00
#define SCREEN_RIGHT_EDGE 0xf0
#define SCREEN_TOP_EDGE 0x40
#define SCREEN_BOTTOM_EDGE 0xd0

#define ACTION_HEIGHT 4
#define ACTION_WIDTH 4

#define PLAYER_LEFT_EDGE 0x01
#define PLAYER_RIGHT_EDGE 0xef
#define PLAYER_TOP_EDGE 0x42
#define PLAYER_BOTTOM_EDGE 0xcf

#define PAD_ALL_DIRECTIONS	0x0f

#define DOWN_MOVE 0x00
#define LEFT_MOVE 0x01
#define UP_MOVE 0x02
#define RIGHT_MOVE 0x03

#define TEXT_BOX_X 6
#define TEXT_BOX_Y 12
#define TEXT_BOX_LENGTH 18
#define TEXT_BOX_HEIGHT 8

// HUD stuff
#define A_LOC 16
#define B_LOC 12

#pragma bss-name(push, "ZEROPAGE")

// GLOBAL VARIABLES
unsigned char pad1;
unsigned char pad1_new;
unsigned char collision;
unsigned char collision_L;
unsigned char collision_R;
unsigned char collision_U;
unsigned char collision_D;
unsigned char collision_action;
unsigned char which_bg = 0;
unsigned char block_moved = 0;
unsigned char text_rendered = 0;
unsigned char text_row = 0;
unsigned char text_col = 0;
unsigned char text_finished = 0;
unsigned char text_x = 1;
unsigned char text_y = 1;
unsigned char push_timer = 0;
const unsigned char *p_maps;
unsigned char coordinates;
unsigned char temp1;
unsigned char temp2;
unsigned char temp3;
unsigned char temp4;
unsigned char temp_x;
unsigned char temp_y;
unsigned char player_x = 64;
unsigned char player_y = 60;
unsigned char shot_direction = 0;  // 0 = down, 1 = left, 2 = up, 3 = right
unsigned char shot_x = -4;
unsigned char shot_y = -4;

unsigned int minutes_left = 1;
unsigned int seconds_left_tens = 0;
unsigned int seconds_left_ones = 1;

// room loader code
int address;
unsigned char x; 
unsigned char y;
unsigned char index;

unsigned char player_height = 14;
unsigned char player_width = 14;
unsigned char i;
unsigned char player_direction = 0; // 0 = down, 1 = left, 2 = up, 3 = right
unsigned char last_player_direction = 0; // 0 = down, 1 = left, 2 = up, 3 = right
unsigned char move_frames = 0;
unsigned char has_moved = 0;
unsigned char display_hud = 0;
unsigned char frame = 0;
unsigned char talk_frame = 0;
unsigned char temp1;
unsigned char text_to_use = 0;
const unsigned char title_text[] = "SIMUALTOR";
const unsigned char start_text[] = "Press  Start";
const unsigned char text_box[] = "                              ";
const unsigned char intro_text1[] = "You're late to the";
const unsigned char intro_text2[] = "Central Ohio Retro Gaming";
const unsigned char intro_text3[] = "convention, hurry and";
const unsigned char intro_text4[] = "find some good games.";
const unsigned char jeqb_text[] = "You found a copy of JEQB";
const unsigned char dashes[] = "-----------------------------";
const unsigned char topBar[] = {0xee,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xef};
const unsigned char bottomBar[] = {0xfe,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xff};
const unsigned char end_text2[] = "Press Start to play again";

const unsigned char game_text1[] = "Just some old video games";
const unsigned char game_text2[] = "You found a copy of Warren Robinett's Adventure for Atari 2600";
const unsigned char game_text34[] = "Just some arcade games with broken joysticks";
const unsigned char game_text35[] = "Pinball machines, but you're out of quarters";


const unsigned char long_text[] = "The quick brown fox jumps over the lazy dogs.";

const unsigned char clock_text[] = "Time Left: ";
const unsigned char items_text[] = "Items Collected:    0 0 *";

const unsigned char title_color_rotate[]={
	0x4,0x6,0x19,0x2
};

unsigned char game_mode;
enum
{
	MODE_TITLE,
	MODE_GAME,
	MODE_PAUSE,
	MODE_SWITCH,
	MODE_TALKING_TIME,
	MODE_END,
	MODE_GAME_OVER
};

#pragma bss-name(push, "BSS")

unsigned char c_map[240];// collision map
unsigned char a_map[240];// action map
unsigned char s_map[240];// sprite map


// these are the 4 backgrounds
// collision data, made by exporting csv from Tiled, and slight modification by CSV2C.py
#include "CSV/a_arcade.c"
#include "CSV/room_1.c"
#include "CSV/room_3.c"
#include "CSV/room_4.c"
#include "CSV/room_5.c"
#include "CSV/room_6.c"
#include "CSV/room_8.c"
#include "CSV/room_9.c"
#include "CSV/room_10.c"
#include "CSV/room_12.c"
#include "CSV/room_13.c"
#include "CSV/room_14.c"
#include "CSV/room_15.c"
#include "CSV/room_18.c"
#include "CSV/room_19.c"
#include "CSV/room_20.c"
#include "CSV/room_23.c"
#include "CSV/room_24.c"
#include "CSV/room_25.c"
#include "CSV/room_28.c"
#include "CSV/room_33.c"
#include "CSV/room_38.c"
#include "CSV/room_43.c"
#include "CSV/room_46.c"
#include "CSV/room_47.c"
#include "CSV/room_48.c"
#include "CSV/title.c"
#include "CSV/blank.c"

const unsigned char cliff_palette[16]={
	0x1b,0x0f,0x30,0x2c,0x1b,0x17,0x11,0x0f,0x1b,0x07,0x17,0x2a,0x1b,0x06,0x37,0x3d
	};

const unsigned char title_palette[16]={ 
	0x0f,0x0f,0x30,0x2c,0x0f,0x01,0x21,0x31,0x0f,0x06,0x16,0x26,0x0f,0x09,0x19,0x29
	 };

const unsigned char trans_palette[16]={
	0x0f,0x0f,0x30,0x2c,0x0f,0x16,0x3d,0x37,0x0f,0x06,0x37,0x2a,0x0f,0x2a,0x1b,0x17
	 };

const unsigned char inside_palette[16]={ 
	0x0f,0x0f,0x30,0x2c,0x0f,0x16,0x3d,0x37,0x0f,0x06,0x37,0x2a,0x0f,0x2d,0x3d,0x1a
	};

const unsigned char outside_palette[16]={ 
	0x1b,0x0f,0x30,0x2c,0x1b,0x17,0x11,0x0f,0x1b,0x07,0x17,0x2a,0x1b,0x05,0x38,0x3d
	};

const unsigned char palette_sp[] = {
	0x1b,0x37,0x24,0x17,0x1b,0x36,0x12,0x16,0x1b,0x17,0x21,0x37,0x1b,0x2d,0x3d,0x37
};

//which room uses which metatiles
const unsigned char metatiles_set[] = {

};

// 5 bytes per metatile definition, tile TL, TR, BL, BR, palette 0-3
// T means top, B means bottom, L left,R right
// 51 maximum # of metatiles = 255 bytes

const unsigned char cliff_metatiles[]={
	0, 0, 0, 0,  0,
	25, 25, 25, 25,  1,
	14, 14, 14, 14,  1,
	25, 25, 10, 12,  1,
	25, 25, 12, 12,  1,
	25, 25, 12, 11,  1,
	26, 28, 25, 25,  1,
	28, 28, 25, 25,  1,
	28, 27, 25, 25,  1,
	13, 25, 13, 25,  1,
	25, 29, 25, 29,  1,
	167, 168, 168, 167,  2,
	31, 25, 129, 31,  1,
	25, 25, 129, 129,  1,
	31, 25, 129, 25,  1,
	25, 25, 129, 31,  1,
	9, 9, 9, 9,  1,
	10, 9, 9, 9,  1,
	9, 9, 26, 9,  1,
	9, 11, 9, 9,  1,
	9, 9, 9, 27,  1,
	129, 129, 129, 129,  1,
	129, 129, 15, 15,  1,
	15, 15, 37, 37,  1,
	30, 30, 30, 30,  2,
	30, 43, 43, 30,  2,
	43, 30, 43, 43,  2,
	43, 43, 30, 43,  2,
	30, 30, 30, 43,  2,
	37, 37, 9, 37,  1,
	9, 37, 37, 37,  1,
	9, 129, 129, 129,  1,
	226, 227, 242, 243,  2,
	214, 215, 230, 231,  2,
	230, 231, 246, 247,  2,
	216, 217, 232, 233,  2,
	248, 249, 244, 245,  2,
	228, 229, 244, 245,  2,
	234, 234, 250, 250,  2,
	224, 225, 240, 241,  0,
	37, 37, 37, 37,  1,
	15, 129, 37, 15,  1,
	37, 15, 37, 37,  1,
	9, 37, 9, 9,  1,
	129, 129, 129, 129,  0,
};

const unsigned char trans_metatiles[]={
	0, 0, 0, 0,  0,
	9, 9, 9, 9,  3,
	211, 0, 211, 0,  0,
	234, 234, 250, 250,  2,
	167, 168, 168, 167,  2,
	193, 193, 193, 193,  1,
	1, 1, 17, 17,  2,
	2, 3, 2, 3,  2,
	18, 19, 18, 19,  2,
	4, 4, 20, 20,  2,
	1, 5, 21, 19,  2,
	8, 2, 20, 24,  2,
	2, 7, 23, 20,  2,
	6, 1, 2, 22,  2,
	204, 205, 220, 221,  1,
	235, 236, 251, 252,  1,
	224, 225, 240, 241,  1,
	0, 203, 218, 219,  1,
	206, 207, 222, 223,  3,
	16, 16, 16, 16,  1,
	136, 136, 152, 152,  1,
};

const unsigned char outside_metatiles[]={
	0, 0, 0, 0,  0,
	25, 25, 25, 25,  1,
	14, 14, 14, 14,  1,
	25, 25, 10, 12,  1,
	25, 25, 12, 12,  1,
	25, 25, 12, 11,  1,
	26, 28, 25, 25,  1,
	28, 28, 25, 25,  1,
	28, 27, 25, 25,  1,
	13, 25, 13, 25,  1,
	25, 29, 25, 29,  1,
	167, 168, 168, 167,  2,
	193, 193, 193, 193,  3,
	129, 129, 129, 129,  0,
	211, 129, 211, 129,  0,
	192, 0, 208, 209,  0,
	9, 9, 9, 9,  1,
	10, 9, 9, 9,  1,
	9, 9, 26, 9,  1,
	9, 11, 9, 9,  1,
	9, 9, 9, 27,  1,
	1, 1, 17, 17,  3,
	2, 3, 2, 3,  3,
	18, 19, 18, 19,  3,
	4, 4, 20, 20,  3,
	1, 5, 21, 19,  3,
	6, 1, 19, 22,  3,
	19, 7, 23, 1,  3,
	8, 19, 1, 24,  3,
	136, 136, 152, 152,  3,
	0, 203, 218, 219,  0,
	204, 205, 220, 221,  0,
	226, 227, 242, 243,  2,
	214, 215, 230, 231,  2,
	230, 231, 246, 247,  2,
	216, 217, 232, 233,  2,
	248, 249, 244, 245,  2,
	228, 229, 244, 245,  2,
	234, 234, 250, 250,  2,
	224, 225, 240, 241,  0,
	235, 236, 251, 252,  3,
	0, 0, 165, 165,  3,
	194, 195, 210, 0,  0,
	195, 196, 0, 212,  0,
	197, 198, 213, 201,  0,
	199, 200, 202, 201,  0,
};

const unsigned char inside_metatiles[]={
	0, 0, 0, 0,  0,
	1, 1, 17, 17,  2,
	2, 3, 2, 3,  2,
	18, 19, 18, 19,  2,
	4, 4, 20, 20,  2,
	1, 5, 21, 19,  2,
	6, 1, 2, 22,  2,
	2, 7, 23, 20,  2,
	8, 19, 20, 24,  2,
	128, 130, 144, 146,  3,
	132, 133, 144, 146,  3,
	150, 151, 144, 146,  3,
	128, 129, 144, 145,  3,
	129, 130, 145, 146,  3,
	147, 131, 144, 145,  3,
	149, 133, 145, 146,  3,
	132, 135, 144, 145,  3,
	134, 148, 145, 146,  3,
	128, 130, 129, 129,  3,
	132, 130, 131, 135,  3,
	147, 133, 129, 134,  3,
	169, 170, 144, 146,  3,
	171, 172, 183, 184,  1,
	171, 172, 185, 186,  1,
	171, 172, 187, 188,  3,
	174, 175, 190, 191,  1,
	161, 160, 177, 161,  1,
	176, 160, 176, 179,  0,
	162, 163, 176, 179,  3,
	137, 138, 153, 154,  0,
	137, 143, 153, 154,  1,
	137, 159, 153, 154,  2,
	137, 158, 153, 154,  3,
	139, 140, 155, 156,  1,
	173, 173, 189, 189,  1,
	141, 142, 157, 0,  1,
	0, 166, 0, 182,  1,
	0, 203, 218, 219,  1,
	204, 205, 220, 221,  1,
	164, 0, 180, 181,  1,
	224, 225, 240, 241,  1,
	0, 0, 165, 165,  1,
	234, 234, 250, 250,  2,
	136, 136, 152, 152,  1,
	235, 236, 251, 252,  3,
	192, 0, 208, 209,  3,
	194, 195, 210, 0,  2,
	195, 196, 0, 212,  2,
	197, 198, 213, 201,  2,
	199, 200, 202, 201,  2,
};

const unsigned char title_metatiles[]={
	0, 0, 0, 0,  0,
	123, 123, 0, 0,  1,
	92, 0, 125, 0,  1,
	92, 0, 124, 0,  1,
	0, 0, 126, 0,  1,
	124, 0, 93, 123,  1,
	91, 92, 93, 92,  1,
	126, 91, 124, 124,  1,
	60, 92, 125, 124,  1,
	126, 126, 124, 124,  1,
	126, 0, 124, 0,  1,
	91, 92, 62, 127,  1,
	95, 60, 0, 124,  1,
	47, 91, 0, 124,  1,
	92, 91, 124, 124,  1,
	92, 0, 127, 0,  1,
	124, 0, 124, 0,  1,
	125, 0, 0, 0,  1,
	95, 123, 0, 0,  1,
	127, 0, 124, 0,  1,
	94, 0, 0, 0,  1,
	91, 123, 124, 0,  1,
	93, 94, 0, 0,  1,
	125, 125, 0, 0,  1,
	0, 125, 0, 0,  1,
	93, 94, 0, 0,  1,
	93, 61, 0, 0,  1,
	125, 125, 0, 0,  1,
	0, 125, 0, 0,  1,
	0, 93, 0, 0,  1,
	94, 125, 0, 0,  1,
	125, 0, 0, 0,  1,
	124, 0, 124, 0,  1,
	0, 95, 0, 0,  1,
	0, 0, 126, 0,  1,
	94, 0, 0, 0,  1,
	0, 0, 92, 0,  1,
	93, 123, 0, 0,  1,
	123, 123, 0, 0,  1,
	94, 0, 0, 0,  1,
	0, 0, 126, 0,  1,};


// PROTOTYPES
void draw_bg(void);
void draw_sprites(void);
void draw_timer(void);
void draw_hud(void);
void draw_talking(void);
void draw_timer(void);
void movement(void);
void action(void);
void bg_collision();
void action_collision();
void change_room_right(void);
void change_room_left(void);
void change_room_up(void);
void change_room_down(void);
void initialize_title_screen(void);
void initialize_game_mode(void);
void initialize_end_screen(void);
void initialize_talking_time(void);
void back_to_game(void);
void countdown_timer(void);

