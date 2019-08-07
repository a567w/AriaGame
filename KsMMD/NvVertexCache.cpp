/************************************************************************************************/
/** 
 * @file		KsPMDConverter.cpp
 * @brief		PMDファイル
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsMMD/KsMMDPreCompile.h"
#include "NvVertexCache.h"

VertexCache::VertexCache()
{
  VertexCache(16);
}


VertexCache::VertexCache(int size)
{
  numEntries = size;

  entries = new int[numEntries];

  for(int i = 0; i < numEntries; i++)
    entries[i] = -1;
}


VertexCache::~VertexCache()
{
	delete[] entries;

	entries = 0;
}


int VertexCache::At(int index)
{
  return entries[index];
}


void VertexCache::Set(int index, int value)
{
  entries[index] = value;
}


void VertexCache::Clear()
{
  for(int i = 0; i < numEntries; i++)
    entries[i] = -1;
}

void VertexCache::Copy(VertexCache* inVcache)
{
  for(int i = 0; i < numEntries; i++)
  {
    inVcache->Set(i, entries[i]);
  }
}

bool VertexCache::InCache(int entry)
{
  bool returnVal = false;

  for(int i = 0; i < numEntries; i++)
  {
    if(entries[i] == entry)
    {
      returnVal = true;
      break;
    }
  }

  return returnVal;
}


int VertexCache::AddEntry(int entry)
{
  int removed;

  removed = entries[numEntries - 1];

  //push everything right one
  for(int i = numEntries - 2; i >= 0; i--)
  {
    entries[i + 1] = entries[i];
  }

  entries[0] = entry;

  return removed;
}

  