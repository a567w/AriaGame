/************************************************************************************************/
/** 
 * @file		KsMeshPart.h
 * @brief		���b�V���p�[�c
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMESHPART_H__
#define __KSMESHPART_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsMeshPart
 * @brief		���b�V���p�[�c
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsMeshPart
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsMeshPart();

		/**
		 * �R���X�g���N�^( ���b�V���p�[�c�𐶐����܂��B)
		 * @param	pEffect			�g�p����G�t�F�N�g�f�[�^
		 * @param	pIndexBuffer	���b�V�������̃C���f�b�N�X �o�b�t�@�[
		 * @param	pVertexBuffer	���b�V�� �p�[�c�̒��_�o�b�t�@�[
		 * @param	pInputLayout	�C���v�b�g���C�A�E�g
		 * @param	numVertices		�`��Ăяo�����Ɏg�p����钸�_�̐�
		 * @param	primitiveCount	�����_�����O����v���~�e�B�u�̐�
		 * @param	startIndex		�C���f�b�N�X�z��̒��Œ��_�̓ǂݎ����J�n����ʒu
		 * @param	vertexOffset	���_�o�b�t�@�[�̍ŏ㕔����̃I�t�Z�b�g
		 */
									KsMeshPart( KsEffect*		pEffect,
												KsIndexBuffer*	pIndexBuffer,
												KsVertexBuffer*	pVertexBuffer,
												KsInputLayout*	pInputLayout,
												KsInt32	numVertices,
												KsInt32	primitiveCount,
												KsInt32	startIndex,
												KsInt32 vertexOffset );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsMeshPart();

		/**
		 * ���b�V���p�[�c�𐶐����܂��B
		 * @param	pEffect			�g�p����G�t�F�N�g�f�[�^
		 * @param	pIndexBuffer	���b�V�������̃C���f�b�N�X �o�b�t�@�[
		 * @param	pVertexBuffer	���b�V�� �p�[�c�̒��_�o�b�t�@�[
		 * @param	pInputLayout	�C���v�b�g���C�A�E�g
		 * @param	numVertices		�`��Ăяo�����Ɏg�p����钸�_�̐�
		 * @param	primitiveCount	�����_�����O����v���~�e�B�u�̐�
		 * @param	startIndex		�C���f�b�N�X�z��̒��Œ��_�̓ǂݎ����J�n����ʒu
		 * @param	vertexOffset	���_�o�b�t�@�[�̍ŏ㕔����̃I�t�Z�b�g
		 */
		void						create( KsEffect*		pEffect,
											KsIndexBuffer*	pIndexBuffer,
											KsVertexBuffer*	pVertexBuffer,
											KsInputLayout*	pInputLayout,
											KsInt32	numVertices,
											KsInt32	primitiveCount,
											KsInt32	startIndex,
											KsInt32 vertexOffset );

		/**
		 * �}�g���b�N�X�p���b�g�𐶐����܂��B
		 * @param	numPallet		�}�g���b�N�X�p���b�g��
		 * @param	pPallet			�}�g���b�N�X�p���b�g
		 */
		void						createPallet( KsInt32 numPallet, KsInt32* pPallet );

		/**
		 * ���b�V���p�[�c��j�����܂��B
		 */
		void						destroy();

		/** 
		 * �`�揈��
		 * @param	pRenderContext	�`��R���e�L�X�g
		 */
		void						draw( KsRenderContext* pRenderContext, KsModelParameter* pParameter=NULL );

		/**
		 * ���̃��b�V�������̃C���f�b�N�X �o�b�t�@�[���擾���܂��B
		 * @return	���b�V�������̃C���f�b�N�X �o�b�t�@�[	
		 */
		KsIndexBuffer*				getIndexBuffer() { return  m_pIndexBuffer; }

		/**
		 * ���̃��b�V�� �p�[�c�̒��_�o�b�t�@�[���擾���܂��B
		 * @return	���b�V�� �p�[�c�̒��_�o�b�t�@�[
		 */
		KsVertexBuffer*				getVertexBuffer() { return m_pVertexBuffer; }

		/**
		 * �`��Ăяo�����Ɏg�p����钸�_�̐����擾���܂��B
		 * @return	���_�̐�
		 */
		KsInt32						getNumVertices() const { return m_numVertices; }

		/**
		 * �����_�����O����v���~�e�B�u�̐����擾���܂��B
		 * @return	�v���~�e�B�u�̐�
		 */
		KsInt32						getPrimitiveCount() const { return m_primitiveCount; }

		/**
		 * �C���f�b�N�X�z��̒��Œ��_�̓ǂݎ����J�n����ʒu���擾���܂��B
		 * @return	�C���f�b�N�X�z��̒��Œ��_�̓ǂݎ����J�n����ʒu
		 */
		KsInt32						getStartIndex() const { return m_startIndex; }

		/**
		 * ���_�o�b�t�@�[�̍ŏ㕔����̃I�t�Z�b�g�� (���_���P�ʂ�) �擾���܂��B
		 * @return	���_�o�b�t�@�[�̍ŏ㕔����̃I�t�Z�b�g
		 */
		KsInt32						getVertexOffset() const { return m_vertexOffset; }

		/**
		 * �g�p�}�g���b�N�X�p���b�g
		 */
		KsInt32						getNumMatrixPallet() const { return m_numPallet; }

		/**
		 * �g�p�}�g���b�N�X�p���b�g
		 */
		KsInt32						getMatrixPallet( KsInt32 index ) { return m_pPallet[ index ]; }

		/**
		 * �G�t�F�N�gID���擾���܂��B
		 * @return	�G�t�F�N�g
		 */
		KsUInt32					getEffectID() const { return m_effectID; }

		/**
		 * �G�t�F�N�gID���Z�b�g���܂��B
		 * @return	�G�t�F�N�g
		 */
		void						setEffectID( KsUInt32 effectID ) { m_effectID = effectID; }

		/**
		 * �G�t�F�N�g���擾���܂��B
		 * @return	�G�t�F�N�g
		 */
		KsEffect*					getEffect() { return m_pEffect; }

		/**
		 * �G�t�F�N�g���Z�b�g���܂��B
		 * @param	pEffect			�G�t�F�N�g
		 */
		void						setEffect( KsEffect* pEffect ) { m_pEffect = pEffect; }

		/**
		 * �{�[���ƒǉ�����
		 * @param	pBone			�{�[��
		 */
		void						addBone( KsBone* pBone ) { m_vpBones.push_back( pBone ); }

		/**
		 * �{�[�������擾���܂��B
		 * @return	�{�[����
		 */
		KsInt32						getNumBone() const { return (KsInt32)m_vpBones.size(); }

		/**
		 * �{�[�������擾���܂��B
		 * @return	�{�[����
		 */
		KsBone*						getBone( KsUInt32 index ) { return m_vpBones[ index ]; }

		/**
		 * �p�����[�^�[���X�V����
		 */
		void						updateParameter( KsModelParameter* pParameter );

	private:
		KsUInt32					m_effectID;			/// �g�p�G�t�F�N�gID
		KsEffect*					m_pEffect;			/// �g�p�G�t�F�N�g
		KsIndexBuffer*				m_pIndexBuffer;		/// ���b�V�������̃C���f�b�N�X �o�b�t�@�[
		KsVertexBuffer*				m_pVertexBuffer;	/// ���b�V�� �p�[�c�̒��_�o�b�t�@�[
		KsInputLayout*				m_pInputLayout;		/// �C���v�b�g���C�A�E�g
		KsInt32						m_numVertices;		/// �`��Ăяo�����Ɏg�p����钸�_�̐�
		KsInt32						m_primitiveCount;	/// �����_�����O����v���~�e�B�u�̐�
		KsInt32						m_startIndex;		/// �C���f�b�N�X�z��̒��Œ��_�̓ǂݎ����J�n����ʒu
		KsInt32						m_vertexOffset;		/// ���_�o�b�t�@�[�̍ŏ㕔����̃I�t�Z�b�g
		KsInt32						m_numPallet;		/// �g�p�}�g���b�N�X�p���b�g��
		KsInt32*					m_pPallet;			/// �g�p�}�g���b�N�X�p���b�g
		KsBoneCollection			m_vpBones;			/// �{�[���R���N�V����
		//KsUserData*				m_pUserData;		/// ���[�U�[�f�[�^
};

#endif		/* __KSMESHPART_H__ */



