/************************************************************************************************/
/** 
 * @file		KsMemoryFixedBlock.h
 * @brief		�Œ胁�����Ǘ��i�t���[���X�g�j
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMEMORYFIXEDBLOCK_H__
#define __KSMEMORYFIXEDBLOCK_H__

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
 * @class		KsMemoryFixedBlock
 * @brief		�Œ胁�����[�}�l�[�W��(4�o�C�g�ȏ�łȂ��ƃ_��)
 * @since		2005/03/04
 * @author		Tsukasa Kato
 */
/************************************************************************************************/
class ksENGINE_API KsMemoryFixedBlock
{
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsMemoryFixedBlock();

		/**
		 * �R���X�g���N�^(�u���b�N���X�g�𐶐�����)
		 * @param		elementSize		�v�f�̃T�C�Y
		 * @param		numElement		�v�f��
		 * @param		numBlock		�u���b�N��
		 */
										KsMemoryFixedBlock( KsUInt32 elementSize, KsUInt32 numElement, KsUInt32 numBlock=0 );

		/**
		 * �f�X�g���N�^
		 */
										~KsMemoryFixedBlock();

		/**
		 * �u���b�N���X�g�𐶐�����
		 * @param		elementSize		�v�f�̃T�C�Y
		 * @param		numElement		�v�f��
		 * @param		numBlock		�u���b�N��
		 */
		void							create( KsUInt32 elementSize, KsUInt32 numElement, KsUInt32 numBlock=0 );

		/**
		 * �v�f�����N���A����
		 */
		void							clear();
	
		/**
		 * �j������
		 */
		void							destroy();
	
		/**
		 * �������[�u���b�N�𐶐�����
		 */
		void							createMemoryBlock();
	
		/**
		 * �������[���u���b�N����m�ۂ���
		 */
		void*							alloc();
	
		/**
		 * ���̃��X�g�Ŋm�ۂ��ꂽ�������[���̃`�F�b�N
		 * @retval		ksTRUE			����Ŋm�ۂ��ꂽ������
		 * @retval		ksFALSE			����ȊO�Ŋm�ۂ��ꂽ������
		 */
		KsBool							isBlockListMemory( void* ptr );

	public:
		KsMemoryFixedUnit*				m_pTopBlock;		/**< �擪�u���b�N�̃|�C���^	*/
		KsMemoryFixedUnit*				m_pCurrentBlock;	/**< ���݂̃u���b�N�̃|�C���^	*/
		KsUInt32						m_elementSize;		/**< �v�f�̃T�C�Y			*/
		KsUInt32						m_blockSize;		/**< �u���b�N�T�C�Y			*/
};

#endif		/* __KSMEMORYFIXEDBLOCK_H__ */

