/************************************************************************************************/
/** 
 * @file		KsScript.h
 * @brief		�X�N���v�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSCRIPT_H__
#define __KSSCRIPT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsTypeScript.h"
#include "KsVariable.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * �X�N���v�g
 * @class	KsScript
 * @author	Tsukasa Kato
 * @since   2006/--/--
 * @version 2006/--/--
 */
/************************************************************************************************/
class ksSCRIPT_API KsScript
{
		friend class KsVirtualMachine;

	public:
		/**
		 * �R���X�g���N�^
		 */
								KsScript();

		/**
		 * �f�X�g���N�^
		 */
		virtual				~KsScript();

		/**
		 * �X�N���v�g�쐬
		 * @param	size		�T�C�Y
		 */
		void					create( KsInt32 size );

		/**
		 * �X�N���v�g��j������
		 */
		void					destroy();

		/**
		 * �X�N���v�g�R�[�h���擾����
		 * @return				�X�N���v�g�R�[�h�̃|�C���^
		 */
		KsChar*					getCode() { return m_pCode; }

		/**
		 * �X�N���v�g�����擾����
		 * @return				�X�N���v�g��
		 */
		const KsString&			getName() { return m_name; }

		/**
		 * �X�N���v�gID���擾����
		 * @return				�X�N���v�gID
		 */
		KsInt32				getID() const { return m_id; }

		/**
		 * ������n���h�����X�g���擾����
		 * @return				������n���h�����X�g
		 */
		KsHandleList*			getStringHandleList() { return m_pStringHandleList; }

		/**
		 * �O���[�o���n���h�����X�g���擾����
		 * @return				�O���[�o���n���h�����X�g
		 */
		KsHandleList*			getGlobalHandleList() { return m_pGlobalHandleList; }

		/**
		 * �\���̃n���h�����X�g���擾����
		 * @return				�\���̃n���h�����X�g
		 */
		KsHandleList*			getStructHandleList() { return m_pStructHandleList; }

		/**
		 * �֐��n���h�����X�g���擾����
		 * @return				�֐��n���h�����X�g
		 */
		KsHandleList*			getFuncHandleList() { return m_pFuncHandleList; }

	protected:
		KsString				m_name;					/**< �X�N���v�g��					*/
		KsInt32				m_id;					/**< ���ʗp�h�c						*/
		KsChar*					m_pCode;				/**< ���s�R�[�h						*/
		KsHandleList*			m_pStringHandleList;	/**< ������n���h�����X�g			*/
		KsHandleList*			m_pGlobalHandleList;	/**< �O���[�o���n���h�����X�g		*/
		KsHandleList*			m_pStructHandleList;	/**< �\���̃n���h�����X�g			*/
		KsHandleList*			m_pFuncHandleList;		/**< �֐��n���h�����X�g				*/
};


#endif /* __KSSCRIPT_H__ */



