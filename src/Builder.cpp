/*
* �ļ�����Builder.cpp
* ���ߣ� jiang peng
* ʱ�䣺 2024.4.14
* ������ �������������ߣ�ģʽ��ʵ������
* ���룺 GBK
* ���ͣ� ������ģʽ
* ˵���� ����Ϊ��������ơ�Ҳ���Ƿֲ��贴�����ӵĶ���
*        ��������ʹ����ͬ�Ĵ������ɲ�ͬ���ͺ���ʽ�Ķ���
*        ����ģʽ����������ģʽ��Ҳ�н�����ģʽ��
*/
#include<iostream>
#include<vector>
#include<map>
using namespace std;

class SunnyShip
{
    public:
        void addParts(string name)
        {
            m_parts.push_back(name);
        }

        void showParts()
        {
            for(const auto& item : m_parts)
            {
                cout<< item <<"    ";
            }
            cout<<endl;
        }
    private:
        vector<string> m_parts;
};

class MerryShip
{
    public:
        void assemble(string name, string parts)
        {
            m_parts.insert(make_pair(name, parts));
        }

        void showParts()
        {
            for(const auto& item : m_parts) 
            {
                cout<<item.first<< ": " <<item.second<<"   ";
            }
            cout<<endl;
        }
    private:
        map<string, string> m_parts;
};

class ShipBuilder
{
    public:
        virtual void reset() = 0;
        virtual void buildBody() = 0;
        virtual void buildWeapon() = 0;
        virtual void buildEngine() = 0;
        virtual void buildInterior() = 0;
        virtual ~ShipBuilder() {}
};

class SunnyBuilder : public ShipBuilder
{
    public:
        SunnyBuilder() 
        {
            reset();
        }

        ~SunnyBuilder() 
        {
            if (m_sunny != nullptr) 
            {
                delete m_sunny;
            }
        }
        void reset() override
        {
            m_sunny = new SunnyShip;
        }

        void buildBody() override
        {
            m_sunny->addParts("�����ǵ�������");
        }

        void buildWeapon() override
        {
            m_sunny->addParts("ʨ����");
        }

        void buildEngine() override
        {
            m_sunny->addParts("��������");
        }

        void buildInterior() override
        {
            m_sunny->addParts("��������װ��");
        }

        SunnyShip* getSunny() 
        {
            SunnyShip* ship = m_sunny;
            m_sunny = nullptr;
            return ship;
        }
    private:
        SunnyShip* m_sunny = nullptr;
};

class MerryBuilder : public ShipBuilder
{
    public:
        MerryBuilder()
        {
            reset();
        }

        ~MerryBuilder()
        {
            if (m_merry != nullptr) 
            {
                delete m_merry;    
            }
        }

        void reset() override
        {
            m_merry = new MerryShip;
        }

        void buildBody() override
        {
            m_merry->assemble("����", "����ľ��");
        }

        void buildWeapon() override
        {
            m_merry->assemble("����", "���Ŵ���");
        }

        void buildEngine() override
        {
            m_merry->assemble("����", "������");
        }

        void buildInterior() override
        {
            m_merry->assemble("����", "��װ");
        }

        MerryShip* getMerry()
        {
            MerryShip* ship = m_merry;
            m_merry = nullptr;
            return ship;
        }
    public:
        MerryShip* m_merry = nullptr;
};

class Director
{
    public:
        void setBuilder(ShipBuilder* builder)
        {
            m_builder = builder;
        }

        void builderSimpleShip()
        {
            m_builder->buildBody();
            m_builder->buildEngine();
        }

        void builderStandardShip()
        {
            builderSimpleShip();
            m_builder->buildWeapon();
        }

        void builderRegalShip()
        {
            builderStandardShip();
            m_builder->buildInterior();
        }

    private:
        ShipBuilder* m_builder = nullptr;
};

void builderSunny()
{
    Director* director = new Director;
    SunnyBuilder* builder = new SunnyBuilder;
    // ��Լ��
    director->setBuilder(builder);
    director->builderSimpleShip();
    SunnyShip* sunny = builder->getSunny();
    sunny->showParts();
    delete sunny;

    // ��׼��
    builder->reset();
    director->setBuilder(builder);
    director->builderStandardShip();
    sunny = builder->getSunny();
    sunny->showParts();
    delete sunny;

    // ������
    builder->reset();
    director->setBuilder(builder);
    director->builderRegalShip();
    sunny = builder->getSunny();
    sunny->showParts();
    delete sunny;
    delete builder;
    delete director;
}

// ����÷����
void builderMerry()
{
    Director* director = new Director;
    MerryBuilder* builder = new MerryBuilder;
    // ��Լ��
    director->setBuilder(builder);
    director->builderSimpleShip();
    MerryShip* merry = builder->getMerry();
    merry->showParts();
    delete merry;

    // ��׼��
    builder->reset();
    director->setBuilder(builder);
    director->builderStandardShip();
    merry = builder->getMerry();
    merry->showParts();
    delete merry;

    // ������
    builder->reset();
    director->setBuilder(builder);
    director->builderRegalShip();
    merry = builder->getMerry();
    merry->showParts();
    delete merry;
    delete builder;
    delete director;
}

int main()
{
    builderSunny();
    cout << "=====================================" << endl;
    builderMerry();
    return 0;
}
