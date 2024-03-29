// items collected like:
// 0000 0CBA
// A = dungeon game
// b = other game
// c = other game
#define ITEM_DUNGEON_GAME 0x01
#define ITEM_COIN_GAME 0x02
#define ITEM_ADVENTURE_GAME 0x04
#define ITEM_BURGER_GAME 0x08
#define ITEM_KETTLEBELL_GAME 0x10
#define ITEM_JOBBIES_GAME 0x20
#define ALL_ITEMS_COLLECTED 0x3F
unsigned char items_collected = 0;
unsigned char item_found = 0;

#pragma region DUNGEON_ROOM
#define DUNGEON_BLOCK_X 0x30
#define DUNGEON_BLOCK_Y 0x50
#define DUNGEON_BLOCK_ROOM 24

#define DUNGEON_GAME_ROOM 5
#define DUNGEON_GAME_X 0x80
#define DUNGEON_GAME_Y 0x90

// dungeon block
unsigned char push_timer = 0;
unsigned char block_moved = 0;
unsigned char has_moved = 0;

#define CLIFF_ROOM 20

#pragma endregion DUNGEON_ROOM

#define TOLIET_WARP_1_ROOM 4
#define TOLIET_WARP_1_Y 0x90
#define TOLIET_WARP_1_X 0xC0

#define TOLIET_WARP_2_ROOM 28
#define TOLIET_WARP_2_Y 0x60
#define TOLIET_WARP_2_X 0xE0

#define TOLIET_WARP_3_ROOM 28
#define TOLIET_WARP_3_Y 0xC0
#define TOLIET_WARP_3_X 0xE0

#define COIN_ROOM_WARP_Y 0xC0
#define COIN_ROOM_WARP_X 0xE0

#pragma region COIN_ROOM
#define COIN_GAME_ROOM 10
#define COIN_GAME_X 0x70
#define COIN_GAME_Y 0xA0

unsigned char player_jump = 0;
unsigned char player_coins = 0;
#define MAX_COINS 6        // how many coins the player has to collect
#define PLAYER_MAX_JUMP 88 // needs to be divisible by 4

#pragma endregion COIN_ROOM


//JOBBIES
#define MAX_JOBBIES 42 //should be 25
unsigned char player_jobbies_tens = 0;
unsigned char player_jobbies_ones = 0;
unsigned char player_jobbies = 0;
unsigned char jobbies_map[]={
	0, 0, 0, 0, 1,
	0, 0, 2, 1, 2,
	0, 4, 2, 1, 8,
	0, 0, 1, 1, 1,
	0, 2, 4, 0, 1,
	0, 5, 4, 2, 0,
};

unsigned char jobbies_map_init[]={
	0, 0, 0, 0, 1,
	0, 0, 2, 1, 2,
	0, 4, 2, 1, 8,
	0, 0, 1, 1, 1,
	0, 2, 4, 0, 1,
	0, 5, 4, 2, 0,
};

#pragma region ADVENTURE_ROOM
#define ADVENTURE_GAME_ROOM 19
#define ADVENTURE_GAME_X 0x90
#define ADVENTURE_GAME_Y 0x60

#pragma endregion ADVENTURE_ROOM

#pragma region FETCH_QUEST
#define FETCH_QUEST_ROOM 23
#define FETCH_QUEST_X 0xD0
#define FETCH_QUEST_Y 0x60
unsigned char on_fetchquest = 0; // 0 - not started, 1 - money, 2 - food, 3 - burgertime, 4 - complete

#pragma endregion FETCH_QUEST

#pragma region REPS
#define REPS_ROOM 21
#define MAX_REPS 30    // how many reps to get the prize
#define REP_TIMER_MAX 5 // how much time to do the reps
unsigned char rep_count = 0;
unsigned char rep_timer = 0;
#pragma endregion REPS


#define JOBBIES_ROOM 14