/************************************************************************************************/
/** 
 * @file		KsCellAnim.h
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KsCellAnim2D_H__
#define __KsCellAnim2D_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsCore.h"
#include "KsArray.h"
#include "KsAnim2DPart.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsRenderSystem;

/*

�Z���A�j���t�@�C���t�H�[�}�b�g

�t�@�C���w�b�_�[
signature	4byte

struct KS_CELLANIM_FILEHEADER
{
	signature;
	version;


	numPart;
	numTexture;
	numTrack;

	startFrame;
	endFrame;
	fps;

};


*/
namespace test
{


class KsCellAnimKeyFrame
{
	public:

		/**
		 * �A�j���t���O
		 */
		enum ksCELL_ANIM_FLAGS
		{
			ksCELL_ANIM_HIDE = 1 << 0,
		};

		/**
		 * �A�j���L�[�^�C�v
		 */
		enum ksCELL_ANIM_KEY_TYPE
		{
			ksCELL_ANIM_KEY_POS      = 1 << 0,	/**< �ʒu				*/
			ksCELL_ANIM_KEY_ROT      = 1 << 1,	/**< ��]				*/
			ksCELL_ANIM_KEY_SCALE    = 1 << 2,	/**< �X�P�[��			*/
			ksCELL_ANIM_KEY_COLOR    = 1 << 3,	/**< �J���[				*/
			ksCELL_ANIM_KEY_UV       = 1 << 4,	/**< UV					*/
			ksCELL_ANIM_KEY_PRIORITY = 1 << 5,	/**< �v���C�I���e�B�[	*/
			ksCELL_ANIM_KEY_USERDATA = 1 << 6,	/**< ���[�U�[�f�[�^		*/
		};

		/**
		 * 
		 */
		struct POS
		{
			KsReal		x;			/**< Y�ʒu���W		*/
			KsReal		y;			/**< X�ʒu���W		*/
		};

		/**
		 * 
		 */
		struct ROT
		{
			KsReal		angle;		/**< ��]�l			*/
			KsReal		padding;	/**< �p�f�B���O		*/
		};

		/**
		 * 
		 */
		struct SCALE
		{
			KsReal		x;			/**< X�X�P�[���l	*/
			KsReal		y;			/**< Y�X�P�[���l	*/
		};

		/**
		 * 
		 */
		struct COLOR
		{
			KsByte		r;
			KsByte		g;
			KsByte		b;
			KsByte		a;
			KsReal		padding;
		};

		/**
		 * 
		 */
		struct UV
		{
			KsReal		x;
			KsReal		y;
		};

		/**
		 * 
		 */
		struct PRIORITY
		{
			KsInt32	priority;
			KsInt32	padding;
		};

		/**
		 * 
		 */
		struct USERDATA
		{
			KsInt32	size;
			KsByte*		data;	// �Œ�4�o�C�g
		};

		/**
		 * 
		 */
		union KEY
		{
			POS			pos;
			ROT			rot;
			SCALE		scale;
			COLOR		color;
			UV			uv;
			PRIORITY	priority;
			USERDATA	userData;
		};

		/**
		 * �R���X�g���N�^
		 */
							KsCellAnimKeyFrame();

		/**
		 * �f�X�g���N�^
		 */
		virtual			~KsCellAnimKeyFrame();

	public:
		KsUInt16			m_target;	// �\���A��\���A�⊮�Ȃǂ̃t���O
		KsUInt16			m_flags;
		KsUInt32			m_type;		// �L�[�̃^�C�v
		KEY*				m_pKey;
		KsByte*				m_pUserData;
};


/************************************************************************************************/
/**
 * @class		KsCellAnimKeyFrame
 * @brief		�V���v���ȃA�j���[�V����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsCellAnimTrack
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsCellAnimTrack();

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsCellAnimTrack();

	public:
		KsInt32					m_frameNo;		/**< �t���[���ԍ�	*/
		KsCellAnimKeyFrame*			m_pKeyFrames;	/**< �L�[�t���[��	*/
};

/************************************************************************************************/
/**
 * @class		KsCellAnimPart
 * @brief		�V���v���ȃA�j���[�V����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsCellAnimPart
{
	public:
		//KsString			m_name;
		KsInt32			m_flags;
		KsInt32			m_priority;
		KsReal				m_px;
		KsReal				m_py;
		KsReal				m_x;
		KsReal				m_y;
		KsReal				m_w;
		KsReal				m_h;
		KsInt32			m_id;
		KsInt32			m_tex;
		KsColor				m_color;
		//KsReal			vertex[ 4 ][ 2 ];
};

/************************************************************************************************/
/**
 * @class		KsCellAnim2D
 * @brief		�V���v���ȃA�j���[�V����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsCellAnim2D
{
	public:
										KsCellAnim2D();
		virtual						~KsCellAnim2D();
		//KsBool							load( const KsChar* pFileName );
/*
		
		void							setColor( const KsColor& color );
		void							setColor( const KsColorReal& color );
		void							setAlpha( KsReal alpha );
		void							setAlpha( KsInt32 alpha );
		void							setScale( KsReal sx, KsReal sy );
		void							setScale( const KsVector2d& scale );
		void							setPos( KsReal x, KsReal y );
		void							setPos( KsInt32 x, KsInt32 y );
		void							setPos( const KsVector2d& pos );
		void							setAngle( KsReal angle );
		//void							trnslate( );
		//void							rotate();
*/
		//virtual void					update( KsReal time );
		//void							setPos( KsReal x, KsReal y ){ m_pos.x = x; m_pos.y = y; }
		//void							setPos( KsInt32 x, KsInt32 y );
		//void							setTexture( KsTexture* pTexture );
		//virtual void					update( ksFPS30 );
		//virtual void					update( KsReal time );
		//virtual void					update( KsReal time );
		//virtual void					draw( KsRenderSystem* pRS );

	public:
		KsUInt32						m_flags;		/**< �t���O				*/
		KsVector2d						m_pivot;		/**< ��_(��]���S)		*/
		KsVector2d						m_pos;			/**< �ʒu				*/
		KsVector2d						m_scale;		/**< �X�P�[��			*/
		KsReal							m_angle;		/**< ��]				*/
		KsColor							m_color;		/**< �J���[				*/
		KsReal							m_fps;			/**< */
		KsInt32						m_startFrame;		/**< */
		KsInt32						m_endFrame;			/**< */
		KsInt32						m_frame;		/**< �t���[��			*/
		KsInt32						m_drawFrame;	/**< �`�悵�Ă���L�[�t���[���ԍ�		*/
		KsInt32						m_nextFrame;	/**< ���ɍăZ�b�g����L�[�t���[���ԍ�	*/
		KsBool							m_bLoop;		/**< ���[�v���邩�ǂ����̃t���O			*/
		KsUInt16						m_numTexture;
		KsArray<KsCellAnimPart*>		m_pPartList;
		KsArray<KsCellAnimPart*>		m_pDrawList;
		KsArray<KsCellAnimTrack*>		m_vpTracks;		/**< �L�[�t���[��						*/
		KsArray<KsTexture*>				m_vpTextures;	/**< �g�p�e�N�X�`��						*/
};


#if 0





/************************************************************************************************/
/**
 * @class		KsAnimKeyFrame
 * @brief		�A�j���[�V����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
KsInt32 KsAnim2DTrack::getKeyFrame( KsReal time, KsReal *pParam, KsAnim2DKeyFrame* pKey1, KsAnim2DKeyFrame* pKey2, KsBool bLoop )
{
	if( time == 0.0f )
	{
		*pKey1  = *m_vKeyFrames[ 0 ];
		*pKey2  = *m_vKeyFrames[ 0 ];
		*pParam = 0.0f;
		return 0;
	}

	KsInt32	num = getNumKeyFrame()-1;

	if( time >= m_maxTime )
	{
		if( !bLoop )
		{
			*pKey1  = *m_vKeyFrames[ num ];
			*pKey2  = *m_vKeyFrames[ num ];
			*pParam = 1.0f;
			return num;
		}

		KsReal		param = KsFloor( time / m_maxTime );

		time = time - param * m_maxTime;
	}


	for( KsInt32 i=0; i<num; i++ )
	{
		if( (m_vKeyFrames[ i ]->m_time <= time) && (time < m_vKeyFrames[ i+1 ]->m_time) )
		{
			*pKey1 = *m_vKeyFrames[ i ];
			*pKey2 = *m_vKeyFrames[ i+1 ];

			KsReal	ft = time - m_vKeyFrames[ i ]->m_time;
			KsReal dt = m_vKeyFrames[ i+1 ]->m_time - m_vKeyFrames[ i ]->m_time;
			KsReal t;
			
			if( dt > 0.00000001f )
			{ 
				t = ft/dt;
			}
			else{
				t = 0.0f;
			}

			*pParam = t;

			return i;
		}
	}

	return -1;
}


void update()
{
	// �v���C�I���e�B�[�X�V�t���O

	// �L�[���ύX���ꂽ�Ƃ��D��x��ύX����

	/* �t���[���X�V */
	m_frame += m_frameRate;

	if( m_frame > m_endFrame )
	{
		if( m_bLoop )
		{
			m_frame -= m_endFrame;
		}
		else
		{
			m_frame = m_endFrame;
		}
	}

	/* �L�[��ݒ肷�邩�ǂ����H */
	if( m_oldFrame == m_frame )
	{
		return;
	}

	/* �⊮����̃A�j���H */
	if( interplate )
	{
		/* �⊮���� */
		/* �⊮�L�[���擾 */

	}
	else
	{
		/* �⊮�Ȃ� */
		if( m_nextFrame <= m_frame )
		{
			/* �V�����L�[���Z�b�g���� */
			/* ��ԋ߂��g���b�N���擾���� */
			m_vpTracks[ ];
		}
	}


	/* �`��o�^ */

	m_oldFrame = m_frame;
}

void KsCellAnim2D::draw( KsRenderSystem* pRS )
{
	for( KsUInt32 ii=0; ii<m_pDrawList.size(); ii++ )
	{
		KsCellAnimPart*		pPart = m_pDrawList[ ii ];

		if( pPart->m_flags )
		{
			//KsAssert( pPart->m_tex < m_vpTextures.size() );
			KsTexture*		pTexture = m_vpTextures[ pPart->m_tex ];

			pRS->drawRectEx(pPart->m_x + m_pos.x,
							pPart->m_y + m_pos.y,
							pPart->m_w,
							pPart->m_h,
							pPart->m_u0,
							pPart->m_v0,
							pPart->m_u1,
							pPart->m_v1,
							pPart->m_color,
							pTexture
							);
		}
	}
}



#endif
};




/************************************************************************************************/
/**
 * @class		KsCellAnimKeyFrame
 * @brief		�V���v���ȃA�j���[�V����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsCellAnimKeyFrame
{
	public:
		KsInt32					m_frame;
		KsArray<KsAnim2DPart*>		m_vpParts;
};

/************************************************************************************************/
/**
 * @class		KsCellAnim2D
 * @brief		�V���v���ȃA�j���[�V����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsCellAnim2D
{
	public:
										KsCellAnim2D();
		virtual						~KsCellAnim2D();
		KsBool							load( const KsChar* pFileName );
/*
		
		void							setColor( const KsColor& color );
		void							setColor( const KsColorReal& color );
		void							setAlpha( KsReal alpha );
		void							setAlpha( KsInt32 alpha );
		void							setScale( KsReal sx, KsReal sy );
		void							setScale( const KsVector2d& scale );
		void							setPos( KsReal x, KsReal y );
		void							setPos( KsInt32 x, KsInt32 y );
		void							setPos( const KsVector2d& pos );
		void							setAngle( KsReal angle );
		//void							trnslate( );
		//void							rotate();
*/
		//virtual void					update( KsReal time );
		void							setPos( KsReal x, KsReal y ){ m_pos.x = x; m_pos.y = y; }
		//void							setPos( KsInt32 x, KsInt32 y );
		void							setTexture( KsTexture* pTexture );
		virtual void					update();
		virtual void					draw( KsRenderSystem* pRS );

	public:
		KsUInt32						m_flags;		/**< �t���O				*/
		KsVector2d						m_pivot;		/**< ��_(��]���S)		*/
		KsVector2d						m_pos;			/**< �ʒu				*/
		KsVector2d						m_scale;		/**< �X�P�[��			*/
		KsReal							m_angle;		/**< ��]				*/
		KsColor							m_color;		/**< �J���[				*/
		KsReal							m_fps;			/**< */
		KsInt32						m_start;		/**< */
		KsInt32						m_end;			/**< */
		KsInt32						m_frame;		/**< �t���[��			*/
		KsInt32						m_drawFrame;	/**< �`�悵�Ă���L�[�t���[���ԍ�		*/
		KsInt32						m_nextFrame;	/**< ���ɍăZ�b�g����L�[�t���[���ԍ�	*/
		KsBool							m_bLoop;		/**< ���[�v���邩�ǂ����̃t���O			*/
		KsArray<KsCellAnimKeyFrame*>	m_vpKeyFrames;	/**< �L�[�t���[��						*/
		KsArray<KsTexture*>				m_vpTextures;	/**< �g�p�e�N�X�`��						*/
};



#endif /* __KsCellAnim2D_H__ */


