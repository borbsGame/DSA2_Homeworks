#ifndef __MYBOUNDINGOBJECTMANAGER_H_
#define __MYBOUNDINGOBJECTMANAGER_H_

#include "RE\ReEng.h"
#include <vector>
#include "MyBoundingObjectClass.h"
class MyBoundingObjectManager
{
	static MyBoundingObjectManager* instance;
	std::vector<MyBoundingObjectClass> boundObj;
	static MeshManagerSingleton* mesh;

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
		boundObj.push_back(MyBoundingObjectClass(vertices));
	}

	void checkCollisions()
	{

	}

	void collide()
	{

	}

	void setMeshManager(MeshManagerSingleton* ms) {
		mesh = ms;
	}

	int getBoundObjects() {
		return boundObj.size();
	}
	void boxVisable(MyBoundingObjectClass boundObject, bool vis) {
		boundObject.setBoxVisibility(vis);
	}
	void setColor(MyBoundingObjectClass boundObject, vector3 color) {
		boundObject.setColor(color);
	}
	void renderSpecific(MyBoundingObjectClass boundObject) {
		boundObject.drawBO(mesh);
		boundObject.setBoxVisibility(true);
	}
	void renderAll() {
		for each(MyBoundingObjectClass bound in boundObj) {
			bound.drawBO(mesh);
			bound.setBoxVisibility(true);
		}
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