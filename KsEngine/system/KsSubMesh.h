/************************************************************************************************/
/** 
 * @file		KsSubMesh.h
 * @brief		�T�u���b�V��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSUBMESH_H__
#define __KSSUBMESH_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsType.h"
#include "KsArray.h"
#include "KsString.h"
#include "KsVector.h"
#include "KsMatrix.h"
#include "KsQuaternion.h"
#include "KsVertexBuffer.h"
#include "KsIndexBuffer.h"
#include "KsMaterial.h"
#include "KsTexture.h"
#include "KsFace.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSubMesh
 * @brief		�T�u���b�V��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsSubMesh
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
		 * �`�揈��
		 */
		virtual void					draw();

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
#if 0
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
		 * �C���f�b�N�X�����擾����
		 * @return		�C���f�b�N�X��
		 */
		KsUInt16						getNumIndex() const { return m_numIndex; }

		/**
		 * �T�u���b�V�������擾����
		 * @return		�T�u���b�V����
		 */
		const KsString&				getName() { return m_name; }

		/**
		 * �}�e���A�������擾����
		 * @return		�}�e���A����
		 */
		const KsString&				getMaterialName() { return m_materialName; }

		/**
		 * �e�N�X�`�������擾����
		 * @return		�e�N�X�`����
		 */
		const KsString&				getTextureName() { return m_textureName; }
#endif

		/**
		 * �w��C���f�b�N�X�̒��_���擾����
		 * @param		index			�C���f�b�N�X
		 * @return						���_�̃|�C���^
		 */
		//const KsVertexBuffer*			getVertexBuffer() const { return m_pVertices[ index ]; }

		/**
		 * �w��C���f�b�N�X�̖ʂ��擾����
		 * @param		index			�C���f�b�N�X
		 * @return						�ʂ̃|�C���^
		 */
		//const KsIndexBuffer*				getIndexData( KsUInt16 index ) { return &m_pFaces[ index ]; }

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
		KsString						m_name;					/**< �T�u���b�V�����O		*/
		KsString						m_textureName;			/**< �g�p�e�N�X�`����		*/
		KsString						m_materialName;			/**< �g�p�}�e���A����		*/
		KsUInt32						m_flags;				/**< �t���O					*/
		KsUInt16						m_numVertex;			/**< ���_��					*/
		KsUInt16						m_numIndex;				/**< �ʂ̐�					*/
		KsUInt16						m_numFace;				/**< �ʍ\��					*/
		KsVertexBuffer*					m_pVertices;			/**< ���_�f�[�^				*/
		KsIndexBuffer*					m_pIndices;				/**< �ʃf�[�^				*/
		KsFace*							m_pFaces;				/**< �ʍ\���f�[�^			*/
		KsMaterial*						m_pMaterials;			/**< �}�e���A���f�[�^		*/
		
};

#endif		/* __KSSUBMESH_H__ */


