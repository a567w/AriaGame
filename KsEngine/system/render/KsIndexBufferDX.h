/************************************************************************************************/
/** 
 * @file		KsIndexBufferDX.h
 * @brief		�C���f�b�N�X�o�b�t�@
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSINDEXBUFFERDX_H__
#define __KSINDEXBUFFERDX_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsIndexBuffer.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr9.h>

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsIndexBufferDX
 * @brief		�C���f�b�N�X�o�b�t�@
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsIndexBufferDX : public KsIndexBuffer
{
	public:
		/**
		 * �C���f�b�N�X�o�b�t�@�𐶐�����
		 * @param	pDevice			�f�o�C�X
		 * @param	numIndex		�C���f�b�N�X�̐�
		 * @param	flags			�t���O
		 */
									KsIndexBufferDX( IDirect3DDevice9* pDevice, KsUInt32 numIndex, KsUInt32 flags=D3DPOOL_DEFAULT );

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsIndexBufferDX();

		/**
		 * �C���f�b�N�X�o�b�t�@�����b�N����
		 * @param	startIndex		���b�N����擪�̃C���f�b�N�X
		 * @param	numIndex		���b�N����C���f�b�N�X�̐�
		 * @param	flags			���b�N�t���O
		 * @return					���b�N�����o�b�t�@�̐擪�|�C���^
		 */
		virtual void*				lock( KsUInt32 startIndex, KsUInt32 numIndex, KsUInt32 flags );

		/**
		 * �C���f�b�N�X�o�b�t�@�̃��b�N����������
		 */
		virtual void				unlock();

		/**
		 * �C���f�b�N�X�o�b�t�@����̓ǂݍ���
		 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	startIndex		���b�N����擪�̃C���f�b�N�X
		 * @param	numIndex		���b�N����C���f�b�N�X�̐�
		 */
		virtual void				read( void* pData, KsUInt32 startIndex, KsUInt32 numIndex );

		/**
		 * �C���f�b�N�X�o�b�t�@�ւ̏�������
		 * @param	pData			�������݃f�[�^�̃|�C���^
		 * @param	startIndex		���b�N����擪�̃C���f�b�N�X
		 * @param	numIndex		���b�N����C���f�b�N�X�̐�
		 */
		virtual void				write( void* pData, KsUInt32 startIndex, KsUInt32 numIndex );

		/**
		 * �C���f�b�N�X�o�b�t�@�o�b�t�@���擾
		 * @return					�C���f�b�N�X�o�b�t�@�̃|�C���^
		 */
		IDirect3DIndexBuffer9*		getIndexBuffer() { return m_pIndexBuffer; }

	private:
		IDirect3DIndexBuffer9*		m_pIndexBuffer;	/**< DirectX�C���f�b�N�X�o�b�t�@		*/
};

#endif		/* __KSINDEXBUFFERDX_H__ */


