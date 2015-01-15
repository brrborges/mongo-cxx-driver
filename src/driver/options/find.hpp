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

#include <cstdint>

#include "bson/document.hpp"
#include "driver/base/read_preference.hpp"
#include "stdx/optional.hpp"

namespace mongo {
namespace driver {
namespace options {

/// Class representing the optional arguments to a MongoDB query
class LIBMONGOCXX_EXPORT find {

   public:
    enum class cursor_type: std::uint8_t;

    /// Sets whether to allow partial results from a mongos if some shards are down (instead of
    /// throwing an error).
    ///
    /// @see http://docs.mongodb.org/meta-driver/latest/legacy/mongodb-wire-protocol/#op-query
    ///
    /// @param allow_partial whether to allow partial results from mongos
    void allow_partial_results(bool allow_partial);

    /// Gets the current setting for allowing partial results from mongos.
    ///
    /// @see http://docs.mongodb.org/meta-driver/latest/legacy/mongodb-wire-protocol/#op-query
    ///
    /// @return whether or not we allow partial results from mongos
    const optional<bool>& allow_partial_results() const;

    /// Sets the number of documents to return per batch.
    ///
    /// @see http://docs.mongodb.org/manual/reference/method/cursor.batchSize/
    ///
    /// @param batch_size the size of the batches to request
    void batch_size(std::int32_t batch_size);

    /// The current batch size setting.
    ///
    /// @see http://docs.mongodb.org/manual/reference/method/cursor.batchSize/
    ///
    /// @return the current batch size
    const optional<std::int32_t>& batch_size() const;

    /// Attaches a comment to the query. If $comment also exists in the modifiers document then
    /// the comment field overwrites $comment.
    ///
    /// @see http://docs.mongodb.org/manual/reference/operator/meta/comment/
    ///
    /// @param comment the comment to attach to this query
    void comment(std::string comment);

    /// Gets the current comment attached to this query.
    ///
    /// @see http://docs.mongodb.org/manual/reference/operator/meta/comment/
    ///
    /// @return the comment attached to this query
    const optional<std::string>& comment() const;

    /// Indicates the type of cursor to use for this query.
    ///
    /// @see http://docs.mongodb.org/meta-driver/latest/legacy/mongodb-wire-protocol/#op-query
    ///
    /// @param cursor_type the cursor type to set
    void cursor_type(cursor_type cursor_type);

    /// Gets the current cursor type.
    ///
    /// @see http://docs.mongodb.org/meta-driver/latest/legacy/mongodb-wire-protocol/#op-query
    ///
    /// @return the current cursor type
    const optional<enum cursor_type>& cursor_type() const;

    /// Sets maximum number of documents to return.
    ///
    /// @param limit the max number of documents to return
    void limit(std::int32_t limit);

    /// Gets the current limit.
    ///
    /// @return the current limit
    const optional<std::int32_t>& limit() const;

    /// Sets the maximum amount of time for this operation to run (server side) in milliseconds.
    ///
    /// @see http://docs.mongodb.org/manual/reference/operator/meta/maxTimeMS
    ///
    /// @param max_time_ms the max amount of time (in milliseconds)
    void max_time_ms(std::int64_t max_time_ms);

    /// The current max_time_ms setting.
    ///
    /// @see http://docs.mongodb.org/manual/reference/operator/meta/maxTimeMS
    ///
    /// @return the current max time (in milliseconds)
    const optional<std::int64_t>& max_time_ms() const;

    /// Sets the meta-operators modifying the output or behavior of the query.
    ///
    /// @see http://docs.mongodb.org/manual/reference/operator/query-modifier/
    ///
    /// @param modifiers the query modifiers
    void modifiers(bson::document::view modifiers);

    /// Gets the current query modifiers.
    ///
    /// @return the current query modifiers
    const optional<bson::document::view>& modifiers() const;

    /// Sets the cursor flag to prevent cursor from timing out server side due to a period of
    /// inactivity.
    ///
    /// @see http://docs.mongodb.org/meta-driver/latest/legacy/mongodb-wire-protocol/#op-query
    ///
    /// @param no_cursor_timeout when true prevents the cursor from timing out
    void no_cursor_timeout(bool no_cursor_timeout);

    /// Gets the current no cursor timeout setting.
    ///
    /// @see http://docs.mongodb.org/meta-driver/latest/legacy/mongodb-wire-protocol/#op-query
    ///
    /// @return the current no cursor timeout setting
    const optional<bool>& no_cursor_timeout() const;

    void oplog_replay(bool oplog_replay);
    const optional<bool>& oplog_replay() const;

    /// Sets a projection which limits the fields to return for all matching documents.
    ///
    /// @see http://docs.mongodb.org/manual/tutorial/project-fields-from-query-results/
    ///
    /// @param projection the projection document
    void projection(bson::document::view projection);

    /// Gets the current projection.
    ///
    /// @see http://docs.mongodb.org/manual/tutorial/project-fields-from-query-results/
    ///
    /// @return the current projection
    const optional<bson::document::view>& projection() const;

    /// Sets the read_preference for this operation.
    ///
    /// @see http://docs.mongodb.org/manual/core/read-preference/
    ///
    /// @param rp the new read_preference
    void read_preference(read_preference rp);

    /// The current read_preference for this operation.
    ///
    /// @see http://docs.mongodb.org/manual/core/read-preference/
    ///
    /// @return the current read_preference
    const optional<class read_preference>& read_preference() const;

    /// Sets the number of documents to skip before returning results.
    ///
    /// @see http://docs.mongodb.org/manual/reference/method/cursor.skip/
    ///
    /// @param skip the number of documents to skip
    void skip(std::int32_t skip);

    /// Gets the current number of documents to skip.
    ///
    /// @see http://docs.mongodb.org/manual/reference/method/cursor.skip/
    ///
    /// @return the number of documents to skip
    const optional<std::int32_t>& skip() const;

    /// The order in which to return matching documents. If $orderby also exists in the modifiers
    /// document, the sort field overwrites $orderby.
    ///
    /// @see http://docs.mongodb.org/manual/reference/method/cursor.sort/
    ///
    /// @param ordering document describing the order of the documents to be returned
    void sort(bson::document::view ordering);

    /// Gets the current sort ordering.
    ///
    /// @see http://docs.mongodb.org/manual/reference/method/cursor.sort/
    ///
    /// @return the current sort ordering
    const optional<bson::document::view>& sort() const;

   private:
    optional<bool> _allow_partial_results;
    optional<std::int32_t> _batch_size;
    optional<std::string> _comment;
    optional<enum cursor_type> _cursor_type;
    optional<std::int32_t> _limit;
    optional<std::int64_t> _max_time_ms;
    optional<bson::document::view> _modifiers;
    optional<bool> _no_cursor_timeout;
    optional<bool> _oplog_replay;
    optional<bson::document::view> _projection;
    optional<class read_preference> _read_preference;
    optional<std::int32_t> _skip;
    optional<bson::document::view> _ordering;

}; // class find

}  // namespace options
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"
