/************************************************************************************************/
/** 
 * @file		KsAdapterListDX11.h
 * @brief		�A�_�v�^��񃊃X�g
 * @author		Tsukasa Kato
 * @date		2003/03/22
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSADAPTERLISTDX11_H__
#define __KSADAPTERLISTDX11_H__

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
 * �r�f�I�J�[�h��񃊃X�g�N���X
 * @class	KsAdapterListDX
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsAdapterListDX11 : public KsAdapterList
{
	public:
		typedef KsArray< KsAdapter* >		KsAdapterArray;

	private:
		KsAdapterArray						m_vpAdapterList;	/**< �A�_�v�^���X�g			*/
		KsRenderSystem*						m_pRenderSystem;	/**< �`��V�X�e���I�u�W�F�N�g	*/

	public:

		/**
		 * �R���X�g���N�^
		 * @param		pRenderSystem		KsRenderSystem�I�u�W�F�N�g
		 */
											KsAdapterListDX11( KsRenderSystem* pRenderSystem );

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsAdapterListDX11();

		/**
		 * ����������
		 * @param		pRenderSystem		KsRenderSystem�I�u�W�F�N�g
		 * @retval		ksTRUE				����
		 * @retval		ksFALSE				���s
		 */
		KsBool								initialize( KsRenderSystem* pRenderSystem );

	public:
		/**
		 * �A�_�v�^�����擾����
		 * @return							�A�_�v�^��
		 */
		virtual KsUInt32					getAdpterCount() const;

		/**
		 * �w�薼�C���f�b�N�X�̃A�_�v�^���擾����
		 * @param		index				�w��C���f�b�N�X
		 * @return							�A�_�v�^	
		 */
		virtual const KsAdapter*			getAdapter( KsInt32 index );

	protected:
		/**
		 * �A�_�v�^��񋓂���
		 * @return	yTrue					�񋓐���
		 */
		virtual KsBool						enumerateAdapter();
};


#endif		/* __KSADAPTERLISTDX11_H__ */

