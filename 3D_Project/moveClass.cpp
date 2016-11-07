#include "stdafx.h"
#include "moveClass.h"
#include "cTransform.h"
#include "cSkinnedAnimation.h"
#include "cTerrain.h"

moveClass::moveClass()
{
}


moveClass::~moveClass()
{
}

void moveClass::init(cSkinnedAnimation* pSkinned, cTransform* trans, cTerrain* terrain)
{
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
	m_gravity = 4.f;

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
		m_jumpPower = 4;
		m_gravity = 10.f;

		isJump = true;
	}


	// ������Ʈ�� �浹�ߴٸ�. ( �ɷ� ������ ������ ���� �־���� �Ѵ�. )

	//m_lastPos = this->pSkinnedTrans->GetWorldPosition();
	//m_lastPos.y = -1000;
	// ���Ŀ� �Ÿ� ���� �̿��ؼ� 2,3��° ���� ���� �ɷ� ������.
	if ((
		PHYSICS_MGR->IsRayHitStaticMeshObject(
		&this->moveRay,
		collObj,
		collObj->pTransform,
		&this->m_prePos,
		NULL)) == true )
	{
		m_lastPos = m_prePos; // ������Ʈ �浹 ���� �� Ŭ ��� Last ���� �����Ѵ�. 
	}
	else
	{
		m_lastPos.y = pCharTrans->GetWorldPosition().y - 10;
	}

	// �ͷ��ΰ� �浹 �ߴٸ�. 
	if (m_pTerrain->IsIntersectRay(&m_prePos, &moveRay) == true )
	{
		if (m_lastPos.y > m_prePos.y)
		{
			m_prePos = m_lastPos;
		}
	}

	//===================== �׽�Ʈ�� ���� �ڵ� ====================
	// ������ true �϶� 
	if (isJump == true)
	{
		this->pCharTrans->MovePositionSelf(0, m_jumpPower*timeDelta, 0);
		m_jumpPower -= m_gravity*timeDelta;

		// ���� ������Ʈ �� m_currentPos ����/
		m_currentPos = pCharTrans->GetWorldPosition(); // ���� ��ġ. 
		moveRay.origin.y = pCharTrans->GetWorldPosition().y + 5; // �Ӹ����� ���Ͽ���
	}


	if (m_jumpPower > 0.f)
	{

	}
	else if (m_jumpPower < 0.f)
	{

	}

	//=================================== �ɸ��͸� ���������� �����̰� �ϴ� �κ� 
	if (m_prePos.y - m_currentPos.y < -1.f)
	{
		//m_jumpPower = 0.f;
		isJump = true;
	}
	if (m_prePos.y - m_currentPos.y < 0.3f && isMove == true && isJump==false) // ���ڴ� �Ѿ �� �ִ� ����. ( �Ʒ����� ���� ����. )
	{
		this->pCharTrans->SetWorldPosition(m_prePos);
		m_currentPos = m_prePos; // ��ǥ ����
	}
	else if (isJump ==true) // ���� ������ 
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

void moveClass::render()
{
//	pChar->Render(pCharTrans);
	GIZMO_MGR->Line(this->moveRay.origin, this->moveRay.origin + this->moveRay.direction * 100, 0xffffff00);

}