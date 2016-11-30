#include "stdafx.h"
#include "cScene_Field.h"
#include "cTerrain.h"
#include "cBerserker.h"
#include "cMonsterManager.h"
#include "cLight_Direction.h"


cScene_Field::cScene_Field()
{
}


cScene_Field::~cScene_Field()
{
}

HRESULT cScene_Field::Scene_Init()
{
	//�����
	//���� ����
	SCENE_MGR->fProgress = 0.0f;
	SCENE_MGR->fString = "Sound Loading";
	SoundInit();

	//�ͷ��� ����
	SCENE_MGR->fProgress = 20.0f;
	SCENE_MGR->fString = "Terrain Loading";
	m_pTerrain = new cTerrain;
	m_pTerrain->Init(
		"../Resources/Textures/MyHeight256.bmp",
		"../Resources/Textures/terrain1.png",
		"../Resources/Textures/terrain2.png",
		"../Resources/Textures/terrain3.png",
		"../Resources/Textures/terrain4.png",
		"../Resources/Textures/Splat2.png",
		1.0f,
		100.0f,
		3,
		100);

	//����Ʈ ����
	SCENE_MGR->fProgress = 40.0f;
	SCENE_MGR->fString = "Terrain Loading";
	cLight_Direction* pLight1 = new cLight_Direction();
	pLight1->Color = D3DXCOLOR(1, 1, 1, 1);
	pLight1->Intensity = 1.0f;
	pLight1->pTransform->SetRotateWorld(90 * ONE_RAD, 0, 0);
	this->lights.push_back(pLight1);


	//������Ʈ ����
	SCENE_MGR->fProgress = 60.0f;
	SCENE_MGR->fString = "Object Loading";
	ObjectInit();


	//���� �Ϸ�
	SCENE_MGR->fProgress = 100.0f;
	SCENE_MGR->fString = "Complete Loading";

	SOUND_MGR->play("field_bgm", 0.8);

	return S_OK;
}

void cScene_Field::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);
	SAFE_DELETE(m_pPlayer);

	m_pMonMgr->Release();
	SAFE_DELETE(m_pMonMgr);
}

void cScene_Field::Scene_Update(float timeDelta)
{
	g_bDXRender = true;

	//�ӽ÷� ������ ���� / �÷��̾� ��ġ
	if (KEY_MGR->IsOnceUp('T'))
	{
		ITEM_MGR->createItem(1, m_pPlayer->pTransform->GetWorldPosition());

	}
	if (KEY_MGR->IsOnceUp('Y'))
	{
		ITEM_MGR->createItem(0, m_pPlayer->pTransform->GetWorldPosition());

	}

	m_pPlayer->Update(timeDelta);
	m_pMonMgr->Update(timeDelta);
}

void cScene_Field::Scene_Render1()
{
	m_pTerrain->Render(this->pMainCamera, dynamic_cast<cLight_Direction*>(lights[0]));
	
	//����Ǵ� LightMatrix
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < this->lights.size(); i++)
		matLights[i] = this->lights[i]->GetLightMatrix();

	//���̴��� ������ ����
	cXMesh_Skinned::sSkinnedMeshEffect->SetMatrixArray("matLights", matLights, 10);
	cXMesh_Skinned::sSkinnedMeshEffect->SetInt("LightNum", this->lights.size());

	cXMesh_Skinned::SetCamera(this->pMainCamera);
	cXMesh_Skinned::SetTechniqueName("Toon");
	cXMesh_Skinned::sSkinnedMeshEffect->SetTexture("Ramp_Tex", RESOURCE_TEXTURE->GetResource("../Resources/Textures/Ramp_1.png"));
	cXMesh_Skinned::SetBaseLight(this->pSceneBaseDirectionLight);


	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetTechniqueName("Toon");		//������� ���� �׸����� ReciveShadow �� Technique ����
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);

	m_pPlayer->Render();
	m_pMonMgr->Render();
}

void cScene_Field::Scene_RenderSprite()
{
	m_pPlayer->BaseSpriteRender();
}

void cScene_Field::Scene_RenderFont()
{
	m_pPlayer->BaseFontRender();
}

void cScene_Field::SoundInit()
{
	//���� ȿ����
	SOUND_MGR->addSound("ban", "../Resources/Sound/ban.ogg", false, false);
	SOUND_MGR->addSound("setWeapon", "../Resources/Sound/��������.ogg", false, false);
	SOUND_MGR->addSound("offWeapon", "../Resources/Sound/��������.wav", false, false);
	SOUND_MGR->addSound("inputWeapon", "../Resources/Sound/���ֿ�.ogg", false, false);
	SOUND_MGR->addSound("walk", "../Resources/Sound/�ȴ�.ogg", true, true);
	SOUND_MGR->addSound("hit", "../Resources/Sound/hit_impact02.ogg", false, false);

	//�����
	SOUND_MGR->addSound("field_bgm", "../Resources/Sound/�縷�����.mp3", true, true);

	//����Ŀ ȿ����
	SOUND_MGR->addSound("bk_atk1_voice", "../Resources/Sound/����Ŀ_��Ÿ3 (1).ogg", false, false);
	SOUND_MGR->addSound("bk_atk2_voice", "../Resources/Sound/����Ŀ_��Ÿ3 (2).ogg", false, false);
	SOUND_MGR->addSound("bk_atk3_voice", "../Resources/Sound/����Ŀ_��Ÿ3 (3).ogg", false, false);
	SOUND_MGR->addSound("bk_atk1", "../Resources/Sound/����Ŀ_��Ÿ6.ogg", false, false);
	SOUND_MGR->addSound("bk_atk2", "../Resources/Sound/����Ŀ_��Ÿ1.ogg", false, false);
	SOUND_MGR->addSound("bk_atk3", "../Resources/Sound/����Ŀ_��Ÿ7.ogg", false, false);
	SOUND_MGR->addSound("bk_heat", "../Resources/Sound/����Ŀ_����.ogg", false, false);
	SOUND_MGR->addSound("bk_dead", "../Resources/Sound/����Ŀ_����.ogg", false, false);
	SOUND_MGR->addSound("bk_charge_voice", "../Resources/Sound/����Ŀ_���_�Ƹ�ũ����.ogg", false, false);
	SOUND_MGR->addSound("charge_boom", "../Resources/Sound/���� ������.ogg", false, false);
	SOUND_MGR->addSound("bk_swing_voice", "../Resources/Sound/����Ŀ_���_����.ogg", false, false);
	SOUND_MGR->addSound("bk_burserk_voice", "../Resources/Sound/����Ŀ_���_����ȭ.ogg", false, false);
	SOUND_MGR->addSound("bk_weapon_voice", "../Resources/Sound/����Ŀ_���_��������.ogg", false, false);

	//�� ȿ����
	SOUND_MGR->addSound("dra_BasicATK", "../Resources/Sound/���õ巡��_����.ogg", false, false);
	SOUND_MGR->addSound("dra_Breath", "../Resources/Sound/���õ巡��_�극��.ogg", false, false);
	SOUND_MGR->addSound("dra_HeadATK", "../Resources/Sound/���õ巡��_��ų1.ogg", false, false);
	SOUND_MGR->addSound("dra_Spawn", "../Resources/Sound/���õ巡��_��ų2.ogg", false, false);

	SOUND_MGR->addSound("dra_Thunder", "../Resources/Sound/���õ巡��_���.ogg", false, false);
	SOUND_MGR->addSound("dra_Meteo", "../Resources/Sound/���õ巡��_���׿�.ogg", false, false);
	SOUND_MGR->addSound("dra_Die", "../Resources/Sound/���õ巡��_����.ogg", false, false);

	//���� ȿ����
	//�Ź�
	SOUND_MGR->addSound("atk_spider", "../Resources/Sound/�Ź�_����.ogg", false, false);
	SOUND_MGR->addSound("dmg_spider", "../Resources/Sound/�Ź�_����.ogg", false, false);
	SOUND_MGR->addSound("die_spider", "../Resources/Sound/�Ź�_����.ogg", false, false);

	//�ٽǸ���ũ
	SOUND_MGR->addSound("atk_basil", "../Resources/Sound/�ٽ�_����.ogg", false, false);
	SOUND_MGR->addSound("atk2_basil", "../Resources/Sound/�ٽ�_����2.ogg", false, false);
	SOUND_MGR->addSound("dmg_basil", "../Resources/Sound/�ٽ�_����.ogg", false, false);
	SOUND_MGR->addSound("die_basil", "../Resources/Sound/�ٽ�_����.ogg", false, false);

	//�̳�Ÿ��ν�
	SOUND_MGR->addSound("atk_mino", "../Resources/Sound/monster_minotauros_atk.mp3", false, false);
	SOUND_MGR->addSound("atk2_mino", "../Resources/Sound/monster_minotauros_atk2.mp3", false, false);
	SOUND_MGR->addSound("die_mino", "../Resources/Sound/monster_minotauros_dead.ogg", false, false);
	SOUND_MGR->addSound("hit_mino", "../Resources/Sound/monster_minotauros_hit.ogg", false, false);
	SOUND_MGR->addSound("wait_mino", "../Resources/Sound/monster_moonknight_cry2.ogg", false, false);
}

void cScene_Field::ObjectInit()
{
	//
	//�ǹ� / �ٿ�� �ڽ� �ε�
	//
	LOAD_MGR->LoadObjects(&m_vObject);
	LOAD_MGR->LoadBoundBox(&m_vBoundBox);

	//
	//ĳ���� ���� ��� ����
	//
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.05f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	//
	//�÷��̾� ����
	//
	m_pPlayer = new cBerserker;
	m_pPlayer->SetTerrain(m_pTerrain);
	m_pPlayer->SetCamera(pMainCamera);
	m_pPlayer->SetMesh(RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Pant/Pant_Master.X", &matCorrection));

	//
	//���� �Ŵ��� ����
	//
	m_pMonMgr = new cMonsterManager;
	m_pMonMgr->SetTerrain(m_pTerrain);
	m_pMonMgr->SetPlayer(m_pPlayer);
	m_pMonMgr->Init();

	//�÷��̾� ���� �Ŵ��� ��ũ
	m_pPlayer->SetMonsterManager(m_pMonMgr);
	m_pPlayer->SetActive(true);
}
