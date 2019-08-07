/************************************************************************************************/
/** 
 * @file		KsPhysicsType.h
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSPHYSICSTYPE_H__
#define __KSPHYSICSTYPE_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksACTIVE_TAG			1
#define ksISLAND_SLEEPING		2
#define ksWANTS_DEACTIVATION	3
#define ksDISABLE_DEACTIVATION	4
#define ksDISABLE_SIMULATION	5

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @enum		ksSHAPE_TYPE
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
typedef enum _ksSHAPE_TYPE
{
	ksSHAPE_SPHERE,
	ksSHAPE_BOX,
	ksSHAPE_CAPSULE

}ksSHAPE_TYPE;

/************************************************************************************************/
/**
 * @enum		ksCONSTRAINT_TYPE
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
typedef enum _ksCONSTRAINT_TYPE
{
	ksCONSTRAINT_SPRING

}ksCONSTRAINT_TYPE;


typedef enum _ksMOTION_STATE_TYPE
{
	ksMOTION_STATE_DEFAULT,
	ksMOTION_STATE_KINEMATIC

}ksMOTION_STATE_TYPE;

typedef enum _ksCOLLISION_FLAGS
{
	ksCF_STATIC_OBJECT= 1,
	ksCF_KINEMATIC_OBJECT= 2,
	ksCF_NO_CONTACT_RESPONSE = 4,
	ksCF_CUSTOM_MATERIAL_CALLBACK = 8,//this allows per-triangle material (friction/restitution)
	ksCF_CHARACTER_OBJECT = 16

}ksCOLLISION_FLAGS;

typedef enum _ksCOLLISION_OBJECT_TYPES
{
	ksCO_COLLISION_OBJECT =1,
	ksCO_RIGID_BODY,
	///CO_GHOST_OBJECT keeps track of all objects overlapping its AABB and that pass its collision filter
	///It is useful for collision sensors, explosion objects, character controller etc.
	ksCO_GHOST_OBJECT,
	ksCO_SOFT_BODY,
	ksCO_HF_FLUID

}ksCOLLISION_OBJECT_TYPES;

#endif		/* __KSPHYSICSTYPE_H__ */

