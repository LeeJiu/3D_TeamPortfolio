#include "stdafx.h"
#include "cSkill_FlameRoad.h"


cSkill_FlameRoad::cSkill_FlameRoad()
{
}


cSkill_FlameRoad::~cSkill_FlameRoad()
{

}


void cSkill_FlameRoad::Effect_Init()
{
	m_flameRoad = new cQuadParticleEmitter();
	m_flameRoad->SetActive(true);


	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(1.0f);  //�ʹ� ũ��
	scales.push_back(6.0f);

	m_flameRoad->Init(
		101,
		50.0f,     //����Ʈ ����
		1.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		3.0f,
		D3DXVECTOR3(0, 1, 10),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(0, 1, 20),
		D3DXVECTOR3(0, 0, 0),     //ȸ����
		D3DXVECTOR3(0, 0, 0),     //��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(150 * ONE_RAD, 0, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3(150 * ONE_RAD, 90 * ONE_RAD, 0),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors, scales,
		1.0f, 3.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/flame.tga"),
		true);


	m_flameRoad2 = new cQuadParticleEmitter();
	m_flameRoad2->SetActive(true);


	VEC_COLOR colors2;
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales2;
	scales2.push_back(1.0f);  //�ʹ� ũ��
	scales2.push_back(4.0f);

	m_flameRoad2->Init(
		102,
		50.0f,     //����Ʈ ����
		1.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		3.0f,
		D3DXVECTOR3(0, 1, 10),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(0, 1, 20),
		D3DXVECTOR3(0, 0, 0),     //ȸ����
		D3DXVECTOR3(0, 0, 0),     //��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(150 * ONE_RAD, 0, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3(150 * ONE_RAD, 90 * ONE_RAD, 0),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors2, scales2,
		1.0f, 3.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/flame2.tga"),
		true);

	m_flameRoad3 = new cPartcleEmitter();
	m_flameRoad3->SetActive(true);

	//�迭�� 2 ���̻� 
	VEC_COLOR colors3;
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	VEC_SCALE scales3;
	scales3.push_back(0.1f);
	scales3.push_back(0.1f);

	LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
		"../Resources/Textures/Effects/flame3.tga");

	//��ƼŬ ������ ����
	m_flameRoad3->Init(
		50,				//�ִ� ��ƼŬ ��
		5.0f,				//�ʴ� ��ƼŬ �߻� ��
		7,					//�ϳ��� ��ƼŬ ���� ������ �ּҰ�
		10,					//�ϳ��� ��ƼŬ ���� ������ �ִ밪
		D3DXVECTOR3(0, 5, 10),	//��ƼŬ ���� �ӵ� �ּҰ� ( ���ñ��� )
		D3DXVECTOR3(0, 10, 20),	//��ƼŬ ���� �ӵ� �ִ밪 ( ���ñ��� )
		D3DXVECTOR3(0, 0, 0),	//��ƼŬ ���� ���� �ּҰ� ( ���ñ��� )
		D3DXVECTOR3(0, 0, 0), //��ƼŬ ���� ���� �ִ밪 ( ���ñ��� )
		colors3,				//�÷� �迭
		scales3,				//������ �迭
		1.1f,				//����ũ�� �ּҰ�
		5.2f,				//�ִ밪
		pTex,				//�ؽ���
		false);


	m_flameRoad3->EmissionType = PATICLE_EMISSION_TYPE::SPHERE_OUTLINE;
	m_flameRoad3->SphereEmissionRange = 3.0f;

}


void cSkill_FlameRoad::Effect_Update(float timeDelta)
{

	if (m_AttackingCount == 1)
	{
		m_flameRoad->StartEmission();
		m_flameRoad2->StartEmission();
		m_flameRoad3->StartEmission();
	
	}




	if (m_IsAttacking)
	{
		m_flameRoad->Update(timeDelta);
		m_flameRoad2->Update(timeDelta);
		m_flameRoad3->Update(timeDelta);
		m_flameRoad->pTransform->SetWorldPosition(m_CasterWorldPos);
		m_flameRoad->pTransform->LookDirection(pTransform->GetForward(), 90.0f * ONE_RAD);
		m_flameRoad2->pTransform->SetWorldPosition(m_CasterWorldPos);
		m_flameRoad2->pTransform->LookDirection(pTransform->GetForward(), 90.0f * ONE_RAD);
		m_flameRoad3->pTransform->SetWorldPosition(m_CasterWorldPos);
		m_flameRoad3->pTransform->LookDirection(pTransform->GetForward(), 90.0f * ONE_RAD);
	}

	if (m_AttackingCount == 180)
	{
		m_flameRoad->StopEmission();
		m_flameRoad2->StopEmission();
		m_flameRoad3->StopEmission();
	
	}

}


void cSkill_FlameRoad::Effect_Render()
{
	if (m_IsAttacking)
	{
		m_flameRoad->Render();
		m_flameRoad2->Render();
		m_flameRoad3->Render();
	}

}