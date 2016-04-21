#ifndef __MYBOUNDINGOBJECTMANAGER_H_
#define __MYBOUNDINGOBJECTMANAGER_H_

#include "RE\ReEng.h"
#include <vector>
#include "MyBoundingObjectClass.h"
class MyBoundingObjectManager
{
	static MyBoundingObjectManager* instance;
	std::vector<MyBoundingObjectClass> boundObj;

public:
	static MyBoundingObjectManager* GetInstance()
	{
		if (instance == nullptr)
			instance = new MyBoundingObjectManager();
		return instance;
	}
	static void ReleaseInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void addBoundingObject(MyBoundingObjectClass boundObject)
	{
		boundObj.push_back(boundObject);
	}

	void createBoundingObject(std::vector<vector3> vertices)
	{
		boundObj.push_back(new MyBoundingObjectClass(vertices));
	}

	void checkCollisions()
	{

	}

	void collide()
	{

	}
	
private:
	MyBoundingObjectManager() {};
	MyBoundingObjectManager(MyBoundingObjectManager const& other) {};
	MyBoundingObjectManager& operator=(MyBoundingObjectManager const& other) {};
	~MyBoundingObjectManager() { Release(); }
	void Release()
	{
		boundObj.clear();
	}
	
};

#endif //__MYBOUNDINGOBJECTMANAGER_H_