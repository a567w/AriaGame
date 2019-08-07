/************************************************************************************************/
/** 
 * @file		KsMemoryFixedUnit.h
 * @brief		�Œ胁�����Ǘ��i�t���[���X�g�j
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMEMORYFIXEDUNIT_H__
#define __KSMEMORYFIXEDUNIT_H__

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
 * @class		KsMemoryFixedUnit
 * @brief		�Œ胁�����[�}�l�[�W��
 * @since		2005/03/04
 * @author		Tsukasa Kato
 */
/************************************************************************************************/
class ksENGINE_API KsMemoryFixedUnit
{
	public:
		KsMemoryFixedUnit*				m_pPrev;		/**< �O�̃u���b�N�̃|�C���^		*/
		KsMemoryFixedUnit*				m_pNext;		/**< ���̃u���b�N�̃|�C���^		*/
		void*							m_pCurrentAddr;	/**< ���݂̃A�h���X				*/
		void*							m_pStartAddr;	/**< �ŏ��̃A�h���X				*/
		void*							m_pEndAddr;		/**< �I���A�h���X				*/
		KsUInt8							m_dummy[ 44 ];	/**< 64�o�C�g�ɂ��邽�߂̃_�~�[	*/
};


#endif		/* __KSMEMORYFIXEDUNIT_H__ */
