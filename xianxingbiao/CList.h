
//建立模板
template < class CElemType>
class CList
{
	//CList类中常数定义
public:
	enum 
	{
		INIT_SIZE = 20,//线性表的元素个数
		INCREMENT_SIZE = 10 //新增元素个数
	};
	//CList类的变量定义
private:
	CElemType *m_pElem;//线性表的的头地址
	int m_nSize;//线性表的当前长度
	int m_nLength;//为线性表分配存储空间长度
	//CList类的成员函数定义
public:
	CList();//构造函数
	~CList();//析构函数
	int GetSize();//获取线性表当前长度
	int GetLength();//获取线性表分配的存储空间长度
	CElemType GetAt(int nIndex);//检索元素
	void SetAt(int nIndex,CElemType e);//修改元素
	int InsertAt(int nIndex, CElemType e);//在指定位置插入元素，返回引导号
	int AddTail(CElemType e);//把元素e加到线性表尾部
	int AddHead(CElemType e);//把元素e加到线性表头部
	void RemoveAt(int nIndex,int nCountor);//在指定位置删除nCountor个元素
	void ShowValues(); //显示表中所有元素
};