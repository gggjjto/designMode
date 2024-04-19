/*
* 文件名：AbstractFactory.cpp
* 作者： jiang peng
* 时间： 2024.4.13
* 描述： 抽象工厂模式的实例代码
* 编码： GBK
* 类型： 创建型模式
*/
#include<iostream>
#include<string>
#include<memory>
using namespace std;

class ShipBody
{
    public:
        virtual string getShipBody() = 0;
        virtual ~ShipBody() {}
};

class WoodBody : public ShipBody
{
    public:
        string getShipBody() override
        {
            return string("用<木材>制作轮船船体...");
        }
};

class IronBody : public ShipBody
{
    public:
        string getShipBody() override
        {
            return string("用<钢铁>制作轮船船体...");
        }
};

class MetalBody : public ShipBody
{
    public:
        string getShipBody() override
        {
            return string("用<合金>制作轮船船体...");
        }
};

class Weapon
{
    public:
        virtual string getWeapon() = 0;
        virtual ~Weapon() {}
};

class Cannon : public Weapon
{
    public:
        string getWeapon() override
        {
            return string("用<枪>制作轮船武器...");
        }
};

class Gun : public Weapon
{
    public:
        string getWeapon() override
        {
            return string("用速射炮>制作轮船武器...");
        }
};

class Laser : public Weapon
{
    public:
        string getWeapon() override
        {
            return string("用<激光>制作轮船武器...");
        }
};

class Engine
{
    public:
        virtual string getEngine() = 0;
        virtual ~Engine() {}
};

class Diesel : public Engine
{
    public:
        string getEngine() override
        {
            return string("用<手动>制作轮船动力...");
        }
};

class Human : public Engine
{
    public:
        string getEngine() override
        {
            return string("用<内燃机>制作轮船动力...");
        }
};

class Nuclear : public Engine
{
    public:
        string getEngine() override
        {
            return string("用<核能>制作轮船动力...");
        }
};

class Ship
{
    public:
        Ship(ShipBody* body, Weapon* weapon, Engine* engine) : m_body(body), m_weapon(weapon), m_engine(engine) {}
        string getProperty() 
        {
            string info = m_body->getShipBody() + m_weapon->getWeapon() + m_engine->getEngine();
            return info;
        }
        ~Ship()
        {
            delete m_body;
            delete m_weapon;
            delete m_engine;
        }
    private:
        // unique_ptr<ShipBody> m_body;
        // unique_ptr<Weapon> m_weapon;
        // unique_ptr<Engine> m_engine;
        ShipBody* m_body = nullptr;
        Weapon* m_weapon = nullptr;
        Engine* m_engine = nullptr;
};

class AbstarctFactory
{
    public:
        virtual Ship* createShip() = 0;
        virtual ~AbstarctFactory() {}
};

class BasicFactory : public AbstarctFactory
{
    public:
        Ship* createShip() override
        {
            Ship* ship = new Ship(new WoodBody, new Gun, new Human);
            cout << "<基础型>战船生产完毕, 可以下水啦..." << endl;
            return ship;
        }
};

class StandardFactory : public AbstarctFactory
{
    public:
        Ship* createShip() override
        {
            Ship* ship = new Ship(new IronBody, new Cannon, new Diesel);
            cout << "<标准型>战船生产完毕, 可以下水啦..." << endl;
            return ship;
        }
};

class UltimateFactory : public AbstarctFactory
{
    public:
        Ship* createShip() override
        {
            Ship* ship = new Ship(new MetalBody, new Laser, new Nuclear);
            cout << "<旗舰型>战船生产完毕, 可以下水啦..." << endl;
            return ship;
        }
};

int main()
{
    AbstarctFactory* factory = new StandardFactory;
    Ship* ship = factory->createShip();
    cout<< ship->getProperty();
    delete ship;
    delete factory;
    return 0;
}
