#include <iostream>

int main() {

    using namespace std;

    std::string name;
    int price, temperature;
    bool hasCashback;

    cout << "Product's name: ";
    cin >> name;
    cout << "Product's price: ";
    cin >> price;
    cout << "Is cash-back available for this product? (true/false) ";
    cin.setf(ios::boolalpha);
    cin >>  hasCashback;
    cout << "Maximum storing temperature: ";
    cin >> temperature;

    return 0;
}