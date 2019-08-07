/************************************************************************************************/
/** 
 * @file		KsHumanIK.h
 * @brief		ボーンポーズ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * コンストラクタ
 */
/************************************************************************************************/
KsIKPoint::KsIKPoint( KsBone* pBone )
	: m_pBone( pBone )
	, m_bIKLimitAngle( ksFALSE )
	, m_IKLimitAngleType( 0 )
{
	

	if( pBone->getName() == "左ひざ" ||
		pBone->getName() == "右ひざ" )
		//pBone->getName() == "右ひざ" ||
		//pBone->getName() == "左足首" ||
		//pBone->getName() == "右足首" ||
		//pBone->getName() == "左足"   ||
		//pBone->getName() == "右足"   )
	{
		if( pBone->getName() == "左ひざ" || pBone->getName() == "右ひざ" )
		{
			m_IKLimitAngleType = 1;
			//joint.IKLimitAngleType = 1;
		}
		else if( pBone->getName() == "左足首" || pBone->getName() == "右足首" )
		{
			m_IKLimitAngleType = 2;
			//joint.IKLimitAngleType = 2;
		}
		else
		{
			m_IKLimitAngleType = 3;
			//joint.IKLimitAngleType = 3;
		}
		m_bIKLimitAngle = ksTRUE;
		//joint.IsLimitAngle = true;
	}
}


/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsHumanIK::KsHumanIK( KsModel* pModel )
	: m_pModel( pModel )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsHumanIK::~KsHumanIK()
{
}


/************************************************************************************************/
/*
 * 更新処理
 */
/************************************************************************************************/
void KsHumanIK::updateIK()
{
	KsVector3d		vec3OrgTargetPos;
	KsVector3d		vec3EffPos;
	KsVector3d		vec3TargetPos;
	KsVector3d		vec3Diff;
	KsVector3d		vec3RotAxis;
	KsVector3d		vec3Translation;
	KsQuaternion	vec4RotQuat;
	KsQuaternion	tempQuat;
	KsMatrix4x4		tempMatrix;
	KsMatrix4x4		parentMatrix;
	KsMatrix4x4		matInvBone;
	KsMatrix4x4		jointWorld;
	KsReal			fRotAngle;
	KsBone*			pTargetBone;
	KsBone*			pEffectBone;

	for( KsUInt32 i=0; i<m_vpEffectors.size(); i++ )
	{
		KsIKEffector*	pIKEffector  = m_vpEffectors[ i ];
		KsIKPoint*		pTargetPoint = pIKEffector->getTargetPoint();
		KsIKPoint*		pEffectPoint = pIKEffector->getEffectorPoint();
		KsUInt32		ChainLength  = pIKEffector->getChainPointCount();
		
		pTargetBone = pTargetPoint->getBone();
		pEffectBone = pEffectPoint->getBone();

		vec3OrgTargetPos = pTargetBone->m_worldTransform.getTranslate();

		// ワールド座標を再計算する
		for( KsInt32 chain = ChainLength - 1 ; chain >= 0 ; chain-- )
		{
			KsBone*	pBone = pIKEffector->getChainPoint( chain )->getBone();

			if( pBone->getParent() )
			{			
				pBone->m_worldTransform = pBone->m_boneTransform * pBone->getParent()->m_worldTransform;;
			}
		}

		if( pEffectBone->getParent() )
		{
			pEffectBone->m_worldTransform = pEffectBone->m_boneTransform * pEffectBone->getParent()->m_worldTransform;;
		}

		//IK
		for( KsInt32 it = 0 ; it < pIKEffector->getIterations(); it++ )
		{
			for( KsUInt32 cbLinkIdx = 0 ; cbLinkIdx < ChainLength ; cbLinkIdx++ )
			{
				KsIKPoint*	pIKPoint = pIKEffector->getChainPoint( cbLinkIdx );
				KsBone*		pIKBone  = pIKPoint->getBone();

				// エフェクタの位置の取得
				vec3EffPos = pEffectBone->m_worldTransform.getTranslate();

				// ワールド座標系から注目ノードの局所(ローカル)座標系への変換
				jointWorld = pIKBone->m_worldTransform;
				matInvBone = jointWorld.inverse();

				// エフェクタ，到達目標のローカル位置
				vec3EffPos    = KsVector3d::Transform( &vec3EffPos, &matInvBone );
				vec3TargetPos = KsVector3d::Transform( &vec3OrgTargetPos, &matInvBone );

				// 十分近ければ終了
				vec3Diff = vec3EffPos - vec3TargetPos;

				if( KsVector3d::Dot( vec3Diff, vec3Diff ) < 0.0000001f )	goto next;

				// (1) 基準関節→エフェクタ位置への方向ベクトル
				vec3EffPos.normalize();

				// (2) 基準関節→目標位置への方向ベクトル
				vec3TargetPos.normalize();

				// ベクトル (1) を (2) に一致させるための最短回転量（Axis-Angle）
				//
				// 回転角
				fRotAngle = KsACos( KsVector3d::Dot( vec3EffPos, vec3TargetPos ) );

				if( ksTOLERANCE2 < KsFabs( fRotAngle ) )
				{
					if( fRotAngle < -pIKEffector->getControlWeight() )
					{
						fRotAngle = -pIKEffector->getControlWeight();
					}
					else if( pIKEffector->getControlWeight() < fRotAngle )
					{
						fRotAngle = pIKEffector->getControlWeight();
					}

					// 回転軸
					vec3RotAxis = KsVector3d::Cross( vec3EffPos, vec3TargetPos );

					if( KsVector3d::Dot( vec3RotAxis, vec3RotAxis ) < ksTOLERANCE2 ) { continue; }

					vec3RotAxis.normalize();

					// 関節回転量の補正
					vec4RotQuat = KsQuaternion::CreateFromAxisAngle( vec3RotAxis, fRotAngle );

					if( pIKPoint->IsIKLimitAngle() )
					{
						limitAngle( vec4RotQuat, pIKPoint );
					}

					vec4RotQuat.normalize();

					tempMatrix             = pIKBone->m_boneTransform;
					vec3Translation        = tempMatrix.getTranslate();
					tempMatrix.setTranslate( KsVector3d::ZERO );
					tempQuat               = KsQuaternion::CreateFromRotationMatrix( tempMatrix );

					tempQuat.normalize();
					//tempQuat = KsQuaternion::Multiply( tempQuat, vec4RotQuat );
					tempQuat = KsQuaternion::Multiply( vec4RotQuat, tempQuat );
					//tempQuat = vec4RotQuat * tempQuat;
					tempQuat.normalize();
		
					tempMatrix = KsMatrix4x4::CreateFromQuaternion( tempQuat );
					tempMatrix.setTranslate( vec3Translation );

					pIKBone->m_boneTransform = tempMatrix;

					// ワールド座標を再計算する
					for( KsInt32 chain = cbLinkIdx; chain >= 0 ; chain-- )
					{
						KsBone*	pBone = pIKEffector->getChainPoint( chain )->getBone();

						if( pBone->getParent() )
						{			
							pBone->m_worldTransform = pBone->m_boneTransform * pBone->getParent()->m_worldTransform;;
						}
					}

					if( pEffectBone->getParent() )
					{
						pEffectBone->m_worldTransform = pEffectBone->m_boneTransform * pEffectBone->getParent()->m_worldTransform;;
					}
				}
			}
		}
next:;
	}

	m_pModel->updateSkinMatrix();
}


void QuaternionToEuler( KsVector3d *pvecAngle, const KsQuaternion *pvec4Quat )
{
	// XYZ軸回転の取得
	// Y回転を求める
	float	x2 = pvec4Quat->x + pvec4Quat->x;
	float	y2 = pvec4Quat->y + pvec4Quat->y;
	float	z2 = pvec4Quat->z + pvec4Quat->z;
	float	xz2 = pvec4Quat->x * z2;
	float	wy2 = pvec4Quat->w * y2;
	float	temp = -(xz2 - wy2);

	// 誤差対策
	if( temp >= 1.f ){ temp = 1.f; }
	else if( temp <= -1.f ){ temp = -1.f; }

	float	yRadian = asinf(temp);

	// 他の回転を求める
	float	xx2 = pvec4Quat->x * x2;
	float	xy2 = pvec4Quat->x * y2;
	float	zz2 = pvec4Quat->z * z2;
	float	wz2 = pvec4Quat->w * z2;

	if( yRadian < 3.1415926f * 0.5f )
	{
		if( yRadian > -3.1415926f * 0.5f )
		{
			float	yz2 = pvec4Quat->y * z2;
			float	wx2 = pvec4Quat->w * x2;
			float	yy2 = pvec4Quat->y * y2;
			pvecAngle->x = atan2f( (yz2 + wx2), (1.f - (xx2 + yy2)) );
			pvecAngle->y = yRadian;
			pvecAngle->z = atan2f( (xy2 + wz2), (1.f - (yy2 + zz2)) );
		}
		else
		{
			pvecAngle->x = -atan2f( (xy2 - wz2), (1.f - (xx2 + zz2)) );
			pvecAngle->y = yRadian;
			pvecAngle->z = 0.f;
		}
	}
	else
	{
		pvecAngle->x = atan2f( (xy2 - wz2), (1.f - (xx2 + zz2)) );
		pvecAngle->y = yRadian;
		pvecAngle->z = 0.f;
	}
}

void QuaternionCreateEuler( KsQuaternion *pvec4Out, const KsVector3d *pvec3EulerAngle )
{
	float	xRadian = pvec3EulerAngle->x * 0.5f;
	float	yRadian = pvec3EulerAngle->y * 0.5f;
	float	zRadian = pvec3EulerAngle->z * 0.5f;
	float	sinX = sinf( xRadian );
	float	cosX = cosf( xRadian );
	float	sinY = sinf( yRadian );
	float	cosY = cosf( yRadian );
	float	sinZ = sinf( zRadian );
	float	cosZ = cosf( zRadian );

	// XYZ
	pvec4Out->x = sinX * cosY * cosZ - cosX * sinY * sinZ;
	pvec4Out->y = cosX * sinY * cosZ + sinX * cosY * sinZ;
	pvec4Out->z = cosX * cosY * sinZ - sinX * sinY * cosZ;
	pvec4Out->w = cosX * cosY * cosZ + sinX * sinY * sinZ;
}

//----------------------------
// ボーンの回転角度を制限する
//----------------------------
void KsHumanIK::limitAngle( KsQuaternion& quat, KsIKPoint* pIKPoint )
{
	KsVector3d	angle;

	// XYZ軸回転の取得
	//angle = quat.convertToEuler();
	QuaternionToEuler( &angle, &quat );
	
	KsInt32	type = pIKPoint->getIKLimitAngleType();

	// 角度制限

	//if( angle.x < 0.0f )
	//	angle.x = 0.0f;
	//if( -0.002f < angle.x )
	//	angle.x = -0.002f;

	// 角度制限
	if( 1 == type )
	{
		KsReal ry_1 = 0.0f;
		KsReal ry_2 = 180.0f;
		
		if( angle.x < -3.14159f )
		{
		    angle.x = -3.14159f;
		}
		if( 0.0f < angle.x )
		{
		    angle.x = 0.0f;
		}

		ry_1 = 15.0f;
		ry_2 = 15.0f;
		if( angle.z > ksDEG( ry_1 ) )
		{
			angle.z = ksDEG( ry_1 );
		}
		if( angle.z < -ksDEG( ry_2 ) )
		{
			angle.z = -ksDEG( ry_2 );
		}

		angle.y = 0.0f;
		angle.z = 0.0f;
	}
#if 0
	else if( 2 == type )
	{
		KsReal ry_1 = 130.0f;
		KsReal ry_2 = -130.0f;
		if( angle.x > ksDEG( ry_1 ) )
		{
			angle.x = ksDEG( ry_1 );
		}
		if( angle.x < ksDEG( ry_2 ) )
		{
			angle.x = ksDEG( ry_2 );
		}

		//angle.y = 0.0f;
		angle.z = 0.0f;
	}
	else if( 3 == type )
	{
		
		KsReal ry_1 = 130.0f;
		KsReal ry_2 = -130.0f;
		if( angle.x > ksDEG( ry_1 ) )
		{
		//	angle.x = ksDEG( ry_1 );
		}
		if( angle.x < ksDEG( ry_2 ) )
		{
			//angle.x = ksDEG( ry_2 );
		}

		ry_1 = 90.0f;
		ry_2 = 0.0f;

		if( angle.y > ksDEG( ry_1 ) )
		{
			angle.y = ksDEG( ry_1 );
		}
		if( angle.y < -ksDEG( ry_2 ) )
		{
			angle.y = -ksDEG( ry_2 );
		}

		//angle.y = 0.0f;
		//angle.z = 0.0f;
	}
#endif
	//angle.y = 0.0f;
	//angle.z = 0.0f;

	QuaternionCreateEuler( &quat, &angle );

	// XYZ軸回転からクォータニオンへ
	//quat.fromEulerAngles( angle.x, angle.y, angle.z );
}

/************************************************************************************************/
/*
 * 更新処理
 */
/************************************************************************************************/
void KsHumanIK::update()
{
	updateIK();
	return;
	KsVector3d		vec3OrgTargetPos;
	KsVector3d		vec3EffPos;
	KsVector3d		vec3TargetPos;
	KsVector3d		vec3Diff;
	KsVector3d		vec3RotAxis;
	KsVector3d		vec3Translation;
	KsQuaternion	vec4RotQuat;
	KsQuaternion	tempQuat;
	KsMatrix4x4		tempMatrix;
	KsMatrix4x4		parentMatrix;
	KsMatrix4x4		matInvBone;
	KsMatrix4x4		jointWorld;
	KsInt32			parentIndex;
	KsReal			fRotAngle;
	KsBone*			pTargetBone;
	KsBone*			pEffectBone;
	KsBone*			pJointList[ 256 ];

	for( KsUInt32 i=0; i<m_vpParameters.size(); i++ )
	{
		KsIKParameter*	pInfo = m_vpParameters[ i ];

		pTargetBone = m_pModel->m_vpBones[ pInfo->BoneIndex ];
		pEffectBone = m_pModel->m_vpBones[ pInfo->TargetBoneIndex ];

		for( KsUInt32 j=0; j<pInfo->ChildBoneIndices.size(); j++ )
		{
			pJointList[ j ] = m_pModel->m_vpBones[ pInfo->ChildBoneIndices[ j ] ];
		}

		vec3OrgTargetPos = pTargetBone->m_worldTransform.getTranslate();

		// ワールド座標を再計算する
		for( KsInt32 chain = pInfo->ChainLength - 1 ; chain >= 0 ; chain-- )
		{
			parentIndex = pJointList[ chain ]->getParentIndex();
			tempMatrix  = pJointList[ chain ]->m_boneTransform;
	                
			if( parentIndex > 0 )
			{
				parentMatrix = m_pModel->m_vpBones[ parentIndex ]->m_worldTransform;
				//tempMatrix   = Matrix.Multiply( tempMatrix, parentMatrix);
				tempMatrix   = tempMatrix * parentMatrix;
			}

			pJointList[ chain ]->m_worldTransform = tempMatrix;
		}

		parentIndex = pEffectBone->getParentIndex();
		tempMatrix  = pEffectBone->m_boneTransform;
	            
		if( parentIndex > 0 )
		{
			parentMatrix = m_pModel->m_vpBones[ parentIndex ]->m_worldTransform;
			//tempMatrix   = Matrix.Multiply( tempMatrix, parentMatrix);
			tempMatrix   = tempMatrix * parentMatrix;
		}

		pEffectBone->m_worldTransform = tempMatrix;


		// ワールド座標を再計算する
		for( KsInt32 it = 0 ; it < pInfo->Iterations ; it++ )
		{
			for( KsInt32 cbLinkIdx = 0 ; cbLinkIdx < pInfo->ChainLength ; cbLinkIdx++ )
			{
				// エフェクタの位置の取得
				vec3EffPos = pEffectBone->m_worldTransform.getTranslate();

				// ワールド座標系から注目ノードの局所(ローカル)座標系への変換
				jointWorld = pJointList[ cbLinkIdx ]->m_worldTransform;
				matInvBone = jointWorld.inverse();

				// エフェクタ，到達目標のローカル位置
				vec3EffPos    = KsVector3d::Transform( &vec3EffPos, &matInvBone );
				vec3TargetPos = KsVector3d::Transform( &vec3OrgTargetPos, &matInvBone );

				// 十分近ければ終了
				vec3Diff = vec3EffPos - vec3TargetPos;

				if( KsVector3d::Dot( vec3Diff, vec3Diff ) < 0.0000001f )	goto next;

				// (1) 基準関節→エフェクタ位置への方向ベクトル
				vec3EffPos.normalize();

				// (2) 基準関節→目標位置への方向ベクトル
				vec3TargetPos.normalize();

				// ベクトル (1) を (2) に一致させるための最短回転量（Axis-Angle）
				//
				// 回転角
				fRotAngle = KsACos( KsVector3d::Dot( vec3EffPos, vec3TargetPos ) );

				if( 0.00000001f < KsFabs( fRotAngle ) )
				{
					if( fRotAngle < -pInfo->ControlWeight )
					{
						fRotAngle = -pInfo->ControlWeight;
					}
					else if( pInfo->ControlWeight < fRotAngle )
					{
						fRotAngle = pInfo->ControlWeight;
					}

					// 回転軸
					vec3RotAxis = KsVector3d::Cross( vec3EffPos, vec3TargetPos );

					if( KsVector3d::Dot( vec3RotAxis, vec3RotAxis ) < 0.0000001f ) { continue; }

					vec3RotAxis.normalize();

					// 関節回転量の補正
					vec4RotQuat = KsQuaternion::CreateFromAxisAngle( vec3RotAxis, fRotAngle );

					//if( jointList[ cbLinkIdx ].IsLimitAngle )
					{
						//vec4RotQuat = LimitAngle( vec4RotQuat, jointList[ cbLinkIdx ].IKLimitAngleType );
					}

					vec4RotQuat.normalize();

					tempMatrix             = pJointList[ cbLinkIdx ]->m_boneTransform;
					vec3Translation        = tempMatrix.getTranslate();
					tempMatrix.setTranslate( KsVector3d::ZERO );
					tempQuat               = KsQuaternion::CreateFromRotationMatrix( tempMatrix );

					tempQuat.normalize();
					//tempQuat = KsQuaternion::Multiply( tempQuat, vec4RotQuat );
					tempQuat = KsQuaternion::Multiply( vec4RotQuat, tempQuat );
					//tempQuat = vec4RotQuat * tempQuat;
					tempQuat.normalize();
		
					tempMatrix = KsMatrix4x4::CreateFromQuaternion( tempQuat );
					tempMatrix.setTranslate( vec3Translation );

					pJointList[ cbLinkIdx ]->m_boneTransform = tempMatrix;


					// ワールド座標を再計算する
					for( KsInt32 chain = cbLinkIdx; chain >= 0 ; chain-- )
					{
						KsBone*		pTemp = pJointList[ chain ];
						parentIndex = pJointList[ chain ]->getParentIndex();
						tempMatrix  = pJointList[ chain ]->m_boneTransform;
	                
						if( parentIndex > 0 )
						{
							KsBone*		pTemp2 = m_pModel->m_vpBones[ parentIndex ];
							parentMatrix = m_pModel->m_vpBones[ parentIndex ]->m_worldTransform;
							//tempMatrix   = Matrix.Multiply( tempMatrix, parentMatrix);
							tempMatrix   = tempMatrix * parentMatrix;
						}

						pJointList[ chain ]->m_worldTransform = tempMatrix;
					}

					parentIndex = pEffectBone->getParentIndex();
					tempMatrix  = pEffectBone->m_boneTransform;

					if( parentIndex > 0 )
					{
						parentMatrix = m_pModel->m_vpBones[ parentIndex ]->m_worldTransform;
						//tempMatrix   = Matrix.Multiply( tempMatrix, parentMatrix);
						tempMatrix   = tempMatrix * parentMatrix;
					}

					pEffectBone->m_worldTransform = tempMatrix;
				}
			}
		}
next:;
	}

	m_pModel->updateSkinMatrix();
}



