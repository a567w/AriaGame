/************************************************************************************************/
/** 
 * @file		KsVertexBuffer.h
 * @brief		�C���f�b�N�X�o�b�t�@
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSINDEXBUFFER_H__
#define __KSINDEXBUFFER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsIndexBuffer
 * @brief		�C���f�b�N�X�o�b�t�@
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsIndexBuffer
{
	public:
		/**
		 * �C���f�b�N�X�o�b�t�@�𐶐�����
		 * @param	pDevice			�f�o�C�X
		 * @param	numIndex		�C���f�b�N�X�̐�
		 * @param	flags			�t���O
		 */
									KsIndexBuffer(){}

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsIndexBuffer(){}

		/**
		 * �C���f�b�N�X�o�b�t�@�����b�N����
		 * @param	startIndex		���b�N����擪�̃C���f�b�N�X
		 * @param	numIndex		���b�N����C���f�b�N�X�̐�
		 * @param	flags			���b�N�t���O
		 * @return					���b�N�����o�b�t�@�̐擪�|�C���^
		 */
		virtual void*				lock( KsUInt32 startIndex, KsUInt32 numIndex, KsUInt32 flags ) = 0;

		/**
		 * �C���f�b�N�X�o�b�t�@�̃��b�N����������
		 */
		virtual void				unlock() = 0;

		/**
		 * �C���f�b�N�X�o�b�t�@����̓ǂݍ���
		 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	startIndex		���b�N����擪�̃C���f�b�N�X
		 * @param	numIndex		���b�N����C���f�b�N�X�̐�
		 */
		virtual void				read( void* pData, KsUInt32 startIndex, KsUInt32 numIndex ) = 0;

		/**
		 * �C���f�b�N�X�o�b�t�@�ւ̏�������
		 * @param	pData			�������݃f�[�^�̃|�C���^
		 * @param	startIndex		���b�N����擪�̃C���f�b�N�X
		 * @param	numIndex		���b�N����C���f�b�N�X�̐�
		 */
		virtual void				write( void* pData, KsUInt32 startIndex, KsUInt32 numIndex ) = 0;

	protected:
		KsUInt32					m_numIndex;		/**< ���_��		*/
};

#endif		/* __KSINDEXBUFFER_H__ */



