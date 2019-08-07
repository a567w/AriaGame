/************************************************************************************************/
/** 
 * @file		KsHumanIK.h
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
#ifndef __KSHUMANIK_H__
#define __KSHUMANIK_H__

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsIKPoint
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsIKPoint
{
	public:
								KsIKPoint( KsBone* pBone );

		KsBone*					getBone() { return m_pBone; }
		KsBool					IsIKLimitAngle() const { return m_bIKLimitAngle; }
		KsInt32					getIKLimitAngleType() const { return m_IKLimitAngleType; };

	public:
		KsBone*					m_pBone;
		KsBool					m_bIKLimitAngle;
		KsInt32					m_IKLimitAngleType;
};

/************************************************************************************************/
/**
 * @class		KsIKEffector
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsIKEffector
{
	public:
		KsInt32					m_iterations;		// 再帰演算回数( IK値1 )
		KsReal					m_controlWeight;	// IKの影響度( IK値2 )
		KsIKPoint*				m_pTarget;
		KsIKPoint*				m_pEffector;
		KsArray<KsIKPoint*>		m_vpChain;	

	public:
		KsIKPoint*				getTargetPoint() { return m_pTarget; }
		KsIKPoint*				getEffectorPoint() { return m_pEffector; }
		KsIKPoint*				getChainPoint( KsUInt32 index ) { return m_vpChain[ index ]; }
		KsUInt32				getChainPointCount() const { return m_vpChain.size(); }
		KsInt32					getIterations() const { return m_iterations; }
		KsReal					getControlWeight() const { return m_controlWeight; }
};

/************************************************************************************************/
/**
 * @class		KsIKEffector
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsIKParameter
{
	public:
		KsString				BoneName;			// IKボーン番号
		KsString				TargetBoneName;		// IKターゲットボーン番号( IKボーンが最初に接続するボーン )
		KsInt32					BoneIndex;			// IKボーン番号
		KsInt32					TargetBoneIndex;	// IKターゲットボーン番号( IKボーンが最初に接続するボーン )
		KsInt32					ChainLength;		// IKチェーンの長さ(子の数)
		KsInt32					Iterations;			// 再帰演算回数( IK値1 )
		KsReal					ControlWeight;		// IKの影響度( IK値2 )
		KsArray<KsInt32>		ChildBoneIndices;	// IK影響下のボーン番号(ChainLength)
		KsArray<KsString>		ChildBoneNames;		// IK影響下のボーン番号(ChainLength)
};

/************************************************************************************************/
/**
 * @class		KsHumanIK
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsHumanIK
{
	public:
						KsHumanIK( KsModel* pModel );
		virtual			~KsHumanIK();
		virtual void	update();
		
		void	updateIK();
		void	limitAngle( KsQuaternion& quat, KsIKPoint* pIKPoint );
	public:
		KsModel*					m_pModel;
		KsArray<KsIKParameter*>		m_vpParameters;
		KsArray<KsIKEffector*>		m_vpEffectors;
};

#if 0
/************************************************************************************************/
/**
 * @class		KsHumanIK
 * @brief		人間用IKシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsHumanIK2
{
	public:
		/**
		 * コンストラクタ
		 */
									KsHumanIK2();

		/**
		 * コンストラクタ
		 */
									KsHumanIK2( KsModel* pModel );

		/**
		 * デストラクタ
		 */
		virtual						~KsHumanIK2();

		/**
		 * 更新処理
		 * @param	gameTime		ゲーム更新時間
		 */
		virtual void				update( KsReal gameTime );

		/**
		 * IKの解析する解法
		 */
		void						solver();
		
	public:
		KsModel*					m_pModel;			/**< ターゲットモデル		*/
		KsArray<KsIKJoint*>			m_vpParameters;		/**< IK*/
		KsArray<KsIKEffector*>		m_vpEffectors;
		KsArray<KsIKPositionConstraint*>		m_vpPositionConstraints;
		KsArray<KsIKDirectionConstraint*>		m_vpKsIKDirectionConstraint;
};
#endif

#endif		/* __KSHUMANIK_H__ */

