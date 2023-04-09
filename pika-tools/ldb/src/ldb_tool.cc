#include "ldb/include/ldb_tool.h"
#include "ldb/include/ldb_cmd.h"
#include <cstdio>
#include <string>

const std::string LDBTool::TOOL_VERSION = "0.0.1"; // tools version

LDBOptions::LDBOptions() {}

void LDBTool::Run(int argc, const char **argv, Options db_options,
                  const LDBOptions &ldb_options) {
  int error_code =
      LDBCommandRunner::RunCommand(argc, argv, db_options, ldb_options);

  exit(error_code);
}

void LDBCommandRunner::PrintHelp(const LDBOptions &ldb_options,
                                 const char *exec_name, bool to_stderr) {
  std::string ret;
  fprintf(to_stderr ? stderr : stdout, "%s\n", ret.c_str());
}

// Run ldb command
int LDBCommandRunner::RunCommand(int argc, const char *const *argv,
                                 Options options,
                                 const LDBOptions &ldb_options) {
  if (argc <= 2) {
    if (argc <= 1) {
      PrintHelp(ldb_options, argv[0], true);
      return 1;
    } else if (std::string(argv[1]) == "--version") {
      printf("ldb verison %s\n", LDBTool::TOOL_VERSION.c_str());
      return 0;
    } else if (std::string(argv[1]) == "--help") {
      PrintHelp(ldb_options, argv[0], false);
      return 0;
    } else {
      PrintHelp(ldb_options, argv[1], true);
      return 1;
    }
  }

  LDBCommand *cmdObj =
      LDBCommand::InitFromCmdLineArgs(argc, argv, options, ldb_options);

  if (cmdObj == nullptr) {
    fprintf(stderr, "Unknown command\n");
    PrintHelp(ldb_options, argv[0], true);
    return 1;
  }

  // run command
  cmdObj->Run();

  if (!cmdObj->ValidateCmdLineOptions()) {
    return 1;
  }

  LDBCommandExecuteResult ret = cmdObj->GetExecuteResult();
  if (!ret.ToString().empty()) {
    fprintf(stderr, "%s\n", ret.ToString().c_str());
  }

  delete cmdObj;

  return ret.IsFailed() ? 1 : 0;
}
