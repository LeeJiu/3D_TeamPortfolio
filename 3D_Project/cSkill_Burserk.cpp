#include "stdafx.h"
#include "cSkill_Burserk.h"


cSkill_Burserk::cSkill_Burserk()
{
}


cSkill_Burserk::~cSkill_Burserk()
{
}


void cSkill_Burserk::Effect_Init()
{
	m_burserking = new cQuadParticleEmitter();
	m_burserking->SetActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(4.0f);  //�ʹ� ũ��
	scales.push_back(4.0f);

	m_burserking->Init(
		10,
		30.0f,     //����Ʈ ����
		1.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		5.0f,
		D3DXVECTOR3(0, 0, 0),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),     //ȸ����
		D3DXVECTOR3(0, 0, 0),     //��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3(0, 180 * ONE_RAD, 0),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors, scales,
		2.0f / 2, 2.0f / 2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicShild.tga"),
		true);

	m_burserking_under = new cQuadParticleEmitter();
	m_burserking_under->SetActive(true);


	VEC_COLOR colors2;
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales2;
	scales2.push_back(3.0f);  //�ʹ� ũ��
	scales2.push_back(3.0f);

	m_burserking_under->Init(
		100,
		5.0f,     //����Ʈ ����
		1.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		1.0f,
		D3DXVECTOR3(0, 1, 0),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(0, 5, 0),
		D3DXVECTOR3(0, 0.5, 0),     //�������� �߻��ϴ� �� ����
		D3DXVECTOR3(0, 0.8, 0),     //�������� �߻��ϴ� �� ��
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3(-90 * ONE_RAD, 0, 720 * ONE_RAD),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors2, scales2,
		2.0f / 2, 2.0f / 2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicAura.tga"),
		true);

	m_burserking->StartEmission();
	m_burserking_under->StartEmission();
}

void cSkill_Burserk::Effect_Update(float timeDelta)
{
	if (m_IsInBuff)
	{
		m_burserking->Update(timeDelta);
		m_burserking->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_burserking->pTransform->SetWorldPosition(pTransform->GetWorldPosition().x, pTransform->GetWorldPosition().y + 1, pTransform->GetWorldPosition().z);
		m_burserking_under->Update(timeDelta);
		m_burserking_under->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_burserking_under->pTransform->SetWorldPosition(pTransform->GetWorldPosition().x, pTransform->GetWorldPosition().y, pTransform->GetWorldPosition().z);
		m_burserking_under->pTransform->RotateSelf(D3DXVECTOR3(0, 5.0f, 0));
	}
}

void cSkill_Burserk::Effect_Render()
{
	if (m_IsInBuff)
	{
		m_burserking->Render();
		m_burserking_under->Render();
	}
}