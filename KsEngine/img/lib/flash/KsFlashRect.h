/************************************************************************************************/
/** 
 * @file		KsFlashRect.h
 * @brief		FLASH�pRect
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSFLASHRECT_H__
#define __KSFLASHRECT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsCore.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsFlashRect
 * @brief		FLASH�pRect
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		�Ȃ�
 */
/************************************************************************************************/
class KsFlashRect
{
	public:
		/**
		 * �R���X�g���N�^
		 * @param	x1		����ʒu�W
		 * @param	y1		����ʒu�W
		 * @param	x2		����ʒu�W
		 * @param	y2		����ʒu�W
		 */
							KsFlashRect( KsInt32 x1, KsInt32 y1, KsInt32 x2, KsInt32 y2 );

		/**
		 * �f�t�H���g�R���X�g���N�^
		 */
							KsFlashRect();

		/**
		 * �f�X�g���N�^
		 */
	    virtual			~KsFlashRect();

		/**
		 * ��`����Ă��邩�̃`�F�b�N
		 * @retval	ksTRUE	
		 * @retval	ksFALSE	
		 */
	    KsBool				isDefined() const { return m_defined; }

		/**
		 * �R���X�g���N�^
		 * @param	x1		����ʒu�W
		 * @param	y1		����ʒu�W
		 * @param	x2		����ʒu�W
		 * @param	y2		����ʒu�W
		 */
		void				setRect( KsInt32 x1, KsInt32 y1, KsInt32 x2, KsInt32 y2 );
	    
	    KsInt32				getX1() const { return m_x1; }
	    KsInt32				getX2() const { return m_x2; }
	    KsInt32				getY1() const { return m_y1; }
	    KsInt32				getY2() const { return m_y2; }

	    void				boundWith( const KsFlashRect &rect );

	private:
	    KsInt32				m_x1;			/**< */
	    KsInt32				m_y1;			/**< */
	    KsInt32				m_x2;			/**< */
	    KsInt32				m_y2;			/**< */
	    KsBool				m_defined;		/**< */
};


KsFlashRect::KsFlashRect()
	: x1( 0 )
	, y1( 0 )
	, x2( 0 )
	, y2( 0 )
	, m_defined( ksFALSE )
{
}

/**
* �R���X�g���N�^
* @param	x1		����ʒu�W
* @param	y1		����ʒu�W
* @param	x2		����ʒu�W
* @param	y2		����ʒu�W
*/
KsFlashRect::KsFlashRect( KsInt32 x1, KsInt32 y1, KsInt32 x2, KsInt32 y2 )
	: m_x1( x1 )
	, m_y1( y1 )
	, m_x2( x2 )
	, m_y2( y2 )
	, m_defined( ksFALSE )
{
}

KsFlashRect::~KsFlashRect()
{
}

void KsFlashRect::setRect( KsInt32 x1, KsInt32 y1, KsInt32 x2, KsInt32 y2 )
{
	m_x1 = x1;
	m_y1 = y1;
	m_x2 = x2;
	m_y2 = y2;
}

void KsFlashRect::boundWith( const KsFlashRect &rect )
{
	x1 = min(x1,r.x1);
	x2 = max(x2, r.x2);
	y1 = min(y1,r.y1);
	y2 = max(y2, r.y2);
}

#endif	/* __KSFLASHRECT_H__ */

