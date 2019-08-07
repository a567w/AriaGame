/************************************************************************************************/
/** 
 * @file		KsGameSingltonTask.h
 * @brief		�Q�[���V���O���g���^�X�N
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSCONTROLTASK_H__
#define __KSCONTROLTASK_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsGameCore.h"
#include "KsGameTask.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsGameSingltonTask
 * @brief		�Q�[���V���O���g���^�X�N
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsGameSingltonTask : public KsGameTask, public KsSingleton< KsGameSingltonTask >
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsGameSingltonTask(){}

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsGameSingltonTask(){}

		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return							�V���O���g���̎Q��
		 */
		static KsGameSingltonTask&			getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return							�V���O���g���̃|�C���^
		 */
		static KsGameSingltonTask*			getInstancePtr();

	protected:
		/**
		 * ����������(�}�l�[�W���ɓo�^���ꂽ�Ƃ��ɓo�^)
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						initialize( void* pParam );

		/**
		 * �^�X�N�̎��s
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						execute( void* pParam );

		/**
		 * �`�揈��
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						render( void* pParam );

		/**
		 * �㏈���֐��Ń������[����폜�����Ƃ��ɌĂ΂��
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						terminate( void* pParam );
};

#endif		/* __KSCONTROLTASK_H__ */



