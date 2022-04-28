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

// const unsigned char test[] =  "XXXXXXXXXXXXXXXXXXXXXXXXXX\XXXXXXXXXXXXXXXXXXXXXXXXXX\XXXXXXXXXXXXXXXXXXXXXXXXXX\";
const unsigned char blank_1[] = "";
const unsigned char alan_1[] = "Brian's to blame for the\ngraphics.";
const unsigned char brian_1[] = "Alan's to blame for the\nprogramming.";
const unsigned char guy_1[] = "\n**You feel like someone\nis right behind you.**";
const unsigned char locked_doors[] = "You hear the doors click\nbehind you, they're locked.";
const unsigned char play_game_text[] = "A CORGS emulator game\nDo you want to play?";
const unsigned char talk_smoke[] = "This is a good place to\nsmoke, but I can't in\nan NES game.";
const unsigned char talk_bathroom[] = "I made a surprise in there\n\nIT'S A SECRET TO EVERYBODY";
const unsigned char talk_hotdog[] = "Back of the line!\n\nUnless you got cash.";
const unsigned char talk_hotdog2[] = "IT'S DANGEROUS TO GO\nALONE!  TAKE THIS.\n\n(It's a burger).";
const unsigned char talk_food[] = "I can't decide. Greasy\nburger or greasy salad?";
const unsigned char talk_bush[] = "These are nice bushes, but I don't think they'd make\ngood clouds.";
const unsigned char talk_nintendo[] = "I know all the cool games\ncoming out. My dad works\nat Nintendo.";
const unsigned char talk_buy[] = "BUY SOMETHIN' WILL YA!";
const unsigned char talk_plumber[] = "A plumber came to fix\nthe toliet, but he's been\nin there for an hour.\nI hope he didn't fall in.";
const unsigned char talk_location[] = "This is the location you\nget when you register for\nthe show last.";
const unsigned char talk_ebay[] = "Hold on while I check the\nprice on eBay...";
const unsigned char talk_admission[] = "Kids admitted free.\nChild at heart? Full charge";
const unsigned char talk_doorprize[] = "I hear this event has good door prizes.";
const unsigned char talk_guynext1[] = "The guy next to me has\nsome really good stuff!";
const unsigned char talk_guynext2[] = "I've got the same stuff as that guy.";
const unsigned char talk_thingyouwant[] = "Thingyoureallywant?  Yeah, I just sold one of those!";
const unsigned char talk_graded[] = "I'm going to buy this and\nhave it graded.";
const unsigned char talk_mywife[] = "If I buy this, my wife willkill me.";
const unsigned char talk_muscle1[] = "Bro, you look jacked. Wannado some reps?";
const unsigned char talk_do_reps[] = "Ready to press A\nas fast as you can?";
const unsigned char talk_reps_done[] = "Legit";
const unsigned char talk_reps_finished[] = "Rise from your grave!\n\nCause you're a BEAST!";
const unsigned char talk_more_reps[] = "You need more practice!";
const unsigned char talk_muscle2[] = "Brah, my bro is yoked. He \ndoes his reps at 61 FPS.";
const unsigned char talk_stick[] = "These buttons are really\nsticky.\n\nSo is the stick.";
const unsigned char talk_king[] = "I'm the king of video\ngames, but that place is a \nbit much.";
const unsigned char talk_arcade[] = "Arcade games are the best.\nThey're like normal games, but standing up.";
const unsigned char talk_pinball[] = "MMMMMULTIBALL!!";
const unsigned char talk_drugs[] = "Hey, psst. Want some drugs?\n\nHa! Gotcha!\n\nWinners Don't Use Drugs.\nWho am I?\n\nWilliam S Sessions, FBI."; // todo add choice
const unsigned char talk_speaker[] = "...and that's why COLECO\nAdam is the definitive\nvideo game machine.";
const unsigned char talk_crowd[] = "I know the speaker isn't\nvery lively, but that wouldtake up a lot of ROM space.";
const unsigned char talk_kick[] = "HEY! HEY! Wanna see my\nkickstarter?";
const unsigned char talk_copies[] = "I have a copy of\nthis, but I don't have two.";
const unsigned char talk_youtube[] = "The KING OF VIDEO GAMES?\nI think he's just a myth.";
const unsigned char talk_kingchat[] = "I hear the KING OF VIDEO\nGAMES is here today.";
const unsigned char talk_outside[] = "Why walk around outside\nwhen there's a video game\nshow going on.";
const unsigned char talk_newgames[] = "I hear they're making new\ngames for old hardware.\n\nI don't get it.";
const unsigned char talk_jealous[] = "Those CORGS simulator guys are stealing my thunder.";
const unsigned char talk_judge[] = "I'm judging this cosplay\ncontest.";
const unsigned char talk_character[] = "It's me! That character\nfrom that game you like!";
const unsigned char talk_pacman[] = "I ran my Blinky costume\nthrough the washer one too many times.\nNow I'm Pinky.";
const unsigned char talk_pacman2[] = "I can't believe that guy\nstole my costume idea.\nI'd say something...\nbut I'm Bashful.";
const unsigned char talk_wizard[] = "My costume?\n\n\n(W)izard (H)uman\n(M)ale (N)eutral.";
const unsigned char talk_genie[] = "I wonder if this game has\nany Game Genie codes. Like,UUVUZKNX or something.";
const unsigned char talk_sprites[] = "We'd have a better crowd\nhere if not for the\nsprite limitations.";
const unsigned char talk_gary[] = "Try to thank a Gary before\nyou leave today. They put\nlots of work into the show.";
const unsigned char talk_inyourway[] = "I just need to browse\nthrough everything here\nfour or five more times.";
const unsigned char talk_clever[] = "I think I saw a ghost!\n\nI FEEL ASLEEP.";
const unsigned char talk_eric[] = "I AM ERROR.\n\n...I mean, Eric.";
const unsigned char talk_complain[] = "I hate these guys, they\nnever sell anything.";
const unsigned char talk_foodtruck[] = "What'll you have!?";
const unsigned char talk_foodtruck2[] = "Sorry, this is really\njust a foodtruck simulator.";
const unsigned char talk_king2[] = "The KING OF VIDEO GAMES?\nI'm gonna try and get his\nautograph.";
const unsigned char talk_space[] = "I'm taking up 98 Bytes in\nthe game rom, but I'm too\nimportant to cut.";
const unsigned char talk_dlc[] = "CORGS Sim DLC down this path, $20 please.";
const unsigned char talk_clip[] = "BE CAREFUL\nLooks like you could clip\nthrough these walls.";


// const unsigned char talk_27[] = "You're not allowed back here, you might accidentally clip across the map.";

const unsigned char fetch_quest_1[] = "GRUMBLE GRUMBLE\nI'm hungry, but I\ncan't leave my booth\n\nCan you help?";
const unsigned char fetch_quest_2[] = "Thank you! One good burger deserves another";

// const unsigned char test[] =  "XXXXXXXXXXXXXXXXXXXXXXXXXX\XXXXXXXXXXXXXXXXXXXXXXXXXX\XXXXXXXXXXXXXXXXXXXXXXXXXX\";
const unsigned char item_1[] = "You found a Famicom Disk\nSystem copy of...\nThe Legend of Zelda";
const unsigned char item_2[] = "You found a Nintendo\nEntertainment System copy\nof...   Super Mario Bros.";
const unsigned char item_3[] = "You found an Atari 2600\ncopy of Warren Robinett's\nAdventure.";
const unsigned char item_4[] = "You got a Bally Midway\nArcade board of...\n Burger Time";
const unsigned char item_5[] = "Those ripped bros gave you\na 20lb kettlebell!";

const unsigned char fetch_1[] = "\nYou got a SILVER COIN!";
const unsigned char fetch_2[] = "\nYou got a JUMBO BURGER!";

const unsigned char intro_1[] = "In the year 20XX";
const unsigned char intro_2[] = "BRIAN J BURKE";
const unsigned char intro_3[] = "visited the CORGS game show";
const unsigned char intro_4[] = "to find the best games.";

// constants used to save rom space
const unsigned char time[] = "TIME";
const unsigned char no[] = "NO";
const unsigned char yes[] = "YES";
const unsigned char thirty_lives[] = "x30";
// const unsigned char intro_5[] = "THE KING OF VIDEO GAMES";

const unsigned char ending_1[] = "Did you collect them all?";
const unsigned char ending_2_1[] = "Truly, you are a";
const unsigned char ending_2_2[] = "KING OF VIDEO GAMES";

const unsigned char game_genie_text[] = "II Turbo: Championship Edition";

const unsigned char sidebar[] = {0xfd,0xfd,0xfd};
const unsigned char bottombar[] = {0xfe,0xed,0xff};


// big space holders
// const unsigned char lorem256_1[] = "LLorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
// const unsigned char lorem256_2[] = "LLorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
//  const unsigned char lorem256_3[] = "LLorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
//   const unsigned char lorem256_4[] = "LLorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aeneanorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";

// keeping track of space left. each line is 64bytes 4=256kb
//const unsigned char lorem1[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
//const unsigned char lorem2[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
//const unsigned char lorem3[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
//const unsigned char lorem4[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";

//const unsigned char lorem5[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
//const unsigned char lorem6[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
//  const unsigned char lorem7[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
//  const unsigned char lorem8[] = "orem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";

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
