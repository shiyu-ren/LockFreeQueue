#include <atomic>

template <typename T>
struct Node
{
    /* data */
    T data;
    Node* next;
    Node() :data(), next(nullptr){}
    Node(const T& data) :data(data), next(nullptr){}
};

template <typename T>
class LockFreeQueue
{
    
public:
    LockFreeQueue(/* args */)
    {
        //dummy node
        head_ = tail_ = new Node<T>();
    }

    bool push(const T& data)
    {
        Node<T> *n = new Node<T>(data);

        Node<T> *tail = nullptr;
        Node<T> *ne = nullptr;
        while(true)
        {
            // 取得尾指针，与尾指针next
            tail = tail_;
            ne = tail->next;

            // 如果其他线程更改了tail_， 重新来
            if(tail_ != tail)   continue;

            //如果尾指针的next不为空，也即有线程已经添加了node，但是还没有更新tail,此时我们直接更改tail
            if(ne != nullptr)
            {
                __sync_bool_compare_and_swap(&tail_, tail, ne);
                continue;
            }

            // 判断加入节点是否成功
            if(__sync_bool_compare_and_swap(&tail_->next, ne, n))
                break;
        }

        __sync_bool_compare_and_swap(&tail_, tail, n);
        
        return true;
    }

    bool pop(T& result)
    {
        if(head_ == tail_)    return false;

        Node<T> *head = nullptr;
        Node<T> *tail = nullptr;
        Node<T> *ne = nullptr;
        while(true)
        {
            head = head_;
            tail = tail_;
            ne = head->next;
            
            // head被其他线程移动，则重新取head
            if(head != head_)   continue;

            // 如果队列为空
            if(head == tail && ne == nullptr)   return false;

            // 此时为有入队线程新添加了节点，但是还没有来得及更新tail
            if(head == tail && ne != nullptr)
            {
                __sync_bool_compare_and_swap(&tail_, tail, ne);
                continue;
            }

            if(__sync_bool_compare_and_swap(&head_, head, ne))
                break;
        }

        result = ne->data;
        delete head;
        return true;
    }
    
private:
    /* data */
    Node<T> *head_;
    Node<T> *tail_;
};

