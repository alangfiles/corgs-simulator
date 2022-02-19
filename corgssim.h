#define SCREEN_LEFT_EDGE 0x00
#define SCREEN_RIGHT_EDGE 0xf0
#define SCREEN_TOP_EDGE 0x20
#define SCREEN_BOTTOM_EDGE 0xe0

#define PLAYER_LEFT_EDGE 0x01
#define PLAYER_RIGHT_EDGE 0xef
#define PLAYER_TOP_EDGE 0x22
#define PLAYER_BOTTOM_EDGE 0xdf

#define DOWN_MOVE 0x00
#define LEFT_MOVE 0x01
#define UP_MOVE 0x02
#define RIGHT_MOVE 0x03

#pragma bss-name(push, "ZEROPAGE")

// GLOBAL VARIABLES
unsigned char pad1;
unsigned char pad1_new;
unsigned char collision;
unsigned char collision_L;
unsigned char collision_R;
unsigned char collision_U;
unsigned char collision_D;
unsigned char which_bg = 0;
const unsigned char *p_maps;
unsigned char coordinates;
unsigned char temp1;
unsigned char temp2;
unsigned char temp3;
unsigned char temp4;
unsigned char temp_x;
unsigned char temp_y;
unsigned char player_x = 64;
unsigned char player_y = 80;
unsigned char shot_direction = 0;  // 0 = down, 1 = left, 2 = up, 3 = right
unsigned char shot_x = 0;
unsigned char shot_y = 0;

unsigned int minutes_left = 4;
unsigned int seconds_left_tens = 0;
unsigned int seconds_left_ones = 0;

// room loader code
int address;
unsigned char x; 
unsigned char y;
unsigned char index;

unsigned char player_height = 13;
unsigned char player_width = 13;
unsigned char i;
unsigned char player_direction = 0; // 0 = down, 1 = left, 2 = up, 3 = right
unsigned char move_frames = 0;
unsigned char has_moved = 0;
unsigned char frame = 0;
const unsigned char title_text[] = "SIMUALTOR";
const unsigned char start_text[] = "Press  Start";
const unsigned char end_text[] = "You found a copy of JEQB";
const unsigned char end_text2[] = "Press Start to play again";
const unsigned char clock_text[] = "Time Left: ";
const unsigned char items_text[] = "Items Collected:    0 0 *";





unsigned char game_mode;
enum
{
	MODE_TITLE,
	MODE_GAME,
	MODE_PAUSE,
	MODE_SWITCH,
	MODE_END,
	MODE_GAME_OVER
};

#pragma bss-name(push, "BSS")

unsigned char c_map[240];
// collision map

// these are the 4 backgrounds
// collision data, made by exporting csv from Tiled, and slight modification by CSV2C.py
#include "CSV/blank.c"
#include "CSV/outsidetop.c"
#include "CSV/entry.c"
#include "CSV/title.c"

const unsigned char palette_bg[] = {
	0x0f,0x00,0x10,0x1a,
	0x0f,0x16,0x3d,0x37,
	0x0f,0x06,0x37,0x1a,
	0x0f,0x15,0x3d,0x2c
}; 

const unsigned char palette_sp[] = {
	0x0F, 0x36, 0x15, 0x1F, 
	0x0f, 0x36, 0x11, 0x27, 
	0x0f, 0x00, 0x0f, 0x15, 
	0x0f, 0x36, 0x1A, 0x07,
};


// 5 bytes per metatile definition, tile TL, TR, BL, BR, palette 0-3
// T means top, B means bottom, L left,R right
// 51 maximum # of metatiles = 255 bytes

const unsigned char metatiles1[]={
	0, 0, 0, 0,  2,
	1, 1, 17, 17,  2,
	2, 3, 2, 3,  2,
	18, 19, 18, 19,  2,
	4, 4, 20, 20,  2,
	1, 5, 21, 19,  2,
	6, 1, 19, 22,  2,
	2, 7, 23, 20,  2,
	8, 19, 20, 24,  2,
	9, 9, 9, 9,  2,
	10, 10, 26, 26,  2,
	11, 27, 27, 11,  2,
	12, 0, 12, 0,  1,
	0, 0, 28, 28,  2,
	136, 136, 152, 152,  1,
	128, 130, 144, 146,  0,
	135, 133, 144, 146,  0,
	150, 151, 144, 146,  0,
	128, 129, 144, 145,  0,
	129, 130, 145, 146,  0,
	147, 131, 144, 145,  0,
	149, 133, 145, 146,  0,
	132, 135, 144, 145,  0,
	134, 148, 145, 146,  0,
	128, 130, 129, 129,  0,
	132, 130, 131, 135,  0,
	147, 133, 129, 134,  0,
	192, 193, 208, 209,  3,
	210, 211, 144, 146,  3,
	168, 169, 184, 185,  1,
	170, 171, 186, 187,  1,
	172, 173, 188, 189,  3,
	174, 175, 190, 191,  0,
	158, 159, 144, 146,  0,
	137, 138, 153, 154,  3,
	139, 140, 155, 156,  1,
	162, 163, 176, 179,  0,
	161, 160, 177, 176,  3,
	176, 160, 161, 179,  1,
	206, 206, 222, 222,  1,
	141, 142, 157, 0,  1,
	164, 165, 180, 181,  3,
	166, 167, 182, 183,  3,
	202, 203, 218, 219,  1,
	204, 205, 220, 221,  1,
	13, 13, 29, 29,  3,
	14, 0, 30, 31,  3,
	200, 201, 216, 217,  1,
	194, 195, 0, 0,  0,
	196, 197, 212, 213,  0,
	198, 199, 214, 215,  0,
};


// PROTOTYPES
void draw_bg(void);
void draw_sprites(void);
void draw_timer(void);
void draw_hud(void);
void movement(void);
void action(void);
void item_detection(void);
void bg_collision();
void change_room_right(void);
void change_room_left(void);
void change_room_up(void);
void change_room_down(void);
void load_title(void);
void load_end(void);
void clear_title(void);
void clear_end(void);
void countdown_timer(void);
void initialize_game(void);
