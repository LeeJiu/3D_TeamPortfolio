#pragma once
#include "cCamera.h"

#define TEX_WIDTH 32
#define TEX_HEIGHT 64

struct stDamage
{
	int unit;					//1의자리 수
	int	tens;					//10의자리 수 
	int hund;					//100의자리 수
	int thou;					//1000의자리 수
	RECT unit_Rc;				//1의자리 렉트	
	RECT tens_Rc;				//10의자리 렉트
	RECT hund_Rc;				//100의자리 렉트
	RECT thou_Rc;				//1000의자리 렉트
	LPDIRECT3DTEXTURE9 unit_tex;	// 이미지들
	LPDIRECT3DTEXTURE9 tens_tex;
	LPDIRECT3DTEXTURE9 hund_tex;
	LPDIRECT3DTEXTURE9 thou_tex;
	float unit_x, unit_y;						// 화면에 그려질 좌표. 
	float countTime;			//카운트할시간
	float time;					//유지시간

	bool isDrawing;			//그려지는중?
};


class cShowDamage
{
private:
	std::vector<stDamage> v_damage;		//데미지 구조체 백터
	std::vector<stDamage>::iterator vi_damage;		//데미지 구조체 백터
	
	int num;				//들어오는 숫자
	int size; 		//벡터사이즈

	//float m_time;
	//bool  m_isDrawing;

public:
	cShowDamage();
	~cShowDamage();

	void Init();

	void SetNumber(int number, cTransform* trans);
	void Release();
	void Update(float timeDelta);
	void Render();
};

