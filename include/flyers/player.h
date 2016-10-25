#ifndef __PLAYER_H_
#define __PLAYER_H_

#include <vector>

#include "flyer.h"
#include "bullet_holder.h"


class Player : public Flyer {
public:
	Player(BulletHolder* pBulletHolderPtr);
	~Player();
	
	//overloaded inhereted objects
	void Update(unsigned int dt);
	void Render();
	
	void moveDirection(Direction dir);
	void shootDirection(Direction dir);

	int getHealth() const;
	void decrementHealth();

private:	
	int health;
	BulletHolder* bulletHolderPtr;

};

#endif
