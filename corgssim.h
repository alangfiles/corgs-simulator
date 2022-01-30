// #define MAX_RIGHT 0xb000
// #define MAX_LEFT 0xb000

#pragma bss-name(push, "ZEROPAGE")

// GLOBAL VARIABLES
unsigned char pad1;
unsigned char pad1_new;
unsigned char collision;
unsigned char collision_L;
unsigned char collision_R;
unsigned char collision_U;
unsigned char collision_D;
unsigned char which_bg;
const unsigned char *p_maps;
unsigned char coordinates;
unsigned char temp1;
unsigned char temp2;
unsigned char temp3;
unsigned char temp4;
unsigned char temp_x;
unsigned char temp_y;
unsigned char i;
const unsigned char title_text[] = "CORGS Simulator";
const unsigned char start_text[] = "Press Start";

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

struct BoxGuy
{
	unsigned char X;
	unsigned char Y;
	unsigned char width;
	unsigned char height;
};

struct BoxGuy BoxGuy1 = {64, 80, 15, 15};

// these are the 4 backgrounds
// collision data, made by exporting csv from Tiled, and slight modification by CSV2C.py
#include "CSV/c1.c" // called c1
#include "CSV/c2.c" // called c2
#include "CSV/c3.c" // called c3
#include "CSV/c4.c" // called c4

const unsigned char *const All_Collision_Maps[] = {c1, c2, c3, c4};

const unsigned char palette_bg[] = {
		0x0f, 0x00, 0x10, 0x30,	 // grays
		0x0f, 0x01, 0x21, 0x31,	 // blues
		0x0f, 0x06, 0x26, 0x36,	 // reds
		0x0f, 0x09, 0x29, 0x39}; // greens

const unsigned char palette_sp[] = {
		0x0f, 0x00, 0x0f, 0x28, // black, gray, yellow
		0x0f, 0x00, 0x0f, 0x15, // black, gray, pink
		0x0f, 0x00, 0x0f, 0x15, // black, gray, pink
		0, 0, 0, 0};

// PROTOTYPES
void draw_bg(void);
void draw_sprites(void);
void movement(void);
void bg_collision(char *object);
void door_collision(char *object);
void change_room_right(void);
void change_room_left(void);
void load_title(void);
void clear_title(void);
void debug_spr(void);
