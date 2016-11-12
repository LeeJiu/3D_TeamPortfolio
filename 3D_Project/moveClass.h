#pragma once

//============= 전방 선언 =========
class cTerrain;
class cBaseObject;
class cCamera;

class moveClass 
{
	cTransform*				pCharTrans;//케릭터움직일 trans
	cBaseObject*            pEnumy;    //애너미 주소값 ( 전방선언)
	cCamera*				pMainCamera;
	Ray                     moveRay;

	D3DXVECTOR3		m_currentPos;// 내 케릭터의 위치
	D3DXVECTOR3		m_prePos;// 내가 갈곳의 위치
	D3DXVECTOR3		m_lastPos;// 가장 높은 y값을 반환 시킬떄 쓸놈.
	D3DXVECTOR3		m_mousePos;// 클릭했을때 위치.
    
	bool isMove;    // 움직이니?
	bool isClick;   // 클릭했니?
	cTerrain*		m_pTerrain; // 전방 선언.

	//==================== jump 
	bool isJump;
	float m_jumpPower;
	float m_gravity;

	bool test;
	bool objTest;

public:
	void init(cTransform* trans, cTerrain* terrain, cCamera* camera);
	
	// 충돌 오브젝트는 여러개 일 수 있음 나중에 벡터 형으로 바뀔 수도 있다.
	void update(float timeDelta, cBaseObject* collObj);
	void render();

	void getLastHeight(cBaseObject* enumy);
	void clickUpdate(cBaseObject* enumy);
	void moveJumpCheck(float timeDelta);

	bool GetIsMove() { return isMove; }

	moveClass();
	~moveClass();
};

