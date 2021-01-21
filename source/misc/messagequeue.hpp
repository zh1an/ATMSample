//
// Created by Zh1an on 2021/1/21.
//

#ifndef ATMSAMPLE_MESSAGEQUEUE_HPP
#define ATMSAMPLE_MESSAGEQUEUE_HPP

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

namespace messaging
{
struct message_base
{  // 队列项目的基类
  virtual ~message_base() = default;
};

template <typename Msg>
struct wrapped_message : message_base
{  // 消息类型有特殊的定义
  Msg contents;
  explicit wrapped_message(Msg const &contents_) : contents(contents_) {}
};

class queue
{  // 消息队列
  std::mutex mutex;
  std::condition_variable conditionVariable;
  std::queue<std::shared_ptr<message_base>> q;  // 实际的队列存储 message_base 指针
public:
  template <typename T>
  void push(T const &msg)
  {
    std::lock_guard<std::mutex> lk(mutex);
    q.push(std::make_shared<wrapped_message<T>>(msg));
    conditionVariable.notify_all();
  }

  std::shared_ptr<message_base> wait_and_pop()
  {
    std::unique_lock<std::mutex> lk(mutex);
    conditionVariable.wait(lk, [&] { return !q.empty(); });
    auto res = q.front();
    q.pop();
    return res;
  }
};
};  // namespace messaging

#endif  // ATMSAMPLE_MESSAGEQUEUE_HPP
