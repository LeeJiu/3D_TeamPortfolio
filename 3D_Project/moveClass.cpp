#include "stdafx.h"
#include "moveClass.h"
#include "cTransform.h"
#include "cSkinnedAnimation.h"
#include "cTerrain.h"
#include "cBaseObject.h"
#include "cCamera.h"

moveClass::moveClass()
{
}


moveClass::~moveClass()
{
}

void moveClass::init(cSkinnedAnimation* pSkinned, cTransform* trans, cTerrain* terrain, cCamera* camera)
{
	//=================== 전방선언 값 대입.
	pMainCamera = camera;
	pChar = pSkinned;
	pCharTrans = trans;
	m_pTerrain = terrain;
	isMove = false;

	//================레이 추가. 아래 방향 바뀌지 않음 .
	moveRay.direction = D3DXVECTOR3(0, -1, 0);
	moveRay.origin = pCharTrans->GetWorldPosition();
	moveRay.origin.y = pCharTrans->GetWorldPosition().y + 3; // 머리위에 붙일예정
	m_currentPos = pCharTrans->GetWorldPosition(); // 현재 위치. 
	m_prePos = pCharTrans->GetWorldPosition();


	//================
	isClick = false;
	isJump = false;

	m_jumpPower = 0;
	m_gravity = 19.8f;

	test = false;

	objTest = true;
}
void moveClass::update(float timeDelta, cBaseObject* collObj)
{
	// 레이 업데이트 
	m_currentPos = pCharTrans->GetWorldPosition(); // 현재 위치. 
	//cRay.direction = D3DXVECTOR3(0, -1, 0);
	moveRay.origin.y = pCharTrans->GetWorldPosition().y + 3; // 머리위에 붙일예정


	if (KEY_MGR->IsStayDown('W'))
	{
		isMove = true;
		moveRay.origin += pCharTrans->GetForward()*0.2f;
	}
	if (KEY_MGR->IsStayDown('S'))
	{
		isMove = true;
		moveRay.origin -= pCharTrans->GetForward()*0.2f;

	}
	if (KEY_MGR->IsStayDown('Q'))
	{
		isMove = true;
		moveRay.origin -= pCharTrans->GetRight()*0.2f;

	}
	if (KEY_MGR->IsStayDown('E'))
	{
		isMove = true;
		moveRay.origin += pCharTrans->GetRight()*0.2f;
	}
	if (KEY_MGR->IsStayDown('A'))
	{
		pCharTrans->RotateSelf(0, -2 * ONE_RAD, 0);
	}

	if (KEY_MGR->IsStayDown('D'))
	{
		pCharTrans->RotateSelf(0, 2 * ONE_RAD, 0);
	}

	if (KEY_MGR->IsStayDown(VK_SPACE))
	{
		m_jumpPower = 6;

		isJump = true;

		LOG_MGR->AddLog("Ray: %.2f, Ray : %.2f, Ray : %.2f",
			moveRay.origin.x,
			moveRay.origin.y,
			moveRay.origin.z);
	}

	if (KEY_MGR->IsOnceDown('P'))
	{
		objTest = !objTest;
		if (objTest == true)
		{
			LOG_MGR->AddLog("objTest true");

		}
		else
		{
			LOG_MGR->AddLog("objTest false");

		}
	
	}
	clickUpdate(collObj); // 클릭 했을때랑 업데이트 도는 부분 들어가 있음.

	// 오브젝트와 충돌했다면. ( 걸러 낼려면 반지름 값을 넣어놔야 한다. )
	//=========================
	if (test == false)
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
	}

	if (objTest == false)
	{
		getLastHeight(NULL);
	}
	else if (objTest == true)
	{
		getLastHeight(collObj);

	}

	if (test == false)
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
	}

	//아래 피직스 매니져 사용 법
	//반환할 좌표 값 = ( NULL or 충돌 할 Obj , Obj,Terrain 비교할 Ray , 터레인 , 반환 시킬 좌표 값)
	//m_prePos = PHYSICS_MGR->getLastHeight(collObj, &moveRay, m_pTerrain, &m_prePos);

	//================================ 여기 사이에 코딩 하면됨

	//===============================
	moveJumpCheck(timeDelta);
	if (test == false)
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
	}

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
		// 오브젝트와 충돌 하지 않았다면 - 현재 위치 보다 낮은 값이 들어간다. ( 이 값이 없으면 아래로 내려가지 않는다. )
		//else
		//{
		//	tempLast.y = pCharTrans->GetWorldPosition().y - 10; // 
		//}
	}
	// 오브젝트와 충돌 했다면 - tempLast 에 값이 들어간다. 


	// 터레인과 충돌 했다면. 
	if (m_pTerrain->IsIntersectRay(&m_prePos, &moveRay))
	{
		if (test == false)
		{
			LOG_MGR->AddLog("시벌: %.2f, Ty : %.2f, Tz : %.2f",
				m_prePos.x,
				m_prePos.y,
				m_prePos.z);

			LOG_MGR->AddLog("Ray: %.2f, Ray : %.2f, Ray : %.2f",
				moveRay.origin.x,
				moveRay.origin.y,
				moveRay.origin.z);
		}
		terrainColl = true;

		if (objColl == true) // 충돌 했다면 . tempLast = obj의 좌표와 같다. ( 그중에 Y축 값이 높은것으로 반환)
		{
			if (tempLast.y > m_prePos.y) // obj 좌표와 terrain 좌표와 비교 한다. 
			{
				m_prePos = tempLast;     // 큰 값을 넣어줌. 
			}
		}
	}


	// 혹시 모를 예외 처리 ( 만약 둘다 충돌 되지 않았다면 일단 터레인 위치로 좌표를 수정 )
	if (objColl == false && terrainColl == false)
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

void moveClass::clickUpdate(cBaseObject* enumy)
{
	//반환할 좌표 값 = ( NULL or 충돌 할 Obj , Obj,Terrain 비교할 Ray , 터레인 , 반환 시킬 좌표 값)
	//m_prePos = PHYSICS_MGR->getLastHeight(collObj, &moveRay, m_pTerrain, &m_prePos);


	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		Ray ray;
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		this->pMainCamera->ComputeRay(&ray, &screenPos);

		this->m_pTerrain->IsIntersectRay(&m_mousePos, &ray);
		m_mousePos = PHYSICS_MGR->getLastHeight(enumy, &ray, m_pTerrain, &m_mousePos);
		isClick = true;
	}

	if (isClick == true)
	{
		D3DXVECTOR3 dir = m_mousePos - moveRay.origin;	// 방향 및 mousePos의 원점 이동.	
		dir.y = 0;


		if (D3DXVec3Length(&dir) > 0.5f)
		{
			isMove = true;
			D3DXVec3Normalize(&dir, &dir);
			D3DXVECTOR3 lerp = pCharTrans->GetForward();
			D3DXVec3Lerp(&lerp, &lerp, &dir, 0.2);
			pCharTrans->LookDirection(lerp, D3DXVECTOR3(0, 1, 0));

			moveRay.origin += dir*0.2f;
		}
		else
		{
			isMove = false;
			isClick = false;

			// LOG_MGR->AddLog("Tx: %.2f, Ty : %.2f, Tz : %.2f",
			// 	moveRay.origin.x,
			// 	moveRay.origin.y,
			// 	moveRay.origin.z);
		}
	}
}
void moveClass::moveJumpCheck(float timeDelta)
{
	//===================== 테스트용 점프 코드 ====================
	// 점프가 true 일때  ( y 값 감소 )

	if (isJump == true)
	{
		this->pCharTrans->MovePositionSelf(0, m_jumpPower*timeDelta, 0);
		m_jumpPower -= m_gravity*timeDelta;

		// 레이 업데이트 및 m_currentPos 갱신/
		m_currentPos = pCharTrans->GetWorldPosition(); // 현재 위치. 
		moveRay.origin.y = pCharTrans->GetWorldPosition().y + 5; // 머리위에 붙일예정

	}

	// 갈수 있는곳 prePos, 현재 위치 current
	//=================================== 케릭터를 최종적으로 움직이게 하는 부분 
	// 위에서 아래로 내려갈 경우 ( 갈곳이 더 아래 있으면(작은값) - 값이 나온다 내려갈수 있는 값이 차가 -1 이면 점프로 바뀌면서 중력적용 )
	if (m_prePos.y - m_currentPos.y < -1.f) //현재 좌표와 움직일 좌표차이가 나면 점프를 트루로 바뀌게 해서 중력을줌.
	{
		isJump = true;
	}
	// 위와 마찮가지 갈 곳이 더 높으면 +값이 나온다. (prePos) --__ (current)
	if (fabs(m_prePos.y - m_currentPos.y) < 0.5f && isJump == false) // 숫자는 넘어갈 수 있는 높이. ( 아래에서 위로 갈떄. )
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
		moveRay.origin.y = pCharTrans->GetWorldPosition().y + 5; // 머리위에 붙일예정
	}

	isMove = false;
}