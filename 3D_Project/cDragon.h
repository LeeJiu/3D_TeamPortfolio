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
   전투를 걸어야 전투가 시작됨.
   도망 치려면 전투 범위에서 벗어나야됨.
*/
enum BONE_NAME_INDEX
{
	BODY,HEAD,LHANAD,RHAND
};
enum SKILL_NAME //틱 클래스에서 쓸꺼. 
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
	cTrailRender* m_pTrailLEye;			//왼눈에붙일트레일
	cTrailRender* m_pTrailREye;			//오른눈에붙일트레일
	cTransform    m_LEyeTrans;			//왼눈 트레일트랜스
	cTransform    m_REyeTrans;			//오른눈 트레일트랜스

	int m_collCount;                    //포문 돌릴때 가져다 쓰셈
	cBoundBox m_bound[COLLISION];       //뼈에 들어갈 바운스
	cTransform* m_pBoneTrans[COLLISION]; //뼈에 들어갈 트렌스
	cTickFunc* m_tick[TICKMAX];

	D3DXVECTOR3 m_collPos[8];
	cTransform* m_pCollTrans[5];           //충돌체크에 쓸 트렌스

	stSphere m_spone;                     // 스폰에 쓰일 꺼. 
	stSphere m_basicAttack;               // 평타 사정 거리

	string m_nowAni;                      // 애니메이션
	
	int skillChance;                      // 스킬 발동확률
	
	int basicAttCoolTime;                 // 기본 공격 쿨타임. 

	bool isMove;                          // 움직이는중?
	bool isBattle;                        // 전투중?
	bool isBasicAttack;                   // 평타중?
	
	bool isBreath;                        // 브레스중?
	bool isEarthquake;                    // 지진중?
	bool isHeadAtt;                       // 머리 치기
	
	bool isNoneBasicAttack;               // 평타이외의 스킬.( 쓸지 안쓸지 모르겠음 )

	float skillCoolTime;                 // 스킬 쿨타임
	float tempCoolTime;                  // 스킬 쿨타이밍에 계산 할 거

	//========== 지진 관련 장판 보여줄때 쓸 변수
	bool isRenderEarthquake;            // 지진중?
	
	stSphere  m_circle[COLLCIRCLE];              // 원 장판
	D3DXVECTOR3      m_quad[COLLCIRCLE][6];      // 쿼드 장판 
	D3DXVECTOR3      m_quadPos[COLLCIRCLE];      // 쿼드 장판
	//========== 지진 , 브레스 렌더 해주는 함수 
	bool earthRender;
	bool breathRender;
    //========== 파티클 변수 추가. 
	cPartcleEmitter* m_pBreathParticle;

	cSkill_Meteo* m_Skill_Meteo[COLLCIRCLE];
	cSkill_Thunder* m_Skill_Thunder[COLLCIRCLE];
	// 기지모 그릴까?
	bool renderGizimo;
	// 죽었다. 
	bool isDie;
	float dieAniTime;
public:
	cDragon();
	~cDragon();
	
	void BaseObjectEnable();					//SetActive(true)하면 실행됨 -> 초기화 함수
	void BaseObjectUpdate(float timeDelta);		//BaseObject 가 Update 때 실행....
	void BaseObjectBoundBox();					//SetMesh() 하면 ComputeBoundBox() 실행되면서 실행됨
	void BaseObjectRender();
	
	void TrailSetting();
	
	//==========이곳에 함수 추가==========
	void Damage(float fDamage);		//cMonster로 부를 수 있는 순수 가상 함수 / 반드시 override
	void MoveToPlayer();
	void MoveToSpone(D3DXVECTOR3 target);

	//========= collTrans 값 갱신 =======
	void collPosUpdate();
	//========= battle 전투 범위 , basic 기본 사거리 =====
	bool battleRange();
	bool basicRange();
	//========= 처음 몬스터 만났을때 쓸 함수 ====
	void spawn();
	// 스킬 업데이트 함수  
	void basicAttackUpdate();
	void breathUpdate();
	void earthUpate();
	void HeadAttUpate();
	void dieUpdate(float timeDelta);

	// 상태값 초기화.
	void stateInit();
	// 몬스터 회전 시키게 하는 함수
	void LookPos(D3DXVECTOR3 target);
	// 애니메이션 관리 해주는 함수
	void aniManager();
	//플레이어 링크
	void SetPlayer(cPlayer* pPlayer) { m_pPlayer = pPlayer; }
	//장판 위치 계산 해주는 함수 

	// 현재 좌표 기준 주변에 랜덤 좌표 생성
	D3DXVECTOR3 makeRndVec(D3DXVECTOR3* pos, float fRadius);
	// 동그랑 장판 네모 장판 한번에 만들어줌. 
	void makeCircleQuad();
	//파티클 초기화
	void initParticle();
	

	cBoundBox GetBodyBound() { return m_bound[0]; }
};

