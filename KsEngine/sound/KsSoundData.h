/************************************************************************************************/
/** 
 * @file		KsSoundData.h
 * @brief		�T�E���h�f�[�^
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSOUNDDATA_H__
#define __KSSOUNDDATA_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                          */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
typedef WORD  ksSOUNDINDEX;            // All normal indices
typedef BYTE  ksSOUNDNOTIFICATIONTYPE; // Notification type
typedef FLOAT ksSOUNDVARIABLEVALUE;    // Variable value
typedef WORD  ksSOUNDVARIABLEINDEX;    // Variable index
typedef WORD  ksSOUNDCATEGORY;         // Sound category
typedef BYTE  ksSOUNDCHANNEL;          // Audio channel
typedef FLOAT ksSOUNDVOLUME;           // Volume value
typedef LONG  ksSOUNDTIME;             // Time (in ms)
typedef SHORT ksSOUNDPITCH;            // Pitch value
typedef BYTE  ksSOUNDLOOPCOUNT;        // For all loops / recurrences
typedef BYTE  ksSOUNDVARIATIONWEIGHT;  // Variation weight
typedef BYTE  ksSOUNDPRIORITY;         // Sound priority
typedef BYTE  ksSOUNDINSTANCELIMIT;    // Instance limitations

/************************************************************************************************/
/**
 * �T�E���h�X�e�[�^�X
 */
/************************************************************************************************/
enum ksSOUND_STATE
{
	ksSOUND_STATE_CREATED           = 0x00000001, /**<  Created, but nothing else			*/
	ksSOUND_STATE_PREPARING         = 0x00000002, /**<  In the middle of preparing			*/
	ksSOUND_STATE_PREPARED          = 0x00000004, /**<  Prepared, but not yet played		*/
	ksSOUND_STATE_PLAYING           = 0x00000008, /**<  Playing (though could be paused)	*/
	ksSOUND_STATE_STOPPING          = 0x00000010, /**<  Stopping							*/
	ksSOUND_STATE_STOPPED           = 0x00000020, /**<  Stopped								*/
	ksSOUND_STATE_PAUSED            = 0x00000040, /**<  Paused 								*/
	ksSOUND_STATE_INUSE             = 0x00000080, /**<  Object is in use 					*/
	ksSOUND_STATE_PREPAREFAILED     = 0x80000000, /**<  Object preparation failed.			*/
};


/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
enum ksSOUND_DATA_TYPE
{
	ksSOUND_DATA_UNKNOWN,
	ksSOUND_DATA_MEMORY,
	ksSOUND_DATA_STREAMING,
};

/************************************************************************************************/
/**
 * @class		KsSoundData
 * @brief		�T�E���h�f�[�^
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsSoundData
{
	public:
		/**
		 * �R���X�g���N�^
		 */
								KsSoundData();

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsSoundData();

		/**
		 * �X�e�[�^�X�擾
		 * @return				�T�E���h�X�e�[�^�X
		 */
		virtual ksSOUND_STATE	getState() = 0;

		/**
		 * �Đ�
		 */
		virtual KsBool			play() = 0;

		/**
		 * �X�g�b�v
		 */
		virtual KsBool			stop() = 0;

		/**
		 * �|�[�Y
		 * @param				�|�[�Y�t���O
		 */
		virtual KsBool			pause( KsBool bPause ) = 0;

		/**
		 * �{�����[��
		 * @param	fVolume		�{�����[�� [ 0.0�`1.0 ]
		 */
		virtual KsBool			setVolume( KsReal fVolume ) = 0;

		/**
		 * ���[�v�񐔂��Z�b�g����
		 * @param	loopCount	���[�v��
		 */
		virtual void			setLoopCount( KsByte loopCount ) = 0;
};

#endif		/* __KSSOUNDDATA_H__ */

