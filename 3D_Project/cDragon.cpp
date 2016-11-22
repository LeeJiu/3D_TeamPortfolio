#include "stdafx.h"
#include "cDragon.h"
#include "cPlayer.h"


cDragon::cDragon()
{
	m_collCount = COLLISION;

}


cDragon::~cDragon()
{
}

void cDragon::BaseObjectEnable()
{
	//=================== �ʱ�ȭ ================
	
	pSkinned->AddApplyTransform("Bip01-HeadNub", &m_boneTrans[0]);
	pSkinned->AddApplyTransform("Bip01-L-Hand_Bone", &m_boneTrans[0]);
	pSkinned->AddApplyTransform("Bip01-R-Hand_Bone", &m_boneTrans[0]);
	pSkinned->AddApplyTransform("Bip01-R-Foot_Bone", &m_boneTrans[0]);
	pSkinned->AddApplyTransform("Bip01-L-Foot_Bone", &m_boneTrans[0]);
}

void cDragon::BaseObjectUpdate(float timeDelta)
{
	//=================== ������Ʈ ==============
}

void cDragon::BaseObjectBoundBox()
{
	//=================== �ٿ�� �ڽ� �߰� ======
}

void cDragon::Damage(float fDamage)
{
	//=================== ������ ���� �Լ� ======
}
void cDragon::BaseObjectRender()
{
	//=================== ���� �Լ� =============
	//�� �̸� 
	// �Ӹ� Bip01-HeadNub
	// ���� Bip01-L-Hand_Bone
	// ���� Bip01-R-Hand_Bone
	// ���� Bip01-R-Foot_Bone
	// �޹� Bip01-L-Foot_Bone
	// ������ BN_Wing_R003,007
	// �޳��� BN_Wing_L003,007
	 
}