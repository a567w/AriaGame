/************************************************************************************************/
/** 
 * @file		KsAdapterDX.h
 * @brief		�A�_�v�^���<BR>
 * @author		Tsukasa Kato
 * @date		2003/03/22
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSADAPTERDX_H__
#define __KSADAPTERDX_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr9.h>

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsVideoModeDXList;


/************************************************************************************************/
/**
 * �E�C���h�E�A�v���P�[�V�����̃p�����[�^�N���X<BR>
 * @class	KsVideoMode
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsAdapterDX
{
	protected:
		IDirect3D9*									m_pD3D;					/**< Direct3D9�I�u�W�F�N�g	*/
		KsUInt32									m_adapterNumber;		/**< �A�_�v�^�i���o�[			*/
		D3DADAPTER_IDENTIFIER9						m_adapterIdentifier;	/**< �A�_�v�^�m�F			*/
		D3DDISPLAYMODE								m_desktopDisplayMode;	/**< �f�B�X�v���C���[�h		*/
		KsVideoModeDXList*							m_pVideoModeList;		/**< �r�f�I���[�h���X�g		*/
		KsInt32									m_tempNumber;			/**< �\���i���o�[			*/
		static KsInt32								m_adapterCount;			/**< �A�_�v�^��				*/

	public:
		/**
		 * �R���X�g���N�^
		 */
													KsAdapterDX();

		/**
		 * �R���X�g���N�^(�R�s�[)
		 * @param		refAdapter					�A�_�v�^
		 */
													KsAdapterDX( const KsAdapterDX& refAdapter );

		/**
		 * �R���X�g���N�^
		 * @param		pD3D						Direct3D9�I�u�W�F�N�g
		 * @param		adapterNumber				�A�_�v�^�i���o�[
		 * @param		adapterIdentifier			�A�_�v�^�m�F
		 * @param		desktopDisplayMode			�f�B�X�v���C���[�h
		 */
													KsAdapterDX( IDirect3D9* pD3D, KsUInt32 adapterNumber, D3DADAPTER_IDENTIFIER9 adapterIdentifier, D3DDISPLAYMODE desktopDisplayMode );

		/**
		 * �f�X�g���N�^
		 */
		virtual									~KsAdapterDX();

		/**
		 * �A�_�v�^�����擾����
		 * @return									�A�_�v�^��
		 */
		std::string									getAdapterName();

		/**
		 * �A�_�v�^�ڍׂ��擾����
		 * @return									�A�_�v�^�ڍ�
		 */
		std::string									getAdapterDescription();

		/**
		 * Direct3D9�I�u�W�F�N�g���擾����
		 * @return									Direct3D9�I�u�W�F�N�g
		 */
		IDirect3D9*									getD3D() { return m_pD3D; }

		/**
		 * �A�_�v�^�i���o�[���擾����
		 * @return									�A�_�v�^�i���o		
		 */
		KsUInt32									getAdapterNumber() const { return m_adapterNumber; }

		/**
		 * �A�_�v�^�i���o�[���擾����
		 * @return									�A�_�v�^�i���o		
		 */
		D3DADAPTER_IDENTIFIER9						getAdapterIdentifier() const { return m_adapterIdentifier; }

		/**
		 * �A�_�v�^�i���o�[���擾����
		 * @return									�A�_�v�^�i���o		
		 */
		D3DDISPLAYMODE								getDesktopMode() const { return m_desktopDisplayMode; }

		/**
		 * �A�_�v�^�i���o�[���擾����
		 * @return									�A�_�v�^�i���o		
		 */
		KsVideoModeDXList*							getVideoModeList();
};


/************************************************************************************************/
/**
 * �E�C���h�E�A�v���P�[�V�����̃p�����[�^�N���X<BR>
 * @class	KsVideoMode
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsAdapterDXList
{
	public:
		typedef std::vector< KsAdapterDX >				KsAdapterDXArray;
		typedef std::vector< KsAdapterDX >::iterator	KsAdapterDXPtr;

	private:
		KsAdapterDXArray							m_adapterList;	/**< �A�_�v�^���X�g			*/
		IDirect3D9*									m_pD3D;			/**< Direct3D9�I�u�W�F�N�g	*/

	public:

		/**
		 * �R���X�g���N�^
		 * @param									Direct3D9�I�u�W�F�N�g
		 */
													KsAdapterDXList( IDirect3D9* pD3D );

		/**
		 * �f�X�g���N�^
		 */
		virtual									~KsAdapterDXList();

		/**
		 * ����������
		 * @param									Direct3D9�I�u�W�F�N�g
		 * @retval			ksTRUE					����
		 * @retval			ksFALSE					���s
		 */
		KsBool										initialize( IDirect3D9* pD3D );

		/**
		 * �A�C�e�������擾����
		 * @return									�A�C�e����
		 */
		KsUInt32									getCount() const;

		/**
		 * �w��C���f�b�N�X�̃A�_�v�^���擾����
		 * @param			index					�w��C���f�b�N�X
		 * @return									�A�_�v�^
		 */
		KsAdapterDX*								getItem( KsInt32 index );

		/**
		 * �w�薼�̃A�_�v�^���擾����
		 * @param			name					�A�_�v�^��
		 * @return									�A�_�v�^
		 */
		KsAdapterDX*								getItem( const std::string& name );
};


#endif		/* __KSADAPTERDX_H__ */

