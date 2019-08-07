/************************************************************************************************/
/** 
 * @file		KsIndexBuffer.h
 * @brief		�C���f�b�N�X�o�b�t�@
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSINDEXBUFFER_H__
#define __KSINDEXBUFFER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsRenderContext;

/************************************************************************************************/
/**
 * @class		KsIndexBuffer
 * @brief		�C���f�b�N�X�o�b�t�@
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsIndexBuffer : public KsBufferObject
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsIndexBuffer();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsIndexBuffer();

		/**
		 * �j������
		 */
		virtual void				destroy() = 0;

		/**
		 * ���\�[�X���擾����
		 * @return					 ���\�[�X
		 */
		virtual void*				getBufferResource() = 0;

		/**
		 * �C���f�b�N�X�o�b�t�@�����b�N����
		 * @param	pContext		�`��R���e�L�X�g
		 * @param	flags			���b�N�t���O
		 * @return					���b�N�����o�b�t�@�̐擪�|�C���^
		 */
		virtual void*				lock( const KsRenderContext* pContext, KsUInt32 flags ) = 0;

		/**
		 * �C���f�b�N�X�o�b�t�@�̃��b�N����������
		 * @param	pContext		�`��R���e�L�X�g
		 */
		virtual void				unlock( const KsRenderContext* pContext ) = 0;

		/**
		 * �C���f�b�N�X�o�b�t�@����̓ǂݍ���
		 * @param	pContext		�`��R���e�L�X�g
		 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	size			�f�[�^�T�C�Y
		 */
		virtual void				read( const KsRenderContext* pContext, void* pData, KsUInt32 size ) = 0;

		/**
		 * �C���f�b�N�X�o�b�t�@�ւ̏�������
		 * @param	pContext		�`��R���e�L�X�g
		 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	size			�f�[�^�T�C�Y
		 */
		virtual void				write( const KsRenderContext* pContext, void* pData, KsUInt32 size ) = 0;

		/**
		 * �C���f�b�N�X�����擾����
		 * @return					�C���f�b�N�X��
		 */
		KsUInt32					getNumIndex() const { return m_numIndex; }

		/**
		 * �C���f�b�N�X�̃t�H�[�}�b�g�^�C�v���擾����
		 */
		KsUInt32					getIndexFormatType() const { return m_indexFormatType; }

	protected:
		KsUInt32					m_numIndex;			/**< �C���f�b�N�X��					*/
		KsUInt32					m_indexFormatType;	/**< �C���f�b�N�X�̃t�H�[�}�b�g�^�C�v	*/
};

#endif		/* __KSINDEXBUFFER_H__ */



