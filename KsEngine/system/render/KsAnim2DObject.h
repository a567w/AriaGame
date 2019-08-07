/************************************************************************************************/
/** 
 * @file		KsAnim2DObject.h
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSANIM2DOBJECT_H__
#define __KSANIM2DOBJECT_H__

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


/************************************************************************************************/
/**
 * @class		KsAnim2DObject
 * @brief		アニメーションオブジェクト
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsAnim2DObject
{
	public:
		KsAnim2DObject(){}
		virtual				~KsAnim2DObject(){}

		/**
		 * ルートジョイント数を取得する
		 * @return				ルートジョイント数
		 */
		//KsUInt32				getNumRootObject() { return m_pRootJointList.size(); }

		/**
		 * ルートジョイントを取得する
		 * @param	index		ルートジョイントインデックス
		 * @return				指定のルートジョイントのポインタ
		 */
		//KsAnim2DObject*				getRootObject( KsUInt32 index=0 ) { return m_pRootJointList[ index ]; }

		//void			update();
		//void			draw();
	//protected:
		//KsAnim2DObject* pRoot=NULL 
		//KsArray<KsAnim2DObject*>		m_vpObjects;
		//KsArray<KsAnim2DPart*>			m_vpParts;
};

/************************************************************************************************/
/**
 * @class		KsAnim2DObject
 * @brief		アニメーションオブジェクト
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
#if 0
class ksENGINE_API KsNormalAnim2D : public KsAnim2DObject
{
	public:
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

		//void							setAnime( KsInt32 index );
		virtual void					update();
		//virtual void					update( KsReal time );
		virtual void					draw();

	private:
		//KsArray<KsAnimation2D*>			m_pAnimations;
		//KsJoint*						m_pRoot;
		//KsArray<KsAnim2DPart*>			m_vpParts;
};
#endif
#if 0
KEYFRAME
targetPartID

/************************************************************************************************/
/**
 * @class		KsAnim2DObject
 * @brief		アニメーションオブジェクト
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsAnim2DObject
{
	public:
								KsAnim2DObject();
		virtual				~KsAnim2DObject();

		/**
		 * ルートジョイント数を取得する
		 * @return				ルートジョイント数
		 */
		//KsUInt32				getNumRootObject() { return m_pRootJointList.size(); }

		/**
		 * ルートジョイントを取得する
		 * @param	index		ルートジョイントインデックス
		 * @return				指定のルートジョイントのポインタ
		 */
		//KsAnim2DObject*				getRootObject( KsUInt32 index=0 ) { return m_pRootJointList[ index ]; }

		//void			update();
		//void			draw();
	protected:
		//KsAnim2DObject* pRoot=NULL 
		KsArray<KsAnim2DObject*>		m_vpObjects;
		KsArray<KsAnim2DPart*>			m_vpParts;
};

#if 0
animMesh

parts
hierarchy


animdata

#endif

#endif

#endif /* __KSANIM2DOBJECT_H__ */


