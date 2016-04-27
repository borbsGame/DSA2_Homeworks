#ifndef __MYBOUNDINGOBJECTCLASS_H_
#define __MYBOUNDINGOBJECTCLASS_H_

#include "RE\ReEng.h"


class MyBoundingObjectClass
{
	float m_fRadius = 0.0f; 
	vector3 m_v3Size = vector3(0.0f);
	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_v3Center = vector3(0.0f); //Will store the center point
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector
	vector3 m_Color = REBLUE;
	bool m_isVisible = true;
	bool m_boxVisible = true;


public:
	//Constructor
	MyBoundingObjectClass(std::vector<vector3> a_lVectorList);

	//Copy Constructor
	MyBoundingObjectClass(MyBoundingObjectClass const& other);
	
	//Copy Assignment Operator
	MyBoundingObjectClass& operator=(MyBoundingObjectClass const& other);
	
	//Destructor
	~MyBoundingObjectClass(void);

	//Changes object contents for other object's
	void Swap(MyBoundingObjectClass& other);

	//Sets the Bounding Object into world coordinates
	void SetModelMatrix(matrix4 a_m4ToWorld);

	//Gets the Bounding Object's center in world coordinates
	vector3 GetCentroidWorld(void);

	vector3 GetCentroidLocal(void);

	//Gets radius of Bounding object's collision sphere
	float GetRadius(void);

	//Checks if there is a collision with another Bounding sphere Object
	bool IsColliding(MyBoundingObjectClass* const a_pOther);

	matrix4 GetModelMatrix(void);

	vector3 GetSize(void);

	//New Methods for Bounding Object
	void setVisibility(bool isVisible);
	bool getVisibility();

	void setBoxVisibility(bool isVisible);
	bool getBoxVisibility();

	void setColor(vector3 color);

	vector3 getMinimum();
	void setMinimum(vector3 newMin);
	vector3 getMaximum();
	void setMaximum(vector3 newMax);

	void drawBO(MeshManagerSingleton* meshMngr);

private:
	
	void Release(void);
	
	void Init(void);
};

#endif //__MYBOUNDINGOBJECTCLASS_H_
