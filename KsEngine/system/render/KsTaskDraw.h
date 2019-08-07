

class KsTaskDraw
{
public:
	KsBool				m_bDraw;
	KsTaskDraw*			m_pPrevTaskDraw;
	KsTaskDraw*			m_pNextTaskDraw;
};




class KsTaskUpdate
{
public:
	KsBool					m_bUpdate;
	KsTaskUpdate*			m_pPrevTaskUpdate;
	KsTaskUpdate*			m_pNextTaskUpdate;
};
