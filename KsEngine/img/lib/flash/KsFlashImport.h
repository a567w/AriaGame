#ifndef FLASH_IMPORT_H_FILE
#define FLASH_IMPORT_H_FILE

#include "FBase.h"
#include "FDisplay.h"
#include "FControl.h"
#include "FAction.h"
#include "FBitmap.h"
#include "FSound.h"

#include <iostream>

class KsKsFlashImportHandler
{
public:
	KsFlashImportHandler() {}

	virtual void Import(KsFlashHeader &data) {}
	virtual void Import(KsFlashTagHeader &data) {}
	
	virtual void Import(KsFlashTagRemoveObject &data) {}
	virtual void Import(KsFlashTagRemoveObject2 &data) {}
	virtual void Import(KsFlashTagPlaceObject &data) {}
	virtual void Import(KsFlashTagPlaceObject2 &data) {}
	virtual void Import(KsFlashTagShowFrame &data) {}

	virtual void Import(KsFlashTagBackgroundColor &data) {}
	virtual void Import(KsFlashTagLabelFrame &data) {}
	virtual void Import(KsFlashTagProtect &data) {}
	virtual void Import(KsFlashTagEnd &data) {}
	virtual void Import(KsFlashTagExportAssets &data) {}
	virtual void Import(KsFlashTagImportAssets &data) {}
	virtual void Import(KsFlashTagDefineBitsPtr &data) {}
	virtual void Import(KsFlashTagEnableDebugger &data) {}
	virtual void Import(KsFlashTagFreeCharacter &data) {}
	
	virtual void Import(KsFlashTagDefineBitsJPEG1 &data) {}
	virtual void Import(KsFlashTagJPEGTables &data) {}
	virtual void Import(KsFlashTagDefineBitsJPEG2 &data) {}
	virtual void Import(KsFlashTagDefineBitsJPEG3 &data) {}
	virtual void Import(KsFlashTagDefineBitsLossless &data) {}
	virtual void Import(KsFlashTagDefineBitsLossless2 &data) {}

	virtual void Import(KsFlashTagDefineShape1 &data) {}
	virtual void Import(KsFlashTagDefineShape2 &data) {}
	virtual void Import(KsFlashTagDefineShape3 &data) {}
	
	virtual void Import(KsFlashTagDefineSound &data) {}
	virtual void Import(KsFlashTagDefineSoundMP3 &data) {}
	virtual void Import(KsFlashTagStartSound &data) {}
	virtual void Import(KsFlashTagSoundStreamHead &data) {}
	virtual void Import(KsFlashTagSoundStreamHead2 &data) {}
	virtual void Import(KsFlashTagSoundStreamBlock &data) {}

	virtual void Import(KsFlashTagDoAction &data) {}

};



class KsFlashMyImporter : public KsFlashImportHandler
{
public:
	KsFlashMyImporter() {}

	virtual void Import(KsFlashHeader &data);
	virtual void Import(KsFlashTagHeader &data);
	
	virtual void Import(KsFlashTagRemoveObject &data);
	virtual void Import(KsFlashTagRemoveObject2 &data);
	virtual void Import(KsFlashTagPlaceObject &data);
	virtual void Import(KsFlashTagPlaceObject2 &data);
	virtual void Import(KsFlashTagShowFrame &data);

	virtual void Import(KsFlashTagBackgroundColor &data);
	virtual void Import(KsFlashTagLabelFrame &data);
	virtual void Import(KsFlashTagProtect &data);
	virtual void Import(KsFlashTagEnd &data);
	virtual void Import(KsFlashTagExportAssets &data);
	virtual void Import(KsFlashTagImportAssets &data);
	virtual void Import(KsFlashTagDefineBitsPtr &data);
	virtual void Import(KsFlashTagEnableDebugger &data);
	virtual void Import(KsFlashTagFreeCharacter &data);
	
	virtual void Import(KsFlashTagDefineBitsJPEG1 &data);
	virtual void Import(KsFlashTagJPEGTables &data);
	virtual void Import(KsFlashTagDefineBitsJPEG2 &data);
	virtual void Import(KsFlashTagDefineBitsJPEG3 &data);
	virtual void Import(KsFlashTagDefineBitsLossless &data);
	virtual void Import(KsFlashTagDefineBitsLossless2 &data);

	virtual void Import(KsFlashTagDefineShape1 &data);
	virtual void Import(KsFlashTagDefineShape2 &data);
	virtual void Import(KsFlashTagDefineShape3 &data);
	
	virtual void Import(KsFlashTagDefineSound &data);
	virtual void Import(KsFlashTagDefineSoundMP3 &data);
	virtual void Import(KsFlashTagStartSound &data);
	virtual void Import(KsFlashTagSoundStreamHead &data);
	virtual void Import(KsFlashTagSoundStreamHead2 &data);
	virtual void Import(KsFlashTagSoundStreamBlock &data);

	virtual void Import(KsFlashTagDoAction &data);
};

class KsFlashImporter
{
public:
	KsFlashImporter() {}
	
	KsFlashHeader		importHeader(std::istream &in, KsFlashImportHandler &i);
	KsFlashHeader		importHeader( KsFile& file, KsFlashImportHandler& header );
	
	KsBool				importTag(std::istream &in, KsFlashImportHandler &i);
private:
	
};


#endif
