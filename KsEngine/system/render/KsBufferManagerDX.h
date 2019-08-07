/************************************************************************************************/
/** 
 * @file		KsBufferManagerDX.h
 * @brief		�o�b�t�@�}�l�[�W��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBUFFERMANAGERDX_H__
#define __KSBUFFERMANAGERDX_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsBufferManager.h"
#include "KsVertexBufferDX.h"
#include "KsIndexBufferDX.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsBufferManager
 * @brief		�o�b�t�@�}�l�[�W��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsBufferManagerDX : public KsBufferManager
{
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsBufferManagerDX( IDirect3DDevice9* pDevice ) : m_pDevice( pDevice ) {}

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsBufferManagerDX(){}

		/**
		 * ���_�o�b�t�@�𐶐�����
		 * @param		vertexSize		���_�T�C�Y
		 * @param		numVertex		���_��
		 * @param		vertexFormat	���_�t�H�[�}�b�g
		 * @param		flags			�t���O
		 * @return						���_�o�b�t�@�̃|�C���^
		 */
		virtual KsVertexBuffer*		createVertexBuffer( KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags );

		/**
		 * �C���f�b�N�X�o�b�t�@�𐶐�����
		 * @param		numIndex		�C���f�b�N�X��
		 * @param		flags			�t���O
		 * @return						�C���f�b�N�X�o�b�t�@�̃|�C���^
		 */
		virtual KsIndexBuffer*			createIndexBuffer( KsUInt32 numIndex, KsUInt32 flags );

	protected:
		IDirect3DDevice9*				m_pDevice;		/**< �f�o�C�X	*/

};

#endif		/* __KSBUFFERMANAGERDX_H__ */



