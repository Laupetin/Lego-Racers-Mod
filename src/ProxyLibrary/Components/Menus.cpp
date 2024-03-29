#include "Menus.h"

#include "Detour.h"
#include "Game/Fields.h"
#include "Offset.h"
#include "Patch.h"
#include "RacersOffset.h"

#include <iostream>

namespace menus
{
    const char* menuNames[]{
        "testmenu", "splash",   "mainmenu", "garage",   "pickset",  "circrace", "singrace", "tuneup",   "options",  "control",  "control1", "control2",
        "pickmem",  "pause",    "carbuild", "editdrvr", "drvrlice", "editcar",  "selchas",  "pickrcr",  "pickrcr",  "pickrcr",  "c_award1", "c_award2",
        "c_award3", "c_award4", "wincar",   "winrrcar", "winvvcar", "ttrial",   "multipic", "circuit1", "circuit2", "circuit3", "circuit4", "circuit5",
        "circuit6", "circuit7", "mainintr", "credits",  "legal",    "legointr", "n64start", "n64intr",  "picklang", "loadall",  "loadnopt", "loadcard",
        "lccreate", "saveall",  "savecard", "savegame", "damaged",  "rumble",   "rumblein", "rumblout", "demolice", "demobuy",  "demobuy2", "strtlang",
        "calibrte", "calbrt1",  "calbrt2",  "arrow",    "menufont", "tinyfont", "font_emb", "banner",   "picker",   "blue",     "textbox",  "imagebox",
        "goback",   "gonext",   "gorace",   "nubutton", "buttonla", "buttonra", "buttonca", "buttonch", "brickbox", "roundbox", "backdrp",  "arrowrs",
        "arrowls",  "textcont", "imagecon", "chck",     "txtarol",  "txtaror",  "racers",   "racers1",  "racers2",  "circuit",  "single",   "vs",
        "time",     "quit",     "legohost", "hosting",  "champtxt", "racename", "dimmer",   "circtext", "numbtext", "circ1",    "circ2",    "circ3",
        "circ4",    "circ5",    "circ6",    "circ7",    "circ7",    "racesel",  "besttime", "besttype", "bestname", "timestat", "showcase", "show2",
        "rcont",    "rcont",    "storage1", "storage2", "breath1",  "breath2",  "sway",     "swayf",    "watch",    "hips",     "tapfoot",  "hey!",
        "jump",     "ta-da",    "yes!",     "spin",     "kiss",     "look",     "kick",     "head1",    "chest",    "leg",      "left1",    "left2",
        "right1",   "right2",   "ok",       "cancel",   "okicon",   "backicon", "racer1",   "racer2",   "newracer", "editracr", "copyracr", "delracer",
        "testtrck", "selector", "context",  "showcase", "editlice", "dialog",   "build",    "ripapart", "qbuild",   "setimage", "bricks",   "race",
        "space",    "castle",   "pirate",   "islander", "magical",  "adventur", "jungle",   "alien",    "rr",       "vv",       "sets",     "sexbox",
        "pieces",   "piecebox", "piecesel", "pieceset", "icon",     "addbrik",  "rotbrik",  "undobrik", "crocker",  "procker",  "exitdoor", "car",
        "piece",    "as",       "brick",    "brick2",   "brick3",   "brckarrw", "bs",       "cameras",  "start",    "stick",    "zs",       "done",
        "dpad1",    "dpad2",    "lshift",   "rshift",   "abutton",  "bbutton",  "uarrow",   "darrow",   "hatsel",   "facesel",  "torsosel", "legsel",
        "partcont", "partbox",  "headbox",  "partpk",   "platform", "lights",   "mix",      "check",    "shaking",  "picbox",   "license",  "textedit",
        "editbox",  "firstbox", "fname",    "ftext",    "swapface", "gold",     "silver",   "bronze",   "trophy1",  "trophy2",  "trophy3",  "trophy4",
        "trophy5",  "trophy6",  "trophy7",  "trophy8",  "select",   "picka",    "pickb",    "dontsave", "slider",   "soundsli", "game",     "video",
        "audio",    "player1",  "player2",  "language", "chmpcont", "lapcont",  "driver",   "drivebox", "drivetxt", "brislide", "musicvol", "soundvol",
        "monobox",  "monocont", "inputsel", "inputcon", "rescont",  "chmptext", "laptext",  "dritext",  "britext",  "mvoltext", "svoltext", "monotext",
        "mono",     "rumblcon", "rumbltxt", "turnleft", "turnrght", "acceler",  "brake",    "fire",     "camera",   "map",      "slide",    "lookback",
        "contcon",  "joystick", "gamepad",  "wheel",    "keyboard", "lefttext", "rghttext", "acletext", "brketext", "firetext", "camtext",  "maptext",
        "pwsltext", "lkbktext", "dshock",   "dialfrme", "dialtext", "okbut",    "yesbut",   "nobut",    "noctl1",   "prevnote", "nextnote", "cuarrow",
        "cdarrow",  "delnote",  "notelst1", "notelst2", "notelst3", "notelst4", "notelst5", "ntszlst1", "ntszlst2", "ntszlst3", "ntszlst4", "ntszlst5",
        "pages",    "pagefree", "numfree",  "langcont", "english",  "spanish",  "french",   "german",   "italian",  "danish",   "swedish",  "norway",
        "dutch",    "finnish",  "sgerr1",   "sgerr2",   "sgerr3",   "sgerr4",   "memcard1", "memcard2", "memcard3", "memcard4", "contbttn", "contbtn2",
        "cfrmyes",  "cfrmno",   "deadzone", "deadtxt",  "sense",    "sensetxt", "realtime", "realtxt",
    };
}

using namespace menus;

ComponentMenus::ComponentMenus()
    : Component("Menus")
{
}

bool ComponentMenus::InstallInternal()
{
    static FunctionDetourTrampolineThiscall<int(void*, int)> menuFunc;
    menuFunc.Init(Offset().Racers01(0x451590),
                  [](void* self, const int num) -> int
                  {
                      std::cout << "Loading menu num " << num;

                      if (num >= 0 && static_cast<size_t>(num) < std::extent_v<decltype(menuNames)>)
                      {
                          std::cout << " (" << menuNames[num] << ")";
                      }

                      std::cout << "\n";

                      return menuFunc(self, num);
                  });

    return true;
}
