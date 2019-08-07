

#include "KsAnimLoader.h"
#include "KsAnimation.h"

#if 0
KsAnimation* KsLoadAnim( KsFileObject* pFile )
{
	KS_KAM_FILE_HEADER		fileHeader;
	KS_KAM_INFO_HEADER		infoHeader;
	KS_KAM_TRACK			track;
	KS_KAM_KEY_FRAME		key;
	KsAnimation*			pAnim;
	KsAnimTrack*			pTrack;
	KsAnimKeyFrame*			pKey;

	pAnim = new KsAnimation();

	pFile->read( &fileHeader, sizeof( KS_KAM_FILE_HEADER ) );
	pFile->read( &infoHeader, sizeof( KS_KAM_INFO_HEADER ) );

	pAnim->m_startTime  = static_cast<KsReal>( infoHeader.start );
	pAnim->m_endTime    = static_cast<KsReal>( infoHeader.end );
	pAnim->m_frameRate  = static_cast<KsReal>( infoHeader.fps );
	pAnim->m_startTime /= static_cast<KsReal>( pAnim->m_frameRate );
	pAnim->m_endTime   /= static_cast<KsReal>( pAnim->m_frameRate );

	/* トラック情報読み込み */
	for( KsInt32 i=0; i<infoHeader.numTrack; i++ )
	{
		pTrack = new KsAnimTrack();

		pFile->read( &track, sizeof( KS_KAM_TRACK ) );

		/* キーフレーム情報読み込み */
		for( KsInt32 j=0; j<track.numFrame; j++ )
		{
			pKey = new KsAnimKeyFrame();

			pFile->read( &key, sizeof( KS_KAM_KEY_FRAME ) );

			pKey->m_time       = static_cast<KsReal>( key.time );
			pKey->m_time      /= pAnim->m_frameRate;
			pKey->m_pos.x      = key.translate.x;
			pKey->m_pos.y      = key.translate.y;
			pKey->m_pos.z      = key.translate.z;
			pKey->m_rotation.x = key.rotate.x;
			pKey->m_rotation.y = key.rotate.y;
			pKey->m_rotation.z = key.rotate.z;
			pKey->m_rotation.w = key.rotate.w;
			pKey->m_scale.x    = key.scale.x;
			pKey->m_scale.y    = key.scale.y;
			pKey->m_scale.z    = key.scale.z;

			pTrack->m_vKeyFrames.push_back( pKey );
		}

		pAnim->m_pvTracks.push_back( pTrack );
	}

	return pAnim;
}


KsAnimation* KsLoadAnim( const KsChar* pFileName )
{
	KsFileBuffer	file;
	KsAnimation*	pAnim;

	if( !file.open( pFileName, ksFILE_FLAG_DEFAULT ) )
	{
		return NULL;
	}

	pAnim = KsLoadAnim( &file );

	file.close();

	return pAnim;
}



KsAnimation* KsLoadAnim( const KsChar* pFileName )
{
	KsAnimation*		pAnim = new KsAnimation();

	FILE*	fp = fopen( pFileName, "rb" );

	/* ファイルヘッダー読み込み */
	fread( &header, sizeof( KS_KAM_FILE_HEADER ), 1, fp );
	fread( &info, sizeof( KS_KAM_INFO_HEADER ), 1, fp );

	pAnim->m_startTime = (KsReal)info.start;
	pAnim->m_endTime   = (KsReal)info.end;
	pAnim->m_frameRate = (KsReal)info.fps;

	pAnim->m_startTime /= pAnim->m_frameRate;
	pAnim->m_endTime /= pAnim->m_frameRate;

	for( KsInt32 i=0; i<info.numTrack; i++ )
	{
		KsAnimTrack*		pTrack;
		KsAnimKeyFrame*		pKey;

		fread( &track, sizeof( KS_KAM_TRACK ), 1, fp );
		
		pTrack = new KsAnimTrack();

		//pTrack->m_maxTime = 
		//pTrack->m_pTarget = 

		for( KsInt32 j=0; j<track.numFrame; j++ ){
			fread( &key, sizeof( KS_KAM_KEY_FRAME ), 1, fp );

			pKey = new KsAnimKeyFrame();
			pKey->m_time = (KsReal)key.time;

			pKey->m_time /= pAnim->m_frameRate;

			pKey->m_pos.x = key.translate.x;
			pKey->m_pos.y = key.translate.y;
			pKey->m_pos.z = key.translate.z;

			pKey->m_rotation.x = key.rotate.x;
			pKey->m_rotation.y = key.rotate.y;
			pKey->m_rotation.z = key.rotate.z;
			pKey->m_rotation.w = key.rotate.w;

			pTrack->m_vKeyFrames.push_back( pKey );
		}

		pAnim->m_pvTracks.push_back( pTrack );
	}

	fclose( fp );

	return pAnim;
}


#endif
