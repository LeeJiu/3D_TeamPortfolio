#include "stdafx.h"
#include "cSkill_Swing.h"


cSkill_Swing::cSkill_Swing()
{
}


cSkill_Swing::~cSkill_Swing()
{
}


void cSkill_Swing::Effect_Init()
{

	//D3DXMATRIXA16 matScale;
	//D3DXMatrixScaling(&matScale, 0.3f, 0.3f, 0.3f);
	//D3DXMATRIXA16 matCorrection = matScale;
	//
	////m_DarkDorm = new cXMesh_Static;
	////m_DarkDorm->Init("../Resources/Textures/Effects/Dorm_ice.X", &matCorrection);
	//
	//m_snowStrom = new cQuadParticleEmitter();
	//m_snowStrom->SetActive(true);
	//
	//VEC_COLOR colors;
	//colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//
	//VEC_SCALE scales;
	//scales.push_back(1.0f);  //�ʹ� ũ��
	//scales.push_back(5.0f);
	//
	//m_snowStrom->Init(
	//	100,
	//	100.0f,     //����Ʈ ����
	//	1.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
	//	5.0f,
	//	D3DXVECTOR3(0, 2, 0),     //������ġ���� ���������� �Ÿ�
	//	D3DXVECTOR3(0, 10, 0),
	//	D3DXVECTOR3(0, 0, 0),     //ȸ����
	//	D3DXVECTOR3(0, 0, 0),     //��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
	//	D3DXVECTOR3(90 * ONE_RAD, 0, 0),	//�ʱ���۽� ȸ�� min
	//	D3DXVECTOR3(90 * ONE_RAD, 0, 0),     //�ʱ���۽� ȸ��Max
	//	D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
	//	D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
	//	D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
	//	D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
	//	colors, scales,
	//	3.0f, 3.0f,
	//	RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/snowStrom.tga"),
	//	true);
	//
	//
	//m_snowStrom_under = new cQuadParticleEmitter();
	//m_snowStrom_under->SetActive(true);
	//
	//
	//VEC_COLOR colors2;
	//colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//
	//VEC_SCALE scales2;
	//scales2.push_back(2.0f);  //�ʹ� ũ��
	//scales2.push_back(2.0f);
	//
	//m_snowStrom_under->Init(
	//	100,
	//	40.0f,     //����Ʈ ����
	//	1.0f,       //���̺�Ÿ�� (�߻� Ƚ���� ���� �ð�(�������� �����)
	//	1.0f,
	//	D3DXVECTOR3(0, 1, 0),     //������ġ���� ���������� �Ÿ�
	//	D3DXVECTOR3(0, 7, 0),
	//	D3DXVECTOR3(0, 0.5, 0),     //�������� �߻��ϴ� �� ����
	//	D3DXVECTOR3(0, 0.8, 0),     //�������� �߻��ϴ� �� ��
	//	D3DXVECTOR3(-90 * ONE_RAD, 0, 0),	//�ʱ���۽� ȸ�� min
	//	D3DXVECTOR3(-90 * ONE_RAD, 0, 720 * ONE_RAD),     //�ʱ���۽� ȸ��Max
	//	D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
	//	D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
	//	D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
	//	D3DXVECTOR3(0, 0, 0),				//��ȸ�� ���� ��ǳ���� ����Ʈ�� ����
	//	colors2, scales2,
	//	3.0f, 9.0f,
	//	RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/snowStorm2.tga"),
	//	true);
	//
	//m_snow = new cPartcleEmitter();
	//m_snow->SetActive(true);
	//
	////�迭�� 2 ���̻� 
	//VEC_COLOR colors_snow;
	//colors_snow.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//colors_snow.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//
	//VEC_SCALE scales_snow;
	//scales_snow.push_back(0.1f);
	//scales_snow.push_back(0.1f);
	//
	//LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
	//	"../Resources/Textures/Effects/snow.tga");
	//
	////��ƼŬ ������ ����
	//m_snow->Init(
	//	50,				//�ִ� ��ƼŬ ��
	//	30.0f,				//�ʴ� ��ƼŬ �߻� ��
	//	7,					//�ϳ��� ��ƼŬ ���� ������ �ּҰ�
	//	10,					//�ϳ��� ��ƼŬ ���� ������ �ִ밪
	//	D3DXVECTOR3(0, 0, 0),	//��ƼŬ ���� �ӵ� �ּҰ� ( ���ñ��� )
	//	D3DXVECTOR3(-10, 10, -10),	//��ƼŬ ���� �ӵ� �ִ밪 ( ���ñ��� )
	//	D3DXVECTOR3(0, 0, 0),	//��ƼŬ ���� ���� �ּҰ� ( ���ñ��� )
	//	D3DXVECTOR3(0, 0, 0), //��ƼŬ ���� ���� �ִ밪 ( ���ñ��� )
	//	colors_snow,				//�÷� �迭
	//	scales_snow,				//������ �迭
	//	1.1f,				//����ũ�� �ּҰ�
	//	50.2f,				//�ִ밪
	//	pTex,				//�ؽ���
	//	false);
	//
	//
	//m_snow->EmissionType = PATICLE_EMISSION_TYPE::SPHERE_OUTLINE;
	//m_snow->SphereEmissionRange = 3.0f;
	//
	//
	//m_snowStrom->StartEmission();
	//m_snowStrom_under->StartEmission();
	//m_snow->StartEmission();
	//
	////m_isSnowStorm = true;
	//m_aniCount = 0;

}


void cSkill_Swing::Effect_Update(float timeDelta)
{

	//if (m_AttackingTime - 100 == m_AttackingCount)
	//{
	//	m_snowStrom->StopEmission();
	//	m_snowStrom_under->StopEmission();
	//	m_snow->StopEmission();
	//}
	//
	//
	//if (m_IsAttacking)
	//{
	//	m_aniCount++;
	//	m_snowStrom->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
	//	m_snowStrom->pTransform->RotateSelf(D3DXVECTOR3(0, -10.0*timeDelta, 0));
	//	m_snowStrom->Update(timeDelta);
	//	m_snowStrom_under->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
	//	m_snowStrom_under->pTransform->RotateSelf(D3DXVECTOR3(0, -5.0*timeDelta, 0));
	//	m_snowStrom_under->Update(timeDelta);
	//	m_snow->pTransform->SetWorldPosition(pTransform->GetWorldPosition() + D3DXVECTOR3(0, 7, 0));
	//	m_snow->Update(timeDelta);
	//}

}
void cSkill_Swing::Effect_Render()
{
	//if (m_IsAttacking)
	//{
	//	//m_DarkDorm->Render(m_snowStrom_under->pTransform);
	//	m_snowStrom_under->Render();
	//	m_snowStrom->Render();
	//	m_snow->Render();
	//
	//}
}