/*************************************************************************************************/
/** 
 * @file	KsWindowParam.cpp
 * @brief	�E�C���h�E�p�����[�^
 * @author	Tukasa Kato
 * @date	2003/03/22
 * @since	----/--/--
 * @version	1.0.0
 */
/*************************************************************************************************/

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                             */
/*===============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsEngine/win/KsWindowParam.h"

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/


/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsWindowParam::KsWindowParam()
	: m_caption( _T("KsSystem") )
	, m_className( _T("KsDefault") )
	, m_posX( 0 )
	, m_posY( 0 )
	, m_sizeX( ksWINDOW_DEFAULT_SIZE_X )
	, m_sizeY( ksWINDOW_DEFAULT_SIZE_Y )
	, m_style( ksWINDOW_DEFAULT_STYLE )
	, m_styleEx( 0 )
{
}

/************************************************************************************************/
/*
 * �����t���R���X�g���N�^
 * @param		caption			�L���v�V����
 * @param		className		�o�^����N���X�l�[��
 * @param		sizeX			�E�C���h�E�̕�
 * @param		sizeY			�E�C���h�E�̍���
 * @param		style			�E�C���h�E�̃X�^�C��
 */
/************************************************************************************************/
KsWindowParam::KsWindowParam( const KsString& caption, const KsString& className, KsInt32 posX, KsInt32 posY, KsInt32 sizeX, KsInt32 sizeY, KsUInt32 style, KsUInt32 styeleEx )
	: m_caption( caption )
	, m_className( className )
	, m_posX( posX )
	, m_posY( posY )
	, m_sizeX( sizeX )
	, m_sizeY( sizeY )
	, m_style( style )
	, m_styleEx( styeleEx )
{
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsWindowParam::~KsWindowParam()
{
}

/************************************************************************************************/
/*
 * �p�����[�^���Z�b�g����
 * @param		caption			�L���v�V����
 * @param		className		�o�^����N���X�l�[��
 * @param		sizeX			�E�C���h�E�̕�
 * @param		sizeY			�E�C���h�E�̍���
 * @param		style			�E�C���h�E�̃X�^�C��
 */
/************************************************************************************************/
void KsWindowParam::setParam( const KsString& caption, const KsString& className, KsInt32 posX, KsInt32 posY, KsInt32 sizeX, KsInt32 sizeY, KsUInt32 style, KsUInt32 styleEx  )
{
	m_caption   = caption;
	m_className = className;
	m_posX      = posX;
	m_posY      = posY;
	m_sizeX     = sizeX;
	m_sizeY     = sizeY;
	m_style     = style;
	m_styleEx   = styleEx;
}


