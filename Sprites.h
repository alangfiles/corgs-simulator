//these enums are used in the room_{X}_sprites values
enum{SPRITE_SHOPKEEPER, SPRITE_BRIAN, SPRITE_ALAN, SPRITE_GUY1, SPRITE_SKIRT, SPRITE_MUSCLE1, SPRITE_MUSCLE2};
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

const unsigned char MuscleMan0[]={

	  0,  0,0x62,1,
	  0,  8,0x72,1,
	  8,  0,0x62,1|OAM_FLIP_H,
	  8,  8,0x72,1|OAM_FLIP_H,
	128

};

const unsigned char Muscleman1[]={

	  0,  0,0x62,2,
	  0,  8,0x72,2,
	  8,  0,0x62,2|OAM_FLIP_H,
	  8,  8,0x72,2|OAM_FLIP_H,
	128

};

const unsigned char MuscleMan2[]={

	  0,  0,0x62,0,
	  0,  8,0x72,0,
	  8,  0,0x62,0|OAM_FLIP_H,
	  8,  8,0x72,0|OAM_FLIP_H,
	128

};

const unsigned char Girl3[]={

	  0,  0,0x60,0,
	  8,  0,0x61,0,
	  0,  8,0x70,0,
	  8,  8,0x71,0,
	128

};

const unsigned char Girl4[]={

	  0,  0,0x60,1,
	  8,  0,0x61,1,
	  0,  8,0x70,1,
	  8,  8,0x71,1,
	128

};

const unsigned char Girl5[]={

	  0,  0,0x60,2,
	  8,  0,0x61,2,
	  0,  8,0x70,2,
	  8,  8,0x71,2,
	128

};

const unsigned char BaldBehind6[]={

	  0,  0,0x63,2,
	  8,  0,0x63,2|OAM_FLIP_H,
	  8,  8,0xa7,2,
	  0,  8,0xa7,2|OAM_FLIP_H,
	128

};

const unsigned char BaldBehind7[]={

	  0,  0,0x63,0,
	  8,  0,0x63,0|OAM_FLIP_H,
	  8,  8,0xa7,0,
	  0,  8,0xa7,0|OAM_FLIP_H,
	128

};

const unsigned char BaldBehind8[]={

	  0,  0,0x63,1,
	  8,  0,0x63,1|OAM_FLIP_H,
	  8,  8,0xa7,1,
	  0,  8,0xa7,1|OAM_FLIP_H,
	128

};

const unsigned char HairBehind9[]={

	  0,  0,0x73,0|OAM_FLIP_H,
	  8,  0,0x73,0,
	  8,  8,0xa7,0,
	  0,  8,0xa7,0|OAM_FLIP_H,
	128

};

const unsigned char HariBehind10[]={

	  0,  0,0x73,1|OAM_FLIP_H,
	  8,  0,0x73,1,
	  8,  8,0xa7,1,
	  0,  8,0xa7,1|OAM_FLIP_H,
	128

};

const unsigned char HairBehind11[]={

	  0,  0,0x73,2|OAM_FLIP_H,
	  8,  0,0x73,2,
	  8,  8,0xa7,2,
	  0,  8,0xa7,2|OAM_FLIP_H,
	128

};

const unsigned char BaldForward12[]={

	  0,  0,0x64,0,
	  8,  0,0x64,0|OAM_FLIP_H,
	  0,  8,0x75,0|OAM_FLIP_H,
	  8,  8,0x75,0,
	128

};

const unsigned char BaldForward13[]={

	  0,  0,0x64,1,
	  8,  0,0x64,1|OAM_FLIP_H,
	  0,  8,0x75,1|OAM_FLIP_H,
	  8,  8,0x75,1,
	128

};

const unsigned char BaldForward14[]={

	  0,  0,0x64,2,
	  8,  0,0x64,2|OAM_FLIP_H,
	  0,  8,0x75,2|OAM_FLIP_H,
	  8,  8,0x75,2,
	128

};

const unsigned char HatForward15[]={

	  0,  0,0x65,2|OAM_FLIP_H,
	  8,  0,0x65,2,
	  0,  8,0x75,2|OAM_FLIP_H,
	  8,  8,0x75,2,
	128

};

const unsigned char HatForward16[]={

	  0,  0,0x65,0|OAM_FLIP_H,
	  8,  0,0x65,0,
	  0,  8,0x75,0|OAM_FLIP_H,
	  8,  8,0x75,0,
	128

};

const unsigned char HatForward17[]={

	  0,  0,0x65,1|OAM_FLIP_H,
	  8,  0,0x65,1,
	  0,  8,0x75,1|OAM_FLIP_H,
	  8,  8,0x75,1,
	128

};

const unsigned char BaldLeft18[]={

	  0,  0,0x84,1,
	  8,  0,0x85,1,
	  8,  8,0x95,1,
	  0,  8,0x96,1,
	128

};

const unsigned char BaldLeft19[]={

	  0,  0,0x84,0,
	  8,  0,0x85,0,
	  8,  8,0x95,0,
	  0,  8,0x96,0,
	128

};

const unsigned char BaldLeft20[]={

	  0,  0,0x84,2,
	  8,  0,0x85,2,
	  8,  8,0x95,2,
	  0,  8,0x96,2,
	128

};

const unsigned char BaldRight21[]={

	  8,  0,0x84,1|OAM_FLIP_H,
	  0,  0,0x85,1|OAM_FLIP_H,
	  0,  8,0x95,1|OAM_FLIP_H,
	  8,  8,0x96,1|OAM_FLIP_H,
	128

};

const unsigned char BaldRight22[]={

	  8,  0,0x84,0|OAM_FLIP_H,
	  0,  0,0x85,0|OAM_FLIP_H,
	  0,  8,0x95,0|OAM_FLIP_H,
	  8,  8,0x96,0|OAM_FLIP_H,
	128

};

const unsigned char BaldRight23[]={

	  8,  0,0x84,2|OAM_FLIP_H,
	  0,  0,0x85,2|OAM_FLIP_H,
	  0,  8,0x95,2|OAM_FLIP_H,
	  8,  8,0x96,2|OAM_FLIP_H,
	128

};

const unsigned char HairLeft24[]={

	  0,  0,0x86,1,
	  8,  0,0x87,1,
	  8,  8,0x95,1,
	  0,  8,0x96,1,
	128

};

const unsigned char HairLeft25[]={

	  0,  0,0x86,0,
	  8,  0,0x87,0,
	  8,  8,0x95,0,
	  0,  8,0x96,0,
	128

};

const unsigned char HairLeft26[]={

	  0,  0,0x86,2,
	  8,  0,0x87,2,
	  8,  8,0x95,2,
	  0,  8,0x96,2,
	128

};

const unsigned char HairRight27[]={

	  8,  0,0x86,1|OAM_FLIP_H,
	  0,  0,0x87,1|OAM_FLIP_H,
	  0,  8,0x95,1|OAM_FLIP_H,
	  8,  8,0x96,1|OAM_FLIP_H,
	128

};

const unsigned char HairRight28[]={

	  8,  0,0x86,0|OAM_FLIP_H,
	  0,  0,0x87,0|OAM_FLIP_H,
	  0,  8,0x95,0|OAM_FLIP_H,
	  8,  8,0x96,0|OAM_FLIP_H,
	128

};

const unsigned char HairRight29[]={

	  8,  0,0x86,2|OAM_FLIP_H,
	  0,  0,0x87,2|OAM_FLIP_H,
	  0,  8,0x95,2|OAM_FLIP_H,
	  8,  8,0x96,2|OAM_FLIP_H,
	128

};

const unsigned char GlassesLeft30[]={

	  0,  0,0x76,0,
	  8,  0,0x77,0,
	  8,  8,0x95,0,
	  0,  8,0x96,0,
	128

};

const unsigned char GlassesLeft31[]={

	  0,  0,0x76,1,
	  8,  0,0x77,1,
	  8,  8,0x95,1,
	  0,  8,0x96,1,
	128

};

const unsigned char GlassesLeft32[]={

	  0,  0,0x76,2,
	  8,  0,0x77,2,
	  8,  8,0x95,2,
	  0,  8,0x96,2,
	128

};

const unsigned char GlassesRight33[]={

	  8,  0,0x76,0|OAM_FLIP_H,
	  0,  0,0x77,0|OAM_FLIP_H,
	  0,  8,0x95,0|OAM_FLIP_H,
	  8,  8,0x96,0|OAM_FLIP_H,
	128

};

const unsigned char GlassesRight34[]={

	  8,  0,0x76,1|OAM_FLIP_H,
	  0,  0,0x77,1|OAM_FLIP_H,
	  0,  8,0x95,1|OAM_FLIP_H,
	  8,  8,0x96,1|OAM_FLIP_H,
	128

};

const unsigned char GlassesRight35[]={
	  
	  8,  0,0x76,2|OAM_FLIP_H,
	  0,  0,0x77,2|OAM_FLIP_H,
	  0,  8,0x95,2|OAM_FLIP_H,
	  8,  8,0x96,2|OAM_FLIP_H,
	128
};



const unsigned char LunchLadyHead36[]={

	  0,  0,0x80,2,
	  8,  0,0x81,2,
	128

};

const unsigned char LunchLady37[]={

	  0,  0,0x80,2,
	  8,  0,0x81,2,
	  0,  8,0x90,3,
	  8,  8,0x91,3,
	128

};

const unsigned char LunchLady38[]={

	  0,  0,0x80,2,
	  8,  0,0x81,2,
	  0,  8,0x90,2,
	  8,  8,0x91,2,
	128

};

const unsigned char SkirtLady39[]={

	  0,  8,0x92,2,
	  0,  0,0x82,2,
	  8,  0,0x83,2,
	  8,  8,0x92,2|OAM_FLIP_H,
	128

};

const unsigned char SkirtLady40[]={

	  0,  8,0x92,0,
	  0,  0,0x82,0,
	  8,  0,0x83,0,
	  8,  8,0x92,0|OAM_FLIP_H,
	128

};

const unsigned char SkirtLady41[]={

	  0,  8,0x92,3,
	  0,  0,0x82,3,
	  8,  0,0x83,3,
	  8,  8,0x92,3|OAM_FLIP_H,
	128

};

const unsigned char BoyKid42[]={

	  0,  0,0xa0,0,
	  0,  8,0xb0,0,
	128

};

const unsigned char BoyKid43[]={

	  0,  0,0xa0,1,
	  0,  8,0xb0,1,
	128

};

const unsigned char BoyKid44[]={

	  0,  0,0xa0,2,
	  0,  8,0xb0,2,
	128

};

const unsigned char GirlKid45[]={

	  0,  0,0xa1,2,
	  0,  8,0xb0,2,
	128

};

const unsigned char GirlKid46[]={

	  0,  0,0xa1,0,
	  0,  8,0xb0,0,
	128

};

const unsigned char GirlKid47[]={

	  0,  0,0xa1,1,
	  0,  8,0xb0,1,
	128

};

const unsigned char SkinnyHatMan48[]={

	  0,  0,0xa2,3,
	  0,  8,0xb2,3,
	128

};

const unsigned char SkinHatMan49[]={

	  0,  0,0xa2,2,
	  0,  8,0xb2,2,
	128

};

const unsigned char SleepyGuy50[]={

	  0,  0,0xa3,2,
	  0,  8,0xb3,2,
	128

};

const unsigned char SleepyGuy51[]={

	  0,  0,0xa3,3,
	  0,  8,0xb3,3,
	128

};

const unsigned char Wizard52[]={

	  0,  0,0xa4,3,
	  8,  0,0xa5,3,
	  0,  8,0xb4,3,
	  8,  8,0xb5,3,
	128

};

const unsigned char Wizard53[]={

	  0,  0,0xa4,2,
	  8,  0,0xa5,2,
	  0,  8,0xb4,2,
	  8,  8,0xb5,2,
	128

};

const unsigned char Wizard54[]={

	  0,  0,0xa4,0,
	  8,  0,0xa5,0,
	  0,  8,0xb4,0,
	  8,  8,0xb5,0,
	128

};

const unsigned char FroGuy55[]={

	  0,  0,0xc0,0,
	  0,  8,0xd0,2,
	  8,  0,0xc0,0|OAM_FLIP_H,
	  8,  8,0xd0,2|OAM_FLIP_H,
	128

};

const unsigned char FroGuy56[]={

	  0,  0,0xc0,1,
	  0,  8,0xd0,3,
	  8,  0,0xc0,1|OAM_FLIP_H,
	  8,  8,0xd0,3|OAM_FLIP_H,
	128

};

const unsigned char CostumeMan57[]={

	  0,  0,0xc1,3,
	  0,  8,0xd1,3,
	  8,  0,0xc1,3|OAM_FLIP_H,
	  8,  8,0xd1,3|OAM_FLIP_H,
	128

};

const unsigned char CostumeMan58[]={

	  0,  0,0xc1,2,
	  0,  8,0xd1,2,
	  8,  0,0xc1,2|OAM_FLIP_H,
	  8,  8,0xd1,2|OAM_FLIP_H,
	128

};

const unsigned char DressGirl59[]={

	  0,  0,0xc2,2,
	  8,  0,0xc3,2,
	  0,  8,0xd2,2,
	  8,  8,0xd2,2|OAM_FLIP_H,
	128

};

const unsigned char DressGirl60[]={

	  0,  0,0xc2,0,
	  8,  0,0xc3,0,
	  0,  8,0xd2,0,
	  8,  8,0xd2,0|OAM_FLIP_H,
	128

};

const unsigned char DressGirl61[]={

	  0,  0,0xc2,1,
	  8,  0,0xc3,1,
	  0,  8,0xd2,1,
	  8,  8,0xd2,1|OAM_FLIP_H,
	128

};

const unsigned char OldCoot62[]={

	  0,  0,0xe0,0,
	  0,  8,0xf0,0,
	  8,  0,0xe0,0|OAM_FLIP_H,
	  8,  8,0xf0,0|OAM_FLIP_H,
	128

};

const unsigned char OldCoot63[]={

	  0,  0,0xe0,1,
	  0,  8,0xf0,1,
	  8,  0,0xe0,1|OAM_FLIP_H,
	  8,  8,0xf0,1|OAM_FLIP_H,
	128

};

const unsigned char OldCoot64[]={

	  0,  0,0xe0,2,
	  0,  8,0xf0,2,
	  8,  0,0xe0,2|OAM_FLIP_H,
	  8,  8,0xf0,2|OAM_FLIP_H,
	128

};

const unsigned char Ghost65[]={

	  0,  0,0xe1,2,
	  0,  8,0xf1,2,
	  8,  0,0xe1,2|OAM_FLIP_H,
	  8,  8,0xf1,2|OAM_FLIP_H,
	128

};

const unsigned char Ghost66[]={

	  0,  0,0xe1,0,
	  0,  8,0xf1,0,
	  8,  0,0xe1,0|OAM_FLIP_H,
	  8,  8,0xf1,0|OAM_FLIP_H,
	128

};

const unsigned char Ghost67[]={

	  0,  0,0xe1,1,
	  0,  8,0xf1,1,
	  8,  0,0xe1,1|OAM_FLIP_H,
	  8,  8,0xf1,1|OAM_FLIP_H,
	128

};

const unsigned char Ghost68[]={

	  0,  0,0xe1,3,
	  0,  8,0xf1,3,
	  8,  0,0xe1,3|OAM_FLIP_H,
	  8,  8,0xf1,3|OAM_FLIP_H,
	128

};

const unsigned char WideBoy69[]={

	  0,  0,0xe2,0,
	  0,  8,0xf2,0,
	  8,  0,0xe2,0|OAM_FLIP_H,
	  8,  8,0xf2,0|OAM_FLIP_H,
	128

};

const unsigned char WideBoy70[]={

	  0,  0,0xe2,1,
	  0,  8,0xf2,1,
	  8,  0,0xe2,1|OAM_FLIP_H,
	  8,  8,0xf2,1|OAM_FLIP_H,
	128

};

const unsigned char WideBoy71[]={

	  0,  0,0xe2,2,
	  0,  8,0xf2,2,
	  8,  0,0xe2,2|OAM_FLIP_H,
	  8,  8,0xf2,2|OAM_FLIP_H,
	128

};

const unsigned char BaldTank72[]={

	  0,  0,0xe3,0,
	  0,  8,0xf3,0,
	  8,  0,0xe3,0|OAM_FLIP_H,
	  8,  8,0xf3,0|OAM_FLIP_H,
	128

};

const unsigned char BaldTank73[]={

	  0,  0,0xe3,1,
	  0,  8,0xf3,1,
	  8,  0,0xe3,1|OAM_FLIP_H,
	  8,  8,0xf3,1|OAM_FLIP_H,
	128

};

const unsigned char BlueBeard74[]={

	  0,  0,0xe4,2,
	  0,  8,0xf4,2,
	  8,  0,0xe4,2|OAM_FLIP_H,
	  8,  8,0xf4,2|OAM_FLIP_H,
	128

};

const unsigned char King75[]={

	  0,  0,0xe5,1,
	  0,  8,0xf5,1,
	  8,  0,0xe5,1|OAM_FLIP_H,
	  8,  8,0xf5,1|OAM_FLIP_H,
	128

};

const unsigned char BeardSideManRight76[]={

	  0,  8,0xf6,2,
	  8,  8,0xf7,2,
	  0,  0,0xc6,2,
	  8,  0,0xc7,2,
	128

};

const unsigned char BeardSideManRight77[]={

	  0,  8,0xf6,0,
	  8,  8,0xf7,0,
	  0,  0,0xc6,0,
	  8,  0,0xc7,0,
	128

};

const unsigned char BeardSideManRight78[]={

	  0,  8,0xf6,3,
	  8,  8,0xf7,3,
	  0,  0,0xc6,3,
	  8,  0,0xc7,3,
	128

};

const unsigned char BeardSideManLeft79[]={

	  8,  8,0xf6,2|OAM_FLIP_H,
	  0,  8,0xf7,2|OAM_FLIP_H,
	  8,  0,0xc6,2|OAM_FLIP_H,
	  0,  0,0xc7,2|OAM_FLIP_H,
	128

};

const unsigned char BeardSideManLeft80[]={

	  8,  8,0xf6,0|OAM_FLIP_H,
	  0,  8,0xf7,0|OAM_FLIP_H,
	  8,  0,0xc6,0|OAM_FLIP_H,
	  0,  0,0xc7,0|OAM_FLIP_H,
	128

};

const unsigned char BeardSideManLeft81[]={

	  8,  8,0xf6,3|OAM_FLIP_H,
	  0,  8,0xf7,3|OAM_FLIP_H,
	  8,  0,0xc6,3|OAM_FLIP_H,
	  0,  0,0xc7,3|OAM_FLIP_H,
	128

};

const unsigned char BigNoseRight82[]={

	  0,  8,0xf6,2,
	  8,  8,0xf7,2,
	  0,  0,0xd6,2,
	  8,  0,0xd7,2,
	128

};

const unsigned char BigNoseRight83[]={

	  0,  8,0xf6,3,
	  8,  8,0xf7,3,
	  0,  0,0xd6,3,
	  8,  0,0xd7,3,
	128

};

const unsigned char BigNoseLeft84[]={

	  8,  8,0xf6,2|OAM_FLIP_H,
	  0,  8,0xf7,2|OAM_FLIP_H,
	  8,  0,0xd6,2|OAM_FLIP_H,
	  0,  0,0xd7,2|OAM_FLIP_H,
	128

};

const unsigned char BigNoseLeft85[]={

	  8,  8,0xf6,3|OAM_FLIP_H,
	  0,  8,0xf7,3|OAM_FLIP_H,
	  8,  0,0xd6,3|OAM_FLIP_H,
	  0,  0,0xd7,3|OAM_FLIP_H,
	128

};

const unsigned char SideLadyRight86[]={

	  0,  8,0xf6,2,
	  8,  8,0xf7,2,
	  0,  0,0xe6,2,
	  8,  0,0xe7,2,
	128

};

const unsigned char SideLadyRight87[]={

	  0,  8,0xf6,0,
	  8,  8,0xf7,0,
	  0,  0,0xe6,0,
	  8,  0,0xe7,0,
	128

};

const unsigned char SideLadyRight88[]={

	  0,  8,0xf6,1,
	  8,  8,0xf7,1,
	  0,  0,0xe6,1,
	  8,  0,0xe7,1,
	128

};

const unsigned char SideLadyLeft89[]={
	
	  8,  8,0xf6,2|OAM_FLIP_H,
	  0,  8,0xf7,2|OAM_FLIP_H,
	  8,  0,0xe6,2|OAM_FLIP_H,
	  0,  0,0xe7,2|OAM_FLIP_H,
	128
};



const unsigned char SideLadyLeft90[]={
	
	  8,  8,0xf6,0|OAM_FLIP_H,
	  0,  8,0xf7,0|OAM_FLIP_H,
	  8,  0,0xe6,0|OAM_FLIP_H,
	  0,  0,0xe7,0|OAM_FLIP_H,
	128
};


const unsigned char SideLadyLeft91[]={

	  8,  8,0xf6,1|OAM_FLIP_H,
	  0,  8,0xf7,1|OAM_FLIP_H,
	  8,  0,0xe6,1|OAM_FLIP_H,
	  0,  0,0xe7,1|OAM_FLIP_H,
	128

};

const unsigned char Alan92[]={

	  0,  0,0xcc,0,
	  8,  0,0xcd,0,
	  0,  8,0xdc,0,
	  8,  8,0xdd,0,
	  0, 16,0xec,1,
	  8, 16,0xed,1,
	  0, 24,0xfc,1,
	  8, 24,0xfd,1,
	128

};

const unsigned char Brian93[]={

	  0,  0,0xce,1,
	  8,  0,0xcf,1,
	  0,  8,0xde,1,
	  8,  8,0xdf,1,
	  0, 16,0xee,1,
	  8, 16,0xef,1,
	  0, 24,0xfe,1,
	  8, 24,0xfe,1|OAM_FLIP_H,
	128

};

const unsigned char PrizeGuy94[]={

	  0,  0,0x02,0,
	  8,  0,0x03,0,
	  0,  8,0x12,0,
	  8,  8,0x13,0,
	128

};

const unsigned char Car95[]={

	  8,  0,0x4f,3,
	  8,  8,0x5f,3,
	  0, 16,0x6f,3|OAM_FLIP_H,
	  8, 24,0x7f,3,
	  0,  0,0x4f,3|OAM_FLIP_H,
	  0,  8,0x5f,3|OAM_FLIP_H,
	  8, 16,0x6f,3,
	  0, 24,0x7f,3|OAM_FLIP_H,
	128

};

const unsigned char Car96[]={

	  8,  0,0x4f,2,
	  8,  8,0x5f,2,
	  0, 16,0x6f,2|OAM_FLIP_H,
	  8, 24,0x7f,2,
	  0,  0,0x4f,2|OAM_FLIP_H,
	  0,  8,0x5f,2|OAM_FLIP_H,
	  8, 16,0x6f,2,
	  0, 24,0x7f,2|OAM_FLIP_H,
	128

};

const unsigned char GamePrize97[]={

	  0,  0,0xac,3,
	  8,  0,0xad,3,
	  0,  8,0xbc,3,
	  8,  8,0xbd,3,
	128

};

const unsigned char Banner98[]={

	  0, 16,0x7c,0,
	  0,  8,0x6c,0,
	  0,  0,0x5c,0,
	  8,  8,0x6d,0,
	 24,  8,0x5d,0,
	 16,  8,0x7d,0,
	 32,  8,0x6c,0|OAM_FLIP_H,
	 32,  0,0x5c,0|OAM_FLIP_H,
	 32, 16,0x7c,0|OAM_FLIP_H,
	  0, 24,0x7c,0,
	 32, 24,0x7c,0|OAM_FLIP_H,
	128

};

const unsigned char Banner99[]={

	  0, 16,0x7c,1,
	  0,  8,0x6c,1,
	  0,  0,0x5c,1,
	  8,  8,0x6d,1,
	 24,  8,0x5d,1,
	 16,  8,0x7d,1,
	 32,  8,0x6c,1|OAM_FLIP_H,
	 32,  0,0x5c,1|OAM_FLIP_H,
	 32, 16,0x7c,1|OAM_FLIP_H,
	  0, 24,0x7c,1,
	 32, 24,0x7c,1|OAM_FLIP_H,
	128

};

const unsigned char Banner100[]={

	  0, 16,0x7c,2,
	  0,  8,0x6c,2,
	  0,  0,0x5c,2,
	  8,  8,0x6d,2,
	 24,  8,0x5d,2,
	 16,  8,0x7d,2,
	 32,  8,0x6c,2|OAM_FLIP_H,
	 32,  0,0x5c,2|OAM_FLIP_H,
	 32, 16,0x7c,2|OAM_FLIP_H,
	  0, 24,0x7c,2,
	 32, 24,0x7c,2|OAM_FLIP_H,
	128

};

const unsigned char BackTV[]={

	  0,  0,0x0f,3,
	  0,  8,0x1f,3,
	  8,  0,0x0f,3|OAM_FLIP_H,
	  8,  8,0x1f,3|OAM_FLIP_H,
	128

};

const unsigned char PrettyGirlRightStand102[]={

	  0,  0,0x40,2,
	  8,  0,0x41,2,
	  0,  8,0x50,2,
	  8,  8,0x51,2,
	128

};

const unsigned char PrettyGirlRightWalk103[]={

	  0,  0,0x40,2,
	  8,  0,0x41,2,
	  0,  8,0x56,2,
	  8,  8,0x57,2,
	128

};

const unsigned char PrettyGirlLeftStand104[]={

	  8,  0,0x40,2|OAM_FLIP_H,
	  0,  0,0x41,2|OAM_FLIP_H,
	  8,  8,0x50,2|OAM_FLIP_H,
	  0,  8,0x51,2|OAM_FLIP_H,
	128

};

const unsigned char PrettyGirlLeftStand105[]={

	  8,  0,0x40,2|OAM_FLIP_H,
	  0,  0,0x41,2|OAM_FLIP_H,
	  8,  8,0x56,2|OAM_FLIP_H,
	  0,  8,0x57,2|OAM_FLIP_H,
	128

};

const unsigned char PrettyGirlStandForward106[]={

	  0,  0,0x42,2,
	  8,  0,0x43,2,
	  0,  8,0x52,2,
	  8,  8,0x52,2|OAM_FLIP_H,
	128

};

const unsigned char PrettyGirlForwardRightUp107[]={

	  0,  0,0x42,2,
	  8,  0,0x43,2,
	  0,  8,0x52,2,
	  8,  8,0x53,2,
	128

};

const unsigned char PrettyGirlForwardLeftUp108[]={

	  0,  0,0x42,2,
	  8,  0,0x43,2,
	  0,  8,0x53,2|OAM_FLIP_H,
	  8,  8,0x52,2|OAM_FLIP_H,
	128

};

const unsigned char PrettyGirlBehindStand109[]={

	  0,  0,0x44,2,
	  8,  0,0x45,2,
	  0,  8,0x54,2,
	  8,  8,0x54,2|OAM_FLIP_H,
	128

};

const unsigned char PrettyGirlBehindRightUp110[]={

	  0,  0,0x44,2,
	  8,  0,0x45,2,
	  0,  8,0x54,2,
	  8,  8,0x55,2,
	128

};

const unsigned char PrettyGirlBehindLeftUp111[]={

	  0,  0,0x44,2,
	  8,  0,0x45,2,
	  0,  8,0x55,2|OAM_FLIP_H,
	  8,  8,0x54,2|OAM_FLIP_H,
	128

};

const unsigned char PunchoutMan112[]={

	  0,  0,0x0e,2|OAM_FLIP_H,
	  8,  0,0x0d,2|OAM_FLIP_H,
	  0,  8,0x1e,2|OAM_FLIP_H,
	  8,  8,0x1d,2|OAM_FLIP_H,
	  0, 16,0x2e,2|OAM_FLIP_H,
	  8, 16,0x2d,2|OAM_FLIP_H,
	 16, 16,0x2c,2,
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


