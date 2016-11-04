#include "stdafx.h"
#include "camera_Test.h"
#include "cLight_Direction.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTerrain.h"
#include "cSkinnedAnimation.h"
#include "cLight_Point.h"

camera_Test::camera_Test()
{
}
camera_Test::~camera_Test()
{
}

HRESULT camera_Test::Scene_Init()
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

	cXMesh_Skinned* pSkinned = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Queen/Queen.X", &matCorrection);

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


	this->pSkinnedTrans->AddChild(this->pMainCamera);
	this->pMainCamera->SetLocalPosition(0, 5, -10);


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
	//pMainCamera->SetWorldPosition(2, 5, 2);
	isClick = false;
	return S_OK;
}

void camera_Test::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);

	SAFE_DELETE(this->pSkinnedTrans);

	this->pSkinned1->Release();
	SAFE_DELETE(this->pSkinned1);
}

void camera_Test::Scene_Update(float timeDelta)
{
	pMainCamera->DefaultControl3(timeDelta, this->pSkinnedTrans);

	// ���� ������Ʈ 
	m_currentPos = pSkinnedTrans->GetWorldPosition(); // ���� ��ġ. 
													  //cRay.direction = D3DXVECTOR3(0, -1, 0);
	cRay.origin.y = pSkinnedTrans->GetWorldPosition().y + 5; // �Ӹ����� ���Ͽ���

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
		//D3DXVECTOR3 dir = m_mousePos - cRay.origin;
		//D3DXVec3Normalize(&dir, &dir);

		D3DXVECTOR3 dir(0, 0, 1);
		cRay.origin += dir*timeDelta;

	//	LOG_MGR->AddLog("Tx: %.2f, Ty : %.2f, Tz : %.2f",
	//		cRay.origin.x,
	//		cRay.origin.y,
	//		cRay.origin.z);
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

void camera_Test::Scene_Render1()
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


void camera_Test::Scene_RenderSprite()
{
}

