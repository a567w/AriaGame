/************************************************************************************************/
/** 
 * @file		KsModelNode.h
 * @brief		�J���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSMODELNODE_H__
#define __KSMODELNODE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsGeometry.h"
#include "KsFrame.h"
#include "KsBone.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
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
		KsUInt16						m_flags;				/**< �t���O					*/
		KsUInt16						m_type;					/**< �^�C�v					*/
		KsChar							m_name[ 32 ];			/**< �m�[�h��				*/
		KsGeometry*						m_pGeometry;			/**< �W�I���g���f�[�^			*/
		KsFrame							m_joint;				/**< �W���C���g				*/
		KsModelNode*					m_pParent;				/**< �e�̃I�u�W�F�N�g			*/
		KsModelNodeList					m_pChildren;			/**< �q���̃I�u�W�F�N�g		*/

		/* �����X�L���f�[�^�̂Ƃ�����(�J�E���g��0���ƃ{�[���͂Ȃ�) */
		KsBone*							m_pBoneRoot;			/**< ���[�g�̃{�[��			*/
		KsBoneList						m_bones;				/**< �{�[�����X�g			*/
};

#if 0

class KsSubMesh : public KsFrame
{
	public:
										KsSubMesh();

		virtual						~KsSubMesh();

		KsUInt16						m_flags;				/**< �t���O					*/
		KsUInt16						m_type;					/**< �^�C�v					*/
		KsChar							m_name[ 32 ];			/**< �m�[�h��				*/
		KsGeometry*						m_pGeometry;			/**< �W�I���g���f�[�^			*/
		KsBone*							m_pBoneRoot;			/**< ���[�g�̃{�[��			*/
		KsBoneList						m_bones;				/**< �{�[�����X�g			*/
};
#endif


#endif		/* __KSMODELNODE_H__ */
