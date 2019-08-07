/************************************************************************************************/
/** 
 * @file		KsTestScene.cpp
 * @brief		テストシーン
 * @author		Tsukasa Kato
 * @date		2011/07/02
 * @since		2011/07/02
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << ワーニング抑制 >>                                          */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/game/scene/KsTestScene.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsTestScene::KsTestScene()
	: KsScene( ksSCENE_TEST_RENDER, 0, 0 )
{
	//KsLoadPMXFile( "D:\\MMD_Data\\Tda式初音ミク・アペンドVer1.00\\Tda式初音ミク・アペンド_Ver1.00.pmx" );
	//KsModelCreateFromPMX( ".\\Actor\\usausa\\usausa.pmx" );
	//KsString			BG0_InFilePath  = "D:\\KGDC\\Aria\\data\\Model\\bg\\khBG3_a.pmd";
	//KsString			BG0_OutFilePath = "D:\\KGDC\\Aria\\data\\Model\\bg\\khBG3_a.kmd";
	//KsString			BG0_InFilePath  = "D:\\KGDC\\Aria\\data\\Model\\bg\\khBG3_b.pmd";
	//KsString			BG0_OutFilePath = "D:\\KGDC\\Aria\\data\\Model\\bg\\khBG3_b.kmd";
	//KsString			BG0_InFilePath  = "D:\\KGDC\\Aria\\data\\Model\\bg\\khBG3_c.pmd";
	//KsString			BG0_OutFilePath = "D:\\KGDC\\Aria\\data\\Model\\bg\\khBG3_c.kmd";

	//KsString			BG0_InFilePath  = "D:\\Data\\Model\\Miku01\\miku01.pmd";
	//KsString			BG0_OutFilePath = "D:\\Data\\Model\\Miku01\\miku01.kmd";

	//KsModelConvertOption	opt;
	//KsModelConvertFromPMD( BG0_InFilePath, BG0_OutFilePath, opt );

	//KsString			PMDFilePath     = "D:\\MMD\\usausa.pmd";

	//ksNew KsPMDActorReader( PMDFilePath );

	m_font.create( L"E:\\KGDC_SourceCode\\Aria\\Data\\Font\\normal.fnt" );

	KsString			BG1_PMDFilePath = "E:\\KGDC\\Aria\\data\\Model\\bg\\khBG3_a.kmd";
	//KsString			BG2_PMDFilePath = "D:\\KGDC\\Aria\\data\\Model\\bg\\khBG3_b.kmd";
	//KsString			BG3_PMDFilePath = "D:\\KGDC\\Aria\\data\\Model\\bg\\khBG3_c.kmd";

	ksNew KsPMDModelReader( BG1_PMDFilePath );
	//ksNew KsModelReader( BG2_PMDFilePath );
	//ksNew KsModelReader( BG3_PMDFilePath );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsTestScene::~KsTestScene()
{
}

/************************************************************************************************/
/*
 * 更新処理
 * @param		pParam				パラメータ
 */
/************************************************************************************************/
void* KsTestScene::update( void* pParam )
{
	return pParam;
}

/************************************************************************************************/
/*
 * 描画処理
 * @param		pParam				パラメータ
 */
/************************************************************************************************/
void* KsTestScene::draw( void* pParam )
{
	KsGameSystem*	pGameSystem = KsGameSystem::getInstancePtr();
	KsGraphics*		pGraphics   = KsGraphics::getInstancePtr();

	//ksDEBUG_PRINT( 10, 10, "a[];axABb" );
	
	//m_pRenderContext->setBlendState( m_pBlendState, 0, 0xFFFFFFFF );
	//pGraphics->drawSprite( KsDebugFontManager::getInstancePtr()->getTexture(),   0,   0, 640, 360 );

	const KsInt32 width  = pGameSystem->getWindowWidth();
	const KsInt32 height = pGameSystem->getWindowHeight() / 15;

	pGraphics->setColorRect( 1.0f, 0.0f, 0.0f, 1.0f );
	pGraphics->drawRect( 0, 500, width, height );

	//pGraphics->drawSprite( m_font.getTexture(), 0, 200, 256, 112 );

	KsInt32		px = 120;
	KsInt32		py = 200;
	m_font.drawString( L"Aria Scene Select", px, py ); py += 20;
	m_font.drawString( L"Model Select", px, py ); py += 20;
	m_font.drawString( L"Stage Select", px, py ); py += 20;

	return pParam;
}


