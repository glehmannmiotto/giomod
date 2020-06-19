/**
 * @file HelloModule.cc HelloModule class
 * implementation
 *
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "HelloModule.hpp"

#include <thread>
#include "ers/ers.h"

dunedaq::giomod::HelloModule::HelloModule(const std::string& name)
  : DAQModule(name)
  , thread_(std::bind(&HelloModule::do_work, this))
  , sink_(nullptr)
{}

void
dunedaq::giomod::HelloModule::init()
{
  register_command("configure", &HelloModule::do_configure);
  register_command("unconfigure", &HelloModule::do_unconfigure);
  register_command("start", &HelloModule::do_start);
  register_command("stop", &HelloModule::do_stop);
  
  sink_.reset(new dunedaq::appfwk::DAQSink<std::string>(get_config()["output"].get<std::string>()));
}

void
dunedaq::giomod::HelloModule::do_configure(const std::vector<std::string>& args)
{

  wait_between_sends_ms_ = get_config().value<int>("wait_between_sends_ms", 1000);
  greeting_text_ = get_config()["greeting_text"].get<std::string>();
}

void
dunedaq::giomod::HelloModule::do_unconfigure(const std::vector<std::string>& args)
{
  return;
}

void
dunedaq::giomod::HelloModule::do_start(const std::vector<std::string>& args)
{
  thread_.start_working_thread_();
}

void
dunedaq::giomod::HelloModule::do_stop(const std::vector<std::string>& args)
{
  thread_.stop_working_thread_();
}

void
dunedaq::giomod::HelloModule::do_work()
{
  int count=0;
  while (thread_.thread_running()) {
    try {
      std::ostringstream os;
      os << count << " " << greeting_text_;
      sink_->push(std::move(os.str()));
      ++count;
    }
    catch (ers::Issue &ex) {
       ers::error(dunedaq::giomod::GreetingFailed(ERS_HERE, ex));
       std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    catch (std::exception &ex) {
       ers::error(dunedaq::giomod::GreetingFailed(ERS_HERE, ex));
       std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    if (wait_between_sends_ms_ > 0) std::this_thread::sleep_for(std::chrono::milliseconds(wait_between_sends_ms_));
  }
}

DEFINE_DUNE_DAQ_MODULE(dunedaq::giomod::HelloModule)
