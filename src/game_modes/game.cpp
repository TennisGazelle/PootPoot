#ifndef __GAME_CPP_
#define __GAME_CPP_

#include "game_modes/game.h"

Game::Game() {

}

Game::~Game() {

}

bool ShootingGame::UpdatePlayers(unsigned int dt) {
  // Update the object
  m_player->update(dt);
  m_opponent->update(dt);

  bulletHolder->Update(dt);
}

bool ShootingGame::UpdateAIOpponent(unsigned int dt) {
  // opponent AI stuff
  static unsigned int movementTimer = 0;
  static unsigned int shootingTimer = 0;
  static int mod = 4;
  Direction opponentDir;
  
  switch(movementTimer % mod) {
     case 0:
       opponentDir = UP; break;
     case 1:
       opponentDir = DOWN; break;
     case 2:
       opponentDir = LEFT; break;
     case 3:
       opponentDir = RIGHT; break;
  }

  if (movementTimer % 100 < 7) {
    m_opponent->moveDirection(opponentDir);
  }
  if (shootingTimer % 157 == 0) {
    m_opponent->shootDirection(opponentDir);
  }

  movementTimer = rand() % 100;
  shootingTimer++;
}

bool ShootingGame::UpdateScore(unsigned int dt) {
  int shot = this->hasPlayerBeenShot();
  if (shot == 1 || shot == 3) {
    m_player->decrementHealth();
    std::cout << "player health is now: " << m_player->getHealth() << std::endl;
  }
  if (shot == 2 || shot == 3) {
    m_opponent->decrementHealth();
    std::cout << "opponent health is now: " << m_opponent->getHealth() << std::endl;
  }

  if (m_player->getHealth() <= 0) {
    std::cout << "You lost!" << std::endl;
    return false;    
  }
  if (m_opponent->getHealth() <= 0) {
    std::cout << "You Won!" << std::endl;
    return false;
  }
  return true;
}

#endif