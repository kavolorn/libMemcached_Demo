#include <iostream>
#include "memcached.hpp"

using namespace std;

int main(int argc, char ** argv)
{
    const char * config_string = "--SERVER=127.0.0.1";
    memcached_st * memc = memcached(config_string, strlen(config_string));

    const char *key = "foo";
    const char *value = "value";

    memcached_return_t rc = memcached_set(memc, key, strlen(key), value, strlen(value), (time_t)0, (uint32_t)0);

    if (rc != MEMCACHED_SUCCESS)
    {
        cerr << "Memcached storing error.";
    }
    else
    {
        cout << "Value has been written correctly.";
    }
    
    memcached_free(memc);
    return 0;
}