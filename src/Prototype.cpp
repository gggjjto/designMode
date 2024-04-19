/*
* �ļ�����Prototype.cpp
* ���ߣ� jiang peng
* ʱ�䣺 2024.4.17
* ������ ԭ��ģʽ��ʵ������
* ���룺 GBK
* ���ͣ� ������ģʽ
* ˵���� ��¡���ܻ��ڸ��������֮����У����ҿ����Ƕ�̬�ģ�
*        ������ͨ������Ŀ������캯���޷�ʵ�ֶ��������Ŀ�����
*        ��ʵ�����һ����̬��������Ҫ�������ṩһ����¡����������һ���麯����
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
            return string("����ƻ����");
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
            return string("�����㽶��");
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
