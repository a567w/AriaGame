/************************************************************************************************/
/** 
 * @file		KsAnimation.h
 * @brief		�{�[��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSANIMLOADER_H__
#define __KSANIMLOADER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsMeshLoader.h"
#include "KsAnimation.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsAnimation
 * @brief		�A�j���[�V����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
typedef struct _KS_KAM_FILE_HEADER
{
	KsUInt32				signature;			/**< ���ʗp						*/
	KsUInt32				version;			/**< �o�[�W�������				*/
	KsUInt32				type;				/**< �^�C�v						*/
	KsUInt32				flags;				/**< �e��t���O					*/
}KS_KAM_FILE_HEADER;

typedef struct _KS_KAM_INFO_HEADER
{
	KsInt32					start;
	KsInt32					end;
	KsInt32					fps;
	KsInt32					numTrack;
}KS_KAM_INFO_HEADER;

typedef struct _KS_KAM_TRACK
{
	KsInt32					target;
	KsInt32					maxTime;
	KsInt32					numFrame;
}KS_KAM_TRACK;

typedef struct _KS_KAM_KEY_FRAME
{
	KsInt32					time;				// �t���[��
	KS_KMD_VECTOR3D			translate;			// �ʒu
	KS_KMD_VECTOR4D			rotate;				// ��](�N�H�[�^�j�I��)
	KS_KMD_VECTOR3D			scale;				// �X�P�[��

}KS_KAM_KEY_FRAME;

extern KsAnimation* KsLoadAnim( const KsChar* pFileName );


#endif /* __KSANIMLOADER_H__ */

