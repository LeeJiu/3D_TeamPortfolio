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
	//=================== 초기화 ================
	
	pSkinned->AddApplyTransform("Bip01-HeadNub", &m_boneTrans[0]);
	pSkinned->AddApplyTransform("Bip01-L-Hand_Bone", &m_boneTrans[0]);
	pSkinned->AddApplyTransform("Bip01-R-Hand_Bone", &m_boneTrans[0]);
	pSkinned->AddApplyTransform("Bip01-R-Foot_Bone", &m_boneTrans[0]);
	pSkinned->AddApplyTransform("Bip01-L-Foot_Bone", &m_boneTrans[0]);
}

void cDragon::BaseObjectUpdate(float timeDelta)
{
	//=================== 업데이트 ==============
}

void cDragon::BaseObjectBoundBox()
{
	//=================== 바운드 박스 추가 ======
}

void cDragon::Damage(float fDamage)
{
	//=================== 데미지 받을 함수 ======
}
void cDragon::BaseObjectRender()
{
	//=================== 렌더 함수 =============
	//본 이름 
	// 머리 Bip01-HeadNub
	// 왼팔 Bip01-L-Hand_Bone
	// 오팔 Bip01-R-Hand_Bone
	// 오발 Bip01-R-Foot_Bone
	// 왼발 Bip01-L-Foot_Bone
	// 오날개 BN_Wing_R003,007
	// 왼날개 BN_Wing_L003,007
	 
}