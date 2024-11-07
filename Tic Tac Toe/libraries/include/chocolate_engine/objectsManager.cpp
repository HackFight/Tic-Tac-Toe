#include<chocolate_engine/objectsManager.h>

void ObjectsManager::IAddObject(Object* object)
{
	objects.push_back(object);
}

void ObjectsManager::IDeleteAllObjects()
{
	for (int i = 0; i < objects.size(); i++)
	{
		(*objects[i]).Delete();
	}

	objects.clear();
}