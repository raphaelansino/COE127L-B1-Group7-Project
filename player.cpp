#include "player.h"

player::player()
{
    //ctor
}

player::~player()
{
    //dtor
}

void player::setname(std::string n)
{
    name = n;
}

void player::setScore(int s)
{
    score = s;

}

std::string player::getName()
{
    return name;

}

int player::getScore()
{
    return score;
}
