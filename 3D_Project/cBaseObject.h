#pragma once

class cXMesh;
class cTransform;
class cSkinnedAnimation;
class cTerrain;

class cBaseObject
{
public:
	cTransform*			pTransform;
	cXMesh*				pMesh;						//�ϰ� ����ϴ� �޽��� ����?
	cBoundBox			BoundBox;
	bool				IgnoreCreateShadow;			//������� ���鶧 ���õǴ�

	cSkinnedAnimation*	pSkinned;	//��Ų�� Animtion

	//Ÿ�� ����
	OBJECT_TYPE			objType;
	MONSTER_TYPE		monType;

protected:
	bool				bActive;	//Ȱ��ȭ ����
	cTerrain*			pTerrain;	//�ͷ��� ����


public:
	cBaseObject(void);
	~cBaseObject(void);

	void Update( float timeDelta );

	void Render(){
		if( this->bActive )
			this->BaseObjectRender();
	}

	//�ͷ����� �����Ѵ�.
	void SetTerrain(cTerrain* terrain) { pTerrain = terrain; }

	//������ �� �޽��� �����Ѵ�.
	void SetMesh( cXMesh*	pMesh );

	//Ȱ��ȭ ����
	void SetActive( bool bActive );

	//Ȱ��ȭ ���θ� ��´�.
	bool IsActive() {
		return this->bActive;
	}

	//��Ų�� �ִϸ��̼� ��´�.
	cSkinnedAnimation* GetSkinnedAnim() { return pSkinned; }

	//�ͷ����� ��´�.
	cTerrain* GetTerrain() { return pTerrain; }

	
	//���õ� �޽��� ���� �ٿ��ڽ��� ���� �Ѵ�.
	void ComputeBoundBox();	
	//

	void RenderShadow(){
		if (this->bActive)
			this->BaseObjectRenderShadow();
	}


protected:

	//override �ؼ� ���ÿ�....
	virtual void BaseObjectEnable() {}							//BaseObject �� Ȱ��ȭ �ɶ� ����
	virtual void BaseObjectDisable(){}							//BaseObject �� ��Ȱ��ȭ �ɶ� ����
	virtual void BaseObjectUpdate( float timeDelta ) {}			//BaseObject �� Update �� ����....
	virtual void BaseObjectNoActiveUpdate( float timeDelte){}	//BaseObject �� ��Ȱ��ȭ�� ������Ʈ ����....
	virtual void BaseObjectRender();							//BaseObject �� �׸��� ����
	virtual void BaseObjectBoundBox();//BaseObject �� �ٿ�� �ڽ��� ����
	virtual void BaseObjectRenderShadow();						//BaseObject �� �׸��� ����

    
};

