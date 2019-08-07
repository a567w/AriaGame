#ifndef FDISPLAY_H_FILE
#define FDISPLAY_H_FILE

#include <string>
#include "FBase.h"
#include "FShape.h"

class KsFlashPlaceObject : public KsFlashSpriteEnabled
{
	public:
										KsFlashPlaceObject( KsUInt16 depth, KsUInt16 charID, KsFlashMatrix &m );
										KsFlashPlaceObject( KsUInt16 depth, KsUInt16 charID, KsFlashMatrix &m, KsFlashColorTransform &c );

		KsBool							hasColorTransform() { return m_hasCfx; }

		KsUInt16						getCharID() { return m_characterID; }
		KsUInt16						getDepth()  { return m_depth; }
		KsFlashMatrix					getMatrix() { return m_matrix; } 
		KsFlashColorTransform			getColorTransform() { return m_cfx; }

	protected:
		friend class	KsFlashImporter;
		KsFlashPlaceObject() {}

	private:
		KsFlashTagHeader				m_header;
		KsUInt16						m_characterID;
		KsUInt16						m_depth;
		KsFlashMatrix					m_matrix;
		KsFlashColorTransform			m_cfx;
		KsBool							m_hasCfx;
};

//TODO: Find out Clip Actions Data Format
class FlashTagPlaceObject2
{
	protected:
		friend class FlashImporter;
	public:
										FlashTagPlaceObject2(KsUInt16 _depth) : hasName(false), hasCharID(false), hasMove(false), hasMatrix(false), hasColorTransform(false), hasRatio(false), hasClipDepth(false), depth(_depth){}
										FlashTagPlaceObject2(KsUInt16 _depth, KsUInt16 _charID) : hasName(false), hasCharID(ksTRUE), hasMove(false), hasMatrix(false), hasColorTransform(false), hasRatio(false), hasClipDepth(false), depth(_depth), charID(_charID)
										{
										}
										FlashTagPlaceObject2(KsUInt16 _depth, KsUInt16 _charID, FlashMatrix& _matrix) : hasName(false), hasCharID(ksTRUE), hasMove(false), hasMatrix(ksTRUE), hasColorTransform(false), hasRatio(false), hasClipDepth(false), depth(_depth)
										{
											charID = _charID;
											matrix = _matrix;
										}
										FlashTagPlaceObject2(KsUInt16 _depth, KsUInt16 _charID, FlashMatrix& _matrix, FlashColorTransform& _cfx) : hasName(false), hasCharID(ksTRUE), hasMove(false), hasMatrix(ksTRUE), hasColorTransform(ksTRUE), hasRatio(false), hasClipDepth(false), depth(_depth)
										{
											charID = _charID;
											matrix = _matrix;
											cfx = _cfx;
										}
										FlashTagPlaceObject2(KsUInt16 _depth, FlashMatrix& _matrix, FlashColorTransform& _cfx) : hasName(false), hasCharID(false), hasMove(false), hasMatrix(ksTRUE), hasColorTransform(ksTRUE), hasRatio(false), hasClipDepth(false), depth(_depth)
										{	
											matrix = _matrix;
											cfx = _cfx;
										}
										~FlashTagPlaceObject2(){}
		
		void							setName(std::string& _name) { hasName = ksTRUE; name = _name; }

		void							setCharID(KsUInt16 _charID){ hasCharID = ksTRUE; charID = _charID; }

		void							setMove(KsBool _move) { m_hasMove = _move; }

		void							setMatrix(FlashMatrix& _matrix) { m_hasMatrix = ksTRUE; m_matrix = _matrix; }

		void							setColorTransform(FlashColorTransform& _cfx) { m_hasColorTransform = ksTRUE; m_cfx = _cfx; }
		void							setRatio(KsUInt16 _ratio) { m_hasRatio = ksTRUE; ratio=_ratio; }
		void							setClipDepth( KsUInt16 _clipDepth )  { hasClipDepth = ksTRUE; clipDepth = _clipDepth; }

		
		KsBool							hasName() const { return m_hasName; }
		KsBool							hasCharID() const { return m_hasCharID; }
		KsBool							hasMove() const { return m_hasMove; }
		KsBool							hasMatrix() const { return m_hasMatrix; }
		KsBool							hasColorTransform() const { return m_hasColorTransform; }
		KsBool							hasRatio() const { return m_hasRatio; }
		KsBool							hasClipDepth() const { return m_hasClipDepth; }

		KsUInt16						getDepth() const { return depth; }
		const KsChar*					getName() const { return m_name.c_str(); }
		KsUInt16						getCharID() const { return m_charID; }	
		KsFlashMatrix					getMatrix() { return m_matrix; } 
		KsFlashColorTransform			getColorTransform() { return m_cfx; }
		KsUInt16						getRatio() const { return ratio); }
		KsUInt16						getClipDepth() const { return m_clipDepth; }
		

	private:
		
		KsFlashTagPlaceObject2(){}

		KsFlashTagHeader				m_header;
		KsBool							m_hasName;
		KsBool							m_hasCharID;
		KsBool							m_hasMove;
		KsBool							m_hasMatrix;
		KsBool							m_hasColorTransform;
		KsBool							m_hasRatio;
		KsBool							m_hasClipDepth;
		
		KsUInt16						m_depth;
		KsString						m_name;
		KsUInt16						m_charID;
		KsFlashMatrix					m_matrix;
		KsFlashColorTransform			m_cfx;	
		KsUInt16						m_ratio;
		KsUInt16						m_clipDepth;
};

class KsFlashRemoveObject
{
	public:
										KsFlashRemoveObject( KsUInt16 charID, KsUInt16 depth ) : m_charID(charID), m_depth(depth){}
	
		virtual							~KsFlashRemoveObject() {}

		KsUInt16						getCharID() const { return m_charID; }
		KsUInt16						getDepth()  const { return m_depth; }

	protected:
		friend class					KsFlashImporter;
										KsFlashTagRemoveObject() {}
	private:
		KsFlashTagHeader				m_header;
		KsUInt16						m_characterID;
		KsUInt16						m_depth;
};



class KsFlashRemoveObject2
{
	public:
										KsFlashTagRemoveObject2( KsUInt16 depth ) : m_depth(depth){}
		virtual							~KsFlashTagRemoveObject2() {}

		KsUInt16						getDepth()  const { return m_depth; }

	protected:
		friend class KsFlashImporter;
		KsFlashRemoveObject2() {}
	private:
		KsFlashTagHeader				m_header;
		KsUInt16						m_depth;
};

class KsFlashShowFrame
{
	public:
		KsFlashTagHeader				m_header;
};


#endif 
