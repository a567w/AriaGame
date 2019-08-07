/************************************************************************************************/
/** 
 * @file		KsScriptSystemLib.cpp
 * @brief		�X�N���v�g�p�̃V�X�e�����C�u����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsScript/KsScriptPreCompile.h"
#include "KsScriptSystemLib.h"
#include "KsVirtualMachine.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �w��o�[�`�����}�V���ւ̃R���\�[���o��
 * @param	pVirtualMachine		�o�[�`�����}�V���̃|�C���^
 * @return	ksSCRIPT_OK			����
 *			ksSCRIPT_ERROR		�G���[
 */
/************************************************************************************************/
static KsInt32 ksCDECL KsScriptPrint( KsVirtualMachine* pVirtualMachine )
{
	if( pVirtualMachine->getVariableTypeTop() == ksVALUE_INT )
	{
		KsInt32		value_i = pVirtualMachine->getVariableTop()->m_value.i;
		return ksSCRIPT_OK;
	}
	else if( pVirtualMachine->getVariableTypeTop() == ksVALUE_FLOAT )
	{
		KsReal		value_f = pVirtualMachine->getVariableTop()->m_value.f;
		return ksSCRIPT_OK;
	}

	return ksSCRIPT_ERROR;
}

/************************************************************************************************/
/*
 * �V�X�e���p�̊֐��|�C���^�̃e�[�u��
 */
/************************************************************************************************/
static KsScriptLibInfo	s_systemScript[] = 
{
	{ "print",		KsScriptPrint		},
	{ "end",		NULL				},
};

/************************************************************************************************/
/*
 * �X�N���v�g�p�̃V�X�e�����C�u���������[�h����
 * @param	pVirtualMachine		���̃��C�u���������[�h����o�[�`�����}�V���̃|�C���^
 * @retval	ksTRUE				���[�h����
 * @retval	ksFALSE				���[�h���s
 */
/************************************************************************************************/
KsBool KsScriptLoadSystemLib( KsVirtualMachine* pVirtualMachine )
{
	return pVirtualMachine->loadLib( s_systemScript );
}

/************************************************************************************************/
/*
 * �X�N���v�g�p�̃V�X�e�����C�u�������A�����[�h����
 * @param	pVirtualMachine		���̃��C�u�������A�����[�h����o�[�`�����}�V���̃|�C���^
 * @retval	ksTRUE				�A�����[�h����
 * @retval	ksFALSE				�A�����[�h���s
 */
/************************************************************************************************/
KsBool KsScriptUnloadSystemLib( KsVirtualMachine* pVirtualMachine )
{
	if( !pVirtualMachine )
	{
		return ksFALSE;
	}

	return pVirtualMachine->unloadLib( s_systemScript );
}






