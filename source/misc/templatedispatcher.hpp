//
// Created by Zh1an on 2021/1/21.
//

#ifndef ATMSAMPLE_TEMPLATEDISPATCHER_HPP
#define ATMSAMPLE_TEMPLATEDISPATCHER_HPP

#include <misc/messagedispatcher.hpp>
#include <misc/messagesender.hpp>

namespace messaging
{
template <typename PreviousDispatcher, typename Msg, typename Func>
class TemplateDispatcher
{
  queue *q;
  PreviousDispatcher *prev;
  Func f;
  bool chained;

  template <typename Dispatcher, typename OtherMsg, typename OtherFunc>
  friend class TemplateDispatcher;  // TemplateDispatcher 实例之间互为友元

  void wait_and_dispatch()
  {
    for (;;)
    {
      auto msg = q->wait_and_pop();
      if (dispatch(msg))  // 如果我们处理了消息，跳出循环
        break;
    }
  }

  bool dispatch(std::shared_ptr<message_base> const &msg)
  {
    if (auto *wrapper = dynamic_cast<wrapped_message<Msg> *>(msg.get()))
    {  // 检查消息类型并调用函数
      f(wrapper->contents);
      return true;
    }
    else
    {
      return prev->dispatch(msg);  // 链至前一个调度器
    }
  }

public:
  TemplateDispatcher(TemplateDispatcher &&other) noexcept
      : q(other.q), prev(other.prev), f(std::move(other.f)), chained(other.chained)
  {
    other.chained = true;
  }

  TemplateDispatcher(queue *q_, PreviousDispatcher *prev_, Func &&f_)
      : q(q_), prev(prev_), f(std::forward<Func>(f_)), chained(false)
  {
    prev_->chained = true;
  }

  TemplateDispatcher(TemplateDispatcher const &) = delete;
  TemplateDispatcher &operator=(TemplateDispatcher const &) = delete;

  template <typename OtherMsg, typename OtherFunc>
  TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc> handle(OtherFunc &&of)  // 可以连接附加的处理函数
  {
    return TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>(q, this, std::forward<OtherFunc>(of));
  }

  ~TemplateDispatcher() noexcept(false)
  {  // 析构函数又是 noexcept(false) 的
    if (!chained)
    {
      wait_and_dispatch();
    }
  }
};
}  // namespace messaging

#endif  // ATMSAMPLE_TEMPLATEDISPATCHER_HPP
