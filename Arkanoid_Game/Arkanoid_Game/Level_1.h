#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.h"
#include "Game.h" 
#include "Ball.h"
#include "GameState.h"
#include "HeadsUpDisplay.h"
#include "GameOverState.h"
#include "PauseState.h"


class Level_1 :  public GameState
{
public:
	Level_1();

private:

	GameDataRef _data;
};

