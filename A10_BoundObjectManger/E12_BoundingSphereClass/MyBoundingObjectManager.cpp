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
		/*int index = 0;
		MyBoundingObjectClass temp1 = boundObj.at(index);

		int count = 1;
		bool notDone = true;

		while (index < getNumBoundObjects())
		{
			MyBoundingObjectClass* temp2 = &getBoundObject(count);

			if (temp1.IsColliding(temp2))
			{
				collide(temp1, getBoundObject(count));
			}
			else
			{
				setColor(temp1, REGREEN);
				if (count == getNumBoundObjects()) { count = 0; index++; }
				else { count++; }
				
			}

		}*/
		int count = 1;
		int numofBO = getNumBoundObjects();
		static int index = 0;

		for (int i = 1; i < numofBO; i++)
		{
			MyBoundingObjectClass temp1 = boundObj.at(index);
			MyBoundingObjectClass* temp2 = &getBoundObject(i);

			if (temp1.IsColliding(temp2))
			{
				collide(temp1, getBoundObject(i));
			}
			else if (count == 0)
			{
				index++;
			}
			else
			{
				setColor(temp1, REGREEN);
				count++;
				count %= numofBO;
			}
		}

		if (index == numofBO)
		{
			index = 0;
		}


	}

	void MyBoundingObjectManager::collide(MyBoundingObjectClass bObjOne, MyBoundingObjectClass bObjTwo)
	{
		setColor(bObjOne, REBLUE);
		setColor(bObjTwo, REBLUE);
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
