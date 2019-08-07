/************************************************************************************************/
/** 
 * @file		KsMesh.h
 * @brief		���b�V��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMESH_H__
#define __KSMESH_H__


/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsType.h"
#include "KsSubMesh.h"
#include "KsMaterial.h"
#include "KsTexture.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsMesh
 * @brief		���b�V���N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsMesh
{
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsMesh();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsMesh();

		/**
		 * �`�揈��
		 */
		virtual void					draw();
	
	protected:

};

#if 0

/************************************************************************************************/
/**
 * @class		KsMesh
 * @brief		���b�V���N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsMesh// : public KsRefCounter
{
		typedef std::vector< KsSubMesh* >					KsSubMeshList;
		typedef std::vector< KsMaterial* >					KsMaterialList;
		typedef std::map< std::string, KsTexture* >		KsTextureList;
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsMesh();

		/**
		 * �R���X�g���N�^
		 * @param		numVertices		���_��
		 * @param		numFaces		�ʂ̐�
		 * @param		numMaterials	�}�e���A����
		 * @param		numTextures		�e�N�X�`����
		 */
		//								KsMesh( KsUInt16 numVertices, KsUInt16 numFaces, KsUInt16 numMaterials, KsUInt16 numTextures );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsMesh();

		/**
		 * �W�I���g������
		 * @param		pData			�f�[�^�̐擪�|�C���^
		 * @retval		ksTRUE			����
		 * @retval		ksFALSE			���s
		 */
		//KsBool							create( KsByte* pData );

		/**
		 * �t�@�C������W�I���g���𐶐�����
		 * @param		pFile			�t�@�C���f�[�^
		 * @retval		ksTRUE			����
		 * @retval		ksFALSE			���s
		 */
		//KsBool							create( KsFileObject* pFile );

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

		const std::string&				getName() { return m_name; }

		KsSubMesh*						getSubMesh( KsInt32 index )	{ return m_pSubMeshList[ index ]; }
		KsMaterial*						getMaterial( KsInt32 index )	{ return m_pMaterialList[ index ]; }
		KsTexture*						getTexture( const std::string& name )	{ return m_pTextureList[ name ]; }

	public:
		std::string						m_name;					/**< ���O(�t�@�C����)	*/
		KsUInt32						m_flags;				/**< �t���O				*/
		KsHierarchy*					m_pHierarchy;			/**< ���g��(�K�w�\��)	*/
		KsSubMeshList					m_pSubMeshList;			/**< �T�u���b�V�����X�g	*/
		KsMaterialList					m_pMaterialList;		/**< �}�e���A�����X�g		*/
		KsTextureList					m_pTextureList;			/**< �e�N�X�`�����X�g		*/
		//BoneList
};
#endif

#endif		/* __KSMESH_H__ */



