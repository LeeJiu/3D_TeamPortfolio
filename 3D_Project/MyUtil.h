#pragma once
#include "cTransform.h"


#define		FEPSILON		0.00001f		//Float �񱳸� �Ҷ� �̰� ������ ������ ���� �ɷ� ������.
/*
e =  0.00001f
a = 10.00001f;
b = 10.000095f
( abs( a - b ) < e ) == ����!!!!
*/

//a �� b �� ����?
#define		FLOATEQUAL( a, b )		( abs((a) - (b) ) < FEPSILON )

//���� 0 �̴�?
#define		FLOATZERO(a)			( abs((a)) < FEPSILON )

//���� ���ʹ�?
#define		VECTORZERO(v)			( FLOATZERO((v).x) && FLOATZERO((v).y) && FLOATZERO((v).z) )


#define		RS(a,b)			Device->SetRenderState((a),(b))		


//ĳ���� ����
//enum ACTOR_STATE
//{
//	AS_IDLE, AS_WALK, AS_ATTACK
//};


//ĳ���� ���� �����ι�
enum ACTOR_STATE
{
	ROBBY_IDLE,         //���� ���� ����â �����

	PET_IDLE,           //�� ž��
	PET_RUN,            //�� �̵�

	SIT_SRT,           //�ɱ�_����
	SIT_LOOP,          //�ɾ��ִ� ����
	SIT_UP,            //�Ͼ�� ���
	LOOP,              //�������

	HELLO,             //�λ�
	CRY,               //���
	DANCE,             //������� ���� ������!

	STF_DMG,           //�ǰ�
	STF_DIE,           //�׾�� ��
	STF_DEAD,          //����
	STF_DOWN,          //�˹�
	STF_STUN,          //�˹����_����
	STF_WAKEUP,        //�˹� �Ͼ��

	STF_IDLE,            //��ȭ����
	STF_WAIT,            //�������
	STF_WALK,            //�ȱ�
	STF_WALK_BACK,       //�ڷΰȱ�
	STF_RUN,             //�޸���
	RUN_R,               //���������� �޸���
	RUN_L,               //�������� �޸���
	STF_STOP,            //�޸��� ���߱�
	STF_PASSOUT,         //��¼Ҹ�
	STF_JUMP,            //����


	STF_WEAPON,          //���� ����
	STF_UNWEAPON,        //���� ����

						 //���� ����

	STF_ATK1,           //�⺻���� 1
	STF_ATK2,           //�⺻���� 2

	STF_BUFF,           //��ų_����
	STF_TYFUNG,         //��ų_��ǳ
	STF_THUNDER,        //��ų_����Ʈ�� �ε�
	STF_FROZEN,         //��ų_��������
	STF_FIRE,           //��ų_��üҰ�
	STF_SPLASH,         //��ų_��������
	STF_BUMB,           //��ų_��������
	STF_DRAIN,          //��ų_�巹��
	STF_SWING,          //��ų_�ķ����
	STF_STORM,          //��ų_õ�պ���
	STF_MAGIC_SHOT,     //��ų_�����߻�

	STF_BLINK,          //��ų_ ����
	END,

	AS_IDLE,
	AS_WALK,
};


//������ ����ü 
typedef struct tagRay{
	D3DXVECTOR3 origin;			//������ ���� ��ġ
	D3DXVECTOR3 direction;		//������ ���� ( ����ȭ �Ǿ��־�� �� )
}Ray, *LPRay;


namespace MyUtil{

	extern DWORD MaxAnisotropic;				//�̹漺 ���͸� �ִ� �ܰ�

	extern LPDIRECT3DDEVICE9 Device;			//���� Device ������ �ι� ( ��¥�߿��� ���� ���� ������ �ȵ�, ���� �Ŀ��� HDC �ʹ� �񱳵� �ȵ� )

	HRESULT CreateDevice();						//����̽� �����Լ�
	void ReleaseDevice();						//����̽� �����Լ�

	POINT GetMousePos();						//���콺��ġ
	void SetMousePos( int x, int y );			//���콺��ġ ����

	float Clamp( float value, float min, float max );	//value ���� min max ���̷� ������
	float Clamp01( float value );						//value �� 0 ~ 1 ���Ϸ� ����
	float ClampMinusOnePlusOne( float value );			//value �� -1 ~ 1 ���Ϸ� ����


	//float ���� ���� 
	//( t �� 0 ~ 1 ������ ���� �޴µ�...)
	//( t �� 0 �ϼ��� from ����� ���� ���ϵǰ� )
	//( t �� 1 �ϼ��� to ����� ���� ���ϵȴ� )
	float Lerp( float from, float to, float t );


	//float ���� ���� �ݴ�
	//value ���� head �� rear ���̿� ������� ��ġ�� �ִ���
	//0~1 ������ ������ �����Ѵ�.
	float InverseLerp( float head, float rear, float value );

	//���� ���� ����
	D3DXVECTOR3 VecLerp( const D3DXVECTOR3& from, const D3DXVECTOR3& to, float t );

	//Random
	void SetRandomSeed();
	float RandomFloatRange( float min, float max );
	int RandomIntRange( int min, int max );


	//������ �븻�� ������ִ� �Լ�
	void ComputeNormal( 
		D3DXVECTOR3* pNorams,			//����� ���� �븻���� �迭 ������ ( �븻������ �迭�� ���� ���� �迭�� ���� ���� )
		const D3DXVECTOR3* pVertices,	//��꿡 ���� ������ġ �迭 ������
		int verticesNum,				//���� ����
		const DWORD* pIndices,			//�ε��� �迭������ ( �ϴ� �ε����� DWORD �� �뵿�ܰ� )
		int indicesNum					//�ε��� �迭������ ����
		);				


	//ź��Ʈ�� ���̳븻 ���
	void ComputeTangentAngBinormal( 
		D3DXVECTOR3* outTangets,			//��� Tangent �迭
		D3DXVECTOR3* outBinormals,			//��� Binormal �迭
		const D3DXVECTOR3* pPositions,		//���� ��ġ �迭
		const D3DXVECTOR3* pNormals,		//���� �븻 �迭
		const D3DXVECTOR2* pUVs,			//������ UV �迭
		const DWORD* pIndices,				//�ε��� �迭
		DWORD NumTris,						//�ﰢ�� ����		
		DWORD NumVertices 					//���� ����
		);
	

	//�÷��� ��Ʈ���� �ս����� ����ü DWORD ������ ��ȯ
	DWORD FloatToDWORD( float f );

	std::string SetAnimation(ACTOR_STATE state);
	void createQuad(D3DXVECTOR3* quad, float row, float col, cTransform* myTrans, D3DXVECTOR3* createPos);

	
	RECT RectMake(int x, int y, int width, int height);


	RECT RectMakeCenter(int x, int y, int width, int height);
	

}