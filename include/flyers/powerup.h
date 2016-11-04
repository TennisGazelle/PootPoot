#ifndef __POWERUP_H_
#define __POWERUP_H_

class AbstractPowerUp {
public:
	AbstractPowerUp() = 0;
	~AbstractPowerUp() = 0;

	// Initialize it
	void Init();

	// get a pointer to the objects in the game
	void setPlayerRef(Player* pPlayer);
	void setGameRef(Graphics* pGraphics);
	void setEngineRef(Engine* pEngine);

	// do change what needs to be change in the game
	virtual void execute() = 0;

private:
	static Object* collider;
	Object* powerUp;


};

class ResizePowerUp : private AbstractPowerUp {
public:
	// overload the execute function
	void execute();

private:
	int resizeingFactor = 50;
};



#endif