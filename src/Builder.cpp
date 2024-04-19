/*
* 文件名：Builder.cpp
* 作者： jiang peng
* 时间： 2024.4.14
* 描述： 生成器（建造者）模式的实例代码
* 编码： GBK
* 类型： 创建型模式
* 说明： 化繁为简，逐个击破。也就是分步骤创建复杂的对象，
*        并且允许使用相同的代码生成不同类型和形式的对象，
*        这种模式叫做生成器模式（也叫建造者模式）
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
            m_sunny->addParts("神树亚当的树干");
        }

        void buildWeapon() override
        {
            m_sunny->addParts("狮吼炮");
        }

        void buildEngine() override
        {
            m_sunny->addParts("可乐驱动");
        }

        void buildInterior() override
        {
            m_sunny->addParts("豪华内饰装修");
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
            m_merry->assemble("船体", "优质木材");
        }

        void buildWeapon() override
        {
            m_merry->assemble("武器", "四门大炮");
        }

        void buildEngine() override
        {
            m_merry->assemble("动力", "蒸汽机");
        }

        void buildInterior() override
        {
            m_merry->assemble("内室", "精装");
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
    // 简约型
    director->setBuilder(builder);
    director->builderSimpleShip();
    SunnyShip* sunny = builder->getSunny();
    sunny->showParts();
    delete sunny;

    // 标准型
    builder->reset();
    director->setBuilder(builder);
    director->builderStandardShip();
    sunny = builder->getSunny();
    sunny->showParts();
    delete sunny;

    // 豪华型
    builder->reset();
    director->setBuilder(builder);
    director->builderRegalShip();
    sunny = builder->getSunny();
    sunny->showParts();
    delete sunny;
    delete builder;
    delete director;
}

// 建造梅利号
void builderMerry()
{
    Director* director = new Director;
    MerryBuilder* builder = new MerryBuilder;
    // 简约型
    director->setBuilder(builder);
    director->builderSimpleShip();
    MerryShip* merry = builder->getMerry();
    merry->showParts();
    delete merry;

    // 标准型
    builder->reset();
    director->setBuilder(builder);
    director->builderStandardShip();
    merry = builder->getMerry();
    merry->showParts();
    delete merry;

    // 豪华型
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
