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

#include "driver/base/database.hpp"
#include "driver/base/read_preference.hpp"
#include "driver/base/uri.hpp"
#include "driver/base/write_concern.hpp"
#include "driver/options/client.hpp"

namespace mongo {
namespace driver {

/// The client class is the entry point into the MongoDB driver. It acts as a logical gateway for
/// accessing the databases of MongoDB clusters. Databases that are accessed via a client inherit
/// all of the options specified on the client via a copy upon instantiation. The client MUST be
/// kept around during the lifetime of all subordinate objects (collections, databases, cursors...)
class LIBMONGOCXX_EXPORT client {

    // TODO: iterable for databases on the server
    // TODO: add + implement client api methods
   public:
    /// Create a new connection to MongoDB. An instance of this class must remain while
    /// subobjects like database and collections are in use. It is the responsability of the
    /// driver user to keep the client around for the lifetime of the connections and while the
    /// various subojects are in use.
    ///
    /// @param mongodb_uri a MongoDB URI representing the connection parameters
    /// @param options additional options that cannot be specefied via the mongodb_uri
    client(
        const uri& mongodb_uri = uri(),
        const options::client& options = options::client()
    );

    client(client&& rhs) noexcept;
    client& operator=(client&& rhs) noexcept;

    ~client();

    /// Sets the read_preference for this client.
    ///
    /// @note Modifications at this level do not effect existing databases or collection instances
    /// that have come from this client but do effect new ones as databases will receive a copy of
    /// the read_preference of this client upon instantiation.
    ///
    /// @see http://docs.mongodb.org/manual/core/read-preference/
    ///
    /// @param rp the new read_preference
    void read_preference(class read_preference rp);

    /// The current read preference for this client.
    ///
    /// @see http://docs.mongodb.org/manual/core/read-preference/
    ///
    /// @return the current read_preference
    class read_preference read_preference() const;

    /// Sets the write_concern for this client.
    ///
    /// @note Modifications at this level do not effect existing databases or collection instances
    /// that have come from this client but do effect new ones as databases will receive a copy of
    /// the write_concern of this client upon instantiation.
    ///
    /// @param wc the new write concern
    void write_concern(class write_concern wc);

    /// The current write_concern for this client.
    ///
    /// @return the current write_concern
    class write_concern write_concern() const;

    /// Access to a particular database (logical grouping of collections)
    ///
    /// @param name the name of the database to get
    /// @return the database
    class database database(const std::string& name) const &;
    class database database(const std::string& name) const && = delete;


    /// Syntactic sugar for accessing a database.
    ///
    /// @param name the name of the database to get
    /// @return the database
    inline class database operator[](const std::string& name) const &;
    inline class database operator[](const std::string& name) const && = delete;

   private:
    friend class database;
    friend class collection;

    class impl;
    std::unique_ptr<impl> _impl;

}; // class client

inline class database client::operator[](const std::string& name) const & {
    return database(name);
}

}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"
