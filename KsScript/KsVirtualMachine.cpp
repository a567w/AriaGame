/************************************************************************************************/
/** 
 * @file		KsVirtualMachine.cpp
 * @brief		�o�[�`�����}�V��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsScript/KsScriptPreCompile.h"
#include "KsVirtualMachine.h"
#include "KsScriptFormat.h"
#include "KsIntermediateCode.h"
#include "KsScriptCalculate.h"


/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsVirtualMachine::KsVirtualMachine()
	: m_id( 0 )
	, m_pos( 0 )
	, m_end( 0 )
	, m_variableStackSize( 0 )
	, m_structMemberBlockSize( 0 )
	, m_handleListBlockSize( 0 )
	, m_pHandleManager( 0 )
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsVirtualMachine::KsVirtualMachine( KsUInt32 variableStackSize, KsUInt32 structMemberBlockSize, KsUInt32 handleListBlockSize )
	: m_id( 0 )
	, m_pos( 0 )
	, m_end( 0 )
	, m_variableStackSize( 0 )
	, m_structMemberBlockSize( 0 )
	, m_handleListBlockSize( 0 )
{
	initialize( variableStackSize, structMemberBlockSize, handleListBlockSize );
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsVirtualMachine::~KsVirtualMachine()
{
	shutdown();
}


/************************************************************************************************/
/*
 * �X�N���v�g�G���W���̏���������
 */
/************************************************************************************************/
KsBool KsVirtualMachine::initialize( KsUInt32 variableStackSize, KsUInt32 structMemberBlockSize, KsUInt32 handleListBlockSize )
{
	m_pHandleManager = new KsHandleManager();
	m_variables      = new KsVariable[ variableStackSize ];

	m_structMemberBlock.create( sizeof(KsStructMemberInfo), structMemberBlockSize, 1 );

	m_handleListBlock.create( sizeof(KsHandleList), handleListBlockSize, 1 );

	m_variableStackSize     = variableStackSize;
	m_structMemberBlockSize = structMemberBlockSize;
	m_handleListBlockSize   = handleListBlockSize;

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �V���b�g�_�E������
 */
/************************************************************************************************/
KsBool KsVirtualMachine::shutdown()
{
	ksDELETE( m_pHandleManager );
	ksDELETEARRAY( m_variables );

	m_structMemberBlock.destroy();
	m_handleListBlock.destroy();

	return ksTRUE;
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsStructMemberInfo* KsVirtualMachine::allocStructMemberBlock()
{
	KsStructMemberInfo*		pData = (KsStructMemberInfo*)m_structMemberBlock.KsAlloc();
	memset( pData, 0, sizeof( KsStructMemberInfo ) );
	return pData;
}
/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsHandleList* KsVirtualMachine::allocHandleListBlock()
{
	KsHandleList*		pData = (KsHandleList*)m_handleListBlock.KsAlloc();
	memset( pData, 0, sizeof( KsHandleList ) );
	return pData;
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsInt32  KsVirtualMachine::findFreeID()
{
	KsInt32   id = 0;

	while( 1 )
	{
		id = m_id;

		for( KsUInt32 i=0; i<m_vpScripts.size(); i++ )
		{
			if( m_vpScripts[ i ]->getID() == id )
			{
				++m_id;
				break;	
			}
		}

		if( id == m_id )
		{
			return id;
		}
	}

	return -1;
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsScript* KsVirtualMachine::findScript( KsInt32 id )
{
	for( KsUInt32 i=0; i<m_vpScripts.size(); i++ )
	{
		if( m_vpScripts[ i ]->getID() == id )
		{
			return m_vpScripts[ i ];
		}
	}

	return NULL;
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsInt32 KsVirtualMachine::loadScriptFile( KsFileObject* pFile )
{
	KS_SCRIPT_FILE_HEADER		header;
	KS_SCRIPT_INFO_HEADER		info;
	KsUInt16					len;
	KsUInt16					len2;
	KsUInt16					next;
	KsUInt32					num;
	KsUInt32					offset;
	KsUInt32					size;
	KsChar						buffer[ 1024 ];
	KsChar*						pCode;
	KsHandle					stringHandle;
	KsHandle					globalHandle;
	KsHandle					structHandle;
	KsHandleList*				pHandleList;
	KsScript*					pScript;

	pScript = new KsScript();

	/* �w�b�_�[�ǂݍ��� */
	pFile->read( &header, sizeof(KS_SCRIPT_FILE_HEADER) );

	/* ��񕔓ǂݍ��� */
	pFile->read( &info, sizeof(KS_SCRIPT_INFO_HEADER) );

	/* �X�N���v�g�t�@�C������ǂݍ��� */
	pFile->read( &len, sizeof(KsUInt16) );
	len = ( ( len + 3 ) & ~3 );
	pFile->read( buffer, len );
	buffer[ len ]   = '\0';
	pScript->m_name = buffer;

	/* �R�[�h���擾���� */
	pFile->seek( header.offsetCode, SEEK_SET );
	pFile->read( &size, sizeof(KsUInt32) );
	pCode = new KsChar[ size ];
	pFile->read( pCode, size );
	pScript->m_pCode = pCode;

	/* ��������Z�b�g���� */
	// ������I�u�W�F�N�g��ǉ�����
	pFile->seek( info.offsetString, SEEK_SET );

	for( KsUInt32 i=0; i<info.numString; i++ )
	{
		pFile->read( &len,  sizeof(KsUInt16) );
		pFile->read( &next, sizeof(KsUInt16) );
		pFile->read( &num,  sizeof(KsUInt32) );

		len2 = ( ( len + 3 ) & ~3 );

		pFile->read( buffer, len2 );
		buffer[ len ] = '\0';

		/* �n���h�����X�g��ǉ�����(�������Ă��łɓo�^����Ă�����Q�ƃJ�E���g���A�b�v�����) */
		//--------------------------------------------------------------------------------
		stringHandle = KsCreateStringHandle( m_pHandleManager, buffer );
		pHandleList  = allocHandleListBlock();

		pHandleList->handle = stringHandle;

		if( pScript->m_pStringHandleList )
		{
			pHandleList->next = pScript->m_pStringHandleList;
		}

		pScript->m_pStringHandleList = pHandleList;
		
		//--------------------------------------------------------------------------------

		for( KsUInt32 j=0; j<num; j++ )
		{
			pFile->read( &offset,  sizeof(KsUInt32) );
			/* �R�[�h�̒l��ϊ����� */
			KsHandle*	pBuf = (KsHandle*)&pCode[ offset ];
			*pBuf = stringHandle;
		}
	}

	/* �O���[�o���ϐ����Z�b�g���� */
	pFile->read( &info.offsetGlobal, SEEK_SET );
	for( KsUInt32 i=0; i<info.numGlobal; i++ )
	{
		pFile->read( &len,  sizeof(KsUInt16) );
		pFile->read( &next, sizeof(KsUInt16) );
		pFile->read( &num,  sizeof(KsUInt32) );

		len2 = ( ( len + 3 ) & ~3 );

		pFile->read( buffer, len2 );
		buffer[ len ] = '\0';

		/* �n���h�����X�g��ǉ�����(�������Ă��łɓo�^����Ă�����Q�ƃJ�E���g���A�b�v�����) */
		//--------------------------------------------------------------------------------
		globalHandle = KsCreateGlobalHandle( m_pHandleManager, buffer );
		pHandleList  = allocHandleListBlock();

		pHandleList->handle = globalHandle;

		if( pScript->m_pGlobalHandleList )
		{
			pHandleList->next = pScript->m_pGlobalHandleList;
		}

		pScript->m_pGlobalHandleList = pHandleList;
		//--------------------------------------------------------------------------------

		/* �z�񂩂ǂ������`�F�b�N���� */
		if( buffer[ 0 ] == '@' )
		{
			KsChar			temp[ 1024 ];
			KsInt32		count = 1;
			
			while( buffer[ count ] != '@' )
			{
				++count;
			}
			--count;
			strncpy( temp, &buffer[ 1 ], count );
			temp[ count ] = '\0';

			/* �z��̐擪��T���ă����N���� */
			KsGlobalObject*		pParent = KsGetGlobalObject( m_pHandleManager, temp );
			KsGlobalObject*		pObject = KsGetGlobalObject( m_pHandleManager, buffer );
			pObject->m_pNext = pParent->m_pNext;
			pParent->m_pNext = pObject;
		}

		/* �O���[�o���ϐ���o�^���� */
		for( KsUInt32 j=0; j<num; j++ )
		{
			pFile->read( &offset,  sizeof(KsUInt32) );
			/* �R�[�h�̒l��ϊ����� */
			KsHandle*	pBuf = (KsHandle*)&pCode[ offset ];
			*pBuf = globalHandle;
		}
	}

	/* �֐��ϐ����Z�b�g���� */
	pFile->seek( info.offsetFunc, SEEK_SET );
	for( KsUInt32 i=0; i<info.numFunc; i++ )
	{
		KsUInt32	flags;
		KsUInt32	handle;
		KsUInt16	numArg;
		KsUInt16	numLocal;
		KsUInt32	codeSize;
		KsUInt32	codeOffset;
		KsChar		funcName[ 1024 ];

		pFile->read( &flags,      sizeof(KsUInt32) );
		pFile->read( &handle,     sizeof(KsUInt32) );
		pFile->read( &numArg,     sizeof(KsUInt16) );
		pFile->read( &numLocal,   sizeof(KsUInt16) );
		pFile->read( &codeSize,   sizeof(KsUInt32) );
		pFile->read( &codeOffset, sizeof(KsUInt32) );
		pFile->read( &len,        sizeof(KsUInt16) );
		pFile->read( &next,       sizeof(KsUInt16) );

		pFile->read( funcName, len );
		funcName[ len ] = '\0';

		KsGlobalObject*		pObject = (KsGlobalObject*)KsCreateGlobalHandle( m_pHandleManager, funcName );

		/* �n���h�����Z�b�g���� */
		pObject->m_variable.m_type    = ksVALUE_FUNCTION;
		pObject->m_variable.m_value.h = pObject->getHandle();

		/* �n���h�����X�g��ǉ����� */
		//--------------------------------------------------------------------------------
		pHandleList  = allocHandleListBlock();

		pHandleList->handle = pObject->getHandle();

		if( pScript->m_pGlobalHandleList )
		{
			pHandleList->next = pScript->m_pGlobalHandleList;
		}

		pScript->m_pGlobalHandleList = pHandleList;
		//--------------------------------------------------------------------------------

		for( KsUInt32 j=0; j<numLocal; j++ )
		{
			pFile->read( &len,  sizeof(KsUInt16) );
			pFile->read( &next, sizeof(KsUInt16) );
			pFile->read( buffer, len );
			buffer[ len ] = '\0';
		}

		KsFunction*   pFunc = new KsFunction();
		pFunc->m_string		= funcName; 
		pFunc->m_numArg     = numArg;
		pFunc->m_numLocal   = numLocal;
		pFunc->m_codeOffset = codeOffset;
		pFunc->m_codeSize   = codeSize;
		pFunc->m_pCode      = pCode;
		m_vpFunctions.add( funcName, pFunc );

		/* �n���h�����X�g��ǉ����� */
		//--------------------------------------------------------------------------------
		pHandleList  = allocHandleListBlock();

		pHandleList->handle = (KsHandle)pFunc;

		if( pScript->m_pFuncHandleList )
		{
			pHandleList->next = pScript->m_pFuncHandleList;
		}

		pScript->m_pFuncHandleList = pHandleList;
		//--------------------------------------------------------------------------------
	}

	/* �\���̃f�[�^�̎擾 */
	pFile->seek( info.offsetStruct, SEEK_SET );
	for( KsUInt32 i=0; i<info.numStruct; i++ )
	{
		KsUInt16		numVar;
		KsUInt16		numFunc;

		pFile->read( &numVar,   sizeof(KsUInt16) );
		pFile->read( &numFunc,  sizeof(KsUInt16) );

		pFile->read( &len, sizeof(KsUInt16) );

		len2 = ( ( len + 3 ) & ~3 );

		pFile->read( buffer, len2 );
		buffer[ len ] = '\0';

		KsStructObject*		pObject = KsGetStructObject( m_pHandleManager, buffer );
		KsStructMemberInfo*	pTemp;

		/* �n���h�����X�g��ǉ�����(�������Ă��łɓo�^����Ă�����Q�ƃJ�E���g���A�b�v�����) */
		//--------------------------------------------------------------------------------
		structHandle = (KsHandle)pObject;
		pHandleList  = allocHandleListBlock();

		pHandleList->handle = structHandle;

		if( pScript->m_pStructHandleList )
		{
			pHandleList->next = pScript->m_pStructHandleList;
		}

		pScript->m_pStructHandleList = pHandleList;
		//--------------------------------------------------------------------------------

		for( KsUInt16 j=0; j<numVar; j++ )
		{
			pFile->read( &len, sizeof(KsUInt16) );

			len2 = ( ( len + 3 ) & ~3 );

			pFile->read( buffer, len2 );

			buffer[ len ] = '\0';

			// �����o�[�����X�g�łȂ��Ă���
			if( pObject->m_pVarList == NULL )
			{
				pObject->m_pVarList = allocStructMemberBlock();
				pTemp = pObject->m_pVarList;

				strcpy( pTemp->name, buffer );
				pTemp->handle = (KsInt32)j;
			}
			else
			{
				pTemp->next = allocStructMemberBlock();
				pTemp = pTemp->next;

				strcpy( pTemp->name, buffer );
				pTemp->handle = (KsInt32)j;
			}
		}
	}

	pScript->m_id = findFreeID();

	m_vpScripts.push_back( pScript );

	return pScript->getID();
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsBool KsVirtualMachine::unloadScript( KsInt32 id )
{
	KsScript*	pScript = findScript( id );

	if( pScript == NULL )
	{
		return ksFALSE;
	}

	KsHandleList*	pTemp;

	pTemp = pScript->getStringHandleList();

	while( pTemp )
	{
		KsDestoryStringObject( m_pHandleManager, pTemp->handle );
		pTemp = pTemp->next;
	}

	pTemp = pScript->getGlobalHandleList();

	while( pTemp )
	{
		KsDestoryGlobalObject( m_pHandleManager, pTemp->handle );
		pTemp = pTemp->next;
	}

	pTemp = pScript->getStructHandleList();

	while( pTemp )
	{
		KsDestoryStructObject( m_pHandleManager, pTemp->handle );
		pTemp = pTemp->next;
	}

	pTemp = pScript->getFuncHandleList();

	while( pTemp )
	{
		KsFunction*	pFunc = (KsFunction*)KsGetHandleObject( pTemp->handle );
		
		if( pFunc )
		{
			pFunc = m_vpFunctions.destroy( pFunc->getString().c_str() );
			ksDELETE( pFunc );
		}

		pTemp = pTemp->next;
	}

	pScript->destroy();

	ksDELETE( pScript );

	return ksTRUE;	
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsVariable* KsVirtualMachine::callFunc( const KsChar* pFuncName )
{
	KsHashNode<KsFunction*>*	pNode;

	/* �֐������� */
	pNode = m_vpFunctions.find( pFuncName );

	if( pNode )
	{
		KsFunction*		pFunc = pNode->m_pData;

		/* ���̊֐����Ŏg�p����ő�X�^�b�N�T�C�Y���m�ۂ��Ă��� */
		/* �ŏI�I�ɂ����ɖ߂�l�Ƃ����i�[����� */
		++m_pos;

		/* ���[�J���ϐ��̃G���A���m�� */
		pFunc->m_pVariables = &m_variables[ m_pos ];
		m_pos += pFunc->m_numLocal;

		call( pFunc );

		--m_pos;

		return getStackTop();
	}

	return NULL;
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsVariable* KsVirtualMachine::callFunc( const KsChar* pFuncName, KsChar* pArgs, ... )
{
	KsHashNode<KsFunction*>*	pNode;

	/* �֐������� */
	pNode = m_vpFunctions.find( pFuncName );

	if( pNode )
	{
		KsFunction*		pFunc = pNode->m_pData;

		/* ���̊֐����Ŏg�p����ő�X�^�b�N�T�C�Y���m�ۂ��Ă��� */
		/* �ŏI�I�ɂ����ɖ߂�l�Ƃ����i�[����� */
		printf( "stack top %d\n", m_pos );
		++m_pos;

		/* ���[�J���ϐ��̃G���A���m�� */
		pFunc->m_pVariables = &m_variables[ m_pos ];
		m_pos += pFunc->m_numLocal;

		/* �������Z�b�g���鏈�� */
		va_list		list;

		list = va_start( list, pArgs );

		// �����̐������擾����
		KsUInt32	len   = (KsUInt32)strlen( pArgs );
		KsUInt32	index = 0;
		for( KsUInt32 i=0; i<len; i++ )
		{
			if( *pArgs == '%' )
			{
				++pArgs;
				++i;
				switch( *pArgs )
				{
					case 'd':
					{
						KsInt32 value = (KsInt32)va_arg( list, int );
						pFunc->m_pVariables[ index ].setInt( value );
						++index;
						break;
					}
					case 'f':
					{
						KsReal value = (KsReal)va_arg( list, double );
						pFunc->m_pVariables[ index ].setFloat( value );
						++index;
						break;
					}
					default:
					{
						break;
					}
				}
				if( i >= len )
				{
					break;
				}
			}
			++pArgs;
		}

		va_end( list );

		call( pFunc );

		--m_pos;
		printf( "stack top %d\n", m_pos );

		return getStackTop();
	}

	return NULL;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVirtualMachine::call( KsFunction* pFunc )
{
	KsChar*				pCode = (KsChar*)pFunc->m_pCode;
	KsUInt32*			pData = (KsUInt32*)&pCode[ pFunc->m_codeOffset ];
	KsBool				bLoop = ksTRUE;	
	KsStructObject*		pStructObj;
	KsStringObject*		pStringObj;
	KsGlobalObject*		pGlobalObj;
	KsVariable*			pVariables;
	KsHandle			handle;
	KsHandle			handle1;
	KsHandle			handle2;
	KsInt32			varIdx;
	KsInt32			index;
	KsInt32			value;
	KsReal				value_f;

	while( bLoop )
	{
		switch( *pData )
		{
			case ksCMD_ADD:
			{
				KsVariableAdd( &m_variables[ m_pos-2 ], &m_variables[ m_pos-2 ], &m_variables[ m_pos-1 ] );
				--m_pos;
				break;
			}
			case ksCMD_SUB:
			{
				KsVariableSub( &m_variables[ m_pos-2 ], &m_variables[ m_pos-2 ], &m_variables[ m_pos-1 ] );
				--m_pos;
				break;
			}
			case ksCMD_MUL:
			{
				KsVariableMul( &m_variables[ m_pos-2 ], &m_variables[ m_pos-2 ], &m_variables[ m_pos-1 ] );
				--m_pos;
				break;
			}
			case ksCMD_DIV:
			{
				KsVariableDiv( &m_variables[ m_pos-2 ], &m_variables[ m_pos-2 ], &m_variables[ m_pos-1 ] );
				--m_pos;
				break;
			}
			case ksCMD_REM:
			{
				KsVariableRem( &m_variables[ m_pos-2 ], &m_variables[ m_pos-2 ], &m_variables[ m_pos-1 ] );
				--m_pos;
				break;
			}
			case ksCMD_OR:
			{
				KsVariableBitOR( &m_variables[ m_pos-2 ], &m_variables[ m_pos-2 ], &m_variables[ m_pos-1 ] );
				--m_pos;
				break;
			}
			case ksCMD_XOR:
			{
				KsVariableBitXOR( &m_variables[ m_pos-2 ], &m_variables[ m_pos-2 ], &m_variables[ m_pos-1 ] );
				--m_pos;
				break;
			}
			case ksCMD_AND:
			{
				KsVariableBitAND( &m_variables[ m_pos-2 ], &m_variables[ m_pos-2 ], &m_variables[ m_pos-1 ] );
				--m_pos;
				break;
			}
			case ksCMD_PLUS:
			{
				break;
			}
			case ksCMD_MINUS:
			{
				KsVariableMinus( &m_variables[ m_pos-1 ], &m_variables[ m_pos-1 ] );
				break;
			}
			case ksCMD_NOT:
			{
				KsVariableNot( &m_variables[ m_pos-1 ], &m_variables[ m_pos-1 ] );
				break;
			}
			case ksCMD_INV:
			{
				KsVariableInv( &m_variables[ m_pos-1 ], &m_variables[ m_pos-1 ] );
				break;
			}
			case ksCMD_SHL:
			{
				KsVariableShiftLeft( &m_variables[ m_pos-2 ], &m_variables[ m_pos-2 ], &m_variables[ m_pos-1 ] );
				--m_pos;
				break;
			}
			case ksCMD_SHR:
			{
				KsVariableShiftRight( &m_variables[ m_pos-2 ], &m_variables[ m_pos-2 ], &m_variables[ m_pos-1 ] );
				--m_pos;
				break;
			}
			case ksCMD_LT:
			{
				KsVariableLT( &m_variables[ m_pos-2 ], &m_variables[ m_pos-2 ], &m_variables[ m_pos-1 ] );
				--m_pos;
				break;
			}
			case ksCMD_GT:
			{
				KsVariableGT( &m_variables[ m_pos-2 ], &m_variables[ m_pos-2 ], &m_variables[ m_pos-1 ] );
				--m_pos;
				break;
			}
			case ksCMD_LTE:
			{
				KsVariableLTE( &m_variables[ m_pos-2 ], &m_variables[ m_pos-2 ], &m_variables[ m_pos-1 ] );
				--m_pos;
				break;
			}
			case ksCMD_GTE:
			{
				KsVariableGTE( &m_variables[ m_pos-2 ], &m_variables[ m_pos-2 ], &m_variables[ m_pos-1 ] );
				--m_pos;
				break;
			}
			case ksCMD_EQ:
			{
				KsVariableEQ( &m_variables[ m_pos-2 ], &m_variables[ m_pos-2 ], &m_variables[ m_pos-1 ] );
				--m_pos;
				break;
			}
			case ksCMD_NEQ:
			{
				KsVariableNEQ( &m_variables[ m_pos-2 ], &m_variables[ m_pos-2 ], &m_variables[ m_pos-1 ] );
				--m_pos;
				break;
			}
			case ksCMD_CALL:
			{
				++pData;

				/* �����̐����擾 */
				memcpy( &value, pData, sizeof( KsInt32 ) );

				/* �߂�A�h���X���Z�b�g���� */

				/* �֐������擾���� */
				if( m_variables[ m_pos - ( value + 1 ) ].getType() == ksVALUE_INVALID )
				{
					pGlobalObj = (KsGlobalObject*)KsGetHandleObject( m_variables[ m_pos - ( value + 1 ) ].m_value.h );

					KsHashNode<KsScriptLibCallback>*		pNode;

					pNode = m_vpLibraries.find( pGlobalObj->getString().c_str() );

					if( pNode )
					{
						KsScriptLibCallback		func = pNode->m_pData;
						--m_pos;
						(*func)( this );
					}
					else
					{
						printf("not find function\n");
						m_pos -= value;
						break;
					}
				}
				else
				{
					m_pos -= value;

					pGlobalObj = (KsGlobalObject*)KsGetHandleObject( m_variables[ m_pos - 1 ].m_value.h );
				
					KsHashNode<KsFunction*>*		pNode;
					pNode = m_vpFunctions.find( pGlobalObj->getString().c_str() );

					if( pNode )
					{
						KsFunction*		pFuncCall;

						pFuncCall = pNode->m_pData;
						/* ���[�J���ϐ��̃G���A���m�� */
						/* �����̐����X�^�b�N������o���Ĉ����Ƃ��Ă킽�� */
						pFuncCall->m_pVariables = &m_variables[ m_pos ];
						pFuncCall->m_pMembers   = (KsVariable*)m_variables[ m_pos - 1 ].m_type;

						/* �������Z�b�g���鏈�� */
						m_pos += pFuncCall->m_numLocal;

						/* �֐��Ăяo�� */
						call( pFuncCall );
					}
					else
					{
						printf("not find function\n");
						break;
					}

					//printf( "stack top %d\n", m_pos );

					/* �֐����̂Ƃ��낪���x�r�߂�A�h���X������悤�ɂ��� */

					//--m_pos;
					//printf( "stack top %d\n", m_pos );
				}
				break;
			}
			case ksCMD_PUSH_FUNC:
			{
				++pData;
				memcpy( &value, pData, sizeof( KsInt32 ) );
				break;
			}
			case ksCMD_PUSH_STRUCT:
			{
				++pData;
				memcpy( &handle, pData, sizeof( KsHandle ) );

				pStringObj = (KsStringObject*)KsGetHandleObject( handle );
				pStructObj = KsGetStructObject( m_pHandleManager, pStringObj->getString().c_str() );
				
				// �J������
				//if( m_variables[ m_pos ].m_type == ksVALUE_STRCT ){
				//}

				// �X�^�b�N�̋t���犄��U��
				// handle = �X�^�b�N�̃|�C���^
				// stack
				// struct obj handle
				// struct size ���̕ϐ�
				// struct obj �́@�����o�[�{struct �I�u�W�F�N�g�̃n���h���p

				// new �Ŋm�ۂ��Ȃ��悤�ɂ���(MemFix���g���E�E�E)
				KsVariable*		pStack = new KsVariable[ pStructObj->m_numVar + 1 ];
				pStack[ 0 ].m_type             = ksVALUE_STRCT;
				pStack[ 0 ].m_value.h          = (KsHandle)pStructObj;
				m_variables[ m_pos ].m_type    = ksVALUE_STRCT;
				m_variables[ m_pos ].m_value.h = (KsHandle)pStack;

				++m_pos;
				break;
			}
			case ksCMD_GET_MEMBER:
			{
				++pData;
				memcpy( &value, pData, sizeof( KsInt32 ) );

				m_variables[ m_pos ] = pFunc->m_pMembers[ value ];

				++m_pos;
				break;
			}
			case ksCMD_GET_LOCAL:
			{
				++pData;
				memcpy( &value, pData, sizeof( KsInt32 ) );
				/* �X�^�b�N�ɃZ�b�g���� */
				m_variables[ m_pos ] = pFunc->m_pVariables[ value ];
				++m_pos;
				break;
			}
			case ksCMD_GET_LOCAL_ARRAY:
			{
				++pData;
				memcpy( &value, pData, sizeof( KsInt32 ) );

				// �z��̃C���f�b�N�X�擾
				--m_pos;
				index = m_variables[ m_pos ].getInt();

				/* �X�^�b�N�ɃZ�b�g���� */
				m_variables[ m_pos ] = pFunc->m_pVariables[ value + index ];
				++m_pos;
				break;
			}
			case ksCMD_GET_GLOBAL:
			{
				++pData;
				memcpy( &handle, pData, sizeof( KsHandle ) );
				
				/* �n���h������l���擾���� */
				pGlobalObj = (KsGlobalObject*)KsGetHandleObject( handle );

				/* �X�^�b�N�ɃZ�b�g���� */
				m_variables[ m_pos ] = *pGlobalObj->getVariable();

				if( m_variables[ m_pos ].getType() == ksVALUE_INVALID ){
					m_variables[ m_pos ].m_value.h = handle;
				}

				++m_pos;
				break;
			}
			case ksCMD_GET_GLOBAL_ARRAY:
			{
				++pData;
				memcpy( &handle, pData, sizeof( KsHandle ) );
				
				/* �n���h������l���擾���� */
				pGlobalObj = (KsGlobalObject*)KsGetHandleObject( handle );

				// �z��̃C���f�b�N�X�擾
				--m_pos;
				index = m_variables[ m_pos ].getInt();

				// �C���f�b�N�X���i�߂�
				for( KsInt32 i=0; i<index; i++ ){
					//if( pGlobalObj->m_pNext == NULL ){
					//	printf("�z��I�[�o�[\n");
					//}
					pGlobalObj = (KsGlobalObject*)pGlobalObj->m_pNext;
				}

				/* �X�^�b�N�ɃZ�b�g���� */
				m_variables[ m_pos ] = *pGlobalObj->getVariable();
				++m_pos;
				break;
			}
			case ksCMD_SET_LOCAL:
			{
				++pData;
				memcpy( &value, pData, sizeof( KsInt32 ) );
				--m_pos;

				if( pFunc->m_pVariables[ value ].getType() == ksVALUE_STRCT )
				{
					pVariables = (KsVariable*)pFunc->m_pVariables[ value ].m_value.h;
					delete [] pVariables;
				}

				pFunc->m_pVariables[ value ] = m_variables[ m_pos ];
				break;
			}
			case ksCMD_SET_LOCAL_ARRAY:
			{
				++pData;
				memcpy( &value, pData, sizeof( KsInt32 ) );
				
				// �z��̃C���f�b�N�X�擾
				--m_pos;
				index = m_variables[ m_pos ].getInt();

				if( pFunc->m_pVariables[ value + index ].getType() == ksVALUE_STRCT )
				{
					pVariables = (KsVariable*)pFunc->m_pVariables[ value + index ].m_value.h;
					delete [] pVariables;
				}

				// �f�[�^���Z�b�g
				--m_pos;
				pFunc->m_pVariables[ value + index ] = m_variables[ m_pos ];
				break;
			}
			case ksCMD_SET_GLOBAL:
			{
				++pData;
				memcpy( handle, pData, sizeof( KsInt32 ) );

				/* �n���h������l���擾���� */
				pGlobalObj = (KsGlobalObject*)KsGetHandleObject( handle );

				if( pGlobalObj->getVariable()->getType() == ksVALUE_STRCT )
				{
					pVariables = (KsVariable*)pGlobalObj->getVariable()->m_value.h;
					delete [] pVariables;
				}

				--m_pos;
				pGlobalObj->setVariable( m_variables[ m_pos ] );

				/* �X�^�b�N�ɃZ�b�g���� */
				break;
			}
			case ksCMD_SET_GLOBAL_ARRAY:
			{
				++pData;
				memcpy( &handle, pData, sizeof( KsHandle ) );

				/* �n���h������l���擾���� */
				pGlobalObj = (KsGlobalObject*)KsGetHandleObject( handle );

				// �z��̃C���f�b�N�X�擾
				--m_pos;
				index = m_variables[ m_pos ].getInt();

				// �C���f�b�N�X���i�߂�
				for( KsInt32 i=0; i<index; i++ ){
					//if( pGlobalObj->m_pNext == NULL ){
					//	printf("�z��I�[�o�[\n");
					//}
					pGlobalObj = (KsGlobalObject*)pGlobalObj->m_pNext;
				}

				if( pGlobalObj->getVariable()->getType() == ksVALUE_STRCT ){
					pVariables = (KsVariable*)pGlobalObj->getVariable()->m_value.h;
					delete [] pVariables;
				}

				--m_pos;
				pGlobalObj->setVariable( m_variables[ m_pos ] );

				if( m_variables[ m_pos ].getType() == ksVALUE_INVALID )
				{
					m_variables[ m_pos ].m_value.h = handle;
				}
				
				break;
			}
			case ksCMD_SET_MEMBER_LOCAL:
			{
				++pData;
				memcpy( &varIdx, pData, sizeof( KsInt32 ) );

				++pData;
				memcpy( &handle, pData, sizeof( KsInt32 ) );

				--m_pos;

				if( pFunc->m_pVariables[ varIdx ].getType() == ksVALUE_STRCT )
				{
					/* �����o�[�� */
					pStringObj = (KsStringObject*)KsGetHandleObject( handle );

					/* �\���̂̃f�[�^�� */
					pVariables = (KsVariable*)pFunc->m_pVariables[ varIdx ].m_value.h;

					/* �\���̂��擾 */
					pStructObj = (KsStructObject*)KsGetHandleObject( pVariables[ 0 ].m_value.h );

					/* �����o�[�̃C���f�b�N�X���擾 */
					index = pStructObj->findVarIndex( pStringObj->getString().c_str() );

					//if( index < 0 ){ �G���[ }

					if( pVariables[ index + 1 ].getType() == ksVALUE_STRCT )
					{
						KsVariable*		pVariables2 = (KsVariable*)pVariables[ index + 1 ].m_value.h;
						delete [] pVariables2;
					}

					pVariables[ index + 1 ] = m_variables[ m_pos ];
				}
				break;
			}
			case ksCMD_SET_MEMBER_LOCAL_ARRAY:
			{
				++pData;
				memcpy( &varIdx, pData, sizeof( KsInt32 ) );

				++pData;
				memcpy( &handle, pData, sizeof( KsInt32 ) );

				/* �z��̃C���f�b�N�X�擾 */
				--m_pos;
				index    = m_variables[ m_pos ].getInt();
				varIdx += index;

				--m_pos;

				if( pFunc->m_pVariables[ varIdx ].getType() == ksVALUE_STRCT )
				{
					/* �����o�[�� */
					pStringObj = (KsStringObject*)KsGetHandleObject( handle );

					/* �\���̂̃f�[�^�� */
					pVariables = (KsVariable*)pFunc->m_pVariables[ varIdx ].m_value.h;

					/* �\���̂��擾 */
					pStructObj = (KsStructObject*)KsGetHandleObject( pVariables[ 0 ].m_value.h );

					/* �����o�[�̃C���f�b�N�X���擾 */
					index = pStructObj->findVarIndex( pStringObj->getString().c_str() );

					//if( index < 0 ){ �G���[ }

					if( pVariables[ index + 1 ].getType() == ksVALUE_STRCT )
					{
						KsVariable*		pVariables2 = (KsVariable*)pVariables[ index + 1 ].m_value.h;
						delete [] pVariables2;
					}

					pVariables[ index + 1 ] = m_variables[ m_pos ];
				}
				break;
			}
			case ksCMD_SET_MEMBER_GLOBAL:
			{
				++pData;
				memcpy( &handle1, pData, sizeof( KsInt32 ) );

				++pData;
				memcpy( &handle2, pData, sizeof( KsInt32 ) );

				/* �n���h������l���擾���� */
				pGlobalObj = (KsGlobalObject*)KsGetHandleObject( handle1 );

				--m_pos;

				if( pGlobalObj->getVariable()->getType() == ksVALUE_STRCT )
				{
					/* �����o�[�� */
					pStringObj = (KsStringObject*)KsGetHandleObject( handle2 );

					/* �\���̂̃f�[�^�� */
					pVariables = (KsVariable*)pGlobalObj->getVariable()->m_value.h;

					/* �\���̂��擾 */
					pStructObj = (KsStructObject*)KsGetHandleObject( pVariables[ 0 ].m_value.h );

					/* �����o�[�̃C���f�b�N�X���擾 */
					index = pStructObj->findVarIndex( pStringObj->getString().c_str() );

					//if( index < 0 ){ �G���[ }

					if( pVariables[ index + 1 ].getType() == ksVALUE_STRCT )
					{
						KsVariable*		pVariables2 = (KsVariable*)pVariables[ index + 1 ].m_value.h;
						delete [] pVariables2;
					}

					pVariables[ index + 1 ] = m_variables[ m_pos ];
				}

				break;
			}
			case ksCMD_SET_MEMBER_GLOBAL_ARRAY:
			{
				++pData;
				memcpy( &handle1, pData, sizeof( KsInt32 ) );

				++pData;
				memcpy( &handle2, pData, sizeof( KsInt32 ) );

				/* �n���h������l���擾���� */
				pGlobalObj = (KsGlobalObject*)KsGetHandleObject( handle1 );

				/* �z��̃C���f�b�N�X�擾 */
				--m_pos;
				index = m_variables[ m_pos ].getInt();

				// �C���f�b�N�X���i�߂�
				for( KsInt32 i=0; i<index; i++ )
				{
					//if( pGlobalObj->m_pNext == NULL ){
					//	printf("�z��I�[�o�[\n");
					//}
					pGlobalObj = (KsGlobalObject*)pGlobalObj->m_pNext;
				}

				--m_pos;

				if( pGlobalObj->getVariable()->getType() == ksVALUE_STRCT )
				{
					/* �����o�[�� */
					pStringObj = (KsStringObject*)KsGetHandleObject( handle2 );

					/* �\���̂̃f�[�^�� */
					pVariables = (KsVariable*)pGlobalObj->getVariable()->m_value.h;

					/* �\���̂��擾 */
					pStructObj = (KsStructObject*)KsGetHandleObject( pVariables[ 0 ].m_value.h );

					/* �����o�[�̃C���f�b�N�X���擾 */
					index = pStructObj->findVarIndex( pStringObj->getString().c_str() );

					//if( index < 0 ){ �G���[ }

					if( pVariables[ index + 1 ].getType() == ksVALUE_STRCT )
					{
						KsVariable*		pVariables2 = (KsVariable*)pVariables[ index + 1 ].m_value.h;
						delete [] pVariables2;
					}

					pVariables[ index + 1 ] = m_variables[ m_pos ];
				}

				//if( m_variables[ m_pos ].getType() == ksVALUE_INVALID ){
				//	m_variables[ m_pos ].m_value.h = handle1;
				//}
				break;
			}
			case ksCMD_GET_MEMBER_LOCAL:
			{
				++pData;
				memcpy( &varIdx, pData, sizeof( KsInt32 ) );

				++pData;
				memcpy( &handle, pData, sizeof( KsInt32 ) );

				if( pFunc->m_pVariables[ varIdx ].getType() == ksVALUE_STRCT )
				{
					/* �����o�[�� */
					pStringObj = (KsStringObject*)KsGetHandleObject( handle );

					/* �\���̂̃f�[�^�� */
					pVariables = (KsVariable*)pFunc->m_pVariables[ varIdx ].m_value.h;

					/* �\���̂��擾 */
					pStructObj = (KsStructObject*)KsGetHandleObject( pVariables[ 0 ].m_value.h );

					/* �����o�[�̃C���f�b�N�X���擾 */
					index = pStructObj->findVarIndex( pStringObj->getString().c_str() );

					if( index < 0 )
					{
						/* �����o�[�֐� */
						KsChar		temp[ 512 ];
						sprintf( temp, "%s.%s", pStructObj->getString().c_str(), pStringObj->getString().c_str() );
						pGlobalObj = KsGetGlobalObject( m_pHandleManager, temp );
						//if( pGlobalObj == NULL ){ printf("error\n"); }
						m_variables[ m_pos ] = *pGlobalObj->getVariable();
						
						// ���̍\���̕ϐ��̐擪�̃|�C���^���ł����ɕێ����Ă��Ȃ��ƃ_��
						// ���̎��́ACALL���Ă΂��͂��Ȃ̂Ŗ߂�l������ꏊ�Ƀ����o�[�ϐ��̐擪�|�C���^���Z�b�g���Ă���
						m_variables[ m_pos ].m_type    = ksVALUE_USER;
						m_variables[ m_pos ].m_value.h = (KsHandle)( &pVariables[ 1 ] );
						// �������^�C�v�����Ƀ����o�[�̃A�h���X���Z�b�g����
						//m_variables[ m_pos ].m_type = (KsInt32)&pVariables[ 1 ];
					}
					else
					{
						m_variables[ m_pos ] = pVariables[ index + 1 ];
					}
				}

				++m_pos;

				break;
			}
			case ksCMD_GET_MEMBER_LOCAL_ARRAY:
			{
				++pData;
				memcpy( &varIdx, pData, sizeof( KsInt32 ) );

				++pData;
				memcpy( &handle, pData, sizeof( KsInt32 ) );

				/* �z��̃C���f�b�N�X�擾 */
				--m_pos;
				index    = m_variables[ m_pos ].getInt();
				varIdx += index;

				if( pFunc->m_pVariables[ varIdx ].getType() == ksVALUE_STRCT )
				{
					/* �����o�[�� */
					pStringObj = (KsStringObject*)KsGetHandleObject( handle );

					/* �\���̂̃f�[�^�� */
					pVariables = (KsVariable*)pFunc->m_pVariables[ varIdx ].m_value.h;

					/* �\���̂��擾 */
					pStructObj = (KsStructObject*)KsGetHandleObject( pVariables[ 0 ].m_value.h );

					/* �����o�[�̃C���f�b�N�X���擾 */
					index = pStructObj->findVarIndex( pStringObj->getString().c_str() );

					if( index < 0 )
					{
						/* �����o�[�֐� */
						KsChar		temp[ 512 ];
						sprintf( temp, "%s.%s", pStructObj->getString().c_str(), pStringObj->getString().c_str() );
						pGlobalObj = KsGetGlobalObject( m_pHandleManager, temp );
						//if( pGlobalObj == NULL ){ printf("error\n"); }
						m_variables[ m_pos ] = *pGlobalObj->getVariable();
						
						// ���̍\���̕ϐ��̐擪�̃|�C���^���ł����ɕێ����Ă��Ȃ��ƃ_��
						// ���̎��́ACALL���Ă΂��͂��Ȃ̂Ŗ߂�l������ꏊ�Ƀ����o�[�ϐ��̐擪�|�C���^���Z�b�g���Ă���
						m_variables[ m_pos ].m_type    = ksVALUE_USER;
						m_variables[ m_pos ].m_value.h = (KsHandle)( &pVariables[ 1 ] );
						// �������^�C�v�����Ƀ����o�[�̃A�h���X���Z�b�g����
						//m_variables[ m_pos ].m_type = (KsInt32)&pVariables[ 1 ];
					}
					else
					{
						m_variables[ m_pos ] = pVariables[ index + 1 ];
					}
				}

				++m_pos;

				break;
			}
			case ksCMD_GET_MEMBER_GLOBAL:
			{
				++pData;
				memcpy( &handle1, pData, sizeof( KsInt32 ) );

				++pData;
				memcpy( &handle2, pData, sizeof( KsInt32 ) );

				/* �n���h������l���擾���� */
				pGlobalObj = (KsGlobalObject*)KsGetHandleObject( handle1 );

				if( pGlobalObj->getVariable()->getType() == ksVALUE_STRCT )
				{
					/* �����o�[�� */
					pStringObj = (KsStringObject*)KsGetHandleObject( handle2 );

					/* �\���̂̃f�[�^�� */
					pVariables = (KsVariable*)pGlobalObj->getVariable()->m_value.h;

					/* �\���̂��擾 */
					pStructObj = (KsStructObject*)KsGetHandleObject( pVariables[ 0 ].m_value.h );

					/* �����o�[�̃C���f�b�N�X���擾 */
					index = pStructObj->findVarIndex( pStringObj->getString().c_str() );

					if( index < 0 )
					{
						/* �����o�[�֐� */
						KsChar		temp[ 1024 ];
						sprintf( temp, "%s.%s", pStructObj->getString().c_str(), pStringObj->getString().c_str() );
						pGlobalObj = KsGetGlobalObject( m_pHandleManager, temp );
						//if( pGlobalObj == NULL ){ printf("error\n"); }
						m_variables[ m_pos ] = *pGlobalObj->getVariable();
						
						// ���̍\���̕ϐ��̐擪�̃|�C���^���ł����ɕێ����Ă��Ȃ��ƃ_��
						// ���̎��́ACALL���Ă΂��͂��Ȃ̂Ŗ߂�l������ꏊ�Ƀ����o�[�ϐ��̐擪�|�C���^���Z�b�g���Ă���
						m_variables[ m_pos ].m_type    = ksVALUE_USER;
						m_variables[ m_pos ].m_value.h = (KsHandle)( &pVariables[ 1 ] );
						// �������^�C�v�����Ƀ����o�[�̃A�h���X���Z�b�g����
						//m_variables[ m_pos ].m_type = (KsInt32)&pVariables[ 1 ];
					}
					else
					{
						m_variables[ m_pos ] = pVariables[ index + 1 ];
					}
				}

				++m_pos;

				break;
			}
			case ksCMD_GET_MEMBER_GLOBAL_ARRAY:
			{
				++pData;
				memcpy( &handle1, pData, sizeof( KsInt32 ) );

				++pData;
				memcpy( &handle2, pData, sizeof( KsInt32 ) );

				/* �n���h������l���擾���� */
				pGlobalObj = (KsGlobalObject*)KsGetHandleObject( handle1 );

				/* �z��̃C���f�b�N�X�擾 */
				--m_pos;
				index = m_variables[ m_pos ].getInt();

				// �C���f�b�N�X���i�߂�
				for( KsInt32 i=0; i<index; i++ )
				{
					//if( pGlobalObj->m_pNext == NULL ){
					//	printf("�z��I�[�o�[\n");
					//}
					pGlobalObj = (KsGlobalObject*)pGlobalObj->m_pNext;
				}

				if( pGlobalObj->getVariable()->getType() == ksVALUE_STRCT )
				{
					/* �����o�[�� */
					pStringObj = (KsStringObject*)KsGetHandleObject( handle2 );

					/* �\���̂̃f�[�^�� */
					pVariables = (KsVariable*)pGlobalObj->getVariable()->m_value.h;

					/* �\���̂��擾 */
					pStructObj = (KsStructObject*)KsGetHandleObject( pVariables[ 0 ].m_value.h );

					/* �����o�[�̃C���f�b�N�X���擾 */
					index = pStructObj->findVarIndex( pStringObj->getString().c_str() );

					if( index < 0 ){
						/* �����o�[�֐� */
						KsChar		temp[ 512 ];
						sprintf( temp, "%s.%s", pStructObj->getString().c_str(), pStringObj->getString().c_str() );
						pGlobalObj = KsGetGlobalObject( m_pHandleManager, temp );
						//if( pGlobalObj == NULL ){ printf("error\n"); }
						m_variables[ m_pos ] = *pGlobalObj->getVariable();
						
						// ���̍\���̕ϐ��̐擪�̃|�C���^���ł����ɕێ����Ă��Ȃ��ƃ_��
						// ���̎��́ACALL���Ă΂��͂��Ȃ̂Ŗ߂�l������ꏊ�Ƀ����o�[�ϐ��̐擪�|�C���^���Z�b�g���Ă���
						m_variables[ m_pos ].m_type    = ksVALUE_USER;
						m_variables[ m_pos ].m_value.h = (KsHandle)( &pVariables[ 1 ] );
						// �������^�C�v�����Ƀ����o�[�̃A�h���X���Z�b�g����
						//m_variables[ m_pos ].m_type = (KsInt32)&pVariables[ 1 ];
					}
					else
					{
						m_variables[ m_pos ] = pVariables[ index + 1 ];
					}
				}

				++m_pos;
				break;
			}
			case ksCMD_RET:
			{
				for( KsInt32 i=0; i<pFunc->m_numLocal; i++ )
				{
					if( pFunc->m_pVariables[ i ].getType() == ksVALUE_STRCT )
					{
						pVariables = (KsVariable*)pFunc->m_pVariables[ i ].m_value.h;
						delete [] pVariables;
						pFunc->m_pVariables[ i ].m_type = ksVALUE_INVALID;
					}
				}
				m_pos -= pFunc->m_numLocal;
				bLoop = ksFALSE;
				break;
			}
			case ksCMD_RETV:
			{
				for( KsInt32 i=0; i<pFunc->m_numLocal; i++ )
				{
					if( pFunc->m_pVariables[ i ].getType() == ksVALUE_STRCT )
					{
						pVariables = (KsVariable*)pFunc->m_pVariables[ i ].m_value.h;
						delete [] pVariables;
					}
				}

				m_esp = &m_variables[ m_pos-1 ];
				/* �g�p�����X�^�b�N���J������ */
				m_pos -= pFunc->m_numLocal;
				m_variables[ m_pos-2 ] = *m_esp;
				bLoop = ksFALSE;
				--m_pos;
				break;
			}
			case ksCMD_PUSH_ZERO:
			{
				m_variables[ m_pos ].setInt( 0 );
				m_pos++;
				break;
			}
			case ksCMD_PUSH_ONE:
			{
				m_variables[ m_pos ].setInt( 1 );
				m_pos++;
				break;
			}
			case ksCMD_PUSH_INT:
			{
				++pData;
				memcpy( &value, pData, sizeof( KsInt32 ) );
				m_variables[ m_pos ].setInt( value );
				m_pos++;
				break;
			}
			case ksCMD_PUSH_FLOAT:
			{
				++pData;
				memcpy( &value_f, pData, sizeof( KsInt32 ) );
				m_variables[ m_pos ].setFloat( value_f );
				m_pos++;
				break;
			}
			case ksCMD_PUSH_STRING:
			{
				++pData;
			
				memcpy( &handle, pData, sizeof( KsHandle ) );
				//printf( "PUSH_STRING  %d\n", handle );
				/* �n���h������l���擾���� */
				pStringObj = (KsStringObject*)KsGetHandleObject( handle );

				/* �X�^�b�N�ɃZ�b�g���� */
				m_variables[ m_pos ].m_type    = ksVALUE_STRING;
				m_variables[ m_pos ].m_value.h = pStringObj->getHandle();
				++m_pos;
				break;
			}
			case ksCMD_PUSH_NULL:
			{
				m_variables[ m_pos ].setInt( 0 );
				m_pos++;
				break;
			}
			case ksCMD_POP:
			{
				// �Ԃ�l���Ȃ��̂ɕϐ��ɑ�������\��������̂ŔO�̂���
				--m_pos;
				break;
			}
			case ksCMD_JZ:
			{
				++pData;
				--m_pos;
				/* 0�ŃW�����v */
				if( !m_variables[ m_pos ].getInt() )
				{
					memcpy( &value, pData, sizeof( KsInt32 ) );
					pData = (KsUInt32*)&pCode[ value ];
					continue;
				}
				break;
			}
			case ksCMD_JNZ:
			{
				++pData;
				--m_pos;
				/* 0�ŃW�����v */
				if( m_variables[ m_pos ].getInt() )
				{
					memcpy( &value, pData, sizeof( KsInt32 ) );
					pData = (KsUInt32*)&pCode[ value ];
					continue;
				}
				break;
			}
			case ksCMD_JMP:
			{
				++pData;
				memcpy( &value, pData, sizeof( KsInt32 ) );
				pData = (KsUInt32*)&pCode[ value ];
				continue;
			}
			default:
			{
				printf( "error code %d\n", *pData );
				break;
			}
		}

		++pData;
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsBool KsVirtualMachine::loadLib( const KsScriptLibInfo* pLibInfo )
{
	KsAssert( pLibInfo, "loadLib pLibInfo null" );

	if( m_vpLibraries.find( pLibInfo[ 0 ].pFuncName ) )
	{
		return ksFALSE;
	}

	for( KsInt32 i=0; pLibInfo[ i ].callback != NULL; i++ )
	{
		m_vpLibraries.add( pLibInfo[ i ].pFuncName, pLibInfo[ i ].callback );
	}

	return ksTRUE;
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsBool KsVirtualMachine::unloadLib( const KsScriptLibInfo* pLibInfo )
{
	KsAssert( pLibInfo, "unloadLib pLibInfo null" );

	if( !m_vpLibraries.find( pLibInfo[ 0 ].pFuncName ) )
	{
		return ksFALSE;
	}

	for( KsInt32 i=0; pLibInfo[ i ].callback != NULL; i++ )
	{
		m_vpLibraries.destroy( pLibInfo[ i ].pFuncName );
	}

	return ksTRUE;
}





