/************************************************************************************************/
/** 
 * @file		KsMemoryFixed.h
 * @brief		�Œ胁�����Ǘ��i�t���[���X�g�j
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMEMORYFIXED_H__
#define __KSMEMORYFIXED_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsMemoryFixed
 * @brief		�Œ胁�����[�}�l�[�W��(4�o�C�g�ȏ�łȂ��ƃ_��)
 * @since		2005/03/04
 * @author		Tsukasa Kato
 */
/************************************************************************************************/
class ksENGINE_API KsMemoryFixed
{
	private:
		/**
		 * �t���[���X�g
		 */
		class KsFreeList
		{
			public:
				KsFreeList*				m_pNext;	/**< ���X�g�̃|�C���^		*/
		};

	public:
		/**
		 * �R���X�g���N�^
		 */
										KsMemoryFixed();

		/**
		 * �R���X�g���N�^
		 * @param		elementSize		�v�f�̃T�C�Y
		 * @param		numElement		�v�f��
		 * @param		numBlock		�u���b�N��
		 */
										KsMemoryFixed( KsUInt32 elementSize, KsUInt32 numElement, KsUInt32 numBlock=0 );

		/**
		 * �f�X�g���N�^
		 */
										~KsMemoryFixed();

		/**
		 * ��������
		 * @param		elementSize		�v�f�̃T�C�Y
		 * @param		numElement		�v�f��
		 * @param		numBlock		�u���b�N��
		 */
		void							create( KsUInt32 elementSize, KsUInt32 numElement, KsUInt32 numBlock );

		/**
		 * �N���A�[����
		 */
		void							clear();
	
		/**
		 * �j������
		 */
		void							destroy();

		/**
		 * �������[�m��
		 * @return						�m�ۂ����������[
		 */
		void*							KsAlloc();

		/**
		 * �������[�J�� 
		 * @param		ptr				�|�C���^
		 */
		void							KsFree( void* ptr );

		/**
		 * ���̃��X�g�Ŋm�ۂ��ꂽ�������[���̃`�F�b�N
		 * @retval		ksTRUE			����Ŋm�ۂ��ꂽ������
		 * @retval		ksFALSE			����ȊO�Ŋm�ۂ��ꂽ������
		 */
		KsBool							isMemory( void* ptr );

	private:
		KsMemoryFixedBlock				m_memoryBlockList;		/**< �������[�u���b�N���X�g	*/
		KsFreeList*						m_pFreeList;			/**< �t���[���X�g�̐擪		*/
};


#endif		/* __KSMEMORYFIXED_H__ */

