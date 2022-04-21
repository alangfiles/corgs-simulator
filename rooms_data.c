#include "CSV/room_1.c"
#include "CSV/room_2.c"
#include "CSV/room_3.c"
#include "CSV/room_4.c"
#include "CSV/room_5.c"
#include "CSV/room_6.c"
#include "CSV/room_8.c"
#include "CSV/room_9.c"
#include "CSV/room_10.c"
#include "CSV/room_11.c"
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
#include "CSV/blank.c"




#pragma region palettes
const unsigned char cliff_palette[16]={
	0x1b,0x0f,0x30,0x2c,0x1b,0x17,0x11,0x0f,0x1b,0x07,0x17,0x2a,0x1b,0x06,0x37,0x3d
	};

const unsigned char title_palette[16]={ 
	0x0f,0x0f,0x30,0x2c,0x0f,0x01,0x21,0x31,0x0f,0x06,0x16,0x26,0x0f,0x09,0x19,0x29
	 };

const unsigned char trans_palette[16]={
	0x0f,0x0f,0x30,0x2c,
	0x0f,0x16,0x3d,0x37,
	0x0f,0x06,0x37,0x2a,
	0x0f,0x2a,0x1b,0x17
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
#pragma endregion palettes

#pragma region metatiles
// 5 bytes per metatile definition, tile TL, TR, BL, BR, palette 0-3
// T means top, B means bottom, L left,R right
// 51 maximum # of metatiles = 255 bytes
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
	16, 16, 16, 16,  1, //19 this is the block
	136, 136, 152, 152,  1,
	0, 0, 0, 0,  0,  //21 - blocking empty tile
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
	0xC0, 0, 0xD0, 0xD1,  3,
};

#pragma endregion metatiles

// const unsigned char * const outside[] = {2,3,4,7,8,9,11,12,14,21,26,27,29};
// const unsigned char * const inside[] = {17,18,19,22,23,24,25,28};
// const unsigned char * const trans[] = {5,10,13};
// const unsigned char * const cliff[] = {20};

// const unsigned char * const outside_col[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,40};
// const unsigned char * const inside_col[] = {0,37,50};
// const unsigned char * const trans_col[] = {0,1,2,4,5,18};
// const unsigned char * const cliff_col[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};



const unsigned char * const room_list[]={
	room_1,room_2,room_3,room_4,room_5,
  room_6,blank,room_8,room_9,room_10,
  room_11,room_12,room_13,room_14,room_15,
  blank,blank,room_18,room_19,room_20,
  room_46,room_47,room_23,room_24,room_25,
  room_28,room_33,room_38,room_43,room_48,
};

const unsigned char inside_hud = 0;
const unsigned char outside_hud = 13;
const unsigned char trans_hud = 0;
const unsigned char title_hud = 0;

const unsigned char * const talk_list[]={
	blank_talk,blank_talk,blank_talk,blank_talk,room_5_talk,
  blank_talk,blank_talk,blank_talk,room_9_talk,blank_talk,
  blank_talk,blank_talk,blank_talk,room_14_talk,blank_talk,
  blank_talk,blank_talk,room_18_talk,room_19_talk,room_20_talk,
  room_46_talk,room_47_talk,room_23_talk,room_24_talk,room_25_talk,
  room_28_talk,blank_talk,blank_talk,room_43_talk,room_48_talk,
};

const unsigned char * const sprite_list[]={
	blank_sprites,blank_sprites,blank_sprites,blank_sprites,room_5_sprites,
  blank_sprites,blank_sprites,blank_sprites,room_9_sprites,blank_sprites,
  room_11_sprites,blank_sprites,blank_sprites,room_14_sprites,blank_sprites,
  blank_sprites,blank_sprites,room_18_sprites,room_19_sprites,room_20_sprites,
  room_46_sprites,room_47_sprites,room_23_sprites,room_24_sprites,room_25_sprites,
  room_28_sprites,blank_sprites,blank_sprites,room_43_sprites,room_48_sprites,
}; 


const unsigned char * const room_palette_list[]={
  title_palette,title_palette,outside_palette,outside_palette,outside_palette,
  trans_palette,title_palette,outside_palette,outside_palette,outside_palette,
  trans_palette,outside_palette,outside_palette,trans_palette,outside_palette,
  title_palette,title_palette,inside_palette,inside_palette,inside_palette,
  cliff_palette,outside_palette,inside_palette,inside_palette,inside_palette,
  inside_palette,outside_palette,outside_palette,inside_palette,outside_palette,
};

const unsigned char * const room_metatile_list[]={
  title_metatiles,title_metatiles,outside_metatiles,outside_metatiles,outside_metatiles,
  trans_metatiles,title_metatiles,outside_metatiles,outside_metatiles,outside_metatiles,
  trans_metatiles,outside_metatiles,outside_metatiles,trans_metatiles,outside_metatiles,
  title_metatiles,title_metatiles,inside_metatiles,inside_metatiles,inside_metatiles,
  cliff_metatiles,outside_metatiles,inside_metatiles,inside_metatiles,inside_metatiles,
  inside_metatiles,outside_metatiles,outside_metatiles,inside_metatiles,outside_metatiles,
};