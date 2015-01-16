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
#include <string>
#include <memory>

#include "bson/document.hpp"

namespace mongo {
namespace driver {

class collection;

/// Class representing a MongoDB aggregation pipeline
class LIBMONGOCXX_EXPORT pipeline {

   public:
    /// Creates a new aggregation pipeline.
    ///
    /// @see http://docs.mongodb.org/manual/core/aggregation-pipeline/
    pipeline();

    pipeline(pipeline&& other) noexcept;
    pipeline& operator=(pipeline&& rhs) noexcept;

    ~pipeline();

    /// Groups documents by some specified expression and outputs to the next stage a
    /// document for each distinct grouping. The output documents contain an _id field
    /// which contains the the distinct key for that group. The output documents can also
    /// contain computed fields that hold the values of some accumulator expression grouped
    /// by the group's _id field.
    ///
    /// @note group does not order output documents
    /// @see http://docs.mongodb.org/manual/reference/operator/aggregation/group/#pipe._S_group
    ///
    /// @param group the group expression as a document
    pipeline& group(bson::document::view group);

    /// Limits the number of documents passed to the next stage in the pipeline.
    ///
    /// @see http://docs.mongodb.org/manual/reference/operator/aggregation/limit/#pipe._S_limit
    ///
    /// @param limit the limit
    pipeline& limit(std::int32_t limit);

    /// Filters the documents to pass only the documents that match the specified condition(s) to
    /// the next pipeline stage.
    ///
    /// @see http://docs.mongodb.org/manual/reference/operator/aggregation/match/#pipe._S_match
    ///
    /// @param filter the filter
    pipeline& match(bson::document::view filter);

    /// Takes documents returned by the aggregation pipeline and writes them to a specified
    /// collection. This stage must be the last stage in the pipeline. The out operator lets the
    /// aggregation framework return result sets of any size.
    ///
    /// @see http://docs.mongodb.org/manual/reference/operator/aggregation/out/#pipe._S_out
    ///
    /// @param collection_name the name of the collection where the output documents should go
    pipeline& out(std::string collection_name);

    /// Projects a subset of the fields in the documents to the next stage of the pipeline.
    ///
    /// @see http://docs.mongodb.org/manual/reference/operator/aggregation/project/#pipe._S_project
    ///
    /// @param projection projection specification
    pipeline& project(bson::document::view projection);

    /// Restricts the contents of the documents based on information stored in the documents
    /// themselves.
    ///
    /// @see http://docs.mongodb.org/manual/reference/operator/aggregation/redact/#pipe._S_redact
    ///
    /// @param restrictions the document restrictions
    pipeline& redact(bson::document::view restrictions);

    /// Skips over the specified number of documents that pass into the stage and passes the
    /// remaining documents to the next stage in the pipeline.
    ///
    /// @see http://docs.mongodb.org/manual/reference/operator/aggregation/skip/#pipe._S_skip
    ///
    /// @param skip the number of documents to skip
    pipeline& skip(std::int32_t skip);

    /// Sorts all input documents and returns them to the pipeline in sorted order.
    ///
    /// @see http://docs.mongodb.org/manual/reference/operator/aggregation/sort/#pipe._S_sort
    ///
    /// @param ordering document specifying the ordering in which the documents are to be sorted
    pipeline& sort(bson::document::view ordering);

    /// Deconstructs an array field from the input documents to output a document for each element.
    /// Each output document is the input docuemnts with the value of the array field replaced by
    /// the element which was unwound.
    ///
    /// @see http://docs.mongodb.org/manual/reference/operator/aggregation/unwind/#pipe._S_unwind
    ///
    /// @param field_name the name of the field to unwind
    pipeline& unwind(std::string field_name);

   private:
    friend class collection;

    class impl;
    std::unique_ptr<impl> _impl;

}; // class pipeline

}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"
