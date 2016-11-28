#include "stdafx.h"
#include "cSkill_Thunder.h"


cSkill_Thunder::cSkill_Thunder()
{
}


cSkill_Thunder::~cSkill_Thunder()
{
}


void cSkill_Thunder::Effect_Init()
{
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.05f);
	D3DXMATRIXA16 matCorrection = matScale;


	m_snowStrom = new cQuadParticleEmitter();
	m_snowStrom->SetActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(5.0f);  //�ʹ� ũ��
	scales.push_back(5.0f);

	m_snowStrom->Init(
		100,
		5.0f,     //����Ʈ ����
		1.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		1.0f,
		D3DXVECTOR3(0, 0, 0),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(2, 0, 1),
		D3DXVECTOR3(0, 0, 0),     //ȸ����
		D3DXVECTOR3(0, 0, 0),     //��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(180 * ONE_RAD, 0, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3(180 * ONE_RAD, 90 * ONE_RAD, 0),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors, scales,
		30.0f, 30.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/thunder_1.tga"),
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
		5.0f,     //����Ʈ ����
		1.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		1.0f,
		D3DXVECTOR3(0, 1, 0),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(0, 2, 0),
		D3DXVECTOR3(0, 0.5, 0),     //�������� �߻��ϴ� �� ����
		D3DXVECTOR3(0, 0.8, 0),     //�������� �߻��ϴ� �� ��
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3(-90 * ONE_RAD, 0, 720 * ONE_RAD),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors2, scales2,
		50.0f, 50.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/darkCloud.tga"),
		true);

	m_snowStrom->StartEmission();
	m_snowStrom_under->StartEmission();


	//m_isSnowStorm = true;

}


void cSkill_Thunder::Effect_Update(float timeDelta)
{
	if (m_CastTime / 1.2 == m_CastTimeCount)
	{
		m_snowStrom_under->StopEmission();
	}

	if (m_AttackingTime - 50 == m_AttackingCount)
	{
		m_snowStrom->StopEmission();

	}


	if (m_IsCasting || m_IsAttacking)
	{
		if(m_CastTimeCount == 1)
		{
			m_snowStrom_under->pTransform->SetWorldPosition(D3DXVECTOR3(m_AttackPos.z, m_AttackPos.y + 50, m_AttackPos.z));
		}

		m_snowStrom_under->pTransform->RotateSelf(D3DXVECTOR3(0, -0.5*timeDelta, 0));
		m_snowStrom_under->Update(timeDelta);



	}


	if (m_IsAttacking)
	{

		m_snowStrom->pTransform->SetWorldPosition(m_AttackPos);
		//m_snowStrom->pTransform->RotateSelf(D3DXVECTOR3(0, -10.0*timeDelta, 0));
		m_snowStrom->Update(timeDelta);

	}

}

void cSkill_Thunder::Effect_Render()
{

	if (m_IsCasting || m_IsAttacking)
	{
		m_snowStrom_under->Render();
	}

	if (m_IsAttacking)
	{
		m_snowStrom->Render();

	}

}