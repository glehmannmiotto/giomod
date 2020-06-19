/**
 * @file GoodbyeModule.cc GoodbyeModule class
 * implementation
 *
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "GoodbyeModule.hpp"
#include "ers/ers.h"

dunedaq::giomod::GoodbyeModule::GoodbyeModule(const std::string& name)
  : DAQModule(name)
  , thread_(std::bind(&GoodbyeModule::do_work, this))
  , source_(nullptr)
{}

void
dunedaq::giomod::GoodbyeModule::init()
{
  register_command("configure", &GoodbyeModule::do_configure);
  register_command("unconfigure", &GoodbyeModule::do_unconfigure);
//  register_command("start", &GoodbyeModule::do_start);
//  register_command("stop", &GoodbyeModule::do_stop);

  source_.reset(new dunedaq::appfwk::DAQSource<std::string>(get_config()["input"].get<std::string>()));

}

void
dunedaq::giomod::GoodbyeModule::do_configure(const std::vector<std::string>& args)
{
  thread_.start_working_thread_();
}


void
dunedaq::giomod::GoodbyeModule::do_unconfigure(const std::vector<std::string>& args)
{
  thread_.stop_working_thread_();
}

void
dunedaq::giomod::GoodbyeModule::do_start(const std::vector<std::string>& args)
{
}

void
dunedaq::giomod::GoodbyeModule::do_stop(const std::vector<std::string>& args)
{
}

void
dunedaq::giomod::GoodbyeModule::do_work()
{
  std::string s;
  while (thread_.thread_running()) {
    if (source_->can_pop()) {
      try {
        source_->pop(s);
        ers::info(dunedaq::giomod::GreetingResponse(ERS_HERE, s, this->get_name()));	
      }
      catch (ers::Issue &ex) {
         ers::error(dunedaq::giomod::GreetingReceptionFailure(ERS_HERE, ex));
      }
    } 
  }
}

DEFINE_DUNE_DAQ_MODULE(dunedaq::giomod::GoodbyeModule)
