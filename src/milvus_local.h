#pragma once

#include <cstdint>
#include <mutex>
#include <string>
#include <vector>
#include "status.h"
#include "common.h"
#include "index.h"
#include "retrieve_result.h"
#include "search_result.h"
#include "storage.h"
#include "type.h"

namespace milvus::local {

class MilvusLocal final : NonCopyableNonMovable {
 public:
    explicit MilvusLocal(const char* db_file);
    ~MilvusLocal();

 public:
    // load all meta info
    bool
    Init();

    Status
    LoadCollection(const std::string& collection_name);

    Status
    ReleaseCollection(const std::string& collection_name);

    Status
    CreateCollection(const std::string& collection_name,
                     const std::string& pk_name,
                     const std::string& schema_proto);

    Status
    GetCollection(const std::string& collection_name,
                  std::string* schema_proto);

    bool
    DropCollection(const std::string& collection_name);

    void
    GetAllCollections(std::vector<std::string>* collection_names);

    Status
    CreateIndex(const std::string& collection_name,
                const std::string& index_name,
                const std::string& index_proto);

    Status
    GetIndex(const std::string& collection_name,
             const std::string& index_name,
             std::string* index_proto);

    Status
    GetAllIndexs(const std::string& collection_name,
                 std::vector<std::string>* all_index_proto);

    Status
    DropIndex(const std::string& collection_name,
              const std::string& index_name);

    /*
     * Row 为InsertRecord proto数据.
     */
    Status
    Insert(const std::string& collection_name,
           const Rows& rows,
           std::vector<std::string>* ids);
    Status
    Retrieve(const std::string& collection_name,
             const std::string& expr,
             RetrieveResult* result);

    Status
    Search(const std::string& collection_name,
           const std::string& plan,
           const std::string& placeholder_group,
           SearchResult* result);

    Status
    DeleteByIds(const std::string& collection_name,
                const std::string& ids,
                int64_t size,
                const std::vector<std::string>& storage_id);

    Status
    GetNumRowsOfCollection(const std::string& collection_name, int64_t* num);

 private:
    Status
    CheckCollectionName(const std::string& collection_name);

 private:
    std::mutex mutex_;
    std::string db_file_;
    Storage storage_;
    Index index_;
    bool initialized;
};

}  // namespace milvus::local
