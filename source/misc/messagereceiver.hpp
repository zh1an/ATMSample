//
// Created by Zh1an on 2021/1/21.
//

#ifndef ATMSAMPLE_MESSAGERECEIVER_HPP
#define ATMSAMPLE_MESSAGERECEIVER_HPP

#include <misc/messagedispatcher.hpp>

namespace messaging
{
class receiver
{
  queue q;  // 一个 receiver 拥有此队列

public:
  operator sender()
  {  // 允许隐式转换到引用队列的 sender
    return sender(&q);
  }
  dispatcher wait()
  {  // 等待队列创建调度器
    return dispatcher(&q);
  }
};
}  // namespace messaging

#endif  // ATMSAMPLE_MESSAGERECEIVER_HPP
