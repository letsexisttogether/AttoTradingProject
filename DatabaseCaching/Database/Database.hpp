#pragma once

#include <string>

class i_db
{
public:
    virtual ~i_db() = default;

    virtual bool begin_transaction() = 0;
    virtual bool commit_transaction() = 0;
    virtual bool abort_transaction() = 0;

    virtual std::string get(const std::string& key) = 0;
    virtual std::string set(const std::string& key,
        const std::string& data) = 0;
    virtual std::string remove(const std::string& key) = 0;
};
