/************************************************************************************************/
/**
 * @file	KsMemoryManager.h
 * @brief	�������[�Ǘ�
 * @author	Tsukasa Kato
 * @date	2004/03/30
 * @version	1.0.0
 */
/************************************************************************************************/
#ifndef __KSMEMORYMANAGER_H__
#define __KSMEMORYMANAGER_H__

/*==============================================================================================*/
/*									<< �C���N���[�h >>											*/
/*==============================================================================================*/

/*==============================================================================================*/
/*										<< ��` >>												*/
/*==============================================================================================*/
#ifndef KS_NORMAL_MEMORY_MANAGER
	#undef new
	#undef DEBUG_NEW
#endif 
	
/*==============================================================================================*/
/*										<< �錾 >>												*/
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsMemoryManager
 * @brief		�������[�Ǘ�
 * @author		Tsukasa Kato
 * @todo		�w��T�C�Y�ȉ��͌Œ�ꏊ���g���悤�ɂ���
 */
/************************************************************************************************/
class ksENGINE_API KsMemoryManager
{
	public:
		/**
		 * �������[���m�ۂ���(malloc)
		 * @param		KsSize				�m�ۂ��郁�����[�̃T�C�Y
		 * @param		pszFile				�t�@�C����
		 * @param		line				�t�@�C���̉��s�ڂ��̍s��
		 * @return							�m�ۂ����������[�̃A�h���X
		 */
		static void*						KsMalloc( KsSize size, KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc );

		/**
		 * �������[���m�ۂ���(calloc)
		 * @param		KsSize				�m�ۂ��郁�����[�̃T�C�Y
		 * @param		pszFile				�t�@�C����
		 * @param		line				�t�@�C���̉��s�ڂ��̍s��
		 * @return							�m�ۂ����������[�̃A�h���X
		 */
		static void*						KsCalloc( KsSize size, KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc );

		/**
		 * �������[���m�ۂ���(ralloc)
		 * @param		pAddress			�m�ۃA�h���X
		 * @param		KsSize				�m�ۂ��郁�����[�̃T�C�Y
		 * @param		pszFile				�t�@�C����
		 * @param		line				�t�@�C���̉��s�ڂ��̍s��
		 * @return							�m�ۂ����������[�̃A�h���X
		 */
		static void*						KsRealloc( void* pAddress, KsSize size, KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc );

		/**
		 * �������[���J������(free)
		 * @param		pAddress			�J�����郁�����[�̃A�h���X
		 */
		static void							KsFree( void* pAddress );

		/**
		 * �������[�̏󋵂��t�@�C���Ƀ_���v���܂�
		 */
		static void							dump();

		/**
		 * �^�O�����X�^�b�N��Push���ăZ�b�g����
		 * @param		pTagName			�^�O��
		 */
		static void							pushTag( const KsChar* pTagName );

		/**
		 * �^�O����Pop����
		 */
		static void							popTag();

		/**
		 * �������[�m�ۊ֐����Ă΂��t�@�C�����Ɖ��s�ڂ����Z�b�g����
		 * @param		pszFile				�t�@�C����
		 * @param		line				�t�@�C���̉��s�ڂ��̍s��
		 */
		static void							SetCallFile( KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc );

		/**
		 * new ���Z�q�I�[�o�[���[�h
		 */
		friend void*						operator new   ( KsSize size );

		/**
		 * new[] ���Z�q�I�[�o�[���[�h
		 */
		friend void*						operator new[] ( KsSize size );

		/**
		 * delete ���Z�q�I�[�o�[���[�h
		 */
		friend void							operator delete   ( void* pAddress );

		/**
		 * delete[] ���Z�q�I�[�o�[���[�h
		 */
		friend void							operator delete[] ( void* pAddress );

	protected:
		/**
		 * �������[���m�ۂ���
		 * @param		KsSize				�m�ۂ��郁�����[�̃T�C�Y
		 * @param		type				�m�ۂ��郁�����[�̃^�C�v
		 * @param		pszFile				�t�@�C����
		 * @param		line				�t�@�C���̉��s�ڂ��̍s��
		 * @return							�m�ۂ����������[�̃A�h���X
		 */
		static void*						allocator( KsSize size, KsUInt32 type, KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc );
	
		/**
		 * �������[���J������
		 * @param		pAddress			�J�����郁�����[�̃A�h���X
		 * @param		type				�J�����郁�����[�̃^�C�v
		 */
		static void							deallocator( void* pAddress, KsUInt32 type );

		/**
		 * �w�肳�ꂽ�A�h���X�̃������[���j�b�g��������
		 * @param		pAddress			�m�ۂ����������[�̃T�C�Y
		 * @return							�w�胁�������g�p���Ă��郁�����[���j�b�g�̃A�h���X
		 */
		static KsMemoryUnit*				findAllocUnit( const void* pAddress );

		/**
		 * ���A�h���X����v�����ꂽ�A�h���X�����߂�
		 * @param		pActualAddress	
		 * @return							�v�����ꂽ�A�h���X
		 */
		static void*						computeRequestAddress( const void* pActualAddress );

		/**
		 * ���Z�b�g����
		 */
		static void							reset();

	protected:
		static KsMemoryUnit*				m_pHashTable[ ksMEMORY_HASH_SIZE ];	/**< �n�b�V���e�[�u��					*/
		static KsUInt32						m_currentAllocCount;				/**< ���݂̃������[�m�ۃJ�E���g		*/
		static KsUInt32						m_breakOnAllocCount;				/**< �J���������[�J�E���g				*/
		static KsUInt32						m_sourceLine;						/**< �\�[�X�t�@�C���̉��s�ڂ�			*/
		static KsChar*						m_sourceFile;						/**< �\�[�X�t�@�C����					*/
		static KsChar*						m_funcName;							/**< �֐���							*/
		static KsMemoryUnit*				m_pReservoir;						/**< �������Ǘ��̃��j�b�g���X�g		*/
		static KsMemoryUnit**				m_ppReservoirBuffer;				/**< �������[���j�b�g�̃o�b�t�@		*/
		static KsUInt32						m_reservoirBufferSize;				/**< �o�b�t�@������m�ۂ��Ȃ�������	*/
		static KsMemoryState				m_state;							/**< �������[�X�e�[�^�X				*/
		static KsInt32						m_tagCount;							/**< �^�O�X�^�b�N�ʒu					*/
		static KsInt32						m_zeroAlloc;						/**< �T�C�Y�O�m�ۗp					*/
		static KsCriticalSection			m_cs;								/**< �N���e�B�J���Z�N�V����			*/
		static KsChar						m_tagNameStack[ ksMEMORY_TAG_STACK_SIZE ][ ksMEMORY_NAME_SIZE ];
		static KsChar						m_nowTagName[ ksMEMORY_NAME_SIZE ];
};

#ifndef KS_NORMAL_MEMORY_MANAGER

/************************************************************************************************/
/*
 * �������[�m��(new)
 */
/************************************************************************************************/
inline void*	operator new ( KsSize size )
{
	return KsMemoryManager::allocator( size, ksALLOC_TYPE_NEW, KsMemoryManager::m_sourceLine, KsMemoryManager::m_sourceFile, KsMemoryManager::m_funcName );
}

/************************************************************************************************/
/*
 * �������[�m��(new[])
 */
/************************************************************************************************/
inline void*	operator new[] ( KsSize size )
{
	return KsMemoryManager::allocator( size, ksALLOC_TYPE_NEW_ARRAY, KsMemoryManager::m_sourceLine, KsMemoryManager::m_sourceFile, KsMemoryManager::m_funcName );
}

/************************************************************************************************/
/*
 * �������[��@(delete)
 */
/************************************************************************************************/
inline void	operator delete ( void* pAddress )
{
	KsMemoryManager::deallocator( pAddress, ksALLOC_TYPE_DELETE );
}

/************************************************************************************************/
/*
 * �������[��@(delete[])
 */
/************************************************************************************************/
inline void	operator delete[] ( void* pAddress ) 
{
	KsMemoryManager::deallocator( pAddress, ksALLOC_TYPE_DELETE_ARRAY );
}

/************************************************************************************************/
/*								<< �������[�֐��u������ >>										*/
/************************************************************************************************/
#define	new				( KsMemoryManager::SetCallFile( __LINE__, _T(__FILE__), _T(__FUNCTION__) ), ksFALSE ) ? 0 : new
#define	delete			( KsMemoryManager::SetCallFile( __LINE__, _T(__FILE__), _T(__FUNCTION__) ), ksFALSE ) ? KsMemoryManager::SetCallFile( 0, _T("??"), _T("??") ) : delete
#define	malloc( s )		( KsMemoryManager::KsMalloc( s, __LINE__, _T(__FILE__), _T(__FUNCTION__) ) )
#define	calloc( s )		( KsMemoryManager::KsCalloc( s, __LINE__, _T(__FILE__), _T(__FUNCTION__) ) )
#define	realloc( p, s )	( KsMemoryManager::KsRalloc( s, p, __LINE__, _T(__FILE__), _T(__FUNCTION__) ) )
#define	free( p )		( KsMemoryManager::KsFree( p ) )

#define	ksNew			( KsMemoryManager::SetCallFile( __LINE__, _T(__FILE__), _T(__FUNCTION__) ), ksFALSE ) ? 0 : new
#define	ksDelete		( KsMemoryManager::SetCallFile( __LINE__, _T(__FILE__), _T(__FUNCTION__) ), ksFALSE ) ? KsMemoryManager::SetCallFile( 0, _T("??"), _T("??") ) : delete

#endif

/************************************************************************************************/
/**
 * �������[���[�N�`�F�b�N�֐�
 * @note	�������[���[�N��memoryLeaks.log �t�@�C���Ƀ_���v����
 */
/************************************************************************************************/
#ifdef DEBUG
	#define KsDumpMemoryLeaks()			KsMemoryManager::dump()
	#define KsMemPushTag( pTagName )	KsMemoryManager::pushTag( pTagName );
	#define KsMemPopTag()				KsMemoryManager::popTag();
#else
	#define KsDumpMemoryLeaks()
	#define KsMemPushTag( pTagName )
	#define KsMemPopTag()
#endif



#endif	/* __KSMEMORYMANAGER_H__ */


