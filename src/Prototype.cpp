/*
* 文件名：Prototype.cpp
* 作者： jiang peng
* 时间： 2024.4.17
* 描述： 原型模式的实例代码
* 编码： GBK
* 类型： 创建型模式
* 说明： 克隆可能会在父类和子类之间进行，并且可能是动态的，
*        很明显通过父类的拷贝构造函数无法实现对子类对象的拷贝，
*        其实这就是一个多态，我们需要给父类提供一个克隆函数并且是一个虚函数。
*/

#include<iostream>
using namespace std;

class Seed
{
    public:
        virtual Seed* clone() = 0;
        virtual string whoSeed() = 0;
        virtual ~Seed() {}
};

class Apple : public Seed
{
    public:
        Seed* clone() override
        {
            return new Apple(*this);
        }

        string whoSeed() override
        {
            return string("我是苹果！");
        }
};

class Banana : public Seed
{
    public:
        Seed* clone() override
        {
            return new Banana(*this);
        }

        string whoSeed() override
        {
            return string("我是香蕉！");
        }
};

int main()
{
    Seed* obj = new Apple;
    Seed* objA = obj->clone();
    cout<<objA->whoSeed()<<endl;

    delete objA;
    delete obj;

    obj = new Banana;
    objA = obj->clone();
    cout<<objA->whoSeed()<<endl;

    delete objA;
    delete obj;

    return 0;
}
