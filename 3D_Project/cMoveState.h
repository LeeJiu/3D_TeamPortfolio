#pragma once
#include "cState.h"


class cMoveState : public cState
{
private:
	cSkinnedAnimation*		m_pAnim;			//�ɸ���
	cTransform*				m_pCharTrans;		//�ɸ��Ϳ����� trans

	Ray                     m_moveRay;

	D3DXVECTOR3		m_currentPos;		// �� �ɸ����� ��ġ
	D3DXVECTOR3		m_prePos;			// ���� ������ ��ġ
	D3DXVECTOR3		m_lastPos;			// ���� ���� y���� ��ȯ ��ų �� ����.
	D3DXVECTOR3		m_mousePos;			// Ŭ�������� ��ġ.

	bool			m_bMove;

	int				m_VKey;

	cTerrain*		m_pTerrain;			// ���� ����.

public:
	cMoveState(cBaseObject* pActor, ACTOR_STATE* pState);
	~cMoveState();

	void Enter(int nNum = 0);
	void Execute();
	void Exit();
};

