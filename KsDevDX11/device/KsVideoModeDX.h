/************************************************************************************************/
/** 
 * @file		KsVideoModeDX.h
 * @brief		�r�f�����[�h���擾����
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSVIDEOMODEDX_H__
#define __KSVIDEOMODEDX_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsTypeD3D9.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsAdapterDX;

/************************************************************************************************/
/**
 * 
 * @class	KsVideoMode
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksDEVD3D9_API KsVideoModeDX
{
	protected:
		D3DDISPLAYMODE				m_displayMode;		/**< �f�B�X�v���C���[�h			*/
		KsInt32					m_modeNumber;		/**< ���[�h���X�g�̉��Ԗڂ�		*/
		static KsInt32				m_modeCount;		/**< �ݒ�ł���r�f�I���[�h��	*/

	public:
		/**
		 * �R���X�g���N�^
		 */
									KsVideoModeDX();

		/**
		 * �R�s�[�R���X�g���N�^
		 */
									KsVideoModeDX( const KsVideoModeDX& refKsVideoMode );

		/**
		 * �R�s�[�R���X�g���N�^
		 */
									KsVideoModeDX( D3DDISPLAYMODE displayMode );

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsVideoModeDX() { --m_modeCount; }

		/**
		 * ��ʕ����擾
		 * @return					��ʕ�
		 */
		KsUInt32					getWidth() const { return m_displayMode.Width; }

		/**
		 * ��ʍ������擾
		 * @return					��ʍ���
		 */
		KsUInt32					getHeight() const { return m_displayMode.Height; }

		/**
		 * ���t���b�V�����[�g(Hz)���擾����
		 * @return					���t���b�V�����[�g(Hz)
		 */
		KsUInt32					getRefreshRate() const { return m_displayMode.RefreshRate; }

		/**
		 * �J���[�[�x(���r�b�g�J���[��)���擾����
		 * @return					�J���[�[�x
		 */
		KsUInt32					getColorDepth() const;

		/**
		 * �f�B�X�v���C�̃t�H�[�}�b�g���擾����
		 * @return					�f�B�X�v���C�̃t�H�[�}�b�g
		 */
		D3DFORMAT					getFormat() const { return m_displayMode.Format; }

		/**
		 * �f�B�X�v���C���[�h���擾����
		 * @return					�f�B�X�v���C���[�h
		 */
		D3DDISPLAYMODE				getDisplayMode() const { return m_displayMode; }

		/**
		 * ���t���b�V�����[�g(Hz)���Z�b�g����
		 * @param		rate		���t���b�V�����[�g(Hz)
		 */
		void						setRefreshRate( KsUInt32 rate ) { m_displayMode.RefreshRate = rate; } 
		
		/**
		 * �f�B�X�v���C���[�h�̏����擾����
		 * @return					�f�B�X�v���C���[�h�̏��
		 */
		KsString					getDisplayModeInfo();
};


#endif /* __KSVIDEOMODEDX_H__ */



