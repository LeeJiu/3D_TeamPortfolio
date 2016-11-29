#include "stdafx.h"
#include "cSkill_Round.h"


cSkill_Round::cSkill_Round()
{
}


cSkill_Round::~cSkill_Round()
{

}


void cSkill_Round::BaseObjectEnable(D3DXVECTOR3  casterWorldPos, float surroundLength, int maxDistance, int castTime, int attackingTime, int coolTime)
{
	m_IsSelect = false;   //���� �����ϴ���
	m_IsCasting = false;  //ĳ���� �����ϴ� ��
	m_IsAttacking = false;  //���� �����ϴ� ��
	m_IsCoolTime = false;   // ��Ÿ���� ���� �� - �̋� ������ false�� �ٲ�����

	m_MaxDistance = maxDistance;  //�ִ� ��Ÿ� ����

	m_CasterWorldPos = casterWorldPos;

	m_SurroundLength = surroundLength;

	m_CastTimeCount = 0;
	m_CastTime = castTime;

	m_CoolTimeCount = 0;
	m_CoolTime = coolTime;

	m_AttackingCount = 0;
	m_AttackingTime = attackingTime;

	pTransform->SetWorldPosition(m_CasterWorldPos);


	// ���� ����Ʈ 
	m_CircleEfc = new cQuadParticleEmitter();  
	m_CircleEfc->SetActive(true);

	m_BoundSphere.SetBound(&pTransform->GetWorldPosition(), &D3DXVECTOR3(m_SurroundLength, 0, m_SurroundLength));

	VEC_COLOR colors2;
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales2;
	scales2.push_back(3.0f);  //�ʹ� ũ��
	scales2.push_back(3.0f);

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
		m_SurroundLength, m_SurroundLength,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/surround_effect.tga"),
		true);

	m_CircleEfc->StartEmission();


	// ���� ����Ʈ  - ������
	m_CastEfc = new cQuadParticleEmitter();
	m_CastEfc->SetActive(true);

	VEC_COLOR colors3;
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales3;
	scales3.push_back(3.0f);  //�ʹ� ũ��
	scales3.push_back(3.0f);


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
		m_SurroundLength, m_SurroundLength,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/surround_effect_false.tga"),
		true);

	m_CastEfc->StartEmission();

	VEC_COLOR colors4;
	colors4.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors4.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors4.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales4;
	scales4.push_back(3.0f);  //�ʹ� ũ��
	scales4.push_back(3.0f);


	//��Ÿ� ǥ�� ����
	m_SurroundEfc = new cQuadParticleEmitter();
	m_SurroundEfc->SetActive(true);


	m_SurroundEfc->Init(
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
		colors4, scales4,
		maxDistance / 2 , maxDistance / 2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/surround_shot_effect.tga"),
		true);

	m_SurroundEfc->StartEmission();


}

void cSkill_Round::BaseObjectUpdate(float timeDelta, D3DXVECTOR3 casterWorldPos, D3DXVECTOR3 mousePos)
{
	m_CasterWorldPos = casterWorldPos;
	m_MousePos = mousePos;


	if (m_IsCasting)  //ĳ������ ���۵Ǹ�
	{
	//	LOG_MGR->AddLog("ĳ���ý���");
		m_IsSelect = false;
		m_CastTimeCount++;

		if (m_CastTimeCount == 1) m_AttackPos = m_MousePos; //ĳ���� ���۽� ���콺 Ŭ�� ��ġ�� �� �� �ֵ���

		if (m_CastTimeCount == m_CastTime) //ĳ������ ������ 
		{
			m_IsCasting = false;
			m_IsAttacking = true;
			m_IsCoolTime = true; //��Ÿ�ӵ��⸦ �����սô�
			

		}

	}

	if (m_IsAttacking)
	{
		m_IsCasting = false;
		m_AttackingCount++;

		if (m_AttackingCount == m_AttackingTime) //�����ð��� ������
		{

			m_IsAttacking = false;
		//	LOG_MGR->AddLog("��ų��");
		}

	}

	

	if (m_IsCoolTime) //��Ÿ�� ���̸� 
	{
	//	LOG_MGR->AddLog("��Ÿ�� ���Դϴ�");

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
			m_SurroundEfc->Update(timeDelta);
			m_SurroundEfc->pTransform->SetWorldPosition(m_CasterWorldPos);
			pTransform->SetWorldPosition(m_MousePos);
			D3DXVECTOR3 selectMax = pTransform->GetWorldPosition() - m_CasterWorldPos;

			if (D3DXVec3Length(&selectMax) < m_MaxDistance)
			{
			//	LOG_MGR->AddLog("���� ����");
				m_CircleEfc->Update(timeDelta);
				m_CircleEfc->pTransform->SetWorldPosition(m_MousePos);

				//Ŭ���� �� ĳ������ ���۵ǵ���

				if (KEY_MGR->IsOnceDown(VK_LBUTTON))
				{
				//	LOG_MGR->AddLog("��������");
					m_IsCasting = true;
					m_IsSelect = false;
					
				}
			}
			else
			{
			//	LOG_MGR->AddLog("���� �Ұ���");
				m_CastEfc->Update(timeDelta);
				m_CastEfc->pTransform->SetWorldPosition(m_MousePos);
			}

		}
	}


	
	




}

void cSkill_Round::BaseObjectRender()
{

	D3DXVECTOR3 selectMax = pTransform->GetWorldPosition() - m_CasterWorldPos;


	if (m_IsSelect)
	{
		m_SurroundEfc->Render();

		if (D3DXVec3Length(&selectMax) < m_MaxDistance)
		{
			m_CircleEfc->Render();
			m_BoundSphere.RenderGizmo(pTransform);
		}
		else
		{
			m_CastEfc->Render();
			m_BoundSphere.RenderGizmo(pTransform);
		}

	}


}


void cSkill_Round::SelectSkill()
{

	m_IsSelect = true;
	m_CastTimeCount = 0;
	m_CoolTimeCount = 0;
	m_AttackingCount = 0;

}

void cSkill_Round::StartCasting()
{
	m_IsCasting = true;
	m_CastTimeCount = 0;
	m_CoolTimeCount = 0;
	m_AttackingCount = 0;
}

