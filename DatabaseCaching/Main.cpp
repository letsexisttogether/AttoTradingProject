#include <iostream>
#include <memory>

#include "Cache/Cache.hpp"
#include "Cache/Sizable/SizableCache.hpp"
#include "Database/Cache/DatabaseCacher.hpp"
#include "Database/Database.hpp"
#include "Database/Decoy/DecoyDatabase.hpp"

std::int32_t main(std::int32_t argc, char** argv)
{
    std::unique_ptr<i_db> initialDatabase{ new DecoyDatabase{} };

    std::unique_ptr<i_db> database
    { 
        new DatabaseCacher
        { 
            initialDatabase.get(), new SizableCache{ 1000, 2000 }
        }
    };

    if (database->begin_transaction())
    {
        database->remove("SomeKey");

        database->set("Name", "Alex");
        database->set("Surname", "Chernenko");
        database->set("Requrest", "SubmitTestTask");
        database->set("SuperSecretKey", "1231312321312");

        std::cout << "And the secret key is ... "
            << database->get("SuperSecretKey") << std::endl;

        database->commit_transaction();
    }

    std::cout << "FullName: " << database->get("Name") << ' '
        << database->get("Surname") << std::endl;


    return EXIT_SUCCESS;
}
