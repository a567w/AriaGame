/************************************************************************************************/
/** 
 * @file		KsSwfRect.h
 * @brief		SWF�pRect
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFRECT_H__
#define __KSSWFRECT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSwfRect
 * @brief		SWF�pRect
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		�Ȃ�
 */
/************************************************************************************************/
class ksSWF_API KsSwfRect
{
	public:
		/**
		 * �R���X�g���N�^
		 */
								KsSwfRect();

		/**
		 * �R���X�g���N�^
		 */
								KsSwfRect( KsInt32 x1, KsInt32 y1, KsInt32 x2, KsInt32 y2 );
	    
		/**
		 * �f�X�g���N�^
		 */
								~KsSwfRect();

	    
	    void					boundWith( const KsSwfRect& rect );
		void					setRect( KsInt32 x1, KsInt32 y1, KsInt32 x2, KsInt32 y2 );
	    
		KsBool					isDefined() { return m_defined; }
	    KsInt32					getX1() const { return m_x1; }
		KsInt32					getY1() const { return m_y1; }
	    KsInt32					getX2() const { return m_x2; }
	    KsInt32					getY2() const { return m_y2; }

	private:
	    KsInt32					m_x1; 
	    KsInt32					m_y1;
	    KsInt32					m_x2;
	    KsInt32					m_y2;
	    KsBool					m_defined;
};

#endif	/* __KSSWFRECT_H__ */
