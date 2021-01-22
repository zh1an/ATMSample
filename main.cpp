#include <core/atmmessage.hpp>
#include <core/atmstatement.hpp>
#include <core/bankstatement.hpp>
#include <core/userstatement.hpp>

#include <iostream>
#include <thread>

int main()
{
  atm_sample::bank_machine bankMachine;
  atm_sample::interface_machine interfaceMachine;

  atm_sample::atm atmMachine(bankMachine.get_sender(), interfaceMachine.get_sender());

  std::thread bank_thread(&atm_sample::bank_machine::run, &bankMachine);
  std::thread if_thread(&atm_sample::interface_machine::run, &interfaceMachine);
  std::thread atm_thread(&atm_sample::atm::run, &atmMachine);

  messaging::sender atm_queue(atmMachine.get_sender());

  bool quit_pressed = false;

  while (!quit_pressed)
  {
    char c = getchar();
    switch (c)
    {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        atm_queue.send(atm_sample::digit_pressed(c));
        break;
      case 'b':
        atm_queue.send(atm_sample::balance_pressed());
        break;
      case 'w':
        atm_queue.send(atm_sample::withdraw_pressed(50));
        break;
      case 'c':
        atm_queue.send(atm_sample::cancel_pressed());
        break;
      case 'q':
        quit_pressed = true;
        break;
      case 'i':
        atm_queue.send(atm_sample::card_inserted("acc1234"));
        break;
        //      default:
        //        break;
    }
  }

  bankMachine.done();
  atmMachine.done();
  interfaceMachine.done();

  atm_thread.join();
  bank_thread.join();
  if_thread.join();

  return 0;
}
