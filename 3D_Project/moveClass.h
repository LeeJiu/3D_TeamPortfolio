#pragma once

//============= ���� ���� =========
class cTerrain;
class cBaseObject;
class cCamera;
class cBoundBox;

#define HEADPOS 4.f
class moveClass 
{
	cTransform*				pCharTrans;//�ɸ��Ϳ����� trans
	cBoundBox*              pCharBound;

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
	bool isOnAir;
	float m_jumpPower;
	float m_gravity;

	//==================== control
	std::map<int, bool>	m_InputKey;

	//bool test;
	//bool objTest;

public:
	void init(cTransform* trans, cTerrain* terrain, cCamera* camera);
	void init(cTransform* trans, cTerrain* terrain,cCamera* camera,cBoundBox* pBox);

	// �浹 ������Ʈ�� ������ �� �� ���� ���߿� ���� ������ �ٲ� ���� �ִ�.
	void update(float timeDelta, cBaseObject* collObj, cBoundBox* collBox, cTransform* collTrans);
	void update(float timeDelta, cBaseObject* collObj, cBoundBox* collBox, cTransform* collTrans, std::map<int, bool> key);
	void update(float timeDelta, std::vector<cBaseObject*> vObj, std::vector<cBaseObject*> vBound, std::map<int, bool> key);
	void render();

	void boundCheck(cBoundBox* collBox,cTransform* collTrans);
	void boundCheck(std::vector<cBaseObject*> vBound);

	void getLastHeight(cBaseObject* enumy);
	void getLastHeight(std::vector<cBaseObject*> vObj);

	void clickUpdate(cBaseObject* enumy);
	void moveJumpCheck(float timeDelta);

	bool GetIsMove() { return isMove; }
	bool GetIsJump() { return isJump; }
	Ray getRay(){ return moveRay; }
	moveClass();
	~moveClass();
};

