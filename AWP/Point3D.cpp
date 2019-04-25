#include"stdafx.h"
#include"Point3D.h"

/*��Ԫ�������������ά�����ļӷ�*/
Point3D operator + (const Point3D& a, const Point3D& b) {
	return Point3D(a.x + b.x, a.y + b.y, a.z + b.z);
}

/*��Ԫ�������������ά�����ļӷ�*/
Point3D operator - (const Point3D& a, const Point3D& b) {
	return Point3D(a.x - b.x, a.y - b.y, a.z - b.z);
}

/*��Ԫ�������������ά�����Ĳ��*/
Point3D operator * (const Point3D& a, const Point3D& b) {
	return Point3D(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

/*��Ԫ�����������*/
Point3D operator * (const float ti, const Point3D& b) {
	return Point3D(ti*b.x, ti*b.y, ti*b.z);
}

/*������ά�����ĵ��*/
float dotProduct(const Point3D& a, const Point3D& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

/*�����������ɵ������ε����*/
float getTriangleArea(const Point3D& a, const Point3D& b, const Point3D& c) {
	Point3D crossProduct = (b - a) * (c - b);
	return 0.5 * crossProduct.getLength();
}

/*��������֮�乹�ɵĽǶȴ�С*/
float getAngleBetween(Point3D a, Point3D b) {
	float cosAngle = dotProduct(a, b) / (a.getLength() * b.getLength());
	if (cosAngle - 1 > -EPS)
	{
		cosAngle = 1;
	}
	else if (cosAngle + 1 < EPS)
	{
		cosAngle = -1;
	}
	return acos(cosAngle);
}

/*����oe������os���ɵĽǶȴ�С*/
float getAngleBetween(Point3D o, Point3D s, Point3D e) {
	return getAngleBetween(o - e, o - s);
}

/*����֮��ľ���*/
float getDistance(Point3D a, Point3D b) {
	return (b - a).getLength();
}

/*�ж�a, b, c�����Ƿ��ߣ����߷���true�� ���򷵻�false*/
bool isCollineation(Point3D a, Point3D b, Point3D c) {
	return ((b - a)*(c - a)).getLength() < EPS;
}

/*��a���߶�bc�Ĵ���*/
Point3D getFootPoint(Point3D a, Point3D b, Point3D c) {
	Point3D footPoint;
	float dx = b.x - c.x;
	float dy = b.y - c.y;
	float dz = b.z - c.z;

	if (abs(dx) < EPS && abs(dy) < EPS && abs(dz) < EPS) {
		return b;
	}
	float u = (a.x - b.x)*(b.x - c.x) +
		(a.y - b.y)*(b.y - c.y) + (a.z - b.z)*(b.z - c.z);
	u = u / ((dx*dx) + (dy*dy) + (dz*dz));
	footPoint.x = b.x + u*dx;
	footPoint.y = b.y + u*dy;
	footPoint.z = b.z + u*dz;
	return footPoint;
}