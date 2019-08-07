/************************************************************************************************/
/**
 * @file	KsDisplayDX.h
 * @brief	
 * @author	Tsukasa Kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/************************************************************************************************/
#ifndef __KSDISPLAYDX_H__
#define __KSDISPLAYDX_H__

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
 * ��ʏ��I���N���X
 * @class	KsDisplay
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsDisplaySubItemDX
{
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsDisplaySubItemDX();

		/**
		 * �f�X�g���N�^
		 */
										~KsDisplaySubItemDX();

		/**
		 * ���t���b�V�����[�g���擾����
		 * @return						���t���b�V�����[�g
		 */
		KsUInt32						getRefreshRate() const { return m_refreshRate; }

		/**
		 * �t�H�[�}�b�g�擾
		 * @return						�t�H�[�}�b�g
		 */
		D3DFORMAT						getFormat()	const { return m_format; }

		/**
		 * �t���J���[�������Ă��邩
		 * @retval		ksTRUE			�����Ă���
		 * @retval		ksFALSE			�����Ă��Ȃ�
		 */
		KsBool							isFullColor()	const { return m_bFullColor; }

		/**
		 * ���t���b�V�����[�g���Z�b�g����
		 * @param		refreshRate		���t���b�V�����[�g
		 */
		void							setRefreshRate( KsUInt32 refreshRate ){ m_refreshRate = refreshRate; }

		/**
		 * �t�H�[�}�b�g���Z�b�g����
		 * @param		format			�t�H�[�}�b�g
		 */
		void							setFormat( D3DFORMAT format ) { m_format = format; }

		/**
		 * �t���J���[�̃t���O���Z�b�g����
		 * @param		flag			�t���J���[�������Ă��邩�̃t���O
		 */
		void							setFullColor( KsBool flag ) { m_bFullColor = flag; }

	public:
		KsUInt32						m_refreshRate;	/**< ���t���b�V�����[�g���X�g		*/
		D3DFORMAT						m_format;		/**< �t�H�[�}�b�g���X�g				*/
		KsUInt32						m_colorFlags;	/**< �ǂ̃J���[�������Ă��邩�H		*/
		KsBool							m_bFullColor;	/**< �t���J���[�������Ă��邩�ǂ���	*/
		KsArray< D3DFORMAT >			m_vFormatList;	/**< �t�H�[�}�b�g�̎��				*/
};

/************************************************************************************************/
/**
 * ��ʏ��I���N���X<BR>
 * @class	KsDisplay
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsDisplayItemDX
{
	public:
		typedef KsArray< KsDisplaySubItemDX* >	KsDisplaySubItemDXList;

	public:
		/**
		 * �R���X�g���N�^
		 */
										KsDisplayItemDX();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsDisplayItemDX();

		/**
		 * ��ʕ����擾����
		 * @return						��ʕ�
		 */
		KsInt32						getWidth() const { return m_width; }

		/**
		 * ��ʂ̍������擾����
		 * @return						��ʂ̍���
		 */
		KsInt32						getHeight() const { return m_height; }

		/**
		 * ��ʕ����Z�b�g����
		 * @param		width			��ʕ�
		 */
		void							setWidth( KsInt32 width ) { m_width = width; }

		/**
		 * ��ʂ̍������Z�b�g����
		 * @param		height			��ʂ̍���
		 */
		void							setHeight( KsInt32 height ) { m_height = height; }

	public:
		KsInt32						m_width;			/**< ��				*/
		KsInt32						m_height;			/**< ����			*/
		KsDisplaySubItemDXList			m_vpSubItems;		/**< �T�u�A�C�e��	*/
};

/************************************************************************************************/
/**
 * ��ʏ��I�����X�g�N���X<BR>
 * @class	KsDisplayListDX
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsDisplayDX
{
	public:
		typedef KsArray< KsDisplayItemDX* >	KsDisplayItemDXList;

	public:
		/**
		 * �R���X�g���N�^
 		 * @param		pAdapter		�A�_�v�^
		 */
										KsDisplayDX( KsAdapterDX* pAdapter );
		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsDisplayDX();

		/**
		 * ��ʐݒ�����擾����
		 * @param		index			�z��̎w��C���f�b�N�X
		 * @return						��ʐݒ���
		 */
		const KsDisplayItemDX*			getItem( KsInt32 index ) { return m_vDisplayItems[ index ]; }

		/**
		 * ��ʐݒ���̐����擾����
		 * @return						��ʐݒ���̐�
		 */
		KsUInt32						getCount() const { return m_vDisplayItems.size(); }

		/**
		 * �A�_�v�^�����擾����
		 * @return						�A�_�v�^��
		 */
		const KsString&					getAdapterName() { return m_adapterName; }

	protected:
		KsString						m_adapterName;		/**< �A�_�v�^��				*/
		KsDisplayItemDXList				m_vDisplayItems;	/**< ��ʐݒ��񃊃X�g		*/
};

#endif	/* __KSDISPLAYDX_H__ */


