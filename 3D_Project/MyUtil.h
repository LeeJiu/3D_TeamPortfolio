#pragma once
#include "cTransform.h"


#define		FEPSILON		0.00001f		//Float 비교를 할때 이값 이하의 오차는 같은 걸로 따진다.
/*
e =  0.00001f
a = 10.00001f;
b = 10.000095f
( abs( a - b ) < e ) == 같다!!!!
*/

//a 와 b 가 같니?
#define		FLOATEQUAL( a, b )		( abs((a) - (b) ) < FEPSILON )

//거의 0 이니?
#define		FLOATZERO(a)			( abs((a)) < FEPSILON )

//제로 벡터니?
#define		VECTORZERO(v)			( FLOATZERO((v).x) && FLOATZERO((v).y) && FLOATZERO((v).z) )


#define		RS(a,b)			Device->SetRenderState((a),(b))		


//오브젝트 타입
enum OBJECT_TYPE
{
	MIGDAL_WALL, MIGDAL_HOUSE,
	TREE01, TREE02, TREE03, TREE04, TREE05,
	TREE01_D, TREE02_D, TREE03_D, TREE04_D, TREE05_D
};



//몬스터 타입
enum MONSTER_TYPE
{
	BASILISK, GRIFF, MINO, SPIDER, SPIDER_QUEEN, SUCCUBUS, DRAGON
};


//캐릭터 상태 디파인문
enum ACTOR_STATE
{
	ROBBY_IDLE,         //게임 시작 선택창 대기모션

	PET_IDLE,           //펫 탑승
	PET_RUN,            //펫 이동

	SIT_SRT,           //앉기_시작
	SIT_LOOP,          //앉아있는 상태
	SIT_UP,            //일어서는 모션
	LOOP,              //습득상태

	HELLO,             //인사
	CRY,               //울기
	DANCE,             //춤을춰라 나의 인형아!

	DMG,           //피격
	DIE,           //죽어가는 중
	DEAD,          //죽음
	DOWN,          //넉백
	STUN,          //넉백상태_루프
	STF_WAKEUP,        //넉백 일어나기

	IDLE,				 //평화상태
	WAIT,				 //대기상태
	WALK,            //걷기
	WALK_BACK,       //뒤로걷기
	RUN,             //달리기
	RUN_R,               //오른쪽으로 달리기
	RUN_L,               //왼쪽으로 달리기
	RUN_STOP,            //달리다 멈추기
	STF_PASSOUT,         //기력소모
	JUMP,            //점프


	WEAPON,          //무기 착용
	UNWEAPON,        //무기 해제

						 //공격 상태

	ATK_01,           //기본공격 1
	ATK_02,           //기본공격 2
	ATK_03,           //버서커 - 추가 기본공격 3

	STF_BUFF,           //스킬_버프
	STF_TYFUNG,         //스킬_태풍
	STF_THUNDER,        //스킬_라이트닝 로드
	STF_FROZEN,         //스킬_빙하지대
	STF_FIRE,           //스킬_즉시소각
	STF_SPLASH,         //스킬_전방폭파
	STF_BUMB,           //스킬_지면폭파
	STF_DRAIN,          //스킬_드레인
	STF_SWING,          //스킬_후려찍기
	STF_STORM,          //스킬_천둥벼락
	STF_MAGIC_SHOT,     //스킬_마법발사
	STF_BLINK,          //스킬_ 점멸

	//버서커 전용 스킬
	SK_BUFF,               // 스킬_버프
	SK_ATKUP,              //스킬_올려치기
	SK_CRASH,              //스킬_도끼찍기
	SK_SWING,              //스킬_도끼돌리기
	SK_CHARGE,             //스킬_광역찍기_차지
	SK_CHARGE_ATK,         //스킬_광역찍기_시전
	SK_HOWL,               //스킬_고함지르기
	SK_ESCAPE,             //스킬_돌진회피
	SK_ACCEL,              //스킬_트리플악셀
	SK_JUMPATK,            // 스킬_날아서 찍기
	
	END,

	AS_IDLE,
	AS_WALK,
};


//반직선 구조체 
typedef struct tagRay{
	D3DXVECTOR3 origin;			//직선의 시작 위치
	D3DXVECTOR3 direction;		//직선의 방향 ( 정규화 되어있어야 함 )
}Ray, *LPRay;


namespace MyUtil{

	extern DWORD MaxAnisotropic;				//이방성 필터링 최대 단계

	extern LPDIRECT3DDEVICE9 Device;			//전역 Device 요주의 인물 ( 진짜중요함 예로 다함 예없음 안됨, 그의 파워는 HDC 와는 비교도 안됨 )

	HRESULT CreateDevice();						//디바이스 생성함수
	void ReleaseDevice();						//디바이스 해제함수

	POINT GetMousePos();						//마우스위치
	void SetMousePos( int x, int y );			//마우스위치 셋팅

	float Clamp( float value, float min, float max );	//value 값을 min max 사이로 맞추줌
	float Clamp01( float value );						//value 값 0 ~ 1 사일로 맞춤
	float ClampMinusOnePlusOne( float value );			//value 값 -1 ~ 1 사일로 맞춤


	//float 선형 보간 
	//( t 는 0 ~ 1 사이의 값을 받는데...)
	//( t 가 0 일수록 from 가까운 값이 리턴되고 )
	//( t 가 1 일수록 to 가까운 값이 리턴된다 )
	float Lerp( float from, float to, float t );


	//float 선형 보간 반대
	//value 값이 head 와 rear 사이에 어느정도 위치에 있는지
	//0~1 사이의 값으로 리턴한다.
	float InverseLerp( float head, float rear, float value );

	//벡터 선형 보간
	D3DXVECTOR3 VecLerp( const D3DXVECTOR3& from, const D3DXVECTOR3& to, float t );

	//Random
	void SetRandomSeed();
	float RandomFloatRange( float min, float max );
	int RandomIntRange( int min, int max );


	//정점의 노말을 계산해주는 함수
	void ComputeNormal( 
		D3DXVECTOR3* pNorams,			//결과로 받을 노말백터 배열 포인터 ( 노말벡터의 배열의 수는 정점 배열의 수와 같다 )
		const D3DXVECTOR3* pVertices,	//계산에 사용된 정점위치 배열 포인터
		int verticesNum,				//정점 갯수
		const DWORD* pIndices,			//인덱스 배열포인터 ( 일단 인덱스는 DWORD 로 대동단결 )
		int indicesNum					//인덱스 배열포인터 갯수
		);				


	//탄젠트와 바이노말 계산
	void ComputeTangentAngBinormal( 
		D3DXVECTOR3* outTangets,			//결과 Tangent 배열
		D3DXVECTOR3* outBinormals,			//결과 Binormal 배열
		const D3DXVECTOR3* pPositions,		//정점 위치 배열
		const D3DXVECTOR3* pNormals,		//정점 노말 배열
		const D3DXVECTOR2* pUVs,			//정점의 UV 배열
		const DWORD* pIndices,				//인덱스 배열
		DWORD NumTris,						//삼각형 갯수		
		DWORD NumVertices 					//정점 갯수
		);
	

	//플룻의 비트값을 손실하지 않은체 DWORD 형으로 변환
	DWORD FloatToDWORD( float f );

	std::string SetAnimation(ACTOR_STATE state);
	void createQuad(D3DXVECTOR3* quad, float row, float col, cTransform* myTrans, D3DXVECTOR3* createPos);

	
	RECT RectMake(int x, int y, int width, int height);


	RECT RectMakeCenter(int x, int y, int width, int height);
	

}