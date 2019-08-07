/************************************************************************************************/
/** 
 * @file		KsHandleManager.h
 * @brief		�n���h���}�l�[�W��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSHANDLEMANAGER_H__
#define __KSHANDLEMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsTypeScript.h"
#include "KsVariable.h"
#include "KsStringObject.h"
#include "KsGlobalObject.h"
#include "KsStructObject.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 *	@class		KsHandleManager
 *	@brief		�n���h���}�l�[�W��
 *	@since		2005/10/25
 *	@author		Tsukasa Kato
 */
/************************************************************************************************/
class ksSCRIPT_API KsHandleManager
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsHandleManager();

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsHandleManager();

		/**
		 * �֐��̃n���h��
		 */
		KsHandle							getFuncHandle();

		/**
		 * �ϐ��̃n���h��
		 */
		KsHandle							getGlobalHandle( const KsChar* pString );

		/**
		 * ������̃n���h��
		 */
		KsHandle							getStringHandle( const KsChar* pString );

		/** 
		 * �\���̂̃n���h��
		 */
		KsHandle							getStructHandle( const KsChar* pString );
		KsGlobalObject*						getGlobalObject( const KsChar* pString );
		KsStructObject*						getStructObject( const KsChar* pString );

		//
		KsHandle							createStringHandle( const KsChar* pString );
		KsHandle							createGlobalHandle( const KsChar* pString );
		KsStructObject*						createStructObject( const KsChar* pString );

		void								destoryStringObject( KsHandle handle );
		void								destoryGlobalObject( KsHandle handle );
		void								destoryStructObject( KsHandle handle );

	public:
		/* �n�b�V���e�[�u������ϐ�����֐����Ŏw��I�u�W�F�N�g���������� */
		/* ��������Ǘ����� */
		KsHashTable< KsHandleObject* >		m_stringHandleList;		/**< ������̃n���h���I�u�W�F�N�g���X�g			*/

		/* �O���[�o���ϐ����Ǘ����� */
		KsHashTable< KsHandleObject* >		m_globalHandleList;		/**< �O���[�o���ϐ��̃n���h���I�u�W�F�N�g���X�g	*/

		/* �\���̂��Ǘ����� */
		KsHashTable< KsHandleObject* >		m_structHandleList;		/**< �\���̂̃n���h���I�u�W�F�N�g���X�g			*/
};


extern KsHandle KsGetStringHandle( KsHandleManager* pHM, const KsChar* pString );
extern KsHandle KsGetGlobalHandle( KsHandleManager* pHM, const KsChar* pString );
extern KsHandle KsGetStructHandle( KsHandleManager* pHM, const KsChar* pString );
extern KsHandle KsGetFuncHandle( const KsChar* pString );

extern KsHandleObject* KsGetHandleObject( KsHandle handle );
extern KsGlobalObject* KsGetGlobalObject( KsHandleManager* pHM, const KsChar* pString );
extern KsStructObject* KsGetStructObject( KsHandleManager* pHM, const KsChar* pString );

extern KsHandle KsCreateStringHandle( KsHandleManager* pHM, const KsChar* pString );
extern KsHandle KsCreateGlobalHandle( KsHandleManager* pHM, const KsChar* pString );

extern void KsDestoryStringObject( KsHandleManager* pHM, KsHandle handle );
extern void KsDestoryGlobalObject( KsHandleManager* pHM, KsHandle handle );
extern void KsDestoryStructObject( KsHandleManager* pHM, KsHandle handle );

#endif		/* __KSHANDLEMANAGER_H__	*/




