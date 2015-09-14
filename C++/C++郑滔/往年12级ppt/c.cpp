#include <iostream>
using namespace std;

class B1
{
public:
    int x;
    virtual void v1(){ cout << "B1::v1" << endl; }
    void f1(){cout << "B1::f1" << endl; }
};

class B2
{
public:
    int y;
    virtual void v2(){	cout << "B2::v2" << endl; }
    void f2(){ cout << "B2::f2" << endl; }
};

class B3
{
public:
    int z;
    virtual void v3(){ cout << "B3::v3" << endl; }
    void f3(){ cout << "B3::f3" << endl; }
};

class D : public B1, public B2, public B3
{
public:
    int a;
    void v3(){ cout << "D::v3" << endl; }
    virtual void vD(){ cout << "D::vD" << endl; }
};

typedef void (*Fun)();

void PrintMember(int *pI)
{
    cout << *pI << endl;
}

void PrintVT(int *pVT)
{
    while(*pVT != NULL)
    {
        (*(Fun*)(pVT))();
        pVT++;
    }
}

void PrintVTAndMember(B1 *pD)
{
    int *pRoot = (int*)pD;
    int *pVTB1 = (int*)*(pRoot + 0);PrintVT(pVTB1);
    int *pMB1 = pRoot +1; PrintMember(pMB1);
    int *pVTB2 = (int*)*(pRoot + 2);PrintVT(pVTB2);
    int *pMB2 = pRoot +3; PrintMember(pMB2);
    int *pVTB3 = (int*)*(pRoot + 4);PrintVT(pVTB3);
    int *pMB3 = pRoot +5; PrintMember(pMB3);
}

void TestVT()
{
    B1 *pB1 = new D();
    D *pD = dynamic_cast<D*>(pB1);
    pD->x = 10;
    pD->y = 20;
    pD->z = 30;
    pD->a = 40;
    PrintVTAndMember(pD);
    delete pD;
}

void TestDynamicCast()
{
    B1 *pB1 = new D();
    cout << "B1:" << pB1 << endl;
    D *pD = dynamic_cast<D*>(pB1);
    cout << "D:"<< pD << endl;
    B2 *pB2 = dynamic_cast<B2*>(pB1);
    cout << "B2:" << pB2 << endl;
    B3 *pB3 = dynamic_cast<B3*>(pB1);
    cout << "B3:" << pB3 << endl;
    delete pD;
}

void mytest()
{
	D d;
	d.x = 10;
    d.y = 20;
    d.z = 30;
    d.a = 40;
	cout << "D:x    " << &d.x << "   " << d.x << endl;
	cout << "D:y    " << &d.y << "   " << d.y << endl;
	cout << "D:z    " << &d.z << "   " << d.z << endl;
	cout << "D:a    " << &d.a << "   " << d.a << endl;


	cout << "D:" << &d << endl;
	B1 *p1=&d;
	cout << "B1:" << &p1 << endl;
	B2 *p2=&d;
	cout << "B2:" << &p2 << endl;
	B3 *p3=&d;
	cout << "B3:" << &p3 << endl;
	

	typedef void (*Fun)(B2 *);
	Fun f=(Fun)(*((char *)p2));
	f(NULL);
}

void main()
{
//	mytest();
	TestVT();

	//TestDynamicCast();
}