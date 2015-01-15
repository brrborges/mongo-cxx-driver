
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

#include "bson/document.hpp"
#include "driver/base/write_concern.hpp"
#include "stdx/optional.hpp"

namespace mongo {
namespace driver {
namespace options {

/// Class representing the optional arguments to a MongoDB update operation
class LIBMONGOCXX_EXPORT update {

   public:
    void upsert(bool upsert);
    const optional<bool>& upsert() const;

    /// Sets the write_concern for this operation.
    ///
    /// @see http://docs.mongodb.org/manual/core/write-concern/
    ///
    /// @param wc the new write_concern
    void write_concern(class write_concern wc);

    /// The current write_concern for this operation.
    ///
    /// @see http://docs.mongodb.org/manual/core/write-concern/
    ///
    /// @return the current write_concern
    const optional<class write_concern>& write_concern() const;

   private:
    optional<bool> _upsert;
    optional<class write_concern> _write_concern;

}; // class update

}  // namespace options
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"
