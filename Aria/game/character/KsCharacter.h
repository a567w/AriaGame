/************************************************************************************************/
/** 
 * @file		KsCharacter.h
 * @brief		KsCharacterファイル
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSCHARACTER_H__
#define __KSCHARACTER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsCharacterPad;

/************************************************************************************************/
/**
 * @class		KsCharacter
 * @brief		キャラクタークラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsCharacter : public KsActor, public KsTask
{
	public:
		/**
		 * コンストラクタ
		 * @param	pModel			モデルデータ
		 * @param	updateOrder		更新オーダー
		 * @param	drawOrder		描画オーダー
		 */
									KsCharacter( KsModel* pModel, KsUInt32 updateOrder, KsUInt32 drawOrder );

		/**
		 * デストラクタ
		 */
		virtual						~KsCharacter();

		/**
		 * 更新処理
		 * @param		pParam		パラメータ
		 */
		virtual void*				update( void* pParam );

		/**
		 * 描画処理
		 * @param		pParam		パラメータ
		 */
		virtual void*				draw( void* pParam );

	protected:
		KsCharacterPad*				m_pPad;		/**< キャラ操作パッド		*/
		//KsCharacterJob*				m_pJob;
};

#if 0
class KsCharacterDebug
{
	public:
		/**
		 * コンストラクタ
		 * @param	pCharacter		キャラクター
		 */
		KsCharacterDebug( KsCharacter* pCharacter );

		/**
		 * デストラクタ
		 */
		virtual						~KsCharacterDebug();

		/**
		 * 更新処理
		 * @param		pParam		パラメータ
		 */
		virtual void*				update( void* pParam );

		/**
		 * 描画処理
		 * @param		pParam		パラメータ
		 */
		virtual void*				draw( void* pParam );

		void						drawBone();
		void						drawPhysics();
};

void KsCharacterDebug::drawBone()
{
	// ボーンモデルを作ってあとは
	const KsUInt32 boneCount = m_pModel->getBoneCount();

	for( KsUInt32 i=0; i<boneCount; i++ )
	{
		m_pModel->getBone();
	}
}


void KsCharacterDebug::drawRigidBody()
{
	// ボーンモデルを作ってあとは
	const KsUInt32 boneCount = m_pModel->getRigidBody();

	for( KsUInt32 i=0; i<boneCount; i++ )
	{
		m_pModel->getRigidBody( i );
	}
}
#endif

#endif /* __KSCHARACTER_H__ */
