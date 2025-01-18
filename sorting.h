#include <string>

void BubbleSort(int quantities[], std::string items[], float prices[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (quantities[j] > quantities[j + 1]) {
                // Swap quantities
                int tempQty = quantities[j];
                quantities[j] = quantities[j + 1];
                quantities[j + 1] = tempQty;

                // Swap items
                std::string tempItem = items[j];
                items[j] = items[j + 1];
                items[j + 1] = tempItem;

                // Swap prices
                float tempPrice = prices[j];
                prices[j] = prices[j + 1];
                prices[j + 1] = tempPrice;
            }
        }
    }
}