#### 使用C++实现无锁队列
- LockFreeQueue实现了一个环形无锁队列，只适用于单生产者消费者并发情况
- LockFreeQueueN2N使用CAS机制实现了无锁队列，适用于多生产者消费者并发情况