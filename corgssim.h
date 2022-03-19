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
unsigned char eject_L; // from the left
unsigned char eject_R; // remember these from the collision sub routine
unsigned char eject_D; // from below
unsigned char eject_U; // from up
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
unsigned char temp5;
unsigned char temp6;
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
void bg_collision_sub(void);
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


