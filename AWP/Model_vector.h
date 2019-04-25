#pragma once
#include "stdafx.h"
#include "Point3D.h"
#include "Face.h"
#include "Point2D.h"
#include "Model.h"

/*ģ����*/
class Model_vector {

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
	vector<HalfEdge> halfEdges;
	int sizeOfHalf;

	/*����ܽ�*/
	vector<bool> isNieght;

	/*�߶Խǵ�ת��*/
	vector<Point2D> angOnEdge;
	
	/*ռ�ݵ�Ĵ���*/
	//vector<float> occupy;
	/*ռ�ݽǶȵĴ��ڣ�����ĽǶ��ǶԱ�i��Ӧ�ĶԽ�*/
	//vector<int> occupyOnAng;
	/*��ľ���*/
	float *dist;

	bool isClose;
	//vector<float> dist;
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
	Model_vector() {
		idOfHalfEdge.clear();
		vertexs.clear();
		faces.clear();
		sizeOfHalf = 0;
		isClose = true;
	}

	/*�������Ĺ��캯���������ǵ�����ļ����������㼯���漯���*/
	Model_vector(char *fileName) {
		memcpy(inputFileName, fileName, sizeof(inputFileName));
		idOfHalfEdge.clear();
		vertexs.clear();
		faces.clear();
		sizeOfHalf = 0;
		isClose = true;
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
	void ReadObjFile(char * filename); void ReadObjFile2(char * filename);
	void ReadPlyFile(char * filename);
	void ReadAsciiPly(char * filename);
	void ReadBinaryPly(char * filename, const char* format);
	void ReadUntilNextLine(ifstream& in) const;
	void ReadIntoWord(ifstream &in, string& word) const;
	static void SwapOrder(char *buf, int sz);
};