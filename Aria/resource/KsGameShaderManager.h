/************************************************************************************************/
/** 
 * @file		KsGameShaderManager.h
 * @brief		�Q�[�����\�[�X
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSGAMESHADEREMANAGER_H__
#define __KSGAMESHADEREMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsGameShaderManager
 * @brief		�Q�[�����\�[�X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsGameShaderManager : public KsSingleton< KsGameShaderManager >
{
	public:
		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return							�V���O���g���̎Q��
		 */
		static KsGameShaderManager&			getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return							�V���O���g���̃|�C���^
		 */
		static KsGameShaderManager*			getInstancePtr();

	public:
		/**
		 * �R���X�g���N�^
		 */
											KsGameShaderManager();

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsGameShaderManager();

		/** 
		 * �t�@�C���p�b�N����V�F�_�[�𐶐�����
		 * @param	rFileName		�t�@�C���p�b�N
		 * @retval	ksTRUE			����
		 * @retval	ksFALSE			���s
		 */
		KsBool								create( const KsString& rFileName );

		/**
		 * ���ׂẴ��\�[�X���������
		 */
		void								destroy();

		/** 
		 * �V�F�_�[�v���O��������������
		 * @param	rShaderName		�V�F�_�[�v���O������
		 * @return					�V�F�_�[�v���O����������Ȃ�����NULL��Ԃ�
		 */
		KsShaderProgram*					find( const KsString& rShaderName );
		

	protected:
		KsFilePack*							m_pFilePack;	/**< �t�@�C���p�b�N		*/
		KsHashTable<KsShaderProgram*>		m_vpShaderTbl;	/**< �V�F�[�_�[�e�[�u��	*/
};

#endif /* __KSGAMESHADEREMANAGER_H__ */

