/************************************************************************************************/
/** 
 * @file		KsFont.h
 * @brief		文字操作
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSFONT_H__
#define __KSFONT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsDIB.h"

/************************************************************************************************/
/**
 * @class	
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsFont : public KsDIB
{
	public:
									KsFont();
		
		virtual					~KsFont();
		
		virtual KsBool				create( ksPIXEL_FORMAT format, KsInt32 width, KsInt32 height );

		//KsBool						open( kind );
		//void						close();

		void						setTextColor( COLORREF color );
		void						setBackColor( COLORREF color );
		void						setBorderColor( COLORREF color );

		HFONT						m_hFont;		/**< フォントのハンドル				*/
		HBRUSH						m_hBrush;		/**< ブラシのハンドル					*/
		HPEN						m_hPen;			/**< ペンのハンドル					*/
		COLORREF					m_textColor;	/**< テキストカラー					*/
		COLORREF					m_backColor;	/**< バックのカラー					*/
		COLORREF					m_borderColor;	/**< 縁取りのカラー					*/

		//void						Test();

		//void						draw( KsInt32 x, KsInt32 y, const KsChar* format, ... );

	protected:
		void						ConfigDefault();
		/* フォントサイズと縁取りなど設定できるようにする */
};

#endif		/* __KSFONT_H__ */


















#if 0


struct NEOENGINE_API NeFontCharacter
{
	public:

		/*! U coord in texture */
		float                           m_fU;

		/*! V coord in texture */
		float                           m_fV;

		/*! Width in texture coords */
		float                           m_fUWidth;

		/*! Height in texture coords */
		float                           m_fVHeight;

		/*! Pixel X coord in texture */
		int                             m_iX;

		/*! Pixel Y coord in texture */
		int                             m_iY;

		/*! Width in pixels */
		int                             m_iWidth;

		/*! Height in pixels */
		int                             m_iHeight;
};





/**
  * \class NeFont
  * \brief Font abstraction. Loads, prints and other methods.
  * \author Mattias Jansson (mattias@realityrift.com)
  */
class NEOENGINE_API NeFont : public NeRefCounter, public NeLoadableEntity
{
	friend class NeFontManager;

	public:

		/**
		* \enum NEFONTALIGN
		* \brief Font alignment
		*/
		enum NEFONTALIGN
		{
		  LEFT,
		  RIGHT
		};

		/**
		* \enum NEFONTLINEWRAP
		* \brief Line wrapping modes
		*/
		enum NEFONTLINEWRAP
		{
			NOWRAP,
			WORDWRAP
		};



	protected:

		/*! Material */
		NeMaterialPtr                   m_pkMaterial;

		/*! Characters */
		NeFontCharacter                 m_akCharacters[256];

		/*! Space between characters */
		int                             m_iSpacing;

		/*! Line height */
		int                             m_iLineHeight;

		/*! Width of space character */
		int                             m_iSpaceWidth;

		/*! Clip box x coord */
		int                             m_iClipX;

		/*! Clip box y coord */
		int                             m_iClipY;

		/*! Clip box width */
		int                             m_iClipWidth;

		/*! Clip box height */
		int                             m_iClipHeight;

		/*! Line wrap flag */
		NEFONTLINEWRAP                  m_eLineWrap;

		/*! Font name */
		std::string                     m_strName;

		/*! Font manager */
		NeFontManager                  *m_pkFontManager;

		/*! Word separators */
		std::string                     m_strWordSeparators;

		/*! Font horizontal alignment */
		NEFONTALIGN                     m_eHorizontalAlign;

		/*! Current color */
		NeColor                         m_kColor;


		/**
		* Main loader method. Called by NeLoadableEntity to load object if file was opened successfully
		* \param uiFlags                Loader flags (currently ignored for fonts)
		* \return                       true if load was successful, false otherwise
		*/
		bool                            LoadNode( unsigned int uiFlags );


		/**
		* Fonts are created by the font manager
		* \param pkResourceManager      Resource manager
		* \param pkFontManager          Font manager
		*/
		                                NeFont( NeResourceManager *pkResourceManager, NeFontManager *pkFontManager );


  public:


		/**
		*/
		virtual                        ~NeFont();

		/**
		* Printf to screen
		* \param iX                     Start x coord in pixels
		* \param iY                     Start y coord in pixels
		* \param pszFormat              Format specifier (see printf function)
		* \return                       number of lines printed
		*/
		int                             Printf( int iX, int iY, const char *pszFormat, ... );

		/**
		* Printf to screen
		* \param fX                     Start x coord in screen coords ( range 0.0f < x < 1.0f )
		* \param fY                     Start y coord in screen coords ( range 0.0f < y < 1.0f )
		* \param pszFormat              Format specifier (see printf function)
		* \return                       number of lines printed
		*/
		int                             Printf( float fX, float fY, const char *pszFormat, ... );

		/**
		* Set clip box. Will not blit any pixels outside this box, and will (optionally) line wrap
		* \param iX                     x coordinate of clip box
		* \param iY                     y coordinate
		* \param iWidth                 width
		* \param iHeight                height
		*/
		void                            SetClipBox( int iX, int iY, int iWidth, int iHeight );

		/**
		* Get clip box
		* \param piX                    Ptr to var receiving x coordinate of clip box
		* \param piY                    Ptr to y coordinate
		* \param piWidth                Ptr to width
		* \param piHeight               Ptr to height
		*/
		void                            GetClipBox( int *piX, int *piY, int *piWidth, int *piHeight );

		/**
		* Reset clip box
		*/
		void                            ResetClipBox();

		/**
		* Set line wrap flag
		* \param eWrap                  New line wrapping mode
		* \return                       Previous wrap mode
		*/
		NEFONTLINEWRAP                  SetLineWrap( NEFONTLINEWRAP eWrap ) { NEFONTLINEWRAP eRet = m_eLineWrap; m_eLineWrap = eWrap; return eRet; }

		/**
		* \return                       Line wrap mode
		*/
		NEFONTLINEWRAP                  GetLineWrap() const { return m_eLineWrap; }

		/**
		* \return                       Line height in pixels
		*/
		int                             GetLineHeight() const { return m_iLineHeight; }

		/**
		* \param rstrString             String
		* \return                       Unclipped total string length in pixels
		*/
		int                             GetStringLength( const std::string &rstrString );

		/**
		* \param rstrString             String
		* \param iX                     Start x coordinate
		* \return                       Number of pixels string would occupy if printed with the current settings (clipbox, linewrap...)
		*/
		int                             GetStringHeight( const std::string &rstrString, int iX );

		/**
		* \return                       Font name
		*/
		const std::string              &GetName() const { return m_strName; }

		/**
		* \return                       Current font color
		*/
		const NeColor                  &GetColor() const;

		/**
		* \param rkColor                New font color to set
		* \return                       Old font color
		*/
		NeColor                         SetColor( const NeColor &rkColor );

		/**
		* Set word separator characters
		* \param rstrSeparators         String with all separator characters
		*/
		void                            SetWordSeparators( const std::string &rstrSeparators );

		/**
		* Set alignment
		* \param eAlign                 New horizontal alignment
		* \return                       Old alignment
		*/
		NEFONTALIGN                     SetHorizontalAlign( NEFONTALIGN eAlign );

		/**
		* \return                       Current horizontal alignment
		*/
		NEFONTALIGN                     GetHorizontalAlign();

		/**
		* Clip line to clipbox, applying line wrap modes and current print direction
		* \param rstrLine               String to clip
		* \param iX                     Start x coordinate
		* \param iY                     Start y coordinate
		* \param piLines                Optional pointer to integer receiving number of resulting lines
		* \return                       Clipped and formatted line
		*/
		std::string                     ClipLine( const std::string &rstrLine, int iX, int iY, int *piLines = 0 );
};




/**
  * \class NeFontManager
  * \brief A collection of fonts
  * \author Mattias Jansson (mattias@realityrift.com)
  */
class NEOENGINE_API NeFontManager
{
	friend class NeFont;
		
	protected:

		/*! Fonts */
		std::vector<NeFont*>            m_vpkFonts;

		/**
		* Deregister font
		* \param pkFont                 Font
		*/
		void                            DeregisterFont( NeFont *pkFont );


	public:

		/**
		*/
		                                NeFontManager();

		/**
		*/
		                               ~NeFontManager();

		/**
		* Create new font
		* \param rstrName               Font name. If font not found (previously loaded), will try loading font file.
		* \param pkResourceManager      Resource manager
		* \return                       New font object. If font name is not null string, and font was not found and load failed, a null pointer is returned
		*/
		NeFontPtr                       CreateFont( const std::string &rstrName, NeResourceManager *pkResourceManager );

		/**
		* Locate font
		* \param rstrName               Font name
		* \return                       Font ptr if found
		*/
		NeFontPtr                       FindFont( const std::string &rstrName );
};


#endif
