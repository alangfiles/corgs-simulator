#define SCREEN_LEFT_EDGE 0x00
#define SCREEN_RIGHT_EDGE 0xf0
#define SCREEN_TOP_EDGE 0x40
#define SCREEN_BOTTOM_EDGE 0xd0

#define ACTION_HEIGHT 16
#define ACTION_WIDTH 16
#define ACTION_BUFFER 1

#define PLAYER_LEFT_EDGE 0x01
#define PLAYER_RIGHT_EDGE 0xef
#define PLAYER_TOP_EDGE 0x42
#define PLAYER_BOTTOM_EDGE 0xcf

#define PAD_ALL_DIRECTIONS	0x0f
#define PAD_ANY_BUT_SELECT	0xdf

#define DOWN_MOVE 0x00
#define LEFT_MOVE 0x01
#define UP_MOVE 0x02
#define RIGHT_MOVE 0x03

#define DOWN 0x00
#define LEFT 0x01
#define UP 0x02
#define RIGHT 0x03
#define B_BUTTON 0x04
#define A_BUTTON 0x04

#define TEXT_BOX_X 6
#define TEXT_BOX_Y 12
#define TEXT_BOX_LENGTH 18
#define TEXT_BOX_HEIGHT 8

#define PLAYER_HEIGHT 12
#define PLAYER_WIDTH 12


/* special locations for special things */
#define DUNGEON_BLOCK_X 0xA0
#define DUNGEON_BLOCK_Y 0xC0
#define DUNGEON_BLOCK_ROOM 22

#define DUNGEON_GAME_ROOM 5
#define DUNGEON_GAME_X 0x80
#define DUNGEON_GAME_Y 0x90

#define COIN_GAME_ROOM 10
#define COIN_GAME_X 0x70
#define COIN_GAME_Y 0xA0

const unsigned char code[]={
	PAD_UP, PAD_UP, PAD_DOWN, PAD_DOWN,
	 PAD_LEFT, PAD_RIGHT, PAD_LEFT, PAD_RIGHT, 
	 PAD_B, PAD_A};
unsigned char code_active = 0;

#define STARTING_ROOM 23

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
unsigned char eject_L; // from the left
unsigned char eject_R; // remember these from the collision sub routine
unsigned char eject_D; // from below
unsigned char eject_U; // from up

unsigned char collision_action;
unsigned char which_bg = 0;

// used for talking time
unsigned char text_rendered = 0;
unsigned char text_length = 0;
unsigned char text_row = 0;
unsigned char text_col = 0;
unsigned char text_decision = TURN_OFF;
unsigned char text_action = 0;


// dungeon block
unsigned char push_timer = 0;
unsigned char block_moved = 0;
unsigned char has_moved = 0;

unsigned char coordinates;
unsigned char temp1;
unsigned char temp2;
unsigned char temp3;
unsigned char temp4;
unsigned char temp5;
unsigned char temp6;

unsigned char player_direction = DOWN;
unsigned char last_player_direction = DOWN;
unsigned char player_x = 0x80;
unsigned char player_y = 0x80;
unsigned char player_jump = 0;
unsigned char player_coins = 0;
#define MAX_COINS 6 //how many coins the player has to collect
#define PLAYER_MAX_JUMP 88 //needs to be divisible by 4

// items collected like:
// 0000 0CBA
// A = dungeon game
// b = other game
// c = other game
#define ITEM_DUNGEON_GAME 0x01
#define ITEM_COIN_GAME 0x02
#define ITEM_THIRD_GAME 0x04
unsigned char items_collected = 0x00;
unsigned char item_found = 0;

unsigned char song;
#define MAX_SONGS 2
enum {SONG_GAME, SONG_PAUSE};
enum {SFX_JUMP, SFX_DING, SFX_NOISE};

struct Base {
	unsigned char x;
	unsigned char y;
	unsigned char width;
	unsigned char height;
};

struct Base Generic; 
struct Base Generic2; 


unsigned char shot_direction = DOWN;
unsigned char shot_x = -4;
unsigned char shot_y = -4;

//offset used for shuffling sprites
unsigned char offset;

//pointer used for a bunch of things
const unsigned char * pointer;

//for shuffling 16 enemies
const unsigned char shuffle_array[]={
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,
0,2,4,6,8,10,12,14,1,3,5,7,9,11,13,15,
15,13,11,9,7,5,3,1,14,12,10,8,6,4,2,0	
};

#define MAX_ROOM_TALKING 16
unsigned char talk_x[MAX_ROOM_TALKING];
unsigned char talk_y[MAX_ROOM_TALKING];
unsigned char talk_type[MAX_ROOM_TALKING];


#define MAX_ROOM_SPRITES 16
unsigned char sprites_x[MAX_ROOM_SPRITES];
unsigned char sprites_y[MAX_ROOM_SPRITES];
//unsigned char sprites_active[MAX_ROOM_SPRITES];
//unsigned char sprites_room[MAX_ROOM_SPRITES];
//unsigned char sprites_actual_x[MAX_ROOM_SPRITES];
unsigned char sprites_type[MAX_ROOM_SPRITES];
const unsigned char * sprites_anim[MAX_ROOM_SPRITES];

//timer stuff
unsigned int minutes_left = 4;
unsigned int seconds_left_tens = 0;
unsigned int seconds_left_ones = 1;

// room loader code
int address;
unsigned char x; 
unsigned char y;
unsigned char index = 0;
unsigned char index2;


//used for animation, could be replaced by getframes?
unsigned char move_frames = 0;


unsigned char bg_display_hud = 0;
unsigned char bg_fade_out = 1;
unsigned char display_hud_sprites = 1;

//used for clock tick frame
unsigned char frame = 0;

const unsigned char start_text[] = "Press  Start";
const unsigned char credits_1[] = "Created by";
const unsigned char credits_2[] = "Brian Burke and Alan Files";
const unsigned char credits_3[] = ";2022"; //';' in chr is (c)
const unsigned char topBar[] = {0xee,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xef};
const unsigned char bottomBar[] = {0xfe,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xed,0xff};
const unsigned char end_text2[] = "Press Start to play again";

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
	MODE_DECISION_TIME,
	MODE_END,
	MODE_GAME_OVER,
};

enum{
	CHOICE_PLAY_GAME
};

#pragma bss-name(push, "BSS")

unsigned char c_map[240];// collision map

unsigned char tile_map[240]; //map where tile data lives

// PROTOTYPES
void draw_bg(void);
void draw_sprites(void);
void draw_timer(void);
void draw_hud(void);
void draw_talking(void);
void countdown_timer(void);
void movement(void);
void action(void);
void action_collision();
void bg_collision();
void bg_collision_sub(void);
void sprite_collisions(void);
void change_room_right(void);
void change_room_left(void);
void change_room_up(void);
void change_room_down(void);
void initialize_title_screen(void);
void initialize_game_mode(void);
void initialize_end_screen(void);
void initialize_talking_time(void);
void initialize_sprites(void);
void initialize_talk_map(void);


