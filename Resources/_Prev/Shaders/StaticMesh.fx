
//
// 전역변수
//

float4x4 matWorld : World;
float4x4 matViewProjection : ViewProjection;
float4 vEyePos : ViewPosition;

float camNear;			//카메라 근거리 평면
float camFar;			//카메라 원거리 평면



texture Diffuse_Tex;
sampler2D Diffuse = sampler_state
{
   Texture = (Diffuse_Tex);
   MAGFILTER = LINEAR;
   MIPFILTER = LINEAR;
   MINFILTER = LINEAR;
};
texture Normal_Tex;
sampler2D Normal = sampler_state
{
   Texture = (Normal_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
   MIPFILTER = LINEAR;
};

texture Specular_Tex;
sampler2D Specular = sampler_state
{
   Texture = (Specular_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
   MIPFILTER = LINEAR;
};


texture Emission_Tex;
sampler2D Emission = sampler_state
{
   Texture = (Emission_Tex);
   MAGFILTER = LINEAR;
   MIPFILTER = LINEAR;
   MINFILTER = LINEAR;
};

float fSpecPower;

// 라이트 행렬
// Pos.x,         Pos.y,          Pos.z,         lightType ( 0 Direction, 1 Point, 2 Spot )
// Dir.x,         Dir.y,          Dir.z,         DistancePow;
// Color.r,       Color.g,        Color.b,       strength
// MaxRange,      MinRange,       InAngle        OutAngle 
float4x4 matLights[10];
int LightNum = 0;

float4x4 baseDirectionLight;			//기본라이팅 행렬





//---------------------------------------------------------------
// Base 관련
//---------------------------------------------------------------

struct VS_INPUT 
{
   float4 Position : POSITION0;
   float2 Texcoord : TEXCOORD0;
   float3 Normal : NORMAL0;
   float3 Binormal : BINORMAL0;
   float3 Tangent : TANGENT0;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float2 Texcoord : TEXCOORD0;
   float3 Normal : TEXCOORD1;
   float3 Binormal : TEXCOORD2;
   float3 Tangent : TEXCOORD3;
   float3 viewDir : TEXCOORD4;
   float3 worldPos : TEXCOORD5;
};

VS_OUTPUT vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output = (VS_OUTPUT)0;

   float4 worldPos = mul( Input.Position, matWorld );
   Output.Position = mul( worldPos, matViewProjection );
   
   Output.Texcoord = Input.Texcoord;
   
   Output.Normal = mul( Input.Normal, (float3x3)matWorld );
   Output.Binormal = mul( Input.Binormal, (float3x3)matWorld );  
   Output.Tangent = mul( Input.Tangent, (float3x3)matWorld ); 
   
   Output.viewDir = vEyePos.xyz - worldPos.xyz;
   Output.worldPos = worldPos;

   return( Output );
}




struct PS_INPUT
{
   float2 Texcoord : TEXCOORD0;
   float3 Normal : TEXCOORD1;
   float3 Binormal : TEXCOORD2;
   float3 Tangent : TEXCOORD3;
   float3 viewDir : TEXCOORD4;
   float3 worldPos : TEXCOORD5;
};




void ComputeLight( 
		out float3 addDiffuse,			//계산되서 나가는 DeffuseColor
		out float3 addSpecular,			//계산되서 나가는 SpecularColor
		float3 position,				//위치 값
		float3 normal,					//노말
		float3 viewDir,					//시선 방향
		int lightIndex					//처리되는 라이트 인덱스
		)
{
	float4x4 matLight = matLights[ lightIndex ];

	float3 lightColor = float3( matLight._31, matLight._32, matLight._33 ) * matLight._34;

	//Direction 처리
	if( matLight._14 == 0.0f )
	{
		//광원의 방향
		float3 dir = float3( matLight._21, matLight._22, matLight._23 );
		float3 lightDir = -dir;

		float NdotL = dot( lightDir, normal );
		float diff = saturate( NdotL );

		//라이트 반사
		float3 lightRefl = normalize( dir + 2.0f * NdotL * normal );
		float spec = saturate( dot( lightRefl, viewDir ) );
		spec = pow( spec, fSpecPower );
		
		addDiffuse = lightColor * diff;
		addSpecular =  lightColor * spec * diff;
	}

	//Point Light and Spot 처리
	else
	{
		float3 lightPosition = float3( matLight._11, matLight._12, matLight._13 );
		float maxRange = matLight._41;
		float minRange = matLight._42;
		float DistancePow = matLight._24;

		//광원의 방향
		float3 lightDir = lightPosition - position;

		//광원의 거리
		float dist = length( lightDir );
		
		//정규화
		lightDir *= ( 1.0f / dist );

		//광원 량....
		float NdotL = dot( lightDir, normal );
		float diff = saturate( NdotL );

		//거리에 따른 감쇠율
		float t = saturate( ( dist - minRange ) / ( maxRange - minRange ) );
		t = 1.0f - pow( t, DistancePow );
		
		//만약 Spot 이라면....

		

		diff *= t;			//받는 광원 량에 감쇠율 적용

		//라이트 반사
		float3 lightRefl = normalize( -lightDir + 2.0f * NdotL * normal );
		float spec = saturate( dot( lightRefl, viewDir ) );
		spec = pow( spec, fSpecPower );
		
		addDiffuse = lightColor * diff;
		addSpecular =  lightColor * spec * diff;		//Spec 은 Diff 의 영향을 받는다.


	}

	


}


float4 ps_main( PS_INPUT Input ) : COLOR0
{   
     //TBN Matrix
     float3x3 TBN = float3x3(
        normalize( Input.Tangent ),
        normalize( Input.Binormal ),
        normalize( Input.Normal ) );
     
	 //   
     // WorldNormal
     //
     float3 norColor = tex2D( Normal, Input.Texcoord ).rgb;
     
	 //Tangent Space Normal
     float3 spaceNor = ( norColor * 2.0f ) - 1.0f;

     float3 worldNormal = mul( spaceNor, TBN );
     float3 viewDir = normalize( Input.viewDir );
  
	 //최종 색
	 float3 finalDiffuse = float3( 0, 0, 0 );
	 float3 finalSpecular = float3( 0, 0, 0 );

	 //기본 라이팅 처리

	 //광원의 방향
	 float3 dir = float3( baseDirectionLight._21, baseDirectionLight._22, baseDirectionLight._23 );
 	 float3 lightDir = -dir;
	 
	 //광원의 컬러
	 float3 lightColor = float3( baseDirectionLight._31, baseDirectionLight._32, baseDirectionLight._33 ) * baseDirectionLight._34;

	 
	 float NdotL = dot( lightDir, worldNormal );
	 
	 //Ambient
	 //float diff = saturate( NdotL );
	 
	 //float diff = max( 0.1f, NdotL );
	 
	 float diff = NdotL;
	 if( diff < 0.0 )
		diff = abs( NdotL ) * 0.3f;


	 //라이트 반사
	 float3 lightRefl = normalize( dir + 2.0f * NdotL * worldNormal );
	 float spec = saturate( dot( lightRefl, viewDir ) );
	 spec = pow( spec, fSpecPower );
	
	 //기본 광원 적용
	 finalDiffuse = lightColor * diff;
	 finalSpecular =  lightColor * spec * diff;		//Specular 에 diff 안곱하면 Specular 에 의한 역광이 나온다...




	 //추가되는 광원
	 float3 addDiffuse = float3( 0, 0, 0 );
	 float3 addSpecular = float3( 0, 0, 0 );
	 for( int i = 0 ; i < LightNum ; i++ )
	 {
		//i 인덱스의 광원이 계산되어 addDiffuse, addSpecular 에 대입된다.
		ComputeLight( 
			addDiffuse, 
			addSpecular,
			Input.worldPos, 
			worldNormal,
			viewDir,
			i );

		//최종 광원 량에 쌓인다.
		finalDiffuse += addDiffuse;
		finalSpecular += addSpecular;
	 }


     //
     // Diffuse
     //
     float3 diffuseColor = tex2D( Diffuse, Input.Texcoord ).rgb * finalDiffuse;
     
     //
     // Specular 
     //
     float3 specularColor = tex2D( Specular, Input.Texcoord ).rgb * finalSpecular;
     
     //
     // Emission
     //
     float3 emissionColor = tex2D( Emission, Input.Texcoord ).rgb;
		
     //
     // Final Color 
     //
     float3 finalColor = diffuseColor + specularColor + emissionColor;
      
     return float4( finalColor, 1 );
   
}



//나무 전용 PixelShader
float4 ps_mainTree( PS_INPUT Input ) : COLOR0
{   
	float4 diffTex = tex2D( Diffuse, Input.Texcoord );
	clip( diffTex.a - 0.1f );


     //TBN Matrix
     float3x3 TBN = float3x3(
        normalize( Input.Tangent ),
        normalize( Input.Binormal ),
        normalize( Input.Normal ) );
     
	 //   
     // WorldNormal
     //
     float3 norColor = tex2D( Normal, Input.Texcoord ).rgb;
     
	 //Tangent Space Normal
     float3 spaceNor = ( norColor * 2.0f ) - 1.0f;

     float3 worldNormal = mul( spaceNor, TBN );
     float3 viewDir = normalize( Input.viewDir );
  
	 //최종 색
	 float3 finalDiffuse = float3( 0, 0, 0 );
	 float3 finalSpecular = float3( 0, 0, 0 );

	 //기본 라이팅 처리

	 //광원의 방향
	 float3 dir = float3( baseDirectionLight._21, baseDirectionLight._22, baseDirectionLight._23 );
 	 float3 lightDir = -dir;
	 
	 //광원의 컬러
	 float3 lightColor = float3( baseDirectionLight._31, baseDirectionLight._32, baseDirectionLight._33 ) * baseDirectionLight._34;

	 
	 float NdotL = dot( lightDir, worldNormal );
	 
	 //Ambient
	 //float diff = saturate( NdotL );
	 
	 float diff = max( 0.3f, NdotL );
	 
	 //float diff = NdotL;
	 //if( diff < 0.0 )
	 //	diff = abs( NdotL ) * 0.1f;


	 //라이트 반사
	 float3 lightRefl = normalize( dir + 2.0f * NdotL * worldNormal );
	 float spec = saturate( dot( lightRefl, viewDir ) );
	 spec = pow( spec, fSpecPower );
	
	 //기본 광원 적용
	 finalDiffuse = lightColor * diff;
	 finalSpecular =  lightColor * spec * diff;		//Specular 에 diff 안곱하면 Specular 에 의한 역광이 나온다...




	 //추가되는 광원
	 float3 addDiffuse = float3( 0, 0, 0 );
	 float3 addSpecular = float3( 0, 0, 0 );
	 for( int i = 0 ; i < LightNum ; i++ )
	 {
		//i 인덱스의 광원이 계산되어 addDiffuse, addSpecular 에 대입된다.
		ComputeLight( 
			addDiffuse, 
			addSpecular,
			Input.worldPos, 
			worldNormal,
			viewDir,
			i );

		//최종 광원 량에 쌓인다.
		finalDiffuse += addDiffuse;
		finalSpecular += addSpecular;
	 }


     //
     // Diffuse
     //
	 
     float3 diffuseColor = diffTex.rgb * finalDiffuse;
     
     //
     // Specular 
     //
     float3 specularColor = tex2D( Specular, Input.Texcoord ).rgb * finalSpecular;
     
     //
     // Emission
     //
     float3 emissionColor = tex2D( Emission, Input.Texcoord ).rgb;
		
     //
     // Final Color 
     //
     float3 finalColor = diffuseColor + specularColor + emissionColor;
      

	  
     return float4( finalColor, 1 );
   
}



//---------------------------------------------------------------
// Depth 관련
//---------------------------------------------------------------

struct VS_INPUT_DEPTH
{
   float4 Position : POSITION0;
   float2 Texcoord : TEXCOORD0;
};

struct VS_OUTPUT_DEPTH
{
   float4 Position : POSITION0;
   float4 FinalPos : TEXCOORD0;
   float2 Texcoord : TEXCOORD1;

};


VS_OUTPUT_DEPTH vs_depth( VS_INPUT_DEPTH Input )
{
   VS_OUTPUT_DEPTH Output = (VS_OUTPUT_DEPTH)0;

   float4 worldPos = mul( Input.Position, matWorld );
   Output.Position = mul( worldPos, matViewProjection );
   
   Output.FinalPos = Output.Position;

   Output.Texcoord = Input.Texcoord;

   return( Output );
}


float4 ps_depth( VS_OUTPUT_DEPTH Input ) : COLOR0
{   
	//행렬변환을 거친 값 z 에 행렬변환에서 얻는 가중치 w 를 나누면 0 ~ 1 사이의 깊이 값이 된다.
	float depth = Input.FinalPos.z / Input.FinalPos.w;

	//위의 depth 값을 카메라의 near 와 far 를 이용하여 선형으로 펴준다....
	//Perspective Projection Linear Depth
    float z = depth;
    float a = camFar / ( camFar - camNear );
    float b = -camNear / ( camFar - camNear );
    depth = b / ( z - a ); 


    return float4( depth, depth, depth, 1 );
}



//---------------------------------------------------------------
// CreateShadow 관련
//---------------------------------------------------------------

float4 ps_CreateShadow( VS_OUTPUT_DEPTH Input ) : COLOR0
{   
	//행렬변환을 거친 값 z 에 행렬변환에서 얻는 가중치 w 를 나누면 0 ~ 1 사이의 깊이 값이 된다.
	float depth = Input.FinalPos.z / Input.FinalPos.w;


	float4 diffTex = tex2D( Diffuse, Input.Texcoord );
	clip( diffTex.a - 0.1f );

    //return float4( depth, depth, depth, 1 );

	return float4( depth.xxx, 1 );
}


//--------------------------------------------------------------//
// Render With ShadowMap 
//--------------------------------------------------------------//


float4x4 matLightViewProjection;			//방향성 광원 ViewProjection 행렬

//쉐도우 Texture
texture Shadow_Tex;
sampler2D ShadowSampler = sampler_state
{
   Texture = (Shadow_Tex);
   ADDRESSU = BORDER;
   ADDRESSV = BORDER;
   BORDERCOLOR = 0xFFFFFFFF;
};

float bias = 0.01f;


struct VS_INPUT_RECIVESHADOW
{
   float4 Position : POSITION0;
   float2 Texcoord : TEXCOORD0;
   float3 Normal : NORMAL0;
   float3 Binormal : BINORMAL0;
   float3 Tangent : TANGENT0;
};

struct VS_OUTPUT_RECIVESHADOW
{
   float4 Position : POSITION0;
   float2 Texcoord : TEXCOORD0;
   float3 Normal : TEXCOORD1;
   float3 Binormal : TEXCOORD2;
   float3 Tangent : TEXCOORD3;
   float3 viewDir : TEXCOORD4;
   float3 worldPos : TEXCOORD5;

   float4 FinalPos : TEXCOORD6;
   float4 LightClipPos : TEXCOORD7;		//광원 입장에서 바라본 위치
};


VS_OUTPUT_RECIVESHADOW vs_ReciveShadow( VS_INPUT_RECIVESHADOW Input )
{
   VS_OUTPUT_RECIVESHADOW Output = (VS_OUTPUT_RECIVESHADOW)0;

   float4 worldPos = mul( Input.Position, matWorld );
   Output.Position = mul( worldPos, matViewProjection );
   
   Output.Texcoord = Input.Texcoord;
   
   Output.Normal = mul( Input.Normal, (float3x3)matWorld );
   Output.Binormal = mul( Input.Binormal, (float3x3)matWorld );  
   Output.Tangent = mul( Input.Tangent, (float3x3)matWorld ); 
   
   Output.viewDir = vEyePos.xyz - worldPos.xyz;
   Output.worldPos = worldPos;


   Output.FinalPos = Output.Position;		//변환 정보
   Output.LightClipPos = mul( worldPos, matLightViewProjection );	//광원 입장에서 본 위치

   return( Output );
}


float4 ps_ReciveShadow( VS_OUTPUT_RECIVESHADOW Input ) : COLOR0
{  
	//광원 입장에서 바라본 위치의 뎁스 값 ( 라이트 행렬을 직교이기때문에 선형으로 안핀다 )
	float lightDepth = Input.LightClipPos.z / Input.LightClipPos.w;

	//Shadow 맵의 UV 추적
	//( -1 ~ 1 )
	float2 shadowUV = Input.LightClipPos.xy / Input.LightClipPos.w;
	shadowUV.y = -shadowUV.y;		//y반전...
	//0 ~ 1 의 범위
	shadowUV = ( shadowUV * 0.5f ) + 0.5f;	

	//현제 그려지는 놈이 위치에 DirectionLight 입장에서 써진 깊이값...
	float shadowDepth = tex2D( ShadowSampler, shadowUV ).r;

	//그림자가 그려지는 상황은 shadowDepth + bias 값 보다 lightDepth 가 큰경우이다.




	//TBN Matrix
    float3x3 TBN = float3x3(
       normalize( Input.Tangent ),
       normalize( Input.Binormal ),
       normalize( Input.Normal ) );
     
	 //   
     // WorldNormal
     //
     float3 norColor = tex2D( Normal, Input.Texcoord ).rgb;
     
	 //Tangent Space Normal
     float3 spaceNor = ( norColor * 2.0f ) - 1.0f;

     float3 worldNormal = mul( spaceNor, TBN );
	 worldNormal = normalize( worldNormal );
     float3 viewDir = normalize( Input.viewDir );
  
	 //최종 색
	 float3 finalDiffuse = float3( 0, 0, 0 );
	 float3 finalSpecular = float3( 0, 0, 0 );

	 //기본 라이팅 처리

	 //광원의 방향
	 float3 dir = float3( baseDirectionLight._21, baseDirectionLight._22, baseDirectionLight._23 );
 	 float3 lightDir = -dir;
	 
	 //광원의 컬러
	 float3 lightColor = float3( baseDirectionLight._31, baseDirectionLight._32, baseDirectionLight._33 ) * baseDirectionLight._34;

	 
	 float NdotL = dot( lightDir, worldNormal );
	 
	 //Ambient
	 //float diff = saturate( NdotL );
	 
	 //float diff = max( 0.1f, NdotL );
	 
	 float diff = NdotL;
	 
	 //그림자가 그려져야 한다면 diff 는 무조건 음수가 된다 
	 if( shadowDepth + bias < lightDepth )
		diff = abs( diff ) * -1.0f;

	 if( diff < 0.0 )
		diff = abs( diff ) * 0.3f;

	 //라이트 반사
	 float3 lightRefl = normalize( dir + 2.0f * NdotL * worldNormal );
	 float spec = saturate( dot( lightRefl, viewDir ) );
	 spec = pow( spec, fSpecPower );
	
	 //기본 광원 적용
	 finalDiffuse = lightColor * diff;
	 finalSpecular =  lightColor * spec * diff;		//Specular 에 diff 안곱하면 Specular 에 의한 역광이 나온다...


	 //추가되는 광원
	 float3 addDiffuse = float3( 0, 0, 0 );
	 float3 addSpecular = float3( 0, 0, 0 );
	 for( int i = 0 ; i < LightNum ; i++ )
	 {
		//i 인덱스의 광원이 계산되어 addDiffuse, addSpecular 에 대입된다.
		ComputeLight( 
			addDiffuse, 
			addSpecular,
			Input.worldPos, 
			worldNormal,
			viewDir,
			i );

		//최종 광원 량에 쌓인다.
		finalDiffuse += addDiffuse;
		finalSpecular += addSpecular;
	 }


     //
     // Diffuse
     //
     float3 diffuseColor = tex2D( Diffuse, Input.Texcoord ).rgb * finalDiffuse;
     
     //
     // Specular 
     //
     float3 specularColor = tex2D( Specular, Input.Texcoord ).rgb * finalSpecular;
     
     //
     // Emission
     //
     float3 emissionColor = tex2D( Emission, Input.Texcoord ).rgb;
		
     //
     // Final Color 
     //
     float3 finalColor = diffuseColor + specularColor + emissionColor;
      
     return float4( finalColor, 1 );


}







//--------------------------------------------------------------//
// Technique Section for Mesh
//--------------------------------------------------------------//
technique Base
{
   pass Pass_0
   {
      VertexShader = compile vs_3_0 vs_main();
      PixelShader = compile ps_3_0 ps_main();
   }
}

technique BaseTree
{
   pass Pass_0
   {
	  CULLMODE = NONE;
      VertexShader = compile vs_3_0 vs_main();
      PixelShader = compile ps_3_0 ps_mainTree();
   }
}


technique Depth
{
   pass Pass_0
   {
      VertexShader = compile vs_3_0 vs_depth();
      PixelShader = compile ps_3_0 ps_depth();
   }
}


technique CreateShadow
{
   pass Pass_0
   {
      VertexShader = compile vs_3_0 vs_depth();
      PixelShader = compile ps_3_0 ps_CreateShadow();
   }
}





technique ReciveShadow
{
   pass Pass_0
   {
      VertexShader = compile vs_3_0 vs_ReciveShadow();
      PixelShader = compile ps_3_0 ps_ReciveShadow();
   }
}