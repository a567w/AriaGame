/************************************************************************************************/
/** 
 * @file		KsMacroDX11.h
 * @brief		DirectX11用エンジン,コアヘッダー
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSMACRODX11_H__
#define __KSMACRODX11_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

inline void ksERROR_DX11( KsUInt32 hr )
{
	switch( hr )
	{
		case D3D11_ERROR_FILE_NOT_FOUND:
			KsPrintf( _T("ファイルが見つかりませんでした。") );
			break;
		case D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS:
			KsPrintf( _T("特定の種類のステート オブジェクトの一意のインスタンスが多すぎます。") );
			break;
		case D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS:
			KsPrintf( _T("特定の種類のビュー オブジェクトの一意のインスタンスが多すぎます。") );
			break;
		case D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD:
			KsPrintf( _T("リソースごとの ID3D11Device::CreateDeferredContext の呼び出しまたは ID3D11DeviceContext::FinishCommandList の呼び出しの後で最初に呼び出した ID3D11DeviceContext::Map が D3D11_MAP_WRITE_DISCARD ではありませんでした。") );
			break;
		case E_FAIL:
			KsPrintf( _T("デバッグ レイヤーを有効にしてデバイスを作成しようとしましたが、該当するレイヤーがインストールされていません。") );
			break;
		case E_INVALIDARG:
			KsPrintf( _T("戻り関数に無効なパラメーターが渡されました。") );
			break;
		case E_OUTOFMEMORY:
			KsPrintf( _T("Direct3D が呼び出しを完了するうえで十分なメモリーを割り当てることができませんでした。") );
			break;
		default:
			KsPrintf( _T("DirectX Error 0x%x08"), hr );
			break;
	}
}

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

#endif /* __KSMACRODX11_H__ */



