#include "stdafx.h"
/*
#pragma once
#include "cBaseObject.h"
#include "moveClass.h"


#define CONTROL_KEY 5

class cTerrain;
class cCamera;
class cInputHandler;
class cWeapon;
class cMonster;

class cBerserker : public cBaseObject
{
private:
std::vector<cMonster*>			 m_Vmon;
std::vector<cMonster*>::iterator m_VmonIter;

private:
cCamera*			m_camera;
cWeapon*			m_Weapon;

cBoundBox*          m_ATKBox;
cTransform*         m_ATKBoxTrans;

ACTOR_STATE			m_state;
std::string			m_Aniname;
std::map<int, bool> m_InputKeys;
bool				m_isMove;

//컴포넌트를 달아준다.
cInputHandler*		m_pInput;
moveClass*			m_pMove;
D3DXVECTOR3			m_mousePos;

//스킬
bool				m_isAttack;

int					m_atkCnt;		//평타단계 수
float				m_time;			//커맨드체크할 타이머
float				m_fadeOut;		//애니 끝나는시간

cMonster*			m_target;

//status
float				m_hp;
float				m_sp;
float				m_attackLength;//공격가능범위
int					m_damage;

float				m_testtime;		//로그찎는용 타이머

public:
cBerserker();
~cBerserker();

void BaseObjectEnable();
void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
void ATKBoxRender();
void WeaponRender();

void SetCamera(cCamera* camera) { m_camera = camera; }
void SetMonsters(std::vector<cMonster*>	vmon) { m_Vmon = vmon; }

cBoundBox* GetATKBox() { return m_ATKBox; }
cTransform* GetATKBoxTrans() { return m_ATKBoxTrans; }

private:
void Monster_pick();
void GetDamaged();

bool LengthCheck();
void Attac_first();
void Attac_second();
void Attac_third();
};

//==========================================

#include "stdafx.h"
#include "cBerserker.h"
#include "cTerrain.h"
#include "cCamera.h"
#include "cInputHandler.h"
#include "cWeapon.h"
#include "cMonster.h"

cBerserker::cBerserker()
{
}

cBerserker::~cBerserker()
{
SAFE_DELETE(m_pInput);
SAFE_DELETE(m_pMove);

SAFE_DELETE(m_Weapon);
SAFE_DELETE(m_ATKBox);
SAFE_DELETE(m_ATKBoxTrans);
}


void cBerserker::BaseObjectEnable()
{
m_pInput = new cInputHandler;

D3DXMATRIXA16 matScale;
D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
D3DXMATRIXA16 matCorrection = matScale;

cXMesh_Static* pSTF_Basic = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Weapon/TAX_Basic.X", &matCorrection);

//무기 관련
m_Weapon = new cWeapon;
m_Weapon->SetMesh(pSTF_Basic);
m_Weapon->SetActive(true);

pSkinned->AddBoneTransform("BN_Weapon_R", m_Weapon->pTransform);

//평타 박스
m_ATKBox = new cBoundBox;
m_ATKBox->Init(D3DXVECTOR3(-0.3f, -0.3f, -0.3f), D3DXVECTOR3(0.3f, 0.3f, 0.3f));

m_ATKBoxTrans = new cTransform;
m_ATKBox->SetBound(&m_ATKBoxTrans->GetWorldPosition(), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
pSkinned->AddBoneTransform("Bip01-L-Hand", m_ATKBoxTrans);


//캐릭터의 그려진 위치를 세팅
pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);
D3DXVECTOR3	minPos(-1, 0, -1);
D3DXVECTOR3	maxPos(1, 3, 1);

m_state = IDLE;
m_Aniname = MyUtil::SetAnimation(m_state);

m_pMove = new moveClass;
m_isMove = false;

m_target = NULL;
m_attackLength = 5;
m_damage = 100;
m_isAttack = false;

//무빙용으로 사용할 키값 세팅
std::pair<int, bool> key_W('W', false);		//W키 안눌림	상태
std::pair<int, bool> key_S('S', false);		//S키 안눌림  "
std::pair<int, bool> key_A('A', false);		//A키 안눌림  "
std::pair<int, bool> key_D('D', false);		//D키 안눌림  "
m_InputKeys.insert(key_W);
m_InputKeys.insert(key_S);
m_InputKeys.insert(key_A);
m_InputKeys.insert(key_D);


m_pMove->init(pTransform, pTerrain, m_camera, NULL);

m_atkCnt = 1;
m_time = 0;
m_testtime = 0;
}

void cBerserker::BaseObjectUpdate(float timeDelta)
{

cCommand* command = m_pInput->HandleInput();
if (command != NULL)
{
command->Execute();
}

//애니메이션셋
m_fadeOut = pSkinned->GetTime();

if (!m_isAttack && m_isMove && (KEY_MGR->IsOnceDown('W') || KEY_MGR->IsOnceDown('D')
|| KEY_MGR->IsOnceDown('A')))
{
m_state = WALK;
m_Aniname = MyUtil::SetAnimation(m_state);
this->pSkinned->Play(m_Aniname, 0.3);
}


if (!m_isAttack && m_isMove && KEY_MGR->IsOnceDown('S'))
{
m_state = WALK_BACK;
m_Aniname = MyUtil::SetAnimation(m_state);
this->pSkinned->Play(m_Aniname, 0.3);
}

if ((!m_isMove && (KEY_MGR->IsOnceUp('W') || KEY_MGR->IsOnceUp('S')
|| KEY_MGR->IsOnceUp('Q') || KEY_MGR->IsOnceUp('E')
|| KEY_MGR->IsOnceUp('A') || KEY_MGR->IsOnceUp('D'))))
{
m_state = IDLE;
m_Aniname = MyUtil::SetAnimation(m_state);
this->pSkinned->Play(m_Aniname, 0.3);
}

m_time += timeDelta;
m_testtime += timeDelta;

//
//=================평타=================
//
if (LengthCheck() && !m_isAttack && KEY_MGR->IsOnceDown('1'))
{
m_isAttack = true;
m_time = 0;
switch (m_atkCnt)
{
case 1 :
m_state = ATK_01;
Attac_first();
m_atkCnt++;
break;

case 2:
m_state = ATK_02;
Attac_second();
m_atkCnt++;
break;
case 3:
pSkinned->ChangeBoneTransform("BN_Weapon_R", "BN_Weapon_L");// 막타를 칠때 BN_Weapon_L로
m_state = ATK_03;
Attac_third();
m_atkCnt = 1;
break;
}
m_Aniname = MyUtil::SetAnimation(m_state);
this->pSkinned->PlayOneShotAFTERIDLE(m_Aniname, 0.3, 0.15);
}

//글쿨 막타만 1.5초
if (m_time > 1)
{
if (m_atkCnt != 1)
{
m_isAttack = false;
m_state = IDLE;
}
else if (m_atkCnt == 1)
{
if (m_time > 1.5)
{
m_isAttack = false;
m_state = IDLE;
}
}
}

if (pSkinned->GetTime() > 0.7)
{
if (pSkinned->IsCurrentBone("BN_Weapon_L"))
pSkinned->ChangeBoneTransform("BN_Weapon_L", "BN_Weapon_R");
}

//평타 초기화시간
if (m_time > 5)
m_atkCnt = 1;

//test용 로그 출려꾸
if (m_testtime > 1)
{
m_testtime = 0;
}

//
//===============무브==============================
//

if (KEY_MGR->IsStayDown('W'))
{
m_InputKeys.find('W')->second = true;
}
else m_InputKeys.find('W')->second = false;


if (KEY_MGR->IsStayDown('S'))
{
m_InputKeys.find('S')->second = true;
}
else m_InputKeys.find('S')->second = false;

if (KEY_MGR->IsStayDown('A'))
{
m_InputKeys.find('A')->second = true;
}
else m_InputKeys.find('A')->second = false;

if (KEY_MGR->IsStayDown('D'))
{
m_InputKeys.find('D')->second = true;
}
else m_InputKeys.find('D')->second = false;


m_pMove->update(timeDelta, NULL, NULL, NULL, m_InputKeys);
m_isMove = m_pMove->GetIsMove();

Monster_pick();
}


void cBerserker::ATKBoxRender()
{
m_ATKBox->RenderGizmo(m_ATKBoxTrans);
}

void cBerserker::WeaponRender()
{

this->m_Weapon->Render();
this->m_Weapon->pTransform->RenderGimozo();


}

void cBerserker::Monster_pick()
{
if (KEY_MGR->IsOnceDown(VK_LBUTTON))
{
Ray ray;
POINT ptMousePos = GetMousePos();
D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
this->m_camera->ComputeRay(&ray, &screenPos);


int size = m_Vmon.size();
for (int i = 0; i < size; i++)
{
if (PHYSICS_MGR->IsRayHitBound(&ray, &m_Vmon[i]->BoundBox, m_Vmon[i]->pTransform, NULL, NULL))
{
LOG_MGR->AddLog("타겟팅됨");
this->m_target = m_Vmon[i];
}
else this->m_target = NULL;
}
}
}

void cBerserker::GetDamaged()
{
}

bool cBerserker::LengthCheck()
{
if (m_target!=NULL)
{
D3DXVECTOR3 vDistance = this->pTransform->GetWorldPosition() - m_target->pTransform->GetWorldPosition();
float distance;
distance = D3DXVec3Length(&vDistance);

if (distance < m_attackLength)
return true;
else return false;
}
else return false;
}

void cBerserker::Attac_first()
{
if (m_target)
{
this->pTransform->LookDirection(m_target->pTransform->GetWorldPosition(), 10 * ONE_RAD);
}

int damage = m_damage * 1;
damage = RandomIntRange(damage - 10, damage + 10);

LOG_MGR->AddLog("%d데미지 줌", damage);
m_target->Damage(damage);
}

void cBerserker::Attac_second()
{
if (m_target)
{
this->pTransform->LookDirection(m_target->pTransform->GetWorldPosition(), 10 * ONE_RAD);
}

int damage = m_damage * 2;
damage = RandomIntRange(damage - 10, damage + 10);

LOG_MGR->AddLog("%d데미지 줌", damage);
m_target->Damage(damage);
}

void cBerserker::Attac_third()
{
if (m_target)
{
this->pTransform->LookDirection(m_target->pTransform->GetWorldPosition(), 10 * ONE_RAD);
}

int damage = m_damage * 3;
damage = RandomIntRange(damage - 10, damage + 10);

LOG_MGR->AddLog("%d데미지 줌", damage);
m_target->Damage(damage);
}


================================1차 수정========================
#pragma once
#include "cPlayer.h"
#include "moveClass.h"

#define CONTROL_KEY 5

class cBerserker : public cPlayer
{
private:
ACTOR_STATE			m_state;
std::string			m_strName;
std::map<int, bool> m_InputKeys;
bool				m_isMove;

//컴포넌트를 달아준다.
moveClass*			m_pMove;
D3DXVECTOR3			m_mousePos;

//스킬
bool				m_isAttack;

int					m_atkCnt;		//평타단계 수
float				m_time;			//커맨드체크할 타이머
float				m_fadeOut;		//애니 끝나는시간


//status
float				m_fHP;
float				m_sp;
float				m_attackLength;//공격가능범위
int					m_damage;

float				m_testtime;		//로그찎는용 타이머

public:
cBerserker();
~cBerserker();

void BaseObjectEnable();
void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
void BaseObjectRender();

//void SetMonsters(std::vector<cMonster*>	vmon) { m_Vmon = vmon; }

private:
void Damage(float damage);

bool LengthCheck();
void Attack01();
void Attack02();
void Attack03();
};

==================================================
#include "stdafx.h"
#include "cPlayer.h"
#include "cBerserker.h"
#include "cWeapon.h"

cBerserker::cBerserker()
{
}

cBerserker::~cBerserker()
{
SAFE_DELETE(m_pMove);
SAFE_DELETE(m_Weapon);
}


void cBerserker::BaseObjectEnable()
{
D3DXMATRIXA16 matScale;
D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
D3DXMATRIXA16 matCorrection = matScale;

cXMesh_Static* pSTF_Basic = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Weapon/TAX_Basic.X", &matCorrection);

//무기 관련
m_Weapon = new cWeapon;
m_Weapon->SetMesh(pSTF_Basic);
m_Weapon->SetActive(true);

//평타 박스
m_Weapon->BoundBox.SetBound(&m_Weapon->pTransform->GetWorldPosition(), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
pSkinned->AddBoneTransform("BN_Weapon_R", m_Weapon->pTransform);




//캐릭터의 그려진 위치를 세팅
pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);
D3DXVECTOR3	minPos(-1, 0, -1);
D3DXVECTOR3	maxPos(1, 3, 1);

m_state = IDLE;
m_strName = MyUtil::SetAnimation(m_state);

m_pMove = new moveClass;
m_isMove = false;

//m_target = NULL;
m_fHP = 1000;
m_attackLength = 5;
m_damage = 100;
m_isAttack = false;

//무빙용으로 사용할 키값 세팅
std::pair<int, bool> key_W('W', false);		//W키 안눌림	상태
std::pair<int, bool> key_S('S', false);		//S키 안눌림  "
std::pair<int, bool> key_A('A', false);		//A키 안눌림  "
std::pair<int, bool> key_D('D', false);		//D키 안눌림  "
m_InputKeys.insert(key_W);
m_InputKeys.insert(key_S);
m_InputKeys.insert(key_A);
m_InputKeys.insert(key_D);


m_pMove->init(pTransform, pTerrain, m_camera, NULL);

m_atkCnt = 1;
m_time = 0;
m_testtime = 0;
}

void cBerserker::BaseObjectUpdate(float timeDelta)
{
//애니메이션셋
if (!m_isAttack && m_isMove && (KEY_MGR->IsOnceDown('W') || KEY_MGR->IsOnceDown('D')
|| KEY_MGR->IsOnceDown('A')))
{
m_state = WALK;
m_strName = MyUtil::SetAnimation(m_state);
this->pSkinned->Play(m_strName, 0.3);
}


if (!m_isAttack && m_isMove && KEY_MGR->IsOnceDown('S'))
{
m_state = WALK_BACK;
m_strName = MyUtil::SetAnimation(m_state);
this->pSkinned->Play(m_strName, 0.3);
}

if ((!m_isMove && (KEY_MGR->IsOnceUp('W') || KEY_MGR->IsOnceUp('S')
|| KEY_MGR->IsOnceUp('Q') || KEY_MGR->IsOnceUp('E')
|| KEY_MGR->IsOnceUp('A') || KEY_MGR->IsOnceUp('D'))))
{
m_state = IDLE;
m_strName = MyUtil::SetAnimation(m_state);
this->pSkinned->Play(m_strName, 0.3);
}

m_time += timeDelta;
m_testtime += timeDelta;

//
//=================평타=================
//
if (LengthCheck() && !m_isAttack && KEY_MGR->IsOnceDown('1'))
{
m_isAttack = true;
m_time = 0;
switch (m_atkCnt)
{
case 1 :
m_state = ATK_01;
Attack01();
m_atkCnt++;
break;

case 2:
m_state = ATK_02;
Attack02();
m_atkCnt++;
break;
case 3:
pSkinned->ChangeBoneTransform("BN_Weapon_R", "BN_Weapon_L");// 막타를 칠때 BN_Weapon_L로
m_state = ATK_03;
Attack03();
m_atkCnt = 1;
break;
}
m_strName = MyUtil::SetAnimation(m_state);
this->pSkinned->PlayOneShotAFTERIDLE(m_strName, 0.3, 0.15);
}

//글쿨 막타만 1.5초
if (m_time > 1)
{
if (m_atkCnt != 1)
{
m_isAttack = false;
m_state = IDLE;
}
else if (m_atkCnt == 1)
{
if (m_time > 1.5)
{
m_isAttack = false;
m_state = IDLE;
}
}
}

if (pSkinned->GetTime() > 0.7)
{
if (pSkinned->IsCurrentBone("BN_Weapon_L"))
pSkinned->ChangeBoneTransform("BN_Weapon_L", "BN_Weapon_R");
}

//평타 초기화시간
if (m_time > 5)
m_atkCnt = 1;

//test용 로그 출려꾸
if (m_testtime > 1)
{
m_testtime = 0;
}

//
//===============무브==============================
//

if (KEY_MGR->IsStayDown('W'))
{
m_InputKeys.find('W')->second = true;
}
else m_InputKeys.find('W')->second = false;


if (KEY_MGR->IsStayDown('S'))
{
m_InputKeys.find('S')->second = true;
}
else m_InputKeys.find('S')->second = false;

if (KEY_MGR->IsStayDown('A'))
{
m_InputKeys.find('A')->second = true;
}
else m_InputKeys.find('A')->second = false;

if (KEY_MGR->IsStayDown('D'))
{
m_InputKeys.find('D')->second = true;
}
else m_InputKeys.find('D')->second = false;


m_pMove->update(timeDelta, NULL, NULL, NULL, m_InputKeys);
m_isMove = m_pMove->GetIsMove();

Monster_pick();
}

void cBerserker::BaseObjectRender()
{
if (m_Weapon)
{
m_Weapon->BoundBox.RenderGizmo(m_Weapon->pTransform);

m_Weapon->Render();
m_Weapon->pTransform->RenderGimozo();
}

this->pSkinned->Render(this->pTransform);
}


void cBerserker::Damage(float damage)
{
m_fHP -= damage;
if (m_fHP <= FEPSILON)
{
m_fHP = 0.0f;
m_state = DEAD;
m_strName = MyUtil::SetAnimation(m_state);
pSkinned->PlayOneShotAfterHold(m_strName);
return;
}

if (m_state != DMG)
{
m_state = DMG;
m_strName = MyUtil::SetAnimation(m_state);
pSkinned->PlayOneShotAfterOther(m_strName, "IDLE", 0.3f);
m_state = IDLE;
}
}

bool cBerserker::LengthCheck()
{
//if (m_target!=NULL)
//{
//	D3DXVECTOR3 vDistance = this->pTransform->GetWorldPosition() - m_target->pTransform->GetWorldPosition();
//	float distance;
//	distance = D3DXVec3Length(&vDistance);
//
//	if (distance < m_attackLength)
//		return true;
//	else return false;
//}
//else return false;
return false;
}

void cBerserker::Attack01()
{
//if (m_target)
//{
//	this->pTransform->LookDirection(m_target->pTransform->GetWorldPosition(), 10 * ONE_RAD);
//}
//
//int damage = m_damage * 1;
//damage = RandomIntRange(damage - 10, damage + 10);
//
//LOG_MGR->AddLog("%d데미지 줌", damage);
//m_target->Damage(damage);
}

void cBerserker::Attack02()
{
//if (m_target)
//{
//	this->pTransform->LookDirection(m_target->pTransform->GetWorldPosition(), 10 * ONE_RAD);
//}
//
//int damage = m_damage * 2;
//damage = RandomIntRange(damage - 10, damage + 10);
//
//LOG_MGR->AddLog("%d데미지 줌", damage);
//m_target->Damage(damage);
}

void cBerserker::Attack03()
{
//if (m_target)
//{
//	this->pTransform->LookDirection(m_target->pTransform->GetWorldPosition(), 10 * ONE_RAD);
//}
//
//int damage = m_damage * 3;
//damage = RandomIntRange(damage - 10, damage + 10);
//
//LOG_MGR->AddLog("%d데미지 줌", damage);
//m_target->Damage(damage);
}

*/