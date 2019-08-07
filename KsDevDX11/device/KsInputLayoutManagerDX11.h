/************************************************************************************************/
/** 
 * @file		KsInputLayoutManagerDX11.h
 * @brief		���̓��C�A�E�g�}�l�[�W��(DirectX11)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSINPUTLAYOUTMANAGERDX11_H__
#define __KSINPUTLAYOUTMANAGERDX11_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsRenderSystemDX11;

/************************************************************************************************/
/**
 * @class		KsInputLayoutManagerDX11
 * @brief		���̓��C�A�E�g�}�l�[�W��(DirectX11)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsInputLayoutManagerDX11 : public KsInputLayoutManager
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsInputLayoutManagerDX11( KsRenderSystemDX11* pRenderSystem );

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsInputLayoutManagerDX11();

		/**
		 * �C���v�b�g���C�A�E�g�𐶐�����
		 * @param		numIndex			�C���f�b�N�X��
		 * @param		flags				�t���O
		 * @return							�C���v�b�g���C�A�E�g�̃|�C���^
		 */
		virtual KsInputLayout*				createInputLayout( const KS_INPUT_ELEMENT_DESC* pInputElementDescs, KsUInt32 numElements, const KsVertexShader* pVertexShader );

	protected:
		 KsRenderSystemDX11*				m_pRenderSystem;
};

#endif		/* __KSINPUTLAYOUTMANAGERDX11_H__ */



