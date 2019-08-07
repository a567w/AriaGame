/************************************************************************************************/
/** 
 * @file		KsTexture.h
 * @brief		�e�N�X�`��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSTEXTURE_H__
#define __KSTEXTURE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
/* 0����15�r�b�g�܂ł͋��ʃt���O��16�r�b�g�ȍ~�͌ŗL�Ŋg���p */
#define ksTEXTURE_FLAG_USE_MANAGER		( 1 << 0 )		/**< �e�N�X�`���}�l�[�W�����g�p����	*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsTexture
 * @brief		�e�N�X�`��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		�Q�ƃJ�E���^��
 */
/************************************************************************************************/
class ksENGINE_API KsTexture : public KsBufferObject
{
		friend class KsTextureManager;

	protected:
		KsString					m_name;			/**< �e�N�X�`����					*/
		KsUInt32					m_id;			/**< �e�N�X�`��ID					*/
		KsUInt32					m_flags;		/**< �e��t���O						*/
		KsUInt32					m_numMipmap;	/**< �~�b�v�}�b�v��					*/
		KsUInt32					m_mipLevels;	/**< �~�b�v�}�b�v���x��				*/
		KsUInt16					m_width;		/**< ��								*/
		KsUInt16					m_height;		/**< ����							*/
		KsTexture*					m_pNext;		/**< �e�N�X�`���̃��X�g				*/

	public:
		/**
		 * �R���X�g���N�^
		 */
									KsTexture();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsTexture();

		/**
		 * �e�N�X�`���̔j��
		 */
		virtual void				destroy() = 0;

		/**
		 * �e�N�X�`�����A�N�e�B�u�ɂ���
		 */
		virtual void				active() = 0;

		/**
		 * ���\�[�X���擾����
		 * @return					 ���\�[�X
		 */
		virtual void*				getBufferResource() = 0;

		/**
		 * ���\�[�X���擾����
		 * @return					 ���\�[�X
		 */
		virtual void*				getTextureResource() = 0;

		/**
		 * �o�b�t�@�����b�N����
		 * @param	pContext		�`��R���e�L�X�g
		 * @param	flags			���b�N�t���O
		 * @return					���b�N�����o�b�t�@�̐擪�|�C���^
		 */
		virtual void*				lock( const KsRenderContext* pContext, KsUInt32 flags ) = 0;

		/**
		 * �o�b�t�@�̃��b�N����������
		 * @param	pContext		�`��R���e�L�X�g
		 */
		virtual void				unlock( const KsRenderContext* pContext ) = 0;

		/**
		 * �o�b�t�@����̓ǂݍ���
		 * @param	pContext		�`��R���e�L�X�g
		 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	size			�f�[�^�T�C�Y
		 */
		virtual void				read( const KsRenderContext* pContext, void* pData, KsUInt32 size ) = 0;

		/**
		 * �o�b�t�@�ւ̏�������
		 * @param	pContext		�`��R���e�L�X�g
		 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	size			�f�[�^�T�C�Y
		 */
		virtual void				write( const KsRenderContext* pContext, void* pData, KsUInt32 size ) = 0;

		/**
		 * �e�N�X�`�������Z�b�g����
		 * @param	pFileName		�e�N�X�`����
		 */
		void						setName( const KsChar* pFileName );

		/**
		 * �t���O�擾
		 * @param	flags			�e�N�X�`���̊e��t���O
		 */
		void						setFlags( KsUInt32 flags ) { m_flags = flags; }

		/**
		 * �t���O�擾
		 * @return					�e�N�X�`���̊e��t���O
		 */
		KsUInt32					getFlags() const { return m_flags; }

		/**
		 * �e�N�X�`�������擾����
		 * @return					�e�N�X�`����
		 */
		const KsChar*				getName() { return m_name.c_str(); }

		/**
		 * �e�N�X�`��ID���擾����
		 * @return					�e�N�X�`��ID
		 */
		KsUInt32					getID() const { return m_id; }

		/**
		 * �e�N�X�`���̕����擾����
		 * @return					�e�N�X�`���̕�
		 */
		KsUInt16					getWidth() const { return m_width; }

		/**
		 * �e�N�X�`���̍������擾����
		 * @return					�e�N�X�`���̍���
		 */
		KsUInt16					getHeight() const { return m_height; }

		/**
		 * �~�b�v�}�b�v�̐����擾
		 * @return					�����Ă���~�b�v�}�b�v��
		 */
		KsUInt32					getNumMipmap() const { return m_numMipmap; }

		/**
		 * �~�b�v�}�b�v�������Ă��邩�ǂ���?
		 * @retval	ksTRUE			�����Ă���
		 * @retval	ksFALSE			�����Ă��Ȃ�
		 */
		KsBool						hasMipmap() { return ( m_numMipmap > 0 ); }

		/**
		 * �~�b�v�}�b�v���x�����擾����
		 * @return					�~�b�v�}�b�v���x��
		 */
		KsBool						getMipLevels() { return m_mipLevels; }
		
};

/************************************************************************************************/
/**
 * �e�N�X�`�����X�g
 */
/************************************************************************************************/
typedef KsArray<KsTexture*>	KsTextureArray;

#endif		/* __KSTEXTURE_H__ */



