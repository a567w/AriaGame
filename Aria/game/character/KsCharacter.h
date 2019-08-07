/************************************************************************************************/
/** 
 * @file		KsCharacter.h
 * @brief		KsCharacter�t�@�C��
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSCHARACTER_H__
#define __KSCHARACTER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                          */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsCharacterPad;

/************************************************************************************************/
/**
 * @class		KsCharacter
 * @brief		�L�����N�^�[�N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsCharacter : public KsActor, public KsTask
{
	public:
		/**
		 * �R���X�g���N�^
		 * @param	pModel			���f���f�[�^
		 * @param	updateOrder		�X�V�I�[�_�[
		 * @param	drawOrder		�`��I�[�_�[
		 */
									KsCharacter( KsModel* pModel, KsUInt32 updateOrder, KsUInt32 drawOrder );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsCharacter();

		/**
		 * �X�V����
		 * @param		pParam		�p�����[�^
		 */
		virtual void*				update( void* pParam );

		/**
		 * �`�揈��
		 * @param		pParam		�p�����[�^
		 */
		virtual void*				draw( void* pParam );

	protected:
		KsCharacterPad*				m_pPad;		/**< �L��������p�b�h		*/
		//KsCharacterJob*				m_pJob;
};

#if 0
class KsCharacterDebug
{
	public:
		/**
		 * �R���X�g���N�^
		 * @param	pCharacter		�L�����N�^�[
		 */
		KsCharacterDebug( KsCharacter* pCharacter );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsCharacterDebug();

		/**
		 * �X�V����
		 * @param		pParam		�p�����[�^
		 */
		virtual void*				update( void* pParam );

		/**
		 * �`�揈��
		 * @param		pParam		�p�����[�^
		 */
		virtual void*				draw( void* pParam );

		void						drawBone();
		void						drawPhysics();
};

void KsCharacterDebug::drawBone()
{
	// �{�[�����f��������Ă��Ƃ�
	const KsUInt32 boneCount = m_pModel->getBoneCount();

	for( KsUInt32 i=0; i<boneCount; i++ )
	{
		m_pModel->getBone();
	}
}


void KsCharacterDebug::drawRigidBody()
{
	// �{�[�����f��������Ă��Ƃ�
	const KsUInt32 boneCount = m_pModel->getRigidBody();

	for( KsUInt32 i=0; i<boneCount; i++ )
	{
		m_pModel->getRigidBody( i );
	}
}
#endif

#endif /* __KSCHARACTER_H__ */
