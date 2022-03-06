
//����ģ��
template < class CElemType>
class CList
{
	//CList���г�������
public:
	enum 
	{
		INIT_SIZE = 20,//���Ա��Ԫ�ظ���
		INCREMENT_SIZE = 10 //����Ԫ�ظ���
	};
	//CList��ı�������
private:
	CElemType *m_pElem;//���Ա�ĵ�ͷ��ַ
	int m_nSize;//���Ա�ĵ�ǰ����
	int m_nLength;//Ϊ���Ա����洢�ռ䳤��
	//CList��ĳ�Ա��������
public:
	CList();//���캯��
	~CList();//��������
	int GetSize();//��ȡ���Ա�ǰ����
	int GetLength();//��ȡ���Ա����Ĵ洢�ռ䳤��
	CElemType GetAt(int nIndex);//����Ԫ��
	void SetAt(int nIndex,CElemType e);//�޸�Ԫ��
	int InsertAt(int nIndex, CElemType e);//��ָ��λ�ò���Ԫ�أ�����������
	int AddTail(CElemType e);//��Ԫ��e�ӵ����Ա�β��
	int AddHead(CElemType e);//��Ԫ��e�ӵ����Ա�ͷ��
	void RemoveAt(int nIndex,int nCountor);//��ָ��λ��ɾ��nCountor��Ԫ��
	void ShowValues(); //��ʾ��������Ԫ��
};