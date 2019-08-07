/************************************************************************************************/
/** 
 * @file		KsSubMesh.h
 * @brief		�W�I���g������
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSUBMESH_H__
#define __KSSUBMESH_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsVertexData.h"
#include "KsIndexData.h"
#include "KsMaterial.h"
#include "KsTexture.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

class KsFaceList
{
public:
	KsUInt16		m_start;
	KsUInt16		m_end;
	KsUInt16		m_materialID;
};


/************************************************************************************************/
/**
 * �T�u���b�V��
 * @class		KsSubMesh
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsSubMesh
{
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsSubMesh();
		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsSubMesh();

		/**
		 * �W�I���g������
		 * @param		pData			�f�[�^�̐擪�|�C���^
		 * @retval		ksTRUE			����
		 * @retval		ksFALSE			���s
		 */
		//KsBool							create( KsByte* pData );

		/**
		 * �W�I���g������
		 * @param		numVertices		���_��
		 * @param		numFaces		�ʂ̐�
		 * @param		numMaterials	�}�e���A����
		 * @param		numTextures		�e�N�X�`����
		 * @retval		ksTRUE			����
		 * @retval		ksFALSE			���s
		 */
		//KsBool							create( KsUInt16 numVertices, KsUInt16 numFaces, KsUInt16 numMaterials, KsUInt16 numTextures );

		/**
		 * �W�I���g���̃t���O���擾����
		 * @return		�W�I���g���̊e��t���O
		 */
		KsUInt32						getFlags()	const { return m_flags; }

		/**
		 * ���_�����擾����
		 * @return		���_��
		 */
		KsUInt16						getNumVertex() const { return m_numVertex; }

		/**
		 * �ʂ̐����擾����
		 * @return		�ʂ̐�
		 */
		KsUInt16						getNumIndex() const { return m_numIndex; }

		/**
		 * �}�e���A�������擾����
		 * @return		�}�e���A����
		 */
		const std::string&				getName() { return m_name; }

		/**
		 * �}�e���A�������擾����
		 * @return		�}�e���A����
		 */
		const std::string&				getMaterialName() { return m_materialName; }

		/**
		 * �e�N�X�`�������擾����
		 * @return		�e�N�X�`����
		 */
		const std::string&				getTextureName() { return m_textureName; }

		/**
		 * �w��C���f�b�N�X�̒��_���擾����
		 * @param		index			�C���f�b�N�X
		 * @return						���_�̃|�C���^
		 */
		//const KsVertexData*				getVertexData() const { return &m_pVertices[ index ]; }

		/**
		 * �w��C���f�b�N�X�̖ʂ��擾����
		 * @param		index			�C���f�b�N�X
		 * @return						�ʂ̃|�C���^
		 */
		//const KsIndexData*				getIndexData( KsUInt16 index ) { return &m_pFaces[ index ]; }

		/**
		 * �w��C���f�b�N�X�̃}�e���A�����擾����
		 * @param		index			�C���f�b�N�X
		 * @return						�}�e���A���̃|�C���^
		 */
		//const KsMaterial*				getMaterial() { return &m_pMaterials[ index ]; }

		/**
		 * �w��C���f�b�N�X�̃e�N�X�`�����擾����
		 * @param		index			�C���f�b�N�X
		 * @return						�e�N�X�`���̃|�C���^
		 */
		//const KsTexture*				getTexture() { return &m_pTextures[ index ]; }

	public:
		KsUInt32						m_flags;				/**< �t���O				*/
		KsUInt16						m_numVertex;			/**< ���_��				*/
		KsUInt16						m_numIndex;				/**< �ʂ̐�				*/
		KsUInt16						m_numFaceList;			/**< �ʍ\��				*/
		KsVertexData*					m_pVertices;			/**< ���_�f�[�^			*/
		KsIndexData*					m_pIndices;				/**< �ʃf�[�^			*/
		KsFaceList*						m_pFaceList;			/**< �ʍ\�����X�g		*/
		std::string						m_name;					/**< �T�u���b�V�����O		*/
		std::string						m_textureName;			/**< �g�p�e�N�X�`����		*/
		std::string						m_materialName;			/**< �g�p�}�e���A����		*/
};

#endif		/* __KSSUBMESH_H__ */


