#include "SerializeInstance.h"
#include <fstream>

#define READ_MODE

int main(int _Argc, char** argv)
{
	//////////////////////////////////////
	//       serialize

	RoadLine L1;
	L1.m_nRefRoadID = 1;
	L1.m_nLineIndex = 1;
	for (int i=0; i<10; i++)
	{
		L1.mLinePoints.push_back(Vertex(1.0, i*2.0));
	}
	
	RoadLine L2;
	L2.m_nRefRoadID = 1;
	L2.m_nLineIndex = 2;
	for (int i=0; i<10; i++)
	{
		L2.mLinePoints.push_back(Vertex(5.0, i*2.0));
	}

	Road R1;
	R1.m_nRoadID = 1;
	R1.m_nFNodeID = -1;
	R1.m_nTNodeID = 1;
	R1.mLines.push_back(L1);
	R1.mLines.push_back(L2);
	for (int i=0; i<10; i++)
	{
		R1.mAxis.push_back(Vertex(3.0, i*2.0));
	}

	Node N1;
	N1.m_nNodeID = 1;
	N1.m_pos = Vertex(3.0, 18.0);
	N1.m_linkedRoadIds.push_back(1);

	RoadManager RM1;
	RM1.mAllRoads.push_back(R1);
	RM1.mAllNodes.push_back(N1);

	OutEngine oe;
	oe << RM1;

	string str = oe.str();

#ifndef READ_MODE
	// Ó²ÅÌ»¯ÐòÁÐ
	ofstream ofile("binary.bin", ios::out|ios::binary);
	if (!ofile)
	{
		cout << "create binari file failed!" << endl;
		return -1;
	}

	ofile.write(str.c_str(), str.length());
	ofile.close();
#endif

	//////////////////////////////////////
	//      deserialize from memory

	InEngine ie(str);

	RoadManager RM2;
	ie >> RM2;

	//////////////////////////////////////
	//    deserialize from hard disk

#ifdef READ_MODE
	ifstream ifile("binary.bin", ios::in|ios::binary);
	if (!ifile)
	{
		cout << "open binary file failed!" <<endl;
		return -1;
	}
	
	ifile.seekg(0, ios::end);
	UINT fSize = ifile.tellg();
	ifile.seekg(0, ios::beg);

	char* pRBuff = new char[fSize + 1];
	ifile.read(pRBuff, fSize);
	pRBuff[fSize] = '/0';

	ifile.close();

	string strfCtx;
	strfCtx.resize(fSize);
	for (size_t i=0 ;i< fSize; i++) {
		strfCtx[i] = pRBuff[i];
	}

	InEngine ieF(strfCtx);
	RoadManager RM3;

	ieF >> RM3;

	delete [] pRBuff;

#endif


	system("pause");

	return 0;
}