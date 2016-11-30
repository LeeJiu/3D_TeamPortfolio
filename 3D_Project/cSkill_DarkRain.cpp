#include "stdafx.h"
#include "cSkill_DarkRain.h"


cSkill_DarkRain::cSkill_DarkRain()
{
}


cSkill_DarkRain::~cSkill_DarkRain()
{

}


void cSkill_DarkRain::Effect_Init()
{
	SOUND_MGR->addSound("mage_DarkSwarm", "../Resources/Sound/������_�ҿ뵹��_����.ogg", false, false);
	SOUND_MGR->addSound("mage_DarkSwarm_se", "../Resources/Sound/������_�ҿ뵹��2.ogg", false, false);
	SOUND_MGR->addSound("mage_DarkSwarm_se2", "../Resources/Sound/������_�ҿ뵹��.ogg", false, true);


	//D3DXMATRIXA16 matScale;
	//D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.05f);
	//D3DXMATRIXA16 matCorrection = matScale;
	//
	//
	//
	//m_lavaStone = new cXMesh_Static;
	//m_lavaStone->Init("../Resources/Textures/Effects/lavaStone.x", &matCorrection);
	//
	//m_lavaStoneTrans = new cTransform;
	//D3DXVECTOR3 lavaStoneHight(0, 20, 0);
	//m_lavaStoneTrans->SetWorldPosition(lavaStoneHight);
	//
	//m_speed = 0.5f;


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
		1.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		2.0f,
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
		2.0f, 9.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/waterDrop.tga"),
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
		9.0f, 9.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/wave.tga"),
		true);

	m_snow = new cPartcleEmitter();
	m_snow->SetActive(true);

	//�迭�� 2 ���̻� 
	VEC_COLOR colors_snow;
	colors_snow.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors_snow.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	VEC_SCALE scales_snow;
	scales_snow.push_back(0.1f);
	scales_snow.push_back(0.1f);

	LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
		"../Resources/Textures/Effects/waterDrop2.tga");

	//��ƼŬ ������ ����
	m_snow->Init(
		100,				//�ִ� ��ƼŬ ��
		40.0f,				//�ʴ� ��ƼŬ �߻� ��
		7,					//�ϳ��� ��ƼŬ ���� ������ �ּҰ�
		10,					//�ϳ��� ��ƼŬ ���� ������ �ִ밪
		D3DXVECTOR3(0, 0, 0),	//��ƼŬ ���� �ӵ� �ּҰ� ( ���ñ��� )
		D3DXVECTOR3(-10, 7, -10),	//��ƼŬ ���� �ӵ� �ִ밪 ( ���ñ��� )
		D3DXVECTOR3(0, 0, 0),	//��ƼŬ ���� ���� �ּҰ� ( ���ñ��� )
		D3DXVECTOR3(0, 0, 0), //��ƼŬ ���� ���� �ִ밪 ( ���ñ��� )
		colors_snow,				//�÷� �迭
		scales_snow,				//������ �迭
		1.1f,				//����ũ�� �ּҰ�
		30.2f,				//�ִ밪
		pTex,				//�ؽ���
		false);


	m_snow->EmissionType = PATICLE_EMISSION_TYPE::SPHERE_OUTLINE;
	m_snow->SphereEmissionRange = 3.0f;


	m_snowStrom->StartEmission();
	m_snowStrom_under->StartEmission();
	m_snow->StartEmission();

	//m_isSnowStorm = true;

}


void cSkill_DarkRain::Effect_Update(float timeDelta)
{
	if (m_CastTime / 1.2 == m_CastTimeCount)
	{
		m_snowStrom_under->StopEmission();
		m_snow->StopEmission();
	}

	if (m_CastTimeCount == 1)
	{
		SOUND_MGR->play("mage_DarkSwarm", 0.8f);
		SOUND_MGR->play("mage_DarkSwarm_se", 0.8f);
		SOUND_MGR->play("mage_DarkSwarm_se2", 0.8f);
	}

	if (m_AttackingTime - 50 == m_AttackingCount)
	{
		m_snowStrom->StopEmission();
	
	}

	if (m_AttackingTime == m_AttackingCount)
	{
		SOUND_MGR->stop("mage_DarkSwarm_se2");
	}


	if (m_IsCasting || m_IsAttacking)
	{
		m_snowStrom_under->pTransform->SetWorldPosition(m_AttackPos);
		m_snowStrom_under->pTransform->RotateSelf(D3DXVECTOR3(0, -5.0*timeDelta, 0));
		m_snowStrom_under->Update(timeDelta);

		//m_speed += 0.3f;
		//m_lavaStoneTrans->SetWorldPosition(D3DXVECTOR3(m_AttackPos.x, m_lavaStoneTrans->GetWorldPosition().y - m_speed * timeDelta, m_AttackPos.z));
		m_snow->pTransform->SetWorldPosition(m_AttackPos);//m_lavaStoneTrans->GetWorldPosition() + D3DXVECTOR3(0, 7, 0));
		m_snow->Update(timeDelta);


	}


	if (m_IsAttacking)
	{
		
		m_snowStrom->pTransform->SetWorldPosition(m_AttackPos);
		//m_snowStrom->pTransform->RotateSelf(D3DXVECTOR3(0, -10.0*timeDelta, 0));
		m_snowStrom->Update(timeDelta);
		
	}

}

void cSkill_DarkRain::Effect_Render()
{
	if (m_IsCasting || m_IsAttacking)
	{
		m_snowStrom_under->Render();

		//m_lavaStone->Render(m_lavaStoneTrans);

		m_snow->Render();
	}

	if (m_IsAttacking)
	{
		
	
		m_snowStrom->Render();
		
	
	}
}