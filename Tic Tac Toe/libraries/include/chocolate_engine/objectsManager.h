#ifndef OBJECTS_MANAGER_H
#define OBJECTS_MANAGER_H

#include<chocolate_engine/logger.h>
#include<vector>
#include <glad/glad.h>

class Object
{
public:
	virtual void Delete() = 0;
};

class ObjectsManager
{
private:
	vector<Object*> objects;

public:
	static void AddObject(Object* object) { return Get().IAddObject(object); }
	static void DeleteAllObjects() { return Get().IDeleteAllObjects(); }

private:
	void IAddObject(Object* object);
	void IDeleteAllObjects();


public:
	ObjectsManager(const ObjectsManager&) = delete;

	static ObjectsManager& Get()
	{
		static ObjectsManager instance;
		return instance;
	}

private:
	ObjectsManager() {}
};

#endif