/*
* 文件名：Singleton.cpp
* 作者： jiang peng
* 时间： 2024.4.11
* 描述： 单例模式的实例代码
* 类型： 创建型模式
* 说明： 在一个项目中，全局范围内，某个类的实例有且仅有一个，
*        通过这个唯一实例向其他模块提供数据的全局访问，这种模式就叫单例模式。
*        单例模式的典型应用就是任务队列。
*/
#include<iostream>
#include<queue>
#include<mutex>
#include<thread>
using namespace std;

class TaskQueue
{
private:
    TaskQueue() = default;
    queue<int> m_taskQ;
    static TaskQueue m_obj;
    mutex m_mutex;
public:
    TaskQueue(const TaskQueue& obj) = delete;
    TaskQueue& operator=(const TaskQueue& obj) = delete;

    static TaskQueue* getInstance() {
        return &m_obj;
    }

    bool isEmpty() {
        lock_guard<mutex> lock_guard(mutex);
        return m_taskQ.empty();
    }

    void addTask(int data) {
        lock_guard<mutex> lock_guard(mutex);
        m_taskQ.push(data);
    }

    int taskTask() {
        lock_guard<mutex> lock_guard(mutex);
        if (!m_taskQ.empty()) {
            return m_taskQ.front();
        }
        return -1;
    }

    bool popTask() {
        lock_guard<mutex> lock_guard(mutex);
        if (!m_taskQ.empty()) {
            m_taskQ.pop();
            return true;
        }
        return false;
    }
};
TaskQueue TaskQueue::m_obj;

int main()
{
    thread t1([](){
        TaskQueue* taskQ = TaskQueue::getInstance();
        for(int i = 1; i <= 100; i++) {
            taskQ->addTask(i + 100);
            cout<< "++push_task: " << i + 100 << ", threadID: " << this_thread::get_id() <<endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    });

    thread t2([](){
        TaskQueue* taskQ = TaskQueue::getInstance();
        this_thread::sleep_for(chrono::milliseconds(100));
        while(!taskQ->isEmpty()) {
            int data = taskQ->taskTask();
            cout<< "--take task: " << data << ", threadID: " << this_thread::get_id() <<endl;
            taskQ->popTask();
            this_thread::sleep_for(chrono::seconds(1));
        }
    });

    t1.join();
    t2.join();

    return 0;
}
