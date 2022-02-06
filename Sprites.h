// a 16x16 pixel metasprite

// const unsigned char PlayerSprDown[] = {
// 		0, 0, 0x00, 0,
// 		8, 0, 0x00, 0 | OAM_FLIP_H,
// 		0, 8, 0x10, 0,
// 		8, 8, 0x10, 0 | OAM_FLIP_H,
// 		128};

// const unsigned char BlueSpr[] = {
// 		0, 0, 0x00, 1,
// 		8, 0, 0x00, 1 | OAM_FLIP_H,
// 		0, 8, 0x10, 1,
// 		8, 8, 0x10, 1 | OAM_FLIP_H,
// 		128};


const unsigned char PlayerSprDown[]={
	  0, 0,0x00,0,
	  8, 0,0x01,0,
	  0, 8,0x10,0,
	  8, 8,0x11,0,
	128
};

const unsigned char PlayerSprDownTwo[]={
	  0, 0,0x02,0,
	  8, 0,0x03,0,
	  0, 8,0x12,0,
	  8, 8,0x13,0,
	128
};

const unsigned char PlayerSprUp[]={
	  0, 0,0x08,0,
	  8, 0,0x09,0,
	  0, 8,0x18,0,
	  8, 8,0x19,0,
	128
};

const unsigned char PlayerSprUpTwo[]={
	  0, 0,0x0A,0,
	  8, 0,0x0B,0,
	  0, 8,0x1A,0,
	  8, 8,0x1B,0,
	128
};

const unsigned char PlayerSprRight[]={
	  0, 0,0x04,0,
	  8, 0,0x05,0,
	  0, 8,0x14,0,
	  8, 8,0x15,0,
	128
};

const unsigned char PlayerSprRightTwo[]={
	  0, 0,0x06,0,
	  8, 0,0x07,0,
	  0, 8,0x16,0,
	  8, 8,0x17,0,
	128
};

const unsigned char PlayerSprLeft[]={
	  0, 0,0x05,0 | OAM_FLIP_H,
		8, 0,0x04,0 | OAM_FLIP_H,
		0, 8,0x15,0 | OAM_FLIP_H,
	  8, 8,0x14,0 | OAM_FLIP_H,
	128
};

const unsigned char PlayerSprLeftTwo[]={
	  0, 0,0x07,0 | OAM_FLIP_H,
	  8, 0,0x06,0 | OAM_FLIP_H,
	  0, 8,0x17,0 | OAM_FLIP_H,
	  8, 8,0x16,0 | OAM_FLIP_H,
	128
};


// const unsigned char PlayerSprDown[]={
// 	- 8,- 8,0x00,0,
// 	  0,- 8,0x01,0,
// 	- 8,  0,0x10,0,
// 	  0,  0,0x11,0,
// 	128
// };

