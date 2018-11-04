#include "SerializeTemplate.h"

class Vertex : public Serializable<Vertex>
{
public:
	Vertex() : mX(0.0), mY(0.0) { }
	Vertex(double x, double y) { mX= x; mY =y;}
	~Vertex() {}

	double mX;
	double mY;

	static string serialize(const Vertex& a)
	{
		OutEngine oe;
		oe << a.mX << a.mY;

		return oe.str();
	}

	static int deserialize(string inc, Vertex& a)
	{
		InEngine ie(inc);

		ie >> a.mX >> a.mY;

		return ie.donesize();
	}
};

class RoadLine : public Serializable<RoadLine>
{
public:
	RoadLine() {}
	~RoadLine() {}

	int m_nRefRoadID;
	int m_nLineIndex;

	vector<Vertex> mLinePoints;

	static string serialize(const RoadLine& a)
	{
		OutEngine oe;
		oe << a.m_nRefRoadID << a.m_nLineIndex;

		int nSize = int(a.mLinePoints.size());
		oe << nSize;

		for (int i =0; i<nSize; i++)
		{
			oe << a.mLinePoints[i];
		}

		return oe.str();
	}

	static int deserialize(string inc, RoadLine& a)
	{
		InEngine ie(inc);
		ie >> a.m_nRefRoadID >> a.m_nLineIndex;

		int nSize = 0;
		ie >> nSize;
		
		while (nSize > 0)
		{
			Vertex vx;
			ie >> vx;

			a.mLinePoints.push_back(vx);

			nSize--;
		}

		return ie.donesize();
	}
};

class Road : public Serializable<Road>
{
public:
	Road() {}
	~Road() {}

	int m_nRoadID;
	int m_nFNodeID;
	int m_nTNodeID;
	
	vector<RoadLine> mLines;
	vector<Vertex> mAxis;

	static string serialize(const Road& a)
	{
		OutEngine oe;
		oe << a.m_nRoadID << a.m_nFNodeID << a.m_nTNodeID;

		int nSize = int(a.mLines.size());
		oe << nSize;

		for (int i=0; i<nSize; i++)
		{
			oe << a.mLines[i];
		}

		nSize = int(a.mAxis.size());
		oe << nSize;
		for (int i=0; i<nSize; i++)
		{
			oe << a.mAxis[i];
		}

		return oe.str();
	}

	static int deserialize(string inc, Road& a)
	{
		InEngine ie(inc);
		ie >> a.m_nRoadID >> a.m_nFNodeID >> a.m_nTNodeID;

		int nSize = 0;
		ie >> nSize;
		
		while(nSize > 0)
		{
			RoadLine L;
			ie >> L;

			a.mLines.push_back(L);

			nSize--;
		}

		ie >>nSize;

		while(nSize > 0)
		{
			Vertex vx;
			ie >> vx;

			a.mAxis.push_back(vx);

			nSize--;
		}

		return ie.donesize();
	}
};

class Node : public Serializable<Node>
{
public:
	Node() {}
	~Node() {}

	int m_nNodeID;
	Vertex m_pos;

	vector<int> m_linkedRoadIds;

	static string serialize(const Node& a)
	{
		OutEngine oe;
		oe << a.m_nNodeID;
		oe << a.m_pos;

		int nSize = int(a.m_linkedRoadIds.size());
		oe << nSize;

		for (int i=0; i<nSize; i++)
		{
			oe << a.m_linkedRoadIds[i];
		}

		return oe.str();
	}

	static int deserialize(string inc , Node& a)
	{
		InEngine ie(inc);
		ie >> a.m_nNodeID;
		ie >> a.m_pos;

		int nSize = 0;
		ie >> nSize;
		
		while(nSize > 0)
		{
			int nId;
			ie >> nId;

			a.m_linkedRoadIds.push_back(nId);

			nSize--;
		}

		return ie.donesize();
	}
};

class RoadManager : public Serializable<RoadManager>
{
public:
	RoadManager() {}
	~RoadManager() {}

	vector<Road> mAllRoads;
	vector<Node> mAllNodes;

	static string serialize(const RoadManager& a)
	{
		OutEngine oe;
		int nSize = int(a.mAllRoads.size());
		oe << nSize;

		for (int i=0; i<nSize; i++)
		{
			oe << a.mAllRoads[i];
		}

		nSize = int(a.mAllNodes.size());
		oe << nSize;

		for (int i=0; i<nSize; i++)
		{
			oe << a.mAllNodes[i];
		}

		return oe.str();
	}

	static int deserialize(string inc, RoadManager& a)
	{
		InEngine ie(inc);

		int nSize = 0;
		ie >> nSize;
		
		while (nSize > 0)
		{
			Road r;
			ie >> r;

			a.mAllRoads.push_back(r);

			nSize--;
		}

		nSize = 0;
		ie >> nSize;
		
		while (nSize > 0)
		{
			Node n;
			ie >> n;

			a.mAllNodes.push_back(n);

			nSize--;
		}

		return ie.donesize();
	}
};