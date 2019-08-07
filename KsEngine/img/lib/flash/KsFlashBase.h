#if 0

All Macromedia KsFlash (SWF) files begin with the following header: 
     SWF File Header      
     Field           Type*           Comment      
     Signature           UI8           Signature byte always �eF�f      
     Signature           UI8           Signature byte always �eW�f      
     Signature           UI8           Signature byte always �eS�f      
     Version           UI8           Single byte file version (e.g. 0x04F for SWF 4)      
     FileLength           UI32           Length of entire file in bytes      
     FrameSize           RECT           Frame size in twips      
     FrameRate           UI16           Frame delay in 8.8 fixed number of frames per second      
     FrameCount           UI16           Total number of frames in movie      
 

#ifndef FBASE_H_FILE
#define FBASE_H_FILE


#include <iostream>
#include <vector>
#include <math.h>



class KsFlashImporter;

typedef unsigned char KsUInt8;
typedef char SBYTE;

typedef unsigned short KsUInt16;
typedef short KsInt16;

typedef unsigned int KsUInt32;
typedef int KsInt32;

#define WRITE_KsUInt8(x) { KsUInt8 s = (x); out.write((char*)&s,1); }
#define WRITE_SBYTE(x) { SBYTE s = (x); out.write((char*)&s,1); }

#define WRITE_KsUInt16(x) { KsUInt16 s = (x); out.write((char*)&s,2); }
#define WRITE_KsInt16(x) { KsInt16 s = (x); out.write((char*)&s,2); }

#define WRITE_KsUInt32(x) { KsUInt32 s = (x); out.write((char*)&s,4); }
#define WRITE_KsInt32(x) { KsInt32 s = (x); out.write((char*)&s,4); }

#define WRITE_KsUInt82(x,f) { KsUInt8 s = (x); f.write((char*)&s,1); }
#define WRITE_SBYTE2(x,f) { SBYTE s = (x); f.write((char*)&s,1); }

#define WRITE_KsUInt162(x,f) { KsUInt16 s = (x); f.write((char*)&s,2); }
#define WRITE_KsInt162(x,f) { KsInt16 s = (x); f.write((char*)&s,2); }

#define WRITE_KsUInt322(x,f) { KsUInt32 s = (x); f.write((char*)&s,4); }
#define WRITE_KsInt322(x,f) { KsInt32 s = (x); f.write((char*)&s,4); }

#define READ_KsUInt8(x) { in.read((char*)&x,1); }
#define READ_SBYTE(x) { in.read((char*)&x,1); }

#define READ_KsUInt16(x) { in.read((char*)&x,2); }
#define READ_KsInt16(x) { in.read((char*)&x,2); }

#define READ_KsUInt32(x) { in.read((char*)&x,4); }
#define READ_KsInt32(x) { in.read((char*)&x,4); }

#define READ_KsUInt82(x,f) { f.read((char*)&x,1); }
#define READ_SBYTE2(x,f) { f.read((char*)&x,1); }

#define READ_KsUInt162(x,f) { f.read((char*)&x,2); }
#define READ_KsInt162(x,f) { f.read((char*)&x,2); }

#define READ_KsUInt322(x,f) { f.read((char*)&x,4); }
#define READ_KsInt322(x,f) { f.read((char*)&x,4); }

#define DEFINE_RW_INTERFACE								\
public:													\
virtual void Write(std::ostream &out) { out << *this; } \
virtual void Read(std::istream &in) { in >> *this; }	\

template <class T> T KsMax(T a, T b)  {return (((a) > (b)) ? (a) : (b)); } 
template <class T> T KsMin(T a, T b)  {return (((a) < (b)) ? (a) : (b)); } 

template<class T> int KsGetBitSizeSigned( T x)


template<class T> T LSHR(T x, int num);

template<class T> int GetBitSize(T x)
{
    int size=0;
    while(x > 0)
    {
      x=LSHR(x,1);
      size++;
    } 
    return size;
}

template<class T> int GetBitSizeSigned(T x)
{
    int size=0;
    int sign = (long(x) < 0);
    T tmp=x;
    if(sign) tmp = tmp*(-1);
    size = GetBitSize(tmp);
    return (size+1);
}

template<class T> T PackBitsSigned(T x)
{    
    UDWORD v=0x0;
    int sign = (long(x) < 0);
    if(sign) x=~x + 1;

    int i = GetBitSizeSigned(x);
//    v = arr1[i];
    for(int b=0; b < i; b++)
    {
        v = (v << 1) | 0x01;
    }
    v = (x & v) | (GetBit(x,sizeof(T)*8-1));
    if(sign) return (T)(~v + 1);
    return (v); 
}

template<class T> T UnPackBitsSigned(T x, int size)
{
    int sign = GetBit(x,size-1);
    
    x = GetIsolatedBits(x,0,size);
    
    T v = 0;
    if(sign == 1) 
    {
        int bit1 = size;
        int bit2 = sizeof(T)*8;
//		v = arr1[bit2-bit1];
        for(int b=0; b < bit2-bit1; b++)
		  {
            v = (v << 1) | 0x01;
        }
//		v <<= bit1;
        for(int b2=0; b2 < bit1; b2++)
        {
            v = (v << 1);
        }

    }
    return (x | v); 
}

template<class T> char GetBit(T x, int bit)
{   
    T y = 1 << bit;
    if((x & y)==0) return (char)0;
    return((char)1);
}

template<class T> T IsolateBits(T x, int bit1, int bit2)
{
    T v=0;
    //v = arr1[bit2-bit1];
    for(int b=0; b < bit2-bit1; b++)
    {
        v = (v << 1) | 0x01;
    }
	//v <<= bit1;
    for(int b2=0; b2 < bit1; b2++)
    {
        v = (v << 1);
    }   
    return (x & v);
}
template<class T> T LSHR(T x, int num)
{
    char sign = (GetBit(x,sizeof(T)*8-1));
    T v = IsolateBits(x, 0, sizeof(T)*8-1);
    v >>= num;
    if(sign==1) 
    {
        v |= (((T)0x1) << (sizeof(T)*8-1));
    }
    return v;
}

template<class T> T GetIsolatedBits(T x, int bit1, int bit2)
{
    T r = IsolateBits(x,bit1,bit2);
    return ((T)(LSHR(r, bit1)));
}





#endif



/************************************************************************************************/
/** 
 * @file		KsFlashColor.h
 * @brief		
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSFLASBASE_H__
#define __KSFLASBASE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsFlashTagType.h"
#include "KsFlashColor.h"
#include "KsFlashRect.h"
#include "KsFlashIDFactory.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/



/************************************************************************************************/
/**
 * @class		KsFlashFixed
 * @brief		Flash(SWF)Header
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class KsFlashFixed
{
	public:
		KsInt16					m_upperval;
		KsUInt16				m_lowerval;
	public: 
								KsFlashFixed(); 
								KsFlashFixed( KsInt16 u, KsUInt16 l ); 
								KsFlashFixed( KsReal64 f ); 

		KsUInt32				convertToRaw () const;
		void					getFromRaw( KsInt32 raw );

		KsReal64				convertToDouble() const;
		void					getFromDouble( KsReal64 x );
		
};

/************************************************************************************************/
/**
 * @class		KsFlashFixed16
 * @brief		Flash(SWF)Header
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class KsFlashFixed16
{
	public:
		KsInt8					m_upperval;
		KsUInt8					m_lowerval;
	public: 
								KsFlashFixed16(); 
								KsFlashFixed16( KsInt8 u, KsUInt8 l ); 
								KsFlashFixed16( KsReal64 f ); 

		KsUInt16				convertToRaw() const;
		
		void					setFromRaw(KsInt16 raw);
		KsReal64				convertToDouble();
		void					setFromDouble(KsReal64 x );

};

/************************************************************************************************/
/**
 * @class		KsFlashVersion
 * @brief		Flash(SWF)Header
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class KsFlashVersion
{
	public:
		/**
		 * �R���X�g���N�^
		 */
								KsFlashVersion() : m_version( 1 ) {}
		/**
		 * �o�[�W���������Z�b�g����
		 * @param				�o�[�W�������
		 */
		virtual void			setVersion( KsInt32 version ) { m_version = version; }
	
		/**
		 * �o�[�W���������擾����
		 * @return				�o�[�W�������
		 */
		virtual KsInt32			getVersion() const { return m_version; }

	private:
		KsInt32					m_version;		/**< �o�[�W�������		*/
};

/************************************************************************************************/
/**
 * @class		KsFlashRect
 * @brief		Flash(SWF)Header
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		�ŏ���3 �o�C�g�́fFWS�f�A4 �o�C�g�ڂ����@�[�W�����A5�`8 �o�C�g�ڂ��t�@�C���̒����ł���B
 *				���̌��ʂ̃T�C�Y�A�t���[���̍Đ����[�g�A�t���[���̐��������B
 */
/************************************************************************************************/
class KsFlashHeader
{
	public:

		/**
		 * �f�X�g���N�^
		 */
								KsFlashHeader( KsUInt8 version, KsUInt32 fileSize, KsInt32 width, KsInt32 height, KsUInt16 frameRate, KsUInt16 frameCount );
		
		/**
		 * �f�X�g���N�^
		 */
		virtual				KsFlashHeader( KsUInt8 version, KsUInt32 fileSize, KsInt32 width, KsInt32 height, KsReal64 frameRate, KsUInt16 frameCount );

		/**
		 * �f�X�g���N�^
		 */
								~KsFlashHeader() {}

		/**
		 * �o�[�W�������擾����
		 * @return				SWF�o�[�W����
		 */
		KsUInt8					getVersion() const { return m_version; }

		/**
		 * �t�@�C���T�C�Y���擾����
		 * @return				�t�@�C���T�C�Y
		 */
		KsUInt32				getFileSize() const { return m_fileSize; }

		/**
		 * �t���[���T�C�Y���擾����
		 * @return				�t���[���T�C�Y
		 */
		KsFlashRect				getFrameSize() { return m_rect; }

		/**
		 * �t���[�����[�g���擾����
		 * @return				�t���[�����[�g
		 */
		KsFlashFixed16			getFrameRate() const { return m_frameRate; }

		/**
		 * �g�[�^���t���[�������擾����
		 * @return				�g�[�^���t���[����
		 */
		KsUInt16				getFrameCount() const { return frameCount; }

	private:
		KsUInt8					m_signature[ 3 ];	/**< SWF ���ʎq				*/
		KsUInt8					m_version;			/**< �o�[�W����				*/
		KsUInt32				m_fileSize;			/**< �t�@�C���T�C�Y			*/
		KsFlashRect				m_frameSize;		/**< �t���[���T�C�Y			*/
		KsFlashFixed16			m_frameRate;		/**< �t���[�����[�g			*/
		KsUInt16				m_frameCount;		/**< �g�[�^���t���[����		*/

	protected:
								KsFlashHeader() {}
		//friend class KsFlashImporter;
};




#endif	/* __KSFLASBASE_H__ */



#if 0



62 byte


/************************************************************************************************/
/**
 * @class		KsFlashTag
 * @brief		Flash(SWF)Header
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		TagHeader 16bit
 *				| ID( 10 bit ) | length( 6 bit ) |
 *  tagID  = Code >> 6; 
 *  length = Code & 0x3f;
 *	length �� 0x3f �̂Ƃ���32bit length
 */
/************************************************************************************************/
class KsFlashTag
{
	    friend class KsFlashImporter;
	
	public:
		/**
		 * �R���X�g���N�^
		 * @param	tagID		�^�OID
		 * @param	length		�^�O�̒���
		 */
	    						KsFlashTag( KsUInt16 tagID, KsUInt32 length ) : m_tagID( tagID ), m_length( length ) {}

		/**
		 * �f�X�g���N�^
		 */
	    virtual					~KsFlashTag() {}

		/**
		 * �^�OID���擾����
		 * @return				�^�OID
		 */
	    KsUInt16				getTagID() const { return m_tagID; }
	
		/**
		 * �^�O�̒������擾����
		 * @return				�^�O�̒���
		 */
	    KsUInt32				getTagLength() const { return m_length; }

	private:
	    KsUInt16				m_tagID;		/**< �^�OID			*/
	    KsUInt32				m_length;		/**< �^�O�̃T�C�Y	*/

	protected:
		/**
		 * �R���X�g���N�^
		 */
	    						KsFlashTag() {}
};



class KsFlashTag
{
	public:
	    KsFlashTag() {}
	    ~FlashTag() {}

	    void 			setImportSize( KsUInt32 size ) { m_importSize = size; }	
	protected:
	    KsUInt32		m_importSize;
};





class KsFlashDisplayListTag : public KsFlashTag
{
	public:
		KsFlashDisplayListTag() {}
		virtual		~KsFlashDisplayListTag() {}
		virtual KsBool			isFrame() { return ksFALSE; }

};


class KsFlashIDEnabled
{
	public:
		KsFlashIDEnabled( KsBool count=ksTrue ) { if( count ){ m_charID = m_idFactory.getCharacterID(); } }

		void				getID( KsUInt16 id ) { m_charID=id; }
		KsUInt16			getID() const { return m_charID; }
	private:
		KsFlashIDFactory	m_idFactory;
		KsUInt16			m_charID;
};




#endif /* __KSFLASHBASE_H__ */



#endif
