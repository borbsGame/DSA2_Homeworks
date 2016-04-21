#ifndef __MYBOUNDINGOBJECTMANAGER_H_
#define __MYBOUNDINGOBJECTMANAGER_H_

#include <vector>
#include "MyBoundingObjectClass.h"

class MyBoundingObjectManager
{
	static MyBoundingObjectManager* instance;
	static MeshManagerSingleton* mesh;

public:
	std::vector<MyBoundingObjectClass> boundObj;

	static MyBoundingObjectManager* GetInstance();

	static void ReleaseInstance();


	MyBoundingObjectClass* createBoundingObject(String model);

	void addBoundingObject(MyBoundingObjectClass boundObject);


	void createBoundingObject(std::vector<vector3> vertices);


	void checkCollisions();

	
	void collide(MyBoundingObjectClass bObjOne, MyBoundingObjectClass bObjTwo);


	void setMeshManager(MeshManagerSingleton* ms);

	int getNumBoundObjects();
	MyBoundingObjectClass getBoundObject(int index);
	

	void boxVisable(MyBoundingObjectClass boundObject, bool vis);
	void setColor(MyBoundingObjectClass boundObject, vector3 color);
	void renderSpecific(MyBoundingObjectClass boundObject);
	void renderAll();
	

private:
	MyBoundingObjectManager() {};
	MyBoundingObjectManager(MyBoundingObjectManager const& other) {};
	MyBoundingObjectManager& operator=(MyBoundingObjectManager const& other) {};
	~MyBoundingObjectManager() { Release(); }
	void Release();

};

#endif //__MYBOUNDINGOBJECTMANAGER_H_
