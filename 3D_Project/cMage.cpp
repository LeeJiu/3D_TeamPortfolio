#include "stdafx.h"
#include "cMage.h"
#include "cTerrain.h"
#include "cCamera.h"
#include "cInputHandler.h"
#include "cWeapon.h"
//��ƼŬ
#include "cPartcleEmitter.h"
#include "cParticleQuad.h""
#include "cParticle.h"
#include "cQuadParticleEmitter.h"


cMage::cMage()
{

}


cMage::~cMage()
{
	SAFE_DELETE(m_pInput);
	SAFE_DELETE(m_pMove);
	SAFE_DELETE(m_ATKBox);

	SAFE_DELETE(pWeapon);
	
}



void cMage::BaseObjectEnable()
{
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	cXMesh_Static* pSTF_Basic = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Weapon/STF_Master.X", &matCorrection);

	//���� ����
	pWeapon = new cWeapon;
	pWeapon->SetMesh(pSTF_Basic);
	pWeapon->SetActive(true);

	pSkinned->AddBoneTransform("Bip01-R-Hand", pWeapon->pTransform);

	m_isPetOn = false;

	//��ų ����
	SkillInit();



	//��Ÿ �ڽ�
	m_ATKBox = new cBoundBox;
	m_ATKBox->Init(D3DXVECTOR3(-0.3f, -0.3f, -0.3f), D3DXVECTOR3(0.3f, 0.3f, 0.3f));

	m_ATKBoxTrans = new cTransform;
	m_ATKBox->SetBound(&m_ATKBoxTrans->GetWorldPosition(), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
	pSkinned->AddBoneTransform("Bip01-L-Hand", m_ATKBoxTrans);



	m_pInput = new cInputHandler;
	m_pInput->AddKey('1', new cTestCommand);
	m_pInput->AddKey('2', new cTestCommand2);
	
	//ĳ������ �׷��� ��ġ�� ����
	pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);
	D3DXVECTOR3	minPos(-1, 0, -1);
	D3DXVECTOR3	maxPos(1, 3, 1);
	BoundBox.Init(minPos, maxPos);

	m_state = IDLE;
	m_Aniname = SetAnimation(m_state);

	m_pMove = new moveClass;
	m_isMove = false;

	//���������� ����� Ű�� ����
	std::pair<int, bool> key_W('W', false);
	std::pair<int, bool> key_S('S', false);
	std::pair<int, bool> key_A('A', false);
	std::pair<int, bool> key_D('D', false);
	m_InputKeys.insert(key_W);
	m_InputKeys.insert(key_S);
	m_InputKeys.insert(key_A);
	m_InputKeys.insert(key_D);
	
	m_pMove->init(pTransform, pTerrain, m_camera, NULL);
}

void cMage::BaseObjectUpdate(float timeDelta)
{
	cCommand* command = m_pInput->HandleInput();
	if (command != NULL)
	{
		command->Execute();
	}

	//�꿡 Ÿ�� �ֳ�
	if (KEY_MGR->IsOnceDown('9'))
	{
		if (m_isPetOn) m_isPetOn = false;
		else
		{
			m_state = PET_RUN;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->Play(m_Aniname, 0.3);
			m_isPetOn = true;
		}
	}


	if (m_isPetOn)
	{
		
	}
	else
	{


		//�ִϸ��̼Ǽ�
		if ((KEY_MGR->IsOnceDown('W') || KEY_MGR->IsOnceDown('D')
			|| KEY_MGR->IsOnceDown('A')))
		{
			m_state = RUN;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->Play(m_Aniname, 0.3);
		}


		if (m_isMove && KEY_MGR->IsOnceDown('S'))
		{
			m_state = WALK_BACK;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->Play(m_Aniname, 0.3);
		}

		if (!m_isMove && (KEY_MGR->IsOnceUp('W') || KEY_MGR->IsOnceUp('S')
			|| KEY_MGR->IsOnceUp('Q') || KEY_MGR->IsOnceUp('E')
			|| KEY_MGR->IsOnceUp('A') || KEY_MGR->IsOnceUp('D')))
		{
			m_state = WAIT;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->Play(m_Aniname, 0.3);
		}

		if (KEY_MGR->IsOnceDown('5'))
		{
			m_state = STF_FROZEN;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->PlayOneShot(m_Aniname, 0.3);
		}

		if (KEY_MGR->IsOnceDown('6'))
		{
			m_state = STF_BUFF;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->PlayOneShot(m_Aniname, 0.3);
		}

		if (KEY_MGR->IsOnceDown('7'))
		{
			m_state = STF_STORM;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->PlayOneShot(m_Aniname, 0.3);
		}

		if (KEY_MGR->IsOnceDown('8'))
		{
			m_state = STF_TYFUNG;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->PlayOneShot(m_Aniname, 0.3);	
			m_isSnowStorm = true;
			m_aniCount = 0;
		}


		//===============����==============================

		if (KEY_MGR->IsStayDown('W'))
		{
			m_InputKeys.find('W')->second = true;
		}
		else m_InputKeys.find('W')->second = false;


		if (KEY_MGR->IsStayDown('S'))
		{
			m_InputKeys.find('S')->second = true;
		}
		else m_InputKeys.find('S')->second = false;

		if (KEY_MGR->IsStayDown('A'))
		{
			m_InputKeys.find('A')->second = true;
		}
		else m_InputKeys.find('A')->second = false;

		if (KEY_MGR->IsStayDown('D'))
		{
			m_InputKeys.find('D')->second = true;

		}
		else m_InputKeys.find('D')->second = false;

		if (KEY_MGR->IsOnceDown('P'))
		{
			m_pInput->SwapKey('1', '2');
		}

		m_pMove->update(timeDelta, NULL, NULL, NULL, m_InputKeys);

		m_isMove = m_pMove->GetIsMove();

		LOG_MGR->AddLog("%s", m_Aniname.c_str());

	}

	this->pWeapon->Update(timeDelta);


	//��ų ��� ����
	if (m_aniCount == 480)
	{
		m_isSnowStorm = false;
	}

	if (m_isSnowStorm)
	{
		m_aniCount++;
		m_snowStrom->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_snowStrom->Update(timeDelta);
		m_snowStrom_under->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_snowStrom_under->Update(timeDelta);
		m_snow->pTransform->SetWorldPosition(pTransform->GetWorldPosition() + D3DXVECTOR3(0,7,0));
		m_snow->Update(timeDelta);
	}
	else
	{

	}
	


}


void cMage::ATKBoxRender()
{
	m_ATKBox->RenderGizmo(m_ATKBoxTrans);
}

void cMage::WeaponRender()
{

	this->pWeapon->Render();
	SkillRender();


}

void  cMage::SkillInit()
{
	m_aniCount = 0;
	SnowStormInit();
	m_isSnowStorm = false;

}


void  cMage::SkillRender()
{
	if (m_isSnowStorm)
	{
		m_snowStrom_under->Render();
		m_snowStrom->Render();
		m_snow->Render();
		
	}
	
}




//����� ���� 

void cMage::SnowStormInit()
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
		1.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		5.0f,
		D3DXVECTOR3(0, 2, 0),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(0, 10, 0),
		D3DXVECTOR3(0, 0, 0),     //ȸ����
		D3DXVECTOR3(0, 0, 0),     //��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(90 * ONE_RAD, 0, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3(90 * ONE_RAD, 0, 0),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors, scales,
		3.0f, 3.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/snowStrom.tga"),
		true);


	m_snowStrom_under = new cQuadParticleEmitter();
	m_snowStrom_under->SetActive(true);


	VEC_COLOR colors2;
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales2;
	scales2.push_back(2.0f);  //�ʹ� ũ��
	scales2.push_back(2.0f);

	m_snowStrom_under->Init(
		100,
		40.0f,     //����Ʈ ����
		1.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
		1.0f,
		D3DXVECTOR3(0, 1, 0),     //������ġ���� ���������� �Ÿ�
		D3DXVECTOR3(0, 7, 0),
		D3DXVECTOR3(0, 0.5, 0),     //�������� �߻��ϴ� �� ����
		D3DXVECTOR3(0, 0.8, 0),     //�������� �߻��ϴ� �� ��
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),	//�ʱ���۽� ȸ�� min
		D3DXVECTOR3 (- 90 * ONE_RAD, 0, 720 * ONE_RAD),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
		colors2, scales2,
		3.0f, 9.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/snowStorm2.tga"),
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
		"../Resources/Textures/Effects/snow.tga");

	//��ƼŬ ������ ����
	m_snow->Init(
		50,				//�ִ� ��ƼŬ ��
		30.0f,				//�ʴ� ��ƼŬ �߻� ��
		7,					//�ϳ��� ��ƼŬ ���� ������ �ּҰ�
		10,					//�ϳ��� ��ƼŬ ���� ������ �ִ밪
		D3DXVECTOR3(0, 0, 0),	//��ƼŬ ���� �ӵ� �ּҰ� ( ���ñ��� )
		D3DXVECTOR3(-10, 10, -10),	//��ƼŬ ���� �ӵ� �ִ밪 ( ���ñ��� )
		D3DXVECTOR3(0, 0, 0),	//��ƼŬ ���� ���� �ּҰ� ( ���ñ��� )
		D3DXVECTOR3(0, 0, 0), //��ƼŬ ���� ���� �ִ밪 ( ���ñ��� )
		colors_snow,				//�÷� �迭
		scales_snow,				//������ �迭
		1.1f,				//����ũ�� �ּҰ�
		50.2f,				//�ִ밪
		pTex,				//�ؽ���
		false);


	m_snow->EmissionType = PATICLE_EMISSION_TYPE::SPHERE_OUTLINE;
	m_snow->SphereEmissionRange = 3.0f;
	m_snow->StartEmission();

	m_snowStrom->StartEmission();
	m_snowStrom_under->StartEmission();




}
