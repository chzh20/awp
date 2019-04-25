#pragma once
#include "stdafx.h"
#include "Point3D.h"
#include "Face.h"
#include "Point2D.h"

/*��߽ṹ*/
__device__ __host__ struct HalfEdge{
	/*�ð�ߵĳ���*/
	float length;
	/*�Աߵ�id*/
	int idOfOppositeEdge;
	/*����id*/
	int idOfStartPoint;
	/*�ð�ߵĶԶ���id*/
	int idOfOppositeVer;

	/*�޲������캯��*/
	__device__ __host__ HalfEdge() {
		length = 0;
		idOfOppositeVer = -1;
		idOfOppositeEdge = -1;
		idOfStartPoint = -1;
	}

	/*�������Ĺ��캯��*/
	__device__ __host__ HalfEdge(double _length, int _idOfOppositeEdge, int _idOfStartPoint, int _idOfOppositeVer) {
		length = _length;
		idOfOppositeVer = _idOfOppositeVer;
		idOfOppositeEdge = _idOfOppositeEdge;
		idOfStartPoint = _idOfStartPoint;
	}
};

/*ģ����*/
class Model{

public:
	/*�����ļ���*/
	char inputFileName[256];
	/*�㼯*/
	vector<Point3D> vertexs;
	/*�漯*/
	vector<Face> faces;
	/*���Ӧ�İ��ID���ð������Ϊ����*/
	vector<int>idOfHalfEdge;

	/*��߼�*/
	HalfEdge halfEdges[NUMOFEDGE];//vector<HalfEdge> halfEdges;
	int sizeOfHalf;
	
	/*����ܽ�*/
	bool isNieght[NUMOFVERS];//vector<bool> isNieght;

	/*�߶Խǵ�ת��*/
	//vector<Point2D> angOnEdge;
	Point2D angOnEdge[NUMOFEDGE];
	/*ռ�ݵ�Ĵ���*/
	//vector<float> occupy;
	/*ռ�ݽǶȵĴ��ڣ�����ĽǶ��ǶԱ�i��Ӧ�ĶԽ�*/
	//vector<int> occupyOnAng;
	/*��ľ���*/
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
	/*���캯��*/
public:

	/*�޲����Ĺ��캯�������㼯���漯���*/
	Model() {
		idOfHalfEdge.clear();
		vertexs.clear();
		faces.clear();
		sizeOfHalf = 0;
	}

	/*�������Ĺ��캯���������ǵ�����ļ����������㼯���漯���*/
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
	/*��Ӧ�İ�߽ṹ�ķ����Ͳ���*/
public:

	/*������߽ṹ*/
	void creatHalfEdge();

	/*�������id, ����eid����ð������ģ�Ͱ�߼��е�id*/
	int idOfFace(int eid) {
		return eid / 3;
	}

	/*��һ����ߵ�id�� ����eid����ð������ģ�Ͱ�߼��е�id*/
	int idOfNextHalfEdge(int eid) {
		return eid / 3 * 3 + (eid + 1) % 3;
	}

	/*��һ����ߵ�id�� ����eid����ð������ģ�Ͱ�߼��е�id*/
	int idOfPreHalfEdge(int eid) {
		return eid / 3 * 3 + (eid + 2) % 3;
	}

	/*�ð�ߵ����*/
	Point3D startOfHalfEdge(int eid) {
		return vertexs[halfEdges[eid].idOfStartPoint];
	}

	/*�ð�ߵ��յ�*/
	Point3D endOfHalfEdge(int eid) {
		return vertexs[halfEdges[idOfNextHalfEdge(eid)].idOfStartPoint];
	}

	/*����һ�����������������ж���, ����vidΪ�õ��id�� eidΪ��vidΪ����һ�����id�������ڽӵ��id*/
	vector<int> findAllAdjVer(int vid, int eid);

	/*Ԥ�����������ܱ���Ϣ*/
	void findAllInfoOnVers();

	void createPoint2dByAng(int eid, float ang, float a, float b, float c);
	/*�����ļ��йص�*/
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