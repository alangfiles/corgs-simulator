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
  TALK_ITEM_2,
  TALK_ITEM_3,
  TALK_ITEM_6,
  TALK_PUNCHOUT,
  TALK_KING,
  TALK_SMOKE,
  TALK_BATHROOM,
  TALK_HOTDOG,
  TALK_FOOD,
  TALK_BUSH,
  TALK_NINTENDO,
  TALK_BUY,
  TALK_PLUMBER,
  TALK_CLIP,
  TALK_LOCATION,
  TALK_EBAY,
  TALK_ADMISSION,
  TALK_DOORPRIZE,
  TALK_GUYNEXT1,
  TALK_GUYNEXT2,
  TALK_THINGYOUWANT,
  TALK_DLC,
  TALK_GRADED,
  TALK_MYWIFE,
  TALK_MUSCLE1,
  TALK_MUSCLE2,
  TALK_STICK,
  TALK_ARCADE,
  TALK_PINBALL,
  TALK_DRUGS,
  TALK_SPEAKER,
  TALK_CROWD,
  TALK_KICK,
  TALK_COPIES,
  TALK_YOUTUBE,
  TALK_KINGCHAT,
  TALK_OUTSIDE,
  TALK_NEWGAMES,
  TALK_JEALOUS,
  TALK_JUDGE,
  TALK_CHARACTER,
  TALK_PACMAN,
  TALK_PACMAN2,
  TALK_WIZARD,
  TALK_GENIE,
  TALK_SPRITES,
  TALK_GARY,
  TALK_INYOURWAY,
  TALK_CLEVER,
  TALK_ERIC,
  TALK_COMPLAIN,
  TALK_FETCHQUEST,
  TALK_FOODTRUCK,
  TALK_KING2,
  TALK_SPACE,
  TALK_FETCHQUEST_1,
  TALK_FETCHTWO,
  TALK_ITEM_4,
  TALK_DO_REPS,
  TALK_REPS_FINISHED,
  TALK_MORE_REPS,
  TALK_ITEM_5,
};

// we only have limited space to display, so here's the template for strings:
// this is used to line up what you type with the line breaks
// X is a character and \ is when the line break happens

//"You hear the doors click  behind you, they're locked.";
//                                    "XXXXXXXXXXXXXXXXXXXXXXXXXX\XXXXXXXXXXXXXXXXXXXXXXXXXX\XXXXXXXXXXXXXXXXXXXXXXXXXX\";
//"*You sense someone behind you*"

//"* A line forms behind you *"
// "Hey! Wait my turn, you're playing now."
//"*I feel someone behind me*"
// const unsigned char test[] =  "XXXXXXXXXXXXXXXXXXXXXXXXXX\XXXXXXXXXXXXXXXXXXXXXXXXXX\XXXXXXXXXXXXXXXXXXXXXXXXXX\";
// const unsigned char test[] =  "XXXXXXXXXXXXXXXXXXXXXXXXXX\XXXXXXXXXXXXXXXXXXXXXXXXXX\XXXXXXXXXXXXXXXXXXXXXXXXXX\";

// const unsigned char test[] =  "I didn't like the outdoors\Brian designed at first,\n\but I like them now.\";
const unsigned char blank_1[] = "";
const unsigned char alan_1[] = "Brian did the graphics.\nI didn't like the outdoors\nhe designed at first,\nbut I like them now.";
const unsigned char brian_1[] = "Alan kept running out of\nprogramming space, then\nfinding more.";
const unsigned char guy_1[] = "Nice outfit.";
const unsigned char locked_doors[] = "The doors lock behind you.";
const unsigned char play_game_text[] = "A CORGS simulator\nDo you want to play?";
const unsigned char talk_smoke[] = "This is a good place to\nsmoke, too bad I can't\nin an NES game.";
const unsigned char talk_bathroom[] = "I made a surprise in there.\nIT'S A SECRET TO EVERYBODY.";
const unsigned char talk_hotdog[] = "Back of the line!\n\nUnless you got cash.";
const unsigned char talk_hotdog2[] = "IT'S DANGEROUS TO GO\nALONE! TAKE THIS.\n\n\n*It's a burger*";
const unsigned char talk_food[] = "I can't decide. Greasy\nburger or greasy salad?";
const unsigned char talk_bush[] = "These are nice bushes, but I don't think they'd make\ngood clouds.";
const unsigned char talk_nintendo[] = "My dad works at Nintendo.";
const unsigned char talk_buy[] = "BUY SOMETHIN' WILL YA!";
const unsigned char talk_plumber[] = "A plumber came to fix\nthe toliet...\n\nI hope he didn't fall in.";
const unsigned char talk_location[] = "I was late to register,\nand this was the only\ntable left.";
const unsigned char talk_ebay[] = "Hold on while I check the\nprice on eBay...";
const unsigned char talk_doorprize[] = "This event has some\nreally neat door prizes!";
const unsigned char talk_guynext1[] = "The guy next to me has\nsome good stuff!";
const unsigned char talk_guynext2[] = "I've got the same stuff as that guy.";
const unsigned char talk_thingyouwant[] = "Thingyoureallywant?\nI just sold one of those!";
const unsigned char talk_mywife[] = "I'm going to buy this and\nhave it graded.";
const unsigned char talk_muscle1[] = "Bro, you look jacked.\nWanna do some REPS?";
const unsigned char talk_do_reps[] = "Ready to press A\nas fast as you can?";
const unsigned char talk_reps_done[] = "You gotta work your\nbody and your mind.";
const unsigned char talk_reps_finished[] = "Rise from your grave!\n\nCause you're a BEAST!";
const unsigned char talk_more_reps[] = "You need more practice!";
const unsigned char talk_muscle2[] = "Brah, my bro is yoked. He \ndoes his REPS at 61 FPS.";
const unsigned char talk_stick[] = "These buttons are really\nsticky.\n\nSo is the stick.";
const unsigned char talk_arcade[] = "Arcade games are the best!\nThey are like normal games,but with more standing.";
const unsigned char talk_pinball[] = "The guy in the corner\nlooks like\nWilliam S. Sessions!";
const unsigned char talk_drugs[] = "Psst. Want some drugs?\n\n\nHa! Gotcha!\n\nWinners Don't Use Drugs."; // todo add choice
const unsigned char talk_speaker[] = "...and that's why COLECO\nAdam is the definitive\nvideo game machine.";
const unsigned char talk_crowd[] = "The speaker isn't very\nlively, but that would takeup a lot of ROM space."; // ideas?
const unsigned char talk_kick[] = "HEY! HEY! Wanna see my\nkickstarter?";
const unsigned char talk_copies[] = "I have a copy of this,\nbut I don't have two.";
const unsigned char talk_youtube[] = "The KING OF VIDEO GAMES?\nI think he's just a myth.";
const unsigned char talk_kingchat[] = "I hear the KING OF VIDEO\nGAMES is here today.";
const unsigned char talk_outside[] = "Why walk around outside\nwhen there's a video game\nshow going on inside?";
const unsigned char talk_newgames[] = "I hear they're making new\ngames for old hardware.\n\nI don't get it.";
const unsigned char talk_judge[] = "I'm judging this cosplay\ncontest.";
const unsigned char talk_character[] = "Why does everyone avoid me?";
const unsigned char talk_pacman[] = "I ran my Blinky costume\nthrough the washer one too many times.\nNow I'm Pinky.";
const unsigned char talk_pacman2[] = "That guy stole my\ncostume idea!\nI'd say something...\nbut I'm Bashful.";
const unsigned char talk_wizard[] = "Wizard needs food\n\n\t\t\t\t...badly.";
const unsigned char talk_genie[] = "I wonder if this game has\nany Game Genie codes. Like,XLXZVNVX or something.";
const unsigned char talk_gary[] = "Thank a Gary before\nyou leave today. They put\nlots of work into the show.";
const unsigned char talk_inyourway[] = "I just need to browse\nthrough everything here\nfour or five more times.";
const unsigned char talk_clever[] = "Do you want to save your\ngame?\n\nYeah, that'd be cool\nif you could do that.";
const unsigned char talk_eric[] = "I AM ERROR.\n\n...I mean, Eric.";
const unsigned char talk_foodtruck[] = "WhatCHA want?";
const unsigned char talk_foodtruck2[] = "Sorry, this is just\na foodtruck simulator.";
const unsigned char talk_king2[] = "The KING OF VIDEO GAMES?\nI'm gonna try and get his\nautograph.";
const unsigned char talk_space[] = "I'm taking up 98 Bytes in\nthe game ROM, but I'm too\nimportant to cut.";

const unsigned char talk_dlc[] = "CORGS Sim DLC this way.\n\n\n$20 please.";
const unsigned char talk_clip[] = "HEY LISTEN!\nI think they put in that\nfence to prevent you from\nclipping through the map.";
const unsigned char talk_admission[] = "Kids admitted free.\n\nChild at heart? Full price.";
const unsigned char talk_graded[] = "I have 5 speedrunning\nrecords.";
const unsigned char talk_jealous[] = "Those CORGS simulator guys are stealing my thunder."; // ideas?
const unsigned char talk_sprites[] = "That block over there lookssuspicious, legendary even.";
const unsigned char talk_complain[] = "I hate these guys, they\nnever sell anything.";
const unsigned char talk_punchout[] = "A controller made out of a punching dummy hooked up toan old NES.";

// const unsigned char talk_27[] = "You're not allowed back here, you might accidentally clip across the map.";

const unsigned char fetch_quest_1[] = "GRUMBLE GRUMBLE\nI'm hungry, but I can't\nleave my booth...\nCan you help?";
// const unsigned char test[] =       "XXXXXXXXXXXXXXXXXXXXXXXXXX\XXXXXXXXXXXXXXXXXXXXXXXXXX\XXXXXXXXXXXXXXXXXXXXXXXXXX\";
const unsigned char fetch_quest_2[] = "Thank you! One super burgerdeserves another.\nHere you go!";
const unsigned char fetch_quest_4[] = "MUNCH MUNCH";

// const unsigned char test[] =  "XXXXXXXXXXXXXXXXXXXXXXXXXX\XXXXXXXXXXXXXXXXXXXXXXXXXX\XXXXXXXXXXXXXXXXXXXXXXXXXX\";
const unsigned char item_1[] = "You got a Famicom Disk\nSystem copy of...\nThe Legend of Zelda.";
const unsigned char item_2[] = "You got an Nintendo\nEntertainment System copy\nof... Super Mario Bros.";
const unsigned char item_3[] = "You got an Atari 2600\ncopy of Warren Robinett's\nAdventure.";
const unsigned char item_4[] = "You got an Arcade JAMMA\nboard of...\nSuper Burger Time.";
const unsigned char item_5[] = "Those bros gave you\na 20lb kettlebell!";
const unsigned char item_6[] = "You sure threw a lot of\nmoney at those video games!";

const unsigned char fetch_1[] = "You got a SILVER COIN!\n\nGo get that guy some food!";
const unsigned char fetch_2[] = "\nYou got a JUMBO BURGER!";

const unsigned char intro_1[] = "  It is the year 20XX...\n\n\tThe CORGS game show\nhas cool games. It is your\n  mission to find them all!";

// constants used to save rom space
const unsigned char time[] = "TIME";
const unsigned char no[] = "NO";
const unsigned char yes[] = "YES";
const unsigned char thirty_lives[] = "x30";

// const unsigned char ending_game[] = " game";
const unsigned char ending_drac[] = " What is a man? A cheerful little pile of video games.\t  But enough talk,\n\t   what have you?";
const unsigned char ending_0[] = "\t\tNary a game?!\n Hold thy peace and begone\n\t\t Thou Knave!";
const unsigned char ending_1[] = "\t\t Only ONE!?\n\t\t Thou art a\n\t SERF OF VIDEO GAMES";
const unsigned char ending_2[] = "\t  TWO are but few!\n\t\t Thou art a\n   VASSAL OF VIDEO GAMES";
const unsigned char ending_3[] = "\tVerily thou hast 3\n\t\t Thou art a\n   SQUIRE OF VIDEO GAMES";
const unsigned char ending_4[] = "\tA hearty four found!\n\t\tI dub thee a\n   KNIGHT OF VIDEO GAMES";
const unsigned char ending_5[] = "\t5!? Sit at my table\n\t\t Thou art a\n\tDUKE OF VIDEO GAMES";
const unsigned char ending_6[] = " 6! Thou hast more than me!\t Thou art the true\n\tKING OF VIDEO GAMES!";

// grade them based on the game
// 1 game, you are but video game stable boy / serf
// 2 games, you are a knight
// 3 games, you are a earl
// 4 games you are an archduke
// 5 games, you have even more than me!

const unsigned char game_genie_text[] = "II' Turbo Championship Edition";

const unsigned char sidebar[] = {0xfd, 0xfd, 0xfd};
const unsigned char bottombar[] = {0xfe, 0xed, 0xff};

// big space holders
// const unsigned char lorem256_1[] = "LLorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
// const unsigned char lorem256_2[] = "LLorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
// const unsigned char lorem256_3[] = "LLorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
// const unsigned char lorem256_4[] = "LLorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";

// keeping track of space left. each line is 64bytes 4=256kb
// const unsigned char lorem1[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
// const unsigned char lorem2[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
// const unsigned char lorem3[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
// const unsigned char lorem4[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";

// const unsigned char lorem5[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
// const unsigned char lorem6[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
// const unsigned char lorem7[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
// const unsigned char lorem8[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";

// const unsigned char lorem9[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
// const unsigned char lorem10[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
// const unsigned char lorem11[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
// const unsigned char lorem12[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";

// const unsigned char lorem13[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
// const unsigned char lorem14[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
// const unsigned char lorem15[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
// const unsigned char lorem16[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";

// const unsigned char lorem17[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
//  const unsigned char lorem18[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
//  const unsigned char lorem19[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
//  const unsigned char lorem20[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
