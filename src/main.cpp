#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include "lock_based_list.cpp"

using namespace std;

stringstream print_list(lock_based_list<int>& list)
{
    stringstream ss;
    for (int i = 0; i < list.get_size(); i++)
    {
        ss << *(list.at(i)) << " ";
    }

    return ss;
}

void push_thread_job(lock_based_list<int>& list, int i)
{
    list.push_front(i);
    //cout << this_thread::get_id() << "\n";
}

bool push_front_test()
{
    lock_based_list<int> list;
    vector<thread> threads;
    for (int i = 0; i < 8; i++)
    {
        threads.push_back(thread(push_thread_job, ref(list), i));
    }

    for (thread& t: threads) {
        t.join();
    }

    if (list.get_size() == 8)
    {
        return true;
    }

    return false;
}

void remove_thread_job(lock_based_list<int>& list)
{
    list.remove(0);
}

bool remove_test()
{
    lock_based_list<int> list;
    for (int i = 0; i < 8; i++)
    {
        list.push_front(333);
    }

    vector<thread> threads;
    for (int i = 0; i < 8; i++)
    {
        threads.push_back(thread(remove_thread_job, ref(list)));
    }

    for (thread& t: threads) {
        t.join();
    }

    if (list.get_size() == 0)
    {
        return true;
    }

    return false;
}

int sum = 0;

void at_thread_job(lock_based_list<int>& list, int i)
{
    sum += *(list.at(i));
}

bool at_test()
{
    lock_based_list<int> list;
    for (int i = 0; i < 8; i++)
    {
        list.push_front(i+50);
    }

    vector<thread> threads;
    for (int i = 0; i < 8; i++)
    {
        threads.push_back(thread(at_thread_job, ref(list), i));
    }

    for (thread& t: threads) {
        t.join();
    }

    if (sum == 428)
    {
        return true;
    }

    return false;
}

int main() {
    cout << push_front_test() << endl;
    cout << remove_test() << endl;
    cout << at_test() << endl;

    return 0;
}