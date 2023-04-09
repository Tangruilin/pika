project(ldb)

aux_source_directory(src LDB_SRC)

add_executable(ldb ${LDB_SRC})

add_dependencies(ldb
  rocksdb
  gflags
  gtest
  ${LIBUNWIND_NAME}
  glog
  snappy
  zstd
  lz4
  zlib
  ${LIBJEMALLOC_NAME}
)

target_include_directories(ldb
  PUBLIC  ..
  PUBLIC  .
  PUBLIC  ./include
  ${INSTALL_INCLUDEDIR}
)

target_link_directories(${PROJECT_NAME}
  PUBLIC ${INSTALL_LIBDIR_64}
  PUBLIC ${INSTALL_LIBDIR})

message(${LIB_GLOG})

target_link_libraries(ldb
  librocksdb.a
  ${LIB_GLOG}
  ${LIB_GFLAGS}
  libsnappy.a
  libzstd.a
  liblz4.a
  libz.a
  ${JEMALLOC_LIBRARY}
)