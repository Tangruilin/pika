#include "ldb/include/ldb_tool.h"

int main(int argc, const char **argv) {
  LDBTool tool;
  tool.Run(argc, argv);
  return 0;
}