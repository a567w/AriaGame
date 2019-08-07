/************************************************************************************************/
/** 
 * @file		KsBoundingSphere.h
 * @brief		�o�E���f�B���O�X�t�B�A
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBOUNDINGSPHERE_H__
#define __KSBOUNDINGSPHERE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsBoundingSphere
 * @brief		�o�E���f�B���O�X�t�B�A
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsBoundingSphere
{
	private:
		KsVector3d				m_center;	/**< ���̒��S�_�B	*/
		KsReal					m_radius;	/**< ���̔��a		*/

	public:
		/**
		 * �R���X�g���N�^
		 */
		KsBoundingSphere();

		/**
		 * �R���X�g���N�^
		 * @brief	KsBoundingSphere �̐V�����C���X�^���X���쐬���܂��B
		 * @param	center		���̒��S�_�B
		 * @param	radius		���̔��a�B
		 */
		KsBoundingSphere( const KsVector3d& center, KsReal radius );

		/**
		 * �R���X�g���N�^
		 * @brief	KsBoundingSphere �̐V�����C���X�^���X���쐬���܂��B
		 * @param	cx			���̒��S�_��X���W�B
		 * @param	cy			���̒��S�_��X���W�B
		 * @param	cz			���̒��S�_��X���W�B
		 * @param	radius		���̔��a�B
		 */
		KsBoundingSphere( KsReal cx, KsReal cy, KsReal cz, KsReal radius );

		/**
		 * �`��Ăяo�����Ɏg�p����钸�_�̐����擾���܂��B
		 * @return	���̒��S�_
		 */
		const KsVector3d&		getCenter() { return m_center; }

		/**
		 * �����_�����O����v���~�e�B�u�̐����擾���܂��B
		 * @return	���̔��a
		 */
		KsReal					getRadius() const { return m_radius; }

		/**
		 * KsBoundingSphere ���Z�b�g���܂��B
		 * @param	center		���̒��S�_�B
		 * @param	radius		���̔��a�B
		 */
		void					set( const KsVector3d& center, KsReal radius );

		/**
		 * KsBoundingSphere ���Z�b�g���܂��B
		 * @param	cx			���̒��S�_��X���W�B
		 * @param	cy			���̒��S�_��X���W�B
		 * @param	cz			���̒��S�_��X���W�B
		 * @param	radius		���̔��a�B
		 */
		void					set( KsReal cx, KsReal cy, KsReal cz, KsReal radius );

		/**
		 * ���̒��S�_���Z�b�g���܂��B
		 * @param	center		���̒��S�_�B
		 */
		void					setCenter( const KsVector3d& center ) { m_center = center; }

		/**
		 * ���̒��S�_���Z�b�g���܂��B
		 * @param	cx			���̒��S�_��X���W�B
		 * @param	cy			���̒��S�_��X���W�B
		 * @param	cz			���̒��S�_��X���W�B
		 */
		void					setCenter( KsReal cx, KsReal cy, KsReal cz ) { m_center.set( cx, cy, cz ); }

		/**
		 * �����_�����O����v���~�e�B�u�̐����Z�b�g���܂��B
		 * @param	radius		���̔��a
		 */
		void					setRadius( KsReal radius ) { m_radius = radius; }
};

#endif		/* __KSBOUNDINGSPHERE_H__ */



