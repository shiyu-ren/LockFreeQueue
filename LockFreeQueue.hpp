#include <atomic>


template <typename T, int CAPICITY>
class LockFreeQueue
{
public:
    LockFreeQueue(/* args */)
    {
        head_ = 0;
        tail_ = 0;
        size_ = 0;
    }

    bool push(const T& data)
    {
        if(size_ >= CAPICITY) return false;
        
        // 先放入，再改变，可以在单消单生场景下保证正确型
        data_[tail_] = data;
        ++tail_;
        if(tail_ == CAPICITY)   tail_ = 0; 
        ++size_;
        
        return true;
    }

    bool pop(T& result)
    {
        if(size_ == 0)    return false;

        result = data_[head_];
        ++head_;
        if(head_ == CAPICITY)   head_ = 0; 
        --size_;

        return true;
    }
    
private:
    /* data */
    int head_;
    int tail_;
    int size_;
    T data_[CAPICITY];
};

