#include "Score.h"


namespace
{
    int score = 0;
}

void Score::AddScore()
{
    score++;
}

void Score::ResetScore()
{
    score = 0;
}

int Score::GetScore()
{
    return score;
}
