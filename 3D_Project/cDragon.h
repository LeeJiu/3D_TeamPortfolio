#pragma once
#include "cMonster.h"
#include "cBoundBox.h"
#include "cTickFunc.h"
#include "cPartcleEmitter.h"
#include  "cSkill_Meteo.h"
#include  "cSkill_Thunder.h"

#define COLLISION 4
#define TICKMAX 5
#define COLLCIRCLE 4
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

class cTrailRender;

class cDragon : public cMonster
{
private:
	cTrailRender* m_pTrailLEye;			//�޴�������Ʈ����
	cTrailRender* m_pTrailREye;			//������������Ʈ����
	cTransform    m_LEyeTrans;			//�޴� Ʈ����Ʈ����
	cTransform    m_REyeTrans;			//������ Ʈ����Ʈ����

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
	
	stSphere  m_circle[COLLCIRCLE];              // �� ����
	D3DXVECTOR3      m_quad[COLLCIRCLE][6];      // ���� ���� 
	D3DXVECTOR3      m_quadPos[COLLCIRCLE];      // ���� ����
	//========== ���� , �극�� ���� ���ִ� �Լ� 
	bool earthRender;
	bool breathRender;
    //========== ��ƼŬ ���� �߰�. 
	cPartcleEmitter* m_pBreathParticle;

	cSkill_Meteo* m_Skill_Meteo[COLLCIRCLE];
	cSkill_Thunder* m_Skill_Thunder[COLLCIRCLE];
	// ������ �׸���?
	bool renderGizimo;
	// �׾���. 
	bool isDie;
	float dieAniTime;
public:
	cDragon();
	~cDragon();
	
	void BaseObjectEnable();					//SetActive(true)�ϸ� ����� -> �ʱ�ȭ �Լ�
	void BaseObjectUpdate(float timeDelta);		//BaseObject �� Update �� ����....
	void BaseObjectBoundBox();					//SetMesh() �ϸ� ComputeBoundBox() ����Ǹ鼭 �����
	void BaseObjectRender();
	
	void TrailSetting();
	
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
	void dieUpdate(float timeDelta);

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
	//��ƼŬ �ʱ�ȭ
	void initParticle();
	

	cBoundBox GetBodyBound() { return m_bound[0]; }
};

