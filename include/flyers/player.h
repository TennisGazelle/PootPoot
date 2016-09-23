#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "flyer.h"

class Player : public Flyer {
public:
	Player();
	~Player();
	
	void moveDirection(Direction dir);
	void shootDirection(Direction dir);

private:	

};

#endif