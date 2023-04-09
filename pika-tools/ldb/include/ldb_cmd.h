#pragma once

#include "ldb/include/ldb_cmd_execute_result.h"
#include "ldb/include/ldb_tool.h"

// LDBCommand is used to save command
class LDBCommand {
public:
  LDBCommand();
  virtual ~LDBCommand();

  // commands
  static const std::string ARG_DB;
  static const std::string DEFAULT_DB_PATH;

  static const std::string ARG_TYPE;
  static const std::string TYPE_META;
  static const std::string TYPE_DATA;

  static const std::string ARG_STRUCTURE;
  static const std::string STRUCTURE_STRING;
  static const std::string STRUCTURE_HASHES;
  static const std::string STRUCTURE_LIST;
  static const std::string STRUCTURE_SET;
  static const std::string STRUCTURE_ZSET;

  struct ParsedParams {
    std::string cmd;
    std::vector<std::string> cmd_params;
    std::map<std::string, std::string> option_map;
    std::vector<std::string> flags;
  };

  enum class STRUCTURE {
    STRING,
    HASHES,
    LIST,
    SET,
    ZSET,
  };

  static LDBCommand *SelectCommand(const ParsedParams &parsed_params);

  static LDBCommand *InitFromCmdLineArgs(
      const std::vector<std::string> &args, const Options &options,
      const LDBOptions &ldb_options,
      const std::function<LDBCommand *(const ParsedParams &)> &selector =
          SelectCommand);

  static LDBCommand *InitFromCmdLineArgs(int argc, char const *const *argv,
                                         const Options &options,
                                         const LDBOptions &ldb_options);

  void Run();

  virtual void DoCommand() = 0;

  virtual bool ValidateCmdLineOptions();

  LDBCommandExecuteResult GetExecuteResult() { return exec_state_; };

  void ClearPreviousRunState();

  static std::string Hex2String(const std::string &str);

  static std::string String2Hex(const std::string &str);

protected:
  LDBCommandExecuteResult exec_state_;
  std::string db_prefix_path_;

  bool is_read_only_;
  bool is_key_hex_;
  bool is_value_hex_;

private:
  bool String2Bool(std::string val);
};

class LDBCommandRunner {
public:
  static void PrintHelp(const LDBOptions &ldb_options, const char *exec_name,
                        bool to_stderr = true);

  static int RunCommand(int argc, char const *const *argv, Options options,
                        const LDBOptions &ldb_options);
};