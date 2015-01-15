// Copyright 2014 MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "driver/config/prelude.hpp"

#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>

#include "bson/builder.hpp"
#include "bson/document.hpp"
#include "driver/base/bulk_write.hpp"
#include "driver/base/cursor.hpp"
#include "driver/base/read_preference.hpp"
#include "driver/base/write_concern.hpp"
#include "driver/options/aggregate.hpp"
#include "driver/options/bulk_write.hpp"
#include "driver/options/count.hpp"
#include "driver/options/delete.hpp"
#include "driver/options/distinct.hpp"
#include "driver/options/find.hpp"
#include "driver/options/find_one_and_delete.hpp"
#include "driver/options/find_one_and_replace.hpp"
#include "driver/options/find_one_and_update.hpp"
#include "driver/options/insert.hpp"
#include "driver/options/update.hpp"
#include "driver/result/bulk_write.hpp"
#include "driver/result/delete.hpp"
#include "driver/result/insert_many.hpp"
#include "driver/result/insert_one.hpp"
#include "driver/result/replace_one.hpp"
#include "driver/result/update.hpp"

namespace mongo {
namespace driver {

class client;
class database;
class pipeline;

// TODO: make copyable when c-driver supports this

class LIBMONGOCXX_EXPORT collection {

   public:
    collection(collection&& other) noexcept;
    collection& operator=(collection&& rhs) noexcept;

    ~collection();

    /// Runs an aggregation framework pipeline.
    ///
    /// @see http://docs.mongodb.org/manual/reference/command/aggregate/
    ///
    /// @param pipeline the pipeline of aggregation operations to perform
    /// @param options optional arguments, see mongo::driver::options::aggregate
    /// @return a mongo::driver::cursor with the results
    cursor aggregate(
        const pipeline& pipeline,
        const options::aggregate& options = options::aggregate()
    );

    /// Sends a container of writes to the server to be executed as a single operation.
    ///
    /// @see http://docs.mongodb.org/manual/core/bulk-write-operations/
    ///
    /// @param requests a container of mongo::driver::model::writes
    /// @param options optional arguments, see mongo::driver::options::bulk_write
    /// @return the optional result of the bulk operation execution, mongo::driver::result::bulk_write
    /// @throws bulk_write_exception
    template<class Container>
    inline optional<result::bulk_write> bulk_write(
        const Container& requests,
        const options::bulk_write& options = options::bulk_write()
    );


    /// Sends writes starting at begin and ending at end to the server as a batch operation.
    ///
    /// @see http://docs.mongodb.org/manual/core/bulk-write-operations/
    ///
    /// @param begin iterator pointing to the first write to send
    /// @param end iterator pointing to the end of the writes
    /// @param options optional arguments, see mongo::driver::options::bulk_write
    /// @return the optional result of the bulk operation execution
    /// @throws bulk_write_exception
    template<class WriteModelIterator>
    inline optional<result::bulk_write> bulk_write(
        WriteModelIterator begin,
        WriteModelIterator end,
        const options::bulk_write& options = options::bulk_write()
    );

    /// Sends a batch of writes represented by the bulk_write to the server.
    ///
    /// @see http://docs.mongodb.org/manual/core/bulk-write-operations/
    ///
    /// @param bulk_write the bulk writes
    /// @return the optional result of the bulk operation execution
    /// @throws bulk_write_exception
    optional<result::bulk_write> bulk_write(
        const class bulk_write& bulk_write
    );

    /// Gets the number of documents matching the filter.
    ///
    /// @see http://docs.mongodb.org/manual/reference/command/count/
    ///
    /// @param filter the filter that documents must match in order to be counted
    /// @param options optional arguments, see mongo::driver::options::count
    /// @return the count of the documents that matched the filter
    std::int64_t count(
        bson::document::view filter,
        const options::count& options = options::count()
    );

    /// Creates an index.
    ///
    /// @see http://docs.mongodb.org/manual/reference/method/db.collection.createIndex/
    /// @see http://docs.mongodb.org/manual/reference/method/db.collection.ensureIndex/#ensureindex-options
    ///
    /// @param keys the keys for the index: {a: 1, b: -1}
    /// @param options optional arguments to index creation command, see ensure-index options link
    bson::document::value create_index(
        bson::document::view keys,
        bson::document::view options
    );

    /// Deletes a single matching document.
    ///
    /// @see http://docs.mongodb.org/manual/reference/command/delete/
    ///
    /// @param filter the first document matching this filter will be deleted
    /// @param options optional arguments, see mongo::driver::options::delete_options
    /// @return the result of performing the deletion
    /// @throws write_exception
    optional<result::delete_result> delete_one(
        bson::document::view filter,
        const options::delete_options& options = options::delete_options()
    );

    /// Deletes all matching documents.
    ///
    /// @see http://docs.mongodb.org/manual/reference/command/delete/
    ///
    /// @param filter the documents matching this filter will be deleted
    /// @param options optional arguments, see mongo::driver::options::delete_options
    /// @return the result of performing the deletion
    /// @throws write_exception
    optional<result::delete_result> delete_many(
        bson::document::view filter,
        const options::delete_options& options = options::delete_options()
    );

    /// Finds the distinct values for a specified field accross a single collection.
    ///
    /// @see http://docs.mongodb.org/manual/reference/command/distinct/
    ///
    /// @param field_name the field for which the distinct values will be found
    /// @param filter a filter for documents to be applied before searching for distinct values
    /// @param options optional arguments, see mongo::driver::options::distinct
    /// @return cursor having the distinct values for the specified field in the matching documents
    cursor distinct(
        const std::string& field_name,
        bson::document::view filter,
        const options::distinct& options = options::distinct()
    );

    /// Drops this collection.
    ///
    /// @see http://docs.mongodb.org/manual/reference/method/db.collection.drop/
    void drop();

    /// Finds the documents matching the filter.
    ///
    /// @see http://docs.mongodb.org/manual/core/read-operations-introduction/
    ///
    /// @param filter the filter
    /// @param options optional arguments, see mongo::driver::options::find
    /// @return cursor with the matching documents from the collection
    cursor find(
        bson::document::view filter,
        const options::find& options = options::find()
    );


    /// Finds a single document matching the filter.
    ///
    /// @see http://docs.mongodb.org/manual/core/read-operations-introduction/
    ///
    /// @param filter the filter
    /// @param options optional arguments, see mongo::driver::options::find
    /// @return an optional document that matched the filter
    optional<bson::document::value> find_one(
        bson::document::view filter,
        const options::find& options = options::find()
    );

    /// Finds a single document and deletes it, returning the original.
    ///
    /// @param filter the filter
    /// @param options optional arguments, see mongo::driver::options::find_one_and_delete
    /// @return the document that was deleted
    /// @throws write_exception
    optional<bson::document::value> find_one_and_delete(
        bson::document::view filter,
        const options::find_one_and_delete& options = options::find_one_and_delete()
    );

    /// Finds a single document and replaces it, returning either the original or the replaced
    /// document.
    ///
    /// @param filter the filter
    /// @param replacement the replacement
    /// @param options optional arguments, see mongo::driver::options::find_one_and_replace
    /// @return the original or replaced document
    /// @throws write_exception
    optional<bson::document::value> find_one_and_replace(
        bson::document::view filter,
        bson::document::view replacement,
        const options::find_one_and_replace& options = options::find_one_and_replace()
    );

    /// Finds a single document and updates it, returning either the original or the updated
    /// document.
    ///
    /// @param filter the filter
    /// @param update the update
    /// @param options optional arguments, see mongo::driver::options::find_one_and_update
    /// @return the original or updated document
    /// @throws write_exception
    optional<bson::document::value> find_one_and_update(
        bson::document::view filter,
        bson::document::view update,
        const options::find_one_and_update& options = options::find_one_and_update()
    );

    /// Inserts a single document into the collection. If the document is missing an identifier
    /// one will be generated for it.
    ///
    /// @param document the document to insert
    /// @param options optional arguments, see mongo::driver::options::insert
    /// @return the result of attempting to perform the insert
    /// @throws write_exception
    optional<result::insert_one> insert_one(
        bson::document::view document,
        const options::insert& options = options::insert()
    );

    /// Inserts many documents into the collection. If any of the documents are missing identifiers
    /// the driver will generate them.
    ///
    /// @warning This method uses the bulk insert command to execute the insertion as opposed to
    /// the legacy OP_INSERT wire protocol message. As a result, using this method to insert many
    /// documents on MongoDB < 2.6 will be slow.
    ///
    /// @param container containing documents to insert
    /// @param options optional arguments, see mongo::driver::options::insert
    /// @return the result of attempting to performing the insert
    /// @throws write_exception
    template<class Container>
    inline optional<result::insert_many> insert_many(
        const Container& container,
        const options::insert& options = options::insert()
    );

    /// Inserts many documents into the collection. If any of the documents are missing identifiers
    /// the driver will generate them.
    ///
    /// @warning This method uses the bulk insert command to execute the insertion as opposed to
    /// the legacy OP_INSERT wire protocol message. As a result, using this method to insert many
    /// documents on MongoDB < 2.6 will be slow.
    ///
    /// @param begin iterator pointing to the first document to be inserted
    /// @param end iterator pointing to the end of the documents to be inserted
    /// @param options optional arguments, see mongo::driver::options::insert
    /// @return the result of attempting to performing the insert
    /// @throws write_exception
    ///
    /// TODO: document DocumentViewIterator concept or static assert
    template<class DocumentViewIterator>
    inline optional<result::insert_many> insert_many(
        DocumentViewIterator begin,
        DocumentViewIterator end,
        const options::insert& options = options::insert()
    );

    /// Produces a list of indexes currently on this collection.
    ///
    /// @return cursor yielding the index specifications
    cursor list_indexes() const;

    /// The name of this collection.
    ///
    /// @return the name of the collection
    const std::string& name() const;

    /// Sets the read_preference for the collection. Changes will not have any effect on existing
    /// cursors or other read operations which use the read preference.
    ///
    /// @see http://docs.mongodb.org/manual/core/read-preference/
    ///
    /// @param rp the read_preference to set
    void read_preference(class read_preference rp);

    /// Gets the read_preference for the collection.
    ///
    /// @see http://docs.mongodb.org/manual/core/read-preference/
    ///
    /// @return the current read_preference
    class read_preference read_preference() const;

    /// Replaces a single document.
    ///
    /// @see http://docs.mongodb.org/manual/reference/command/update/
    ///
    /// @param filter document representing the document to be replaced
    /// @param replacement the replacement document
    /// @param options optional arguments, see mongo::driver::options::update
    /// @return the result of attempting to replace a document
    /// @throws write_exception
    optional<result::replace_one> replace_one(
        bson::document::view filter,
        bson::document::view replacement,
        const options::update& options = options::update()
    );

    /// Updates a single document.
    ///
    /// @see http://docs.mongodb.org/manual/reference/command/update/
    ///
    /// @param filter document representing the document to be updated
    /// @param update document representing the update to be applied
    /// @param options optional arguments, see mongo::driver::options::update
    /// @return the result of attempting to update a document
    /// @throws write_exception
    optional<result::update> update_one(
        bson::document::view filter,
        bson::document::view update,
        const options::update& options = options::update()
    );

    /// Updates multiple documents.
    ///
    /// @see http://docs.mongodb.org/manual/reference/command/update/
    ///
    /// @param filter document representing the documents to be updated
    /// @param update document representing the update to be applied
    /// @param options optional arguments, see mongo::driver::options::update
    /// @return the result of attempting to update multiple documents
    /// @throws write_exception
    optional<result::update> update_many(
        bson::document::view filter,
        bson::document::view update,
        const options::update& options = options::update()
    );

    /// Sets the write_concern for the collection. Changes will not have any effect on existing
    /// write operations.
    ///
    /// @param wc the write_concern to set
    void write_concern(class write_concern wc);

    /// Gets the write_concern for the collection.
    ///
    /// @return the current write_concern
    class write_concern write_concern() const;

   private:
    friend class database;

    collection(const database& database, const std::string& collection_name);

    class impl;
    std::unique_ptr<impl> _impl;

}; // class collection

template<class Container>
inline optional<result::bulk_write> collection::bulk_write(
    const Container& requests,
    const options::bulk_write& options
) {
    return bulk_write(requests.begin(), requests.end(), options);
}

template<class WriteModelIterator>
inline optional<result::bulk_write> collection::bulk_write(
    WriteModelIterator begin,
    WriteModelIterator end,
    const options::bulk_write& options
) {
    class bulk_write writes(options.ordered().value_or(true));

    std::for_each(begin, end, [&](const model::write& current){
        writes.append(current);
    });

    return bulk_write(writes);
}

template<class Container>
inline optional<result::insert_many> collection::insert_many(
    const Container& container,
    const options::insert& options
) {
    return insert_many(container.begin(), container.end(), options);
}

template<class DocumentViewIterator>
inline optional<result::insert_many> collection::insert_many(
    DocumentViewIterator begin,
    DocumentViewIterator end,
    const options::insert& options
) {
    class bulk_write writes(false);

    std::map<std::size_t, bson::document::element> inserted_ids{};
    size_t index = 0;
    std::for_each(begin, end, [&](const bson::document::view& current){
        // TODO: put this somewhere else not in header scope (bson::builder)
        if ( !current.has_key("_id")) {
            bson::builder::document new_document;
            new_document << "_id" << bson::oid(bson::oid::init_tag);
            new_document << bson::builder::helpers::concat{current};

            writes.append(model::insert_one(new_document.view()));

            inserted_ids.emplace(index++, new_document.view()["_id"]);
        } else {
            writes.append(model::insert_one(current));

            inserted_ids.emplace(index++, current["_id"]);
        }

    });

    if (options.write_concern())
        writes.write_concern(*options.write_concern());
    result::bulk_write res(std::move(bulk_write(writes).value()));
    optional<result::insert_many> result(result::insert_many(std::move(res), std::move(inserted_ids)));
    return result;
}

}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"
