/************************************************************************************************/
/** 
 * @file		KsSingleton.h
 * @brief		�V���O���g��
 * @author		Tsukasa Kato
 * @data		2005/06/27
 * @since		2005/06/27
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSINGLETON_H__
#define __KSSINGLETON_H__

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
	* @class	KsSingleton
	* @brief	�V���O���g���N���X
	* @author	Tsukasa Kato
	* @data	2005/06/27
	* @since   2005/06/27
	* @note	�d�l����Ƃ��́A�K���p�����Ă������B
	*/
/************************************************************************************************/
template< typename T > class KsSingleton
{
	protected:
		static	T*					m_pInstance;		/**< �C���X�^���X	*/
	
	public:
    	/**
			* �R���X�g���N�^
			*/
									KsSingleton() { m_pInstance = static_cast< T* >( this ); }

    	/**
    		* �f�X�g���N�^
    		*/
		virtual						~KsSingleton() { m_pInstance = 0; }
		
		/**
			* �V���O���g���̎Q�Ƃ��擾
			* @return					�V���O���g���̎Q��
			*/
		static T&					getInstance() { return ( *m_pInstance );  }
		
		/**
			* �V���O���g���̃|�C���^���擾
			* @return					�V���O���g���̃|�C���^
			*/
		static T*					getInstancePtr() {  return ( m_pInstance );  }
};

/************************************************************************************************/
/**
	* @class	KsSingletonDeclare
	* @brief	�V���O���g���N���X
	* @author	Tsukasa Kato
	* @data	2005/06/27
	* @since   2005/06/27
	* @note	�d�l����Ƃ��́A�K���p�����Ă������B
	*/
/************************************************************************************************/
template< typename T > class KsSingletonDeclare
{
	protected:
		static	T*					m_pInstance;		/**< �C���X�^���X	*/
	
	protected:
    	/**
			* �R���X�g���N�^
			*/
									KsSingletonDeclare(){}

    	/**
    		* �f�X�g���N�^
    		*/
		virtual						~KsSingletonDeclare(){}
		
	public:

		/**
			* �C���X�^���X�̐���
			* @return					�������ꂽ�C���X�^���X
			*/
		static T*					createInstance() { if( !m_pInstance ) m_pInstance = new T; return m_pInstance; }


		/**
			* �C���X�^���X�̔j��
			*/
		static void					destoryInstance() { ksDELETE( m_pInstance ); }

		/**
			* �V���O���g���̎Q�Ƃ��擾
			* @return					�V���O���g���̎Q��
			*/
		static T&					getInstance() { return ( *m_pInstance );  }
		
		/**
			* �V���O���g���̃|�C���^���擾
			* @return					�V���O���g���̃|�C���^
			*/
		static T*					getInstancePtr() {  return ( m_pInstance );  }
};


#endif		/* __KSSINGLETON_H__ */


