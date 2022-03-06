#include<iostream>
#include"CList.h"
using namespace std;

/* 类模板中成员函数定义 */
//构造函数，用于线性表初始化
template<class CElemType>
CList<CElemType>::CList()
{
	m_nSize = 0;
	m_nLength = INIT_SIZE;
	m_pElem = new CElemType[INIT_SIZE]; //开辟动态存储空间
}
//析构函数，用于删除线性表
template<class CElemType>
CList<CElemType>::~CList()
{
	delete[]m_pElem; //删除动态存储空间
}

//获取线性表当前长度
template<class CElemType>
int CList<CElemType>::GetSize()
{
	return m_nSize;
}
//获取线性表分配的存储容量
template<class CElemType>
int CList<CElemType>::GetLength()
{
	return m_nLength;
}
//检索元素
template<class CElemType>
CElemType CList<CElemType>::GetAt(int nIndex)
{
	return m_pElem[nIndex];
}
//修改元素
template<class CElemType>
void CList<CElemType>::SetAt(int nIndex, CElemType e)
{
	m_pElem[nIndex] = e;
}
//把元素e加到线性表的尾部
template<class CElemType>
int CList<CElemType>::AddTail(CElemType e)
{
	return InsertAt(GetSize(), e);
}
//把元素e加到线性表的头部
template<class CElemType>
int CList<CElemType>::AddHead(CElemType e)
{
	return InsertAt(0, e);
}


/////////////////在指定位置（nIndex）插入元素e，返回索引号///////////////////
template <class CElemType>
int CList<CElemType>::InsertAt(int nIndex, CElemType e)
{
	//索引超出范围
	if (nIndex > GetSize())
	{
		cout << "索引超出范围，未插入任何元素！" << endl;
		return -1;
	}
	//////空间已满，此时需要增加空间
	if (GetSize() == GetLength())
	{
		//开辟新空间（增加INCREMENT_SIZE个空间）
		CElemType *p = new CElemType[GetSize() + INCREMENT_SIZE];
		//将原地址索引nIndex前边的空间复制给新开辟的空间
		for (int i = 0; i < nIndex; i++)
		{
			p[i] = m_pElem[i];
		}
		//将原地址索引nIndex后边的空间复制给新开辟的空间（位置后移）
		for (int i = nIndex; i < GetSize(); i++)
		{
			p[i + 1] = m_pElem[i];
		}
		delete[]m_pElem; //删除原空间
		m_nLength += INCREMENT_SIZE; //更新空间长度
		m_pElem = p; //复制空间（位置经过调整的空间复制给原空间）
		delete[]p; //释放临时变量p的空间
	}
	//空间还有剩余，直接插入到相应位置
	else
	{
		//插入点后的元素后移一个位置，插入点前位置不变
		for (int i = GetSize() - 1; i >= nIndex; i--)
		{
			m_pElem[i + 1] = m_pElem[i];
		}
	}
	m_pElem[nIndex] = e; //将待插入的元素放到指定位置（nIndex）
	m_nSize++; //空间长度+1
	return nIndex;
}
//从指定位置删除nCounter个元素
template<class CElemType>
void CList<CElemType>::RemoveAt(int nIndex, int nCounter)
{
	//索引超出范围或者最后一个元素超出范围
	if (nIndex > GetSize() - 1 || nIndex + nCounter >= GetSize())
	{
		cout << "索引超出范围，未删除任何元素！" << endl;
		return;
	}
	//删除所选中的空间（后面的元素覆盖前面的元素位置）
	for (int i = nIndex; i <= nIndex + nCounter; i++)
	{
		m_pElem[i] = m_pElem[i + nCounter];
	}
	m_nSize -= nCounter; //线性表空间改变
	//空间冗余时，删除多元的空间
	if (GetLength() > INIT_SIZE && GetLength() - GetSize() >= INCREMENT_SIZE)
	{
		//计算合适的线性表空间大小
		int N = GetSize() + (GetLength() - GetSize()) % INCREMENT_SIZE;
		CElemType *p = new CElemType[N];
		//将原线性表中元素复制给p并删除原空间，再将复制给线性表
		for (int i = 0; i < GetSize(); i++)
		{
			p[i] = m_pElem[i];
			delete[]m_pElem;
			m_pElem = p;
			m_nLength = N;
		}
		delete[]p; //释放p的空间
	}

}
//显示表中所有元素
template<class CElemType>
void CList<CElemType>::ShowValues()
{
	//表中无元素
	if (GetSize() == 0)
	{
		cout << "表中无元素！" << endl;
	}
	//表中有元素
	else
	{
		for (int i = 0; i < GetSize(); i++)
		{
			cout << m_pElem[i] << ' ';
			if ((i + 1) % 15 == 0 && i != GetSize() - 1) //每10个元素为一行
			{
				cout << endl;
			}
		}
		cout << endl;
	}
}
