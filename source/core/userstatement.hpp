//
// Created by Zh1an on 2021/1/21.
//

#ifndef ATMSAMPLE_USERSTATEMENT_HPP
#define ATMSAMPLE_USERSTATEMENT_HPP

#include <misc/messagereceiver.hpp>

#include <iostream>

namespace atm_sample
{
class interface_machine
{
  messaging::receiver incoming;

public:
  messaging::sender get_sender() { return incoming; }
  void done() { get_sender().send(messaging::close_queue()); }

  void run()
  {
    try
    {
      for (;;)
      {
        incoming.wait()
            .handle<issue_money>([&](issue_money const &msg) {
                std::cout << "Issuing " << msg.amount << std::endl;
                
            })
            .handle<display_insufficient_funds>(
                [&](display_insufficient_funds const &msg) { std::cout << "Insufficient funds" << std::endl; })
            .handle<display_enter_pin>(
                [&](display_enter_pin const &msg) { std::cout << "Please enter your PIN (0-9) " << std::endl; })
            .handle<display_enter_card>(
                [&](display_enter_card const &msg) { std::cout << "Please enter your card (I)" << std::endl; })
            .handle<display_balance>([&](display_balance const &msg) {
              std::cout << "The balance of your account is " << msg.amount << std::endl;
            })
            .handle<display_withdrawal_options>([&](display_withdrawal_options const &msg) {
              std::cout << "Withdraw 50? (w)" << std::endl;
              std::cout << "Display Balance? (b)" << std::endl;
              std::cout << "Cancel? (c)" << std::endl;
            })
            .handle<display_withdrawal_cancelled>(
                [&](display_withdrawal_cancelled const &msg) { std::cout << "Withdrawal cancelled" << std::endl; })
            .handle<display_pin_incorrect_message>(
                [&](display_pin_incorrect_message const &msg) { std::cout << "PIN incorrect" << std::endl; })
            .handle<eject_card>([&](eject_card const &msg) { std::cout << "Ejecting card" << std::endl; });
      }
    }
    catch (messaging::close_queue &)
    {
    }
  }
};
}  // namespace atm_sample

#endif  // ATMSAMPLE_USERSTATEMENT_HPP
