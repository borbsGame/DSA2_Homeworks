#include "MyBoundingObjectManager.h"

MyBoundingObjectManager* MyBoundingObjectManager::instance;
MeshManagerSingleton* MyBoundingObjectManager::mesh;

	MyBoundingObjectManager* MyBoundingObjectManager::GetInstance()
	{
		if (instance == nullptr)
			instance = new MyBoundingObjectManager();
		return instance;
	}
	void MyBoundingObjectManager::ReleaseInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	MyBoundingObjectClass* MyBoundingObjectManager::createBoundingObject(String model) {
		return new MyBoundingObjectClass(mesh->GetVertexList(model));
	}

	void MyBoundingObjectManager::addBoundingObject(MyBoundingObjectClass boundObject)
	{
		boundObj.push_back(boundObject);
	}

	void MyBoundingObjectManager::createBoundingObject(std::vector<vector3> vertices)
	{
		boundObj.push_back(MyBoundingObjectClass(vertices));
	}

	void MyBoundingObjectManager::checkCollisions()
	{

	}

	void MyBoundingObjectManager::collide()
	{

	}

	void MyBoundingObjectManager::setMeshManager(MeshManagerSingleton* ms) {
		mesh = ms;
	}

	int MyBoundingObjectManager::getNumBoundObjects() {
		return boundObj.size();
	}

	MyBoundingObjectClass MyBoundingObjectManager::getBoundObject(int index)
	{
		if (index < getNumBoundObjects())
			return boundObj[index];
		else
			return boundObj[0];
	}

	void MyBoundingObjectManager::boxVisable(MyBoundingObjectClass boundObject, bool vis) {
		boundObject.setBoxVisibility(vis);
	}
	void MyBoundingObjectManager::setColor(MyBoundingObjectClass boundObject, vector3 color) {
		boundObject.setColor(color);
	}
	void MyBoundingObjectManager::renderSpecific(MyBoundingObjectClass boundObject) {
		boundObject.drawBO(mesh);
		boundObject.setBoxVisibility(true);
	}
	void MyBoundingObjectManager::renderAll() {
		for each(MyBoundingObjectClass bound in boundObj) {
			bound.drawBO(mesh);
			bound.setBoxVisibility(true);
		}
	}


	void MyBoundingObjectManager::Release()
	{
		boundObj.clear();
	}
