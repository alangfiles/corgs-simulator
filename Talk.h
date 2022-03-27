enum
{
  TALK_BLANK,
  TALK_ALAN,
  TALK_BRIAN,
  TALK_GUY,
  TALK_GAME,
  TALK_PLAY_GAME,
  TALK_LOCKED_DOORS,
  TALK_ITEM_1,
};

// we only have limited space to display, so here's the template for strings:
// this is used to line up what you type with the line breaks
// X is a character and \ is when the line break happens

//const unsigned char test[] =  "XXXXXXXXXXXXXXXXXXXXXXXXXX\XXXXXXXXXXXXXXXXXXXXXXXXXX\XXXXXXXXXXXXXXXXXXXXXXXXXX\";
const unsigned char item_1[] =  "You found a Famicom Disk   System copy of...             The Legend of Zelda";
const unsigned char blank_1[] = " ";
const unsigned char alan_1[] =  "Brian's to blame for the   graphics";
const unsigned char brian_1[] = "Alan's to blame for the    programming";
const unsigned char guy_1[] =   "This game's better than the real thing";
const unsigned char game_1[] =  "You found an old, dusty    game.";
const unsigned char locked_doors[] =  "You hear the doors click   behind you, they're locked.";
const unsigned char play_game_text[] = 
                                "A corgs emulator game,     looks fun, do you want to  play? Maybe not, it'll probably take all day and not be that interesting.";


//some texts I might want
const unsigned char game_text1[] = "Just some old video games";
const unsigned char game_text2[] = "You found a copy of Warren Robinett's Adventure for Atari 2600";
const unsigned char game_text34[] = "Just some arcade games with broken joysticks";
const unsigned char game_text35[] = "Pinball machines, but you're out of quarters";