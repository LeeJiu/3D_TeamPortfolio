#pragma once

class cXMesh;
class cTransform;
class cSkinnedAnimation;
class cTerrain;

class cBaseObject
{
public:
	cTransform*			pTransform;
	cXMesh*				pMesh;						//니가 사용하는 메쉬가 뭐니?
	cBoundBox			BoundBox;
	bool				IgnoreCreateShadow;			//쉐도우맵 만들때 무시되니

	cSkinnedAnimation*	pSkinned;	//스킨드 Animtion

	//타입 정보
	OBJECT_TYPE			objType;
	MONSTER_TYPE		monType;

protected:
	bool				bActive;	//활성화 여부
	cTerrain*			pTerrain;	//터레인 정보


public:
	cBaseObject(void);
	~cBaseObject(void);

	void Update( float timeDelta );

	void Render(){
		if( this->bActive )
			this->BaseObjectRender();
	}

	//터레인을 셋팅한다.
	void SetTerrain(cTerrain* terrain) { pTerrain = terrain; }

	//랜더링 될 메쉬를 셋팅한다.
	void SetMesh( cXMesh*	pMesh );

	//활성화 셋팅
	void SetActive( bool bActive );

	//활성화 여부를 얻는다.
	bool IsActive() {
		return this->bActive;
	}

	//스킨드 애니메이션 얻는다.
	cSkinnedAnimation* GetSkinnedAnim() { return pSkinned; }

	//터레인을 얻는다.
	cTerrain* GetTerrain() { return pTerrain; }

	
	//셋팅된 메쉬에 따라 바운드박스를 재계산 한다.
	void ComputeBoundBox();	
	//

	void RenderShadow(){
		if (this->bActive)
			this->BaseObjectRenderShadow();
	}


protected:

	//override 해서 쓰시오....
	virtual void BaseObjectEnable() {}							//BaseObject 가 활성화 될때 실행
	virtual void BaseObjectDisable(){}							//BaseObject 가 비활성화 될때 실행
	virtual void BaseObjectUpdate( float timeDelta ) {}			//BaseObject 가 Update 때 실행....
	virtual void BaseObjectNoActiveUpdate( float timeDelte){}	//BaseObject 가 비활성화시 업데이트 실행....
	virtual void BaseObjectRender();							//BaseObject 를 그릴때 실행
	virtual void BaseObjectBoundBox();//BaseObject 의 바운드 박스를 세팅
	virtual void BaseObjectRenderShadow();						//BaseObject 를 그릴때 실행

    
};

