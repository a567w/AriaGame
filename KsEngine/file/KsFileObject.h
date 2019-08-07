/*************************************************************************************************/
/**
 * @file	KsFileObject.h
 * @brief	�t�@�C������̊��N���X
 * @author	Tsukasa Kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/*************************************************************************************************/
#ifndef __KSFILEOBJECT_H__
#define __KSFILEOBJECT_H__

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*===============================================================================================*/

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/
#define ksSEEK_SET		( SEEK_SET )
#define ksSEEK_CUR		( SEEK_CUR )
#define ksSEEK_END		( SEEK_END )

/*===============================================================================================*/
/*                                     << �錾 >>                                                */
/*===============================================================================================*/

/*************************************************************************************************/
/**
 * @enum	ksFILE_FLAG
 * @brief	�t�@�C�����J���Ƃ��̃t���O
 */
/*************************************************************************************************/
enum ksFILE_FLAG
{
	ksNONE    = 0,								/**< ��`����ĂȂ�	*/
	ksREAD    = 0x00000001,						/**< �ǂݍ��ݗp		*/
	ksWRITE   = 0x00000002,						/**< �������ݗp		*/
	ksAPPEND  = 0x00000004,						/**< �ǉ������p		*/
	ksBINARY  = 0x00000008,						/**< �o�C�i���p		*/
	ksCOMMIT  = 0x00000016,						/**< �R�~�b�g�p		*/
	ksFILE_FLAG_DEFAULT = ( ksREAD | ksBINARY )	/**< �f�t�H���g		*/
};

/*************************************************************************************************/
/**
 * @enum	ksFILE_STATE
 * @brief	�t�@�C���̏��
 */
/*************************************************************************************************/
enum ksFILE_STATE
{
	ksINVALID,			/**< �����Ȓl				*/
	ksOPEN,				/**< �t�@�C���͊J����Ă���	*/
	ksCLOSED,			/**< �t�@�C���͕��Ă���	*/
};

/*************************************************************************************************/
/**
 * @enum	ksBYTE_OERDER
 * @brief	���g���G���f�B�A�����r�b�N�G���f�B�A�����̃��[�h
 */
/*************************************************************************************************/
enum ksBYTE_ORDER
{
	ksLITTLEENDIAN,		/**< ���g���G���f�B�A��		*/
	ksBIGENDIAN,		/**< �r�b�N�G���f�B�A��		*/
};

/*************************************************************************************************/
/**
 * �t�@�C������p ���p��(32bit)
 */
/*************************************************************************************************/
typedef union _KS_DATA4
{
	KsReal				f;
	KsInt32				i32;
	KsUInt32			u32;
	KsByte				byte[ 4 ];
}KS_DATA4;

/*************************************************************************************************/
/**
 * �t�@�C������p ���p��(16bit)
 */
/*************************************************************************************************/
typedef union _KS_DATA2
{
	KsInt16				s16;
	KsUInt16			u16;
	KsByte				byte[ 2 ];
}KS_DATA2;

/*************************************************************************************************/
/**
 * @class	KsFile
 * @brief	�t�@�C���N���X
 * @author	tsukasa kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/*************************************************************************************************/
class ksENGINE_API KsFileObject
{
	protected:
		ksFILE_STATE					m_state;			/**< �t�@�C���̏��		*/
		ksBYTE_ORDER					m_byteOrder;		/**< �o�C�g�̕��я�		*/
		KsUInt32						m_flags;			/**< �t���O				*/
		KsInt32							m_size;				/**< �t�@�C���T�C�Y		*/
		KsString						m_path;				/**< �t�@�C���̃p�X		*/
		KsString						m_name;				/**< �t�@�C����			*/
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsFileObject() : m_state( ksINVALID ), m_byteOrder( ksLITTLEENDIAN ), m_flags( 0 ), m_size( 0 ) {}

		/**
		 * �f�X�g���N�^
		 * @brief						�t�@�C�����J����Ă��������
		 */
		virtual							~KsFileObject(){}
	
		/**
		 * �t�@�C���p�X���擾����
		 * @return						�t�@�C���̃p�X
		 */
		const KsString&					getPath() const { return m_path; }

		/**
		 * �t�@�C�������擾����
		 * @return						�t�@�C����
		 */
		const KsString&					getName() const { return m_name; }

		/**
		 * ���g���G���f�B�A�����r�b�N�G���f�B�A�������擾����
		 * @return						���g���G���f�B�A�����r�b�N�G���f�B�A�����̃t���O
		 */
		ksBYTE_ORDER					getByteOrder() const { return m_byteOrder; }

		/**
		 * �t�@�C���p�X���Z�b�g����
		 * @param	path				�t�@�C���̃p�X
		 */
		void							setPath( const KsString& path ) { m_path = path; }
		
		/**
		 * �t�@�C�������Z�b�g����
		 * @param	name				�t�@�C����
		 */
		void							setName( const KsString& name ) { m_name = name; }

		/**
		 * ���g���G���f�B�A�����r�b�N�G���f�B�A�������Z�b�g����
		 * @param	byteOrder			���g���G���f�B�A�����r�b�N�G���f�B�A�����̃t���O
		 */
		void							setByteOrder( ksBYTE_ORDER byteOrder ) { m_byteOrder = byteOrder; }
		
		/**
		 * �t�@�C���T�C�Y���擾����
		 * @return						�t�@�C���T�C�Y
		 */
		virtual KsInt32					getSize() const { return m_size; }

		/**
		 * �t�@�C�����J��
 		 * @param	fullPath			�t�@�C���̃t���p�X
		 * @param	flags				�t�@�C���̃I�[�v���t���O
		 * @retval	ksTRUE				����
		 * @retval	ksFALSE				���s
		 */
		virtual KsBool					open( const KsString& fullPath, KsInt32 flags, ksBYTE_ORDER byteOrder=ksLITTLEENDIAN ) = 0;

		/**
		 * �t�@�C�����J��
		 * @param	path				�t�@�C���̃p�X
		 * @param	fileName			�t�@�C����
		 * @param	flags				�t�@�C���̃I�[�v���t���O
		 * @retval	ksTRUE				����
		 * @retval	ksFALSE				���s
		 */
		virtual KsBool					open( const KsString& path = _T(""), const KsString& fileName = _T(""), KsInt32 flags = ksNONE ) = 0;

		/**
		 * �t�@�C�������
		 */
		virtual void					close() = 0;

		/**
		 * �t�@�C���|�C���^���擾����
		 * @return						�t�@�C���|�C���^
		 */
		virtual const void*				getFilePtr() const = 0;

		/**
		 * �t�@�C�����J����ėL���ɂȂ��Ă��邩���`�F�b�N����
		 * @retval	ksTRUE				�t�@�C���͊J����Ă���
		 * @retval	ksFALSE				�t�@�C���͊J����Ă��Ȃ�
		 */
		virtual KsBool					isValid() = 0;

		/**
		 * �t�@�C�� �|�C���^�̌��݈ʒu���擾����
		 * @return						�t�@�C���擪���猻�݈ʒu�܂ł̃I�t�Z�b�g�A�h���X
		 */
		virtual KsInt32					tell() = 0;

		/**
		 * �w�肳�ꂽ�ʒu�Ƀt�@�C�� �|�C���^���ړ�����
		 * @param	offset				�w��ʒu����̃o�C�g��
		 * @param	mode				�w��ʒu
		 * @return						����ɏ������ꂽ�ꍇ�A0 ��Ԃ��܂��B����ȊO�̏ꍇ�� 0 �ȊO�̒l��Ԃ��܂�
		 */
		virtual KsInt32					seek( KsInt32 offset, KsInt32 mode ) = 0;

		/**
		 * �t�@�C�����畂�������_�̒l��ǂݍ���
		 * @return						���������_�̒l
		 */
		virtual KsReal					readReal() = 0;

		/**
		 * �t�@�C������32bit�����l��ǂݍ���
		 * @return					32bit�����l
		 */
		virtual KsInt32					readInt32() = 0;

		/**
		 * �t�@�C�����畄���Ȃ�32bit�����l��ǂݍ���
		 * @return						�����Ȃ�32bit�����l
		 */
		virtual KsUInt32				readUInt32() = 0;

		/**
		 * �t�@�C������16bit�����l��ǂݍ���
		 * @return						16bit�����l
		 */
		virtual KsInt16					readInt16() = 0;

		/**
		 * �t�@�C�����畄���Ȃ�16bit�����l��ǂݍ���
		 * @return						�����Ȃ�16bit�����l
		 */
		virtual KsUInt16				readUInt16() = 0;

		/**
		 * �t�@�C������8bit�����l��ǂݍ���
		 * @return						8bit�����l
		 */
		virtual KsInt8					readInt8() = 0;

		/**
		 * �t�@�C�����畄���Ȃ�8bit�����l��ǂݍ���
		 * @return						�����Ȃ�8bit�����l
		 */
		virtual KsUInt8					readUInt8() = 0;

		/**
		 * �t�@�C������ꕶ����ǂݍ���
		 * @return						�ꕶ�����̒l
		 */
		virtual KsChar					readChar() = 0;

		/**
		 * �t�@�C�����畄���Ȃ�8bit�����l��ǂݍ���
		 * @return						�����l
		 */
		virtual KsInt32					readByte() = 0;

		/**
		 * �t�@�C�����當�����ǂݍ���
		 * @return						������
		 */
		virtual KsString				readString() = 0;

		/**
		 * �G���R�[�h���ꂽ��������ǂݍ���
		 * @return						�ϒ��T�C�Y�̃G���R�[�h���ꂽ 32-bit ������������
		 */
		virtual KsUInt32				readEncodedU32() = 0;

		/**
		 * �o�b�t�@�Ɏw��o�C�g�����ǂݍ���
		 * @param	pBuffer				(OUT)�ǂݍ��ނ��߂̃o�b�t�@
		 * @param	count				�ǂݍ��ރo�C�g��
		 * @return						�ǂݍ��񂾃o�C�g��
		 */
		virtual KsSize					read( void *pBuffer, KsInt32 count ) = 0;

		/**
		 * �t�@�C���ɒl����������
		 * @param	val					�������ޒl
		 * @return						�������񂾃o�C�g��
		 */
		virtual KsSize					writeReal( KsReal val ) = 0;

		/**
		 * �t�@�C���ɒl����������
		 * @param	val					�������ޒl
		 * @return						�������񂾃o�C�g��
		 */
		virtual KsSize					writeInt32( KsInt32 val ) = 0;

		/**
		 * �t�@�C���ɒl����������
		 * @param	val					�������ޒl
		 * @return						�������񂾃o�C�g��
		 */
		virtual KsSize					writeUInt32( KsUInt32 val ) = 0;

		/**
		 * �t�@�C���ɒl����������
		 * @param	val					�������ޒl
		 * @return						�������񂾃o�C�g��
		 */
		virtual KsSize					writeInt16( KsInt16 val ) = 0;

		/**
		 * �t�@�C���ɒl����������
		 * @param	val					�������ޒl
		 * @return						�������񂾃o�C�g��
		 */
		virtual KsSize					writeUInt16( KsUInt16 val ) = 0;

		/**
		 * �t�@�C���ɒl����������
		 * @param	val					�������ޒl
		 * @return						�������񂾃o�C�g��
		 */
		virtual KsSize					writeInt8( KsInt8 val ) = 0;

		/**
		 * �t�@�C���ɒl����������
		 * @param	val					�������ޒl
		 * @return						�������񂾃o�C�g��
		 */
		virtual KsSize					writeUInt8( KsUInt8 val ) = 0;

		/**
		 * �t�@�C���ɒl����������
		 * @param	val					�������ޒl
		 * @return						�������񂾃o�C�g��
		 */
		virtual KsSize					writeChar( KsChar val ) = 0;

		/**
		 * �t�@�C���ɒl����������
		 * @param	val					�������ޒl
		 * @return						�������񂾃o�C�g��
		 */
		virtual KsSize					writeByte( KsInt32 val ) = 0;

		/**
		 * �o�b�t�@����t�@�C���ɒl����������
		 * @param	pBuffer				�������ރo�b�t�@
		 * @param	count				�������ރo�C�g��
		 * @return						�������񂾃o�C�g��
		 */
		virtual KsSize					write( const void *pBuffer, KsInt32 count ) = 0;
};

#endif /* __KSFILEOBJECT_H__ */


