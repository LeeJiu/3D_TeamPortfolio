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
#include "cPlayer.h"
#include "cMage.h"

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

	D3DXMatrixScaling(&matScale, 1, 1, 1);
	matCorrection = matScale * matRotate;
	m_Land = new cBaseObject;
	m_Land->SetMesh(RESOURCE_STATICXMESH->GetResource(
		"../Resources/Meshes/TestMesh/boundMesh.X", &matCorrection));
	m_Land->SetActive(true);

	//m_Land->pTransform->SetWorldPosition(0, this->m_pTerrain->GetHeight(0, 0) - 18, 0);
	m_Land->pTransform->SetWorldPosition(0, 0, 0);


	//������ �ε��� SkinnedMesh �ν��Ͻ��� �����.
	this->pPlayer = new cPlayer;
	this->pPlayer->SetMesh(pSkinned);
	this->pPlayer->SetTerrain(m_pTerrain);
	this->pPlayer->SetActive(true);
	this->current_State = IDLE;

	//ĳ���Ͱ� �׷��� ��ġ Ʈ������
	this->pPlayer->pTransform = new cTransform();
	this->pPlayer->pTransform->SetWorldPosition(0, m_pTerrain->GetHeight(0, 0), 0);

	this->pTransForCamera = new cTransform();

	this->pPlayer->pTransform->AddChild(this->pMainCamera);
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
	cRay.origin = pPlayer->pTransform->GetWorldPosition();
	//=============== ���� �ʱ�ȭ ��.
	pMainCamera->SetWorldPosition(2, 5, 2);
	isClick = false;



	return S_OK;
}

void animation_Test::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);

	SAFE_DELETE(this->pPlayer->pTransform);
	SAFE_DELETE(this->pTransForCamera);

	this->pSkinned1->Release();
	SAFE_DELETE(this->pSkinned1);
}

void animation_Test::Scene_Update(float timeDelta)
{
	this->pPlayer->Update(timeDelta);

	// ���� ������Ʈ
	m_currentPos = pPlayer->pTransform->GetWorldPosition(); // ���� ��ġ.
													  //cRay.direction = D3DXVECTOR3(0, -1, 0);
	cRay.origin.y = pPlayer->pTransform->GetWorldPosition().y + 5; // �Ӹ����� ���Ͽ���

	this->pTransForCamera->SetWorldPosition(this->pPlayer->pTransform->GetWorldPosition());

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
		this->pTransForCamera->SetWorldMatrix(this->pPlayer->pTransform->GetFinalMatrix());

		this->pPlayer->pTransform->AddChild(this->pMainCamera);
		this->pMainCamera->SetLocalPosition(0, 5, -10);
		isCharView = true;
		isAltView = false;
	}


	if (isCharView)
	{
		pMainCamera->DefaultControl3(timeDelta, this->pPlayer->pTransform);
	}
	else if (isAltView)
	{
		pMainCamera->DefaultControl3(timeDelta, this->pTransForCamera);
	}

	//+=======================================�ִϸ��̼� üũ ���� ==============================+
	
	
	//=========================
	//if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	//{
	//	pSkinned1->Play("STF_IDLE", 0.3f);
	//	Ray ray;
	//	POINT ptMousePos = GetMousePos();
	//	D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
	//	this->pMainCamera->ComputeRay(&ray, &screenPos);
	//
	//	this->m_pTerrain->IsIntersectRay(&m_mousePos, &ray);
	//	isClick = true;
	//
	//}
	//
	//if (isClick == true)
	//{
	//	D3DXVECTOR3 dir = m_mousePos - cRay.origin;	// ���� �� mousePos�� ���� �̵�.
	//	dir.y = 0;
	//
	//
	//	if (D3DXVec3Length(&dir) > 0.5f)
	//	{
	//		isMove = true;
	//		D3DXVec3Normalize(&dir, &dir);
	//		D3DXVECTOR3 lerp = pPlayer->pTransform->GetForward();
	//		D3DXVec3Lerp(&lerp, &lerp, &dir, 0.2);
	//		pPlayer->pTransform->LookDirection(lerp, D3DXVECTOR3(0, 1, 0));
	//
	//		cRay.origin += dir*0.2f;
	//	}
	//	else
	//	{
	//		isMove = false;
	//		isClick = false;
	//
	//		LOG_MGR->AddLog("Tx: %.2f, Ty : %.2f, Tz : %.2f",
	//			cRay.origin.x,
	//			cRay.origin.y,
	//			cRay.origin.z);
	//	}
	//}
	//
	//
	//if ((
	//	PHYSICS_MGR->IsRayHitStaticMeshObject(
	//		&this->cRay,
	//		this->m_Land,
	//		this->m_Land->pTransform,
	//		&this->m_prePos,
	//		NULL)) == true)
	//{
	//	m_lastPos = m_prePos; // ������Ʈ �浹 ���� �� Ŭ ��� Last ���� �����Ѵ�.
	//}
	//else
	//{
	//	m_lastPos.y = pPlayer->pTransform->GetWorldPosition().y - 10;
	//}
	//
	//// �ͷ��ΰ� �浹 �ߴٸ�.
	//if (this->m_pTerrain->IsIntersectRay(&m_prePos, &cRay) == true)
	//{
	//	if (m_lastPos.y > m_prePos.y)
	//	{
	//		m_prePos = m_lastPos;
	//	}
	//}
	//
	//
	//
	////=================================== �ɸ��͸� ���������� �����̰� �ϴ� �κ�
	//if (fabs(m_prePos.y - m_currentPos.y) < 0.5f && isMove == true) // ���ڴ� �Ѿ �� �ִ� ����. ( �Ʒ����� ���� ����. )
	//{
	//	this->pPlayer->pTransform->SetWorldPosition(m_prePos);
	//	m_currentPos = m_prePos; // ��ǥ ����
	//}
	//// ���̶� �ɸ��� �Ÿ��� �־����� ���̰� ���̻� �Ѿ�� ���ϰ� �����.
	//float rayCheckDis = D3DXVec3Length(&(cRay.origin - pPlayer->pTransform->GetWorldPosition()));
	//if (rayCheckDis > 0.25f) // ��� ���� �ӷ� ���� ���� ���� ��.
	//{
	//	cRay.origin = pPlayer->pTransform->GetWorldPosition();
	//	cRay.origin.y = pPlayer->pTransform->GetWorldPosition().y + 5; // �Ӹ����� ���Ͽ���
	//
	//}
	//else isMove = false;
	////=================================== �ɸ��͸� ���������� �����̰� �ϴ� �κ�  ��.


	if (KEY_MGR->IsOnceDown(VK_SPACE))
	
	{
		//LOG_MGR->AddLog("%d %d %s", KEY_MGR->IsOnceUp('W'), current_State, current_Ani.c_str());
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
	this->pPlayer->Render();

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

