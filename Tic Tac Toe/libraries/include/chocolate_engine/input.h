#ifndef INPUT_H
#define INPUT_H

#include<chocolate_engine/engine.h>

class Input
{
public:
	static bool GetKeyDown(int key) { return Get().IGetKeyDown(key); }

private:
	bool IGetKeyDown(int key);

public:
	Input(const Input&) = delete;

	static Input& Get()
	{
		static Input instance;
		return instance;
	}

private:
	Input() {}
};

#endif