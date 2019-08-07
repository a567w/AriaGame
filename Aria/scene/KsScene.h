/************************************************************************************************/
/** 
 * @file		KsScene.h
 * @brief		�V�[��
 * @author		Tsukasa Kato
 * @date		2011/07/02
 * @since		2011/07/02
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSCENE_H__
#define __KSSCENE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsSceneType.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * �V�[��
 * @class	KsScene
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsScene : public KsTask
{
	public:
		/**
		 * �R���X�g���N�^
		 * @param	updateOrder				�X�V�I�[�_�[
		 * @param	drawOrder				�`��I�[�_�[
		 */
											KsScene( ksSCENE_TYPE sceneType, KsUInt32 updateOrder, KsUInt32 drawOrder );

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsScene();

	protected:
		/**
		 * �X�V����
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						update( void* pParam );

		/**
		 * �`�揈��
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						draw( void* pParam );

	private:
		ksSCENE_TYPE						m_sceneType;		/**< �V�[���^�C�v	*/
};

#endif	/* __KSSCENE_H__ */

