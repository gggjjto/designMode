/*
* 文件名：Dirbging.cpp
* 作者： jiang peng
* 时间： 2024.4.19
* 描述： 桥接模式的实例代码
* 编码： GBK
* 类型： 结构型模式
* 说明： 将抽象部分和它的实现部分分离，使它们可以独立的变化，这种处理模式就是桥接模式。
*/

#include<iostream>
#include<map>
using namespace std;

struct Person
{
    Person(string name, string job, string abiliy, string reward, string beiZhu)
    {
        this->name = name;
        this->job = job;
        this->abiliy = abiliy;
        this->reward = reward;
        this->beiZhu = beiZhu;
    }
    ~Person()
    {
        cout<< name << "被析构" <<endl;
    }
    string name;
    string job;
    string abiliy;
    string reward;
    string beiZhu;
};

class AbstarctTeam
{
    public:
        AbstarctTeam(string name) : m_teamName(name) {}
        string getMember()
        {
            return m_teamName;
        }

        void addMember(Person* p) 
        {
            m_infoMap.insert(make_pair(p->name, p));
        }

        void show()
        {
            cout<< m_teamName <<": "<<endl;
            for(const auto& item : m_infoMap) 
            {
                cout<< "[Name: " << item.second->name 
                    << ", job: " << item.second->job
                    << ", abiliy: " << item.second->abiliy
                    << ", beiZhu: " << item.second->beiZhu
                    << "]" <<endl;
            }
        }

        virtual void executeTask() = 0;
        virtual ~AbstarctTeam()
        {
            for (const auto& item : m_infoMap) 
            {
                delete item.second;
            }
        }
    protected:
        string m_teamName = string();
        map<string, Person*> m_infoMap;
};

class CaoMaoTeam : public AbstarctTeam
{
    public:
        using AbstarctTeam::AbstarctTeam;
        void executeTask() override
        {
            cout<< "海上冒险!" <<endl;
        }
};

class SmokerTeam : public AbstarctTeam
{
    public:
        using AbstarctTeam::AbstarctTeam;
        void executeTask() override
        {
            cout<<"为了正义！"<<endl;
        }
};

class AbstractShip
{
    public:
        AbstractShip(AbstarctTeam* team) : m_team(team) {}
        void showTeam()
        {
            m_team->show();
            m_team->executeTask();
        }

        virtual string getName() = 0;
        virtual void feature() = 0;
        virtual ~AbstractShip() {}

    protected:
        AbstarctTeam* m_team = nullptr;
};

class Merry : public AbstractShip
{
    public:
        using AbstractShip::AbstractShip;
        string getName() override
        {
            return string("前进 - 梅利号");
        }

        void feature() override
        {
            cout<< getName()
                << "-- 一艘在梦中航线的船" <<endl;
        }
};

class NiuMaShip : public AbstractShip
{
    public:
        using AbstractShip::AbstractShip;
        string getName() override
        {
            return string("前进 - 海军号");
        }

        void feature() override
        {
            cout<< getName()
                << "-- 好久没有得到放松的人开的一艘希望船 -- 希望到达彼岸" <<endl;
        }
};

int main()
{
    CaoMaoTeam* caomao = new CaoMaoTeam("草帽海贼团");
    Person* luffy = new Person("路飞", "船长", "橡胶果实能力者", "30亿贝里", "爱吃肉");
    Person* zoro = new Person("索隆", "剑士", "三刀流", "11亿1100万贝里", "路痴");
    Person* sanji = new Person("山治", "厨师", "隐形黑", "10亿3200万贝里", "好色");
    Person* nami = new Person("娜美", "航海士", "天候棒+宙斯", "3亿6600万贝里", "喜欢钱");
    caomao->addMember(luffy);
    caomao->addMember(zoro);
    caomao->addMember(sanji);
    caomao->addMember(nami);
    Merry* sunny = new Merry(caomao);
    sunny->feature();
    sunny->showTeam();

    SmokerTeam* team = new SmokerTeam("斯摩格的海军部队");
    Person* smoker = new Person("斯摩格", "中将", "冒烟果实能力者", "", "爱吃烟熏鸡肉");
    Person* dasiqi = new Person("达斯琪", "大佐", "一刀流", "", "近视");
    team->addMember(smoker);
    team->addMember(dasiqi);
    NiuMaShip* ship = new NiuMaShip(team);
    ship->feature();
    ship->showTeam();

    delete caomao;
    delete sunny;
    delete team;
    delete ship;

    return 0;
}
