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
unsigned char last_direction = 0; // 0 = down, 1 = left, 2 = up, 3 = right
unsigned char move_frames = 0;
unsigned char has_moved = 0;
unsigned char frame = 0;
const unsigned char title_text[] = "CORGS Simulator";
const unsigned char start_text[] = "Press Start";
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
#include "CSV/c1.c" // called c1
#include "CSV/c2.c" // called c2
#include "CSV/c3.c" // called c3
#include "CSV/c4.c" // called c4
#include "CSV/c5.c" // called c5

const unsigned char *const All_Collision_Maps[] = {c1, c2, c3, c4};

const unsigned char palette_bg[] = {
		0x0f, 0x10, 0x17, 0x3d,	 
		0x0f, 0x06, 0x29, 0x14,	 
		0x0f, 0x14, 0x12, 0x36,	
		0x0f, 0x00, 0x23, 0x39}; 

const unsigned char palette_sp[] = {
		0x0f, 0x36, 0x10, 0x08, 
		0x0f, 0x00, 0x0f, 0x15, 
		0x0f, 0x00, 0x0f, 0x15, 
		0, 0, 0, 0};


// 5 bytes per metatile definition, tile TL, TR, BL, BR, palette 0-3
// T means top, B means bottom, L left,R right
// 51 maximum # of metatiles = 255 bytes

const unsigned char metatiles1[]={
	0x88, 0x88, 0x88, 0x88,  3,  // 0: Empty space
	0x10, 0x10, 0x10, 0x10,  0,  // 1: Brick
	0x1E, 0x1C, 0xA8, 0xAB,  2,  // 2: Table 2
	0x0F, 0x1F, 0xA8, 0xAB,  1,  // 3: Table 1
	0x98, 0x9B, 0xA8, 0xAB,  3,  // 4: empty table
	0x01, 0x02, 0x11, 0x12,  0,  // 5: door
	0xD5, 0xD6, 0xE5, 0xE6,  0,  // 6: TR corner
	0xD5, 0xD6, 0xE5, 0xE6,  0,  // 7: TL corner
	0xD1, 0xD2, 0xE1, 0xE2,  0   // 8: sidewaysDoor
};


// PROTOTYPES
void draw_bg(void);
void draw_sprites(void);
void draw_timer(void);
void movement(void);
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
void initialize_game(void);
