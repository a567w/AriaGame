/************************************************************************************************/
/** 
 * @file		KsMesh.h
 * @brief		���b�V���N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMESH_H__
#define __KSMESH_H__

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
class ksENGINE_API KsMesh
{
	private:
		KsString					m_name;				/// ���̃��b�V���̖��O���擾���܂��B
		KsBoundingSphere			m_boundingSphere;	/// ���̃��b�V�����܂܂�Ă��� BoundingSphere ���擾���܂��B
		KsMeshPartCollection		m_vpMeshParts;		/// ���̃��b�V�����\������ ModelMeshPart �I�u�W�F�N�g���擾���܂��B���b�V���̊e�p�[�c�́A�����}�e���A�������L����v���~�e�B�u�̏W���ō\������Ă��܂��B
		//KsEffectCollection			m_vpEffects;		/// ���̃��b�V���Ɋ֘A�t�����Ă���G�t�F�N�g�̃R���N�V�������擾���܂��B
		//KsUserData*				m_pUserData;		/// ���[�U�[�f�[�^

		//     ���̃��b�V���Ɋ֘A�t�����Ă���G�t�F�N�g�̃R���N�V�������擾���܂��B
		//ModelEffectCollection		Effects

		//     ���̃��b�V���̐e�{�[�����擾���܂��B���b�V���̐e�{�[���ɂ̓��f���Őe���b�V���Ɋ֘A�������b�V����z�u������@���L�q����ϊ��s�񂪊܂܂�܂��B
		//ModelBone					ParentBone

	public:
		/**
		 * �R���X�g���N�^
		 */
									KsMesh();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsMesh();

		/** 
		 * �`�揈��
		 * @param	pRenderContext	�`��R���e�L�X�g
		 */
		virtual void				draw( KsRenderContext* pRenderContext, KsModelParameter* pParameter=NULL );

		//     ���݂� Effect �ݒ���g�p���āA���̃��b�V�����̂��ׂĂ� ModelMeshPart �I�u�W�F�N�g��`�悵�܂��B
		KsMeshPart*					getMeshPart( KsUInt32 index ) { return m_vpMeshParts[ index ]; }
		KsUInt32					getMeshPartCount() const { return m_vpMeshParts.size(); }

	public:
		void						addMeshParts( KsMeshPart* pMeshPart ) { m_vpMeshParts.push_back( pMeshPart ); }
};

#endif		/* __KSMESH_H__ */



