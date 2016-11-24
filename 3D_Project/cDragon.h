#pragma once
#include "cMonster.h"
#include "cBoundBox.h"
#include "cTickFunc.h"

#define COLLISION 4
#define TICKMAX 5
/*
   ������ �ɾ�� ������ ���۵�.
   ���� ġ���� ���� �������� ����ߵ�.
*/
enum BONE_NAME_INDEX
{
	BODY,HEAD,LHANAD,RHAND
};
enum SKILL_NAME //ƽ Ŭ�������� ����. 
{
	BasicAtt, HeadAtt,Breath, Earthquake,Pattern
};
struct stSphere
{
	D3DXVECTOR3 worldCenter;
	float radius;
};

class cDragon : public cMonster
{
private:
	int m_collCount;                    //���� ������ ������ ����
	cBoundBox m_bound[COLLISION];       //���� �� �ٿ
	cTransform* m_pBoneTrans[COLLISION]; //���� �� Ʈ����
	cTickFunc* m_tick[TICKMAX];

	D3DXVECTOR3 m_collPos[8];
	cTransform* m_pCollTrans[5];           //�浹üũ�� �� Ʈ����

	stSphere m_spone;                     // ������ ���� ��. 
	stSphere m_basicAttack;               // ��Ÿ ���� �Ÿ�

	string m_nowAni;                      // �ִϸ��̼�
	
	int skillChance;                      // ��ų �ߵ�Ȯ��
	
	int basicAttCoolTime;                 // �⺻ ���� ��Ÿ��. 

	bool isMove;                          // �����̴���?
	bool isBattle;                        // ������?
	bool isBasicAttack;                   // ��Ÿ��?
	
	bool isBreath;                        // �극����?
	bool isEarthquake;                    // ������?
	bool isHeadAtt;                       // �Ӹ� ġ��
	
	bool isNoneBasicAttack;               // ��Ÿ�̿��� ��ų.( ���� �Ⱦ��� �𸣰��� )

	float skillCoolTime;                 // ��ų ��Ÿ��
	float tempCoolTime;                  // ��ų ��Ÿ�ֿ̹� ��� �� ��

	//========== ���� ���� ���� �����ٶ� �� ����
	bool isRenderEarthquake;            // ������?
	
	stSphere  m_circle[5];              // �� ����
	D3DXVECTOR3      m_quad[3][6];      // ���� ���� 
	//========== ���� , �극�� ���� ���ִ� �Լ� 
	bool earthRender;
	bool breathRender;
    
public:
	cDragon();
	~cDragon();
	
	void BaseObjectEnable();					//SetActive(true)�ϸ� ����� -> �ʱ�ȭ �Լ�
	void BaseObjectUpdate(float timeDelta);		//BaseObject �� Update �� ����....
	void BaseObjectBoundBox();					//SetMesh() �ϸ� ComputeBoundBox() ����Ǹ鼭 �����
	void BaseObjectRender();
	
	
	//==========�̰��� �Լ� �߰�==========
	void Damage(float fDamage);		//cMonster�� �θ� �� �ִ� ���� ���� �Լ� / �ݵ�� override
	void MoveToPlayer();
	void MoveToSpone(D3DXVECTOR3 target);

	//========= collTrans �� ���� =======
	void collPosUpdate();
	//========= battle ���� ���� , basic �⺻ ��Ÿ� =====
	bool battleRange();
	bool basicRange();
	//========= ó�� ���� �������� �� �Լ� ====
	void spawn();
	// ��ų ������Ʈ �Լ�  
	void basicAttackUpdate();
	void breathUpdate();
	void earthUpate();
	void HeadAttUpate();
	// ���°� �ʱ�ȭ.
	void stateInit();
	// ���� ȸ�� ��Ű�� �ϴ� �Լ�
	void LookPos(D3DXVECTOR3 target);
	// �ִϸ��̼� ���� ���ִ� �Լ�
	void aniManager();
	//�÷��̾� ��ũ
	void SetPlayer(cPlayer* pPlayer) { m_pPlayer = pPlayer; }
	//���� ��ġ ��� ���ִ� �Լ� 

	// ���� ��ǥ ���� �ֺ��� ���� ��ǥ ����
	D3DXVECTOR3 makeRndVec(D3DXVECTOR3* pos, float fRadius);
	// ���׶� ���� �׸� ���� �ѹ��� �������. 
	void makeCircleQuad();
	
};

