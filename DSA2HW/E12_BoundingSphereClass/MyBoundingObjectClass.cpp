#include "MyBoundingObjectClass.h"

void MyBoundingObjectClass::Init(void)
{
	m_fRadius = 0.0f;
	m_m4ToWorld = IDENTITY_M4;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);
}
void MyBoundingObjectClass::Swap(MyBoundingObjectClass& other)
{
	std::swap(m_fRadius, other.m_fRadius);
	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);
}
void MyBoundingObjectClass::Release(void)
{

}
//The big 3
MyBoundingObjectClass::MyBoundingObjectClass(std::vector<vector3> a_lVectorList)
{
	uint nVertexCount = a_lVectorList.size();

	if (nVertexCount > 0)
	{
		m_v3Min = a_lVectorList[0];
		m_v3Max = a_lVectorList[0];
	}

	for (uint i = 0; i < nVertexCount; i++)
	{
		if (a_lVectorList[i].x > m_v3Max.x)
			m_v3Max.x = a_lVectorList[i].x;
		else if (a_lVectorList[i].x < m_v3Min.x)
			m_v3Min.x = a_lVectorList[i].x;

		if (a_lVectorList[i].y > m_v3Max.y)
			m_v3Max.y = a_lVectorList[i].y;
		else if (a_lVectorList[i].y < m_v3Min.y)
			m_v3Min.y = a_lVectorList[i].y;

		if (a_lVectorList[i].z > m_v3Max.z)
			m_v3Max.z = a_lVectorList[i].z;
		else if (a_lVectorList[i].z < m_v3Min.z)
			m_v3Min.z = a_lVectorList[i].z;
	}

	m_v3Center = (m_v3Max + m_v3Min) / 2.0f;
	m_fRadius = glm::distance(m_v3Center, m_v3Max);
	m_v3Size.x = glm::distance(vector3(m_v3Min.x, 0.0, 0.0), vector3(m_v3Max.x, 0.0, 0.0));
	m_v3Size.y = glm::distance(vector3(0.0, m_v3Min.y, 0.0), vector3(0.0, m_v3Max.y, 0.0));
	m_v3Size.z = glm::distance(vector3(0.0f, 0.0, m_v3Min.z), vector3(0.0, 0.0, m_v3Max.z));
}
MyBoundingObjectClass::MyBoundingObjectClass(MyBoundingObjectClass const& other)
{
	m_fRadius = other.m_fRadius;
	m_m4ToWorld = other.m_m4ToWorld;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;
}
MyBoundingObjectClass& MyBoundingObjectClass::operator=(MyBoundingObjectClass const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyBoundingObjectClass temp(other);
		Swap(temp);
	}
	return *this;
}
MyBoundingObjectClass::~MyBoundingObjectClass() { 
	Release(); 
};

void MyBoundingObjectClass::drawBO(MeshManagerSingleton* meshMngr) {
	if (m_isVisible) {
		if (m_boxVisible) {
			meshMngr->AddCubeToRenderList(
				glm::translate(vector3(this->GetCentroidWorld())) *
				glm::scale(vector3(this->GetSize())), this->m_Color, WIRE);
		}
		meshMngr->AddSphereToRenderList(
			glm::translate(vector3(this->GetCentroidWorld())) *
			glm::scale(vector3(this->GetRadius()) * 2.0f), this->m_Color, WIRE);
	}
	if (this->m_Color == RERED) {
		std::cout << "ayo";
	}
	if (this->m_Color == REGREEN) {
		std::cout << "ayo";
	}
}


//Accessors
void MyBoundingObjectClass::SetModelMatrix(matrix4 a_m4ToWorld) { 
	m_m4ToWorld = a_m4ToWorld;
}
vector3 MyBoundingObjectClass::GetCentroidWorld(void) { 
	return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f)); 
}
vector3 MyBoundingObjectClass::GetCentroidLocal(void) {
	return m_v3Center;
}
float MyBoundingObjectClass::GetRadius(void) { 
	return m_fRadius; 
}
matrix4 MyBoundingObjectClass::GetModelMatrix(void) {
	return m_m4ToWorld;
}
vector3 MyBoundingObjectClass::GetSize(void) {
	return m_v3Size;
}
void MyBoundingObjectClass::setColor(vector3 color) {
	this->m_Color = color;
}
vector3 MyBoundingObjectClass::getMinimum() {
	return m_v3Min;
}
void MyBoundingObjectClass::setMinimum(vector3 newMin) {
	m_v3Min = newMin;
}
vector3 MyBoundingObjectClass::getMaximum() {
	return m_v3Max;
}
void MyBoundingObjectClass::setMaximum(vector3 newMax) {
	m_v3Max = newMax;
}
bool MyBoundingObjectClass::getVisibility(){
	return m_isVisible;
}
void MyBoundingObjectClass::setVisibility(bool isVisible) {
	m_isVisible = isVisible;
}
bool MyBoundingObjectClass::getBoxVisibility() {
	return m_boxVisible;
}
void MyBoundingObjectClass::setBoxVisibility(bool isVisible) {
	m_boxVisible = isVisible;
}


bool MyBoundingObjectClass::IsColliding(MyBoundingObjectClass* const a_pOther)
{
	vector3 v3Temp = vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f));
	vector3 v3Temp1 = vector3(a_pOther->GetModelMatrix() * vector4(a_pOther->GetCentroidLocal(), 1.0f));

	bool bAreColliding = false;
	bAreColliding = (glm::distance(v3Temp, v3Temp1) < m_fRadius + a_pOther->GetRadius());

	if (bAreColliding) {

		vector3 v3Temp = vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f));
		vector3 v3Temp1 = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->GetCentroidLocal(), 1.0f));

		bAreColliding = true;
		vector3 vMin1 = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
		vector3 vMax1 = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));
		vector3 vMin2 = vector3(a_pOther->GetModelMatrix() * vector4(a_pOther->getMinimum(), 1.0f));
		vector3 vMax2 = vector3(a_pOther->GetModelMatrix() * vector4(a_pOther->getMaximum(), 1.0f));

		//Check for X
		if (vMax1.x < vMin2.x)
			bAreColliding = false;
		if (vMin1.x > vMax2.x)
			bAreColliding = false;

		//Check for Y
		if (vMax1.y < vMin2.y)
			bAreColliding = false;
		if (vMin1.y > vMax2.y)
			bAreColliding = false;

		//Check for Z
		if (vMax1.z < vMin2.z)
			bAreColliding = false;
		if (vMin1.z > vMax2.z)
			bAreColliding = false;

	}
	return bAreColliding;

}
