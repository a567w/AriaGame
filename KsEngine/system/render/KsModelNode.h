/************************************************************************************************/
/** 
 * @file		KsModelNode.h
 * @brief		カラー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSMODELNODE_H__
#define __KSMODELNODE_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsGeometry.h"
#include "KsFrame.h"
#include "KsBone.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsModel;
class KsModelNode;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef std::vector< KsModelNode* >				KsModelNodeList;
typedef std::vector< KsModelNode* >::iterator		KsModelNodeListPtr;
typedef std::vector< KsBone* >						KsBoneList;
typedef std::vector< KsBone* >::iterator			KsBoneListPtr;

/************************************************************************************************/
/**
 * 
 * @class	
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsModelNode
{
	public:
		friend	class KsModel;
	public:
										KsModelNode();
		virtual						~KsModelNode();

	public:
		KsUInt16						m_flags;				/**< フラグ					*/
		KsUInt16						m_type;					/**< タイプ					*/
		KsChar							m_name[ 32 ];			/**< ノード名				*/
		KsGeometry*						m_pGeometry;			/**< ジオメトリデータ			*/
		KsFrame							m_joint;				/**< ジョイント				*/
		KsModelNode*					m_pParent;				/**< 親のオブジェクト			*/
		KsModelNodeList					m_pChildren;			/**< 子供のオブジェクト		*/

		/* ワンスキンデータのときだけ(カウントが0だとボーンはない) */
		KsBone*							m_pBoneRoot;			/**< ルートのボーン			*/
		KsBoneList						m_bones;				/**< ボーンリスト			*/
};

#if 0

class KsSubMesh : public KsFrame
{
	public:
										KsSubMesh();

		virtual						~KsSubMesh();

		KsUInt16						m_flags;				/**< フラグ					*/
		KsUInt16						m_type;					/**< タイプ					*/
		KsChar							m_name[ 32 ];			/**< ノード名				*/
		KsGeometry*						m_pGeometry;			/**< ジオメトリデータ			*/
		KsBone*							m_pBoneRoot;			/**< ルートのボーン			*/
		KsBoneList						m_bones;				/**< ボーンリスト			*/
};
#endif


#endif		/* __KSMODELNODE_H__ */
