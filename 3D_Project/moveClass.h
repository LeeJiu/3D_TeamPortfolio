#pragma once

//============= ���� ���� =========
class cTerrain;
class cSkinnedAnimation;
class cBaseObject;
class cCamera;

class moveClass 
{
	cSkinnedAnimation*		pChar;  //�ɸ���
	cTransform*				pCharTrans;//�ɸ��Ϳ����� trans
	cBaseObject*            pEnumy;    //�ֳʹ� �ּҰ� ( ���漱��)
	cCamera*				pMainCamera;
	Ray                     moveRay;

	D3DXVECTOR3		m_currentPos;// �� �ɸ����� ��ġ
	D3DXVECTOR3		m_prePos;// ���� ������ ��ġ
	D3DXVECTOR3		m_lastPos;// ���� ���� y���� ��ȯ ��ų�� ����.
	D3DXVECTOR3		m_mousePos;// Ŭ�������� ��ġ.
    
	bool isMove;    // �����̴�?
	bool isClick;   // Ŭ���ߴ�?
	cTerrain*		m_pTerrain; // ���� ����.


	//==================== jump 
	bool isJump;
	float m_jumpPower;
	float m_gravity;

	bool test;

public:
	void init(cSkinnedAnimation* pSkinned, cTransform* trans, cTerrain* terrain,cCamera* camera);
	
	// �浹 ������Ʈ�� ������ �� �� ���� ���߿� ���� ������ �ٲ� ���� �ִ�.
	void update(float timeDelta, cBaseObject* collObj);
	void render();

	void getLastHeight(cBaseObject* enumy);
	void clickUpdate(cBaseObject* enumy);
	void moveJumpCheck(float timeDelta);
	moveClass();
	~moveClass();
};

