/************************************************************************************************/
/** 
 * @file		KsMatrix3x3.h
 * @brief		�}�g���b�N�X����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSTRANSFORM_H__
#define __KSTRANSFORM_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsVector3d.h"
#include "KsMatrix3x3.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*************************************************************************************************/
/**
 * @class	KsMatrix3x3
 * @brief	�}�g���b�N�X����N���X
 * @author	Tsukasa Kato
 * @date	----/--/--
 * @since	----/--/--
 */
/*************************************************************************************************/
class ksENGINE_API KsTransform
{
	public:
		KsTransform();
		KsTransform( const KsQuaternion& q, const KsVector3d& c = KsVector3d::ZERO );
		KsTransform( const KsMatrix3x3& b, const KsVector3d& c = KsVector3d::ZERO );
		KsTransform( const KsTransform& other );

		KsTransform& operator=(const KsTransform& other)
		{
			m_basis = other.m_basis;
			m_origin = other.m_origin;
			return *this;
		}


		void mult(const KsTransform& t1, const KsTransform& t2)
		{
			m_basis  = t1.m_basis  * t2.m_basis;
			m_origin.set( t1.m_origin.x * t2.m_origin.x, t1.m_origin.y * t2.m_origin.y, t1.m_origin.z * t2.m_origin.z );
		}

		KsVector3d operator()(const KsVector3d& v) const
		{
			return KsVector3d( 
				(m_basis.m11 * v.x + m_basis.m12 * v.y + m_basis.m13 * v.z  ) + m_origin.x, 
				(m_basis.m21 * v.x + m_basis.m22 * v.y + m_basis.m23 * v.z  ) + m_origin.y, 
				(m_basis.m31 * v.x + m_basis.m32 * v.y + m_basis.m33 * v.z  ) + m_origin.z );
		}


		KsVector3d operator*(const KsVector3d& v) const
		{
			return (*this)(v);
		}

		KsQuaternion operator*(const KsQuaternion& q) const
		{
			return getRotation() * q;
		}

		KsMatrix3x3&        getBasis()          { return m_basis; }

		const KsMatrix3x3&  getBasis()    const { return m_basis; }

		KsVector3d&         getOrigin()         { return m_origin; }
		const KsVector3d&   getOrigin()   const { return m_origin; }

		KsQuaternion getRotation() const 
		{ 
			return m_basis.getRotate();
		}

		void setOrigin(const KsVector3d& origin) 
		{ 
			m_origin = origin;
		}

		void setBasis(const KsMatrix3x3& basis)
		{ 
			m_basis = basis;
		}


		void setRotate(const KsQuaternion& q)
		{
			m_basis.set(q);
		}

		KsTransform& operator*=(const KsTransform& t) 
		{
			m_origin += m_basis * t.m_origin;
			m_basis *= t.m_basis;
			return *this;
		}

		KsTransform inverse() const
		{ 
			KsMatrix3x3 inv = m_basis;
			inv.transpose();
			return KsTransform(inv, inv * -m_origin);
		}

		KsTransform operator*(const KsTransform& t) const;


	private:
		KsMatrix3x3			m_basis;
		KsVector3d			m_origin;

	public:
		/**
		 * �P�ʍs��
		 */
		static const KsTransform		IDENTITY;
};


/*************************************************************************************************/
/*---------------------------<< �C�����C�������w�b�_�[�t�@�C�� >>------------------------------------*/
								#include "KsEngine/math/KsTransform.inl"
/*-----------------------------------------------------------------------------------------------*/
/*************************************************************************************************/


#endif /* __KSTRANSFORM_H__ */


