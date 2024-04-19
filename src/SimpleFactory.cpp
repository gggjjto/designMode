/*
* 文件名：SimpleFactory.cpp
* 作者： jiang peng
* 时间： 2024.4.11
* 描述： 简单工厂模式的实例代码
* 类型： 创建型模式
* 说明： 实现类与类之间的解耦合，这样我们在创建对象的时候就变成了拿来主义，使程序更加便于维护。
*/
#include<iostream>
using namespace std;

class Abstarct
{
    public:
        virtual void transform() {}
        virtual void ability() {}
        virtual ~Abstarct() {}
};

class apple : public Abstarct
{
    public:
        void transform() override
        {
            cout<<"Genesis golden apple"<<endl;
        }

        void ability() override
        {
            cout<<"The Snow Queen Poisoned apples"<<endl;
        }
};

class banana : public Abstarct
{
    public:
        void transform() override
        {
            cout<<"还没熟的香蕉是绿色的"<<endl;
        }

        void ability() override
        {
            cout<<"熟过了的香蕉是黑色的"<<endl;
        }
};

class orange : public Abstarct
{
    public:
        void transform() override
        {
            cout<<"橘子和橙子是不一样的"<<endl;
        }

        void ability() override
        {
            cout<<"橙汁是橙子的汁"<<endl;
        }
};

enum class Type:char {Apple, Banana, Orange};
class Factory
{
public:
    Factory() {}
    ~Factory() {}
    Abstarct* createFruit(Type type)
    {
        Abstarct* prt = nullptr;
        switch(type) 
        {
            case Type::Apple : 
                prt = new apple;
                break;
            case Type::Banana :
                prt = new banana;
                break;
            case Type::Orange :
                prt = new orange;
                break;
        }
        return prt;
    }
};


int main() {
    Factory* factory = new Factory;
    Abstarct* obj = factory->createFruit(Type::Apple);
    obj->ability();
    obj->transform();
    return 0;
}
