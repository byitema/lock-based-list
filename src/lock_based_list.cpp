#include <mutex>

using namespace std;

template<typename T>
class lock_based_list
{
private:
    //list node
    struct node
    {
        shared_ptr<T> data;
        unique_ptr<node> next;

        node(): next(){}

        node(T const& value): data(make_shared<T>(value)){}
    };

    node head;
    mutex m;
    size_t size;
public:
    lock_based_list(): size(0){}
    ~lock_based_list()
    {
        //TODO
    }

    //deleting copy constructors
    lock_based_list(lock_based_list const& list) = delete;
    lock_based_list& operator=(lock_based_list const& list) = delete;

    //add
    void push_front(T const& value)
    {
        unique_ptr<node> new_node(new node(value));

        lock_guard<mutex> lock(m);
        new_node->next = move(head.next);
        head.next = move(new_node);
        size++;
    }

    //size
    size_t get_size()
    {
        lock_guard<mutex> lock(m);
        return size;
    }

    //get by index
    shared_ptr<T> at(size_t index)
    {
        lock_guard<mutex> lock(m);
        if (index >= 0 && index < size)
        {
            node* current_node = head.next.get();
            size_t i = 0;
            while (i != index)
            {
                current_node = current_node->next.get();
                i++;
            }

            return current_node->data;
        }

        return shared_ptr<T>();
    }

    //remove by index
    void remove(size_t index)
    {
        lock_guard<mutex> lock(m);
        if (index >= 0 && index < size)
        {
            node* current_node = head.next.get();
            size_t i = 0;
            while (i != (index - 1))
            {
                current_node = current_node->next.get();
                i++;
            }

            node* const next = current_node->next.get();
            unique_ptr<node> old_next = move(current_node->next);
            current_node->next = move(next->next);
            size--;
        }
    }
};
