/************************************************************************************************/
/** 
 * @file		KsKeyFrame.h
 * @brief		カラー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSKEYFRAME_H__
#define __KSKEYFRAME_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsType.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * 
 * @class	
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsKeyFrame
{
	public:
		/**
		 * コンストラクタ
		 */
										KsKeyFrame() : m_time( 0.0f ) { m_scale.x = 1.0f; m_scale.y = 1.0f; m_scale.z = 1.0f; }

		/**
		 * デストラクタ
		 */
		virtual							~KsKeyFrame(){}

		KsReal							GetTime() const { return m_time; }
		const KsVector3d				GetPos()	{ return m_pos; }
		const KsQuaternion				GetRot()	{ return m_rot; }
		const KsVector3d				GetScale()	{ return m_scale; }

		void							SetTime( KsReal time ) const { m_time = time; }
		void							SetPos( const KsVector3d& pos )	{ m_pos = pos; }
		void							SetRot( const KsQuaternion& rot )	{ m_rot = rot; }
		void							SetScale( const KsVector3d& scale )	{ m_scale = scale; }

	protected:
		KsReal							m_time;		/**< 時間		*/
		KsVector3d						m_pos;		/**< 位置		*/
		KsQuaternion					m_rot;		/**< 回転		*/
		KsVector3d						m_scale;	/**< スケール	*/
};

class KsAnim
{
	private:
		typedef std::vector< KsKeyFrame* >		KsKeyFrameList;

		/**
		 * アニメの補完の種類
		 */
		enum ksANIM_INTERPOLATE_KIND
		{
			ksANIM_INTERPOLATE_LINEAR,		/**< 直線補完		*/
			ksANIM_INTERPOLATE_SPLINE,		/**< スプライン補完	*/
			// エルミート補完
		};

	public:
		/**
		 * コンストラクタ
		 */
										KsAnim();

		/**
		 * デストラクタ
		 */
		virtual							~KsAnim();

		/**
		 * キーフレームを追加する
		 * @param		pFrame			追加するキーフレーム
		 */
		void							AddKeyFrame( const KsKeyFrame* pFrame );

		/**
		 * 更新処理
		 * @param		dt				更新時間
		 * @note		時間は,[ 0.0f･･･1.0f ]で管理する
		 */
		void							Update( KsReal dt );

	protected:
		KsInt32							m_id;				/**< ID									*/
		KsInt32							m_startKeyFrame;	/**< 開始キーフレーム					*/
		KsInt32							m_lastKeyFrame;		/**< 終了キーフレーム					*/
		KsInt32							m_nextKeyFrame;		/**< 次のキーフレーム					*/
		KsReal							m_totalTime;		/**< トータル時間						*/
		KsReal							m_currentTime;		/**< 現在の時間							*/
		KsReal							m_offsetTime;		/**< 0.0fから1.0fの間にするまでの補正値	*/
		KsKeyFrameList					m_vKeyFrames;		/**< キーフレームリスト					*/
};


#endif		/* __KSKEYFRAME_H__ */
