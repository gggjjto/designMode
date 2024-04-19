/*
* �ļ�����Dirbging.cpp
* ���ߣ� jiang peng
* ʱ�䣺 2024.4.19
* ������ �Ž�ģʽ��ʵ������
* ���룺 GBK
* ���ͣ� �ṹ��ģʽ
* ˵���� �����󲿷ֺ�����ʵ�ֲ��ַ��룬ʹ���ǿ��Զ����ı仯�����ִ���ģʽ�����Ž�ģʽ��
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
        cout<< name << "������" <<endl;
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
            cout<< "����ð��!" <<endl;
        }
};

class SmokerTeam : public AbstarctTeam
{
    public:
        using AbstarctTeam::AbstarctTeam;
        void executeTask() override
        {
            cout<<"Ϊ�����壡"<<endl;
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
            return string("ǰ�� - ÷����");
        }

        void feature() override
        {
            cout<< getName()
                << "-- һ�������к��ߵĴ�" <<endl;
        }
};

class NiuMaShip : public AbstractShip
{
    public:
        using AbstractShip::AbstractShip;
        string getName() override
        {
            return string("ǰ�� - ������");
        }

        void feature() override
        {
            cout<< getName()
                << "-- �þ�û�еõ����ɵ��˿���һ��ϣ���� -- ϣ������˰�" <<endl;
        }
};

int main()
{
    CaoMaoTeam* caomao = new CaoMaoTeam("��ñ������");
    Person* luffy = new Person("·��", "����", "�𽺹�ʵ������", "30�ڱ���", "������");
    Person* zoro = new Person("��¡", "��ʿ", "������", "11��1100����", "·��");
    Person* sanji = new Person("ɽ��", "��ʦ", "���κ�", "10��3200����", "��ɫ");
    Person* nami = new Person("����", "����ʿ", "����+��˹", "3��6600����", "ϲ��Ǯ");
    caomao->addMember(luffy);
    caomao->addMember(zoro);
    caomao->addMember(sanji);
    caomao->addMember(nami);
    Merry* sunny = new Merry(caomao);
    sunny->feature();
    sunny->showTeam();

    SmokerTeam* team = new SmokerTeam("˹Ħ��ĺ�������");
    Person* smoker = new Person("˹Ħ��", "�н�", "ð�̹�ʵ������", "", "������Ѭ����");
    Person* dasiqi = new Person("��˹��", "����", "һ����", "", "����");
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
