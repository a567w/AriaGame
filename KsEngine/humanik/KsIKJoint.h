/************************************************************************************************/
/** 
 * @file		KsIKJoint.h
 * @brief		人間用IK
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#ifndef __KSIKJOINT_H__
#define __KSIKJOINT_H__

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsIKJoint
 * @brief		IK用ジョイント
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsIKJoint
{
	public:
		/**
		 * コンストラクタ
		 */
		KsIKJoint();

		/**
		 * デストラクタ
		 */
		virtual						~KsIKJoint();

		/**
		 * IK制御用パラメータを取得する
		 * @param	index			インデックス
		 * @return					IK制御用パラメータ
		 */
		//KsIKParameter*				getIKParameter( KsInt32 index );

	public:
};

#endif		/* __KSIKJOINT_H__ */

