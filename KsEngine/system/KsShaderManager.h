/************************************************************************************************/
/** 
 * @file		KsShaderManager.h
 * @brief		シェーダーマネージャー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSHADERMANAGER_H__
#define __KSSHADERMANAGER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsType.h"
#include "KsSingleton.h"
#include "KsHash.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsShader;

/************************************************************************************************/
/**
 * @class		KsShaderManager
 * @brief		シェーダーマネージャー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		本当は、ハッシュテーブルなどを使用したほうがいいがあまりテクスチャマテリアルは、
 *				あまり、使わないはずなので線形で探索する。
 */
/************************************************************************************************/
class ksENGINE_API KsShaderManager : public KsSingleton< KsShaderManager >
{
	public:
		/** 
		 * シェーダーパラメータ
		 */
		enum ksSHADER_PARAM
		{
			ksSHADER_TIME,
			ksSHADER_WORLD_MATRIX,
			ksSHADER_VIEW_MATRIX,
			ksSHADER_WORLD_VIEW_MATRIX,
			ksSHADER_VIEW_PROJECTION_MATRIX,
			ksSHADER_WORLD_VIEW_PROJECTION_MATRIX,
			ksSHADER_MATERIAL_DIFFUSE,
			ksSHADER_MATERIAL_AMBIENT,
			ksSHADER_MATERIAL_SPECULER,
			ksSHADER_LIGHT_DIFFUSE,
			ksSHADER_LIGHT_AMBIENT,
			ksSHADER_LIGHT_SPECULER,
			ksSHADER_GLOBAL_DATA_MAX,
			ksSHADER_FORCE32          = 0x7fffffff,
		};
#if 0
		static const KsChar*	 s_globalShaderDataParams[] = 
		{
			"g_fTime",
			"g_ViewMatrix",
			"g_ViewProjectionMatrix",
			"g_materialDiffuseColor",
			"g_materialAmbientColor",
			"g_materialAmbientColor",
		};
#endif

	public:
		/**
		 * コンストラクタ
		 */
									KsShaderManager(){}

		/**
		 * デストラクタ
		 */
		virtual					~KsShaderManager(){}

		/**
		 * ファイルからシェーダーを生成
		 * @param	_bCompiled		コンパイル済みかどうかのフラグ
		 * @return					シェーダーデータのポインタ
		 */
		virtual KsShader*			createFromFile( const KsChar* pName, KsBool _bCompiled ) = 0;

		/**
		 * リソースからシェーダーを生成
		 * @param	_bCompiled		コンパイル済みかどうかのフラグ
		 * @return					シェーダーデータのポインタ
		 */
		virtual KsShader*			createFromResource( const KsChar* pName, KsBool _bCompiled ) = 0;

		/**
		 * 指定した名前のシェーダーを検索する
		 * 取得した後に参照カウントをあげる必要がある
		 * @param	pName			ファイル名
		 * @return					見つかったシェーダーのポインタ
		 */
		virtual KsShader*			find( const KsChar* pName );

		/**
		 * 検索して見つかったら参照カウントをアップする
		 * @param	pName			ファイル名
		 * @return					見つかったシェーダーのポインタ
		 */
		virtual KsShader*			findRefInc( const KsChar* pName );

		/**
		 * シェーダーを追加する
		 * DEBUGモードのときは、2重登録チェックをする
		 * @param	pShader			追加するシェーダーのポインタ
		 * @retval	ksTRUE			成功
		 * @retval	ksFALSE			失敗
		 */
		virtual KsBool				add( KsShader* pShader );

		/**
		 * シェーダーをマネージャから取り除く
		 * @param	pShader			取り除くシェーダーのポインタ
		 * @retval	ksTRUE			成功
		 * @retval	ksFALSE			失敗
		 */
		virtual KsBool				remove( KsShader* pShader );

		/**
		 * シェーダーを削除する
		 * @param	pShader			削除するシェーダーのポインタ
		 * @retval	ksTRUE			成功
		 * @retval	ksFALSE			失敗
		 */
		virtual KsBool				destroy( KsShader* pShader );

		/**
		 * すべてのシェーダーを破棄する(参照カウント関係なく破棄される)
		 * @retval	ksTRUE			成功
		 * @retval	ksFALSE			失敗
		 */
		virtual KsBool				destroyAll();


		virtual void				setVertexShaderConstantB( KsUInt32 startRegister, const KsBool*  pConstantData, KsUInt32 count ) = 0;
		virtual void				setVertexShaderConstantF( KsUInt32 startRegister, const KsReal*  pConstantData, KsUInt32 count ) = 0;
		virtual void				setVertexShaderConstantI( KsUInt32 startRegister, const KsInt32* pConstantData, KsUInt32 count ) = 0;

		virtual void				setPixelShaderConstantB( KsUInt32 startRegister, const KsBool*  pConstantData, KsUInt32 count ) = 0;
		virtual void				setPixelShaderConstantF( KsUInt32 startRegister, const KsReal*  pConstantData, KsUInt32 count ) = 0;
		virtual void				setPixelShaderConstantI( KsUInt32 startRegister, const KsInt32* pConstantData, KsUInt32 count ) = 0;

#if 0
		virtual void				setTime( KsReal fTime ) = 0;
		virtual void				setViewMatrix( const KsMatrix4x4* pMatrix ) = 0;
		virtual void				setViewProjectionMatrix( const KsMatrix4x4* pMatrix ) = 0;
		virtual void				setWorldViewProjectionMatrix( const KsMatrix4x4* pMatrix ) = 0;
		virtual void				setWorldMatrix( const KsMatrix4x4* pMatrix ) = 0;

		virtual void				setMaterialDiffuse( const KsColorReal* pColor ) = 0;
		virtual void				setMaterialAmbient( const KsColorReal* pColor ) = 0;
		virtual void				setMaterialSpeculer( const KsColorReal* pColor ) = 0;
		virtual void				setLightDiffuse( const KsColorReal* pColor ) = 0;
		virtual void				setLightAmbient( const KsColorReal* pColor ) = 0;
		virtual void				setLightSpeculer( const KsColorReal* pColor ) = 0;
		//setVertexDeclaration

		HRESULT CreateVertexDeclaration(          CONST D3DVERTEXELEMENT9* pVertexElements,
    IDirect3DVertexDeclaration9** ppDecl
);

typedef struct _D3DVERTEXELEMENT9 {
    WORD Stream;
    WORD Offset;
    BYTE Type;
    BYTE Method;
    BYTE Usage;
    BYTE UsageIndex;
} D3DVERTEXELEMENT9;

HRESULT SetVertexDeclaration(          IDirect3DVertexDeclaration9 *pDecl
);

#endif
	protected:
		KsHashTable< KsShader* >	m_pShaders;		/**< シェーダーリスト	*/

	public:
		/**
		 * シングルトンの参照を取得
		 * @return					シングルトンの参照
		 */
		static KsShaderManager&		getInstance();
		
		/**
		 * シングルトンのポインタを取得
		 * @return					シングルトンのポインタ
		 */
		static KsShaderManager*		getInstancePtr();
};

#endif		/* __KSSHADERMANAGER_H__ */




