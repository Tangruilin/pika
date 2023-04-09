#include "ldb/include/ldb_cmd.h"
#include "ldb/include/ldb_tool.h"
#include "ldb/include/utils.h"
#include <cstdio>
#include <string>

using ParsedParams = LDBCommand::ParsedParams;

const std::string ARG_DB = "db";
const std::string DEFAULT_DB = "./db";

const std::string ARG_TYPE = "type";
const std::string TYPE_META = "meta";
const std::string TYPE_DATA = "data";

const std::string ARG_STRUCTURE = "structure";
const std::string STRUCTURE_STRING = "string";
const std::string STRUCTURE_HASHES = "hashes";
const std::string STRUCTURE_LIST = "list";
const std::string STRUCTURE_SET = "set";
const std::string STRUCTURE_ZSET = "zset";

LDBCommand *LDBCommand::InitFromCmdLineArgs(
    const std::vector<std::string> &args, const Options &options,
    const LDBOptions &ldb_options,
    const std::function<LDBCommand *(const ParsedParams &)> &selector) {
  //  parsed_params.flags
  ParsedParams parsed_params;
  std::vector<std::string> cmdTokens;

  const std::string OPTION_PREFIX = "--";
  // Parse
  for (const auto &arg : args) {
    if (arg[0] == '-' && arg[1] == '-') {
      std::vector<std::string> splits = StringSplit(arg, '=');
      //--option=option_value
      if (splits.size() == 2) {
        std::string optionKey = splits[0].substr(OPTION_PREFIX.size());
        parsed_params.option_map[optionKey] = splits[1];
      } else if (splits.size() == 1) {
        // --flag_name
        std::string optionKey = splits[0].substr(OPTION_PREFIX.size());
        parsed_params.flags.push_back(optionKey);
      } else {
        // option_value contain '='
        std::string optionKey = splits[0].substr(OPTION_PREFIX.size());
        parsed_params.option_map[optionKey] =
            arg.substr(splits[0].length() + 1);
      }
    } else {
      cmdTokens.push_back(arg);
    }
  }

  if (cmdTokens.size() < 1) {
    fprintf(stderr, "Command not specified!");
    return nullptr;
  }

  parsed_params.cmd = cmdTokens[0];
  parsed_params.cmd_params.assign(cmdTokens.begin() + 1, cmdTokens.end());

  // Get Command
  LDBCommand *command = selector(parsed_params);

  return command;
}

LDBCommand *LDBCommand::SelectCommand(const ParsedParams &parsed_params) {
  //  parsed_params.flags
  printf("const char *, ...");
  return nullptr;
}

LDBCommand *LDBCommand::InitFromCmdLineArgs(int argc, char const *const *argv,
                                            const Options &options,
                                            const LDBOptions &ldb_options) {
  std::vector<std::string> args;
  for (int i = 1; i < argc; ++i) {
    args.push_back(argv[i]);
  }
  return InitFromCmdLineArgs(args, options, ldb_options,
                             LDBCommand::SelectCommand);
}

void LDBCommand::Run() { DoCommand(); }