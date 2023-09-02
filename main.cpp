#include "LRUCache.hpp"
#include <vector>
#include <string>
#include <memory>
#include "Database.hpp"

constexpr size_t CacheSize = 10;
constexpr size_t DatabaseSize = 1000;

using ECommerceCache = LRUCache<int, ProductDetails>;

int main() {
    std::unique_ptr<ECommerceCache> cache = std::make_unique<ECommerceCache>(CacheSize);
    std::unique_ptr<Database> db = std::make_unique<Database>(DatabaseSize, std::move(cache));

    db->generateDummyData();
    db->displayCache();
    
    db->fetchProductDetails(5);
    db->displayCache();

    db->fetchProductDetails(6);
    db->fetchProductDetails(24);
    db->fetchProductDetails(88);
    db->fetchProductDetails(39);

    db->displayCache();
    db->fetchProductDetails(6);
    db->displayCache();

    db->fetchProductDetails(95);
    db->fetchProductDetails(100);
    db->fetchProductDetails(500);
    db->fetchProductDetails(670);
    db->fetchProductDetails(999);

    db->displayCache();

    db->fetchProductDetails(999);
    db->fetchProductDetails(999);
    db->fetchProductDetails(999);

    db->displayCache();

    db->fetchProductDetails(6);
    db->fetchProductDetails(2);
    db->fetchProductDetails(5);
    db->fetchProductDetails(500);
    db->fetchProductDetails(460);

    db->displayCache();
    
    return 0;
}