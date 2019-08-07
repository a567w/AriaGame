All Macromedia KsFlash (SWF) files begin with the following header: 
     SWF File Header      
     Field           Type*           Comment      
     Signature           UI8           Signature byte always ‘F’      
     Signature           UI8           Signature byte always ‘W’      
     Signature           UI8           Signature byte always ‘S’      
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
		void					setFromDouble(KsReal64 x);

};

/************************************************************************************************/
/**
 * @class		KsFlashVersion
 * @brief		Flash(SWF)Header
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsFlashVersion
{
	public:
		/**
		 * コンストラクタ
		 */
								KsFlashVersion() : m_version( 1 ) {}
		/**
		 * バージョン情報をセットする
		 * @param				バージョン情報
		 */
		virtual void			setVersion( KsInt32 version ) { m_version = version; }
	
		/**
		 * バージョン情報を取得する
		 * @return				バージョン情報
		 */
		virtual KsInt32			getVersion() const { return m_version; }

	private:
		KsInt32					m_version;		/**< バージョン情報		*/
};

