#include "pch.h"
#include "CppUnitTest.h"
#include"..\\IntersectProject\global.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			line l1, l2,l3;
			l1.a = 1;
			l1.b = 2;
			l1.c = 3;
			l2.a = 2;
			l2.b = 4;
			l2.c = 100;
			l3.a = -2;
			l3.b = 41;
			l3.c = 100;
		//	te();
		//	calaIntersectLineOnly(l1,l2);
		//	Assert::IsTrue(calaIntersectLineOnly(l1, l2) ==  0);
		}
		TEST_METHOD(TestMethod2)
		{
			line l1, c1;
			l1.a = 1;
			l1.b = 0;
			l1.c = -3;
			c1.a = 0;
			c1.b = 0;
			c1.c = 1;
		//	Assert::IsTrue(calaIntersectLineCircle(l1, c1) == -1);
		}
		TEST_METHOD(TestMethod3)
		{
			line c2, c1;
			c2.a = 0;
			c2.b = 0;
			c2.c = 3;
			c1.a = 0;
			c1.b = 0;
			c1.c = 1;
		//	Assert::IsTrue(calaIntersectCircleOnly(c1, c2) == -1);
		}
		TEST_METHOD(TestMethod4)
		{
			line c2, c1,l1;
			l1.a = 1;
			l1.b = 0;
			l1.c = -3;
			c2.a = 0;
			c2.b = 0;
			c2.c = 3;
			c1.a = 0;
			c1.b = 0;
			c1.c = 1;
			//	Assert::IsTrue(calaIntersectCircleOnly(l1, c2) == -1);
		}
		TEST_METHOD(TestMethod5)
		{
			line l1;
			//trans(l1, 2, 3, 4, 5);
		}
	};
}
