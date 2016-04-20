#pragma once
#include <vector>
class MyBoundingObjectManager
{
	static MyBoundingObjectManager* instance;
	std::vector<MyBoundingObject> boundObj;

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

	void addBoundingObject(MyBoundingObject boundObject)
	{
		boundObj.push_back(boundObject);
	}

	void createBoundingObject(std::vector<vector3> vertices)
	{
		boundObj.push_back(new MyBoundingObject(vertices));
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