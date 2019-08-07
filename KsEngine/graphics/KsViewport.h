/************************************************************************************************/
/** 
 * @file		KsViewport.h
 * @brief		�r���[�|�[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSVIEWPORT_H__
#define __KSVIEWPORT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsViewport
 * @brief		�r���[�|�[�g�N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsViewport
{
	public:
		KsInt32					m_x;		/**< X���W				*/
		KsInt32					m_y;		/**< Y���W				*/
		KsInt32					m_w;		/**< ��					*/
		KsInt32					m_h;		/**< ����				*/
		KsReal					m_minZ;		/**< minZ�l				*/
		KsReal					m_maxZ;		/**< maxZ�l				*/
		
		/**
		 * �R���X�g���N�^
		 * @note ���ׂ� 0�ŏ�����
		 */
								KsViewport() : m_x( 0 ), m_y( 0 ), m_w( 0 ), m_h( 0 ), m_minZ( 0.0f ), m_maxZ( 0.0f ) {}
		
		/**
		 * �R���X�g���N�^
		 * @param		x		X���W
		 * @param		y		X���W
		 * @param		w		��
		 * @param		h		����
		 * @param		near	near�N���b�v�l
		 * @param		far		far�N���b�v�l
		 */
								KsViewport( KsInt32 x, KsInt32 y, KsInt32 w, KsInt32 h, KsReal minZ, KsReal maxZ ) : m_x( x ), m_y( y ), m_w( w ), m_h( h ), m_minZ( minZ ), m_maxZ( maxZ ) {}
	
		/**
		 * �Z�b�g
		 * @param		x		X���W
		 * @param		y		X���W
		 * @param		w		��
		 * @param		h		����
 		 * @param		near	near�N���b�v�l
		 * @param		far		far�N���b�v�l
		 */
		void					set( KsInt32 x, KsInt32 y, KsInt32 w, KsInt32 h, KsReal minZ, KsReal maxZ ) { m_x = x; m_y = y; m_w = w; m_h = h; m_minZ = minZ; m_maxZ = maxZ; }


		KsBool					operator == (const KsViewport& vp) const { return (m_x == vp.m_x) && (m_y == vp.m_y) && (m_w == vp.m_w) && (m_h == vp.m_h) && (m_minZ == vp.m_minZ) && (m_maxZ == vp.m_maxZ); }
		KsBool					operator != (const KsViewport& vp) const { return !operator == (vp); }
};


#endif		/* __KSVIEWPORT_H__ */



