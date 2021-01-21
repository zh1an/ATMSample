//
// Created by Zh1an on 2021/1/21.
//

#ifndef ATMSAMPLE_MESSAGESENDER_HPP
#define ATMSAMPLE_MESSAGESENDER_HPP

#include <misc/messagequeue.hpp>

namespace messaging
{
class sender
{
  queue *q;  // sender 就是封装了队列指针
public:
  sender() : q(nullptr) {}  // 默认构造的 sender 没有队列
  explicit sender(queue *q_) : q(q_) {}  // 允许从指向队列的指针进行构造
  template <typename Message>
  void send(Message const &msg)
  {
    if (q)
    {
      q->push(msg);
    }
  }
};
}  // namespace messaging

#endif  // ATMSAMPLE_MESSAGESENDER_HPP
