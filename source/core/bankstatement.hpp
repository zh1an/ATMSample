//
// Created by Zh1an on 2021/1/21.
//

#ifndef ATMSAMPLE_BANKSTATEMENT_HPP
#define ATMSAMPLE_BANKSTATEMENT_HPP

namespace atm_sample
{
class bank_machine
{
  messaging::receiver incoming;
  unsigned balance;

public:
  bank_machine() : balance(199) {}

  void done() { get_sender().send(messaging::close_queue()); }

  messaging::sender get_sender() { return incoming; }

  void run()
  {
    try
    {
      for (;;)
      {
        incoming.wait()
            .handle<verify_pin>([&](verify_pin const &msg) {
              if (msg.pin == "1937")
              {
                msg.atm_queue.send(pin_verified());
              }
              else
              {
                msg.atm_queue.send(pin_incorrect());
              }
            })
            .handle<withdraw>([&](withdraw const &msg) {
              if (this->balance >= msg.amount)
              {
                this->balance -= msg.amount;
              }
            })
            .handle<get_balance>([&](get_balance const &msg) { msg.atm_queue.send(atm_sample::balance(balance)); })
            .handle<withdrawal_processed>([&](withdrawal_processed const &msg) {
            })
            .handle<cancel_withdrawal>([&](cancel_withdrawal const &msg) {
            });
      }
    }
    catch (messaging::close_queue const &)
    {
    }
  }
};
}  // namespace atm_sample

#endif  // ATMSAMPLE_BANKSTATEMENT_HPP
