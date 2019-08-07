/************************************************************************************************/
/** 
 * @file		KsOVRType.h
 * @brief		OVR�^�C�v
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSOVRTYPE_H__
#define __KSOVRTYPE_H__

/*==============================================================================================*/
/*                                  << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @enum		ksSTEREO_MODE
 * @brief		�X�e���I ���[�h
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
enum ksSTEREO_MODE
{
	ksSTEREO_NONE                 = 0,
	ksSTEREO_LEFT_RIGHT_MULTIPASS = 1
};

/************************************************************************************************/
/**
 * @enum		ksCAMERA_EYE_TYPE
 * @brief		�X�e���I �J���� �^�C�v
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
enum ksSTEREO_EYE_TYPE
{
	ksSTEREO_EYE_CENTER,
	ksSTEREO_EYE_LEFT,
	ksSTEREO_EYE_RIGHT
};


#endif /* __KSOVRTYPE_H__ */
