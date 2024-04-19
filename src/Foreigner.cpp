/*
* �ļ�����Foreigner.cpp
* ���ߣ� jiang peng
* ʱ�䣺 2024.4.18
* ������ ������ģʽ��ʵ������
* ���룺 UTF-8
* ˵���� ��һ����Ľӿ�ת�����û�ϣ������һ���ӿڣ�ʹ�����ݵĶ����ܹ��໥��ϲ�һ����������ģʽ�ͽ�������ģʽ��
*        ˵���ˣ�������ģʽ���൱������һ�����롣
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

// ������
class American : public Foreigner
{
    public:
        string confession() override
        {
            return string("���ǳ����������");
        }
};

class French : public Foreigner
{
    public:
        string confession() override
        {
            return string("����ǿ���������");
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
            return string("ǿ�������֡������ǲ����ܱ���ˡ��ԭ�µģ�");
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

            m_panda.recvMessage("������˵��" + msg);
        }

        void translateToHuman() override
        {
            string msg = m_panda.sendMessage();
            m_foreigner->setResult("�����У�" + msg);
        }
};

class FrenchChopper : public AbstarctChopper
{
    public:
        using AbstarctChopper::AbstarctChopper;
                void translateToPanda() override    
        {
            string msg = m_foreigner->confession();

            m_panda.recvMessage("������˵��" + msg);
        }

        void translateToHuman() override
        {
            string msg = m_panda.sendMessage();
            m_foreigner->setResult("�����У�" + msg);
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
