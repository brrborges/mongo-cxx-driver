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

#include "driver/base/write_concern.hpp"
#include "driver/model/write.hpp"
#include "stdx/optional.hpp"

namespace mongo {
namespace driver {

class collection;

/// A bulk_write represents a batch of writes to be sent to the server at the same time.
class LIBMONGOCXX_EXPORT bulk_write {

   public:
    /// Initialize a new Bulk Operation to be executed against a mongo::driver::collection.
    //
    /// @param ordered If true all operations will be executed serially in the order provided.
    /// and the entire bulk operation will abort on the first error. If false operations will be
    /// executed in arbitrary order (possibly in parallel on the server) and any errors will be
    /// reported after attempting all operations.
    explicit bulk_write(bool ordered);

    bulk_write(bulk_write&& other) noexcept;
    bulk_write& operator=(bulk_write&& rhs) noexcept;

    ~bulk_write();

    void append(const model::write& operation);

    void write_concern(class write_concern wc);
    /*
     * Uncomment and implement when c-driver provides this functionality
     * class write_concern write_concern() const;
     */

   private:
    friend class collection;

    class impl;
    std::unique_ptr<impl> _impl;

}; // class bulk_write

}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"
