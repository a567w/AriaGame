

//===============================================================================================//
// ���ʂ̃Z�b�g
//===============================================================================================//
inline void KsPlane::set( const KsVector3d& refNormal, KsReal distance )
{
	m_normal   = refNormal;
	m_distance = distance;
}

//===============================================================================================//
// ���ʂ̃Z�b�g
//===============================================================================================//
inline void KsPlane::set( const KsVector3d& refPointA, const KsVector3d& refPointB, const KsVector3d& refPointC )
{
	KsVector3d		abVector = refPointB - refPointA;
	KsVector3d		acVector = refPointC - refPointA;
	
	m_normal = acVector.crossProduct( abVector );
	m_normal.normalize();
	
	m_distance = -m_normal.dotProduct( refPointA );
}

//===============================================================================================//
// ���ʂ̃Z�b�g
//===============================================================================================//
inline void KsPlane::set( const KsVector3d& refNormal, const KsVector3d& refPoint )
{
	m_normal   =  refNormal;
	m_distance = -m_normal.dotProduct( refPoint );
}

//===============================================================================================//
// YZ���ʂ��琂����L�΂��Č��������ꏊ��X���W���擾����
//===============================================================================================//
inline KsReal KsPlane::getX( KsReal y, KsReal z )
{
	if( KsFabs( m_normal.x ) < ksTOLERANCE ){
		return 0.0f;
	}
	
	return ( -( m_normal.y*y + m_normal.z*z + m_distance )/m_normal.x );
}

//===============================================================================================//
// XZ���ʂ��琂����L�΂��Č��������ꏊ��Y���W���擾����
//===============================================================================================//
inline KsReal KsPlane::getY( KsReal x, KsReal z )
{
	if( KsFabs( m_normal.y ) < ksTOLERANCE ){
		return 0.0f;
	}
	
	return ( -( m_normal.x*x + m_normal.z*z + m_distance )/m_normal.y );
}

//===============================================================================================//
// XY���ʂ��琂����L�΂��Č��������ꏊ��Z���W���擾����
//===============================================================================================//
inline KsReal KsPlane::getZ( KsReal x, KsReal y )
{
	if( KsFabs( m_normal.y ) < ksTOLERANCE ){
		return 0.0f;
	}

	return ( -( m_normal.x*x + m_normal.y*y + m_distance )/m_normal.z );
}

//===============================================================================================//
// YZ���ʂ��琂����L�΂��Č����������W���擾����
//===============================================================================================//
inline KsVector3d KsPlane::getPointX( KsReal y, KsReal z )
{
	if( KsFabs( m_normal.x ) < ksTOLERANCE ){
		return KsVector3d( 0.0f, y, z );
	}
	
	return  KsVector3d( ( -( m_normal.y*y + m_normal.z*z + m_distance )/m_normal.x ), y, z );
}

//===============================================================================================//
// XZ���ʂ��琂����L�΂��Č����������W���擾����
//===============================================================================================//
inline KsVector3d KsPlane::getPointY( KsReal x, KsReal z )
{
	if( KsFabs( m_normal.y ) < ksTOLERANCE ){
		return KsVector3d( x, 0.0f, z );
	}
	
	return KsVector3d( x, ( -( m_normal.x*x + m_normal.z*z + m_distance )/m_normal.y ), z );
}

//===============================================================================================//
// XY���ʂ��琂����L�΂��Č����������W���擾����
//===============================================================================================//
inline KsVector3d KsPlane::getPointZ( KsReal x, KsReal y )
{
	if( KsFabs( m_normal.y ) < ksTOLERANCE ){
		return KsVector3d( x, y, 0.0f );
	}

	return KsVector3d( x, y, ( -( m_normal.x*x + m_normal.y*y + m_distance )/m_normal.z ) );
}

//===============================================================================================//
// ���ʏ��1�_���擾����
//===============================================================================================//
inline KsVector3d KsPlane::getOnPoint() const
{
	return	( m_normal*( -m_distance ) ); 
}

//===============================================================================================//
// �_�ƕ��ʂ̋��������߂�
//===============================================================================================//
inline KsReal KsPlane::distance( const KsVector3d& refPoint ) const 
{
	return ( m_normal.dotProduct( refPoint ) + m_distance ); 
}

//===============================================================================================//
// ���ʂ������܂�
//===============================================================================================//
inline KsPlane& KsPlane::operator = ( const KsPlane& refPlane )
{
	m_normal   = refPlane.m_normal;
	m_distance = refPlane.m_distance;
	
	return ( *this );
}

//===============================================================================================//
// ���ʂ����������ǂ����𔻒肷��
//===============================================================================================//
inline KsBool KsPlane::operator == ( const KsPlane& refPlane ) const 
{
	return ( ( KsFabs( refPlane.m_distance - m_distance ) < ksTOLERANCE ) &&  ( refPlane.m_normal == m_normal ) );
}

//===============================================================================================//
// ���ʂ��������Ȃ����ǂ����𔻒肷��
//===============================================================================================//
inline KsBool KsPlane::operator != ( const KsPlane& refPlane ) const 
{
	return ( ( KsFabs( refPlane.m_distance - m_distance ) > ksTOLERANCE ) ||  ( refPlane.m_normal != m_normal ) );
}


