#include "services/http/data_source/RocksDbDataSource.h"
#include "services/http/data_source/RocksDbUtils.h"
#include "glog/logging.h"

// TODO(HOMEWORK-2): ADD YOUR CODE HERE.

namespace services {
namespace http {
namespace data_source {

RocksDbDataSource::RocksDbDataSource(std::shared_ptr<rocksdb::DB> instance) : db_(instance) {
  LOG(INFO) << "rocksdb open successfully";
}

std::vector<QueryResult> RocksDbDataSource::query(const std::string &key) {
  // TODO(HOMEWORK-2): ADD YOUR CODE HERE.
  return RocksDbUtils::searchPrefix(db_.get(), key);
}

} // namespace data_source
} // namespace http
} // namespace services
