#pragma once
#include "stdafx.h"
#include "Point3D.h"
#include "Face.h"
#include "Point2D.h"

/*半边结构*/
__device__ __host__ struct HalfEdge{
	/*该半边的长度*/
	float length;
	/*对边的id*/
	int idOfOppositeEdge;
	/*起点的id*/
	int idOfStartPoint;
	/*该半边的对顶点id*/
	int idOfOppositeVer;

	/*无参数构造函数*/
	__device__ __host__ HalfEdge() {
		length = 0;
		idOfOppositeVer = -1;
		idOfOppositeEdge = -1;
		idOfStartPoint = -1;
	}

	/*带参数的构造函数*/
	__device__ __host__ HalfEdge(double _length, int _idOfOppositeEdge, int _idOfStartPoint, int _idOfOppositeVer) {
		length = _length;
		idOfOppositeVer = _idOfOppositeVer;
		idOfOppositeEdge = _idOfOppositeEdge;
		idOfStartPoint = _idOfStartPoint;
	}
};

/*模型类*/
class Model{

public:
	/*导入文件名*/
	char inputFileName[256];
	/*点集*/
	vector<Point3D> vertexs;
	/*面集*/
	vector<Face> faces;
	/*点对应的半边ID，该半边是其为起点的*/
	vector<int>idOfHalfEdge;

	/*半边集*/
	HalfEdge halfEdges[NUMOFEDGE];//vector<HalfEdge> halfEdges;
	int sizeOfHalf;
	
	/*点的周角*/
	bool isNieght[NUMOFVERS];//vector<bool> isNieght;

	/*边对角的转化*/
	//vector<Point2D> angOnEdge;
	Point2D angOnEdge[NUMOFEDGE];
	/*占据点的窗口*/
	//vector<float> occupy;
	/*占据角度的窗口，这里的角度是对边i对应的对角*/
	//vector<int> occupyOnAng;
	/*点的距离*/
	float dist[NUMOFVERS];
	
	int GetNumOfVerts() {
		return vertexs.size();
	}

	int GetNumOfFaces() {
		return faces.size();
	}

	int GetNumOfEdges() {
		return sizeOfHalf;// halfEdges.size();
	}
	/*构造函数*/
public:

	/*无参数的构造函数，将点集和面集清空*/
	Model() {
		idOfHalfEdge.clear();
		vertexs.clear();
		faces.clear();
		sizeOfHalf = 0;
	}

	/*带参数的构造函数，参数是导入的文件名，并将点集和面集清空*/
	Model(char *fileName) {
		memcpy(inputFileName, fileName, sizeof(inputFileName));
		idOfHalfEdge.clear();
		vertexs.clear();
		faces.clear();
		sizeOfHalf = 0;
	}

	string GetFileName() const
	{
		return string(inputFileName);
	}
	/*对应的半边结构的方法和操作*/
public:

	/*创建半边结构*/
	void creatHalfEdge();

	/*所在面的id, 参数eid代表该半边所在模型半边集中的id*/
	int idOfFace(int eid) {
		return eid / 3;
	}

	/*下一条半边的id， 参数eid代表该半边所在模型半边集中的id*/
	int idOfNextHalfEdge(int eid) {
		return eid / 3 * 3 + (eid + 1) % 3;
	}

	/*上一条半边的id， 参数eid代表该半边所在模型半边集中的id*/
	int idOfPreHalfEdge(int eid) {
		return eid / 3 * 3 + (eid + 2) % 3;
	}

	/*该半边的起点*/
	Point3D startOfHalfEdge(int eid) {
		return vertexs[halfEdges[eid].idOfStartPoint];
	}

	/*该半边的终点*/
	Point3D endOfHalfEdge(int eid) {
		return vertexs[halfEdges[idOfNextHalfEdge(eid)].idOfStartPoint];
	}

	/*遍历一个顶点所关联的所有顶点, 参数vid为该点的id， eid为以vid为起点的一条半边id。返回邻接点的id*/
	vector<int> findAllAdjVer(int vid, int eid);

	/*预处理点的所有周边信息*/
	void findAllInfoOnVers();

	void createPoint2dByAng(int eid, float ang, float a, float b, float c);
	/*读入文件有关的*/
public:
	void LoadModel();
	void ReadMFile(char *filename);
	void ReadFile(char * filename);
	void ReadObjFile(char * filename);
	
	void ReadPlyFile(char * filename);
	void ReadAsciiPly(char * filename);
	void ReadBinaryPly(char * filename, const char* format);
	void ReadUntilNextLine(ifstream& in) const;
	void ReadIntoWord(ifstream &in, string& word) const;
	static void SwapOrder(char *buf, int sz);
};