
#pragma once

#include <string>

class BotData {
public:
    std::string name;
    std::string catchPhrase;
    std::string playStyle;
};



const BotData RANDALL_BOT_DATA = {
    "Randall",
    "Knows how the pieces move, but that's about it.",
    "Makes random moves."
};

const BotData GREEDO_BOT_DATA = {
    "Greedo",
    "Greedy little bastard, and quite stupid.",
    "Random but prioritizes taking pieces."
};

const BotData TREE_WIZARD_BOT_DATA = {
    "Tree Wizard",
    "Knows what is to come",
    "Can see several moves into the future, depending on setting."
};
// Beat 400 elo bot
