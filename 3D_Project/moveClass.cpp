#include "stdafx.h"
#include "moveClass.h"
#include "cTransform.h"
#include "cTerrain.h"
#include "cBaseObject.h"
#include "cCamera.h"
#include "cBoundBox.h"
moveClass::moveClass()
{
}


moveClass::~moveClass()
{
}

void moveClass::init(cTransform* trans, cTerrain* terrain, cCamera* camera)
{
	//=================== 전방선언 값 대입.
	pMainCamera = camera;
	pCharTrans = trans;
	//pCharBound = pBox;
	m_pTerrain = terrain;

	isMove = false;

	//================레이 추가. 아래 방향 바뀌지 않음 .
	moveRay.direction = D3DXVECTOR3(0, -1, 0);
	moveRay.origin = pCharTrans->GetWorldPosition();
	moveRay.origin.y = pCharTrans->GetWorldPosition().y + HEADPOS; // 머리위에 붙일예정
	m_currentPos = pCharTrans->GetWorldPosition(); // 현재 위치. 
	m_prePos = pCharTrans->GetWorldPosition();
	this->pCharTrans->SetWorldPosition(m_prePos);

	//================
	isClick = false;
	isJump = false;

	m_jumpPower = 0;
	m_gravity = 19.8f;
}

void moveClass::init(cTransform* trans, cTerrain* terrain, cCamera* camera, cBoundBox* pBox)
{
	//=================== 전방선언 값 대입.
	pMainCamera = camera;
	pCharTrans = trans;
	pCharBound = pBox;
	m_pTerrain = terrain;

	//================레이 추가. 아래 방향 바뀌지 않음 .
	moveRay.direction = D3DXVECTOR3(0, -1, 0);
	moveRay.origin = pCharTrans->GetWorldPosition();
	moveRay.origin.y = pCharTrans->GetWorldPosition().y + HEADPOS; // 머리위에 붙일예정
	m_currentPos = pCharTrans->GetWorldPosition(); // 현재 위치. 
	m_prePos = pCharTrans->GetWorldPosition();
	this->pCharTrans->SetWorldPosition(m_prePos);

	//================
	isClick = false;
	isJump = false;
	isMove = false;

	m_jumpPower = 0;
	m_gravity = 19.8f;

	//test = false;
	//objTest = true;
}

void moveClass::update(float timeDelta, cBaseObject* collObj, cBoundBox* collBox, cTransform* collTrans)
{
	// 레이 업데이트 
	m_currentPos = pCharTrans->GetWorldPosition(); // 현재 위치. 
	//cRay.direction = D3DXVECTOR3(0, -1, 0);
	moveRay.origin.y = pCharTrans->GetWorldPosition().y + HEADPOS; // 머리위에 붙일예정

	this->isMove = false;

	LOG_MGR->AddLog("move %d", m_InputKey.find('W')->second);

	if (m_InputKey.find('W')->second)		//m_InputKey.find(키값)->second이 true이면.
	{
		this->isMove = true;
		moveRay.origin += pCharTrans->GetForward()*0.1f;
	}

	if (m_InputKey.find('S')->second)
	{
		this->isMove = true;
		moveRay.origin -= pCharTrans->GetForward()*0.1f;
	}

	if (m_InputKey.find('A')->second)
	{
		this->isMove = true;
		pCharTrans->RotateSelf(0, -2 * ONE_RAD, 0);
	}

	if (m_InputKey.find('D')->second)
	{
		this->isMove = true;
		pCharTrans->RotateSelf(0, 2 * ONE_RAD, 0);
	}

	if (m_InputKey.find(VK_SPACE)->second)
	{
		m_jumpPower = 10;
		this->isJump = true;
	}



	clickUpdate(collObj); // 클릭 했을때랑 업데이트 도는 부분 들어가 있음.

	// 오브젝트와 충돌했다면. ( 걸러 낼려면 반지름 값을 넣어놔야 한다. )
	//=========================
	//getLastHeight(NULL);

	getLastHeight(collObj);


	//아래 피직스 매니져 사용 법
	//반환할 좌표 값 = ( NULL or 충돌 할 Obj , Obj,Terrain 비교할 Ray , 터레인 , 반환 시킬 좌표 값)
	//m_prePos = PHYSICS_MGR->getLastHeight(collObj, &moveRay, m_pTerrain, &m_prePos);

	moveJumpCheck(timeDelta);
	boundCheck(collBox, collTrans);


	/*	if (test == false)
		{
		LOG_MGR->AddLog("Tx: %.2f, Ty : %.2f, Tz : %.2f",
		m_prePos.x,
		m_prePos.y,
		m_prePos.z);

		LOG_MGR->AddLog("Ray: %.2f, Ray : %.2f, Ray : %.2f",
		moveRay.origin.x,
		moveRay.origin.y,
		moveRay.origin.z);
		test = true;
		}*/
	//test = true;
}

void moveClass::update(float timeDelta, cBaseObject * collObj, cBoundBox * collBox, cTransform * collTrans, std::map<int, bool> key)
{
	m_InputKey = key;	//키값 캐릭터에서 받아와

	// 레이 업데이트 
	m_currentPos = pCharTrans->GetWorldPosition(); // 현재 위치. 
	//cRay.direction = D3DXVECTOR3(0, -1, 0);
	moveRay.origin.y = pCharTrans->GetWorldPosition().y + HEADPOS; // 머리위에 붙일예정

	this->isMove = false;

	if (m_InputKey.find('W')->second)		//m_InputKey.find(키값)->second이 true이면.
	{
		this->isMove = true;
		moveRay.origin += pCharTrans->GetForward()*0.2f;
	}

	if (m_InputKey.find('S')->second)
	{
		this->isMove = true;
		moveRay.origin -= pCharTrans->GetForward()*0.1f;
	}

	if (m_InputKey.find('A')->second)
	{
		this->isMove = true;
		pCharTrans->RotateSelf(0, -2 * ONE_RAD, 0);
	}

	if (m_InputKey.find('D')->second)
	{
		this->isMove = true;
		pCharTrans->RotateSelf(0, 2 * ONE_RAD, 0);
	}

	if (m_InputKey.find(VK_SPACE)->second)
	{
		m_jumpPower = 12;
		this->isJump = true;
	}



	//clickUpdate(collObj); // 클릭 했을때랑 업데이트 도는 부분 들어가 있음.

	// 오브젝트와 충돌했다면. ( 걸러 낼려면 반지름 값을 넣어놔야 한다. )
	//=========================
	//getLastHeight(NULL);

	getLastHeight(collObj);


	//아래 피직스 매니져 사용 법
	//반환할 좌표 값 = ( NULL or 충돌 할 Obj , Obj,Terrain 비교할 Ray , 터레인 , 반환 시킬 좌표 값)
	m_prePos = PHYSICS_MGR->getLastHeight(collObj, &moveRay, m_pTerrain, &m_prePos);

	moveJumpCheck(timeDelta);
	boundCheck(collBox, collTrans);


	/*	if (test == false)
	{
	LOG_MGR->AddLog("Tx: %.2f, Ty : %.2f, Tz : %.2f",
	m_prePos.x,
	m_prePos.y,
	m_prePos.z);

	LOG_MGR->AddLog("Ray: %.2f, Ray : %.2f, Ray : %.2f",
	moveRay.origin.x,
	moveRay.origin.y,
	moveRay.origin.z);
	test = true;
	}*/
	//test = true;
}

void moveClass::update(float timeDelta, std::vector<cBaseObject*> vObj, std::vector<cBaseObject*> vBound, std::map<int, bool> key)
{
	m_InputKey = key;	//키값 캐릭터에서 받아와

	// 레이 업데이트 
	m_currentPos = pCharTrans->GetWorldPosition(); // 현재 위치. 
	//cRay.direction = D3DXVECTOR3(0, -1, 0);
	moveRay.origin.y = pCharTrans->GetWorldPosition().y + HEADPOS; // 머리위에 붙일예정

	this->isMove = false;

	if (m_InputKey.find('W')->second)		//m_InputKey.find(키값)->second이 true이면.
	{
		this->isMove = true;
		moveRay.origin += pCharTrans->GetForward()*0.2f;
	}

	if (m_InputKey.find('S')->second)
	{
		this->isMove = true;
		moveRay.origin -= pCharTrans->GetForward()*0.1f;
	}

	if (m_InputKey.find('A')->second)
	{
		this->isMove = true;
		pCharTrans->RotateSelf(0, -2 * ONE_RAD, 0);
	}

	if (m_InputKey.find('D')->second)
	{
		this->isMove = true;
		pCharTrans->RotateSelf(0, 2 * ONE_RAD, 0);
	}

	if (m_InputKey.find(VK_SPACE)->second)
	{
		m_jumpPower = 12;
		this->isJump = true;
	}



	//clickUpdate(collObj); // 클릭 했을때랑 업데이트 도는 부분 들어가 있음.

	// 오브젝트와 충돌했다면. ( 걸러 낼려면 반지름 값을 넣어놔야 한다. )
	//=========================
	//getLastHeight(NULL);

	getLastHeight(vObj);

	//아래 피직스 매니져 사용 법
	//반환할 좌표 값 = ( NULL or 충돌 할 Obj , Obj,Terrain 비교할 Ray , 터레인 , 반환 시킬 좌표 값)
	
	//m_prePos = PHYSICS_MGR->getLastHeight(collObj, &moveRay, m_pTerrain, &m_prePos);

	moveJumpCheck(timeDelta);
	
	boundCheck(vBound);

	/*	if (test == false)
	{
	LOG_MGR->AddLog("Tx: %.2f, Ty : %.2f, Tz : %.2f",
	m_prePos.x,
	m_prePos.y,
	m_prePos.z);

	LOG_MGR->AddLog("Ray: %.2f, Ray : %.2f, Ray : %.2f",
	moveRay.origin.x,
	moveRay.origin.y,
	moveRay.origin.z);
	test = true;
	}*/
	//test = true;
}

void moveClass::getLastHeight(cBaseObject* enumy)
{
	D3DXVECTOR3 tempLast(0, 0, 0); // 임시 저장 변수.
	bool objColl = false;
	bool terrainColl = false;

	if (enumy != NULL)
	{
		if ((
			PHYSICS_MGR->IsRayHitStaticMeshObject(
			&this->moveRay,
			enumy,
			enumy->pTransform,
			&this->m_prePos,
			NULL)) == true)
		{
			tempLast = m_prePos; // 오브젝트 충돌 값이 더 클 경우 Last 값을 갱신한다. 
			objColl = true;      // 오브젝트 충돌 했다. 

		}

	}
	// 오브젝트와 충돌 했다면 - tempLast 에 값이 들어간다. 


	// 터레인과 충돌 했다면. 
	if (m_pTerrain->IsIntersectRay(&m_prePos, &moveRay) == true)
	{

		terrainColl = true;

		if (objColl == true) // 충돌 했다면 . tempLast = obj의 좌표와 같다. ( 그중에 Y축 값이 높은것으로 반환)
		{
			if (tempLast.y > m_prePos.y) // obj 좌표와 terrain 좌표와 비교 한다. 
			{
				m_prePos = tempLast;     // 큰 값을 넣어줌. 
			}
		}
	}
	// 예외처리 / 맨 처음 한번은 쿼드 트리에서 레이체크를 못한다.
	if (objColl == false && terrainColl == false)
	{
		m_prePos.y = m_pTerrain->GetHeight(m_prePos.x, m_prePos.z);
		this->pCharTrans->SetWorldPosition(m_prePos);
		m_currentPos.y = m_pTerrain->GetHeight(m_prePos.x, m_prePos.z);
	}
	// 예외처리 / 맨 처음 한번은 쿼드 트리에서 레이체크를 못한다.
	if (objColl == true && terrainColl == false)
	{
		m_prePos.y = m_pTerrain->GetHeight(m_prePos.x, m_prePos.z);
		this->pCharTrans->SetWorldPosition(m_prePos);
	}

}

void moveClass::render()
{
	//	pChar->Render(pCharTrans);
	GIZMO_MGR->Line(this->moveRay.origin, this->moveRay.origin + this->moveRay.direction * 100, 0xffffff00);
	GIZMO_MGR->WireSphere(this->m_mousePos, 0.5f, 0xffff0000);
}

void moveClass::clickUpdate(cBaseObject* enemy)
{
	//	//반환할 좌표 값 = ( NULL or 충돌 할 Obj , Obj,Terrain 비교할 Ray , 터레인 , 반환 시킬 좌표 값)
	//	//m_prePos = PHYSICS_MGR->getLastHeight(collObj, &moveRay, m_pTerrain, &m_prePos);
	//	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	//	{
	//		Ray ray;
	//		POINT ptMousePos = GetMousePos();
	//		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
	//		this->pMainCamera->ComputeRay(&ray, &screenPos);
	//
	//	//	this->m_pTerrain->IsIntersectRay(&m_mousePos, &ray);
	//		m_mousePos = PHYSICS_MGR->getLastHeight(enemy, &ray, m_pTerrain, &m_mousePos);
	//		isClick = true;
	//	}
	//
	//	if (isClick == true)
	//	{
	//		D3DXVECTOR3 dir = m_mousePos - moveRay.origin;	// 방향 및 mousePos의 원점 이동.	
	//		dir.y = 0;
	//
	//
	//		if (D3DXVec3Length(&dir) > 0.5f)
	//		{
	//			isMove = true;
	//			D3DXVec3Normalize(&dir, &dir);
	//			D3DXVECTOR3 lerp = pCharTrans->GetForward();
	//			D3DXVec3Lerp(&lerp, &lerp, &dir, 0.2);
	//			pCharTrans->LookDirection(lerp, D3DXVECTOR3(0, 1, 0));
	//
	//			moveRay.origin += dir*0.2f;
	//		}
	//		else
	//		{
	//			isMove = false;
	//			isClick = false;
	//			// LOG_MGR->AddLog("Tx: %.2f, Ty : %.2f, Tz : %.2f",
	//			// 	moveRay.origin.x,
	//			// 	moveRay.origin.y,
	//			// 	moveRay.origin.z);
	//		}
	//	}
}

void moveClass::moveJumpCheck(float timeDelta)
{
	//===================== 테스트용 점프 코드 ====================
	// 점프가 true 일때  ( y 값 감소 )

	if (isJump == true)
	{
		this->pCharTrans->MovePositionSelf(0, m_jumpPower * timeDelta, 0);
		m_jumpPower -= m_gravity * timeDelta;

		// 레이 업데이트 및 m_currentPos 갱신/
		m_currentPos = pCharTrans->GetWorldPosition(); // 현재 위치. 
		moveRay.origin.y = pCharTrans->GetWorldPosition().y + HEADPOS; // 머리위에 붙일예정
	}

	// 갈수 있는곳 prePos, 현재 위치 current
	//=================================== 케릭터를 최종적으로 움직이게 하는 부분 
	// 위에서 아래로 내려갈 경우 ( 갈곳이 더 아래 있으면(작은값) - 값이 나온다 내려갈수 있는 값이 차가 -1 이면 점프로 바뀌면서 중력적용 )
	if (m_prePos.y - m_currentPos.y < -2.f) //현재 좌표와 움직일 좌표차이가 나면 점프를 트루로 바뀌게 해서 중력을줌.
	{
		isJump = true;
	}
	
	// 위와 마찬가지 갈 곳이 더 높으면 +값이 나온다. (prePos) --__ (current)
	if (fabs(m_prePos.y - m_currentPos.y) < 0.7f && isMove == true && isJump == false) // 숫자는 넘어갈 수 있는 높이. ( 아래에서 위로 갈 때. )
	{
		this->pCharTrans->SetWorldPosition(m_prePos);
		m_currentPos = m_prePos; // 좌표 갱신
	}
	else if (isJump == true) // 점프 했을때 
	{
		D3DXVECTOR3 jumpPos = m_prePos;
		jumpPos.y = m_currentPos.y;

		this->pCharTrans->SetWorldPosition(jumpPos);
		m_currentPos = jumpPos; // 좌표 갱신

		//================ 지상이랑 체크. 
		if (fabs(m_prePos.y - m_currentPos.y) <= 0.3f)// 0.2은 EPSILON 값.
		{
			isJump = false;
			m_jumpPower = 0;
		}

	}

	// 레이랑 케릭터 거리가 멀어지면 레이가 더이상 넘어가지 못하게 만든다.
	float rayCheckDis = D3DXVec3Length(&(moveRay.origin - pCharTrans->GetWorldPosition()));
	if (rayCheckDis > 0.21f) // 상수 값은 속력 보다 조금 높은 값.
	{
		moveRay.origin = pCharTrans->GetWorldPosition();
		moveRay.origin.y = pCharTrans->GetWorldPosition().y + HEADPOS; // 머리위에 붙일예정
	}


}

void moveClass::boundCheck(cBoundBox* collBox, cTransform* collTrans)
{
	if (collBox != NULL &&
		PHYSICS_MGR->IsBlocking(
		pCharTrans,
		pCharBound,
		collTrans, collBox, 1.f))
	{
		moveRay.origin = pCharTrans->GetWorldPosition();
		moveRay.origin.y = pCharTrans->GetWorldPosition().y + HEADPOS; // 머리위에 붙일예정

		m_currentPos = pCharTrans->GetWorldPosition();
		m_prePos = pCharTrans->GetWorldPosition();

	}
}
void moveClass::boundCheck(std::vector<cBaseObject*> vBound)
{
	std::vector<cBaseObject*>::iterator iter;

	for (iter = vBound.begin(); iter != vBound.end(); ++iter)
	{
		float dist = D3DXVec3Length(&((*iter)->pTransform->GetWorldPosition() - pCharTrans->GetWorldPosition()));
		if (dist < 5)
		{
			if (PHYSICS_MGR->IsBlocking(
				pCharTrans,
				pCharBound,
				(*iter)->pTransform, &(*iter)->BoundBox, 1.f))
			{
				moveRay.origin = pCharTrans->GetWorldPosition();
				moveRay.origin.y = pCharTrans->GetWorldPosition().y + HEADPOS; // 머리위에 붙일예정

				m_currentPos = pCharTrans->GetWorldPosition();
				m_prePos = pCharTrans->GetWorldPosition();

			}
		}
		//(*iter)->pTransform
	}

}

void moveClass::getLastHeight(std::vector<cBaseObject*> vObj)
{
	D3DXVECTOR3 tempLast(0, 0, 0); // 임시 저장 변수.
	bool objColl = false;
	bool terrainColl = false;

	std::vector<cBaseObject*>::iterator iter;
	for (iter = vObj.begin(); iter != vObj.end(); ++iter)
	{
		float dist = D3DXVec3Length(&((*iter)->pTransform->GetWorldPosition() - pCharTrans->GetWorldPosition()));
	
		if ((*iter)->objType != MIGDAL_WALL || (*iter)->objType != MIGDAL_HOUSE &&dist < 2)
		{
			if ((
				PHYSICS_MGR->IsRayHitStaticMeshObject(
				&this->moveRay,
				(*iter),
				(*iter)->pTransform,
				&this->m_prePos,
				NULL)) == true)
			{
				tempLast = m_prePos; // 오브젝트 충돌 값이 더 클 경우 Last 값을 갱신한다. 
				objColl = true;      // 오브젝트 충돌 했다. 
	
			}
		}
		 else if ((*iter)->objType == MIGDAL_WALL || (*iter)->objType == MIGDAL_HOUSE && dist < 30)
		 {
		 	if ((
		 		PHYSICS_MGR->IsRayHitStaticMeshObject(
		 		&this->moveRay,
		 		(*iter),
		 		(*iter)->pTransform,
		 		&this->m_prePos,
		 		NULL)) == true)
		 	{
		 		tempLast = m_prePos; // 오브젝트 충돌 값이 더 클 경우 Last 값을 갱신한다. 
		 		objColl = true;      // 오브젝트 충돌 했다. 
		 
		 	}
		 }
	}

	// 오브젝트와 충돌 했다면 - tempLast 에 값이 들어간다. 


	// 터레인과 충돌 했다면. 
	if (m_pTerrain->IsIntersectRay(&m_prePos, &moveRay) == true)
	{

		terrainColl = true;

		if (objColl == true) // 충돌 했다면 . tempLast = obj의 좌표와 같다. ( 그중에 Y축 값이 높은것으로 반환)
		{
			if (tempLast.y > m_prePos.y) // obj 좌표와 terrain 좌표와 비교 한다. 
			{
				m_prePos = tempLast;     // 큰 값을 넣어줌. 
			}
		}
	}
	// 예외처리 / 맨 처음 한번은 쿼드 트리에서 레이체크를 못한다.
	if (objColl == false && terrainColl == false)
	{
		m_prePos.y = m_pTerrain->GetHeight(m_prePos.x, m_prePos.z);
		this->pCharTrans->SetWorldPosition(m_prePos);
		m_currentPos.y = m_pTerrain->GetHeight(m_prePos.x, m_prePos.z);

	}
	// 예외처리 / 맨 처음 한번은 쿼드 트리에서 레이체크를 못한다.
	if (objColl == true && terrainColl == false)
	{
		m_prePos.y = m_pTerrain->GetHeight(m_prePos.x, m_prePos.z);
		this->pCharTrans->SetWorldPosition(m_prePos);
	}

}