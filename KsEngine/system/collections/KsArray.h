/************************************************************************************************/
/** 
 * @file		KsArray.h
 * @brief		�ϒ��z��
 * @author		Tsukasa Kato
 * @date		2008/02/06
 * @since		2008/02/06
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSARRAY_H__
#define __KSARRAY_H__

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
* �ϒ��z��
* @class		KsArray
* @brief		�ϒ��z��
* @since		2008/02/06
* @author		Tsukasa Kato
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
									KsArray( KsUInt32 size ) : m_data( 0 ), m_allocSize( 0 ), m_size( 0 ){ this->arrayRalloc( size ); }
				
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
			if( other.m_allocSize == 0 )	{ m_data = 0; }
			else							{ m_data = new T[ other.m_allocSize ]; }

			// �J�E���g
			m_size = other.m_size;
		
			// �m�ۃT�C�Y
			m_allocSize = other.m_allocSize;

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
		void						arrayRalloc( KsUInt32 size )
		{
			T*	temp = m_data;
		
			m_data		= new T[ size ];
			m_allocSize = size;
		
			KsUInt32 end = m_size < size ? m_size : size;

			if( m_allocSize < m_size ){ m_size = m_allocSize; }

			if( temp )
			{
				for( KsUInt32 i=0; i<end; ++i ){
					m_data[ i ] = temp[ i ];
				}

				delete [] temp;
			}
		}
	
		/**
		 * �z��Ɍ�납��v�f��ǉ�����
		 * @param	data			�ǉ�����v�f
		 */
		void						push_back( const T& data )
		{
			if( m_size + 1 > m_allocSize )
			{
				this->arrayRalloc( m_size * 2 + 1 ); 
			}

			m_data[ m_size++ ] = data;
		}
	
		/**
		 * �z��Ɍ�납��v�f��ǉ�����
		 * @param	index			�ǉ��f�[�^�̃C���f�b�N�X
		 * @param	data			�ǉ�����v�f
		 */
		void						insert( KsUInt32 index, const T& data )
		{
			if( index + 1 > m_allocSize )
			{
				this->arrayRalloc( m_size * 2 + 1 ); 
			}

			if( m_size + 1 > m_allocSize )
			{
				this->arrayRalloc( m_size * 2 + 1 ); 
			}

			if( m_size > 0 )
			{
				// �w��C���f�b�N�X�̃f�[�^�������ăf�[�^���l�߂�
				for ( KsUInt32 i=m_size-1; i>=index; i-- )
				{
					m_data[ i+1 ] = m_data[ i ];	
				}
			}
			
			m_data[ index ] = data;

			//if( m_size >= index )
			//{
				++m_size;
			//}
			//else
			//{
				//m_size = index + 1;
			//}
		}

		/**
		 * �z�񂩂�폜����
		 * @param	index			�����f�[�^�̃C���f�b�N�X
		 */
		void						erase( KsUInt32 index )
		{
			// �w��C���f�b�N�X�̃f�[�^�������ăf�[�^���l�߂�
			for ( KsUInt32 i=index+1; i<m_size; ++i )
			{
				m_data[ i-1 ] = m_data[ i ];
			}

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
		 * ���Z�b�g����
		 */
		void						reset()
		{
			m_size = 0;
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
		T*							m_data;			/**< �f�[�^���擾����			*/
		KsUInt32					m_allocSize;	/**< �m�ۃT�C�Y���擾����		*/
		KsUInt32					m_size;			/**< �z��̗v�f�����擾����	*/
};


#endif	/* __KSARRAY_H__ */

