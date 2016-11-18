#include "stdafx.h"
#include "cMage.h"
#include "cTerrain.h"
#include "cCamera.h"
#include "cItem.h"
//��ƼŬ
#include "cPartcleEmitter.h"
#include "cParticleQuad.h""
#include "cParticle.h"
#include "cQuadParticleEmitter.h"

//��ų

cMage::cMage()
{

}


cMage::~cMage()
{
	SAFE_DELETE(m_pMove);
	SAFE_DELETE(m_ATKBox);

	SAFE_DELETE(pWeapon);
	
}



void cMage::BaseObjectEnable()
{

	//���� ����
	MonsterInit();

	

	//���� ����

	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	cXMesh_Static* pSTF_Basic = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Weapon/STF_Master.X", &matCorrection);


	pWeapon = new cItem;
	pWeapon->SetMesh(pSTF_Basic);
	pWeapon->SetActive(true);

	pSkinned->AddBoneTransform("Bip01-R-Hand", pWeapon->pTransform);

	m_isPetOn = false;

	//��ų ����
	SkillInit();



	//��Ÿ �ڽ�
	m_ATKBox = new cBaseObject;
	m_ATKBox->BoundBox.Init(D3DXVECTOR3(-0.3f, -0.3f, -0.3f), D3DXVECTOR3(0.3f, 0.3f, 0.3f));

	
	m_ATKBox->BoundBox.SetBound(&m_ATKBox->pTransform->GetWorldPosition(), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
	pSkinned->AddBoneTransform("Bip01-L-Hand", m_ATKBox->pTransform);



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


		if (KEY_MGR->IsOnceDown('4'))
		{
			m_state = ATK_01;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->PlayOneShot(m_Aniname, 0.3);
			MagicATKInit();
			m_magicATK->StartEmission();
			m_isMagicATK = true;
			m_aniCount = 0;
			
		}

		if (KEY_MGR->IsOnceDown('5'))
		{
			m_state = STF_BUFF;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->PlayOneShot(m_Aniname, 0.3);
			m_magicShild->StartEmission();
			m_isMagicShild = true;
			m_aniCount = 0;
		}

		if (KEY_MGR->IsOnceDown('6'))
		{
			m_state = STF_FROZEN;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->PlayOneShot(m_Aniname, 0.3);
			FlameRoadInit();
			m_flameRoad_cast = true;
			m_flameRoad_cast_count = 0;
			m_aniCount = 0;
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
			m_snowStrom->StartEmission();
			m_snowStrom_under->StartEmission();
			m_snow->StartEmission();
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

		m_pMove->update(timeDelta, NULL, NULL, NULL, m_InputKeys);

		m_isMove = m_pMove->GetIsMove();

		LOG_MGR->AddLog("%s", m_Aniname.c_str());

	}

	this->pWeapon->Update(timeDelta);


	//��ų ��� ����
	


	if (m_aniCount == 480)
	{
		m_snowStrom->StopEmission();
		m_snowStrom_under->StopEmission();
		m_snow->StopEmission();
		//m_isSnowStorm = false;
	}

	if (m_aniCount == 120)
	{
		m_magicATK->StopEmission();
		m_isMagicATK = false;
	}

	if (m_aniCount == 600)
	{
		m_magicShild->StopEmission();
		
	}


	if (m_flameRoad_cast)
	{
		m_flameRoad_cast_count++;
	}

	if (m_flameRoad_cast_count == 120)
	{
		m_flameRoad->StartEmission();
		m_flameRoad2->StartEmission();
		m_flameRoad3->StartEmission();
		m_isFlameRoad = true;
		m_aniCount = 0;
	}

	if (m_aniCount == 200)
	{
		m_flameRoad->StopEmission();
		m_flameRoad2->StopEmission();
		m_flameRoad3->StopEmission();
		m_flameRoad_cast_count = 0;
		m_isFlameRoad = false;
		m_flameRoad_cast = false;
	}



	if (m_isMagicATK)
	{
		m_aniCount++;
		m_magicATK->Update(timeDelta);
		m_magicATK->pTransform->SetWorldPosition(this->m_ATKBox->pTransform->GetWorldPosition());
	}



	if (m_isFlameRoad)
	{
		m_aniCount++;
		m_flameRoad->Update(timeDelta);
		m_flameRoad2->Update(timeDelta);
		m_flameRoad3->Update(timeDelta);
		m_flameRoad->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_flameRoad->pTransform->LookDirection(pTransform->GetForward(), 90.0f * ONE_RAD);
		m_flameRoad2->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_flameRoad2->pTransform->LookDirection(pTransform->GetForward(), 90.0f * ONE_RAD);
		m_flameRoad3->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_flameRoad3->pTransform->LookDirection(pTransform->GetForward(), 90.0f * ONE_RAD);
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


	if (m_isMagicShild)
	{
		m_aniCount++;
		m_magicShild->Update(timeDelta);
		m_magicShild->pTransform->SetWorldPosition(this->pTransform->GetWorldPosition());

	}
	


	MonsterUpdate(timeDelta);

}


void cMage::ATKBoxRender()
{



	//m_ATKBox->BoundBox.RenderGizmo(m_ATKBox->pTransform);


}

void cMage::WeaponRender()
{

	this->pWeapon->Render();
	
	MonsterRender();

	SkillRender();



}

void  cMage::SkillInit()
{
	m_aniCount = 0;
	SnowStormInit();
	MagicShildInit();
	
	m_isSnowStorm = false;
	m_isMagicATK = false;
	m_isMagicShild = false;
	m_isFlameRoad = false;
	m_flameRoad_cast = false;
}


void  cMage::SkillRender()
{
	if (m_isSnowStorm)
	{
		m_snowStrom_under->Render();
		m_snowStrom->Render();
		m_snow->Render();
		
	}

	if (m_isMagicATK)
	{
		m_magicATK->Render();
	}

	if (m_isMagicShild)
	{
		m_magicShild->Render();
	}

	if (m_isFlameRoad)
	{
		m_flameRoad->Render();
		m_flameRoad2->Render();
		m_flameRoad3->Render();
	}
	
}


//��Ÿ
void cMage::MagicATKInit()
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
		1.0f, 2.5f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicalATK.tga"),
		true);

	m_magicATK->StartEmission();




}


void cMage::FlameRoadInit()
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





//���� �ǵ�

void cMage::MagicShildInit()
{
	m_magicShild = new cQuadParticleEmitter();
	m_magicShild->SetActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(5.0f);  //�ʹ� ũ��
	scales.push_back(5.0f);

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
		2.0f, 2.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicShild.tga"),
		true);

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


void cMage::MonsterInit()
{
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	cXMesh_Skinned* pMonster = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Minho/MOB_Minho.X", &matCorrection);

	//���� ����
	m_pMonster = new cBaseObject;
	m_pMonster->SetMesh(pMonster);
	m_pMonster->SetActive(true);

	m_pMonster->BoundBox.Init(D3DXVECTOR3(-0.5, -0.5, -0.5), D3DXVECTOR3(0.5, 5.5, 0.5));
	m_pMonster->pTransform->SetWorldPosition(D3DXVECTOR3(0, 8, 0));


	m_isTarget = false;
	m_MobCollision = false;




}


void cMage::MonsterUpdate(float timeDelta)
{
	
	m_pMonster->pSkinned->Update(timeDelta);



	MonsterCollision(timeDelta);
	
	

}


void cMage::MonsterCollision(float timeDelta)
{

	D3DXVECTOR3 magicATKLegth = pTransform->GetWorldPosition() - m_pMonster->pTransform->GetWorldPosition();

	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		Ray ray;
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		this->m_camera->ComputeRay(&ray, &screenPos);

		if (PHYSICS_MGR->IsRayHitBound(&ray, &m_pMonster->BoundBox, m_pMonster->pTransform, NULL, NULL))
		{
			m_isTarget = true;
			m_pMonster->pSkinned->PlayOneShot("WAIT", 0.3f);

		}
		else
		{
			m_isTarget = false;
			m_pMonster->pSkinned->Play("IDLE", 0.3f);
		}


		if (m_isTarget &&D3DXVec3Length(&magicATKLegth) > 20)
		{
			m_state = RUN;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->Play(m_Aniname, 0.3);
		}

	
	}



	if (m_isTarget && D3DXVec3Length(&magicATKLegth) > 20)
	{
		pTransform->LookPosition(m_pMonster->pTransform->GetWorldPosition(), 90.0f * ONE_RAD);
		pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 10.0f * timeDelta));
		m_StateCount = 0;
		//��Ÿ� ���̸� �̵��ض�
	}
	else
	{

		m_StateCount++;
		if (m_StateCount == 1)
		{
			m_state = WAIT;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->Play(m_Aniname, 0.3);
		}
	
	}




	if (m_isTarget && D3DXVec3Length(&magicATKLegth) < 20);
	{
	

		if (m_isMagicATK)
		{
			pSkinned->RemoveBoneTransform("Bip01-L-Hand");
			m_ATKBox->pTransform->LookPosition(m_pMonster->pTransform->GetWorldPosition() + D3DXVECTOR3(0, 2, 0));
			m_ATKBox->pTransform->MovePositionSelf(0, 0, 30.0f * timeDelta);
		}
		else
		{
			pSkinned->AddBoneTransform("Bip01-L-Hand", m_ATKBox->pTransform);
		}
	
	}
	
	if (PHYSICS_MGR->IsOverlap(m_ATKBox, m_pMonster))
	{
		
	}





}


void cMage::MonsterRender()
{

	m_pMonster->Render();
	m_pMonster->BoundBox.RenderGizmo(m_pMonster->pTransform);

}