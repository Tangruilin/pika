#pragma once

#include "ldb/include/ldb_cmd.h"

class GetCommand : public LDBCommand {
  void DoCommand() override { printf("GetCommand"); };
};

class PutCommand : public LDBCommand {
  void DoCommand() override { printf("PutCommand"); }
};

class ScanCommand : public LDBCommand {
  void DoCommand() override { printf("ScanCommand"); }
};