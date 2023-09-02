#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <vector>
#include <string>
#include "LRUCache.hpp"

struct ProductDetails {
    int productId;
    std::string productName;
    std::string description;
    std::vector<uint8_t> image;
    std::vector<std::string> comments;

    ProductDetails(
        int id, std::string name
    ) : productId(id), productName(name), description("description"), image({}), comments({}) {}
};

class Database {
private:
    size_t size;
    std::vector<ProductDetails*> data;
    std::unique_ptr<LRUCache<int, ProductDetails>> cache;

    inline ProductDetails* fetchFromDatabase(int id) {
        auto it = std::find_if(data.begin(), data.end(), [id](const auto& details) {
            return details->productId == id;
        });
        return *it;
    }

public:
    Database(size_t size,  std::unique_ptr<LRUCache<int, ProductDetails>> cache): size(size), cache(std::move(cache)) {}

    inline ProductDetails* fetchProductDetails(int id) {
        bool inCache = false;
        ProductDetails* product = cache->retrieve(id, inCache);
        
        if (inCache) {
            std::cout << id << ": in cache!\n";
            return product;
        } else {
            std::cout << id << ": cache miss..\n";
            product = fetchFromDatabase(id);
            cache->insert(id, product);
        }

        return product;
    };

    void generateDummyData() {
        for (size_t i = 0; i < size; i++) {
            ProductDetails* product = new ProductDetails(i, "name-" + std::to_string(i));
            data.push_back(product);
        }
    }

    void displayCache() {
        cache->display();
    };

};

#endif