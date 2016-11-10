#pragma once
#include "cState.h"


class cMoveState : public cState
{
private:
	cSkinnedAnimation*		m_pAnim;			//케릭터
	cTransform*				m_pCharTrans;		//케릭터움직일 trans

	Ray                     m_moveRay;

	D3DXVECTOR3		m_currentPos;		// 내 케릭터의 위치
	D3DXVECTOR3		m_prePos;			// 내가 갈곳의 위치
	D3DXVECTOR3		m_lastPos;			// 가장 높은 y값을 반환 시킬 때 쓸놈.
	D3DXVECTOR3		m_mousePos;			// 클릭했을때 위치.

	bool			m_bMove;

	int				m_VKey;

	cTerrain*		m_pTerrain;			// 전방 선언.

public:
	cMoveState(cBaseObject* pActor, ACTOR_STATE* pState);
	~cMoveState();

	void Enter(int nNum = 0);
	void Execute();
	void Exit();
};

