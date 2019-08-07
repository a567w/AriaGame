/************************************************************************************************/
/** 
 * @file		KsVirtualMachine.h
 * @brief		�o�[�`�����}�V��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSVIRTUALMACHINE_H__
#define __KSSVIRTUALMACHINE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsTypeScript.h"
#include "KsVariable.h"
#include "KsFunction.h"
#include "KsHandleManager.h"
#include "KsScript.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define ksVARIABLE_STACK_SIZE		( 1024 * 10 )	/**< �ϐ��̃X�^�b�N�̃T�C�Y				*/
#define ksHANDLE_LIST_BLOCK_SIZE	( 1024 * 10 )	/**< �n���h�����X�g�u���b�N�̃T�C�Y		*/
#define ksSTRUCT_MEMBER_BLOCK_SIZE	( 256 )			/**< �\���̃����o�[�u���b�N�̃T�C�Y		*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * �o�[�W�����}�V��
 * @class	KsVirtualMachine
 * @author	Tsukasa Kato
 * @since   2006/--/--
 * @version 2006/--/--
 */
/************************************************************************************************/
class ksSCRIPT_API KsVirtualMachine
{
	private:
		KsInt32								m_id;						/**< �Ǘ�ID�o�^�p				*/
		KsInt32								m_pos;						/**< �X�^�b�N�ʒu				*/
		KsInt32								m_end;						/**< �X�^�b�N�Ō�̈ʒu			*/
		KsVariable*							m_variables;				/**< �S�̂̃X�^�b�N				*/
		KsVariable*							m_esp;						/**< �Ō�ɃZ�b�g���ꂽ�l(�Ԃ�l�Ƃ��͂������Q�Ƃ���΂���)*/
		KsMemoryFixed						m_structMemberBlock;		/**< �\���̂̃����o�[�u���b�N		*/
		KsMemoryFixed						m_handleListBlock;			/**< �n���h���̃��X�g�p�u���b�N	*/

	public:
		KsArray< KsScript* >				m_vpScripts;				/**< �ő�̃X�N���v�g���X�g			*/
		KsHashTable< KsFunction* >			m_vpFunctions;				/**< �O���[�o���֐����X�g				*/
		KsHashTable< KsScriptLibCallback >	m_vpLibraries;				/**< ���C�u�����֐����X�g				*/
		KsUInt32							m_variableStackSize;		/**< �ϐ��̃X�^�b�N�̃T�C�Y			*/
		KsUInt32							m_structMemberBlockSize;	/**< �n���h�����X�g�u���b�N�̃T�C�Y	*/
		KsUInt32							m_handleListBlockSize;		/**< �\���̃����o�[�u���b�N�̃T�C�Y	*/
		KsHandleManager*					m_pHandleManager;			/**< �n���h���}�l�[�W��				*/
	private:
		/**
		 * ��ID����������
		 * @return							�󂫃X�N���v�gID
		 */
		KsInt32								findFreeID();

		/**
		 * ID����X�N���v�g����������
		 * @param	id						�X�N���v�gID
		 * @return							���������X�N���v�g�|�C���^
		 */
		KsScript*							findScript( KsInt32 id );

		/**
		 * �\���̃����o�[���m��
		 * @return							�\���̃����o�[���|�C���^
		 */
		KsStructMemberInfo*					allocStructMemberBlock();

		/**
		 * �n���h�����X�g�u���b�N�m��
		 * @return							�n���h�����X�g�u���b�N�|�C���^
		 */
		KsHandleList*						allocHandleListBlock();

		/**
		 * �X�N���v�g�֐��̌Ăяo��
		 * @param	pFunc					�Ăяo���֐�
		 */
		void								call( KsFunction* pFunc );

	public:
		/**
		 * �R���X�g���N�^
		 */
											KsVirtualMachine();

		/**
		 * �R���X�g���N�^(�X�N���v�g�G���W���̏�������������)
		 * @param	variableStackSize		�ϐ��̃X�^�b�N�̃T�C�Y
		 * @param	structMemberBlockSize	�n���h�����X�g�u���b�N�̃T�C�Y
		 * @param	handleListBlockSize		�\���̃����o�[�u���b�N�̃T�C�Y
		 */
											KsVirtualMachine( KsUInt32 variableStackSize, KsUInt32 structMemberBlockSize, KsUInt32 handleListBlockSize );

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsVirtualMachine();

		/**
		 * �ϐ��X�^�b�N�̃g�b�v���擾����
		 */
		KsVariable*							getStackTop() { return &m_variables[ m_pos ]; }

		/**
		 * �ϐ��X�^�b�N�̃g�b�v�̃^�C�v���擾����
		 */
		ksVALUE_TYPE						getVariableTypeTop() const { return m_variables[ m_pos ].getType(); }

		/**
		 * �w��ϐ��X�^�b�N�̃g�b�v�̃^�C�v���擾����
		 */
		ksVALUE_TYPE						getVariableType( KsInt32 index ) const { return m_variables[ m_pos - index ].getType(); }

		/**
		 * �ϐ��X�^�b�N�̃g�b�v���擾����
		 */
		KsVariable*							getVariableTop() { return &m_variables[ m_pos ]; }

		/**
		 * �w��ϐ��X�^�b�N���擾����
		 */
		KsVariable*							getVariable( KsInt32 index ) { return &m_variables[ m_pos - index ]; }

		/** 
		 * �|�b�v����
		 */
		void								pop() { --m_pos; }

		/**
		 * �������v�b�V������
		 * @param	value					�����l
		 */
		void								pushInt( KsInt32 value ) { m_variables[ m_pos++ ].setInt( value ); }

		/**
		 * �����������v�b�V������
		 * @param	value					�����l
		 */
		void								pushFloat( KsReal value ) { m_variables[ m_pos++ ].setFloat( value ); }


		/**
		 * �X�N���v�g�G���W���̏���������
		 * @param	variableStackSize		�ϐ��̃X�^�b�N�̃T�C�Y
		 * @param	structMemberBlockSize	�n���h�����X�g�u���b�N�̃T�C�Y
		 * @param	handleListBlockSize		�\���̃����o�[�u���b�N�̃T�C�Y
		 * @retval	ksTRUE					����
		 * @retval	ksFALSE					���s
		 */
		KsBool								initialize(	KsUInt32 variableStackSize     = ksVARIABLE_STACK_SIZE,
														KsUInt32 structMemberBlockSize = ksHANDLE_LIST_BLOCK_SIZE,
														KsUInt32 handleListBlockSize   = ksSTRUCT_MEMBER_BLOCK_SIZE );

		/**
		 * �V���b�g�_�E������
		 * @retval	ksTRUE					����
		 * @retval	ksFALSE					���s
		 */
		KsBool								shutdown();

		/**
		 * �X�N���v�g�t�B���̓ǂݍ��ݏ���
		 * �Ǘ����邽�߂̖��O���K�v(?�X�N���v�g�ɓ����Ă閼�O���g���H)
		 * @param	pFile					�ǂݍ��ރt�@�C���I�u�W�F�N�g
		 */
		KsInt32								loadScriptFile( KsFileObject* pFile );

		/**
		 * �A�����[�h����
		 * @param	id						�A�����[�h����X�N���v�g��ID
		 */
		KsBool								unloadScript( KsInt32 id );

		/**
		 * �X�N���v�g�֐��̌Ăяo��
		 * @param	pFuncName				�Ăяo���֐���
		 * @param	pArgs					�����t�H�[�}�b�g
		 * @param	...						�ψ���
		 * @return							�Ԃ�l
		 */
		KsVariable*							callFunc( const KsChar* pFuncName, KsChar* pArgs, ... );

		/**
		 * �X�N���v�g�֐��̌Ăяo��
		 * @param	pFuncName				�Ăяo���֐���
		 */
		KsVariable*							callFunc( const KsChar* pFuncName );

		/**
		 * ���C�u�������Z�b�g����(�������C�u����)
		 * ���C�u�����𑝂₷�ƌ����Ɏ��Ԃ�������悤�ɂȂ�̂łȂ�ׂ��g�p���郉�C�u���������������N����悤�ɂ���
		 * @param	pLibInfo				�X�N���v�g���C�u�������
		 */
		KsBool								loadLib( const KsScriptLibInfo* pLibInfo );

		/**
		 * ���C�u�������J������
		 * @param	pLibInfo				�X�N���v�g���C�u�������
		 */
		KsBool								unloadLib( const KsScriptLibInfo* pLibInfo );
};


#endif /* __KSSVIRTUALMACHINE_H__ */



