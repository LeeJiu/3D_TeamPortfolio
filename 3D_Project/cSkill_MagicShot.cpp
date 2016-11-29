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
		50.0f,     //����Ʈ ����
		1.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		1.0f,
		D3DXVECTOR3(0, 0, 0),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(0, 1, -1),
		D3DXVECTOR3(0, 1, -1),     //ȸ����
		D3DXVECTOR3(1, 1, 1),     //��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(90 * ONE_RAD, 90 * ONE_RAD, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3(180 * ONE_RAD, 180 * ONE_RAD, 0),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors, scales,
		1.0f /2, 2.5f /2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicalATK.tga"),
		true);

	m_magicATK->StartEmission();
}

void cSkill_MagicShot::Effect_Update(float timeDelta)
{
	if (m_IsAttacking || m_IsShot)
	{
		m_magicATK->Update(timeDelta);
		m_magicATK->pTransform->SetWorldPosition(pTransform->GetWorldPosition());

	}



}

void cSkill_MagicShot::Effect_Render()
{
	if (m_IsAttacking || m_IsShot)
	{
		m_magicATK->Render();

		if (m_AttackingCount == m_AttackingTime / 1.5f)
		{
			m_magicATK->StopEmission();
		}
	}



}