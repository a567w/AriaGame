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
