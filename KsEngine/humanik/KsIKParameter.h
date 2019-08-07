/************************************************************************************************/
/** 
 * @file		KsHumanIK.h
 * @brief		�l�ԗpIK
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#ifndef __KSHUMANIK_H__
#define __KSHUMANIK_H__

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


#if 0
/************************************************************************************************/
/**
 * @class		KsIKParameter
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsIKParameter
{
	public:
		KsString				BoneName;			// IK�{�[���ԍ�
		KsString				TargetBoneName;		// IK�^�[�Q�b�g�{�[���ԍ�( IK�{�[�����ŏ��ɐڑ�����{�[�� )
		KsInt32					BoneIndex;			// IK�{�[���ԍ�
		KsInt32					TargetBoneIndex;	// IK�^�[�Q�b�g�{�[���ԍ�( IK�{�[�����ŏ��ɐڑ�����{�[�� )
		KsInt32					ChainLength;		// IK�`�F�[���̒���(�q�̐�)
		KsInt32					Iterations;			// �ċA���Z��( IK�l1 )
		KsReal					ControlWeight;		// IK�̉e���x( IK�l2 )
		KsArray<KsInt32>		ChildBoneIndices;	// IK�e�����̃{�[���ԍ�(ChainLength)
		KsArray<KsString>		ChildBoneNames;		// IK�e�����̃{�[���ԍ�(ChainLength)
};

#endif

#endif		/* __KSHUMANIK_H__ */
