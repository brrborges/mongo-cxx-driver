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

#include <memory>
#include <string>

#include "driver/base/collection.hpp"
#include "driver/base/write_concern.hpp"
#include "driver/base/read_preference.hpp"

namespace mongo {
namespace driver {

class client;

/// The database class serves as a representation of a MongoDB database. It acts as a gateway
/// for accessing collections that are contained within the particular database that an instance
/// of the class represents. It inherits all of its default settings from the client that calls
/// it's constructor.
class LIBMONGOCXX_EXPORT database {

    // TODO: iterable for collections in the database
    // TODO: make copyable when c-driver supports this
    // TODO: add auth functions (add_user, remove_all_users, remove_user)
   public:
    database(database&& other) noexcept;
    database& operator=(database&& rhs) noexcept;

    ~database();

    /// Runs a command against this database.
    ///
    /// @see http://docs.mongodb.org/manual/reference/method/db.runCommand/
    ///
    /// @param command document representing the command to be run
    /// @return the result of executing the command
    /// @throws operation_exception
    bson::document::value command(bson::document::view command);

    /// Explicitly creates a collection with specified options.
    ///
    /// @see http://docs.mongodb.org/manual/reference/method/db.createCollection/
    ///
    /// @param name the new collection's name
    /// @param options the options for the new collection
    class collection create_collection(const std::string& name, bson::document::view options);

    /// Drops the database.
    ///
    /// @see http://docs.mongodb.org/manual/reference/method/db.dropDatabase/
    void drop();

    /// Checks whether this database contains a collection having name.
    ///
    /// @param name the name of the collection
    /// @return bool whether the collection exists in this database
    bool has_collection(const std::string& name);

    /// Enumerates the collections of this database.
    ///
    /// @return mongo::driver::cursor containing the collection information
    cursor list_collections();

    /// Get the name of this database.
    ///
    /// @return the name of this database.
    const std::string& name() const;

    // TODO: should this be called move?
    void rename(
        const std::string& new_name,
        bool drop_target_before_rename
    );

    bson::document::value stats();

    /// Sets the read_preference for this database.
    ///
    /// @note Modifications at this level do not effect existing collection instances that have come
    /// from this database but do effect new ones as new collections will receive a copy of the
    /// read_preference of this database upon instantiation.
    ///
    /// @see http://docs.mongodb.org/manual/core/read-preference/
    ///
    /// @param rp the new read_preference
    void read_preference(class read_preference rp);

    /// The current read preference for this database.
    ///
    /// @see http://docs.mongodb.org/manual/core/read-preference/
    ///
    /// @return the current read_preference
    class read_preference read_preference() const;

    /// Sets the write_concern for this database.
    ///
    /// @note Modifications at this level do not effect existing collection instances that have come
    /// from this database but do effect new ones as new collections will receive a copy of the
    /// write_concern of this client upon instantiation.
    void write_concern(class write_concern wc);

    /// The current write_concern for this database.
    ///
    /// @return the current write_concern
    class write_concern write_concern() const;

    /// Access a collection (logical grouping of documents)
    ///
    /// @param name the name of the collection to get
    /// @return the collection
    class collection collection(const std::string& name) const;

    /// Syntactic sugar for accessing a collection.
    ///
    /// @param name the name of the collection to get
    /// @return the collection
    inline class collection operator[](const std::string& name) const;

   private:
    friend class client;
    friend class collection;

    database(const class client& client, const std::string& name);

    class impl;
    std::unique_ptr<impl> _impl;

}; // class database

inline collection database::operator[](const std::string& name) const {
    return collection(name);
}

}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"
