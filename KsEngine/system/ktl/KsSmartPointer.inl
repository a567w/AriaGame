
/*************************************************************************************************/
/* explicit �����I�Ȍ^�`�F�b�N�p */
/*************************************************************************************************/
template< typename T > 
KsSmartPtr< T >::KsSmartPtr( T* p ) : m_ptr( p )
{
	m_pPrev = m_pNext = this;
}

/*************************************************************************************************/
/*
 * �R�s�[�R���X�g���N�^
 */
/*************************************************************************************************/
template< typename T > 
KsSmartPtr< T >::KsSmartPtr( const KsSmartPtr<T>& ref ) : m_ptr( ref.m_ptr )
{
	m_pNext          = ref.m_pNext;
	m_pNext->m_pPrev = this;
	m_pPrev          = const_cast< SmartPtr<T>* >( &ref );
	m_pPrev->m_pNext = this;
}

/*************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/*************************************************************************************************/
template< typename T > 
KsSmartPtr< T >::~KsSmartPtr()
{
	Deleter();
};

/*************************************************************************************************/
/*
 * �폜����
 */
/*************************************************************************************************/
template< typename T > 
void KsSmartPtr< T >::destroy()
{
	if( m_pNext == this ){
		delete m_ptr;
	}
	else{
		m_pPrev->m_pNext = m_pNext;
		m_pNext->m_pPrev = m_pPrev;
	}
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
template< typename T > 
KsInt32 KsSmartPtr< T >::getCount() const
{
	const KsSmartPtrObject*		pTemp = m_pNext;
	KsInt32					count = 1;

	while( pTemp ){
		++count;
		pTemp = pTemp->m_pNext;
	}
	return count;
}

/*************************************************************************************************/
/*
 * = ���Z�q�I�[�o�[���[�h
 */
/*************************************************************************************************/
template< typename T > 
KsSmartPtr< T >& KsSmartPtr< T >::operator=( const KsSmartPtr<T>& ref )
{
	if( m_ptr != rhs.m_ptr )
	{
		// �����������|�C���^���m�ۂ��Ă�����J������
		Deleter();
		m_ptr            = ref.m_ptr;
		m_pNext          = ref.m_pNext;
		m_pNext->m_pPrev = this;
		m_pPrev          = const_cast< SmartPtr<T>* >( &ref );
		m_pPrev->m_pNext = this;
	}

	return (*this);
}

/*************************************************************************************************/
/*
 *  = ���Z�q�I�[�o�[���[�h
 */
/*************************************************************************************************/
template< typename T > 
KsSmartPtr< T >& KsSmartPtr< T >::operator=( const T* ptr )
{
	//�Ƃ肠�����J������
	Deleter();
	m_ptr   = const_cast<T*>( ptr );
	m_pPrev = this;
	m_pNext = this;

	return (*this);
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
template< typename T > 
KsBool KsSmartPtr< T >::operator < ( const KsSmartPtr<T>& ref ) const
{
	return ( *m_ptr < *ref->Get() );
}


