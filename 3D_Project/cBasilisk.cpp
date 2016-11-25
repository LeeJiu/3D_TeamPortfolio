#include "stdafx.h"
#include "cBasilisk.h"
#include "cPlayer.h"
#include "cWayPoint.h"


cBasilisk::cBasilisk()
{
	m_fHP = 1000;
	m_fRange = 20;
	m_state = WALK;
	m_strName = MyUtil::SetAnimation(m_state);
	m_bIsOverlap = false;
	m_bHit = false;
	m_bHit2 = false;
	m_fAtkTime = 0;
	m_fDeadTime = 0;
}


cBasilisk::~cBasilisk()
{
	SAFE_DELETE(m_pWayPoint);
}

void cBasilisk::BaseObjectEnable()
{
	pSkinned->Play("WALK");

	m_pWayPoint = new cWayPoint(pTerrain);
	m_pWayPoint->Init(pTransform, 10.0f);
}

void cBasilisk::BaseObjectUpdate(float timeDelta)
{
	float distance = D3DXVec3Length(&(m_pPlayer->pTransform->GetWorldPosition() - pTransform->GetWorldPosition()));

	if (distance < m_fRange)
	{
		m_bIsOverlap = PHYSICS_MGR->IsOverlap(this, m_pPlayer);
		//m_bIsOverlap = PHYSICS_MGR->IsOverlap(m_pHitTrans, &m_pHitBound, m_pPlayer->pTransform, &m_pPlayer->BoundBox);

		if (m_state == WALK || m_state == WAIT)
		{
			if (m_bIsOverlap == true)
			{
				if (m_bHit2 == false)
				{
					Attack02(timeDelta);
				}
				else
				{
					Attack01(timeDelta);
				}
			}
			else
			{
				m_state = RUN;
				m_strName = MyUtil::SetAnimation(m_state);
				pSkinned->Play(m_strName);
			}
			
		}
		else if (m_state == RUN)
		{
			if (m_bIsOverlap == true)
			{
				if (m_bHit2 == false)
				{
					Attack02(timeDelta);
				}
				else
				{
					Attack01(timeDelta);
				}
			}
			else
			{
				MoveToPlayer();
			}
		}
		else if (m_state == ATK_01)
		{
			Attack01(timeDelta);
		}
		else if (m_state == ATK_02)
		{
			Attack02(timeDelta);
		}
	}
	//범위 밖
	else
	{
		if (m_state == RUN)
		{
			m_state = WAIT;
			m_strName = MyUtil::SetAnimation(m_state);
			pSkinned->Play(m_strName);
		}
		else if (m_state == WALK)
		{
			m_pWayPoint->Update(pTransform);
		}

		m_bHit2 = false;
	}

	SetAniState();
}

void cBasilisk::BaseObjectBoundBox()
{
	pSkinned->AddBoneTransform("Bip01-Head", m_pHitTrans);
	m_pHitTrans->MovePositionSelf(0.5f, 0, 0);
	m_pHitBound.SetBound(&m_pHitTrans->GetWorldPosition(), &D3DXVECTOR3(0.5f, 0.8f, 0.5f));

	BoundBox.SetBound(&D3DXVECTOR3(0, 1.0f, 0), &D3DXVECTOR3(1.5f, 1.0f, 3.0f));
}

void cBasilisk::BaseObjectRender()
{
	this->pSkinned->Render(this->pTransform);
	this->pTransform->RenderGimozo();
	this->BoundBox.RenderGizmo(this->pTransform);
	this->m_pHitBound.RenderGizmo(m_pHitTrans);
	m_pHitTrans->RenderGimozo();
}

void cBasilisk::Damage(float fDamage)
{
	if (m_state != DMG && m_state != DIE)
	{
		m_state = DMG;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterOther(m_strName, "WAIT");
		m_fHP -= fDamage;
	}
	else if (m_state == DIE || m_state == DMG)
	{
		return;
	}

	if (m_fHP <= FEPSILON)
	{
		m_fHP = 0.0f;
		m_state = DIE;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterHold(m_strName);
		m_fDeadTime = 0;
		return;
	}
}

void cBasilisk::MoveToPlayer()
{
	//레이 세팅
	D3DXVECTOR3 currentPos = pTransform->GetWorldPosition();
	Ray ray;
	ray.direction = D3DXVECTOR3(0, -1, 0);
	ray.origin = currentPos;
	ray.origin.y += 3;


	//거리를 구한다. / 플레이어와 몬스터의 거리
	D3DXVECTOR3 dirToTarget = m_pPlayer->pTransform->GetWorldPosition() - currentPos;
	float dist = D3DXVec3Length(&dirToTarget);
	dirToTarget.y = 0;


	//방향을 구한다.
	D3DXVec3Normalize(&dirToTarget, &dirToTarget);
	dirToTarget.y = 0;
	D3DXVECTOR3 forward = pTransform->GetForward();
	forward.y = 0;
	D3DXVec3Normalize(&forward, &forward);

	float angle = acosf(D3DXVec3Dot(&forward, &dirToTarget));
	if (angle >= 160 * ONE_RAD)
	{
		pTransform->RotateSelf(0, 30 * ONE_RAD, 0);
	}

	D3DXVECTOR3 lerp = pTransform->GetForward();
	D3DXVec3Lerp(&lerp, &lerp, &dirToTarget, 0.2);
	pTransform->LookDirection(lerp, pTransform->GetUp());


	//이동량
	float deltaMove = 8.0f * TIME_MGR->GetFrameDeltaSec();
	float t = Clamp01(deltaMove / dist);

	//현재 위치에서 웨이 포인트로 보간된 위치값을 레이에 넣는다.
	ray.origin = VecLerp(currentPos, m_pPlayer->pTransform->GetWorldPosition(), t);
	ray.origin.y += 3;	//머리 위에 붙인다.


	D3DXVECTOR3 pos;
	//레이랑 터레인 체크하자
	if (pTerrain->IsIntersectRay(&pos, &ray))
	{
		pTransform->SetWorldPosition(pos);
		currentPos = pos;
	}

	// 레이랑 케릭터 거리가 멀어지면 레이가 더이상 넘어가지 못하게 만든다.
	float rayCheckDis = D3DXVec3Length(&(ray.origin - currentPos));
	if (rayCheckDis > t + 0.01f) // 상수 값은 속력 보다 조금 높은 값.
	{
		ray.origin = currentPos;
		ray.origin.y += 3;
	}
}

void cBasilisk::Attack01(float timeDelta)
{
	if (m_state != ATK_01)
	{
		m_state = ATK_01;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterOther(m_strName, "WAIT");

		m_bHit = true;
		m_fAtkTime = 0;
		return;
	}

	m_fAtkTime += timeDelta;
	if (m_fAtkTime > 0.8f && m_bHit == true)
	{
		//피격 판정 + 플레이어에게 데미지 전달
		if (PHYSICS_MGR->IsOverlap(m_pHitTrans, &m_pHitBound, m_pPlayer->pTransform, &m_pPlayer->BoundBox))
		{
			LOG_MGR->AddLog("때린다");
			m_pPlayer->Damage(100);
			m_fAtkTime = 0;
			m_bHit = false;
		}
	}
}

void cBasilisk::Attack02(float timeDelta)
{
	if (m_state != ATK_02)
	{
		m_state = ATK_02;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterOther(m_strName, "WAIT");

		m_bHit = true;
		m_fAtkTime = 0;
		return;
	}

	m_fAtkTime += timeDelta;
	if (m_fAtkTime > 0.8f && m_bHit == true)
	{
		//피격 판정 + 플레이어에게 데미지 전달
		if (PHYSICS_MGR->IsOverlap(m_pHitTrans, &m_pHitBound, m_pPlayer->pTransform, &m_pPlayer->BoundBox))
		{
			LOG_MGR->AddLog("때린다");
			m_pPlayer->Damage(150);
			m_fAtkTime = 0;
			m_bHit = false;
			//어택2를 사용했다.
			m_bHit2 = true;
		}
	}
}

void cBasilisk::SetAniState()
{
	string aniName = pSkinned->GetNowPlayingAni();
	if (strcmp(aniName.c_str(), "IDLE") == 0)
	{
		m_state = IDLE;
		m_strName = MyUtil::SetAnimation(m_state);
	}
	else if (strcmp(aniName.c_str(), "WAIT") == 0)
	{
		m_state = WAIT;
		m_strName = MyUtil::SetAnimation(m_state);
		m_fAtkTime = 0;
		m_bHit = false;
	}
	else if (strcmp(aniName.c_str(), "RUN") == 0)
	{
		m_state = RUN;
		m_strName = MyUtil::SetAnimation(m_state);
	}
	else if (strcmp(aniName.c_str(), "DMG") == 0)
	{
		m_state = DMG;
		m_strName = MyUtil::SetAnimation(m_state);
		m_fAtkTime = 0;
		m_bHit = false;
	}
}
