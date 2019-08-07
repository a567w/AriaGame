/************************************************************************************************/
/** 
 * @file		KsShaderProgram.h
 * @brief		�V�F�[�_�[�I�u�W�F�N�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSHADERPROGRAM_H__
#define __KSSHADERPROGRAM_H__

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
 * @class		KsShaderProgram
 * @brief		�V�F�[�_�[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		
 */
/************************************************************************************************/
class ksENGINE_API KsShaderProgram : public KsRefCounter
{
		friend class KsShaderManager;
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsShaderProgram();

		/**
		 * �R���X�g���N�^
		 */
									KsShaderProgram( ksSHADER_TYPE type );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsShaderProgram();

		/**
		 * �f�[�^����V�F�[�_�[�𐶐�����
		 * @param	pData			�f�[�^
		 * @param	dataSize		�f�[�^�T�C�Y
		 * @retval	ksTRUE			��������
		 * @retval	ksFALSE			�������s
		 */
		virtual KsBool				createFromMemory( const void* pData, KsUInt32 dataSize ) = 0;

		/**
		 * �V�F�[�_�[ID���擾����
		 * @return					�V�F�[�_�[ID
		 */
		KsUInt32					getID() const { return m_id; }

		/**
		 * �V�F�[�_�[�����擾����
		 * @return					�V�F�[�_�[��
		 */
		const KsString&				getName() { return m_name; }

		/**
		 * �V�F�[�_�[�^�C�v���擾����
		 * @return					�V�F�[�_�[�^�C�v
		 */
		ksSHADER_TYPE				getType() const { return m_type; }

	protected:
		KsUInt32					m_id;				/**< �V�F�[�_�[ID		*/
		KsString					m_name;				/**< �V�F�[�_�[��		*/
		ksSHADER_TYPE				m_type;				/**< �V�F�[�_�[�^�C�v		*/
};


#endif		/* __KSSHADERPROGRAM_H__ */

