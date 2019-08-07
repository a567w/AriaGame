/************************************************************************************************/
/** 
 * @file		KsPack.cpp
 * @brief		�p�b�N
 * @author		Tsukasa Kato
 * @date		2004/11/24
 * @since		2004/11/24
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

#if 0
/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsPack::KsPack()
{
	m_fd        = -1;
	m_topSector = 0;
	m_path[ 0 ] = '\0';
	m_pInfoList = NULL;
}

/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsPack::~KsPack()
{
	destroy();
}

/************************************************************************************************/
/* 
 * ��񃊃X�g�𐶐�
 */
/************************************************************************************************/
KsBool KsPack::create( const KsChar* pPackName )
{
	/* HOST����ǂݍ��� */
	sprintf( m_path, "host0:DATA/%s", pPackName );

	m_fd = StIoOpen( m_path, SCE_O_RDONLY, 0644 );

	/* �ǂݍ��� */
	StIoRead( m_fd, &m_header, sizeof( KsPackHeader ) );

	m_pInfoList = new KsPackInfo2[ m_header.numFiles ];

	/* ��񕔂�ǂݍ��� */
	StIoRead( m_fd, m_pInfoList, m_header.numFiles * sizeof( KsPackInfo2 ) );

#if 0
	StPrintf( "numFiles %d\n", m_header.numFiles );
	StPrintf( "alignment %d\n", m_header.alignment );

	for( KsUInt32 i=0; i<m_header.numFiles; i++ ){
		StPrintf("--------------------------------------------------\n");
		StPrintf( "nameLen  %d \n", m_pInfoList[ i ].nameLength );
		StPrintf( "nameCRC1 %x \n", m_pInfoList[ i ].nameCRC1 );
		StPrintf( "nameCRC2 %x \n", m_pInfoList[ i ].nameCRC2 );
		StPrintf( "offset   %d \n", m_pInfoList[ i ].offset );
		StPrintf( "flag     %d \n", m_pInfoList[ i ].flags );
		StPrintf( "realSize %d \n", m_pInfoList[ i ].realSize );
		StPrintf( "compSize %d \n", m_pInfoList[ i ].compressedSize );

	}
#endif

	StIoClose( m_fd );
	m_fd = -1;

	return stTRUE;
}

/************************************************************************************************/
/* 
 * ��񃊃X�g�𐶐�
 */
/************************************************************************************************/
void KsPack::destroy()
{
	if( m_fd >= 0 ){
		sceIoClose( m_fd );
		m_fd = -1;
	}
	stDELETEARRAY( m_pInfoList );
}

/************************************************************************************************/
/*
 * �t�@�C�����J������
 */
/************************************************************************************************/
KsBool KsPack::open()
{
	close();

	/* �������g���C */
	m_fd = StIoOpen( m_path );

	return stTRUE;
}

/************************************************************************************************/
/*
 * ����
 */
/************************************************************************************************/
void KsPack::close()
{
	if( m_fd >= 0 ){
		sceIoClose( m_fd );
		m_fd = -1;
	}
}

/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsPackInfo2* KsPack::find( const KsChar* pFileName )
{
	/* �L�[ */
	KsUInt32	key = KsCrc32( (StUInt8*)pFileName );

	/* �Q���T���Ŏw��L�[�̃f�[�^������������ */
	KsInt32		index = binarySearch( key );

	if( index < 0 ){
		/* �t�@�C����������Ȃ� */
		return NULL;
	}

	return &m_pInfoList[ index ];

/*
	CRC1�����ł̓_���ȏꍇ�́A�t�@�C�����̒�����CRC2�܂Ń`�F�b�N����悤�ɂ���
*/
	/*
	if( m_pInfoList[ index ].nameCRC2 != key2 ){
		if( m_pInfoList[ index ].nameCRC2 < key2 ){
			// ��𒲂ׂ�
			for( KsInt32 i=index+1; i<m_header.numFiles; i++ ){
				if( m_pInfoList[ i ].nameCRC1 != key ){
					break;
				}
				if( m_pInfoList[ i ].nameCRC2 == key2 ){
					//if( m_pInfoList[ index ].nameLength == length ){
					//}
					findFlag = stTRUE;
					break;
				}
			}
		}
		else{
			// ���𒲂ׂ�
			for( KsInt32 i=index-1; i>0; i-- ){
				if( m_pInfoList[ i ].nameCRC1 != key ){
					break;
				}
				if( m_pInfoList[ i ].nameCRC2 == key2 ){
					findFlag = stTRUE;
					break;
				}
			}
		}
	}*/
}


/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsInt32 KsPack::binarySearch( KsUInt32 key )
{
	KsInt32		left, right, center;
	
	left  = 0;
	right = m_header.numFiles - 1;
	
	while( left <= right )
	{
		center = ( left + right ) / 2;
		
		if( m_pInfoList[ center ].nameCRC1 > key ){
			right = center - 1;
		}
		else if( m_pInfoList[ center ].nameCRC1 < key ){
			left = center + 1;
		}
		else{
			return center;
		}
	}

	return -1;
}
#endif
