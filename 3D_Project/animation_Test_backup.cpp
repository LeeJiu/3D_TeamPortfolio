#include "stdafx.h"

/*
.h


#pragma once
#include "cScene.h"

class cBaseObject;
class cCamera;
class cTerrain;
class cSkinnedAnimation;

class animation_Test : public cScene
{
private:

cSkinnedAnimation*		pSkinned1;
cTransform*				pSkinnedTrans;
cTransform*				pTransForCamera;		//ī�޶��

// ���� ��ŷ�� ����.
Ray						cRay; //�ɸ��Ϳ� �� ����.
bool                    objectHit;

// �����ӿ� �Ẽ��.
D3DXVECTOR3		m_currentPos;// �� �ɸ����� ��ġ
D3DXVECTOR3		m_prePos;// ���� ������ ��ġ
D3DXVECTOR3		m_lastPos;// ���� ���� y���� ��ȯ ��ų�� ����.
D3DXVECTOR3		m_mousePos;// Ŭ�������� ��ġ.

bool isMove;
bool isObject;
bool isTerrain;
bool isClick;


bool isCharView, isAltView;		//ī�޶��

int current_State;
std::string current_Ani;


std::vector<cLight*>	lights;

cTerrain*		m_pTerrain;
D3DXVECTOR3		m_hitPos;


D3DXVECTOR3		m_hitDir;
bool			m_bMove;

cBaseObject*	m_Land;			//�ø��� ������Ʈ

D3DXMATRIXA16 temp;


public:
animation_Test(void);
~animation_Test(void);


virtual HRESULT Scene_Init();

virtual void Scene_Release();

virtual void Scene_Update(float timeDelta);

virtual void Scene_Render1();

virtual void Scene_RenderSprite();


};


=========================

.cpp

#include "StdAfx.h"
#include "animation_Test.h"
#include "cLight_Direction.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTerrain.h"
#include "cSkinnedAnimation.h"
#include "cLight_Point.h"

animation_Test::animation_Test(void)
{
}

animation_Test::~animation_Test(void)
{
}

HRESULT animation_Test::Scene_Init()
{
m_pTerrain = new cTerrain;
m_pTerrain->Init(
"../Resources/Textures/MyHeight512.bmp",
"../Resources/Textures/terrain1.jpg",
"../Resources/Textures/terrain2.png",
"../Resources/Textures/terrain3.png",
"../Resources/Textures/terrain4.png",
"../Resources/Textures/Splat.png",
1.0f,
100.0f,
3,
100);

m_hitPos = D3DXVECTOR3(0, 0, 0);

m_bMove = false;

D3DXMATRIXA16 matScale;
D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
D3DXMATRIXA16 matRotate;
D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
D3DXMATRIXA16 matCorrection = matScale * matRotate;

cXMesh_Skinned* pSkinned = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Elf/Elf_Master.X", &matCorrection);


//+++�ִϸ��̼� üũ ����+++++

current_State = 0;             //���� ���� ENUM �ʱ�ȭ
current_Ani = "STF_IDLE";      //���� ���� �ѹ��� ���ڿ��� �ٲ㼭 �ǽð����� �ִϰ� �ٲ�



//=================== ����ƽ ���� �׸�.
D3DXMatrixScaling(&matScale, 1, 1, 1);

matCorrection = matScale * matRotate;
m_Land = new cBaseObject;
m_Land->SetMesh(RESOURCE_STATICXMESH->GetResource(
"../Resources/Meshes/TestMesh/boundMesh.X", &matCorrection));
m_Land->SetActive(true);

//m_Land->pTransform->SetWorldPosition(0, this->m_pTerrain->GetHeight(0, 0) - 18, 0);
m_Land->pTransform->SetWorldPosition(0, 0, 0);


//������ �ε��� SkinnedMesh �ν��Ͻ��� �����.
this->pSkinned1 = new cSkinnedAnimation();
this->pSkinned1->Init(pSkinned);

//ĳ���Ͱ� �׷��� ��ġ Ʈ������
this->pSkinnedTrans = new cTransform();
pSkinnedTrans->SetWorldPosition(0, m_pTerrain->GetHeight(0, 0), 0);

this->pTransForCamera = new cTransform();

this->pSkinnedTrans->AddChild(this->pMainCamera);
this->pMainCamera->SetLocalPosition(0, 5, -10);
isCharView = true;
isAltView = false;

//����Ʈ Ǫ��
cLight_Direction* pLight1 = new cLight_Direction();
pLight1->Color = D3DXCOLOR(1, 1, 1, 1);
pLight1->Intensity = 1.0f;
pLight1->pTransform->SetRotateWorld(45 * ONE_RAD, 45 * ONE_RAD, 45 * ONE_RAD);

cLight_Point* pLight2 = new cLight_Point();
pLight2->Color = D3DXCOLOR(1, 1, 1, 0);
pLight2->minRange = 5.0f;
pLight2->maxRange = 10.0f;
pLight2->distancePow = 10.0f;

cLight_Point* pLight3 = new cLight_Point();
pLight3->Color = D3DXCOLOR(1, 1, 1, 0);
pLight3->minRange = 5.0f;
pLight3->maxRange = 10.0f;
pLight3->distancePow = 10.0f;
pLight3->pTransform->SetWorldPosition(3, 3, 0);
pLight3->Intensity = 0.5f;

this->lights.push_back(pLight1);
this->lights.push_back(pLight2);
this->lights.push_back(pLight3);

isMove = false;
//================���� �߰�. �Ʒ� ���� �ٲ��� ���� .
cRay.direction = D3DXVECTOR3(0, -1, 0);
cRay.origin = pSkinnedTrans->GetWorldPosition();
//=============== ���� �ʱ�ȭ ��.
pMainCamera->SetWorldPosition(2, 5, 2);
isClick = false;



return S_OK;
}

void animation_Test::Scene_Release()
{
m_pTerrain->Release();
SAFE_DELETE(m_pTerrain);

SAFE_DELETE(this->pSkinnedTrans);
SAFE_DELETE(this->pTransForCamera);

this->pSkinned1->Release();
SAFE_DELETE(this->pSkinned1);
}

void animation_Test::Scene_Update(float timeDelta)
{
// ���� ������Ʈ
m_currentPos = pSkinnedTrans->GetWorldPosition(); // ���� ��ġ.
//cRay.direction = D3DXVECTOR3(0, -1, 0);
cRay.origin.y = pSkinnedTrans->GetWorldPosition().y + 5; // �Ӹ����� ���Ͽ���

this->pTransForCamera->SetWorldPosition(this->pSkinnedTrans->GetWorldPosition());

if (isCharView && KEY_MGR->IsStayDown(VK_MENU))
{
isAltView = true;
isCharView = false;
this->pMainCamera->ReleaseParent();
this->pTransForCamera->AddChild(this->pMainCamera);
}
if (isAltView && KEY_MGR->IsOnceUp(VK_MENU))
{
this->pMainCamera->Reset();
this->pTransForCamera->Reset();
this->pTransForCamera->SetWorldMatrix(this->pSkinnedTrans->GetFinalMatrix());

this->pSkinnedTrans->AddChild(this->pMainCamera);
this->pMainCamera->SetLocalPosition(0, 5, -10);
isCharView = true;
isAltView = false;
}


if (isCharView)
{
pMainCamera->DefaultControl3(timeDelta, this->pSkinnedTrans);
}
else if (isAltView)
{
pMainCamera->DefaultControl3(timeDelta, this->pTransForCamera);
}

//+=======================================�ִϸ��̼� üũ ���� ==============================+


if (KEY_MGR->IsOnceDown(VK_UP)) // UPŰ�� ���� �ִϸ� �� �� �ִ�
{
current_State++;
if (END == current_State) current_State = 0;
}

switch (current_State)
{
case ROBBY_IDLE:  current_Ani = "STF_IDLE";
break;
case PET_IDLE:  current_Ani = "PET_IDLE";
break;
case PET_RUN:  current_Ani = "PET_RUN";
break;
case SIT_SRT:  current_Ani = "SIT_SRT";
break;
case SIT_LOOP:  current_Ani = "SIT_LOOP";
break;
case SIT_UP:  current_Ani = "SIT_UP";
break;
case LOOP:  current_Ani = "LOOP";
break;
case HELLO:  current_Ani = "HELLO";
break;
case CRY:  current_Ani = "CRY";
break;
case DANCE:  current_Ani = "DANCE";
break;
case STF_DMG:  current_Ani = "STF_DMG";
break;

case STF_DIE:  current_Ani = "STF_DIE";
break;

case STF_DEAD:  current_Ani = "STF_DEAD";
break;
case STF_DOWN:  current_Ani = "STF_DOWN";
break;
case STF_STUN:  current_Ani = "STF_STUN";
break;
case STF_WAKEUP:  current_Ani = "STF_WAKEUP";
break;
case STF_IDLE:  current_Ani = "STF_IDLE";
break;
case STF_WAIT:  current_Ani = "STF_WAIT";
break;
case STF_WALK:  current_Ani = "STF_WALK";
break;
case STF_WALK_BACK:  current_Ani = "STF_WALK_BACK";
break;
case STF_RUN:  current_Ani = "STF_RUN";
break;
case RUN_R:  current_Ani = "RUN_R";
break;
case RUN_L:  current_Ani = "RUN_L";
break;
case STF_STOP:  current_Ani = "STF_STOP";
break;
case STF_PASSOUT:  current_Ani = "STF_PASSOUT";
break;
case STF_JUMP:  current_Ani = "STF_JUMP";
break;
case STF_WEAPON:  current_Ani = "STF_WEAPON";
break;
case STF_UNWEAPON:  current_Ani = "STF_UNWEAPON";
break;
case STF_ATK1:  current_Ani = "STF_ATK1";
break;
case STF_ATK2:  current_Ani = "STF_ATK2";
break;
case STF_BUFF:  current_Ani = "STF_BUFF";
break;
case STF_TYFUNG:  current_Ani = "STF_TYFUNG";
break;
case STF_THUNDER:  current_Ani = "STF_THUNDER";
break;
case STF_FROZEN:  current_Ani = "STF_FROZEN";
break;
case STF_FIRE:  current_Ani = "STF_FIRE";
break;
case STF_SPLASH:  current_Ani = "STF_SPLASH";
break;
case STF_BUMB:  current_Ani = "STF_BUMB";
break;
case STF_DRAIN:  current_Ani = "STF_DRAIN";
break;
case STF_SWING:  current_Ani = "STF_SWING";
break;
case STF_STORM:  current_Ani = "STF_STORM";
break;
case STF_MAGIC_SHOT:  current_Ani = "STF_MAGIC_SHOT";
break;
case STF_BLINK:  current_Ani = "STF_BLINK";
break;
default: current_Ani = "STF_IDLE";
break;
}


pSkinned1->Play(current_Ani,0.3f);

//+===========================================================================================+


if (KEY_MGR->IsStayDown('W'))
{
isMove = true;
cRay.origin += pSkinnedTrans->GetForward()*0.2f;
}
if (KEY_MGR->IsStayDown('S'))
{
isMove = true;
cRay.origin -= pSkinnedTrans->GetForward()*0.2f;

}
if (KEY_MGR->IsStayDown('Q'))
{
isMove = true;
cRay.origin += pSkinnedTrans->GetRight()*0.2f;

}
if (KEY_MGR->IsStayDown('E'))
{
isMove = true;
cRay.origin -= pSkinnedTrans->GetRight()*0.2f;
}
if (KEY_MGR->IsStayDown('A'))
{
pSkinnedTrans->RotateSelf(0, -2 * ONE_RAD, 0);
}

if (KEY_MGR->IsStayDown('D'))
{
pSkinnedTrans->RotateSelf(0, 2 * ONE_RAD, 0);
}

//=========================
if (KEY_MGR->IsOnceDown(VK_LBUTTON))
{
Ray ray;
POINT ptMousePos = GetMousePos();
D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
this->pMainCamera->ComputeRay(&ray, &screenPos);

this->m_pTerrain->IsIntersectRay(&m_mousePos, &ray);
isClick = true;

}

if (isClick == true)
{
D3DXVECTOR3 dir = m_mousePos - cRay.origin;	// ���� �� mousePos�� ���� �̵�.
dir.y = 0;


if (D3DXVec3Length(&dir) > 0.5f)
{
isMove = true;
D3DXVec3Normalize(&dir, &dir);
D3DXVECTOR3 lerp = pSkinnedTrans->GetForward();
D3DXVec3Lerp(&lerp, &lerp, &dir, 0.2);
pSkinnedTrans->LookDirection(lerp, D3DXVECTOR3(0, 1, 0));

cRay.origin += dir*0.2f;
}
else
{
isMove = false;
isClick = false;

LOG_MGR->AddLog("Tx: %.2f, Ty : %.2f, Tz : %.2f",
cRay.origin.x,
cRay.origin.y,
cRay.origin.z);
}
}




// ������Ʈ�� �浹�ߴٸ�. ( �ɷ� ������ ������ ���� �־���� �Ѵ�. )

//m_lastPos = this->pSkinnedTrans->GetWorldPosition();
//m_lastPos.y = -1000;
// ���Ŀ� �Ÿ� ���� �̿��ؼ� 2,3��° ���� ���� �ɷ� ������.
if ((
PHYSICS_MGR->IsRayHitStaticMeshObject(
&this->cRay,
this->m_Land,
this->m_Land->pTransform,
&this->m_prePos,
NULL)) == true)
{
m_lastPos = m_prePos; // ������Ʈ �浹 ���� �� Ŭ ��� Last ���� �����Ѵ�.
}
else
{
m_lastPos.y = pSkinnedTrans->GetWorldPosition().y - 10;
}

// �ͷ��ΰ� �浹 �ߴٸ�.
if (this->m_pTerrain->IsIntersectRay(&m_prePos, &cRay) == true)
{
if (m_lastPos.y > m_prePos.y)
{
m_prePos = m_lastPos;
}
}



//=================================== �ɸ��͸� ���������� �����̰� �ϴ� �κ�
if (fabs(m_prePos.y - m_currentPos.y) < 0.5f && isMove == true) // ���ڴ� �Ѿ �� �ִ� ����. ( �Ʒ����� ���� ����. )
{
this->pSkinnedTrans->SetWorldPosition(m_prePos);
m_currentPos = m_prePos; // ��ǥ ����
}
// ���̶� �ɸ��� �Ÿ��� �־����� ���̰� ���̻� �Ѿ�� ���ϰ� �����.
float rayCheckDis = D3DXVec3Length(&(cRay.origin - pSkinnedTrans->GetWorldPosition()));
if (rayCheckDis > 0.25f) // ��� ���� �ӷ� ���� ���� ���� ��.
{
cRay.origin = pSkinnedTrans->GetWorldPosition();
cRay.origin.y = pSkinnedTrans->GetWorldPosition().y + 5; // �Ӹ����� ���Ͽ���

}

isMove = false;
//=================================== �ɸ��͸� ���������� �����̰� �ϴ� �κ�  ��.

this->pSkinned1->Update(timeDelta);





//if (KEY_MGR->IsStayDown(VK_LCONTROL))
//{

//	if (KEY_MGR->IsOnceDown('1'))
//		this->pSkinned1->Play("Idle_01", 0.3f);

//	if (KEY_MGR->IsOnceDown('2'))
//		this->pSkinned1->Play("Idle_02", 0.3f);

//	if (KEY_MGR->IsOnceDown('3'))
//		this->pSkinned1->PlayOneShot("Walk", 0.3f);

//}



//if (m_bMove == true)
//{
//	//�Ÿ��� ���Ѵ�.
//	D3DXVECTOR3 dirToTarget = this->m_hitPos - this->pSkinnedTrans->GetWorldPosition();
//	float dist = D3DXVec3Length(&dirToTarget);

//	//��Ʈ ����Ʈ�� ��ġ�ϰ� �Ǹ� lookdirection�� ���� �ʴ´�.
//	//�ڽ��� �ڽ��� ��ġ�� ���� �Ǹ� ���� �����������.
//	if (dist <= 0.001)
//	{
//		m_bMove = false;
//		this->pSkinned1->Play("Idle_01", 0.3f);
//		return;
//	}

//	D3DXVec3Normalize(&dirToTarget, &dirToTarget);

//	//������ ���Ѵ�.
//	this->pSkinnedTrans->LookDirection(dirToTarget);

//	//�̵���
//	float deltaMove = 5.0f * timeDelta;
//	float t = Clamp01(deltaMove / dist);

//	//���� ��ġ���� ��Ʈ ����Ʈ��
//	D3DXVECTOR3 pos = VecLerp(this->pSkinnedTrans->GetWorldPosition(), this->m_hitPos, t);

//	//���� ��´�. / �ͷ����� ����
//	pos.y = this->m_pTerrain->GetHeight(pos.x, pos.z);

//	this->pSkinnedTrans->SetWorldPosition(pos);
//}

if (KEY_MGR->IsOnceDown(VK_SPACE))
{
LOG_MGR->AddLog("Tx: %.2f, Ty : %.2f, Tz : %.2f",
this->pSkinnedTrans->GetWorldPosition().x,
this->pSkinnedTrans->GetWorldPosition().y,
this->pSkinnedTrans->GetWorldPosition().z);

LOG_MGR->AddLog("Rx: %.2f, Ry : %.2f, Rz : %.2f",
m_prePos.x,
m_prePos.y,
m_prePos.z);

}


}

void animation_Test::Scene_Render1()
{
m_pTerrain->Render(this->pMainCamera, dynamic_cast<cLight_Direction*>(lights[0]));

//����Ǵ� LightMatrix
D3DXMATRIXA16 matLights[10];
for (int i = 0; i < this->lights.size(); i++)
matLights[i] = this->lights[i]->GetLightMatrix();

//���̴��� ������ ����
cXMesh_Skinned::sSkinnedMeshEffect->SetMatrixArray("matLights", matLights, 10);
cXMesh_Skinned::sSkinnedMeshEffect->SetInt("LightNum", this->lights.size());

//SkinnedEffect CameraMatrix ����
//D3DXMATRIXA16 matViewProjection = pCamera->GetViewProjectionMatrix();
//m_pSkinnedEffect->SetMatrix( "matViewProjection", &matViewProjection );

cXMesh_Skinned::SetCamera(this->pMainCamera);
this->pSkinned1->Render(pSkinnedTrans);

//������ �ִ� Animation ������غ���..
RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Queen/Queen.X")->ShowAnimationName(0, 100);

//Hit ��ġ�� ��
GIZMO_MGR->WireSphere(this->m_mousePos, 0.5f, 0xffff0000);

//���̴��� ������ ����
cXMesh_Static::SetCamera(this->pMainCamera);
cXMesh_Static::SetTechniqueName("Base");		//������� ���� �׸����� ReciveShadow �� Technique ����
cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);

m_Land->Render();
//========== ���� ������
GIZMO_MGR->Line(this->cRay.origin, this->cRay.origin + this->cRay.direction * 100, 0xffffff00);

}


void animation_Test::Scene_RenderSprite()
{
}





*/