/************************************************************************************************/
/** 
 * @file		KsVertexBuffer.h
 * @brief		���_�o�b�t�@
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSVERTEXBUFFER_H__
#define __KSVERTEXBUFFER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
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
 * @class		KsVertexBuffer
 * @brief		���_�o�b�t�@
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsVertexBuffer : public KsBufferObject
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsVertexBuffer();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsVertexBuffer();

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
		 * ���_�o�b�t�@�����b�N����
		 * @param	pContext		�`��R���e�L�X�g
		 * @param	flags			���b�N�t���O
		 * @return					���b�N�����o�b�t�@�̐擪�|�C���^
		 */
		virtual void*				lock( const KsRenderContext* pContext, KsUInt32 flags ) = 0;

		/**
		 * ���_�o�b�t�@�̃��b�N����������
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
		 * ���_�̃T�C�Y���擾����
		 * @return					���_�̃T�C�Y
		 */
		virtual KsUInt32			getVertexSize() const { return m_vertexSize; }

		/**
		 * ���_�����擾����
		 * @return					���_��
		 */
		virtual KsUInt32			getNumVertex() const { return m_numVertex; }

		/**
		 * ���_�t�H�[�}�b�g���擾����
		 * @return					���_�t�H�[�}�b�g��
		 */
		virtual KsUInt32			getVertexFormat() const { return m_vertexFormat; }

	protected:
		KsUInt32					m_vertexSize;		/**< ���_�̃T�C�Y		*/
		KsUInt32					m_numVertex;		/**< ���_��				*/
		KsUInt32					m_vertexFormat;		/**< ���_�t�H�[�}�b�g		*/
};

#endif		/* __KSVERTEXBUFFER_H__ */



