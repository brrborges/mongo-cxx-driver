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
#include "driver/base/write_concern.hpp"
#include "stdx/optional.hpp"

namespace mongo {
namespace driver {
namespace options {

/// Class representing the optional arguments to a MongoDB find_and_modify delete operation
class LIBMONGOCXX_EXPORT find_one_and_delete {

   public:
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

    /// Sets a projection which limits the fields to return.
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

    /// Sets the order to search for a matching document.
    ///
    /// @warning This can influence which document the operation modifies if the provided filter
    /// selects multiple documents.
    ///
    /// @see http://docs.mongodb.org/manual/reference/method/db.collection.findAndModify/
    ///
    /// @param ordering document describing the order of the documents to be returned
    void sort(bson::document::view ordering);

    /// Gets the current sort ordering.
    ///
    /// @see http://docs.mongodb.org/manual/reference/method/db.collection.findAndModify/
    ///
    /// @return the current sort ordering
    const optional<bson::document::view>& sort() const;

   private:
    optional<std::int64_t> _max_time_ms;
    optional<bson::document::view> _projection;
    optional<bson::document::view> _ordering;

}; // class find_one_and_delete

}  // namespace options
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"
