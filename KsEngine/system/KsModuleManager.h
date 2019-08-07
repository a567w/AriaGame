/************************************************************************************************/
/** 
 * @file		KsModule.h
 * @brief		���W���[��
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMODULEMANAGER_H__
#define __KSMODULEMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsType.h"
#include "KsSingleton.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
#if 0
/************************************************************************************************/
/**
 *  ���W���[���̃C���^�[�t�F�[�X�N���X
 *	@class		KsModule
 *	@brief		���W���[���̃C���^�[�t�F�[�X
 *	@since		2003/10/25
 *	@author		Tsukasa Kato
 */
/************************************************************************************************/
class ksENGINE_API KsModuleManager : public KsSingleton< KsModuleManager >
{
	friend class KsModule;

	public:

		/**
		 * �R���X�g���N�^
		 */
										KsModuleManager();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsModuleManager();

		/**
		 * ��������p�X��ǉ�����
		 * @param	path				�ǉ�����p�X
		 * @retval	ksTRUE				�ǉ�����
		 * @retval	kaFALSE				�ǉ����s(�p�X�����݂��Ȃ�)
		 */
		KsBool							addSearchPath( const KsString& path );

		void							removeSearchPath( const KsString& path );

		virtual void*					loadModule( const KsString& path );

		virtual void					addModule( KsModule* pModule );

		virtual void					removeModule( KsModule* pModule );

		/**
		 * �w��p�X�����݂��Ă��邩�ǂ����̃`�F�b�N
		 * @param	path				�`�F�b�N����p�X
		 * @retval	ksTRUE				�p�X�����݂���
		 * @retval	kaFALSE				�p�X�����݂��Ȃ�
		 */
		KsBool							isPathExists( const KsString& path );

	protected:
		KsArray< KsString >				m_searchPaths;		/**< �����p�X���X�g		*/
		KsHashTable< KsModule* >		m_hashModules;		/**< ���[�W���[�����X�g	*/
};

#endif

#endif /* __KSMODULEMANAGER_H__ */

