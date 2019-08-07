/************************************************************************************************/
/** 
 * @file		KsStructObject.h
 * @brief		�\���̃I�u�W�F�N�g
 * @author		Tsukasa Kato
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSTRUCTOBJECT_H__
#define __KSSTRUCTOBJECT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsTypeScript.h"
#include "KsStringObject.h"

/************************************************************************************************/
/**
 * �\���̃����o�[���
 * @class	KsStructMemberInfo
 * @author	Tsukasa Kato
 * @since   2006/--/--
 * @version 2006/--/--
 */
/************************************************************************************************/
typedef struct KsStructMemberInfo
{
	KsChar						name[ 56 ];		/**< �����o�[�ϐ�����֐����ő�(55����)	*/
	KsInt32					handle;			/**< �n���h���܂��̓C���f�b�N�X			*/
	KsStructMemberInfo*			next;			/**< ���̃����o�[�ւ̃|�C���^			*/
}KsStructMemberInfo;

/************************************************************************************************/
/**
 * �\���̃I�u�W�F�N�g
 * @class	KsStructObject
 * @author	Tsukasa Kato
 * @since   2006/--/--
 * @version 2006/--/--
 */
/************************************************************************************************/
class KsStructObject : public KsStringObject
{
		friend class KsHandleManager;
		friend class KsVirtualMachine;

	public:
		/**
		 * �R���X�g���N�^
		 */
										KsStructObject();

		/**
		 * �R���X�g���N�^
		 * @param	pString			������
		 */
										KsStructObject( const KsChar* pString );


		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsStructObject();

		/**
		 * �^�C�v�擾
		 */
		virtual ksVALUE_TYPE			getType() const { return ksVALUE_STRCT; }

		/**
		 * ���O����\���̃����o�[�����擾����
		 * @param	pName				���O
		 * @return						�\���̃����o�[���
		 */
		KsStructMemberInfo*				findVar( const KsChar* pName );

		/**
		 * ���O����\���̃����o�[���̃C���f�b�N�X���擾����
		 * @param	pName				���O
		 * @return						�\���̃����o�[���̃C���f�b�N�X
		 */
		KsInt32						findVarIndex( const KsChar* pName );

	public:
		KsInt32						m_numMember;		/**< �����o�[�̐�			*/
		KsInt32						m_numVar;			/**< �����o�[�ϐ��̐�		*/
		KsInt32						m_numFunc;			/**< �����o�[�֐��̐�		*/
		KsStructMemberInfo*				m_pVarList;			/**< �����o�[�ϐ��̃��X�g	*/
		KsStructMemberInfo*				m_pFuncList;		/**< �����o�[�֐��̃��X�g	*/

		//KsStructMemberInfo*			findFunc( const KsChar* pName );
};



#endif /* __KSSTRUCTOBJECT_H__ */

