#pragma once

#include "rocksdb/options.h"
#include "rocksdb/rocksdb_namespace.h"
#include "rocksdb/slice.h"

using ROCKSDB_NAMESPACE::Options;
using ROCKSDB_NAMESPACE::Slice;

class SliceFormatter {
public:
  virtual ~SliceFormatter() {}
  virtual std::string Format(const Slice &s) const = 0;
};

// Options for customizing ldb tool (beyond the DB Options)
struct LDBOptions {
  // Create LDBOptions with default values for all fields
  LDBOptions();

  // Key formatter that converts a slice to a readable string.
  // Default: Slice::ToString()
  std::shared_ptr<SliceFormatter> key_formatter;

  std::string print_help_header = "ldb - Pika Tool";
};

class LDBTool {
public:
  static const std::string TOOL_VERSION;
  void Run(int argc, const char **argv, Options db_options = Options(),
           const LDBOptions &ldb_options = LDBOptions());
};