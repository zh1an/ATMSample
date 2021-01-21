//
// Created by Zh1an on 2021/1/21.
//

#ifndef ATMSAMPLE_ATMMESSAGE_HPP
#define ATMSAMPLE_ATMMESSAGE_HPP

#include <misc/messagesender.hpp>

#include <string>

namespace atm_sample
{
struct withdraw
{
  std::string account;
  unsigned amount;
  mutable messaging::sender atm_queue;

  withdraw(std::string account_, unsigned amount_, messaging::sender atm_queue_)
      : account(std::move(account_)), amount(amount_), atm_queue(atm_queue_)
  {
  }
};

struct withdraw_ok
{
};

struct withdraw_denied
{
};

struct cancel_withdrawal
{
  std::string account;
  unsigned amount;

  cancel_withdrawal(std::string account_, unsigned amount_) : account(std::move(account_)), amount(amount_) {}
};

struct withdrawal_processed
{
  std::string account;
  unsigned amount;

  withdrawal_processed(std::string account_, unsigned amount_) : account(std::move(account_)), amount(amount_) {}
};

struct card_inserted
{
  std::string account;

  explicit card_inserted(std::string account_) : account(std::move(account_)) {}
};

struct digit_pressed
{
  char digit;

  explicit digit_pressed(char digit_) : digit(digit_) {}
};

struct clear_last_pressed
{
};

struct eject_card
{
};

struct withdraw_pressed
{
  unsigned amount;

  explicit withdraw_pressed(unsigned amount_) : amount(amount_) {}
};

struct cancel_pressed
{
};

struct issue_money
{
  unsigned amount;

  explicit issue_money(unsigned amount_) : amount(amount_) {}
};

struct verify_pin
{
  std::string account;
  std::string pin;
  mutable messaging::sender atm_queue;

  verify_pin(std::string account_, std::string pin_, messaging::sender atm_queue_)
      : account(std::move(account_)), pin(std::move(pin_)), atm_queue(atm_queue_)
  {
  }
};

struct pin_verified
{
};

struct pin_incorrect
{
};

struct display_enter_pin
{
};

struct display_enter_card
{
};

struct display_insufficient_funds
{
};

struct display_withdrawal_cancelled
{
};

struct display_pin_incorrect_message
{
};

struct display_withdrawal_options
{
};

struct get_balance
{
  std::string account;
  mutable messaging::sender atm_queue;

  get_balance(std::string account_, messaging::sender atm_queue_) : account(std::move(account_)), atm_queue(atm_queue_)
  {
  }
};

struct balance
{
  unsigned amount;

  explicit balance(unsigned amount_) : amount(amount_) {}
};

struct display_balance
{
  unsigned amount;

  explicit display_balance(unsigned amount_) : amount(amount_) {}
};

struct balance_pressed
{
};

}  // namespace atm_sample

#endif  // ATMSAMPLE_ATMMESSAGE_HPP
