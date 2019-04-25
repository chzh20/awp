#pragma once
#include"stdafx.h"

/*����ȿ��Ա�ʾһ����ά�ĵ㣬Ҳ���Ա�ʾһ����ά�е�����*/
class Point3D{

	/*�����ά���꣬Ҳ���Ա�ʾһ����ά����*/
public:
	float x, y, z;

	/*���캯��*/
public:

	/*�޲����Ĺ��캯��*/
	Point3D(){}

	/*�������Ĺ��캯��*/
	Point3D(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	/*���ص�Ԫ�����*/
public:

	/*��Ԫ���������ά�����ļӷ�*/
	Point3D operator += (const Point3D& others) {
		x += others.x;
		y += others.y;
		z += others.z;
		return *this;
	}

	/*��Ԫ���������ά�����ļ���*/
	Point3D operator -= (const Point3D& others) {
		x -= others.x;
		y -= others.y;
		z -= others.z;
		return *this;
	}

	/*��Ԫ���������ά����������*/
	Point3D operator *= (const float times) {
		x *= times;
		y *= times;
		z *= times;
		return *this;
	}

	/*��Ԫ���������ά��������������������Ϊ0*/
	Point3D operator /= (const float times) {
		x /= times;
		y /= times;
		z /= times;
		return *this;
	}

	/*��ά���ϵĻ������㷽��*/
public:

	/*�����ĳ���*/
	float getLength() {
		return sqrt(x * x + y * y + z * z);
	}
	/*������λ��*/
	Point3D normalize() {
		float len = getLength();
		return Point3D(x / len, y / len, z / len);
	}
};

/*��Ԫ�������������ά�����ļӷ�*/
Point3D operator + (const Point3D& a, const Point3D& b);

/*��Ԫ�������������ά�����ļӷ�*/
Point3D operator - (const Point3D& a, const Point3D& b);

/*��Ԫ�������������ά�����Ĳ��*/
Point3D operator * (const Point3D& a, const Point3D& b);

Point3D operator * (const float ti, const Point3D& a);

/*������ά�����ĵ��*/
float DotProduct(const Point3D& a, const Point3D& b);

/*�����������ɵ������ε����*/
float getTriangleArea(const Point3D& a, const Point3D& b, const Point3D& c);

/*��������֮�乹�ɵĽǶȴ�С*/
float getAngleBetween(Point3D a, Point3D b);

/*����oe������os���ɵĽǶȴ�С*/
float getAngleBetween(Point3D o, Point3D s, Point3D e);

/*����֮��ľ���*/
float getDistance(Point3D a, Point3D b);

/*�ж�a, b, c�����Ƿ��ߣ����߷���true�� ���򷵻�false*/
bool isCollineation(Point3D a, Point3D b, Point3D c);

/*��a���߶�bc�Ĵ���*/
Point3D getFootPoint(Point3D a, Point3D b, Point3D c);
