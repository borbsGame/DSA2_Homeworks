class MyBoundingObjectManager
{
	static MyBoundingObjectManager* instance;
	
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
	
private:
	MyBoundingObjectManager() {};
	MyBoundingObjectManager(MyBoundingObjectManager const& other) {};
	MyBoundingObjectManager& operator=(MyBoundingObjectManager const& other) {};
	~MyBoundingObjectManager() { Release(); }
	void Release()
	{
		
	}

}