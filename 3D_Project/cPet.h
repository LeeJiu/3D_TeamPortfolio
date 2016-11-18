#pragma once
#include "cBaseObject.h"
#include "moveClass.h"



class cTerrain;
class cCamera;
class cStateHandler;

class cPet : public cBaseObject
{
private:

	cCamera*			m_camera;

	ACTOR_STATE           m_state;
	std::string           m_current_Ani;
	std::string           m_Aniname;
	std::map<int, bool>   m_InputKeys;
	
	bool                  m_isMove;

	//������Ʈ�� �޾��ش�.
	moveClass*            m_pMove;


public:
	cPet();
	~cPet();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);


};

