/************************************************************************************************/
/** 
 * @file		KsHardwareBufferManager.h
 * @brief		�o�b�t�@�}�l�[�W��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSHARDWAREBUFFERMANAGER_H__
#define __KSHARDWAREBUFFERMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsHardwareBufferManager
 * @brief		�o�b�t�@�}�l�[�W��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsHardwareBufferManager : public KsSingleton< KsHardwareBufferManager >
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsHardwareBufferManager(){}

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsHardwareBufferManager(){}

		/**
		 * ���_�o�b�t�@�𐶐�����
		 * @param		vertexSize			���_�T�C�Y
		 * @param		numVertex			���_��
		 * @param		vertexFormat		���_�t�H�[�}�b�g
		 * @param		flags				�t���O
		 * @return							���_�o�b�t�@�̃|�C���^
		 */
		virtual KsVertexBuffer*				createVertexBuffer( KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags ) = 0;

		/**
		 * ���_�o�b�t�@�𐶐�����
		 * @param		vertexSize			[in] ���_�T�C�Y
		 * @param		numVertex			[in] ���_��
		 * @param		vertexFormat		[in] ���_�t�H�[�}�b�g
		 * @param		flags				[in] �t���O
		 * @return							���_�o�b�t�@�̃|�C���^
		 */
		virtual KsVertexBuffer*				createVertexBuffer( void* pData, KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags ) = 0;

		/**
		 * �C���f�b�N�X�o�b�t�@�𐶐�����
		 * @param		numIndex			�C���f�b�N�X��
		 * @param		flags				�t���O
		 * @return							�C���f�b�N�X�o�b�t�@�̃|�C���^
		 */
		virtual KsIndexBuffer*				createIndexBuffer( KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags ) = 0;

		/**
		 * �C���f�b�N�X�o�b�t�@�𐶐�����
		 * @param	pData					[in] �f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	size					[in] �f�[�^�T�C�Y
		 * @param	numIndex				[in] �C���f�b�N�X�̐�
		 * @param	indexFormat				[in] �C���f�b�N�X�t�H�[�}�b�g
		 * @param	flags					[in] �t���O
		 * @return							�C���f�b�N�X�o�b�t�@�̃|�C���^
		 */
		virtual KsIndexBuffer*				createIndexBuffer( void* pData, KsUInt32 size, KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags ) = 0;

		/**
		 * �萔�o�b�t�@�𐶐�����
		 * @param	pData				[in] �f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	size				[in] �f�[�^�T�C�Y
		 * @param	flags				[in] �t���O
		 * @return						�萔�o�b�t�@�̃|�C���^
		 */
		virtual KsConstantBuffer*		createConstantBuffer( KsUInt32 size, KsUInt32 flags ) = 0;

		/**
		 * �萔�o�b�t�@�𐶐�����
		 * @param	size				[in] �o�b�t�@�T�C�Y
		 * @param	flags				[in] �t���O
		 * @return						�萔�o�b�t�@�̃|�C���^
		 */
		virtual KsConstantBuffer*		createConstantBuffer( void* pData, KsUInt32 size, KsUInt32 flags ) = 0;

		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return							�V���O���g���̎Q��
		 */
		static KsHardwareBufferManager&		getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return							�V���O���g���̃|�C���^
		 */
		static KsHardwareBufferManager*		getInstancePtr();
};

#endif		/* __KSHARDWAREBUFFERMANAGER_H__ */



