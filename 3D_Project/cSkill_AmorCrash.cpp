#include "stdafx.h"
#include "cSkill_AmorCrash.h"


cSkill_AmorCrash::cSkill_AmorCrash()
{
}


cSkill_AmorCrash::~cSkill_AmorCrash()
{
}


void cSkill_AmorCrash::Effect_Init()
{
	m_snowStrom = new cQuadParticleEmitter();
	m_snowStrom->SetActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(1.0f);  //�ʹ� ũ��
	scales.push_back(5.0f);

	m_snowStrom->Init(
		100,
		100.0f,     //����Ʈ ����
		5.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		5.5f,
		D3DXVECTOR3(0, 1, 0),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(0, 4, 0),
		D3DXVECTOR3(0, 0, 0),     //ȸ����
		D3DXVECTOR3(0, 0, 0),     //��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 90 * ONE_RAD, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3(90 * ONE_RAD, 0, 0),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors, scales,
		0.0f, 5.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/blood.tga"),
		true);


	m_snowStrom_under = new cQuadParticleEmitter();
	m_snowStrom_under->SetActive(true);


	VEC_COLOR colors2;
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales2;
	scales2.push_back(3.0f);  //�ʹ� ũ��
	scales2.push_back(3.0f);

	m_snowStrom_under->Init(
		100,
		20.0f,     //����Ʈ ����
		1.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		1.0f,
		D3DXVECTOR3(0, 0, 0),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0.5, 0),     //�������� �߻��ϴ� �� ����
		D3DXVECTOR3(0, 0.8, 0),     //�������� �߻��ϴ� �� ��
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3(-90 * ONE_RAD, 0, 720 * ONE_RAD),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors2, scales2,
		0.0f, 3.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/blood.tga"),
		true);


	m_chargeEfc = new cQuadParticleEmitter();
	m_chargeEfc->SetActive(true);

	VEC_COLOR colors3;
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales3;
	scales3.push_back(1.0f);  //�ʹ� ũ��
	scales3.push_back(5.0f);

	m_chargeEfc->Init(
		10,
		30.0f,     //����Ʈ ����
		1.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		1.0f,
		D3DXVECTOR3(0, 0, 0),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(0, 1, 0),
		D3DXVECTOR3(0, 0, 0),     //ȸ����
		D3DXVECTOR3(0, 0, 0),     //��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3(0, 180 * ONE_RAD, 0),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors, scales,
		0.0f / 2, 5.0f / 2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/charge.tga"),
		true);

	m_chargeEfc_under = new cQuadParticleEmitter();
	m_chargeEfc_under->SetActive(true);

	VEC_COLOR colors4;
	colors4.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors4.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors4.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales4;
	scales4.push_back(1.0f);  //�ʹ� ũ��
	scales4.push_back(5.0f);

	m_chargeEfc_under->Init(
		100,
		5.0f,     //����Ʈ ����
		1.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		1.0f,
		D3DXVECTOR3(0, 0, 0),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0.5, 0),     //�������� �߻��ϴ� �� ����
		D3DXVECTOR3(0, 0.8, 0),     //�������� �߻��ϴ� �� ��
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3(-90 * ONE_RAD, 0, 720 * ONE_RAD),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors2, scales2,
		0.0f / 2, 5.0f / 2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/chargeStorm.tga"),
		true);

	m_snowStrom->StartEmission();
	m_snowStrom_under->StartEmission();
	m_chargeEfc->StartEmission();
	m_chargeEfc_under->StartEmission();


}

void cSkill_AmorCrash::Effect_Update(float timeDelta)
{
	if (m_CastTime / 1.2 == m_CastTimeCount)
	{
		//m_snowStrom_under->StopEmission();
		//m_snow->StopEmission();
	}

	if (m_AttackingTime / 0.9 == m_AttackingCount)
	{
		m_snowStrom->StopEmission();

	}


	if (m_IsSelect)
	{
		m_chargeEfc->Update(timeDelta);
		m_chargeEfc_under->Update(timeDelta);
		m_chargeEfc->pTransform->SetWorldPosition(m_CasterWorldPos.x, m_CasterWorldPos.y + 1, m_CasterWorldPos.z);
		m_chargeEfc_under->pTransform->SetWorldPosition(m_CasterWorldPos);
		m_chargeEfc_under->pTransform->RotateSelf(D3DXVECTOR3(0, -5.0f, 0));

	}


	if (m_IsAttacking)
	{
		m_snowStrom_under->pTransform->SetWorldPosition(m_AttackPos);
		m_snowStrom_under->Update(timeDelta);
		m_snowStrom->pTransform->SetWorldPosition(m_AttackPos);
		m_snowStrom->Update(timeDelta);

	}
}


void cSkill_AmorCrash::Effect_Render()
{
	if (m_IsSelect)
	{
		
		m_chargeEfc_under->Render();
		m_chargeEfc->Render();
	}

	if (m_IsAttacking)
	{
		m_snowStrom_under->Render();

		m_snowStrom->Render();


	}

}