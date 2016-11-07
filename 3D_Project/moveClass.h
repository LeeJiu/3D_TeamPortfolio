#pragma once
#include "cScene.h"

//============= ���� ���� =========
class cTerrain;
class cSkinnedAnimation;

class moveClass 
{
	cSkinnedAnimation*		pChar;  //�ɸ���
	cTransform*				pCharTrans;//�ɸ��Ϳ����� trans

	Ray                     moveRay;

	D3DXVECTOR3		m_currentPos;// �� �ɸ����� ��ġ
	D3DXVECTOR3		m_prePos;// ���� ������ ��ġ
	D3DXVECTOR3		m_lastPos;// ���� ���� y���� ��ȯ ��ų�� ����.
	D3DXVECTOR3		m_mousePos;// Ŭ�������� ��ġ.
    
	bool isMove;

	cTerrain*		m_pTerrain; // ���� ����.


	//==================== jump 
	bool isJump;
	float m_jumpPower;
	float m_gravity;

public:
	void init(cSkinnedAnimation* pSkinned, cTransform* trans, cTerrain* terrain);
	
	// �浹 ������Ʈ�� ������ �� �� ���� ���߿� ���� ������ �ٲ� ���� �ִ�.
	void update(float timeDelta, cBaseObject* collObj);
	void render();

	moveClass();
	~moveClass();
};

