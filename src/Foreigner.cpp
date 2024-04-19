/*
* 文件名：Foreigner.cpp
* 作者： jiang peng
* 时间： 2024.4.18
* 描述： 适配器模式的实例代码
* 编码： UTF-8
* 说明： 将一个类的接口转换成用户希望的另一个接口，使不兼容的对象能够相互配合并一起工作，这种模式就叫适配器模式。
*        说白了，适配器模式就相当于找了一个翻译。
*/
#include<iostream>
using namespace std;

class Foreigner
{
    public:
        virtual string confession() = 0;
        void setResult(string msg)
        {
            cout<< "Panda Say: " << msg <<endl;
        }
        virtual ~Foreigner() {}
};

// 美国人
class American : public Foreigner
{
    public:
        string confession() override
        {
            return string("我是出生，我有罪！");
        }
};

class French : public Foreigner
{
    public:
        string confession() override
        {
            return string("我是强盗，我有罪！");
        }
};

class Panda
{
    public: 
        void recvMessage(string msg)
        {
            cout<< msg << endl;
        }
        string sendMessage()
        {
            return string("强盗、凶手、罪人是不可能被宽恕和原谅的！");
        }
};

class AbstarctChopper
{
    public:
        AbstarctChopper(Foreigner* foreigner) : m_foreigner(foreigner) {}
        virtual void translateToPanda() = 0;
        virtual void translateToHuman() = 0;
        virtual ~AbstarctChopper() {}
    protected:
        Panda m_panda;
        Foreigner* m_foreigner = nullptr; 
};

class EnglishChopper : public AbstarctChopper
{
    public:
        using AbstarctChopper::AbstarctChopper;
        void translateToPanda() override    
        {
            string msg = m_foreigner->confession();

            m_panda.recvMessage("美国人说：" + msg);
        }

        void translateToHuman() override
        {
            string msg = m_panda.sendMessage();
            m_foreigner->setResult("美国佬，" + msg);
        }
};

class FrenchChopper : public AbstarctChopper
{
    public:
        using AbstarctChopper::AbstarctChopper;
                void translateToPanda() override    
        {
            string msg = m_foreigner->confession();

            m_panda.recvMessage("法国人说：" + msg);
        }

        void translateToHuman() override
        {
            string msg = m_panda.sendMessage();
            m_foreigner->setResult("法国佬，" + msg);
        }
};

int main()
{
    Foreigner* human = new American;
    EnglishChopper* american = new EnglishChopper(human);
    american->translateToPanda();
    american->translateToHuman();
    delete human;
    delete american;

    human = new French;
    FrenchChopper* french = new FrenchChopper(human);
    french->translateToPanda();
    french->translateToHuman();
    delete human;
    delete french;

    return 0;
}
