/************************************************************************************************/
/** 
 * @file		KsFont.h
 * @brief		�t�H���g�`��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSFONT_H__
#define __KSFONT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @enum		ksSPRITE_SORT_MODE
 * @brief		�X�v���C�g�t�H���g���[�h
 * @since		2003/10/25
 * @author		Tsukasa Kato
 */
/************************************************************************************************/
enum ksSPRITE_SORT_MODE
{
	ksSPRITE_SORT_MODE_DEFERRED,
	ksSPRITE_SORT_MODE_IMMEDIATE,
	ksSPRITE_SORT_MODE_TEXTURE,
	ksSPRITE_SORT_MODE_BACKTOFRONT,
	ksSPRITE_SORT_MODE_FRONTTOBACK,
};

/************************************************************************************************/
/**
 * @enum		ksSPRITE_SORT_MODE
 * @brief		�X�v���C�g�t�H���g���[�h
 * @since		2003/10/25
 * @author		Tsukasa Kato
 */
/************************************************************************************************/
enum ksSPRITE_EFFECTS
{
	ksSPRITE_EFFECTS_NONE             = 0,
	ksSPRITE_EFFECTS_FLIPHORIZONTALLY = 1,
	ksSPRITE_EFFECTS_FLIPVERTICALLY   = 2,
	ksSPRITE_EFFECTS_FLIPBOTH         = ksSPRITE_EFFECTS_FLIPHORIZONTALLY | ksSPRITE_EFFECTS_FLIPVERTICALLY,
};

/************************************************************************************************/
/**
 * @struct		KsGlyph
 * @brief		�X�v���C�g�t�H���g���[�h
 * @since		2003/10/25
 * @author		Tsukasa Kato
 */
/************************************************************************************************/
struct KsGlyph
{
	KsUInt32		Character;
	KsRect			Subrect;
	KsReal			XOffset;
	KsReal			YOffset;
	KsReal			XAdvance;
};

/************************************************************************************************/
/**
 * @class		KsFont
 * @brief		�t�H���g�`��N���X
 * @since		2003/10/25
 * @author		Tsukasa Kato
 */
/************************************************************************************************/
class ksENGINE_API KsFont
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsFont();
		/**
		 * �R���X�g���N�^
		 * @param	pFileName		�t�@�C����
		 */
									KsFont( const KsWChar* pFileName );

		/**
		 * �R���X�g���N�^
		 * @param	pData			�f�[�^
		 * @param	dataSize		�f�[�^�T�C�Y
		 */
									KsFont( const KsByte* pData, KsUInt32 dataSize );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsFont();

		/**
		 * ��������
		 */
		void						create( const KsWChar* pFileName );

		/**
		 * ��������
		 */
		void						create( KsBinaryReader* pReader );

		/**
		 * �j������
		 */
		void						destroy();

		/**
		 * ������`��
		 */
		void						drawString( const KsWChar*  pText, const KsVector2d& position, KsColor color = KsColor::WHITE, KsReal rotation = 0.0f, const KsVector2d& origin = KsVector2d::ZERO, KsReal scale = 1.0f, ksSPRITE_EFFECTS effects = ksSPRITE_EFFECTS_NONE, KsReal layerDepth = 0.0f );
		void						drawString( const KsSChar*  pText, const KsVector2d& position, KsColor color = KsColor::WHITE, KsReal rotation = 0.0f, const KsVector2d& origin = KsVector2d::ZERO, KsReal scale = 1.0f, ksSPRITE_EFFECTS effects = ksSPRITE_EFFECTS_NONE, KsReal layerDepth = 0.0f );
		void						drawString( const KsString& rText, const KsVector2d& position, KsColor color = KsColor::WHITE, KsReal rotation = 0.0f, const KsVector2d& origin = KsVector2d::ZERO, KsReal scale = 1.0f, ksSPRITE_EFFECTS effects = ksSPRITE_EFFECTS_NONE, KsReal layerDepth = 0.0f );

		void						drawString( const KsWChar*  pText, KsInt32 x, KsInt32 y );

		KsVector4d					measureString( const KsWChar* pText );
		KsBool						containsCharacter( KsWChar character );


		KsTexture*					getTexture() { return m_pTexture; }

	protected:

		template<typename TAction>
		void						forEachGlyph( const KsWChar* pText, TAction action );

		/**
		 * 
		 * @return					
		 */
		const KsGlyph*				findGlyph( KsWChar character );

		/**
		 * 
		 * @return					
		 */
		KsWChar						getDefaultCharacter() const;

		/**
		 * 
		 * @return					
		 */
		void						setDefaultCharacter( KsWChar character );

		/**
		 * ���C���X�y�[�X���擾����
		 * @return					���C���X�y�[�X
		 */
		KsReal						getLineSpacing() const;

		/**
		 * ���C���X�y�[�X���Z�b�g����
		 * @param	spacing			���C���X�y�[�X
		 */
		void						setLineSpacing( KsReal spacing );

		/**
		 * 
		 * @return					
		 */
		KsInt32						binarySearch( KsUInt32 key );

	protected:
		KsReal						m_lineSpacing;		/**< ���C���X�y�[�X			*/
		KsTexture*					m_pTexture;			/**< �t�H���g�e�N�X�`��		*/
		const KsGlyph*				m_pDefaultGlyph;	/**< �f�t�H���g�O���t			*/
		KsGlyph*					m_pGlyphs;			/**< �O���t���X�g				*/
		KsUInt32					m_numGlyph;			/**< �O���t���F				*/
		KsGraphics*					m_pGraphics;		/**< �O���b�t�B�N�X�I�u�W�F�N�g	*/
};


#endif		/* __KSFONT_H__ */
