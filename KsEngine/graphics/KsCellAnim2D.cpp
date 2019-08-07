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

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsCellAnim2D.h"
#include "KsAnim2DPart.h"
#include "KsXmlTextReader.h"
#include "KsRenderSystem.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


namespace test
{

KsCellAnimKeyFrame::KsCellAnimKeyFrame()
	: m_target( 0 )
	, m_type( 0 )
	, m_flags( 0 )
	, m_pKey( 0 )
	, m_pUserData( 0 )
{
}

KsCellAnimKeyFrame::~KsCellAnimKeyFrame()
{
	ksDELETEARRAY( m_pKey );
	ksDELETEARRAY( m_pUserData );
}


KsCellAnimTrack::KsCellAnimTrack()
	: m_frameNo( 0 )
	, m_pKeyFrames( 0 )
{
}

KsCellAnimTrack::~KsCellAnimTrack()
{
	ksDELETEARRAY( m_pKeyFrames );
}

KsCellAnim2D::KsCellAnim2D()
{
}

KsCellAnim2D::~KsCellAnim2D()
{
}

};



KsCellAnim2D::KsCellAnim2D()
	: m_frame( 0 )
	, m_drawFrame( 0 )
	, m_nextFrame( 0 )
{
}

KsCellAnim2D::~KsCellAnim2D()
{
	for( KsUInt32 ii=0; ii<m_vpKeyFrames.size(); ii++ )
	{
		KsCellAnimKeyFrame*		pKeyFrame = m_vpKeyFrames[ ii ];

		for( KsUInt32 jj=0; jj<pKeyFrame->m_vpParts.size(); jj++ )
		{
			KsAnim2DPart*		pPart = pKeyFrame->m_vpParts[ jj ];

			ksDELETE( pPart );
		}

		ksDELETE( pKeyFrame );
	}

	m_vpTextures.clear();
}

void KsCellAnim2D::setTexture( KsTexture* pTexture )
{
	m_vpTextures.push_back( pTexture );
}

KsBool KsStrCmp( const KsChar* pStr0, const KsChar* pStr1 )
{
	return ( stricmp( pStr0, pStr1 ) == 0 );
}

#if 0
class KsCellAnim2DLoader
{
public:
	KsCellAnim2D*		create( const KsChar* pFileName );

public:
	KsBool				readHeader( const KsXmlTextReader* pXmlReader, KsCellAnim2D* pChipAnim2D );
};

KsBool KsCellAnim2DLoader::readHeader( const KsXmlTextReader* pXmlReader, KsCellAnim2D* pChipAnim2D )
{
	/* ヘッダー情報を取得 */
	while( !(ksXmlEndElement == pXmlReader->getNodeType() && KsStrCmp( pXmlReader->getName(), "header" )) )
	{
		pXmlReader->read();

		if( KsStrCmp( pXmlReader->getName(), "fps" ) )
		{
			pXmlReader->read();
			m_fps = s_cast<KsReal>( atof( pXmlReader->getValue() ) );
			pXmlReader->read();
			pXmlReader->read();
		}
		else if( KsStrCmp( pXmlReader->getName(), "start" ) )
		{
			pXmlReader->read();
			m_start = atoi( pXmlReader->getValue() );
			pXmlReader->read();
			pXmlReader->read();
		}
		else if( KsStrCmp( pXmlReader->getName(), "end" ) )
		{
			pXmlReader->read();
			m_end = atoi( pXmlReader->getValue() );
			pXmlReader->read();
			pXmlReader->read();
		}
	}
}

KsCellAnim2D* KsCellAnim2DLoader::create( const KsChar* pFileName )
{
	KsXmlTextReader*	pXmlReader = new KsXmlTextReader( pFileName );

	while( pXmlReader->read() )
	{
		KsXmlNodeType	nodeType = pXmlReader->getNodeType();

		switch( nodeType )
		{
			case ksXmlElement:
			{
				/* アニメーションタイプ */
				if( KsStrCmp( pXmlReader->getName(), "KsCellAnim2D" ) )
				{
					
				}
				else if( KsStrCmp( pXmlReader->getName(), "header" ) )
				{
					
				}
				else if( KsStrCmp( pXmlReader->getName(), "keyframe_array" ) )
				{
					KsInt32	keyFrameID  = 0;
					KsInt32	numKeyFrame = 0;

					while( pXmlReader->moveToNextAttribute() )
					{
						if( KsStrCmp( pXmlReader->getName(), "id" ) )
						{
							keyFrameID = atoi( pXmlReader->getValue() );
						}
						else if( KsStrCmp( pXmlReader->getName(), "count" ) )
						{
							numKeyFrame = atoi( pXmlReader->getValue() );
						}
					}

					while( !(ksXmlEndElement == pXmlReader->getNodeType() && KsStrCmp( pXmlReader->getName(), "keyframe_array" )) )
					{
						pXmlReader->read();

						if( ksXmlElement == pXmlReader->getNodeType() )
						{
						if( KsStrCmp( pXmlReader->getName(), "keyframe" ) )
						{

							KsCellAnimKeyFrame*		pKeyFrame = new KsCellAnimKeyFrame();

							KsAnim2DPart*	pPart = new KsAnim2DPart();

							while( !(ksXmlEndElement == pXmlReader->getNodeType() && KsStrCmp( pXmlReader->getName(), "keyframe" )) )
							{
								if( ksXmlElement == pXmlReader->getNodeType() )
								{
									if( KsStrCmp( pXmlReader->getName(), "frame" ) )
									{
										pXmlReader->read();
										pKeyFrame->m_frame = atoi( pXmlReader->getValue() );
										pXmlReader->read();
									}
									else if( KsStrCmp( pXmlReader->getName(), "size" ) )
									{
										pXmlReader->read();
										sscanf( pXmlReader->getValue(), "%f %f %f %f", &pPart->m_x, &pPart->m_y, &pPart->m_w, &pPart->m_h );
										pXmlReader->read();
									}
									else if( KsStrCmp( pXmlReader->getName(), "tex_coord" ) )
									{
										pXmlReader->read();
										sscanf( pXmlReader->getValue(), "%f %f %f %f", &pPart->m_u0, &pPart->m_v0, &pPart->m_u1, &pPart->m_v1 );
										pXmlReader->read();
									}
								}
								pXmlReader->read();
							}
							pKeyFrame->m_vpParts.push_back( pPart );
							m_vpKeyFrames.push_back( pKeyFrame );

						}
						}
					}
				}
				break;
			}
			case ksXmlText:
			{
				break;
			}
			case ksXmlEndElement:
			{
				break;
			}
			case ksXmlDeclaration:
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}

	ksDELETE( pXmlReader );

	return ksTRUE;
}
#endif

KsBool KsCellAnim2D::load( const KsChar* pFileName )
{
	KsXmlTextReader*	pXmlReader = new KsXmlTextReader( pFileName );

	while( pXmlReader->read() )
	{
		KsXmlNodeType	nodeType = pXmlReader->getNodeType();

		switch( nodeType )
		{
			case ksXmlElement:
			{
				/* アニメーションタイプ */
				if( KsStrCmp( pXmlReader->getName(), "KsCellAnim2D" ) )
				{
					
				}
				else if( KsStrCmp( pXmlReader->getName(), "header" ) )
				{
					/* ヘッダー情報を取得 */
					while( !(ksXmlEndElement == pXmlReader->getNodeType() && KsStrCmp( pXmlReader->getName(), "header" )) )
					{
						pXmlReader->read();

						if( KsStrCmp( pXmlReader->getName(), "fps" ) )
						{
							pXmlReader->read();
							m_fps = s_cast<KsReal>( atof( pXmlReader->getValue() ) );
							pXmlReader->read();
							pXmlReader->read();
						}
						else if( KsStrCmp( pXmlReader->getName(), "start" ) )
						{
							pXmlReader->read();
							m_start = atoi( pXmlReader->getValue() );
							pXmlReader->read();
							pXmlReader->read();
						}
						else if( KsStrCmp( pXmlReader->getName(), "end" ) )
						{
							pXmlReader->read();
							m_end = atoi( pXmlReader->getValue() );
							pXmlReader->read();
							pXmlReader->read();
						}
					}
				}
				else if( KsStrCmp( pXmlReader->getName(), "keyframe_array" ) )
				{
					KsInt32	keyFrameID  = 0;
					KsInt32	numKeyFrame = 0;

					while( pXmlReader->moveToNextAttribute() )
					{
						if( KsStrCmp( pXmlReader->getName(), "id" ) )
						{
							keyFrameID = atoi( pXmlReader->getValue() );
						}
						else if( KsStrCmp( pXmlReader->getName(), "count" ) )
						{
							numKeyFrame = atoi( pXmlReader->getValue() );
						}
					}

					while( !(ksXmlEndElement == pXmlReader->getNodeType() && KsStrCmp( pXmlReader->getName(), "keyframe_array" )) )
					{
						pXmlReader->read();

						if( ksXmlElement == pXmlReader->getNodeType() )
						{
						if( KsStrCmp( pXmlReader->getName(), "keyframe" ) )
						{

							KsCellAnimKeyFrame*		pKeyFrame = new KsCellAnimKeyFrame();

							KsAnim2DPart*	pPart = new KsAnim2DPart();

							while( !(ksXmlEndElement == pXmlReader->getNodeType() && KsStrCmp( pXmlReader->getName(), "keyframe" )) )
							{
								if( ksXmlElement == pXmlReader->getNodeType() )
								{
									if( KsStrCmp( pXmlReader->getName(), "frame" ) )
									{
										pXmlReader->read();
										pKeyFrame->m_frame = atoi( pXmlReader->getValue() );
										pXmlReader->read();
									}
									else if( KsStrCmp( pXmlReader->getName(), "size" ) )
									{
										pXmlReader->read();
										sscanf( pXmlReader->getValue(), "%f %f %f %f", &pPart->m_x, &pPart->m_y, &pPart->m_w, &pPart->m_h );
										pXmlReader->read();
									}
									else if( KsStrCmp( pXmlReader->getName(), "tex_coord" ) )
									{
										pXmlReader->read();
										sscanf( pXmlReader->getValue(), "%f %f %f %f", &pPart->m_u0, &pPart->m_v0, &pPart->m_u1, &pPart->m_v1 );
										pXmlReader->read();
									}
								}
								pXmlReader->read();
							}
							pKeyFrame->m_vpParts.push_back( pPart );
							m_vpKeyFrames.push_back( pKeyFrame );

						}
						}
					}
				}
				break;
			}
			case ksXmlText:
			{
				break;
			}
			case ksXmlEndElement:
			{
				break;
			}
			case ksXmlDeclaration:
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}

	ksDELETE( pXmlReader );

	return ksTRUE;
}

void KsCellAnim2D::update()
{
	if( !m_nextFrame )
	{
		m_nextFrame = m_vpKeyFrames[ 1 ]->m_frame;
	}

	++m_frame;

	if( m_frame == m_nextFrame )
	{
		if( m_frame == m_end )
		{
			m_frame     = 0;
			m_nextFrame = m_vpKeyFrames[ 1 ]->m_frame;
			m_drawFrame = 0;
		}
		else
		{
			++m_drawFrame;

			if( (m_drawFrame + 1)== m_vpKeyFrames.size() )
			{
				m_nextFrame = m_end;
			}
			else
			{
				m_nextFrame = m_vpKeyFrames[ m_drawFrame + 1 ]->m_frame;
			}
		}
	}
}

void KsCellAnim2D::draw( KsRenderSystem* pRS )
{
	//pRS->setRenderState( ksRENDER_STATE_ZTEST_ENABLE, ksFALSE );
	KsCellAnimKeyFrame*		pKeyFrame = m_vpKeyFrames[ m_drawFrame ];
	KsTexture*				pTexture  = m_vpTextures[ 0 ];
	KsAnim2DPart*			pPart     = pKeyFrame->m_vpParts[ 0 ];

	pRS->drawRectEx(	pPart->m_x + m_pos.x,  pPart->m_y + m_pos.y,  pPart->m_w,  pPart->m_h,
						pPart->m_u0, pPart->m_v0, pPart->m_u1, pPart->m_v1,
						pPart->m_color,
						pTexture );
}
