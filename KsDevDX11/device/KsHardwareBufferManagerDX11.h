/************************************************************************************************/
/** 
 * @file		KsHardwareBufferManagerDX11.h
 * @brief		�o�b�t�@�}�l�[�W��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBUFFERMANAGERDX11_H__
#define __KSBUFFERMANAGERDX11_H__

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
 * @class		KsBufferManager
 * @brief		�o�b�t�@�}�l�[�W��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsHardwareBufferManagerDX11 : public KsHardwareBufferManager
{
	public:
		/**
		 * �R���X�g���N�^
		 * @param	pRenderSystem		�`��V�X�e��
		 */
										KsHardwareBufferManagerDX11( KsRenderSystemDX11* pRenderSystem );

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsHardwareBufferManagerDX11();

		/**
		 * ���_�o�b�t�@�𐶐�����
		 * @param		vertexSize		[in] ���_�T�C�Y
		 * @param		numVertex		[in] ���_��
		 * @param		vertexFormat	[in] ���_�t�H�[�}�b�g
		 * @param		flags			[in] �t���O
		 * @return						���_�o�b�t�@�̃|�C���^
		 */
		virtual KsVertexBuffer*			createVertexBuffer( KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags );

		/**
		 * ���_�o�b�t�@�𐶐�����
		 * @param		vertexSize		[in] ���_�T�C�Y
		 * @param		numVertex		[in] ���_��
		 * @param		vertexFormat	[in] ���_�t�H�[�}�b�g
		 * @param		flags			[in] �t���O
		 * @return						���_�o�b�t�@�̃|�C���^
		 */
		virtual KsVertexBuffer*			createVertexBuffer( void* pData, KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags );

		/**
		 * �C���f�b�N�X�o�b�t�@�𐶐�����
		 * @param	numIndex			[in] �C���f�b�N�X�̐�
		 * @param	indexFormat			[in] �C���f�b�N�X�t�H�[�}�b�g
		 * @param	flags				[in] �t���O
		 * @return						�C���f�b�N�X�o�b�t�@�̃|�C���^
		 */
		virtual KsIndexBuffer*			createIndexBuffer( KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags );

		/**
		 * �C���f�b�N�X�o�b�t�@�𐶐�����
		 * @param	pData				[in] �f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	size				[in] �f�[�^�T�C�Y
		 * @param	numIndex			[in] �C���f�b�N�X�̐�
		 * @param	indexFormat			[in] �C���f�b�N�X�t�H�[�}�b�g
		 * @param	flags				[in] �t���O
		 * @return						�C���f�b�N�X�o�b�t�@�̃|�C���^
		 */
		virtual KsIndexBuffer*			createIndexBuffer( void* pData, KsUInt32 size, KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags );

		/**
		 * �萔�o�b�t�@�𐶐�����
		 * @param	pData				[in] �f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	size				[in] �f�[�^�T�C�Y
		 * @param	flags				[in] �t���O
		 * @return						�萔�o�b�t�@�̃|�C���^
		 */
		virtual KsConstantBuffer*		createConstantBuffer( KsUInt32 size, KsUInt32 flags );

		/**
		 * �萔�o�b�t�@�𐶐�����
		 * @param	size				[in] �o�b�t�@�T�C�Y
		 * @param	flags				[in] �t���O
		 * @return						�萔�o�b�t�@�̃|�C���^
		 */
		virtual KsConstantBuffer*		createConstantBuffer( void* pData, KsUInt32 size, KsUInt32 flags );

	protected:
		KsRenderSystemDX11*				m_RenderSystem;		/**< �`��V�X�e��	*/

};


#endif		/* __KSBUFFERMANAGERDX11_H__ */



