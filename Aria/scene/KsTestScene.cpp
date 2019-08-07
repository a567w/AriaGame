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
#include "KsGamePreCompile.h"
#include "KsTestScene.h"

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
	KsModelCreateFromPMX( ".\\Actor\\usausa\\usausa.pmx" );
	//KsString			BG0_InFilePath  = "D:\\KGDC\\Aria\\data\\Model\\bg\\khBG3_a.pmd";
	//KsString			BG0_OutFilePath = "D:\\KGDC\\Aria\\data\\Model\\bg\\khBG3_a.kmd";
	//KsString			BG0_InFilePath  = "D:\\KGDC\\Aria\\data\\Model\\bg\\khBG3_b.pmd";
	//KsString			BG0_OutFilePath = "D:\\KGDC\\Aria\\data\\Model\\bg\\khBG3_b.kmd";
	//KsString			BG0_InFilePath  = "D:\\KGDC\\Aria\\data\\Model\\bg\\khBG3_c.pmd";
	//KsString			BG0_OutFilePath = "D:\\KGDC\\Aria\\data\\Model\\bg\\khBG3_c.kmd";

	KsString			BG0_InFilePath  = "D:\\Data\\Model\\Miku01\\miku01.pmd";
	KsString			BG0_OutFilePath = "D:\\Data\\Model\\Miku01\\miku01.kmd";

	KsModelConvertOption	opt;
	KsModelConvertFromPMD( BG0_InFilePath, BG0_OutFilePath, opt );

	KsString			PMDFilePath     = "D:\\MMD\\usausa.pmd";

	ksNew KsPMDActorReader( PMDFilePath );

	KsString			BG1_PMDFilePath = "D:\\KGDC\\Aria\\data\\Model\\bg\\khBG3_a.kmd";
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
	return pParam;
}


