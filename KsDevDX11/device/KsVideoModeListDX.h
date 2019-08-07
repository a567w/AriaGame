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
#ifndef __KSVIDEOMODELISTDX_H__
#define __KSVIDEOMODELISTDX_H__

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
 * @class	KsVideoModeListDX
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksDEVD3D9_API KsVideoModeListDX
{
	public:
		typedef KsArray< KsVideoModeDX* >		KsVideoModeDXArray;

	protected:
		KsVideoModeDXArray			m_vpVideoModeList;	/**< �r�f�I���[�h���X�g	*/
		KsAdapterDX*				m_pAdapter;			/**< �A�_�v�^			*/
	
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsVideoModeListDX();

		/**
		 * �R���X�g���N�^
		 * @param		pAdapter	�A�_�v�^�̃|�C���^
		 */
									KsVideoModeListDX( KsAdapterDX* pAdapter );

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsVideoModeListDX();

		/**
		 * ������
		 * @param		pAdapter	�A�_�v�^�N���X�̃|�C���^
		 * @retval		ksTRUE		����
		 * @retval		ksFALSE		���s
		 */
		KsBool						initialize( KsAdapterDX* pAdapter );

		/**
		 * �A�C�e�������擾����
		 * @return					�A�C�e����
		 */
		KsUInt32					getCount();


		/**
		 * �A�C�e�������擾����
		 * @return					�A�C�e����
		 */
		KsUInt32					getCount() const;

		/**
		 * �w��C���f�b�N�X�̃r�f�I���[�h���擾����
		 * @param		index		�w��C���f�b�N�X
		 * @return					�r�f�I���[�h
		 */
		KsVideoModeDX*				getItem( KsInt32 index );

		/**
		 * �w�薼�̃r�f�I���[�h���擾����
		 * @param		name		�r�f�I���[�h��
		 * @return					�r�f�I���[�h
		 */
		KsVideoModeDX*				getItem( const KsString& name );
};


#endif /* __KSVIDEOMODELISTDX_H__ */



