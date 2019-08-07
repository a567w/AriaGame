#ifndef FSPRITE_H_FILE
#define FSPRITE_H_FILE
#include "FBase.h"


struct SWFSprite_s
{
  struct SWFCharacter_s character;

  int frames;
  int totalFrames;

  int nBlocks;
  SWFBlock *blocks;
};

class KsFlashTagSprite : public KsFlashID, public KsFlashTag
{
public:
						KsFlashTagSprite() : m_frames( 0 ) {}
	virtual				~KsFlashTagSprite() {}

	void Add(FlashSprite*tag);

private:

	std::vector<FlashSprite*> tags;
	
	FlashIDFactory idFactory;

	gc_vector<FlashSprite*> gc;
	KsUInt16			m_frames;
};

class FlashTagDefineMovie : public FlashIDEnabled, public FlashTag
{
public:
	FlashTagDefineMovie(char *url) : str(url) {}
private:
	gc_vector<char *> gc;
	char *str;
};

#endif
