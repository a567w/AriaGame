/************************************************************************************************/
/** 
 * @file		KsGameResourceManager.h
 * @brief		�Q�[�����\�[�X
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSGAMERESOURCEMANAGER_H__
#define __KSGAMERESOURCEMANAGER_H__

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
 * @enum		ksTEXTURE_RESOURCE_TYPE
 * @brief		�e�N�X�`�����\�[�X�^�C�v
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
enum ksTEXTURE_RESOURCE_TYPE
{
	ksTEXTURE_RESOURCE_COMMON,					/**< ���ʃe�N�X�`��					*/
	ksTEXTURE_RESOURCE_MENUM,					/**< ���j���[�p�e�N�X�`��			*/
	ksTEXTURE_RESOURCE_STAGE,					/**< �X�e�[�W�p�e�N�X�`��			*/
	ksTEXTURE_RESOURCE_MAX,						/**< �e�N�X�`�����\�[�X�^�C�v�ő吔	*/
	ksTEXTURE_RESOURCE_FORCE32 = 0x7fffffff,	/**< ����32bit						*/
};

/************************************************************************************************/
/**
 * @class		KsGameResourceManager
 * @brief		�Q�[�����\�[�X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsGameResourceManager : public KsSingleton< KsGameResourceManager >
{
		typedef KsArray<KsTexture*>		KsTextureArray;

	public:
		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return							�V���O���g���̎Q��
		 */
		static KsGameResourceManager&		getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return							�V���O���g���̃|�C���^
		 */
		static KsGameResourceManager*		getInstancePtr();

	public:
		/**
		 * �R���X�g���N�^
		 */
											KsGameResourceManager();

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsGameResourceManager();

		/**
		 * �����󋵃R�[���o�b�N
		 */
		//KsBool							setup( callback=NULL );

		/** 
		 * ��������
		 */
		void								create();

		/**
		 * ���ׂẴe�N�X�`�����\�[�X���������
		 */
		void								destroy();

		/**
		 * �w��^�C�v�̃e�N�X�`�����\�[�X���������
		 * @param	type					�e�N�X�`���^�C�v
		 */
		void								destroyTextures( ksTEXTURE_RESOURCE_TYPE type );

	protected:
		KsTextureArray						m_vpTextures[ ksTEXTURE_RESOURCE_MAX ];	/**< �e�N�X�`��	*/
};

#endif /* __KSGAMERESOURCEMANAGER_H__ */

