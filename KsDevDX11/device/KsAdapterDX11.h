/************************************************************************************************/
/** 
 * @file		KsAdapterDX.h
 * @brief		�A�_�v�^���<BR>
 * @author		Tsukasa Kato
 * @date		2003/03/22
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSADAPTERDX11_H__
#define __KSADAPTERDX11_H__

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
 * �r�f�I�J�[�h���N���X
 * @class	KsAdapterDX
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsAdapterDX11 : public KsAdapter
{
	protected:
		KsRenderSystem*						m_pRenderSystem;
		IDXGIAdapter*						m_pDXGIAdapter;			/**< �A�_�v�^�[DX11			*/
		KsArray<IDXGIOutput*>				m_vpOutputs;
		//KsVideoModeListDX*					m_pVideoModeList;		/**< �r�f�I���[�h���X�g		*/
		KsString							m_name;
		KsString							m_description;

	public:
		/**
		 * �R���X�g���N�^(�R�s�[)
		 * @param		refAdapter			�A�_�v�^
		 */
											KsAdapterDX11( IDXGIAdapter* pDXGIAdapter );

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsAdapterDX11();

		/**
		 * ����������
		 * @param		pDXGIAdapter		IDXGIAdapter�I�u�W�F�N�g
		 * @retval		ksTRUE				����
		 * @retval		ksFALSE				���s
		 */
		KsBool								initialize( IDXGIAdapter* pDXGIAdapter );

		/**
		 * �A�_�v�^�����擾����
		 * @return							�A�_�v�^��
		 */
		virtual const KsString&				getAdapterName();

		/**
		 * �A�_�v�^�ڍׂ��擾����
		 * @return							�A�_�v�^�ڍ�
		 */
		virtual const KsString&				getAdapterDescription();

		/**
		 * �A�_�v�^�i���o�[���擾����
		 * @return							�A�_�v�^�i���o		
		 */
		virtual const KsDisplayMode*		getDisplayMode( KsInt32 index );

		/**
		 * �A�_�v�^�i���o�[���擾����
		 * @return							�A�_�v�^�i���o		
		 */
		virtual const KsDisplayModeList*	getDisplayModeList();

	protected:

		/**
		 * �f�B�X�v���C���[�h��񋓂���
		 * @return	yTrue					�񋓐���
		 */
		virtual KsBool						enumerateDisplayMode();
};

#endif		/* __KSADAPTERDX11_H__ */

