/**
 * @file HelloModule.hpp
 *
 * HelloModule is a simple DAQModule implementation that produces Hello messages.
 *
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef GIOMOD_SRC_HELLOMODULE_HPP_
#define GIOMOD_SRC_HELLOMODULE_HPP_

#include "appfwk/DAQModule.hpp"
#include "appfwk/ThreadHelper.hpp"
#include "appfwk/DAQSink.hpp"
#include "ers/Issue.h"

namespace dunedaq {
ERS_DECLARE_ISSUE(giomod, GreetingFailed, "Failed to give my greeting", ERS_EMPTY)

namespace giomod {
/**
 * @brief HelloModule creates Hello messages sends them
 * downstream
 */
class HelloModule : public dunedaq::appfwk::DAQModule
{
public:
  /**
   * @brief HelloModule Constructor
   * @param name Instance name for this HelloModule instance
   */
  explicit HelloModule(const std::string& name);

  void init() override;

  HelloModule(const HelloModule&) =
    delete; ///< HelloModule is not copy-constructible
  HelloModule& operator=(const HelloModule&) =
    delete; ///< HelloModule is not copy-assignable
  HelloModule(HelloModule&&) =
    delete; ///< HelloModule is not move-constructible
  HelloModule& operator=(HelloModule&&) =
    delete; ///< HelloModule is not move-assignable

private:
  // Commands
  void do_configure(const std::vector<std::string>& args);
  void do_unconfigure(const std::vector<std::string>& args);
  void do_start(const std::vector<std::string>& args);
  void do_stop(const std::vector<std::string>& args);

  // Threading
  dunedaq::appfwk::ThreadHelper thread_;
  void do_work();

  // Configuration
  std::unique_ptr<dunedaq::appfwk::DAQSink<std::string>> sink_;
  std::string greeting_text_;
  size_t wait_between_sends_ms_;
};
} // namespace giomod
} // namespace dunedaq

#endif // GIOMOD_SRC_HELLOMODULE_HPP_
