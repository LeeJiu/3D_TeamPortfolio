#include "stdafx.h"
#include "cDragon.h"
#include "cPlayer.h"


cDragon::cDragon()
{
	m_collCount = COLLISION;
	m_fHP = 30000.f;
}


cDragon::~cDragon()
{
	for (int i = 1; i < COLLISION; i++)
	{
		SAFE_DELETE(m_boneTrans[i]);
	}

	for (int i = 1; i < 5; i++)
	{
		SAFE_DELETE(collTrans[i]);
	}
}

void cDragon::BaseObjectEnable()
{
	m_boneTrans[0] = pTransform;     // pTrans 값을 0 번에 입력
	collTrans[0] = pTransform;

	// 뼈에 붙일 트렌스 초기화
	for (int i = 1; i < COLLISION; i++)
	{
		m_boneTrans[i] = new cTransform; //동적 할당 되있는거. 
	}

	for (int i = 1; i < 5; i++)
	{
		collTrans[i] = new cTransform; //동적 할당 되있는거. 
	}
	//=================== 초기화 ================
	//pTransform , 몬스터 움직일때 쓰는 trans 

	pSkinned->AddBoneTransform("Bip01-HeadNub", m_boneTrans[1]);
	pSkinned->AddBoneTransform("Bip01-L-Hand_Bone", m_boneTrans[2]);
	pSkinned->AddBoneTransform("Bip01-R-Hand_Bone", m_boneTrans[3]);

	//0몸통
	m_Bound[0].Init(D3DXVECTOR3(-4, 0, -4), D3DXVECTOR3(4, 8, 4.5));
	//머리
	m_Bound[1].Init(D3DXVECTOR3(-2, -1, -2), D3DXVECTOR3(0, 1, 0.5));
	//왼팔
	m_Bound[2].Init(D3DXVECTOR3(0, -1, -1), D3DXVECTOR3(2, 1, 1));
	//오른팔
	m_Bound[3].Init(D3DXVECTOR3(0, -1, -1), D3DXVECTOR3(2, 1, 1));

	//처음 시작시 플레이 애니메이션
	this->pSkinned->Play("Spawn", 0.3f);
	this->pSkinned->Stop();
	collPosUpdate();
	// 스폰 지역 월드 센터 값 
	spone.worldCenter = pTransform->GetWorldPosition();
	spone.radius = 20.f;
}

void cDragon::BaseObjectUpdate(float timeDelta)
{
	// 전투 범위에 들어오면 
	if (battleRange() == true) 
	{
	collPosUpdate();

	}
	else
	{

	}
	



	//=================== 업데이트 ==============
	if (KEY_MGR->IsStayDown(VK_LCONTROL))
	{
		if (KEY_MGR->IsOnceDown('1'))
			this->pSkinned->Play("None_1", 0.3f);

		if (KEY_MGR->IsOnceDown('2'))
			this->pSkinned->Play("SK_Fring_03", 0.3f);

		if (KEY_MGR->IsOnceDown('3'))
			this->pSkinned->Play("Spawn", 0.3f);

		if (KEY_MGR->IsOnceDown(VK_SPACE))
			this->pSkinned->PlayOneShot("Walk_F", 0.3, 0.3);

		if (KEY_MGR->IsOnceDown('4'))
			this->pSkinned->Play("SK_Firing_02", 0.3f);
		if (KEY_MGR->IsOnceDown('5'))
			this->pSkinned->Play("SK_Firing_01", 0.3f);
		if (KEY_MGR->IsOnceDown('6'))
			this->pSkinned->Play("Run_F", 0.3f);
		if (KEY_MGR->IsOnceDown('7'))
			this->pSkinned->Play("Passout", 0.3f);
		if (KEY_MGR->IsOnceDown('8'))
			this->pSkinned->Play("IDLE_P_01", 0.3f);
		if (KEY_MGR->IsOnceDown('9'))
			this->pSkinned->Play("IDLE_C", 0.3f);
		if (KEY_MGR->IsOnceDown('0'))
			this->pSkinned->Play("DMG_F", 0.3f);
		if (KEY_MGR->IsOnceDown('Z'))
			this->pSkinned->Play("DMG_B", 0.3f);
		if (KEY_MGR->IsOnceDown('X'))
			this->pSkinned->Play("ATK_02", 0.3f);
		if (KEY_MGR->IsOnceDown('C'))
			this->pSkinned->Play("ATK_01", 0.3f);

		if (KEY_MGR->IsOnceDown('V'))
			this->pSkinned->Stop();
	}
}

void cDragon::BaseObjectBoundBox()
{
	//=================== 바운드 박스 추가 ======
}

void cDragon::Damage(float fDamage)
{
	//=================== 데미지 받을 함수 ======
}
void cDragon::BaseObjectRender()
{
	//=================== 렌더 함수 =============
	//본 이름 
	// 머리 Bip01-HeadNub
	// 왼팔 Bip01-L-Hand_Bone
	// 오팔 Bip01-R-Hand_Bone
	// 오발 Bip01-R-Foot_Bone
	// 왼발 Bip01-L-Foot_Bone
	// 오날개 BN_Wing_R003,007
	// 왼날개 BN_Wing_L003,007
	pSkinned->Render(m_boneTrans[0]);
	for (int i = 0; i < COLLISION; i++)
	{
		//m_boneTrans[i]->RenderGimozo(true);

	}
	for (int i = 0; i < COLLISION; i++)
	{
		m_Bound[i].RenderGizmo(m_boneTrans[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		collTrans[i]->RenderGimozo(true);
	}
}

void cDragon::collPosUpdate()
{
	//좌표 갱신.
	//0번은 몸통 바운드 박스 기준
	m_Bound[0].GetWorldBox(m_boneTrans[0], collPos);
	collTrans[1]->SetWorldPosition(collPos[0]);
	collTrans[2]->SetWorldPosition(collPos[3]);
	collTrans[3]->SetWorldPosition(collPos[4]);
	collTrans[4]->SetWorldPosition(collPos[7]);
}

bool cDragon::battleRange()
{
	D3DXVECTOR3 Length = spone.worldCenter - m_pPlayer->pTransform->GetWorldPosition();
	float dis = D3DXVec3Length(&Length);

	if (dis < spone.radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}