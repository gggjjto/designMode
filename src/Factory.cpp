/*
* 文件名：Factory.cpp
* 作者： jiang peng
* 时间： 2024.4.13
* 描述： 工厂模式的实例代码
* 编码： UTF-8
* 说明： 实现类与类之间的解耦合，这样我们在创建对象的时候就变成了拿来主义，使程序更加便于维护。
*/
#include<iostream>
#include<memory>
using namespace std;

class Abstarct
{
    public:
        virtual void transform() = 0;
        virtual void ability() = 0;
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

/******************************************************/
class AbstarctFactory
{
    public:
        virtual Abstarct* createSimple() = 0;
        virtual ~AbstarctFactory() {}
};

class appleFactory : public AbstarctFactory
{
    public:
        Abstarct* createSimple() override
        {
            return new apple;
        }
        ~appleFactory()
        {
            cout<<"delete apple"<<endl;
        }

};

class bananaFactory : public AbstarctFactory
{
    public:
        Abstarct* createSimple() override
        {
            return new banana;
        }
        ~bananaFactory()
        {
            cout<<"delete banana"<<endl;
        }
};

class orangeFactory : public AbstarctFactory
{
    public:
        Abstarct* createSimple() override
        {
            return new orange;
        }
        ~orangeFactory() 
        {
            cout<<"delete orange"<<endl;
        }
};
/******************************************************/

int main() {
    unique_ptr<AbstarctFactory> factory = make_unique<appleFactory>();
    Abstarct* obj = factory->createSimple();
    obj->ability();
    obj->transform();
    return 0;
}
