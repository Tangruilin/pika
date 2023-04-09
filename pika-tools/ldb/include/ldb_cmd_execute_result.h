#pragma once

#include <string>
class LDBCommandExecuteResult {
public:
  enum class State {
    EXEC_NOT_STARTED = 0,
    EXEC_SUCCEED = 1,
    EXEC_FAILED = 2,
  };

  LDBCommandExecuteResult() : state_(State::EXEC_NOT_STARTED), message_("") {}

  LDBCommandExecuteResult(State state, std::string &msg)
      : state_(state), message_(msg) {}

  std::string ToString() {
    std::string ret;
    switch (state_) {
    case State::EXEC_SUCCEED:
      break;
    case State::EXEC_FAILED:
      ret.append("Failed: ");
      break;
    case State::EXEC_NOT_STARTED:
      ret.append("Not started: ");
    }
    if (!message_.empty()) {
      ret.append(message_);
    }
    return ret;
  }

  void Reset() {
    state_ = State::EXEC_NOT_STARTED;
    message_ = "";
  }

  bool IsSucceed() { return state_ == State::EXEC_SUCCEED; }

  bool IsNotStarted() { return state_ == State::EXEC_NOT_STARTED; }

  bool IsFailed() { return state_ == State::EXEC_FAILED; }

  static LDBCommandExecuteResult Succeed(std::string msg) {
    return LDBCommandExecuteResult(State::EXEC_SUCCEED, msg);
  }

  static LDBCommandExecuteResult Failed(std::string msg) {
    return LDBCommandExecuteResult(State::EXEC_FAILED, msg);
  }

private:
  State state_;
  std::string message_;

  bool operator==(const LDBCommandExecuteResult &);
  bool operator!=(const LDBCommandExecuteResult &);
};