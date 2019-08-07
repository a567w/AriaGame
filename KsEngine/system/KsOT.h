/************************************************************************************************/
/** 
 * @file		KsOT.h
 * @brief		�I�[�_�����O�e�[�u��
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSOT_H__
#define __KSOT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsType.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsTaskBase;

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define ksOT_ORDER_MAX			( 32 )					/**< �I�[�_�[�̍ő�l			*/
#define ksOT_ORDER_CAMERA		( ksOT_ORDER_MAX )		/**< �J�����̃I�[�_�[			*/
#define ksOT_SORT_TBL_MAX		( 1<<14 )				/**< �\�[�g�p�̃e�[�u���̍ő�l	*/

/************************************************************************************************/
/**
 * �I�[�_�����O�e�[�u������p�̃t���O
 */
/************************************************************************************************/
#define ksOT_FLAGS_PRIORITYSORT	( 1<<1 )										/**< �D�揇�ʂŃ\�[�g���邩�ǂ����̃t���O					*/
#define ksOT_FLAGS_ZSORT			( 1<<2 )										/**< Z�l�Ń\�[�g���邩�ǂ����̃t���O						*/
#define ksOT_FLAGS_STOP			( 1<<3 )										/**< �X�g�b�v������Ƃ��̃I�[�_�[�͓����Ȃ��̂ŕ`�悵�Ȃ�	*/
#define ksOT_FLAGS_SORT_USE		( ksOT_FLAGS_PRIORITYSORT | ksOT_FLAGS_ZSORT )	/**< �\�[�g���g�p���邩�ǂ����̃t���O						*/

/************************************************************************************************/
/**
 * @class		KsOT_List
 * @brief		��{�^�X�N�}�l�[�W���N���X
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
class ksENGINE_API KsOT_List
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsOT_List();

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsOT_List();
		
		/**
		 * �^�X�N�̃v���C�I���e�B�Ń\�[�g����
		 * @brief 		��{�I�Ƀ\�[�g���ĕ`�揇�Ԃ�ύX����̂ł��̃��X�g�ɂȂ����Ă���^�X�N��
		 *				���ׂăv���C�I���e�B���A������Ɛݒ肳��Ă��Ȃ���,�������\�[�g�ł��Ȃ��B
		 */
		void						sort();

		/**
		 * �^�X�N��Z�l�Ń\�[�g����(Z�\�[�g)
		 * @brief 		��{�I�Ƀ\�[�g���ĕ`�揇�Ԃ�ύX����̂ł��̃��X�g�ɂȂ����Ă���^�X�N��
		 *				���ׂ�Z�l���A������Ɛݒ肳��Ă��Ȃ���,�������\�[�g�ł��Ȃ��B
		 */
		void						zsort();

		/**
		 * �����N��ǉ�����
		 * @param		pTask		�ǉ��^�X�N
		 */
		void						add( KsTaskBase* pTask );

		/**
		 * �t���O���擾����
		 * @return					�t���O���擾����
		 */
		KsUInt32					getFlags() const { return m_flags; }

		/**
		 * �t���O���Z�b�g����
		 * @param		flags		�e��t���O
		 */
		void						setFlags( KsUInt32 flags ) { m_flags = flags; }

		/**
		 * ���X�g�����擾����
		 * @return					���X�g��
		 */
		KsUInt32					getCount() const { return m_count; }

		/**
		 * ���X�g�̐擪�̃|�C���^���擾����
		 * @return					���X�g�̐擪�|�C���^
		 */
		KsTaskBase*						getTop() { return m_pTop; }

		/**
		 * ���X�g�̍Ō���̃|�C���^���擾����
		 * @return					���X�g�̍Ō���|�C���^
		 */
		KsTaskBase*						getEnd() { return m_pEnd; }

		/**
		 * �m�[�}���`��
		 * @param		pParam		�p�����[�^
		 */
		void						normalRender( void* pParam );

		/**
		 * �\�[�g�`��
		 * @param		pParam		�p�����[�^
		 */
		void						sortRender( void* pParam );

		/**
		 * �N���A����
		 */
		void						clear();

		/**
		 * ���X�g������O������
		 * @param		pTask		���O���^�X�N�̃|�C���^
		 */
		void						remove( KsTaskBase* pTask );

	protected:
		KsUInt32					m_flags;						/**< �e��t���O				*/
		KsTaskBase*						m_pTop;							/**< ���X�g�̐擪			*/
		KsTaskBase*						m_pEnd;							/**< ���X�g�̍Ō�			*/
		KsUInt32					m_count;						/**< ���X�g�̐�				*/
		KsTaskBase*						m_sortTbl[ ksOT_SORT_TBL_MAX ];	/**< �\�[�g�p�̃��[�N�G���A	*/
};

/************************************************************************************************/
/**
 * �I�_�[�����O�e�[�u��
 * @class		KsOT
 * @brief		�I�_�[�����O�e�[�u��
 * @date		2004/10/17
 * @since		2004/10/17
 * @sa			KsOT_List (�֘A���ڂ��Q��)
 */
/************************************************************************************************/
class ksENGINE_API KsOT
{
		//friend class KsOT;
		friend class KsOT_List;
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsOT();
		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsOT();

		/**
		 * �^�X�N��o�^����
		 * @param		pTask		�o�^����^�X�N�̃|�C���^
		 * @retval		ksTRUE		����
		 * @retval		ksFALSE		���s
		 */
        KsBool						entry( KsTaskBase* pTask );

		/**
		 * ���O��
		 * @param		pTask		���O���^�X�N�̃|�C���^
		 */
		void						remove( KsTaskBase* pTask );

		/**
		 * �I�[�_�[�̍ő�l���擾����
		 * @return					�I�[�_�̍ő�l
		 */
		KsUInt32					getOrderMax() const { return ksOT_ORDER_MAX; }

		/**
		 * �t���O���擾����
		 * @return					�t���O���擾����
		 */
		KsUInt32					getFlags() const { return m_flags; }

		/**
		 * �t���O���Z�b�g����
		 * @param		flags		�e��t���O
		 */
		void						setFlags( KsUInt32 flags ) { m_flags = flags; }

		/**
		 * �I�[�_�[���擾����
		 * @param		index		�C���f�b�N�X
		 * @return					�I�[�_�[���X�g�̃|�C���^
		 */
		KsOT_List*					getOrder( KsUInt32 index ) { return &m_order[ index ]; }

		/**
		 * �`�揈��
		 * @param		pParam		�p�����[�^
		 */
		void						render( void* pParam );

		/**
		 * �N���A����
		 */
		void						clear();

	protected:
		/**
		 * �w��I�[�_�[��`��
		 * @param		order		�w��I�[�_�[
		 * @param		pParam		�p�����[�^
		 */
		void						orderRender( KsUInt32 order, void* pParam );

		/**
		 * �J���������N��`��
		 * @param		pParam		�p�����[�^
		 */
		void						cameraRender( void* pParam );

		/**
		 * �f�t�H���g�`��
		 * @param		pParam		�p�����[�^
		 */
		void						defaultRender( void* pParam );

	protected:
		KsUInt32					m_flags;						/**< �t���O								*/
		KsOT_List					m_order[ ksOT_ORDER_MAX+1 ];	/**< �I�[�_�[(+1�̓J���������N�̂���)	*/
};

#endif	/* __KSOT_H__ */

