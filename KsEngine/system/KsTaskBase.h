/************************************************************************************************/
/** 
 * @file		KsTaskBase.h
 * @brief		��{�^�X�N
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSTASK_H__
#define __KSTASK_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsCore.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsTaskBase;
class KsOT_List;
class KsOT;

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define ksTASK_NAME_LENGTH			( 16 )			/**< �^�X�N�̖��O�̍ő咷( 15���� + '\0' )	*/
#define ksTASK_ORDER_DEFAULT		(  4 )			/**< �f�t�H���g�̃^�X�N�I�[�_�[				*/

/************************************************************************************************/
/**
 * �^�X�N�̐���t���O
 */
/************************************************************************************************/
#define ksTASK_FLAGS_NONE			( 0 )			/**< ��										*/
#define ksTASK_FLAGS_DELETE		( 1<< 1 )		/**< �폜�t���O								*/
#define ksTASK_FLAGS_DELETE_FORCE	( 1<< 2 )		/**< �����폜�t���O							*/
#define ksTASK_FLAGS_SLEEP_EXEC	( 1<< 3 )		/**< �^�X�N���s�������X���[�v��Ԃɂ���		*/
#define ksTASK_FLAGS_SLEEP_REND	( 1<< 4 )		/**< �^�X�N�`�揈�����X���[�v��Ԃɂ���		*/
#define ksTASK_FLAGS_WAIT_EXEC		( 1<< 5 )		/**< �E�G�C�g�^�C�}�[���͎��s�����Ȃ�		*/
#define ksTASK_FLAGS_WAIT_REND		( 1<< 6 )		/**< �E�G�C�g�^�C�}�[���͕`�悳���Ȃ�		*/
#define ksTASK_FALGS_RENDER_HIDE	( 1<< 9 )		/**< �`�悵�Ȃ��t���O						*/
#define ksTASK_FALGS_INITIALIZE	( 1<<10 )		/**< �������������ǂ����̃t���O				*/
#define ksTASK_FLAGS_PAUSE_CHILD	( 1<<28 )		/**< �q���̃^�X�N�����e��					*/
#define ksTASK_FLAGS_PAUSE_MY		( 1<<29 )		/**< �����̃^�X�N�����e��					*/
#define ksTASK_FLAGS_LINK_UPDATE	( 1<<30 )		/**< �`�惊���N�̍X�V����					*/
#define ksTASK_FLAGS_USE_WORKAREA	( 1<<31 )		/**< ���[�N�G���A���g�p����					*/

// �J���������́A�t���O�������Ă����ق�����������
//#define ksTASK_FLAGS_CAMERA
// ���������X�g�b�vexec
// �����ȉ��X�g�b�vexec
// �`�悵�Ȃ��t���O���Z�b�g
// ���������X�g�b�vrender
// �����ȉ��X�g�b�vrender

#define ksTASK_FLAGS_SLEEP			( ksTASK_FLAGS_SLEEP_EXEC | ksTASK_FLAGS_SLEEP_REND )
#define ksTASK_FLAGS_WAIT			( ksTASK_FLAGS_WAIT_EXEC | ksTASK_FLAGS_WAIT_REND )
#define ksTASK_FLAGS_PAUSE			( ksTASK_FLAGS_PAUSE_CHILD | ksTASK_FLAGS_PAUSE_MY )

#define ksTASK_RENDER_ORDER_NONE	( 0 )
#define ksTASK_RENDER_ORDER_ALL	( 0xffffffff )

/************************************************************************************************/
/**
 * @enum	�^�X�N�̃^�C�v
 */
/************************************************************************************************/
enum ksTASK_TYPE
{
	ksTASK_TYPE_BASE    = 0,				/**< ��{�^�X�N				*/
	ksTASK_TYPE_SCENE   = 1,				/**< �V�[���^�X�N			*/
	ksTASK_TYPE_SPRITE  = 2,				/**< �X�v���C�g�^�X�N		*/
	ksTASK_TYPE_SHADOW  = 3,				/**< �e�p�^�X�N				*/
	ksTASK_TYPE_MANAGER = 4,				/**< ����^�X�N				*/
	ksTASK_TYPE_DEBUG   = 16,				/**< �f�o�b�N�p�^�X�N		*/
	ksTASK_TYPE_CAMERA  = 0xffff,
};

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

typedef void* (*KsTaskCallback)( KsTaskBase* pTask, void* pParam );

/************************************************************************************************/
/** 
 * �^�X�N�̗D�揇��( �`��Ń\�[�g����ꍇ�ɕK�v )
 *		-i : 32bit�����Ő����l�Ń\�[�g�p
 *		-z : ���������_��Z�\�[�g�p
 */
/************************************************************************************************/
typedef union _KsTaskPRIORITY
{
	KsInt32		i;					/**< �D�揇��		*/
	KsReal		z;					/**< Z�\�[�g�l		*/
}KsTaskPRIORITY;

/************************************************************************************************/
/**
 * ��{�^�X�N�N���X
 * @class		KsTaskBase
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
class ksENGINE_API KsTaskBase
{
		friend class KsOT_List;
		friend class KsOT;
		friend class KsTaskManager;
	
	public:
		/**
		 * �R���X�g���N�^
		 * @brief	0�ŏ����������
		 */
											KsTaskBase();

		/**
		 * �R���X�g���N�^
		 * @param	order					�`��I�[�_�[
		 */
											KsTaskBase( KsUInt32 order );

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsTaskBase();

		/**
		 * �Z��^�X�N��ǉ�����
		 * @param		pTask				�ǉ�����Z��^�X�N�̃|�C���^
		 * @param		pUserData			���[�U�[�f�[�^
		 * @note		���[�U�[�f�[�^��NULL�̂Ƃ��́A�}�l�[�W���̎��s�����̂Ƃ���,
		 *				�}�l�[�W���ɓn���ꂽ���[�U�[�f�[�^�����[�U�[�f�[�^�ɓn����ď����������B
		 *				�������A���̏ꍇ�AaddChild�����Ƃ��ɂ́A���������Ă΂�Ȃ��B���̂��߁A
		 *				���[�U�[�f�[�^��NULL�ȊO������Ƃ��̃��[�U�[�f�[�^���g�p����addChild�����Ƃ���
		 *				�ǉ����ꂽ�^�X�N�̏������������Ă΂��B
		 */
		void								addBrother( KsTaskBase* pTask, void* pUserData=NULL );

		/**
		 * �q�^�X�N��ǉ�����
		 * @param		pTask				�ǉ�����q�^�X�N�̃|�C���^
		 * @param		pUserData			���[�U�[�f�[�^
		 * @note		���[�U�[�f�[�^��NULL�̂Ƃ��́A�}�l�[�W���̎��s�����̂Ƃ���,
		 *				�}�l�[�W���ɓn���ꂽ���[�U�[�f�[�^�����[�U�[�f�[�^�ɓn����ď����������B
		 *				�������A���̏ꍇ�AaddChild�����Ƃ��ɂ́A���������Ă΂�Ȃ��B���̂��߁A
		 *				���[�U�[�f�[�^��NULL�ȊO������Ƃ��̃��[�U�[�f�[�^���g�p����addChild�����Ƃ���
		 *				�ǉ����ꂽ�^�X�N�̏������������Ă΂��B
		 */
		void								addChild( KsTaskBase* pTask, void* pUserData=NULL );

		/**
		 * �����̃^�X�N���Ƃ�͂���(�K�w�́A�����ɂ����܂�)
		 */
		void								detach();

		/**
		 * ���S�ɐ؂藣��detach���K�v
		 * @param		pTask				��菜���q�^�X�N�̃|�C���^
		 * ���S�ɐ؂藣�����1�̃^�X�N�ɂȂ�
		 */
		KsTaskBase*								cut();

		/**
		 * ������艺�̊K�w����^�X�N���폜����(�폜�t���O���A����)
		 */
		void								remove();

		/**
		 * ������艺�̊K�w����^�X�N���폜����(�폜�t���O���A����)
		 */
		void								destroy();

		/**
		 * ��������kill�֐� (�}�l�[�W������O��Ă���Ƃ������g�p�\�ɂ���H)
		 */
		//void								kill();

		/**
		 * ID(����������艺�̊K�w�����v����^�X�N����������)
		 * @param		id					��������ID
		 */
		KsTaskBase*								find( KsUInt32 id );

		/**
		 * ���O����(����������艺�̊K�w�����v����^�X�N����������)
		 *
		 */
		KsTaskBase*								find( const KsChar* name );

		/**
		 * �`�惊���N��ύX����(������g�p����ɂ́A�}�l�[�W���ɓo�^����Ă���K�v������܂��B)
		 * @param		order				�V�����I�[�_�[
		 */
		void								changeRenderLink( KsUInt32 order );

		/**
		 * �`�惊���N������O��
		 * @param		pTask				�`�惊���N����͂����^�X�N�̃|�C���^
		 */
		void								removeRenderLink( KsTaskBase* pTask=NULL );

		/**
		 * �^�X�N�����Z�b�g����
		 * @param		string				�^�X�N��
		 */
		void								setName( const KsChar* string );

		/**
		 * �^�X�N�̎���ID���Z�b�g����(��{�I�ɂ͂��Ԃ�Ȃ��悤�ɂ���)
		 * @param		id					�^�X�N��ID
		 */
		void								setID( KsUInt32 id );

		/**
		 * �^�X�N�̐���t���O���Z�b�g����
		 * @param		flags				�^�X�N�̐���t���O
		 */
		void								setFlags( KsUInt32 flags );

		/**
		 * �D�揇�ʂ��Z�b�g����
		 * @param		priotiry			�v���C�I���e�B
		 */
		void								setPriority( KsInt32 priority );

		/**
		 * �I�[�_���Z�b�g
		 * @param		order				�w��I�[�_�[
		 */
		void								setOrder( KsUInt32 order );

		/**
		 * Z�l���Z�b�g����
		 * @param		z					z�l
		 */
		void								setZsort( KsReal z );

		/**
		 * �^�X�N�����擾����
		 * @return		�^�X�N���̕�����( �Œ�15���� + '\0' )
		 */
		const KsChar*						getName();

		/**
		 * �^�X�N�̎���ID���擾����
		 * @return		�^�X�N��ID���擾����
		 */
		KsUInt32							getID() const;

		/**
		 * �^�X�N�̐���t���O���擾����
		 * @return		�^�X�N�̐���t���O
		 */
		KsUInt32							getFlags() const;

		/**
		 * �^�X�N�̃^�C�v���擾����
		 */
		ksTASK_TYPE							getType() const;

		/**
		 * �D�揇�ʂ��Z�b�g����
		 * @return							�v���C�I���e�B
		 */
		KsTaskPRIORITY						getPriority() const;

		/**
		 * �I�_�[���擾����
		 */
		KsUInt32							getOrder() const;

		/**
		 * �e�^�X�N���擾����
		 * @return		�e�^�X�N�̃|�C���^
		 */
		KsTaskBase*								getParent();

		/**
		 * ���j�^�X�N���擾����
		 */
		KsTaskBase*								getTopBrother();

		/**
		 * �Ō���^�X�N���擾����
		 */
		KsTaskBase*								getEndBrother();

		/**
		 * �Z�^�X�N���擾����
		 */
		KsTaskBase*								getPrevBrother();

		/**
		 * ��^�X�N���擾����
		 */
		KsTaskBase*								getNextBrother();

		/**
		 * �Z��^�X�N���擾����
		 * @param		index				�q�^�X�N�̃C���f�b�N�X
		 * @return		�q�^�X�N�̃|�C���^
		 */
		KsTaskBase*								getBrother( KsUInt32 index );

		/**
		 * �q�^�X�N�̐����擾����
		 * @return		�q�^�X�N�̐�
		 */
		KsUInt32							getNumBrother() const;

		/**
		 * �q�^�X�N���擾����
		 * @param		index				�q�^�X�N�̃C���f�b�N�X
		 * @return		�q�^�X�N�̃|�C���^
		 */
		KsTaskBase*								getChild( KsUInt32 index );

		/**
		 * �q�^�X�N�̐����擾����
		 * @return		�q�^�X�N�̐�
		 */
		KsUInt32							getNumChild() const;

		/**
		 * �R�[���o�b�N�֐�
		 */
		KsTaskBase*								allChildCallback( KsTaskBase* pTask, KsTaskCallback callback, void* pUserData );

	protected:
		/**
		 * ����������(�}�l�[�W���ɓo�^���ꂽ�Ƃ��ɓo�^)
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						initialize( void* pParam ) = 0;

		/**
		 * �^�X�N�̎��s
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						execute( void* pParam ) = 0;

		/**
		 * �`�揈��
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						render( void* pParam ) = 0;

		/**
		 * �㏈���֐��Ń������[����폜�����Ƃ��ɌĂ΂��
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						terminate( void* pParam ) = 0;

	protected:
		KsChar								m_name[ ksTASK_NAME_LENGTH ];		/**< �^�X�N���̍ő咷					*/
		KsUInt32							m_id;								/**< �^�X�N����ID(�����I�Ɋ���U��?)	*/
		KsUInt32							m_flags;							/**< �^�X�N�̊e��t���O					*/
		KsUInt32							m_order;							/**< �`��I�[�_�[						*/
		ksTASK_TYPE							m_type;								/**< �^�X�N�̃^�C�v(���)				*/
		KsTaskPRIORITY						m_priority;							/**< �D�揇��							*/
		KsReal								m_waitTimer;						/**< �E�G�C�g�^�C�}�[					*/
		KsTaskBase*								m_pParent;							/**< �e�^�X�N�̃|�C���^					*/
		KsTaskBase*								m_pPrevBrother;						/**< �Z��^�X�N�̃|�C���^(�Z)			*/
		KsTaskBase*								m_pNextBrother;						/**< �Z��^�X�N�̃|�C���^(��)			*/
		KsTaskBase*								m_pChild;							/**< �q�^�X�N�̃|�C���^					*/
		KsTaskBase*								m_pPrev;							/**< �`�惊���N�O						*/
		KsTaskBase*								m_pNext;							/**< �`�惊���N��						*/
		KsTaskManager*						m_pManager;							/**< �o�^����Ă���}�l�[�W���̃|�C���^	*/
};

#endif /* __ksTASK_H__ */

