/************************************************************************************************/
/** 
 * @file		KsShader.h
 * @brief		シェーダーマネージャー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSHADER_H__
#define __KSSHADER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsType.h"
#include "KsRefCounter.h"
#include "KsString.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsShader
 * @brief		シェーダー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		
 */
/************************************************************************************************/
class ksENGINE_API KsShader : public KsRefCounter
{
		friend class KsShaderManager;

	public:

		/**
		 * シェーダータイプ
		 */
		enum ksSHADER_TYPE
		{
			ksPIXEL_SHADER,
			ksVERTEX_SHADER,
			ksPIXEL_AND_VERTEX_SHADER,
		};

	public:
		/**
		 * コンストラクタ
		 */
									KsShader();

		/**
		 * デストラクタ
		 */
		virtual					~KsShader();

		/**
		 * シェーダ開始
		 */
		virtual void				begine() = 0;

		/**
		 * シェーダ終了
		 */
		virtual void				end() = 0;

		/**
		 * 指定パス開始
		 */
		virtual void				beginePass( KsUInt32 pass ) = 0;

		/**
		 * パス終了
		 */
		virtual void				endPass() = 0;

		/**
		 * テクニックをセットする
		 * @param	index			テクニックインデックス
		 */
		virtual void				setTechnique( KsUInt32 index ) = 0;

		/**
		 * テクニックをセットする
		 * @param	hTechnique		テクニックハンドル
		 */
		virtual void				setTechnique( KsHandle hTechnique ) = 0;

		/**
		  * テクニックをセットする
		 * @param	pTechniqueName	テクニック名
		 */
		virtual void				setTechnique( const KsChar* pTechniqueName ) = 0;

		/**
		 * テクニックのハンドル取得する
		 * @param	pTechniqueName	テクニック名
		 * @return					テクニックのハンドル
		 */
		virtual KsHandle			getTechnique( const KsChar* pTechniqueName ) = 0;

		virtual void				setVertexShaderConstantB( KsUInt32 startRegister, const KsBool*  pConstantData, KsUInt32 count ) = 0;
		virtual void				setVertexShaderConstantF( KsUInt32 startRegister, const KsReal*  pConstantData, KsUInt32 count ) = 0;
		virtual void				setVertexShaderConstantI( KsUInt32 startRegister, const KsInt32* pConstantData, KsUInt32 count ) = 0;

		virtual void				setPixelShaderConstantB( KsUInt32 startRegister, const KsBool*  pConstantData, KsUInt32 count ) = 0;
		virtual void				setPixelShaderConstantF( KsUInt32 startRegister, const KsReal*  pConstantData, KsUInt32 count ) = 0;
		virtual void				setPixelShaderConstantI( KsUInt32 startRegister, const KsInt32* pConstantData, KsUInt32 count ) = 0;

		/**
		 * シェーダーIDを取得する
		 * @return					シェーダーID
		 */
		KsUInt32					getID() const { return m_id; }

		/**
		 * シェーダー名を取得する
		 * @return					シェーダー名
		 */
		const KsString&				getName() { return m_name; }

		/**
		 * 現在のテクニック番号を取得する
		 * @return					現在のテクニック番号
		 */
		KsHandle					getCurrentTechnique() const { return m_hCurrentTechnique; }

		/** 
		 * テクニック数を取得する
		 * @return					テクニック数
		 */
		KsUInt32					getNumTechnique() const { return m_numTechnique; }

		/**
		 * パス数を取得する
		 * @return					パス数
		 */
		KsUInt32					getNumPass() const { return m_numPass; }

	protected:
		KsUInt32					m_id;					/**< シェーダーID				*/
		KsString					m_name;					/**< シェーダー名				*/
		KsHandle					m_hCurrentTechnique;	/**< 使用テクニックインデックス	*/
		KsUInt32					m_numTechnique;			/**< テクニック数				*/
		KsUInt32					m_numPass;				/**< パス数						*/

		//void						setViewMatrx();
		//void						setVierProjMatrix();
		//void						setTime();
};


#endif		/* __KSSHADER_H__ */

