#include <iostream>
#include <ctime>
#include "memcached.hpp"

using namespace std;

int main(int argc, char ** argv)
{
    const char * config_string = "--SERVER=127.0.0.1 --BINARY-PROTOCOL";
    memcached_st * memc = memcached(config_string, strlen(config_string));

    // Storing key value in memcached system
    
    const char * key = "foo";
    const char * value = "bar";

    memcached_return_t rc = memcached_set(memc, key, strlen(key), value, strlen(value), 0, 0);

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
    
    char * return_value = memcached_get(memc, key, strlen(key), &value_length, &flags, &rc);
    
    if (rc != MEMCACHED_SUCCESS)
    {
        cerr << "Memcached reading error.\n";
        return 1;
    }
    else
    {
        cout << return_value << endl;
    }
    
    // Working with increment
    
    const char * inc_key = "var1";
    uint64_t inc_variable = 0;
    
    time_t now = time( NULL);
    struct tm now_tm = *localtime(&now);
    struct tm then_tm = now_tm;
    then_tm.tm_sec += 10;
    
    rc = memcached_increment_with_initial(memc, inc_key, strlen(inc_key), 1, 1, mktime(&then_tm), &inc_variable);
    
    if (rc != MEMCACHED_SUCCESS)
    {
        cerr << "Memcached increment error.\n" << memcached_strerror(memc, rc) << endl;
        return 1;
    }
    else
    {
        cout << "Value has been incremented correctly.\n";
    }
    
    cout << inc_variable << endl;
    
    memcached_free(memc);
    return 0;
}