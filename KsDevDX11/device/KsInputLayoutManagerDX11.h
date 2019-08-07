/************************************************************************************************/
/** 
 * @file		KsInputLayoutManagerDX11.h
 * @brief		入力レイアウトマネージャ(DirectX11)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSINPUTLAYOUTMANAGERDX11_H__
#define __KSINPUTLAYOUTMANAGERDX11_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsRenderSystemDX11;

/************************************************************************************************/
/**
 * @class		KsInputLayoutManagerDX11
 * @brief		入力レイアウトマネージャ(DirectX11)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsInputLayoutManagerDX11 : public KsInputLayoutManager
{
	public:
		/**
		 * コンストラクタ
		 */
											KsInputLayoutManagerDX11( KsRenderSystemDX11* pRenderSystem );

		/**
		 * デストラクタ
		 */
		virtual								~KsInputLayoutManagerDX11();

		/**
		 * インプットレイアウトを生成する
		 * @param		numIndex			インデックス数
		 * @param		flags				フラグ
		 * @return							インプットレイアウトのポインタ
		 */
		virtual KsInputLayout*				createInputLayout( const KS_INPUT_ELEMENT_DESC* pInputElementDescs, KsUInt32 numElements, const KsVertexShader* pVertexShader );

	protected:
		 KsRenderSystemDX11*				m_pRenderSystem;
};

#endif		/* __KSINPUTLAYOUTMANAGERDX11_H__ */



