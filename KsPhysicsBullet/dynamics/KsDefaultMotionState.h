/************************************************************************************************/
/** 
 * @file		KsDefaultMotionState.h
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSDEFAULTMOTIONSTATE_H__
#define __KSDEFAULTMOTIONSTATE_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsDefaultMotionState
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
class ksPHYSICSBULLET_API KsDefaultMotionState : public KsMotionState
{
	public:
		/**
		 * コンストラクタ
		 */
									KsDefaultMotionState( const KsMatrix4x4& refTransform );

		/**
		 * デストラクタ
		 */
		virtual						~KsDefaultMotionState();

		/**
		 * リソースを取得する
		 * @return					 リソース
		 */
		virtual void*				getMotionStateResource();

	private:
		btDefaultMotionState*		m_pMotionState;
};

#endif		/* __KSDEFAULTMOTIONSTATE_H__ */

