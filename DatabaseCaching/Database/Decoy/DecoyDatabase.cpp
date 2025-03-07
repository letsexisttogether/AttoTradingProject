#include "DecoyDatabase.hpp"

#include <iostream>

bool DecoyDatabase::begin_transaction()
{
    std::cout << "The transaction begun..." << std::endl;

    return true;
}

bool DecoyDatabase::commit_transaction()
{
    std::cout << "The transaction is commited..." << std::endl;

    return true;
}

bool DecoyDatabase::abort_transaction()
{
    std::cout << "The transaction was aborted..." << std::endl;

    return true;
}

std::string DecoyDatabase::get(const std::string& key)
{
    if (key == "SuperSecretKey")
    {
        return "Can't tell secrets here";
    }

    return "Some decoy data for " + key;
}

std::string DecoyDatabase::set(const std::string& key,
    const std::string& data)
{
    return key;
}

std::string DecoyDatabase::remove(const std::string& key)
{
    return key; 
}
