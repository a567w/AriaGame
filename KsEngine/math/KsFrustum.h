/************************************************************************************************/
/** 
 * @file		KsFrustum.h
 * @brief		ビューポー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSFRUSTUM_H__
#define __KSFRUSTUM_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsType.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsPlane;

/************************************************************************************************/
/**
 * 
 * @class	
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
enum ksFRUSTUM_PLANE_KIND
{
	ksFRUSTUM_PLANE_NEAR   = 0,
	ksFRUSTUM_PLANE_FAR    = 1,
	ksFRUSTUM_PLANE_LEFT   = 2,
	ksFRUSTUM_PLANE_RIGHT  = 3,
	ksFRUSTUM_PLANE_TOP    = 4,
	ksFRUSTUM_PLANE_BOTTOM = 5
};

/************************************************************************************************/
/**
 * 
 * @class	
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsFrustum
{
	public:
								KsFrustum();
		
		virtual				~KsFrustum();
		
		KsPlane					m_planes[ 6 ];
		
		KsReal					m_near;
		KsReal					m_far;
		
		
		void					RenderOutline();

};

#endif		/* __KSFRUSTUM_H__ */



#if 0

    Frustum::Frustum(float fovy, float aspect, float near, float far)
        {
                // Define a frustum looking along the -ve z axis.
                planes[NEAR] = Plane(Vector3(0,0,1), near);
                planes[FAR]  = Plane(Vector3(0,0,-1), far);

                const Vector3 origin(zero);
                const float tanfy = tan(fovy/2.0f);
                planes[TOP]    = Plane(Vector3( 1.0f, 0.0f, tanfy * aspect), origin);
                planes[BOTTOM] = Plane(Vector3(-1.0f, 0.0f, tanfy * aspect), origin);

                planes[RIGHT] = Plane(Vector3(0.0f,  1.0f, tanfy), origin);
                planes[LEFT]  = Plane(Vector3(0.0f, -1.0f, tanfy), origin);

                for(int p = 0; p < Frustum::PLANE_COUNT; ++p)
                        planes[p] = normalize(planes[p]);
        }

        static void getAllCorners(const Box& boxy, Vector3 c[])
        {
                c[0] = boxy.minCorner();
                c[1] = boxy.maxCorner();
                c[2] = Vector3(c[0].x(), c[1].y(), c[0].z());
                c[3] = Vector3(c[0].x(), c[1].y(), c[1].z());
                c[4] = Vector3(c[0].x(), c[0].y(), c[1].z());
                c[5] = Vector3(c[1].x(), c[1].y(), c[0].z());
                c[6] = Vector3(c[1].x(), c[0].y(), c[0].z());
                c[7] = Vector3(c[1].x(), c[0].y(), c[1].z());
        }

        bool Frustum::intersects(const Box& boxy) const
        {
                const int N_CORNERS = 8;
                Vector3 boxCorners[N_CORNERS];
                getAllCorners(boxy, boxCorners);

                // test all 8 corners against the 6 sides
                // if all points are behind 1 specific plane, we are out
                // if we are in with all points, then we are fully in
                for(int p = 0; p < Frustum::PLANE_COUNT; ++p)
                {
                        int iInCount = N_CORNERS;

                        for(int i = 0; i < N_CORNERS; ++i)
                        {
                                // test point [i] against the planes
                                if (distance(planes[p], boxCorners[i]) > 0.0f)
                                        --iInCount;
                        }

                        // were all the points outside of plane p?
                        if (iInCount == 0)
                                return false;
                }

                return true;
        }

        Frustum transformFrustum(const Matrix& m, const Frustum& f)
        {
                Frustum result;

                for (int i=0; i!=Frustum::PLANE_COUNT; ++i)
                        result.planes[i] = transformPlane(m, f.planes[i]);

                return result;
        }
}

//-----------------------------------------------------------------------------
// Build a frustum from a persepective projection matrix.  The matrix may only
// contain a projection; any rotation, translation or scale will cause the
// constructed frustum to be incorrect.
//-----------------------------------------------------------------------------
VOID ComputeFrustumFromProjection( Frustum* pOut, XMMATRIX* pProjection )
{
    XMASSERT( pOut );
    XMASSERT( pProjection );

    // Corners of the projection frustum in homogenous space.
    static XMVECTOR HomogenousPoints[6] =
    {
        {  1.0f,  0.0f, 1.0f, 1.0f },   // right (at far plane)
        { -1.0f,  0.0f, 1.0f, 1.0f },   // left
        {  0.0f,  1.0f, 1.0f, 1.0f },   // top
        {  0.0f, -1.0f, 1.0f, 1.0f },   // bottom

        { 0.0f, 0.0f, 0.0f, 1.0f },     // near
        { 0.0f, 0.0f, 1.0f, 1.0f }      // far
    };

    XMVECTOR Determinant;
    XMMATRIX matInverse = XMMatrixInverse( &Determinant, *pProjection );

    // Compute the frustum corners in world space.
    XMVECTOR Points[6];

    for( INT i = 0; i < 6; i++ )
    {
        // Transform point.
        Points[i] = XMVector4Transform( HomogenousPoints[i], matInverse );
    }

    pOut->Origin = XMFLOAT3( 0.0f, 0.0f, 0.0f );
    pOut->Orientation = XMFLOAT4( 0.0f, 0.0f, 0.0f, 1.0f );

    // Compute the slopes.
    Points[0] = Points[0] * XMVectorReciprocal( XMVectorSplatZ( Points[0] ) );
    Points[1] = Points[1] * XMVectorReciprocal( XMVectorSplatZ( Points[1] ) );
    Points[2] = Points[2] * XMVectorReciprocal( XMVectorSplatZ( Points[2] ) );
    Points[3] = Points[3] * XMVectorReciprocal( XMVectorSplatZ( Points[3] ) );

    pOut->RightSlope = XMVectorGetX( Points[0] );
    pOut->LeftSlope = XMVectorGetX( Points[1] );
    pOut->TopSlope = XMVectorGetY( Points[2] );
    pOut->BottomSlope = XMVectorGetY( Points[3] );

    // Compute near and far.
    Points[4] = Points[4] * XMVectorReciprocal( XMVectorSplatW( Points[4] ) );
    Points[5] = Points[5] * XMVectorReciprocal( XMVectorSplatW( Points[5] ) );

    pOut->Near = XMVectorGetZ( Points[4] );
    pOut->Far = XMVectorGetZ( Points[5] );

    return;
}



    XMFLOAT3 Origin;            // Origin of the frustum (and projection).
    XMFLOAT4 Orientation;       // Unit quaternion representing rotation.

    FLOAT RightSlope;           // Positive X slope (X/Z).
    FLOAT LeftSlope;            // Negative X slope.
    FLOAT TopSlope;             // Positive Y slope (Y/Z).
    FLOAT BottomSlope;          // Negative Y slope.
    FLOAT Near, Far;            // Z of the near plane and far plane.


	      class Box;

        class NVMATH_CLASS Frustum
        {
        public:
                // Construct a frustum from typical view parameters.  fovy has the same meaning as for glut_perspective_reshaper.
                // The resulting frustum is centred at the origin, pointing along the z-axis.
                Frustum()       {}
                Frustum(float fovy, float aspect, float near, float far);

                // Unlike some intersection methods, we don't bother to distinguish intersects
                // from contains.  A true result could indicate either.
                bool intersects(const Box&) const;

        private:
                friend Frustum transformFrustum(const Matrix&, const Frustum&);

                enum PlaneIndices { NEAR, LEFT, RIGHT, TOP, BOTTOM, FAR, PLANE_COUNT };
                Plane planes[PLANE_COUNT];
        };

        Frustum transformFrustum(const Matrix&, const Frustum&);
class NEOENGINE_API NeFrustum : public NeSRTNode
{
	public:

		/**
		* \enum NEFRUSTUMPLANE
		* \brief Frustum planes
		*/
		enum NEFRUSTUMPLANE
		{
			LEFT        = 0,
			RIGHT       = 1,
			TOP         = 2,
			BOTTOM      = 3,
			FRONT       = 4,
			BACK        = 5,
			NUMPLANES   = 6
		};
	pvCornerPointsWorld[0] = vRightTopNear;
	pvCornerPointsWorld[1] = XMVectorSelect( vRightTopNear, vLeftBottomNear, vGrabX );
	pvCornerPointsWorld[2] = vLeftBottomNear;
	pvCornerPointsWorld[3] = XMVectorSelect( vRightTopNear, vLeftBottomNear,vGrabY );

	pvCornerPointsWorld[4] = vRightTopFar;
	pvCornerPointsWorld[5] = XMVectorSelect( vRightTopFar, vLeftBottomFar, vGrabX );
	pvCornerPointsWorld[6] = vLeftBottomFar;
	pvCornerPointsWorld[7] = XMVectorSelect( vRightTopFar ,vLeftBottomFar, vGrabY );
	public:

		/*! Vertex signs. These indicate which box corner in the AA box should be used as near and far vertex when culling against frustum during rendering. 6 planes in frustum as first index. Second index is vertex component, 0 = x, 1 = y, 2 = z. A value of 0 is positive and 1 is negative */
		unsigned char                   m_aiPVertexSign[6][3];

		/*! N is inverted P but precalculate to gain speed */
		unsigned char                   m_aiNVertexSign[6][3];

		/*! The view matrix corresponding to this frustum */
		NeMatrix                        m_kViewMatrix;

		/*! The equation data (normal and distance) for the 6 frustum planes */
		NePlane                         m_akPlanes[6];

		/*! View vector (which is -zvector of rotation of course)*/
		NeVector3d                      m_kDirection;

		/*! Near plane distance along m_kDirection */
		float                           m_fZNear;

		/*! Far plane distance along m_kDirection */
		float                           m_fZFar;


		/**
		* Resets member data
		*/
		                                NeFrustum();

		/**
		* Test if point is inside volume
		* \param rkPoint                Point to check
		* \return                       true if inside volume, false otherwise
		*/
		virtual bool                    Intersection( const NeVector3d &rkPoint );

		/**
		* Test if line intersects with volume
		* \param rkLine                 Line to check
		* \return                       true if intersection with volume, false otherwise
		*/
		virtual bool                    Intersection( const NeLine &rkLine );

		/**
		* Test if intersection with plane
		* \param rkPlane                Plane to check
		* \return                       true if intersection, false otherwise
		*/
		virtual bool                    Intersection( const NePlane &rkPlane );

		/**
		* Test if intersection with polygon
		* \param rkV0                   First corner
		* \param rkV1                   Second corner
		* \param rkV2                   Third corner
		* \param rkNormal               Optional precalculated normal
		* \return                       true if intersection, false otherwise
		*/
		virtual bool                    Intersection( const NeVector3d &rkV0, const NeVector3d &rkV1, const NeVector3d &rkV2, const NeVector3d &rkNormal = NeVector3d::ORIGO );

		/**
		* Render outlines
		*/
		void                            RenderOutlines();
};



#endif
