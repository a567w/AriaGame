/************************************************************************************************/
/** 
 * @file		KsBufferObject.h
 * @brief		�o�b�t�@�I�u�W�F�N�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBUFFEROBJECT_H__
#define __KSBUFFEROBJECT_H__

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
 * @struct		KS_BUFFER_DESC
 * @brief		�o�b�t�@DECS
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
typedef struct KS_BUFFER_DESC
{
    KsUInt32		ByteWidth;
    KsUInt32		Usage;
    KsUInt32		BindFlags;
    KsUInt32		CPUAccessFlags;
    KsUInt32		MiscFlags;
    KsUInt32		StructureByteStride;

} KS_BUFFER_DESC;


/************************************************************************************************/
/**
 * @class		KsIndexBuffer
 * @brief		�C���f�b�N�X�o�b�t�@
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsBufferObject : public KsRefCounter
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsBufferObject();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsBufferObject();

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
};

#endif		/* __KSBUFFEROBJECT_H__ */



