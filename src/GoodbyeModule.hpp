/**
 * @file GoodbyeModule.hpp
 *
 * GoodbyeModule is a simple DAQModule implementation that produces Goodbye messages.
 *
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef GIOMOD_SRC_GOODBYEMODULE_HPP_
#define GIOMOD_SRC_GOODBYEMODULE_HPP_

#include "appfwk/DAQModule.hpp"
#include "appfwk/ThreadHelper.hpp"
#include "appfwk/DAQSource.hpp"
#include "ers/Issue.h"

namespace dunedaq {
ERS_DECLARE_ISSUE(giomod, GreetingIssue, "Failed to give my greeting", ERS_EMPTY)

ERS_DECLARE_ISSUE(giomod, GreetingReceptionFailure, "Failed receiving a greeting", ERS_EMPTY)

ERS_DECLARE_ISSUE(giomod, GreetingResponse, "Received greeting " << greeting << ". Well..." << name << " says Good-bye!", ((std::string)greeting) ((std::string)name) )

namespace giomod {
/**
 * @brief GoodbyeModule creates Goodbye messages sends them
 * downstream
 */
class GoodbyeModule : public dunedaq::appfwk::DAQModule
{
public:
  /**
   * @brief GoodbyeModule Constructor
   * @param name Instance name for this GoodbyeModule instance
   */
  explicit GoodbyeModule(const std::string& name);

  void init() override;

  GoodbyeModule(const GoodbyeModule&) =
    delete; ///< GoodbyeModule is not copy-constructible
  GoodbyeModule& operator=(const GoodbyeModule&) =
    delete; ///< GoodbyeModule is not copy-assignable
  GoodbyeModule(GoodbyeModule&&) =
    delete; ///< GoodbyeModule is not move-constructible
  GoodbyeModule& operator=(GoodbyeModule&&) =
    delete; ///< GoodbyeModule is not move-assignable

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
  std::unique_ptr<dunedaq::appfwk::DAQSource<std::string>> source_;
};
} // namespace giomod
} // namespace dunedaq

#endif // GIOMOD_SRC_GOODBYEMODULE_HPP_
