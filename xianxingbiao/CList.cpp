#include<iostream>
#include"CList.h"
using namespace std;

/* ��ģ���г�Ա�������� */
//���캯�����������Ա��ʼ��
template<class CElemType>
CList<CElemType>::CList()
{
	m_nSize = 0;
	m_nLength = INIT_SIZE;
	m_pElem = new CElemType[INIT_SIZE]; //���ٶ�̬�洢�ռ�
}
//��������������ɾ�����Ա�
template<class CElemType>
CList<CElemType>::~CList()
{
	delete[]m_pElem; //ɾ����̬�洢�ռ�
}

//��ȡ���Ա�ǰ����
template<class CElemType>
int CList<CElemType>::GetSize()
{
	return m_nSize;
}
//��ȡ���Ա����Ĵ洢����
template<class CElemType>
int CList<CElemType>::GetLength()
{
	return m_nLength;
}
//����Ԫ��
template<class CElemType>
CElemType CList<CElemType>::GetAt(int nIndex)
{
	return m_pElem[nIndex];
}
//�޸�Ԫ��
template<class CElemType>
void CList<CElemType>::SetAt(int nIndex, CElemType e)
{
	m_pElem[nIndex] = e;
}
//��Ԫ��e�ӵ����Ա��β��
template<class CElemType>
int CList<CElemType>::AddTail(CElemType e)
{
	return InsertAt(GetSize(), e);
}
//��Ԫ��e�ӵ����Ա��ͷ��
template<class CElemType>
int CList<CElemType>::AddHead(CElemType e)
{
	return InsertAt(0, e);
}


/////////////////��ָ��λ�ã�nIndex������Ԫ��e������������///////////////////
template <class CElemType>
int CList<CElemType>::InsertAt(int nIndex, CElemType e)
{
	//����������Χ
	if (nIndex > GetSize())
	{
		cout << "����������Χ��δ�����κ�Ԫ�أ�" << endl;
		return -1;
	}
	//////�ռ���������ʱ��Ҫ���ӿռ�
	if (GetSize() == GetLength())
	{
		//�����¿ռ䣨����INCREMENT_SIZE���ռ䣩
		CElemType *p = new CElemType[GetSize() + INCREMENT_SIZE];
		//��ԭ��ַ����nIndexǰ�ߵĿռ临�Ƹ��¿��ٵĿռ�
		for (int i = 0; i < nIndex; i++)
		{
			p[i] = m_pElem[i];
		}
		//��ԭ��ַ����nIndex��ߵĿռ临�Ƹ��¿��ٵĿռ䣨λ�ú��ƣ�
		for (int i = nIndex; i < GetSize(); i++)
		{
			p[i + 1] = m_pElem[i];
		}
		delete[]m_pElem; //ɾ��ԭ�ռ�
		m_nLength += INCREMENT_SIZE; //���¿ռ䳤��
		m_pElem = p; //���ƿռ䣨λ�þ��������Ŀռ临�Ƹ�ԭ�ռ䣩
		delete[]p; //�ͷ���ʱ����p�Ŀռ�
	}
	//�ռ仹��ʣ�ֱ࣬�Ӳ��뵽��Ӧλ��
	else
	{
		//�������Ԫ�غ���һ��λ�ã������ǰλ�ò���
		for (int i = GetSize() - 1; i >= nIndex; i--)
		{
			m_pElem[i + 1] = m_pElem[i];
		}
	}
	m_pElem[nIndex] = e; //���������Ԫ�طŵ�ָ��λ�ã�nIndex��
	m_nSize++; //�ռ䳤��+1
	return nIndex;
}
//��ָ��λ��ɾ��nCounter��Ԫ��
template<class CElemType>
void CList<CElemType>::RemoveAt(int nIndex, int nCounter)
{
	//����������Χ�������һ��Ԫ�س�����Χ
	if (nIndex > GetSize() - 1 || nIndex + nCounter >= GetSize())
	{
		cout << "����������Χ��δɾ���κ�Ԫ�أ�" << endl;
		return;
	}
	//ɾ����ѡ�еĿռ䣨�����Ԫ�ظ���ǰ���Ԫ��λ�ã�
	for (int i = nIndex; i <= nIndex + nCounter; i++)
	{
		m_pElem[i] = m_pElem[i + nCounter];
	}
	m_nSize -= nCounter; //���Ա�ռ�ı�
	//�ռ�����ʱ��ɾ����Ԫ�Ŀռ�
	if (GetLength() > INIT_SIZE && GetLength() - GetSize() >= INCREMENT_SIZE)
	{
		//������ʵ����Ա�ռ��С
		int N = GetSize() + (GetLength() - GetSize()) % INCREMENT_SIZE;
		CElemType *p = new CElemType[N];
		//��ԭ���Ա���Ԫ�ظ��Ƹ�p��ɾ��ԭ�ռ䣬�ٽ����Ƹ����Ա�
		for (int i = 0; i < GetSize(); i++)
		{
			p[i] = m_pElem[i];
			delete[]m_pElem;
			m_pElem = p;
			m_nLength = N;
		}
		delete[]p; //�ͷ�p�Ŀռ�
	}

}
//��ʾ��������Ԫ��
template<class CElemType>
void CList<CElemType>::ShowValues()
{
	//������Ԫ��
	if (GetSize() == 0)
	{
		cout << "������Ԫ�أ�" << endl;
	}
	//������Ԫ��
	else
	{
		for (int i = 0; i < GetSize(); i++)
		{
			cout << m_pElem[i] << ' ';
			if ((i + 1) % 15 == 0 && i != GetSize() - 1) //ÿ10��Ԫ��Ϊһ��
			{
				cout << endl;
			}
		}
		cout << endl;
	}
}
