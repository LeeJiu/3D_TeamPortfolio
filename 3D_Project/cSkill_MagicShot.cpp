#include "stdafx.h"
#include "cSkill_MagicShot.h"


cSkill_MagicShot::cSkill_MagicShot()
{
}


cSkill_MagicShot::~cSkill_MagicShot()
{
}



void cSkill_MagicShot::Effect_Init()
{
	m_magicATK = new cQuadParticleEmitter;
	m_magicATK->SetActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(1.5f);  //�ʹ� ũ��
	scales.push_back(2.5f);

	m_magicATK->Init(
		100,
		10.0f,     //����Ʈ ����
		0.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		0.5f,
		D3DXVECTOR3(0, 0, 0),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),     //ȸ����
		D3DXVECTOR3(0, 0, 0),     //��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 180 * ONE_RAD, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3(180 * ONE_RAD, 0, 0),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors, scales,
		5.0f /2, 7.5f /2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicalATK2.tga"),
		true);

	m_magicATK->StartEmission();


	//2�� �����ڽ�

	m_magicATK2 = new cQuadParticleEmitter;
	m_magicATK2->SetActive(true);

	VEC_COLOR colors2;
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales2;
	scales2.push_back(1.5f);  //�ʹ� ũ��
	scales2.push_back(2.5f);

	m_magicATK2->Init(
		100,
		20.0f,     //����Ʈ ����
		0.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		0.5f,
		D3DXVECTOR3(0, 0, 0),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),     //ȸ����
		D3DXVECTOR3(0, 0, 0),     //��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 180 * ONE_RAD, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3(180 * ONE_RAD, 0, 0),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors2, scales2,
		10.0f / 2, 10.5f / 2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicalATK.tga"),
		true);

	m_magicATK2->StartEmission();

	m_magicATK3 = new cQuadParticleEmitter;
	m_magicATK3->SetActive(true);

	VEC_COLOR colors3;
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales3;
	scales3.push_back(1.5f);  //�ʹ� ũ��
	scales3.push_back(2.5f);

	m_magicATK3->Init(
		100,
		10.0f,     //����Ʈ ����
		0.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		0.5f,
		D3DXVECTOR3(0, 0, 0),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),     //ȸ����
		D3DXVECTOR3(0, 0, 0),     //��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 180 * ONE_RAD, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3(180 * ONE_RAD, 0, 0),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors3, scales3,
		3.5f / 2, 5.5f / 2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicalATK2.tga"),
		true);

	m_magicATK3->StartEmission();



}

void cSkill_MagicShot::Effect_Update(float timeDelta)
{

	if (m_AttackingCount == 1)
	{
		m_magicATK2->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_magicATK3->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
	}

	if (m_IsAttacking || m_IsShot)
	{
		m_magicATK->Update(timeDelta);
		m_magicATK->pTransform->SetWorldPosition(pTransform->GetWorldPosition());

		float followSpeed = 7.0f;
		m_magicATK2->Update(timeDelta);
		m_magicATK2->pTransform->Interpolate(*m_magicATK2->pTransform, *pTransform, followSpeed * timeDelta);

		m_magicATK3->Update(timeDelta);
		m_magicATK3->pTransform->Interpolate(*m_magicATK3->pTransform, *m_magicATK2->pTransform, followSpeed * timeDelta);

		
		//m_magicATK->pTransform->RotateSelf(D3DXVECTOR3(0.5f, 0, 0));


	}



}

void cSkill_MagicShot::Effect_Render()
{
	if (m_IsAttacking || m_IsShot)
	{
		if (m_IsHit)
		{
			m_magicATK2->Render();
		}
		m_magicATK->Render();
		m_magicATK3->Render();

		if (m_AttackingCount == m_AttackingTime / 1.5f)
		{
			//m_magicATK->StopEmission();
		}
	}



}