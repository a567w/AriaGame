/************************************************************************************************/
/** 
 * @file		KsMacroDX11.h
 * @brief		DirectX11�p�G���W��,�R�A�w�b�_�[
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSMACRODX11_H__
#define __KSMACRODX11_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

inline void ksERROR_DX11( KsUInt32 hr )
{
	switch( hr )
	{
		case D3D11_ERROR_FILE_NOT_FOUND:
			KsPrintf( _T("�t�@�C����������܂���ł����B") );
			break;
		case D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS:
			KsPrintf( _T("����̎�ނ̃X�e�[�g �I�u�W�F�N�g�̈�ӂ̃C���X�^���X���������܂��B") );
			break;
		case D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS:
			KsPrintf( _T("����̎�ނ̃r���[ �I�u�W�F�N�g�̈�ӂ̃C���X�^���X���������܂��B") );
			break;
		case D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD:
			KsPrintf( _T("���\�[�X���Ƃ� ID3D11Device::CreateDeferredContext �̌Ăяo���܂��� ID3D11DeviceContext::FinishCommandList �̌Ăяo���̌�ōŏ��ɌĂяo���� ID3D11DeviceContext::Map �� D3D11_MAP_WRITE_DISCARD �ł͂���܂���ł����B") );
			break;
		case E_FAIL:
			KsPrintf( _T("�f�o�b�O ���C���[��L���ɂ��ăf�o�C�X���쐬���悤�Ƃ��܂������A�Y�����郌�C���[���C���X�g�[������Ă��܂���B") );
			break;
		case E_INVALIDARG:
			KsPrintf( _T("�߂�֐��ɖ����ȃp�����[�^�[���n����܂����B") );
			break;
		case E_OUTOFMEMORY:
			KsPrintf( _T("Direct3D ���Ăяo�����������邤���ŏ\���ȃ������[�����蓖�Ă邱�Ƃ��ł��܂���ł����B") );
			break;
		default:
			KsPrintf( _T("DirectX Error 0x%x08"), hr );
			break;
	}
}

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

#endif /* __KSMACRODX11_H__ */



