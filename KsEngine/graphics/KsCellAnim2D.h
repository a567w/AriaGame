/************************************************************************************************/
/** 
 * @file		KsCellAnim.h
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KsCellAnim2D_H__
#define __KsCellAnim2D_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsCore.h"
#include "KsArray.h"
#include "KsAnim2DPart.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsRenderSystem;

/*

セルアニメファイルフォーマット

ファイルヘッダー
signature	4byte

struct KS_CELLANIM_FILEHEADER
{
	signature;
	version;


	numPart;
	numTexture;
	numTrack;

	startFrame;
	endFrame;
	fps;

};


*/
namespace test
{


class KsCellAnimKeyFrame
{
	public:

		/**
		 * アニメフラグ
		 */
		enum ksCELL_ANIM_FLAGS
		{
			ksCELL_ANIM_HIDE = 1 << 0,
		};

		/**
		 * アニメキータイプ
		 */
		enum ksCELL_ANIM_KEY_TYPE
		{
			ksCELL_ANIM_KEY_POS      = 1 << 0,	/**< 位置				*/
			ksCELL_ANIM_KEY_ROT      = 1 << 1,	/**< 回転				*/
			ksCELL_ANIM_KEY_SCALE    = 1 << 2,	/**< スケール			*/
			ksCELL_ANIM_KEY_COLOR    = 1 << 3,	/**< カラー				*/
			ksCELL_ANIM_KEY_UV       = 1 << 4,	/**< UV					*/
			ksCELL_ANIM_KEY_PRIORITY = 1 << 5,	/**< プライオリティー	*/
			ksCELL_ANIM_KEY_USERDATA = 1 << 6,	/**< ユーザーデータ		*/
		};

		/**
		 * 
		 */
		struct POS
		{
			KsReal		x;			/**< Y位置座標		*/
			KsReal		y;			/**< X位置座標		*/
		};

		/**
		 * 
		 */
		struct ROT
		{
			KsReal		angle;		/**< 回転値			*/
			KsReal		padding;	/**< パディング		*/
		};

		/**
		 * 
		 */
		struct SCALE
		{
			KsReal		x;			/**< Xスケール値	*/
			KsReal		y;			/**< Yスケール値	*/
		};

		/**
		 * 
		 */
		struct COLOR
		{
			KsByte		r;
			KsByte		g;
			KsByte		b;
			KsByte		a;
			KsReal		padding;
		};

		/**
		 * 
		 */
		struct UV
		{
			KsReal		x;
			KsReal		y;
		};

		/**
		 * 
		 */
		struct PRIORITY
		{
			KsInt32	priority;
			KsInt32	padding;
		};

		/**
		 * 
		 */
		struct USERDATA
		{
			KsInt32	size;
			KsByte*		data;	// 最低4バイト
		};

		/**
		 * 
		 */
		union KEY
		{
			POS			pos;
			ROT			rot;
			SCALE		scale;
			COLOR		color;
			UV			uv;
			PRIORITY	priority;
			USERDATA	userData;
		};

		/**
		 * コンストラクタ
		 */
							KsCellAnimKeyFrame();

		/**
		 * デストラクタ
		 */
		virtual			~KsCellAnimKeyFrame();

	public:
		KsUInt16			m_target;	// 表示、非表示、補完などのフラグ
		KsUInt16			m_flags;
		KsUInt32			m_type;		// キーのタイプ
		KEY*				m_pKey;
		KsByte*				m_pUserData;
};


/************************************************************************************************/
/**
 * @class		KsCellAnimKeyFrame
 * @brief		シンプルなアニメーション
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsCellAnimTrack
{
	public:
		/**
		 * コンストラクタ
		 */
									KsCellAnimTrack();

		/**
		 * デストラクタ
		 */
		virtual					~KsCellAnimTrack();

	public:
		KsInt32					m_frameNo;		/**< フレーム番号	*/
		KsCellAnimKeyFrame*			m_pKeyFrames;	/**< キーフレーム	*/
};

/************************************************************************************************/
/**
 * @class		KsCellAnimPart
 * @brief		シンプルなアニメーション
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsCellAnimPart
{
	public:
		//KsString			m_name;
		KsInt32			m_flags;
		KsInt32			m_priority;
		KsReal				m_px;
		KsReal				m_py;
		KsReal				m_x;
		KsReal				m_y;
		KsReal				m_w;
		KsReal				m_h;
		KsInt32			m_id;
		KsInt32			m_tex;
		KsColor				m_color;
		//KsReal			vertex[ 4 ][ 2 ];
};

/************************************************************************************************/
/**
 * @class		KsCellAnim2D
 * @brief		シンプルなアニメーション
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsCellAnim2D
{
	public:
										KsCellAnim2D();
		virtual						~KsCellAnim2D();
		//KsBool							load( const KsChar* pFileName );
/*
		
		void							setColor( const KsColor& color );
		void							setColor( const KsColorReal& color );
		void							setAlpha( KsReal alpha );
		void							setAlpha( KsInt32 alpha );
		void							setScale( KsReal sx, KsReal sy );
		void							setScale( const KsVector2d& scale );
		void							setPos( KsReal x, KsReal y );
		void							setPos( KsInt32 x, KsInt32 y );
		void							setPos( const KsVector2d& pos );
		void							setAngle( KsReal angle );
		//void							trnslate( );
		//void							rotate();
*/
		//virtual void					update( KsReal time );
		//void							setPos( KsReal x, KsReal y ){ m_pos.x = x; m_pos.y = y; }
		//void							setPos( KsInt32 x, KsInt32 y );
		//void							setTexture( KsTexture* pTexture );
		//virtual void					update( ksFPS30 );
		//virtual void					update( KsReal time );
		//virtual void					update( KsReal time );
		//virtual void					draw( KsRenderSystem* pRS );

	public:
		KsUInt32						m_flags;		/**< フラグ				*/
		KsVector2d						m_pivot;		/**< 基点(回転中心)		*/
		KsVector2d						m_pos;			/**< 位置				*/
		KsVector2d						m_scale;		/**< スケール			*/
		KsReal							m_angle;		/**< 回転				*/
		KsColor							m_color;		/**< カラー				*/
		KsReal							m_fps;			/**< */
		KsInt32						m_startFrame;		/**< */
		KsInt32						m_endFrame;			/**< */
		KsInt32						m_frame;		/**< フレーム			*/
		KsInt32						m_drawFrame;	/**< 描画しているキーフレーム番号		*/
		KsInt32						m_nextFrame;	/**< 次に再セットするキーフレーム番号	*/
		KsBool							m_bLoop;		/**< ループするかどうかのフラグ			*/
		KsUInt16						m_numTexture;
		KsArray<KsCellAnimPart*>		m_pPartList;
		KsArray<KsCellAnimPart*>		m_pDrawList;
		KsArray<KsCellAnimTrack*>		m_vpTracks;		/**< キーフレーム						*/
		KsArray<KsTexture*>				m_vpTextures;	/**< 使用テクスチャ						*/
};


#if 0





/************************************************************************************************/
/**
 * @class		KsAnimKeyFrame
 * @brief		アニメーション
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
KsInt32 KsAnim2DTrack::getKeyFrame( KsReal time, KsReal *pParam, KsAnim2DKeyFrame* pKey1, KsAnim2DKeyFrame* pKey2, KsBool bLoop )
{
	if( time == 0.0f )
	{
		*pKey1  = *m_vKeyFrames[ 0 ];
		*pKey2  = *m_vKeyFrames[ 0 ];
		*pParam = 0.0f;
		return 0;
	}

	KsInt32	num = getNumKeyFrame()-1;

	if( time >= m_maxTime )
	{
		if( !bLoop )
		{
			*pKey1  = *m_vKeyFrames[ num ];
			*pKey2  = *m_vKeyFrames[ num ];
			*pParam = 1.0f;
			return num;
		}

		KsReal		param = KsFloor( time / m_maxTime );

		time = time - param * m_maxTime;
	}


	for( KsInt32 i=0; i<num; i++ )
	{
		if( (m_vKeyFrames[ i ]->m_time <= time) && (time < m_vKeyFrames[ i+1 ]->m_time) )
		{
			*pKey1 = *m_vKeyFrames[ i ];
			*pKey2 = *m_vKeyFrames[ i+1 ];

			KsReal	ft = time - m_vKeyFrames[ i ]->m_time;
			KsReal dt = m_vKeyFrames[ i+1 ]->m_time - m_vKeyFrames[ i ]->m_time;
			KsReal t;
			
			if( dt > 0.00000001f )
			{ 
				t = ft/dt;
			}
			else{
				t = 0.0f;
			}

			*pParam = t;

			return i;
		}
	}

	return -1;
}


void update()
{
	// プライオリティー更新フラグ

	// キーが変更されたとき優先度を変更する

	/* フレーム更新 */
	m_frame += m_frameRate;

	if( m_frame > m_endFrame )
	{
		if( m_bLoop )
		{
			m_frame -= m_endFrame;
		}
		else
		{
			m_frame = m_endFrame;
		}
	}

	/* キーを設定するかどうか？ */
	if( m_oldFrame == m_frame )
	{
		return;
	}

	/* 補完ありのアニメ？ */
	if( interplate )
	{
		/* 補完あり */
		/* 補完キーを取得 */

	}
	else
	{
		/* 補完なし */
		if( m_nextFrame <= m_frame )
		{
			/* 新しいキーをセットする */
			/* 一番近いトラックを取得する */
			m_vpTracks[ ];
		}
	}


	/* 描画登録 */

	m_oldFrame = m_frame;
}

void KsCellAnim2D::draw( KsRenderSystem* pRS )
{
	for( KsUInt32 ii=0; ii<m_pDrawList.size(); ii++ )
	{
		KsCellAnimPart*		pPart = m_pDrawList[ ii ];

		if( pPart->m_flags )
		{
			//KsAssert( pPart->m_tex < m_vpTextures.size() );
			KsTexture*		pTexture = m_vpTextures[ pPart->m_tex ];

			pRS->drawRectEx(pPart->m_x + m_pos.x,
							pPart->m_y + m_pos.y,
							pPart->m_w,
							pPart->m_h,
							pPart->m_u0,
							pPart->m_v0,
							pPart->m_u1,
							pPart->m_v1,
							pPart->m_color,
							pTexture
							);
		}
	}
}



#endif
};




/************************************************************************************************/
/**
 * @class		KsCellAnimKeyFrame
 * @brief		シンプルなアニメーション
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsCellAnimKeyFrame
{
	public:
		KsInt32					m_frame;
		KsArray<KsAnim2DPart*>		m_vpParts;
};

/************************************************************************************************/
/**
 * @class		KsCellAnim2D
 * @brief		シンプルなアニメーション
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsCellAnim2D
{
	public:
										KsCellAnim2D();
		virtual						~KsCellAnim2D();
		KsBool							load( const KsChar* pFileName );
/*
		
		void							setColor( const KsColor& color );
		void							setColor( const KsColorReal& color );
		void							setAlpha( KsReal alpha );
		void							setAlpha( KsInt32 alpha );
		void							setScale( KsReal sx, KsReal sy );
		void							setScale( const KsVector2d& scale );
		void							setPos( KsReal x, KsReal y );
		void							setPos( KsInt32 x, KsInt32 y );
		void							setPos( const KsVector2d& pos );
		void							setAngle( KsReal angle );
		//void							trnslate( );
		//void							rotate();
*/
		//virtual void					update( KsReal time );
		void							setPos( KsReal x, KsReal y ){ m_pos.x = x; m_pos.y = y; }
		//void							setPos( KsInt32 x, KsInt32 y );
		void							setTexture( KsTexture* pTexture );
		virtual void					update();
		virtual void					draw( KsRenderSystem* pRS );

	public:
		KsUInt32						m_flags;		/**< フラグ				*/
		KsVector2d						m_pivot;		/**< 基点(回転中心)		*/
		KsVector2d						m_pos;			/**< 位置				*/
		KsVector2d						m_scale;		/**< スケール			*/
		KsReal							m_angle;		/**< 回転				*/
		KsColor							m_color;		/**< カラー				*/
		KsReal							m_fps;			/**< */
		KsInt32						m_start;		/**< */
		KsInt32						m_end;			/**< */
		KsInt32						m_frame;		/**< フレーム			*/
		KsInt32						m_drawFrame;	/**< 描画しているキーフレーム番号		*/
		KsInt32						m_nextFrame;	/**< 次に再セットするキーフレーム番号	*/
		KsBool							m_bLoop;		/**< ループするかどうかのフラグ			*/
		KsArray<KsCellAnimKeyFrame*>	m_vpKeyFrames;	/**< キーフレーム						*/
		KsArray<KsTexture*>				m_vpTextures;	/**< 使用テクスチャ						*/
};



#endif /* __KsCellAnim2D_H__ */


