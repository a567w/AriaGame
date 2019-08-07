/************************************************************************************************/
/** 
 * @file		KsBufferManager.h
 * @brief		�o�b�t�@�}�l�[�W��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBUFFERMANAGER_H__
#define __KSBUFFERMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsSingleton.h"
#include "KsVertexBuffer.h"
#include "KsIndexBuffer.h"

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
class KsBufferManager : public KsSingleton< KsBufferManager >
{
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsBufferManager(){}

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsBufferManager(){}

		/**
		 * ���_�o�b�t�@�𐶐�����
		 * @param		vertexSize		���_�T�C�Y
		 * @param		numVertex		���_��
		 * @param		vertexFormat	���_�t�H�[�}�b�g
		 * @param		flags			�t���O
		 * @return						���_�o�b�t�@�̃|�C���^
		 */
		virtual KsVertexBuffer*		createVertexBuffer( KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags ) = 0;

		/**
		 * �C���f�b�N�X�o�b�t�@�𐶐�����
		 * @param		numIndex		�C���f�b�N�X��
		 * @param		flags			�t���O
		 * @return						�C���f�b�N�X�o�b�t�@�̃|�C���^
		 */
		virtual KsIndexBuffer*			createIndexBuffer( KsUInt32 numIndex, KsUInt32 flags ) = 0;

		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return						�V���O���g���̎Q��
		 */
		static KsBufferManager&			getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return						�V���O���g���̃|�C���^
		 */
		static KsBufferManager*			getInstancePtr();
};

#endif		/* __KSBUFFERMANAGER_H__ */



