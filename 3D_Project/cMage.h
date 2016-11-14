#pragma once
#include "cBaseObject.h"
#include "cTestCommand.h"
#include "cTestCommand2.h"
#include "moveClass.h"


#define CONTROL_KEY 5

class cTerrain;
class cCamera;
class cInputHandler;
class cStateHandler;
class cWeapon;


class cMage : public cBaseObject
{
private:

	cWeapon*             pWeapon;
	

	cCamera*			m_camera;
	
	cBoundBox*           m_ATKBox;
	cTransform*          m_ATKBoxTrans;

	ACTOR_STATE			m_state;
	std::string			m_current_Ani;
	std::string			m_Aniname;
	std::map<int, bool> m_InputKeys;

	bool                m_isPetOn;
	bool				m_isMove;

	//컴포넌트를 달아준다.
	cInputHandler*		m_pInput;
	moveClass*			m_pMove;

public:
	cMage();
	~cMage();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
	void ATKBoxRender();
	void WeaponRender();
	
	void PetOnUpdate();

	void SetCamera(cCamera* camera) { m_camera = camera; }

	cBoundBox* GetATKBox() { return m_ATKBox; }
	cTransform* GetATKBoxTrans() { return m_ATKBoxTrans; }
	bool        GetIsPetOn() { return m_isPetOn; }
};


