#include "stdafx.h"
#include "cSkill_MagicShild.h"


cSkill_MagicShild::cSkill_MagicShild()
{
}


cSkill_MagicShild::~cSkill_MagicShild()
{
	

}


void cSkill_MagicShild::Effect_Init()
{
	SOUND_MGR->addSound("mage_magicShild", "../Resources/Sound/������_����_����.ogg", false, false);
	SOUND_MGR->addSound("mage_magicShild_se", "../Resources/Sound/������_����.ogg", false, false);

	m_magicShild = new cQuadParticleEmitter();
	m_magicShild->SetActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(4.0f);  //�ʹ� ũ��
	scales.push_back(4.0f);

	m_magicShild->Init(
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
		2.0f/2, 2.0f/2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicShild.tga"),
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
		2.0f/2, 2.0f/2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicAura.tga"),
		true);

	m_magicShild->StartEmission();
	m_snowStrom_under->StartEmission();
}

void cSkill_MagicShild::Effect_Update(float timeDelta)
{
	if (m_BuffCount == 1)
	{
		SOUND_MGR->play("mage_magicShild", 0.8f);
		SOUND_MGR->play("mage_magicShild_se", 0.8f);
	}



	if (m_IsInBuff)
	{
		m_magicShild->Update(timeDelta);
		m_magicShild->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_magicShild->pTransform->SetWorldPosition(pTransform->GetWorldPosition().x, pTransform->GetWorldPosition().y + 1, pTransform->GetWorldPosition().z);
		m_snowStrom_under->Update(timeDelta);
		m_snowStrom_under->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_snowStrom_under->pTransform->SetWorldPosition(pTransform->GetWorldPosition().x, pTransform->GetWorldPosition().y, pTransform->GetWorldPosition().z);
		m_snowStrom_under->pTransform->RotateSelf(D3DXVECTOR3(0, 5.0f, 0));
	}



}

void cSkill_MagicShild::Effect_Render()
{

	if (m_IsInBuff)
	{
		m_magicShild->Render();
		m_snowStrom_under->Render();
	}
}