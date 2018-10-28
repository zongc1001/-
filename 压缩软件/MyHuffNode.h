#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <vector>
using namespace std;


template <class CharType, class WeightType>
class HuffNode
{
public:
    virtual WeightType getWeight() = 0;
    virtual bool isLeaf() = 0;
    virtual MyHuffNode<CharType, WeightType>* getLeft() = 0;
    virtual MyHuffNode<CharType, WeightType>* getRight() = 0;
    virtual void setLeft(MyHuffNode<CharType, WeightType>) = 0;
    virtual void setRight(MyHuffNode<CharType, WeightType>) = 0;
};

template <class CharType, class WeightType>
class LeafNode : public MyHuffNode<CharType, WeightType>
{
private:
    CharType cha;
    WeightType weight;
public:
    LeafNode(CharType& cha, WeightType& weight);
    virtual ~LeafNode(){};
    CharType getCha();
    WeightType getWeight();
    bool isLeaf();
    HuffNode<CharType, WeightType>* getLeft();
    HuffNode<CharType, WeightType>* getRight();
    void setLeft(HuffNode<CharType, WeightType>* child) {};
    void setRight(HuffNode<CharType, WeightType>* child) {};
};

template <class CharType, class WeightType>
class IntlNode: public MyHuffNode<CharType, WeightType>
{
private:
    MyHuffNode<CharType, WeightType>* left;
    MyHuffNode<CharType, WeightType>* right;
    WeightType weight;
public:
    IntlNode(WeightType& weight, HuffNode<CharType, WeightType>* left,
            HuffNode<CharType, WeightType>* right);
    virtual ~IntlNode(){};
    WeightType getWeight();
    bool isLeaf();
    HuffNode<CharType, WeightType>* getLeft();
    HuffNode<CharType, WeightType>* getRight();
    void setLeft(HuffNode<CharType, WeightType> *child);
    void setRight(HuffNode<CharType, WeightType> *child);
};

template <class CharType, class WeightType>
class HuffTree
{
protected:
    HuffNode<CharType, WeightType>* root;
    String* charCodes;    //字符编码信息
    HuffNode<CharType, WeightType>* pCurNode;
    int num;
    long long (*CharIndex)(CharType&);   //字符位置映射
    
    void creatCode(HuffNode<CharType, WeightType>* r, char code[], int len = 0);//生成字符编码
    void clear(HuffNode<CharType, WeightType>* r);

public:
    HuffTree(CharType ch[], WeightType weight[], int n, long long (*CharIndex)(CharType&));
    virtual ~HuffNode();
    String encode();
    list<CharType> decode(String strCode);
};

template <class CharType, class WeightType>
void HuffTree<CharType, WeightType>::creatCode(HuffNode<CharType, WeightType>* r, char code[], int len)
{
    if(r->isLeaf())
    {
        CharType ch = ((LeafNode<Chartype, WeightType>*)r) -> getCha();
        code[len] = '\0';
        Sring strCode(code);
        charCodes[(*CharIndex)(ch)] = strCode;
    }
    else
    {
        code[len] = '0';
        creatCode(r->getLeft(), code, len + 1);
        code[len] = '1';
        creatCode(r->getRight(), code, len + 1);
    }
}
template <class CharType, class WeightType>
struct CmpNode
{
    bool operator()(HuffNode<CharType, WeightType> a, HuffNode<CharType, WeightType> b)
    {
        return a.getWeight() > b.getWeight();
    }
}

template <class CharType, class WeightType>
HuffTree<CharType, WeightType>::HuffTree(CharType ch[], WeightType weight[], int n, long long (*CharIndex)(CharType &))
{
    this.CharIndex = CharIndex;
    num = n;
    charCodes = new String[num];
    priority_queue<HuffNode<CharType, WeightType>, vector<HuffNode<CharType, WeightType>>, CmpNode> minHeap;
    int i;
    for(i = 0; i < num;i++)
    {
        LeafNode<CharType, WeightType> temp(ch[i], weight[i]);
        minHeap.push(temp);
    }

    for(i = 0; i < num-1; i++)
    {
        LeafNode<CharType, WeightType> r, r1, r2;
        r1 = minHeap.top();
        minHeap.pop();
        r2 = minHeap.top();
        minHeap.pop();
        LeafNode<CharType, WeightType> r(IntlNode<CharType, WeightType>(r1.getWeight() + r2.getWeight(),
            r1, r2));
        minHeap.push(r);
    }
    IntlNode<CharType, WeightType> rt;
    rt = minHeap.top();
    minHeap.pop();
    root = &rt;
    pCurNode = root;
    char* code = new char[num];
    CreatCode(root, code);
    delete[] code;


}

