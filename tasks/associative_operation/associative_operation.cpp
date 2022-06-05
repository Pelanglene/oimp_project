#include "associative_operation.h"

bool IsAssociative(const std::vector<std::vector<size_t>>& table) {
    size_t table_size = table.size();
    for (size_t i = 0; i < table_size; ++i){
        for (size_t j = 0; j < table_size; ++j){
            for (size_t k = 0; k < table_size; ++k){
                if (table[table[i][j]][k] != table[i][table[j][k]]) {
                    return false;
                }
            }
        }
    }
    return true;
}

