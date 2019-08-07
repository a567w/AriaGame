/************************************************************************************************/
/** 
 * @file		KsMesh.h
 * @brief		�J���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSMODEL_H__
#define __KSMODEL_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsModelNode.h"
#include "KsFileObject.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * 
 * @class	
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsModel
{
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsModel();

		/**
		 * �R�s�[�R���X�g���N�^
		 */
										KsModel( const KsModel* pModel );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsModel();

		/**
		 * �`�悷��
		 */
		void							Render();

		/**
		 * �N���[��
		 */
		KsModel*						Clone() { return new KsModel( this ); }

		/**
		 * �t�@�C�����烂�f���f�[�^��ǂݍ���
		 * @retval		ksTRUE			����
		 * @retval		ksFALSE			���s
		 */
		KsBool							Load( const KsChar* pFileName );
		KsBool							Load( const KsFileObject* pFile );

	public:
		KsUInt16						m_flags;				/**< �t���O					*/
		KsUInt16						m_type;					/**< �^�C�v					*/
		KsChar							m_fileName[ 128 ];		/**< �t�@�C����				*/
		KsUInt16						m_numNode;				/**< �m�[�h��				*/
		KsUInt16						m_reserv;				/**< �\���g					*/
		KsModelNode*					m_pRoot;				/**< ���[�g�m�[�h			*/
		KsModelNodeList					m_pObjects;				/**< �m�[�h���X�g			*/
};


#endif		/* __KSMODEL_H__ */