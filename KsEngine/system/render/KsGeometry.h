/************************************************************************************************/
/** 
 * @file		KsGeometry.h
 * @brief		�W�I���g������
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSGEOMETRY_H__
#define __KSGEOMETRY_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsVertex.h"
#include "KsFace.h"
#include "KsMaterial.h"
#include "KsTexture.h"
#include "KsFileObject.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * �W�I���g���N���X
 * @class		KsGeometry
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsGeometry : public KsRefCounter
{
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsGeometry();

		/**
		 * �R���X�g���N�^
		 * @param		numVertices		���_��
		 * @param		numFaces		�ʂ̐�
		 * @param		numMaterials	�}�e���A����
		 * @param		numTextures		�e�N�X�`����
		 */
										KsGeometry( KsUInt16 numVertices, KsUInt16 numFaces, KsUInt16 numMaterials, KsUInt16 numTextures );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsGeometry();

		/**
		 * �W�I���g������
		 * @param		pData			�f�[�^�̐擪�|�C���^
		 * @retval		ksTRUE			����
		 * @retval		ksFALSE			���s
		 */
		KsBool							create( KsByte* pData );

		/**
		 * �t�@�C������W�I���g���𐶐�����
		 * @param		pFile			�t�@�C���f�[�^
		 * @retval		ksTRUE			����
		 * @retval		ksFALSE			���s
		 */
		KsBool							create( KsFileObject* pFile );

		/**
		 * �W�I���g������
		 * @param		numVertices		���_��
		 * @param		numFaces		�ʂ̐�
		 * @param		numMaterials	�}�e���A����
		 * @param		numTextures		�e�N�X�`����
		 * @retval		ksTRUE			����
		 * @retval		ksFALSE			���s
		 */
		KsBool							create( KsUInt16 numVertices, KsUInt16 numFaces, KsUInt16 numMaterials, KsUInt16 numTextures );

		/**
		 * �W�I���g���̔j��
		 */
		void							destory();

		/**
		 *
		 */
		void							lock();

		/**
		 *
		 */
		void							unlock();

		/**
		 * �W�I���g���̃t���O���擾����
		 * @return		�W�I���g���̊e��t���O
		 */
		KsUInt32						getFlags()	const { return m_flags; }

		/**
		 * ���_�����擾����
		 * @return		���_��
		 */
		KsUInt16						getNumVertices() const { return m_numVertices; }

		/**
		 * �ʂ̐����擾����
		 * @return		�ʂ̐�
		 */
		KsUInt16						getNumFaces() const { return m_numFaces; }

		/**
		 * �}�e���A�������擾����
		 * @return		�}�e���A����
		 */
		KsUInt16						getNumMaterials() const { return m_numMaterials; }

		/**
		 * �e�N�X�`�������擾����
		 * @return		�e�N�X�`����
		 */
		KsUInt16						getNumTexture()	const { return m_numTextures; }

		/**
		 * �w��C���f�b�N�X�̒��_���擾����
		 * @param		index			�C���f�b�N�X
		 * @return						���_�̃|�C���^
		 */
		const KsVertex*					getVertex( KsUInt16 index ) const { return &m_pVertices[ index ]; }

		/**
		 * �w��C���f�b�N�X�̖ʂ��擾����
		 * @param		index			�C���f�b�N�X
		 * @return						�ʂ̃|�C���^
		 */
		const KsFace*					getFace( KsUInt16 index ) { return &m_pFaces[ index ]; }

		/**
		 * �w��C���f�b�N�X�̃}�e���A�����擾����
		 * @param		index			�C���f�b�N�X
		 * @return						�}�e���A���̃|�C���^
		 */
		const KsMaterial*				getMaterial( KsUInt16 index ) { return &m_pMaterials[ index ]; }

		/**
		 * �w��C���f�b�N�X�̃e�N�X�`�����擾����
		 * @param		index			�C���f�b�N�X
		 * @return						�e�N�X�`���̃|�C���^
		 */
		const KsTexture*				getTexture( KsUInt16 index ) { return &m_pTextures[ index ]; }

	public:
		KsUInt32						m_id;					/**< ID					*/
		KsUInt32						m_flags;				/**< �t���O				*/
		KsUInt16						m_numVertices;			/**< ���_��				*/
		KsUInt16						m_numFaces;				/**< �ʂ̐�				*/
		KsUInt16						m_numMaterials;			/**< �}�e���A����		*/
		KsUInt16						m_numTextures;			/**< �e�N�X�`����		*/
		KsVertex*						m_pVertices;			/**< ���_�f�[�^			*/
		KsFace*							m_pFaces;				/**< �ʃf�[�^			*/
		KsMaterial*						m_pMaterials;			/**< �}�e���A���f�[�^		*/
		KsTexture*						m_pTextures;			/**< �Q�Ƃ���e�N�X�`��	*/
};


#endif		/* __KSGEOMETRY_H__ */
