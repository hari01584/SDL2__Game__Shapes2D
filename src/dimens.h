#ifndef ANDROID_PROJECT_MAIN_D
#define ANDROID_PROJECT_MAIN_D

const static float MIN_OUT_OF_BOUNDS_Y_PARTICLE_SPEED = 3;
const static float MAX_OUT_OF_BOUNDS_Y_PARTICLE_SPEED = 7;
const static int DIMEN_FACTOR = 3;


const static int BACK_BUTTON_PRESS = 769;
extern int width;
extern int height;

const static int NO_OF_FALLING_POINTS_MAINSCREN = 100;
const static int NO_OF_FALLING_RECTANGLES_MAINSCREN = 15;
const static int NO_OF_FALLING_CIRLCES_MAINSCREN = 10;

const static char* TITLE_PATH = "assets/title.png";

const static char* IMAGE_PLAY_BG = "assets/playbg.png";
const static char* IMAGE_PLAY = "assets/play.png";
const static char* IMAGE_OPTIONS_BG = "assets/optionsbg.png";
const static char* IMAGE_OPTIONS = "assets/options.png";
const static char* IMAGE_EXIT_BG = "assets/exitbg.png";
const static char* IMAGE_EXIT = "assets/exit.png";

const static char* BABY_INFO_BG = "assets/babyinfobg.png";
const static char* BABY_INFO_INSTR = "assets/babyinfoInstr.png";

const static char* BABY_CONFIRM_BG = "assets/confBaby.png";
const static char* BABY_CONFIRM = "assets/confBabytext.png";


const static char* FONT_OPENSANS = "assets/fonts/OpenSans-Regular.ttf";

#if defined(ANDROID)
const static char* HEADER_BABY = "How to play? (1st Time Instructions)";
const static char* S02_BABY = "-> Android touch, drag and hold object to move!";
const static char* S03_BABY = "-> Double click on object to morph";
const static char* S04_BABY = "-> Avoid red and orange while getting green!";

#else
const static char* HEADER_BABY = "How to play? (1st Time Instructions)";
const static char* S02_BABY = "-> Use WASD To Navigate Your Block!";
const static char* S03_BABY = "-> Space To Morph Your Shape Object!";
const static char* S04_BABY = "-> Avoid red and orange while getting green!";

#endif


const std::string gameover_quotes[] ={
        "As you stumble upon the infinite, you lost the track of the one who took your life..",
        "The game is not that easy as it sounds, Just try it!",
        "TIP: Always farm for more health at beginning of rounds!"
        "Game made by Agent Orange! :D (Self Shoutout yey)",
        "You dont need to avoid all the red blocks, The goal is to get more green and not lose!",
        "Sometimes you must take wrong steps to arrive at right decisions.",
        "I feel happy making this game, It was my first which is released!",
        "After certain period of time there will be quick rush (Very speedy objects) [Not a feature, But a bug]",
        "I used almost everything in my CPP knowledge to make this game (Yep its inadequate, ikr)",
        "A game doesnt need to be grand, It should be simple and fun! ~HSK(Someone you dont know)"
};

//#ifdef ANDROID
//const static std::string IMAGE_PLAY = "assets/android/play.png";
//const static std::string IMAGE_OPTIONS = "assets/android/options.png";
//const static std::string IMAGE_EXIT = "assets/android/exit.png";
//#else
//const static std::string IMAGE_PLAY = "assets/windows/play.png";


#endif
