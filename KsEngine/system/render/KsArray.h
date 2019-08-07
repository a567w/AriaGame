/************************************************************************************************/
/** 
 * @file		KsArray.h
 * @brief		�ϒ��z��(STL��vector�݂���)
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSARRAY_H__
#define __KSARRAY_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"

/************************************************************************************************/
/**
 *  �ϒ��z��
 *	@class		KsArray
 *	@brief		�z��
 *	@since		2003/10/25
 *	@author		tukasa kato
 */
/************************************************************************************************/
template <typename T> class KsArray
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsArray() : m_data( 0 ), m_allocSize( 0 ), m_size( 0 ) {}
		
		/**
		 * �R���X�g���N�^
		 * @param	size			�m�ۂ���T�C�Y
		 */
									KsArray( KsUInt32 size ) : m_data( 0 ), m_allocSize( 0 ), m_size( 0 ){ this->realloc( size ); }
					
		/**
		 * �f�X�g���N�^
		 */
									~KsArray(){ if( m_data ){ delete [] m_data; }	}

		/**
		 * ���( operator )
		 * @param	other			�������z��
		 */
		void						operator = ( const KsArray< T >& other )
		{
			if( m_data ){ delete [] m_data; }

			// �T�C�Y�`�F�b�N
			if( other.allocSize == 0 )	{ m_data = 0; }
			else						{ m_data = new T[ other.allocSize ]; }

			// �J�E���g
			m_size = other.m_size;
			
			// �m�ۃT�C�Y
			allocSize = other.allocSize;

			for( KsUInt32 i=0; i<other.m_size; ++i ){ m_data[ i ] = other.m_data[ i ]; }
		}

		/**
		 * �z����̗v�f���擾����( operator )
		 * @param	index			�擾����C���f�b�N�X
		 */
		T&							operator []( KsUInt32 index )		{ return m_data[ index ]; }
		
		/**
		 * �z����̗v�f���擾����( operator )
		 * @param	index			�擾����C���f�b�N�X
		 */
		const T&					operator []( KsUInt32 index ) const { return m_data[ index ]; }

		/**
		 * �V�����������[���m�ۂ��Ȃ���
		 * @param	size			�V�����m�ۂ���T�C�Y
		 */
		void						realloc( KsUInt32 size )
		{
			T*	temp = m_data;
			
			m_data		= new T[ size ];
			m_allocSize = size;
			
			KsUInt32 end = m_size < size ? m_size : size;

			for( KsUInt32 i=0; i<end; ++i ){ m_data[ i ] = temp[ i ]; }

			if( m_allocSize < m_size ){ m_size = m_allocSize; }
			
			delete [] temp;
		}
		
		/**
		 * �z��Ɍ�납��v�f��ǉ�����
		 * @param	data			�ǉ�����v�f
		 */
		void						push_back( const T& data )
		{
			if( m_size + 1 > m_allocSize ){ this->realloc( m_size * 2 + 1 ); }

			m_data[ m_size++ ] = data;
		}
		
		/**
		 * �z�񂩂�폜����
		 * @param	index			�����f�[�^�̃C���f�b�N�X
		 */
		void						erase( KsUInt32 index )
		{
			// �w��C���f�b�N�X�̃f�[�^�������ăf�[�^���l�߂�
			for ( KsUInt32 i=index+1; i<m_size; ++i ){ m_data[ i-1 ] = m_data[ i ]; }

			--m_size;
		}

		/**
		 * �z�񂩂�폜����
		 * @param	index			�����f�[�^�̃C���f�b�N�X
		 * @param	count			�w��C���f�b�N�X���������
		 */
		void						erase( KsUInt32 index, KsUInt32 count )
		{
			for( KsUInt32 i=(index + count); i<m_size; ++i ){
				m_data[ i-count ] = m_data[ i ];
			}

			m_size -= count;
		}
		
		/**
		 * �z����N���A�[����
		 */
		void						clear()
		{
			if( m_data ){ delete [] m_data; }
			m_data      = 0;
			m_allocSize = 0;
			m_size		= 0;
		}
		
		/**
		 * �|�C���^���擾����
		 * @return					�z��̃|�C���^
		 */
		T*							pointer()				{ return m_data;			}
		
		/**
		 * �z�񂪋󂩂ǂ������`�F�b�N����
		 * @retval	ksTRUE			�z��͋�
		 * @retval	ksFALSE			�󂶂�Ȃ�
		 */
		KsBool						empty()			const	{ return ( m_size == 0 );	}
		
		/**
		 * �m�ۂ���T�C�Y
		 * @return					�m�ۂ���Ă���z��̐�
		 */
		KsUInt32					getAllocSize()	const	{ return m_allocSize;		}

		/**
		 * �J�E���g�����擾����
		 * @return					�g���Ă���z��̐�
		 */
		KsUInt32					size()			const	{ return m_size;			}

	private:
		T*							m_data;				/**< �f�[�^���擾����			*/
		KsUInt32					m_allocSize;		/**< �m�ۃT�C�Y���擾����		*/
		KsUInt32					m_size;				/**< �z��̗v�f�����擾����	*/
};

#endif	/* __KSARRAY_H__ */
