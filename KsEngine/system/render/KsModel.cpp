/************************************************************************************************/
/** 
 * @file		KsModel.h
 * @brief		���f���f�[�^
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsModel.h"
#include "KsFile.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_MODEL_HEADER
{
	KsChar			id[ 4 ];
	KsUInt16		type;
	KsUInt16		flags;
	KsUInt16		numNode;
	KsUInt16		reserv;
}KS_MODEL_HEADER;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsModel::KsModel()
{
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsModel::~KsModel()
{
	KsModelNodeList::iterator it;

	for( it=m_pObjects.begin(); it<m_pObjects.end(); it++ ){
		ksDELETE( *it );
	}
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
void KsModel::Render()
{

}

/************************************************************************************************/
/*
 * ���f���ǂݍ���
 */
/************************************************************************************************/
KsBool KsModel::Load( const KsChar* pFileName )
{
	KsFile	file;

	/* �t�@�C���ǂݍ��� */
	if( file.open( pFileName, ksREAD | ksBINARY ) )
	{
		KS_MODEL_HEADER		header;

		/* ���f���f�[�^�w�b�_����ǂݍ��� */
		file.read( &header, sizeof( KS_MODEL_HEADER ) );

		m_flags   = header.flags;
		m_type    = header.type;
		m_numNode = header.numNode;

		printf( "------------<< ���f����� >>-------------\n" );
		printf( "heaer id  %s\n", header.id );
		printf( "num flag  %d\n", header.flags );
		printf( "num type  %d\n", header.type );
		printf( "num node  %d\n", header.numNode );

		/* �K�w�\�����擾���� */
		for( KsInt32 i=0; i<header.numNode; i++ )
		{
			/* �K�v�ȃm�[�h������� */
			KsModelNode* pNode = new KsModelNode;

			/* ���X�g�ɒǉ� */
			m_pObjects.push_back( pNode );
		}

		/* �W�I���g���ƊK�w�\���̍\�z */
		for( KsInt32 in=0; in<header.numNode; in++ )
		{
			KsInt16		id       = file.readInt16();
			KsInt16		type     = file.readInt16();
			KsInt16		flags    = file.readInt16();
			KsInt16		index    = file.readInt16();
			KsInt16		parent   = file.readInt16();
			KsInt16		numChild = file.readInt16();
			KsInt16		child    = 0;

			printf( "-------------<< �K�w��� >>--------------\n" );
			printf( "parent    %d\n", parent );
			printf( "numChild  %d\n", numChild );

			m_pObjects[ in ]->m_type  = type;
			m_pObjects[ in ]->m_flags = flags;

			/* �e���Z�b�g���� */
			if( parent != -1 ){
				m_pObjects[ in ]->m_pParent = m_pObjects[ parent ];
			}
			else{
				m_pObjects[ in ]->m_pParent = NULL;
			}

			/* �q���Z�b�g���� */
			for( KsInt16 ci=0; ci<numChild; ci++ ){
				child = file.readInt16();
				m_pObjects[ in ]->m_pChildren.push_back( m_pObjects[ child ] );
			}
		}

		/* �W�I���g���ƊK�w�\���̍\�z */
		for( KsInt32 ig=0; ig<header.numNode; ig++ )
		{
			m_pObjects[ ig ]->m_pGeometry = new KsGeometry();
			m_pObjects[ ig ]->m_pGeometry->Create( &file );
		}

		return ksTRUE;
	}

	return ksFALSE;
}
