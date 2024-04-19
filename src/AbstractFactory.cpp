/*
* �ļ�����AbstractFactory.cpp
* ���ߣ� jiang peng
* ʱ�䣺 2024.4.13
* ������ ���󹤳�ģʽ��ʵ������
* ���룺 GBK
* ���ͣ� ������ģʽ
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
            return string("��<ľ��>�����ִ�����...");
        }
};

class IronBody : public ShipBody
{
    public:
        string getShipBody() override
        {
            return string("��<����>�����ִ�����...");
        }
};

class MetalBody : public ShipBody
{
    public:
        string getShipBody() override
        {
            return string("��<�Ͻ�>�����ִ�����...");
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
            return string("��<ǹ>�����ִ�����...");
        }
};

class Gun : public Weapon
{
    public:
        string getWeapon() override
        {
            return string("��������>�����ִ�����...");
        }
};

class Laser : public Weapon
{
    public:
        string getWeapon() override
        {
            return string("��<����>�����ִ�����...");
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
            return string("��<�ֶ�>�����ִ�����...");
        }
};

class Human : public Engine
{
    public:
        string getEngine() override
        {
            return string("��<��ȼ��>�����ִ�����...");
        }
};

class Nuclear : public Engine
{
    public:
        string getEngine() override
        {
            return string("��<����>�����ִ�����...");
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
            cout << "<������>ս���������, ������ˮ��..." << endl;
            return ship;
        }
};

class StandardFactory : public AbstarctFactory
{
    public:
        Ship* createShip() override
        {
            Ship* ship = new Ship(new IronBody, new Cannon, new Diesel);
            cout << "<��׼��>ս���������, ������ˮ��..." << endl;
            return ship;
        }
};

class UltimateFactory : public AbstarctFactory
{
    public:
        Ship* createShip() override
        {
            Ship* ship = new Ship(new MetalBody, new Laser, new Nuclear);
            cout << "<�콢��>ս���������, ������ˮ��..." << endl;
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
