#include "stdafx.h"
#include "cViewDamage.h"
#include "cCamera.h"



cViewDamage::cViewDamage()
{
	num = 0;
	m_isDrawing = false;
}


cViewDamage::~cViewDamage()
{
	
}

void cViewDamage::Init()
{
	//unit_quard = new cQuadParticleEmitter();
	//tens_quard = new cQuadParticleEmitter();
	//hund_quard = new cQuadParticleEmitter();
	//thou_quard = new cQuadParticleEmitter();
	//mil_quard = new cQuadParticleEmitter();
	//
	//
	//unit_quard->SetActive(true);
	//tens_quard->SetActive(true);
	//hund_quard->SetActive(true);
	//thou_quard->SetActive(true);
	//mil_quard->SetActive(true);
	//
	//VEC_COLOR colors;
	//colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//
	//VEC_SCALE scales;
	//scales.push_back(0.5f);
	//scales.push_back(0.5f);
	//
	//unit_quard->Init(
	//	1,
	//	1.f,
	//	2.f,
	//	4.0f,
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),	
	//	D3DXVECTOR3(0, 0, 0),   
	//	D3DXVECTOR3(0, 0, 0),	
	//	D3DXVECTOR3(0, 0, 0),	
	//	D3DXVECTOR3(0, 0, 0),	
	//	D3DXVECTOR3(0, 0, 0),	
	//	colors, scales,
	//	0.5, 0.5f,
	//	NULL,
	//	true);
	//
	//VEC_COLOR colors2;
	//colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//
	//VEC_SCALE scales2;
	//scales2.push_back(0.5f);
	//scales2.push_back(0.5f);
	//
	//tens_quard->Init(
	//	1,
	//	1.f,
	//	2.f,
	//	4.0f,
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	colors2, scales2,
	//	0.5, 0.5f,
	//	NULL,
	//	true);
	//
	//VEC_COLOR colors3;
	//colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//
	//VEC_SCALE scales3;
	//scales3.push_back(0.5f);
	//scales3.push_back(0.5f);
	//
	//hund_quard->Init(
	//	1,
	//	1.f,
	//	2.f,
	//	4.0f,
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	colors3, scales3,
	//	0.5f, 0.5f,
	//	NULL,
	//	true);
	//
	//VEC_COLOR colors4;
	//colors4.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//colors4.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//
	//VEC_SCALE scales4;
	//scales4.push_back(0.5f);
	//scales4.push_back(0.5f);
	//
	//thou_quard->Init(
	//	1,
	//	1.f,
	//	2.f,
	//	4.0f,
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	colors4, scales4,
	//	0.5f, 0.5f,
	//	NULL,
	//	true);
	//
	//VEC_COLOR colors5;
	//colors5.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//colors5.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//
	//VEC_SCALE scales5;
	//scales5.push_back(0.5f);
	//scales5.push_back(0.5f);
	//
	//mil_quard->Init(
	//	1,
	//	1.f,
	//	2.f,
	//	4.0f,
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	D3DXVECTOR3(0, 0, 0),
	//	colors5, scales5,
	//	0.5f, 0.5f,
	//	NULL,
	//	true);
}

void cViewDamage::SetNumber(int number, cTransform* trans)
{
	///m_time = 0;
	///char temp[32];
	///
	///num = 0;
	///num = number;
	///if (num != 0)
	///{
	///	if (num < 10)
	///	{
	///		char temp[32];
	///		unit = num;
	///		
	///		sprintf_s(temp, "../Resources/Textures/num_%d.tga", unit);
	///		unit_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
	///		
	///	}
	///	//쿼드로 출력할거면 여기서 trans값을 빌보드해서 쿼드이미지를 맞춰서띄워주면뎀. -> texture로
	///	else if (10 <= num && num < 100)
	///	{
	///		unit = (number % 10);
	///		tens = (number / 10);
	///
	///
	///		sprintf_s(temp, "../Resources/Textures/num_%d.tga", unit);
	///		unit_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
	///		sprintf_s(temp, "../Resources/Textures/num_%d.tga", tens);
	///		tens_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
	///	    
	///		LOG_MGR->AddLog(" %d,%d", unit, tens);
	///	}
	///	else if (100 <= num && num < 1000)
	///	{
	///		unit = (number % 10);
	///		tens = (number / 10) % 10;
	///		hund = (number / 100);
	///
	///		unit_quard->pTransform->AttachTo(trans);
	///		tens_quard->pTransform->AttachTo(trans);
	///		hund_quard->pTransform->AttachTo(trans);
	///
	///		sprintf_s(temp, "../Resources/Textures/num_%d.tga", unit);
	///		unit_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
	///		sprintf_s(temp, "../Resources/Textures/num_%d.tga", tens);
	///		tens_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
	///		sprintf_s(temp, "../Resources/Textures/num_%d.tga", hund);
	///		hund_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
	///	}
	///	else if (1000 <= num && num < 10000)
	///	{
	///		unit = (number % 10);
	///		tens = (number / 10) % 10;
	///		hund = (number / 100) % 10;
	///		thou = (number / 1000);
	///
	///		sprintf_s(temp, "../Resources/Textures/num_%d.tga", unit);
	///		unit_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
	///		sprintf_s(temp, "../Resources/Textures/num_%d.tga", tens);
	///		tens_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
	///		sprintf_s(temp, "../Resources/Textures/num_%d.tga", hund);
	///		hund_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
	///		sprintf_s(temp, "../Resources/Textures/num_%d.tga", thou);
	///		thou_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
	///	}
	///	else if (10000 <= num && num < 100000)
	///	{
	///		unit = (number % 10);
	///		tens = (number / 10) % 10;
	///		hund = (number / 100) % 10;
	///		thou = (number / 1000) % 10;
	///		mil = (number / 10000);
	///
	///		sprintf_s(temp, "../Resources/Textures/num_%d.tga", unit);
	///		unit_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
	///		sprintf_s(temp, "../Resources/Textures/num_%d.tga", tens);
	///		tens_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
	///		sprintf_s(temp, "../Resources/Textures/num_%d.tga", hund);
	///		hund_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
	///		sprintf_s(temp, "../Resources/Textures/num_%d.tga", thou);
	///		thou_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
	///		sprintf_s(temp, "../Resources/Textures/num_%d.tga", mil);
	///		mil_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
	///	}
	///	else
	///	{
	///		LOG_MGR->AddLog("숫자 표기 범위를 벗어낫다대스");
	///		return;
	///	}
	///}
	///m_isDrawing = true;
	///
}

void cViewDamage::Release()
{
	//SAFE_DELETE(unit_quard);
	//SAFE_DELETE(tens_quard);
	//SAFE_DELETE(hund_quard);
	//SAFE_DELETE(thou_quard);
	//SAFE_DELETE(mil_quard);
}

void cViewDamage::Update(float timeDelta, cCamera* camera)
{
	//m_time += timeDelta;
	//if (m_time > 1)
	//{
	//	m_isDrawing = false;
	//	unit_quard->StopEmission();
	//	tens_quard->StopEmission();
	//	hund_quard->StopEmission();
	//	thou_quard->StopEmission();
	//	mil_quard->StopEmission();
	//}
	//
	//
	//
	//if (m_isDrawing)
	//{
	//	if (num < 10)
	//	{
	//		unit_quard->pTransform->MovePositionSelf(0, 2, 0);
	//
	//		unit_quard->StartEmission();
	//		
	//		unit_quard->Update(timeDelta);
	//		unit_quard->SetCameraSort(camera, true);
	//	}
	//	else if (10 <= num && num < 100)
	//	{
	//		unit_quard->pTransform->MovePositionSelf(0.25, 3, 0);
	//		tens_quard->pTransform->MovePositionSelf(-0.25, 3, 0);
	//
	//		unit_quard->StartEmission();
	//		tens_quard->StartEmission();
	//
	//		unit_quard->Update(timeDelta);
	//		tens_quard->Update(timeDelta);
	//
	//		unit_quard->SetCameraSort(camera, true);
	//		tens_quard->SetCameraSort(camera, true);
	//	}
	//	else if (100 <= num && num < 1000)
	//	{
	//		unit_quard->pTransform->SetLocalPosition(-0.25, 3, 0);
	//		tens_quard->pTransform->SetLocalPosition(0, 3, 0);
	//		hund_quard->pTransform->SetLocalPosition(0.25, 3, 0);
	//
	//		unit_quard->StartEmission();
	//		tens_quard->StartEmission();
	//		hund_quard->StartEmission();
	//
	//		unit_quard->Update(timeDelta);
	//		tens_quard->Update(timeDelta);
	//		hund_quard->Update(timeDelta);
	//
	//		unit_quard->SetCameraSort(camera, true);
	//		tens_quard->SetCameraSort(camera, true);
	//		hund_quard->SetCameraSort(camera, true);
	//	}
	//	else if (1000 <= num && num < 10000)
	//	{
	//		//unit_quard->pTransform->MovePositionSelf(-0.75, 3, 0);
	//		//tens_quard->pTransform->MovePositionSelf(-0.25, 3, 0);
	//		//hund_quard->pTransform->MovePositionSelf(0.25, 3, 0);
	//		//thou_quard->pTransform->MovePositionSelf(0.75, 3, 0);
	//	
	//		unit_quard->StartEmission();
	//		tens_quard->StartEmission();
	//		hund_quard->StartEmission();
	//		thou_quard->StartEmission();
	//	
	//		unit_quard->Update(timeDelta);
	//		tens_quard->Update(timeDelta);
	//		hund_quard->Update(timeDelta);
	//		thou_quard->Update(timeDelta);
	//	
	//		unit_quard->SetCameraSort(camera, true);
	//		tens_quard->SetCameraSort(camera, true);
	//		hund_quard->SetCameraSort(camera, true);
	//		thou_quard->SetCameraSort(camera, true);
	//	}
	//	else if (10000 <= num && num < 100000)
	//	{
	//		//unit_quard->pTransform->MovePositionLoc(-1, 3, 0);
	//		//tens_quard->pTransform->MovePositionSelf(-0.5, 3, 0);
	//		//hund_quard->pTransform->MovePositionSelf(0, 3, 0);
	//		//thou_quard->pTransform->MovePositionSelf(0.5, 3, 0);
	//		//mil_quard->pTransform->MovePositionSelf(1, 3, 0);
	//	
	//		unit_quard->StartEmission();
	//		tens_quard->StartEmission();
	//		hund_quard->StartEmission();
	//		thou_quard->StartEmission();
	//		mil_quard->StartEmission();
	//	
	//		unit_quard->Update(timeDelta);
	//		tens_quard->Update(timeDelta);
	//		hund_quard->Update(timeDelta);
	//		thou_quard->Update(timeDelta);
	//		mil_quard->Update(timeDelta);
	//		
	//		unit_quard->SetCameraSort(camera, true);
	//		tens_quard->SetCameraSort(camera, true);
	//		hund_quard->SetCameraSort(camera, true);
	//		thou_quard->SetCameraSort(camera, true);
	//		mil_quard->SetCameraSort(camera, true);
	//	}
	//
	//	D3DXVECTOR3 camPos(camera->GetWorldPosition().x, camera->GetWorldPosition().y, camera->GetWorldPosition().z);
	//	D3DXVECTOR3 dir(0, 1, 0);
	//
	//	unit_quard->pTransform->LookPosition(camPos, dir);
	//	tens_quard->pTransform->LookPosition(camPos, dir);
	//	hund_quard->pTransform->LookPosition(camPos, dir);
	//	thou_quard->pTransform->LookPosition(camPos, dir);
	//	mil_quard->pTransform->LookPosition(camPos, dir);
	//
	//	unit_quard->pTransform->SetRotateLocal(0, 180 * ONE_RAD, 0);
	//	tens_quard->pTransform->SetRotateLocal(0, 180 * ONE_RAD, 0);
	//	hund_quard->pTransform->SetRotateLocal(0, 180 * ONE_RAD, 0);
	//}
}

void cViewDamage::Render()
{
	//if (m_isDrawing)
	//{
	//	if (num < 10)
	//	{
	//		unit_quard->Render();
	//	}
	//	else if (10 <= num && num < 100)
	//	{
	//		unit_quard->Render();
	//		tens_quard->Render();
	//	}
	//	else if (100 <= num && num < 1000)
	//	{
	//		unit_quard->Render();
	//		tens_quard->Render();
	//		hund_quard->Render();
	//		unit_quard->pTransform->RenderGimozo();
	//		tens_quard->pTransform->RenderGimozo();
	//		hund_quard->pTransform->RenderGimozo();
	//
	//	}
	//	else if (1000 <= num && num < 10000)
	//	{
	//		unit_quard->Render();
	//		tens_quard->Render();
	//		hund_quard->Render();
	//		thou_quard->Render();
	//	}
	//	else if (10000 <= num && num < 100000)
	//	{
	//		unit_quard->Render();
	//		tens_quard->Render();
	//		hund_quard->Render();
	//		thou_quard->Render();
	//		mil_quard->Render();
	//	}
	//}
}
