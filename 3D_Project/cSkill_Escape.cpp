#include "stdafx.h"
#include "cSkill_Escape.h"


cSkill_Escape::cSkill_Escape()
{
}


cSkill_Escape::~cSkill_Escape()
{
}

void cSkill_Escape::BaseObjectEnable(D3DXVECTOR3  casterWorldPos, float moveLength, int castTime, int buffCount, int coolTime)
{
	m_IsSelect = false;
	m_IsCasting = false;
	m_IsInBuff = false;
	m_IsCoolTime = false;

	m_MoveLength = moveLength;
	m_CasterWorldPos = casterWorldPos;

	//pTransform->LookDirection(D3DXVECTOR3(0, 0, 1), D3DXVECTOR3(0, 1, 0));
	pTransform->SetWorldPosition(m_CasterWorldPos);  // Ʈ������ ��ǥ 
	//pTransform->LookDirection(D3DXVECTOR3(0, 0, -1), 90 * ONE_RAD);

	m_CastTimeCount = 0;
	m_CastTime = castTime;

	m_CoolTimeCount = 0;
	m_CoolTime = coolTime;

	m_BuffCount = 0;
	m_BuffTime = buffCount;


	// ���� ����Ʈ 
	m_CircleEfc = new cQuadParticleEmitter();
	m_CircleEfc->SetActive(true);

	VEC_COLOR colors2;
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales2;
	scales2.push_back(1.0f);  //�ʹ� ũ��
	scales2.push_back(1.0f);

	m_CircleEfc->Init(
		30,
		2.0f,     //����Ʈ ����
		1.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		1.0f,
		D3DXVECTOR3(0, 1, 0),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(0, 1, 0),
		D3DXVECTOR3(0, 0, 0),     //�������� �߻��ϴ� �� ����
		D3DXVECTOR3(0, 0, 0),     //�������� �߻��ϴ� �� ��
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors2, scales2,
		3.0f, 3.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/surround_effect.tga"),
		true);

	m_CircleEfc->StartEmission();
}


void cSkill_Escape::BaseObjectUpdate(float timeDelta, D3DXVECTOR3 CasterWorldPos, D3DXVECTOR3 lookDir)
{
	m_CasterWorldPos = CasterWorldPos;
	m_LookDir = lookDir;

	if (m_IsCoolTime) //��Ÿ�� ���̸� 
	{
		LOG_MGR->AddLog("��Ÿ�� ���Դϴ�");

		m_CoolTimeCount++; //��Ÿ���� ���������

		if (m_CoolTimeCount == m_CoolTime)
		{
			m_IsCoolTime = false;
		}

	}
	else //��Ÿ�� ���� �ƴϸ�
	{
		if (m_IsSelect)
		{


		}
	}




	if (m_IsCasting)
	{
		m_IsSelect = false;
		m_CastTimeCount++;

		if (m_CastTimeCount == m_CastTime)
		{
			pTransform->SetWorldPosition(CasterWorldPos);
			pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, m_MoveLength));
		}

		

		if (m_CastTimeCount == m_CastTime) //ĳ������ ������ 
		{
			m_IsCasting = false;
			m_IsInBuff = true;
			m_IsCoolTime = true; //��Ÿ�ӵ��⸦ �����սô�

		}

	}

	if (m_IsInBuff)
	{
		m_IsCasting = false;
		m_BuffCount++;
		pTransform->LookDirection(m_LookDir, D3DXVECTOR3(0,1,0));
		pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_CircleEfc->Update(timeDelta);
		m_CircleEfc->pTransform->SetWorldPosition(pTransform->GetWorldPosition());

		if (m_BuffCount == m_BuffTime) //�����ð��� ������
		{

			m_IsInBuff = false;
			LOG_MGR->AddLog("���� ��");
		}

	}

}


void cSkill_Escape::BaseObjectRender()
{
	if (m_IsCasting || m_IsInBuff)
	{
		m_CircleEfc->Render();
	}
}

void cSkill_Escape::SelectSkill()
{
	m_IsSelect = true;
	m_CastTimeCount = 0;
	m_CoolTimeCount = 0;
	m_BuffCount = 0;

}//UI�� ��ų�� ���콺 ���� ������ �ҷ�����

void cSkill_Escape::StartCasting()
{
	m_IsCasting = true;
	m_CastTimeCount = 0;
	m_CoolTimeCount = 0;
	m_BuffCount = 0;
}//��ų�� ����Ѵ� ��ý��� ��ų�� �� �Լ��� �ҷ�����

