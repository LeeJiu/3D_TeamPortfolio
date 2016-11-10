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
	pMainCamera = camera;
	pChar = pSkinned;
	pCharTrans = trans;
	m_pTerrain = terrain;
	isMove = false;
	//================���� �߰�. �Ʒ� ���� �ٲ��� ���� .
	moveRay.direction = D3DXVECTOR3(0, -1, 0);
	moveRay.origin = pCharTrans->GetWorldPosition();
	//	isClick = false;
	//================
	isJump = false;
	m_jumpPower = 0;
	m_gravity = 19.8f;

}
void moveClass::update(float timeDelta, cBaseObject* collObj)
{
	// ���� ������Ʈ 
	m_currentPos = pCharTrans->GetWorldPosition(); // ���� ��ġ. 
	//cRay.direction = D3DXVECTOR3(0, -1, 0);
	moveRay.origin.y = pCharTrans->GetWorldPosition().y + 5; // �Ӹ����� ���Ͽ���


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
		moveRay.origin += pCharTrans->GetRight()*0.2f;

	}
	if (KEY_MGR->IsStayDown('E'))
	{
		isMove = true;
		moveRay.origin -= pCharTrans->GetRight()*0.2f;
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
	}
	clickUpdate(); // Ŭ�� �������� ������Ʈ ���� �κ� �� ����.

	// ������Ʈ�� �浹�ߴٸ�. ( �ɷ� ������ ������ ���� �־���� �Ѵ�. )
	//=========================

	getLastHeight(collObj);
	//�Ʒ� ������ �Ŵ��� ��� ��
	//��ȯ�� ��ǥ �� = ( NULL or �浹 �� Obj , Obj,Terrain ���� Ray , �ͷ��� , ��ȯ ��ų ��ǥ ��)
	//m_prePos = PHYSICS_MGR->getLastHeight(collObj, &moveRay, m_pTerrain, &m_prePos);

	//================================ ���� ���̿� �ڵ� �ϸ��

	//===============================
	moveJumpCheck();

}
void moveClass::getLastHeight(cBaseObject* enumy)
{
	D3DXVECTOR3 tempLast(0, 0, 0); // �ӽ� ���� ����.

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
			tempLast = m_prePos; // ������Ʈ �浹 ���� �� Ŭ ��� Last ���� �����Ѵ�. 
			objColl = true;      // ������Ʈ �浹 �ߴ�. 
		}
	    // ������Ʈ�� �浹 ���� �ʾҴٸ� - ���� ��ġ ���� ���� ���� ����. ( �� ���� ������ �Ʒ��� �������� �ʴ´�. )
		//else
		//{
		//	tempLast.y = pCharTrans->GetWorldPosition().y - 10; // 
		//}
	}
	// ������Ʈ�� �浹 �ߴٸ� - tempLast �� ���� ����. 


	// �ͷ��ΰ� �浹 �ߴٸ�. 
	if (m_pTerrain->IsIntersectRay(&m_prePos, &moveRay) == true)
	{
		terrainColl = true;

		if (objColl == true) // �浹 �ߴٸ� . tempLast = obj�� ��ǥ�� ����. ( ���߿� Y�� ���� ���������� ��ȯ)
		{
			if (tempLast.y > m_prePos.y) // obj ��ǥ�� terrain ��ǥ�� �� �Ѵ�. 
			{
				m_prePos = tempLast;     // ū ���� �־���. 
			}
		}
	}

	// Ȥ�� �� ���� ó�� ( ���� �Ѵ� �浹 ���� �ʾҴٸ� �ϴ� �ͷ��� ��ġ�� ��ǥ�� ���� )
	if (objColl == false && terrainColl == false) 
	{
		m_prePos.y = m_pTerrain->GetHeight(m_prePos.x, m_prePos.z);
	}


}
void moveClass::render()
{
	//	pChar->Render(pCharTrans);
	GIZMO_MGR->Line(this->moveRay.origin, this->moveRay.origin + this->moveRay.direction * 100, 0xffffff00);

}

void moveClass::clickUpdate()
{
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
		D3DXVECTOR3 dir = m_mousePos - moveRay.origin;	// ���� �� mousePos�� ���� �̵�.	
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
void moveClass::moveJumpCheck()
{
	//===================== �׽�Ʈ�� ���� �ڵ� ====================
	// ������ true �϶�  ( y �� ���� )

	if (isJump == true)
	{
		this->pCharTrans->MovePositionSelf(0, m_jumpPower*timeDelta, 0);
		m_jumpPower -= m_gravity*timeDelta;

		// ���� ������Ʈ �� m_currentPos ����/
		m_currentPos = pCharTrans->GetWorldPosition(); // ���� ��ġ. 
		moveRay.origin.y = pCharTrans->GetWorldPosition().y + 5; // �Ӹ����� ���Ͽ���

	}

	// ���� �ִ°� prePos, ���� ��ġ current
	//=================================== �ɸ��͸� ���������� �����̰� �ϴ� �κ� 
	// ������ �Ʒ��� ������ ��� ( ������ �� �Ʒ� ������(������) - ���� ���´� �������� �ִ� ���� ���� -1 �̸� ������ �ٲ�鼭 �߷����� )
	if (m_prePos.y - m_currentPos.y < -1.f) //���� ��ǥ�� ������ ��ǥ���̰� ���� ������ Ʈ��� �ٲ�� �ؼ� �߷�����.
	{
		isJump = true;
	}
	// ���� �������� �� ���� �� ������ +���� ���´�. (prePos) --__ (current)
	if (fabs(m_prePos.y - m_currentPos.y) < 0.5f && isMove == true && isJump == false) // ���ڴ� �Ѿ �� �ִ� ����. ( �Ʒ����� ���� ����. )
	{
		this->pCharTrans->SetWorldPosition(m_prePos);
		m_currentPos = m_prePos; // ��ǥ ����
	}
	else if (isJump == true) // ���� ������ 
	{
		D3DXVECTOR3 jumpPos = m_prePos;
		jumpPos.y = m_currentPos.y;

		this->pCharTrans->SetWorldPosition(jumpPos);
		m_currentPos = jumpPos; // ��ǥ ����

		//================ �����̶� üũ. 
		if (fabs(m_prePos.y - m_currentPos.y) <= 0.2f)// 0.2�� EPSILON ��.
		{
			isJump = false;
			m_jumpPower = 0;
		}

	}

	// ���̶� �ɸ��� �Ÿ��� �־����� ���̰� ���̻� �Ѿ�� ���ϰ� �����.
	float rayCheckDis = D3DXVec3Length(&(moveRay.origin - pCharTrans->GetWorldPosition()));
	if (rayCheckDis > 0.21f) // ��� ���� �ӷ� ���� ���� ���� ��.
	{
		moveRay.origin = pCharTrans->GetWorldPosition();
		moveRay.origin.y = pCharTrans->GetWorldPosition().y + 5; // �Ӹ����� ���Ͽ���
	}

	isMove = false;
}