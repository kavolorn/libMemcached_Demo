#include <iostream>
#include "memcached.hpp"

using namespace std;

int main(int argc, char ** argv)
{
    const char * config_string = "--SERVER=127.0.0.1";
    memcached_st * memc = memcached(config_string, strlen(config_string));

    // Storing key value in memcached system
    
    const char *key = "foo";
    const char *value = "value";

    memcached_return_t rc = memcached_set(memc, key, strlen(key), value, strlen(value), (time_t)0, (uint32_t)0);

    if (rc != MEMCACHED_SUCCESS)
    {
        cerr << "Memcached storing error.\n";
        return 1;
    }
    else
    {
        cout << "Value has been written correctly.\n";
    }
    
    // Getting back stored value
    
    size_t value_length;
    uint32_t flags;
    memcached_return_t error;
    
    char * return_value = memcached_get(memc, key, strlen(key), &value_length, &flags, &error);
    
    if (error != MEMCACHED_SUCCESS)
    {
        cerr << "Memcached reading error.\n";
        return 1;
    }
    else
    {
        cout << return_value << endl;
    }
    
    memcached_free(memc);
    return 0;
}