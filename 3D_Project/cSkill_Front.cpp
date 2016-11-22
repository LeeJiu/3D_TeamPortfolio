#include "stdafx.h"
#include "cSkill_Front.h"


cSkill_Front::cSkill_Front()
{
}


cSkill_Front::~cSkill_Front()
{
}

void cSkill_Front::BaseObjectEnable(D3DXVECTOR3 casterWorldPos, float maxDistance, float maxWidth, int castTime, int attackingTime, int coolTime)
{
	m_IsSelect = false;   //���� �����ϴ���
	m_IsCasting = false;  //ĳ���� �����ϴ� ��
	m_IsAttacking = false;  //���� �����ϴ� ��
	m_IsCoolTime = false;   // ��Ÿ���� ���� �� - �̋� ������ false�� �ٲ�����

	m_CasterWorldPos = casterWorldPos;
	m_MaxDistance = maxDistance;  //�ִ� ��Ÿ� ����
	m_MaxWidth = maxWidth;

	m_CastTimeCount = 0;
	m_CastTime = castTime;

	m_CoolTimeCount = 0;
	m_CoolTime = coolTime;

	m_AttackingCount = 0;
	m_AttackingTime = attackingTime;


	pTransform->SetWorldPosition(m_CasterWorldPos);
	m_BoundBox.SetBound(&pTransform->GetWorldPosition(), &D3DXVECTOR3(m_MaxWidth, 10, m_MaxDistance));


	// ���� ����Ʈ - ������
	m_CastEfc = new cQuadParticleEmitter();
	m_CastEfc->SetActive(true);

	VEC_COLOR colors3;
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales3;
	scales3.push_back(1.5f);  //�ʹ� ũ��
	scales3.push_back(1.5f);


	m_CastEfc->Init(
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
		colors3, scales3,
		1, 1,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/front_effect.tga"),
		true);


	m_CastEfc->pTransform->Scaling(D3DXVECTOR3( m_MaxWidth, 1, m_MaxDistance));

	m_CastEfc->StartEmission();


}


void cSkill_Front::BaseObjectUpdate(float timeDelta, D3DXVECTOR3 casterWorldPos, D3DXVECTOR3 mousePos)
{

	m_CasterWorldPos = casterWorldPos;
	m_LookDir = mousePos;


	if (m_IsCasting)  //ĳ������ ���۵Ǹ�
	{
		LOG_MGR->AddLog("ĳ���ý���");
		m_IsSelect = false;
		m_CastTimeCount++;

		if (m_CastTimeCount == m_CastTime) //ĳ������ ������ 
		{
			m_IsCasting = false;
			m_IsAttacking = true;
			m_IsCoolTime = true; //��Ÿ�ӵ��⸦ �����սô�
			m_AttackPos = m_LookDir;

		}

	}

	if (m_IsAttacking)
	{
		m_IsCasting = false;
		m_AttackingCount++;

		if (m_AttackingCount == m_AttackingTime) //�����ð��� ������
		{

			m_IsAttacking = false;
			LOG_MGR->AddLog("��ų��");
		}

	}



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
			m_CastEfc->Update(timeDelta);
			pTransform->SetWorldPosition(D3DXVECTOR3(0,0,0));
			pTransform->SetWorldPosition(D3DXVECTOR3(m_CasterWorldPos.x, 0, m_CasterWorldPos.z));
			pTransform->LookPosition(D3DXVECTOR3(m_LookDir.x, 0, m_LookDir.z), 90 * ONE_RAD);
			//m_BoundBox.SetBound(&pTransform->GetWorldPosition(), &D3DXVECTOR3(m_MaxWidth, 10, m_MaxDistance));
			m_CastEfc->pTransform->SetWorldPosition(D3DXVECTOR3(m_CasterWorldPos.x, 0, m_CasterWorldPos.z));
			m_CastEfc->pTransform->LookPosition(D3DXVECTOR3(m_LookDir.x, 0, m_LookDir.z), 90 * ONE_RAD);
	
			//m_CastEfc->pTransform->LookPosition(m_LookDir, 180 * ONE_RAD);
			D3DXVECTOR3 selectMax = pTransform->GetWorldPosition() - m_CasterWorldPos;

	
			if (KEY_MGR->IsOnceDown(VK_LBUTTON))
			{
				LOG_MGR->AddLog("��������");
				m_IsCasting = true;
				m_IsSelect = false;

			}
		
		}
	}



}

void cSkill_Front::BaseObjectRender()
{
	D3DXVECTOR3 selectMax = pTransform->GetWorldPosition() - m_CasterWorldPos;


	if (m_IsSelect)
	{
		m_CastEfc->Render();
		m_BoundBox.RenderGizmo(pTransform);

	

	}
}

void cSkill_Front::SelectSkill()
{
	m_IsSelect = true;
	m_CastTimeCount = 0;
	m_CoolTimeCount = 0;
	m_AttackingCount = 0;
}//UI�� ��ų�� ���콺 ���� ������ �ҷ�����

void cSkill_Front::StartCasting()
{
	m_IsCasting = true;
	m_CastTimeCount = 0;
	m_CoolTimeCount = 0;
	m_AttackingCount = 0;
}//��ų�� ����Ѵ� ��ý��� ��ų�� �� �Լ��� �ҷ�����