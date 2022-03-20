//these enums are used in the room_{X}_sprites values
enum{SPRITE_SHOPKEEPER, SPRITE_BRIAN, SPRITE_ALAN, SPRITE_GUY1};
#define TURN_OFF 0xff

#pragma region playersprites
const unsigned char PlayerSprDown[]={
	  0,  0,0x00,0,
	  8,  0,0x01,0,
	  0,  8,0x10,0,
	  8,  8,0x10,0|OAM_FLIP_H,
	128

};

const unsigned char PlayerSprDownTwo[]={
	  0,  0,0x00,0,
	  8,  0,0x01,0,
	  0,  8,0x10,0,
	  8,  8,0x11,0,
	128
};

const unsigned char PlayerSprDownThree[]={
	  0,  0,0x00,0,
	  8,  0,0x01,0,
	  0,  8,0x11,0|OAM_FLIP_H,
	  8,  8,0x10,0|OAM_FLIP_H,
	128
};

const unsigned char PlayerSprUp[]={
	  0,  0,0x04,0,
	  8,  0,0x05,0,
	  0,  8,0x10,0,
	  8,  8,0x10,0|OAM_FLIP_H,
	128
};

const unsigned char PlayerSprUpTwo[]={
	  0,  0,0x04,0,
	  8,  0,0x05,0,
	  0,  8,0x10,0,
	  8,  8,0x11,0,
	128

};

const unsigned char PlayerSprUpThree[]={
	  0, 0,0x04,0,
	  8, 0,0x05,0,
	  0, 8,0x11,0|OAM_FLIP_H,
	  8, 8,0x10,0|OAM_FLIP_H,
	128
};

const unsigned char PlayerSprRight[]={
	  0, 0,0x20,0,
	  8, 0,0x21,0,
	  0, 8,0x30,0,
	  8, 8,0x31,0,
	128
};

const unsigned char PlayerSprRightTwo[]={
	  0, 0,0x20,0,
	  8, 0,0x21,0,
	  0, 8,0x32,0,
	  8, 8,0x33,0,
	128
};

const unsigned char PlayerSprRightThree[]={
	  0, 0,0x20,0,
	  8, 0,0x21,0,
	  0, 8,0x34,0,
	  8, 8,0x35,0,
	128
};

const unsigned char PlayerSprRightFour[]={
	  0, 0,0x20,0,
	  8, 0,0x21,0,
	  0, 8,0x22,0,
	  8, 8,0x23,0,
	128
};

const unsigned char PlayerSprRightFive[]={
	  0, 0,0x20,0,
	  8, 0,0x21,0,
	  0, 8,0x24,0,
	  8, 8,0x25,0,
	128
};

const unsigned char PlayerSprLeft[]={
	  0, 0,0x21,0 | OAM_FLIP_H,
	  8, 0,0x20,0 | OAM_FLIP_H,
	  0, 8,0x31,0 | OAM_FLIP_H,
	  8, 8,0x30,0 | OAM_FLIP_H,
	128
};

const unsigned char PlayerSprLeftTwo[]={
	  0, 0,0x21,0 | OAM_FLIP_H,
	  8, 0,0x20,0 | OAM_FLIP_H,
	  0, 8,0x33,0 | OAM_FLIP_H,
	  8, 8,0x32,0 | OAM_FLIP_H,
	128
};

const unsigned char PlayerSprLeftThree[]={
	  0, 0,0x21,0 | OAM_FLIP_H,
	  8, 0,0x20,0 | OAM_FLIP_H,
	  0, 8,0x35,0 | OAM_FLIP_H,
	  8, 8,0x34,0 | OAM_FLIP_H,
	128
};

const unsigned char PlayerSprLeftFour[]={
	  0, 0,0x21,0 | OAM_FLIP_H,
	  8, 0,0x20,0 | OAM_FLIP_H,
	  0, 8,0x23,0 | OAM_FLIP_H,
	  8, 8,0x22,0 | OAM_FLIP_H,
	128
};

const unsigned char PlayerSprLeftFive[]={
	  0, 0,0x21,0 | OAM_FLIP_H,
	  8, 0,0x20,0 | OAM_FLIP_H,
	  0, 8,0x25,0 | OAM_FLIP_H,
	  8, 8,0x24,0 | OAM_FLIP_H,
	128
};


#pragma endregion playersprites


const unsigned char Shot[]={
	  0, 0,0x08,0,
	128
};

const unsigned char Shopkeeper[]={
	  0, 0,0x66,2,
		8, 0,0x67,2,
		0, 8,0x76,1,
	  8, 8,0x77,1,
	128
};

const unsigned char ShopkeeperTwo[]={
	  0, 0,0x62,1,
		8, 0,0x63,1,
		0, 8,0x72,1,
	  8, 8,0x73,1,
	128
};

const unsigned char Brian[]={
	  0, 0,0xCE,1,
		8, 0,0xCF,1,
		0, 8,0xDE,1,
	  8, 8,0xDF,1,
		0, 16,0xEE,1,
		8, 16,0xEF,1,
		0, 24,0xFE,1,
		8, 24,0xFF,1,
	128
};

const unsigned char Alan[]={
	  0, 0,0xCC,1,
		8, 0,0xCD,1,
		0, 8,0xDC,1,
	  8, 8,0xDD,1,
		0, 16,0xEC,1,
		8, 16,0xED,1,
		0, 24,0xFC,1,
		8, 24,0xFD,1,
	128
};

const unsigned char guy1[]={

	  0, 0,0x21,0 | OAM_FLIP_H,
	  8, 0,0x20,0 | OAM_FLIP_H,
	  0, 8,0x25,0 | OAM_FLIP_H,
	  8, 8,0x24,0 | OAM_FLIP_H,
	128

};

const unsigned char peopletest_1_data[]={

	  0,  0,0x64,0,
	  8,  8,0x75,0,
	  8,  0,0x64,0|OAM_FLIP_H,
	  0,  8,0x75,0|OAM_FLIP_H,
	128

};

const unsigned char peopletest_2_data[]={

	  0,  0,0x66,0,
	  8,  0,0x67,0,
	  8,  8,0x75,0,
	  0,  8,0x75,0|OAM_FLIP_H,
	128

};

const unsigned char peopletest_3_data[]={

	  8,  8,0x75,0,
	  0,  8,0x75,0|OAM_FLIP_H,
	  0,  0,0x63,0,
	  8,  0,0x73,0,
	128

};

const unsigned char peopletest_4_data[]={

	  0,  0,0x68,2,
	  8,  0,0x69,2,
	  0,  8,0x7a,2,
	  8,  8,0x79,2,
	128

};

const unsigned char peopletest_5_data[]={

	  0,  8,0x7a,2,
	  8,  8,0x79,2,
	  0,  0,0x6a,2,
	  8,  0,0x6b,2,
	128

};

const unsigned char peopletest_6_data[]={

	  8,  8,0x71,2,
	  0,  0,0x60,2,
	  0,  8,0x70,2,
	  8,  0,0x61,2,
	128

};

const unsigned char peopletest_7_data[]={

	  0,  0,0xa0,2,
	  0,  8,0xb0,2,
	128

};

const unsigned char peopletest_8_data[]={

	  0,  0,0xa1,2,
	  0,  8,0xb0,2,
	128

};

const unsigned char peopletest_9_data[]={

	  0,  0,0xa2,2,
	  0,  8,0xb2,2,
	128

};

const unsigned char peopletest_10_data[]={

	  0,  0,0xa3,2,
	  0,  8,0xb3,2,
	128

};

const unsigned char peopletest_11_data[]={

	  0,  0,0xa4,2,
	  8,  0,0xa5,2,
	  0,  8,0xb4,2,
	  8,  8,0xb5,2,
	128

};

const unsigned char peopletest_12_data[]={

	  0,  0,0xc0,2,
	  0,  8,0xd0,2,
	  8,  0,0xc0,2|OAM_FLIP_H,
	  8,  8,0xd0,2|OAM_FLIP_H,
	128

};

const unsigned char peopletest_13_data[]={

	  0,  0,0xc1,0,
	  8,  0,0xc2,0,
	  0,  8,0xd1,0,
	  8,  8,0xd1,0|OAM_FLIP_H,
	128

};

const unsigned char peopletest_14_data[]={

	  0,  0,0xc3,2,
	  0,  8,0xd3,2,
	  8,  0,0xc3,2|OAM_FLIP_H,
	  8,  8,0xd3,2|OAM_FLIP_H,
	128

};

const unsigned char peopletest_15_data[]={

	  0,  0,0xc4,3,
	  0,  8,0xd4,3,
	  8,  0,0xc4,3|OAM_FLIP_H,
	  8,  8,0xd4,3|OAM_FLIP_H,
	128

};

const unsigned char peopletest_16_data[]={

	  0,  0,0xe0,1,
	  0,  8,0xf0,1,
	  8,  0,0xe0,1|OAM_FLIP_H,
	  8,  8,0xf0,1|OAM_FLIP_H,
	128

};

const unsigned char peopletest_17_data[]={

	  0,  0,0xe1,2,
	  0,  8,0xf1,2,
	  8,  0,0xe1,2|OAM_FLIP_H,
	  8,  8,0xf1,2|OAM_FLIP_H,
	128

};

const unsigned char peopletest_18_data[]={

	  0,  0,0xe2,0,
	  0,  8,0xf2,0,
	  8,  0,0xe2,0|OAM_FLIP_H,
	  8,  8,0xf2,0|OAM_FLIP_H,
	128

};

const unsigned char peopletest_19_data[]={

	  0,  0,0xe3,0,
	  0,  8,0xf3,0,
	  8,  0,0xe3,0|OAM_FLIP_H,
	  8,  8,0xf3,0|OAM_FLIP_H,
	128

};

const unsigned char peopletest_20_data[]={

	  0,  0,0xe4,3,
	  0,  8,0xf4,3,
	  8,  0,0xe4,3|OAM_FLIP_H,
	  8,  8,0xf4,3|OAM_FLIP_H,
	128

};

const unsigned char peopletest_21_data[]={

	  0,  0,0xe6,2,
	  8,  0,0xe7,2,
	  0,  8,0xf6,2,
	  8,  8,0xf7,2,
	128

};

const unsigned char peopletest_22_data[]={

	  0,  0,0xc6,3,
	  0,  8,0xd6,3,
	  8,  0,0xc6,3|OAM_FLIP_H,
	  8,  8,0xd6,3|OAM_FLIP_H,
	128

};



// const unsigned char PunchingMan[]={
// 	  0, 0,0x78,1,
// 		8, 0,0x79,1,
// 		0, 8,0x98,1,
// 	  8, 8,0x99,1,
// 		0, 16,0xA8,1,
// 		8, 16,0xA9,1,
// 	128
// };


