const unsigned char room_23[]={

6,1,1,1,1,1,1,0,0,1,1,1,1,1,1,5,
2,0,0,28,26,0,0,0,0,0,0,46,47,0,0,3,
2,0,0,0,0,20,0,0,0,0,0,48,49,44,0,3,
2,0,0,0,0,18,0,0,0,0,0,0,0,0,0,3,
2,0,0,0,23,19,0,0,0,0,0,0,0,0,0,0,
2,27,16,17,21,9,0,0,0,0,0,0,0,0,0,0,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,39,3,
7,4,4,4,4,4,4,0,0,4,4,4,4,4,4,8,

};

// it's important that the dungeon block is 0 in this list
// so we can move it.
const unsigned char room_23_sprites[]={
	184, 87, SPRITE_LunchLadyHead36,
	64, 112, SPRITE_BaldRight22,
	//32, 128, SPRITE_HairForward114,
	160, 96, SPRITE_FroGuy55,
	32, 176, SPRITE_GlassesRight35,
	TURN_OFF
};

const unsigned char room_23_talk[]={
	192, 97, TALK_FOODTRUCK,
	88, 120, TALK_FETCHQUEST,
	//32, 128, SPRITE_HairForward114,
	168, 104, TALK_KING2,
	40, 184, TALK_SPACE,
	TURN_OFF
};