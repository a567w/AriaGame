/************************************************************************************************/
/** 
 * @file		KsPMD.cpp
 * @brief		PMD�t�@�C��
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                          */
/*==============================================================================================*/
#include "KsMMD/KsMMDPreCompile.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*************************************************************************************************/
/*
 * VMD�t�@�C���ǂݍ��ݏ���
 * @param	filePath	�t�@�C���p�X
 * @return	PMD�t�@�C���f�[�^
 */
/*************************************************************************************************/
KS_VMD_DATA* KsLoadVMDFile( const KsString& filePath )
{
	KS_VMD_DATA*	pVMD  = new KS_VMD_DATA();
	KsFileObject*	pFile = new KsFileBuffer( filePath, ksREAD | ksBINARY );

	// VMD �w�b�_�[�ǂݍ���
	pFile->read( &pVMD->Header, sizeof( KS_VMD_HEADER ) );

	// �L�[�t���[�����ǂݍ���
	pFile->read( &pVMD->NumFrame, sizeof( KsUInt32 ) );

	// �L�[�t���[���ǂݍ���
	pVMD->Frames = new KS_VMD_KEYFRAME[ pVMD->NumFrame ];
	pFile->read( pVMD->Frames, sizeof( KS_VMD_KEYFRAME ) * pVMD->NumFrame );

	// �\��L�[�t���[�����ǂݍ���
	pFile->read( &pVMD->NumFace, sizeof( KsUInt32 ) );

	// �\��f�[�^�ǂݍ���
	pVMD->Faces = new KS_VMD_FACE[ pVMD->NumFace ];
	pFile->read( pVMD->Faces, sizeof( KS_VMD_FACE ) * pVMD->NumFace );

	ksDELETE( pFile );

	return pVMD;
}

/*************************************************************************************************/
/*
 * KsAnimation�t�@�C���ǂݍ��ݏ���
 * @param	filePath	�t�@�C���p�X
 * @return	KsAnimation�t�@�C���f�[�^
 */
/*************************************************************************************************/
KsAnimation* KsAnimationCreateFromVMD( const KsString& filePath )
{
	KS_VMD_DATA*	pVMD = KsLoadVMDFile( filePath );

	if( NULL == pVMD )
	{
		return NULL;
	}

	KsAnimationChannel*	pAnimChannel = new KsAnimationChannel();

	 for( KsUInt32 i=0; i<pVMD->NumFrame; i++ )
	 {
		KS_VMD_KEYFRAME*	pFrame = &pVMD->Frames[ i ];

		KsKeyFrameCollection*	pKeyFrameCollection = pAnimChannel->getKeyFrameCollection( pFrame->BoneName );

		if( NULL == pKeyFrameCollection )
		{
			pKeyFrameCollection = new KsKeyFrameCollection();
			pKeyFrameCollection->setBoneName( &pFrame->BoneName[ 0 ] );
			pKeyFrameCollection->setHasTranslation( ksTRUE );
			pKeyFrameCollection->setHasRotation( ksTRUE );
			pKeyFrameCollection->setHasScale( ksFALSE );

			pAnimChannel->addKeyFrameCollection( pKeyFrameCollection->getBoneName(), pKeyFrameCollection );
		}

		KsKeyFrame keyFrame( *(KsVector3d*)&pFrame->Position, *(KsQuaternion*)&pFrame->Rotation, pFrame->FrameNo );

		keyFrame.setBezierX( pFrame->InterpolationX[0], pFrame->InterpolationX[4], pFrame->InterpolationX[8], pFrame->InterpolationX[12] );
		keyFrame.setBezierY( pFrame->InterpolationY[0], pFrame->InterpolationY[4], pFrame->InterpolationY[8], pFrame->InterpolationY[12] );
		keyFrame.setBezierZ( pFrame->InterpolationZ[0], pFrame->InterpolationZ[4], pFrame->InterpolationZ[8], pFrame->InterpolationZ[12] );
		keyFrame.setBezierAngle( pFrame->InterpolationRot[0], pFrame->InterpolationRot[4], pFrame->InterpolationRot[8], pFrame->InterpolationRot[12] );

		pKeyFrameCollection->addSortedKeyFrame( keyFrame );

		if( pKeyFrameCollection->getDuration() < keyFrame.getTime() )
		{
			pKeyFrameCollection->setDuration( keyFrame.getTime() );
		}
	 }

	KsAnimation*	pAnim = new KsAnimation( pVMD->Header.ModelName,  pAnimChannel ); 

	for( KsUInt32 i=0; i<pAnimChannel->getNumCollection(); i++ )
	{
		KsKeyFrameCollection*	pKeyFrameCollection = pAnimChannel->getKeyFrameCollection( i );

		if( pKeyFrameCollection->getBoneName() == "�E�Ђ�" )
		{
			for( KsUInt32 j=0; j<pKeyFrameCollection->getKeyFrameCount(); j++ )
			{
				KsKeyFrame*	pCurr = pKeyFrameCollection->getKeyFrame( j );
			}
		}

		if( 1 == pKeyFrameCollection->getKeyFrameCount() )
		{
			KsKeyFrame*	pCurr = pKeyFrameCollection->getKeyFrame( 0 );
			if( pCurr->getTranslate() == KsVector3d::ZERO )
			{
				pKeyFrameCollection->setHasTranslation( ksFALSE );
			}
			if( pCurr->getRotation() == KsQuaternion::IDENTITY )
			{
				pKeyFrameCollection->setHasRotation( ksFALSE );
			}
			continue;
		}

		pKeyFrameCollection->setHasTranslation( ksFALSE );
		pKeyFrameCollection->setHasRotation( ksFALSE );

		for( KsUInt32 j=0; j<pKeyFrameCollection->getKeyFrameCount()-1; j++ )
		{
			KsKeyFrame*	pCurr = pKeyFrameCollection->getKeyFrame( j );
			KsKeyFrame*	pNext = pKeyFrameCollection->getKeyFrame( j+1 );

			if( pCurr->getTranslate() != KsVector3d::ZERO )
			{
				pKeyFrameCollection->setHasTranslation( ksTRUE );
				break;
			}
		}

		for( KsUInt32 j=0; j<pKeyFrameCollection->getKeyFrameCount()-1; j++ )
		{
			KsKeyFrame*	pCurr = pKeyFrameCollection->getKeyFrame( j );
			KsKeyFrame*	pNext = pKeyFrameCollection->getKeyFrame( j+1 );

			if( pCurr->getRotation() != KsQuaternion::IDENTITY )
			{
				pKeyFrameCollection->setHasRotation( ksTRUE );
				break;
			}
		}
	}

	return pAnim;
}

