/************************************************************************************************/
/** 
 * @file		KsInputLayoutManager.h
 * @brief		���̓��C�A�E�g�}�l�[�W��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSINPUTLAYOUTMANAGER_H__
#define __KSINPUTLAYOUTMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define	KS_APPEND_ALIGNED_ELEMENT	( 0xffffffff )

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsRenderContext;
class KsVertexShader;


/************************************************************************************************/
/**
 * @struct		KS_INPUT_CLASSIFICATION
 * @brief		���͗v�fDESC
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
typedef enum KS_INPUT_CLASSIFICATION
{
    KS_INPUT_PER_VERTEX_DATA   = 0,		// ���̓f�[�^�͒��_�P�ʂ̃f�[�^�ł��B
    KS_INPUT_PER_INSTANCE_DATA = 1,		// ���̓f�[�^�̓C���X�^���X�P�ʂ̃f�[�^�ł��B

} KS_INPUT_CLASSIFICATION;

/************************************************************************************************/
/**
 * @struct		KS_INPUT_ELEMENT_DESC
 * @brief		���͗v�fDESC
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
typedef struct KS_INPUT_ELEMENT_DESC
{
    const KsChar*				SemanticName;
    KsUInt32					SemanticIndex;
    KS_GI_FORMAT				Format;
    KsUInt32					InputSlot;
    KsUInt32					AlignedByteOffset;
    KS_INPUT_CLASSIFICATION		InputSlotClass;
    KsUInt32					InstanceDataStepRate;

} KS_INPUT_ELEMENT_DESC;


/************************************************************************************************/
/**
 * @class		KsInputLayoutManager
 * @brief		���̓��C�A�E�g�}�l�[�W��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsInputLayoutManager : public KsSingleton< KsInputLayoutManager >
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsInputLayoutManager();

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsInputLayoutManager();

		/**
		 * �C���v�b�g���C�A�E�g�𐶐�����
		 * @param		numIndex			�C���f�b�N�X��
		 * @param		flags				�t���O
		 * @return							�C���v�b�g���C�A�E�g�̃|�C���^
		 */
		virtual KsInputLayout*				createInputLayout( const KS_INPUT_ELEMENT_DESC* pInputElementDescs, KsUInt32 numElements, const KsVertexShader* pVertexShader ) = 0;

		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return							�V���O���g���̎Q��
		 */
		static KsInputLayoutManager&		getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return							�V���O���g���̃|�C���^
		 */
		static KsInputLayoutManager*		getInstancePtr();

};

#endif		/* __KSINPUTLAYOUTMANAGER_H__ */



