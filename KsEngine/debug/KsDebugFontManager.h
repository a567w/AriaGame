/************************************************************************************************/
/** 
 * @file		KsDebugFontManager.h
 * @brief		�f�o�b�N�p�t�H���g�\������
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSDEBUGFONTMANAGER_H__
#define __KSDEBUGFONTMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsDebugFontManager
 * @brief		�f�o�b�N�p�t�H���g�}�l�[�W���N���X
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class ksENGINE_API KsDebugFontManager : public KsSingleton< KsDebugFontManager >
{
	public:
		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return						�V���O���g���̎Q��
		 */
		static KsDebugFontManager&		getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return						�V���O���g���̃|�C���^
		 */
		static KsDebugFontManager*		getInstancePtr();

	public:
		/**
		 * �R���X�g���N�^
		 * @param	pFullPath			�t�H���g�t���p�X
		 */
										KsDebugFontManager( const KsChar* pFullPath );

		/**
		 * �R���X�g���N�^
		 * @param	pTexture			�t�H���g�e�N�X�`��	
		 */
										KsDebugFontManager( KsTexture* pTexture );

		/**
		 * �f�X�g���N�^
		 */
										~KsDebugFontManager();

		/**
		 * �f�o�b�N�������\������
		 */
		void							print( KsInt32 x, KsInt32 y, const KsChar* format, ... );

		/**
		 * �f�o�b�N�������\������
		 */
		void							print( const KsChar* format, ... );

		/**
		 * �f�o�b�N�������\������
		 */
		void							flush();

	public:
		KsTexture*						getTexture() { return m_pTexture; }

	private:
		KsDebugFont						m_fontWork[ 256 ];	/**< */
		KsTexture*						m_pTexture;			/**< */
		KsInt32							m_count;			/**< */
		KsInt32							m_px;				/**< */
		KsInt32							m_py;				/**< */
		KsInt32							m_line;
};

#ifndef MASTER
	#define ksDEBUG_INIT( pTex )	if( !KsDebugFontManager::getInstancePtr() ){  new KsDebugFontManager( pTex ); }
	#define ksDEBUG_FLUSH()			if( KsDebugFontManager::getInstancePtr() ){  KsDebugFontManager::getInstance().flush(); }
	#define ksDEBUG_PRINT			KsDebugFontManager::getInstance().print
	#define ksDEBUG_TERM()			if( KsDebugFontManager::getInstancePtr() ) { delete KsDebugFontManager::getInstancePtr(); }
#else
	#define ksDEBUG_INIT( _pRS )	
	#define ksDEBUG_FLUSH()		
	#define ksDEBUG_PRINT			
	#define ksDEBUG_TERM()
#endif //#ifndef MASTER

#endif /* __KSDEBUGFONTMANAGER_H__ */
