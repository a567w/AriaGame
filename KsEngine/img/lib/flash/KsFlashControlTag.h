#ifndef FCONTROL_H_FILE
#define FCONTROL_H_FILE

#include "FBase.h"
#include "./md5/md5.h"
#include <vector>
#include <string>


class FlashImportHandler;

class KsFlashControlTag : public KsFlashTag
{
}

class KsFlashTagDefineBitsPtr : public KsFlashControlTag
{
public:
	KsFlashTagDefineBitsPtr(UDWORD ptr) : ref(ptr){}
	UDWORD GetPtr() { return ref; }
	void SetPtr(UDWORD ptr) { ref = ptr; }

private:
	friend class FlashImportHandler;
	KsFlashTagDefineBitsPtr(){};
	UDWORD ref;
};

class KsFlashTagProtect : public KsFlashControlTag
{
public:	
	friend class FlashImportHandler;
	KsFlashTagProtect() : hasPass(false){}
	KsFlashTagProtect(std::string& password) : hasPass(false)
	{
		hasPass = true;		
		md5Pass = crypt_md5(password.c_str(), "Aa");
	}
	
	std::string GetEncryptedPassword(){return md5Pass;}
	
	void SetEncryptedPassword(std::string& encPassword){
		hasPass = true;
		md5Pass = encPassword;
	}
	void SetPassword(std::string& password)
	{		
		hasPass = true;				
		md5Pass = crypt_md5(password.c_str(), "Aa");;
	}
	bool HasPassword() { return hasPass; }
private:
	bool hasPass;
	std::string md5Pass;

	friend class FlashImporter;	
};



class KsFlashTagBackgroundColor : public KsFlashControlTag
{
		friend class KsFlashImporter;

	public:	

							KsFlashTagBackgroundColor( KsUInt8 r, KsUInt8 g, KsUInt8 b);
							
							KsFlashTagBackgroundColor( KsFlashColor &color );
		
		virtual				~KsFlashTagBackgroundColor() {}

		KsFlashColor		getColor() { return KsFlashColor( m_red, m_green, m_blue ); }
		KsUInt8				m_red;
		KsUInt8				m_green;
		KsUInt8				m_blue;

	private:
		KsFlashTagBackgroundColor() {}
};


KsFlashTagBackgroundColor::KsFlashTagBackgroundColor( KsUInt8 r, KsUInt8 g, KsUInt8 b)
	: m_red( r )
	, m_green( g )
	, m_blue( b )
{
}

KsFlashTagBackgroundColor::KsFlashTagBackgroundColor( const KsFlashColor &color )
{
	m_red   = color.getRed();
	m_green = color.getGreen();
	m_blue  = color.getBlue();
}
	
	
class KsFlashTagLabelFrame : public KsFlashControlTag
{
DEFINE_RW_INTERFACE
public:
	friend class FlashImportHandler;
						KsFlashTagLabelFrame( KsChar* string ) { m_name = string; }
	virtual				~KsFlashTagLabelFrame(){ m_name.clear(); }

	const KsChar*		getLabel() { return m_name.c_str(); }
	
private:
	KsFlashTagLabelFrame() {}

	KsString		m_name;
};

class KsFlashTagEnd : public KsFlashControlTag
{
public:
				KsFlashTagEnd(){}
	virtual		~KsFlashTagEnd(){}
}

DECLARE_SIMPLE_TAG2(FlashTagEnd)

class FlashTagExportAssets : public KsFlashControlTag
{
DEFINE_RW_INTERFACE
public:
	friend class FlashImportHandler;
	FlashTagExportAssets() {}
	~FlashTagExportAssets() {}

	void AddAsset(char *str, UWORD id);

	unsigned int GetAssetNum() { return assets_str.size(); }
	flash_pair<char*, UWORD> GetAsset(long num) { return(flash_pair<char*,UWORD>(assets_str[num],assets_id[num])); }
private:
	friend class FlashImporter;
private:
	std::vector <char*> assets_str;
	std::vector <UWORD> assets_id;
	gc_vector<char *> gc;
};
class FlashTagImportAssets : public KsFlashControlTag
{
DEFINE_RW_INTERFACE
FlashTagImportAssets() {}
public:
	friend class FlashImportHandler;
	FlashTagImportAssets(char *_swfurl) : swfurl(_swfurl) {}
	~FlashTagImportAssets() { }

	void AddAsset(char *str, UWORD id);

	const char *GetSwfUrl() { return swfurl; }
	unsigned int GetAssetNum() { return assets_str.size(); }
	flash_pair<char*, UWORD> GetAsset(long num) { return(flash_pair<char*,UWORD>(assets_str[num],assets_id[num])); }
private:
	friend class FlashImporter;


private:
	char *swfurl;
	std::vector <char*> assets_str;
	std::vector <UWORD> assets_id;
    gc_vector<char *> gc;
};


class FlashTagFreeCharacter : public KsFlashControlTag
{
DEFINE_RW_INTERFACE
FlashTagFreeCharacter() {}
public:
	FlashTagFreeCharacter(UWORD _id) { _id = id; }
	UWORD GetID(void) const { return id; }
private:
	friend class FlashImporter;
	UWORD id;
};

#endif
