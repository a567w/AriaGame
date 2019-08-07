/*************************************************************************************************/
/**
 * @file	KsSprite.h
 * @brief	�X�v���C�g�N���X
 * @author	Tsukasa Kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/*************************************************************************************************/
#ifndef __KSSPRITE_H__
#define __KSSPRITE_H__

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*===============================================================================================*/
#include "KsTask.h"

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/
#define ksSPRITE_FLAGS_FILP_X		( 1<< 1 )
#define ksSPRITE_FLAGS_FILP_Y		( 1<< 2 )
#define ksSPRITE_BLEND_ADD			( 1<< 3 )
#define ksSPRITE_BLEND_SUB			( 1<< 4 )
#define ksSPRITE_BLEND_ALPHA		( 1<< 5 )
#define ksSPRITE_CLIP_X			( 1<< 6 )
#define ksSPRITE_CLIP_Y			( 1<< 7 )
#define ksSPRITE_INVISIBLE			( 1<< 8 )	/**< �s��									*/
#define ksSPRITE_DEFAULT_PRIORITY	( 64 )		/**< �X�v���C�g�̃f�t�H���g��Ԃł̗D�揇��	*/
#define ksSPRITE_TASK_ORDER		( 3 )		/**< �X�v���C�g�^�X�N�̃I�[�_�[				*/

#define ksSPRITE_WORK_MAX			( 1<<10 )	/**< �X�v���C�g���[�N�G���A(�ő�1024�X�v���C�g)	*/

/*===============================================================================================*/
/*                                     << �錾 >>                                                */
/*===============================================================================================*/
class KsTexture;
class KsVertexBuffer;

class KsRectReal
class KsSprite : public KsTask
{
	public:
								KsSprite();

		virtual				~KsSprite();

		/**
		 * ����������(�}�l�[�W���ɓo�^���ꂽ�Ƃ��ɓo�^)
		 * @param	pParam		�p�����[�^
		 */
		virtual void*			initialize( void* pParam );

		/**
		 * �^�X�N�̎��s
		 * @param	pParam		�p�����[�^
		 */
		virtual void*			execute( void* pParam );

		/**
		 * �`�揈��
		 * @param	pParam		�p�����[�^
		 */
		virtual void*			render( void* pParam );

		/**
		 * �㏈���֐��Ń������[����폜�����Ƃ��ɌĂ΂��
		 * @param	pParam		�p�����[�^
		 */
		virtual void*			terminate( void* pParam );

	protected:
		KsUInt32				m_spriteFlags;		/**< �e��t���O		*/
		KsVector2d				m_controlPoint;		/**< ��_			*/
		KsVector2d				m_scale;			/**< �X�P�[��		*/
		KsVector2d				m_trans;			/**< ���s�ړ�		*/
		KsReal					m_angle;			/**< ��]�l			*/
		KsReal					m_x;				/**< �摜�̍�		*/
		KsReal					m_y;				/**< �摜�̏�		*/
		KsReal					m_w;				/**< �摜�̕�		*/
		KsReal					m_h;				/**< �摜�̍���		*/
		KsReal					m_clipX;			/**< �N���b�s���OX	*/
		KsReal					m_clipY;			/**< �N���b�s���OY	*/
		KsReal					m_clipW;			/**< �N���b�s���OW	*/
		KsReal					m_clipH;			/**< �N���b�s���OH	*/
		KsVector4d				m_ST;

};

/*************************************************************************************************/
/**
 * @class	KsSprite
 * @brief	�X�v���C�g
 * @author	tsukasa kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/*************************************************************************************************/
class KsSprite : public KsTask
{
		friend class KsSpriteWorkArea;
	public:
		KsUInt16						m_spriteFlags;		/**< �X�v���C�g�t���O		*/
		KsUInt8							m_useWork;			/**< ���[�N�t���O			*/
		KsUInt8							m_reserv;			/**< ��					*/
		KsTexture*						m_pTexture;			/**< �e�N�X�`��				*/
		KsReal							m_centerX;			/**< ���SX���W				*/
		KsReal							m_centerY;			/**< ���SY���W				*/
		KsReal							m_scaleX;			/**< X�X�P�[���l			*/
		KsReal							m_scaleY;			/**< Y�X�P�[���l			*/
		KsInt32							m_clipX;			/**< */
		KsInt32							m_clipY;
		KsInt32							m_clipW;
		KsInt32							m_clipH;
		KsReal							m_rotate;			/**< ��]��					*/
		KsVertexBuffer*					m_pVertex;			/**< ���_�f�[�^				*/
		KsReal							m_x[ 4 ];			/**< �Z�b�g���W�ۑ��p		*/
		KsReal							m_y[ 4 ];			/**< �Z�b�g���W�ۑ��p		*/
		//KsMatrix						m_mat;				// �ړ��Ɖ�]�̓}�g���b�N�X���g�����ق������������E�E�E
		//KsMatrix						m_ltm;				//

	public:
		/**
		 * �R���X�g���N�^
		 */
										KsSprite();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsSprite();

		/**
		 * �X�v���C�g����
		 * @param		x				X���W
		 * @param		y				Y���W
		 * @param		w				��
		 * @param		h				����
		 * @param		tx				�e�N�X�`����X���W
		 * @param		ty				�e�N�X�`����Y���W
		 * @param		tw				�e�N�X�`���̕�
		 * @param		th				�e�N�X�`���̍���
		 * @param		scaleX			X�̃X�P�[���l
		 * @param		scaleY			Y�̃X�P�[���l
		 * @param		rotate			��]��
		 * @param		color			�J���[
		 * @param		pTexture		�g�p�e�N�X�`���̃|�C���^(�g�p���Ȃ��Ƃ��́ANULL��ݒ�)
		 */
		void							create( KsReal	x,	KsReal	 y,	KsReal	 w, KsReal	h,
												KsReal	tx,	KsReal	ty,	KsReal	tw,	KsReal	th,
												KsReal	scaleX, KsReal		scaleY,
												KsReal	rotate, KsUInt32	color,	KsTexture* pTexture );

		/**
		 * �X�v���C�g����
		 * @param		x				X���W
		 * @param		y				Y���W
		 * @param		w				��
		 * @param		h				����
		 * @param		tx				�e�N�X�`����X���W
		 * @param		ty				�e�N�X�`����Y���W
		 * @param		tw				�e�N�X�`���̕�
		 * @param		th				�e�N�X�`���̍���
		 * @param		color			�J���[
		 * @param		pTexture		�g�p�e�N�X�`���̃|�C���^(�g�p���Ȃ��Ƃ��́ANULL��ݒ�)
		 */
		void							create( KsReal	 x,	KsReal	 y,	KsReal	 w, KsReal	h,
												KsReal	tx,	KsReal	ty,	KsReal	tw,	KsReal	th,
												KsUInt32	color,	KsTexture* pTexture );

		/**
		 * �X�v���C�g����
		 * @param		x				�X�v���C�g�\����X���W(�X�v���C�g�̒��S����_�Ƃ���)
		 * @param		y				�X�v���C�g�\����Y���W(�X�v���C�g�̒��S����_�Ƃ���)
		 * @param		tx				�e�N�X�`����X���W
		 * @param		ty				�e�N�X�`����Y���W
		 * @param		w				��
		 * @param		h				����
		 * @param		color			�J���[
		 * @param		pTexture		�g�p�e�N�X�`���̃|�C���^(�g�p���Ȃ��Ƃ��́ANULL��ݒ�)
		 */
		void							create( KsReal	 x,	KsReal	 y,
												KsReal	tx,	KsReal	ty,
												KsReal	 w,	KsReal	 h,
												KsUInt32	color,	KsTexture* pTexture );

		/**
		 * �X�v���C�g�t���O���Z�b�g����
		 * @param		flags			�e��t���O
		 */
		void							setSpriteFlags( KsUInt32 flags );

		/**
		 * UV���W���Z�b�g���܂�
		 * @param		tx				�e�N�X�`����X���W
		 * @param		ty				�e�N�X�`����Y���W
		 * @param		tw				�e�N�X�`���̕�
		 * @param		th				�e�N�X�`���̍���
		 */
		void							setUVWH( KsReal tx, KsReal ty, KsReal tw, KsReal th );

		/**
		 * �w�蒸�_�̒��_�J���[���Z�b�g����
		 * @param		index			�C���f�b�N�X
		 * @param		color			�J���[
		 */
		void							setColor( KsUInt32 index, KsUInt32 color );

		/**
		 * ���ׂĂ̒��_�J���[���Z�b�g����
		 * @param		color			�J���[
		 */
		void							setColorAll( KsUInt32 color );


		/**
		 * �X�P�[���l���Z�b�g����
		 * @param		scaleX			�X�P�[��X
		 * @param		scaleX			�X�P�[��Y
		 */
		void							setScale( KsReal scaleX, KsReal scaleY );

		/**
		 * �e�N�X�`�����Z�b�g����
		 * @param		pTexture		�e�N�X�`��
		 */
		void							setTexture( KsTexture* pTexture );

		/**
		 * �ʒu���W���Z�b�g����
		 * @param		x				X���W
		 * @param		y				Y���W
		 */
		void							setTranslate( KsReal x, KsReal y );

		/**
		 * ��]�p�x�Z�b�g����
		 * @param		rotate			��]�p�x
		 */
		void							setRotate( KsReal rotate );

		/**
		 * ���̏�Ԃ���w��ʉ�]������
		 * @param		x				X�����̈ړ���
		 * @param		y				Y�����̈ړ���
		 */
		void							translate( KsReal x, KsReal y );

		/**
		 * ���̏�Ԃ���w��ʉ�]������
		 * @param		rotate			��]��
		 */
		void							rotate( KsReal rotate );

		/**
		 * ����������(�}�l�[�W���ɓo�^���ꂽ�Ƃ��ɓo�^)
		 * @param		pParam			�p�����[�^
		 */
		virtual void*					initialize( void* pParam );

		/**
		 * �^�X�N�̎��s
		 * @param		pParam			�p�����[�^
		 */
		virtual void*					execute( void* pParam );

		/**
		 * �`�揈��
		 * @param		pParam			�p�����[�^
		 */
		virtual void*					render( void* pParam );

		/**
		 * �㏈���֐��Ń������[����폜�����Ƃ��ɌĂ΂��
		 * @param		pParam			�p�����[�^
		 */
		virtual void*					terminate( void* pParam );

	protected:
		/**
		 * �X�^�[�g�A�b�v
		 */
		void							startup();

		/**
		 * �p�����[�^���N���A�[����
		 */
		void							clear();

		/**
		 * ���_�Ȃǂ��ăZ�b�g���Ȃ���
		 */
		void							reset();

		/**
		 * ���_�o�b�t�@�𐶐�����
		 */
		void							createVertexBuffer();

		/**
		 * ���_�o�b�t�@���폜����
		 */
		void							destroyVertexBuffer();
};

class KsSpriteManager
{
	KsSpriteManager();
};

/*************************************************************************************************/
/**
 * @class	KsSpriteWorkArea
 * @brief	�X�v���C�g���[�N�G���A
 * @author	tsukasa kato
 * @date	2003/11/30
 * @version	1.0.0
 * @note	�������[�N������Ȃ��Ȃ�����new�Ő��������
 */
/*************************************************************************************************/
class KsSpriteWorkArea
{
	public:
		/**
		 * ������
		 */
		static void					initialize();

		static void					terminate();

		/**
		 * �X�v���C�g����
		 */
		static KsSprite*				createSprite();

		/**
		 * �X�v���C�g�j��
		 * @param		pSprite			�X�v���C�g
		 */
		static void					destroySpreite( KsSprite* pSprite );

	private:
		static KsSprite					m_spriteWork[ ksSPRITE_WORK_MAX ];	/**< �X�v���C�g�p���[�N			*/
		static KsSprite*				m_spriteStack[ ksSPRITE_WORK_MAX ];	/**< �󂫃��[�N�G���A�X�^�b�N	*/
		static KsInt32					m_stackCount;						/**< �X�^�b�N�J�E���g			*/
};


inline void KsSpriteWorkAreaInitialize() { KsSpriteWorkArea::initialize(); }


#endif /* __KSSPRITE_H__ */



