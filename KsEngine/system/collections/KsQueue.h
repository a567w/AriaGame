/************************************************************************************************/
/**
 * @file		KsQueue.h
 * @brief		�L���[
 * @author		Tsukasa Kato
 * @date		2008/02/06
 * @since		2008/02/06
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSQUEUE_H__
#define __KSQUEUE_H__

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
 * @class		KsQueue
 * @brief		�L���[
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/
template < typename T, KsInt32 max > class KsQueue
{
	public:
		typedef T					valueType;

	public:
		/**
		 * �R���X�g���N�^
		 */
									KsQueue() : m_top( 0 ), m_end( 0 ), m_size( 0 ) {}
	
		/**
		 * �f�X�g���N�^
		 */
									~KsQueue() {}

		/**
 		 * �X�^�b�N���󂩂ǂ������`�F�b�N����
		 * @retval		ksTRUE			��ł�
		 * @retval		ksFALSE			�󂶂�Ȃ�
		 */
		KsBool						empty() const { return ( m_size == 0 ); }

		/**
		 * �f�[�^���i�[���܂�
		 * @param		T				�i�[����f�[�^
		 */
		void						push( const T& data )
		{
			if( m_size < max ){
				m_data[ m_end ] = data;
				if( ++m_end > max-1 ){
					m_end = 0;
				}
				m_size++;
			}	
		}
	
		/**
		 * �f�[�^�����o���܂�
		 * @return						��O�i�[�����f�[�^
		 */
		T&							pop() 
		{
			if( m_size > 0 ){
				KsInt32		top = m_top;
				if( ++m_top > max-1 ){
					m_top = 0;
				}
				m_size--;
				return m_data[ top ];
			}
			return m_data[ 0 ];
		}

		/**
		 * �f�[�^�����o���܂�
		 * @return						��O�i�[�����f�[�^
		 */
		const T&					pop() const 
		{
			if( m_size > 0 ){
				KsInt32		top = m_top;
				if( ++m_top > max-1 ){
					m_top = 0;
				}
				m_size--;
				return m_data[ top ];
			}
			return m_data[ 0 ];
		}

		/**
		 * �f�[�^�����o���܂�
		 * @return						��O�i�[�����f�[�^
		 */
		T&							top() { return m_data[ m_top ]; }

		/**
		 * �f�[�^�����o���܂�
		 * @return						��O�i�[�����f�[�^
		 */
		const T&					top() const { return m_data[ m_top ]; }

		/**
		 * �f�[�^�����o���܂�
		 * @return						��O�i�[�����f�[�^
		 */
		T&							end()
		{
			if( m_end ){
				return m_data[ m_end-1 ];
			}
			return m_data[ 0 ];
		}

		/**
		 * �f�[�^�����o���܂�
		 * @return						��O�i�[�����f�[�^
		 */
		const T&					end() const
		{
			if( m_end ){
				return m_data[ m_end-1 ];
			}
			return m_data[ 0 ];
		}

		/**
		 * �w��f�[�^���擾���܂��B
		 * @param  		num				�擪����̃f�[�^�ԍ�
		 * @return						�f�[�^
		 */
		T&							getData( KsInt32 num ) 
		{
			if( num < max ){
				KsInt32	index = m_top + num;
				if( index > max-1 ){
					index = 0;
				}
				return m_data[ index ];
			}
			return m_data[ 0 ];
		}

		/**
		 * �w��f�[�^���擾���܂��B
		 * @param  		num				�擪����̃f�[�^�ԍ�
		 * @return						�f�[�^
		 */
		const T&					getData( KsInt32 num ) const 
		{
			if( num < max ){
				KsInt32	index = m_top + num;
				if( index > max-1 ){
					index = 0;
				}
				return m_data[ index ];
			}
			return m_data[ 0 ];
		}
	
		/**
		 * �l��ς���
		 * @param		index			����������f�[�^�̃C���f�b�N�X
		 * @param		data			�f�[�^
		 */
		void						swap( KsInt32 index, const T& data )
		{
			m_data[ index ] = data;
		}

		/**
		 * �N���A�[����
		 */
		void						clear() { m_top = 0; m_end = 0; m_size = 0; }

		/**
		 * ���݊i�[����Ă���f�[�^�̐����擾
		 * @return						�i�[����Ă���f�[�^�̐�
		 */
		KsInt32						size()	const { return m_size;	}
	
		/**
		 * �i�[�ł���f�[�^�̐����擾
		 * @return						�i�[�ł���f�[�^�̐�
		 */
		KsInt32						getMax()	const { return max;	}

	private:
		T							m_data[ max ];		/**< �f�[�^						*/
		KsInt32						m_top;				/**< �L���[���f�[�^�̐擪�ʒu		*/
		KsInt32						m_end;				/**< �L���[���f�[�^�̍Ō�ʒu		*/
		KsInt32						m_size;				/**< �i�[����Ă���f�[�^�̐�		*/
};

#endif	/* __KSQUEUE_H__ */


