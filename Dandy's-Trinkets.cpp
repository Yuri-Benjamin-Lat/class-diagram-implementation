#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <limits>
using namespace std;

class Product 
{
public:
    string productId;
    string productName;
    double productPrice;    

    Product() : productId(""), productName(""), productPrice(0.0) {}
    Product(string id, string n, double p) : productId(id), productName(n), productPrice(p) {}

    void getProductDetails() const 
    {
        cout << "   " << productId << "  " << setw(20) << productName << setw(9) << productPrice << " Tapes" << endl;
    }
};

class ShoppingCart 
{
private:
    vector<pair<Product, int>> cart;

public:
    void addProduct(const Product& product, int quantity) 
    {
        for (auto& item : cart) 
        {
            if (item.first.productId == product.productId) 
            {
                item.second += quantity;
                cout << "Product quantity updated successfully!" << endl;
                return;
            }
        }
        
        cart.push_back(make_pair(product, quantity));
        cout << "Product added successfully!" << endl;
    }

    void displayCart(int currentOrderId) const 
    {
        if (cart.empty()) 
        {
            cout << "                Shopping cart is empty!" << endl;
            return;
        }
        
        double totalAmount = 0.0;
        
        cout << "Order ID: #" << currentOrderId << endl;
        cout << "Product ID" << setw(15) << "Name" << setw(16) << "Price" << setw(10) << "Quantity" << endl;
        
        for (const auto& item : cart) 
        {
            const Product& product = item.first;
            int quantity = item.second;
            double itemTotal = product.productPrice * quantity;
            totalAmount += itemTotal;
            cout << "   " << product.productId << "   " << setw(20) << product.productName
                 << setw(11) << product.productPrice << setw(8) << quantity << endl;
        }
        
        cout << "====================================================" << endl;
        cout << "Total Amount: " << fixed << setprecision(2) << totalAmount << " Tapes" << endl;
    }
    
    vector<pair<Product, int>> getCartItems() const 
    {
        return cart;
    }
    
     void clearCart() 
    {
        cart.clear();
    }
};

class Order 
{
public:
    int orderId;
    double totalAmount;
    vector<pair<Product, int>> items;

    Order(int id, double amount, const vector<pair<Product, int>>& cartItems)
        : orderId(id), totalAmount(amount), items(cartItems) {}

    void displayOrder() const 
    {
        cout << "\nOrder ID: " << orderId << endl;
        cout << "Total Amount: " << fixed << setprecision(2) << totalAmount << " Tapes" << endl;
        cout << "Order Details:" << endl;
        cout << "Product ID" << setw(15) << "Name" << setw(16) << "Price" << setw(10) << "Quantity" << endl;
        for (const auto& item : items) 
        {
            const Product& product = item.first;
            int quantity = item.second;
            
            cout << "   " << product.productId << "   " << setw(20) << product.productName
                 << setw(11) << product.productPrice << setw(8) << quantity << endl;
        }
        cout << "=====================================================" << endl;
    }
};

// Return/Continue prompt after viewing specific sections
void waitForKeyPress() 
{
    cout << "\nPress enter to continue..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Non-case sensitizing for user-friendliness
string toUpperCase(string str) 
{
    for (char& c : str) 
    {
        c = toupper(c);
    }
    return str;
}

// Generic function for Y/N prompts
char getYesNoResponse(const string& prompt) 
{
    char response;
    while (true) 
    {
        cout << prompt;
        cin >> response;
        response = toupper(response);
        if (response == 'Y' || response == 'N') 
        {
            return response;
        }
        cout << "Invalid input! Please enter Y or N." << endl;
    }
}

// Anti-error and loop
int getMenuChoice() 
{
    int choice;
    while (true) 
    {
        cout << ": ";
        if (cin >> choice) 
        {
            if (choice >= 1 && choice <= 4) 
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return choice;
            } else 
            {
                cout << "Invalid choice! Please enter a number between 1 and 4." << endl;
            }
        } else 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number (1-4)." << endl;
        }
    }
}

// Allowing only specific integers
int getQuantity() 
{
    int quantity;
    while (true) 
    {
        cout << "Enter the quantity of the product you want to add: ";
        if (cin >> quantity) 
        {
            if (quantity > 0) 
            { 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return quantity;
            } else 
            {
                cout << "Quantity must be greater than zero! Please enter a valid quantity." << endl;
            }
        } else 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid integer for quantity." << endl;
        }
    }
}

int main() 
{
    vector<Product> products = 
    {   
        Product("A123", "Sweet Charm", 100),
        Product("B234", "Dog Plush", 125),
        Product("C345", "Magnifying Glass", 150),
        Product("D456", "Friendship Bracelet", 175),
        Product("E567", "Crayon Set", 200),
        Product("F678", "Diary", 225),
        Product("G789", "Night Cap", 250),
        Product("H890", "Vee's Remote", 275),    
        Product("I901", "Savory Charm", 300),
        Product("J110", "Dandy's Plush", 325)
    };

    vector<Order> orders;
    ShoppingCart cart;
    int choice;
    bool condition = true;
    char addMore;
    string productId;
    int quantity;
    int orderId = 1;
    
    cout << "==================================";
    cout << "\nWelcome to Dandy's trinket store!!";
    cout << "\n==================================";
    
    while(condition) 
    {
        cout << "\n\n             ~ Menu ~";
        cout << "\n\n1. View Products";
        cout << "\n2. View Shopping Cart";
        cout << "\n3. View Orders";
        cout << "\n4. Exit\n\n";

        choice = getMenuChoice();
        
        system("cls");
        
        switch(choice) 
        {
            case 1:
                cout << "============================================";
                cout << "\n           ~ Available trinkets ~";
                cout << "\n============================================\n\n";
                
                cout << "Product ID" << setw(14) << "Name" << setw(18) << "Price" << endl;
                
                for (const auto& product : products) 
                {
                    product.getProductDetails();
                }

                do 
                {
                    cout << "\n    Enter the ID of the product you want \n        to add to the shopping cart. \n\nID: ";
                    cin >> productId;

                    productId = toUpperCase(productId);

                    bool found = false;
                    for (const auto& product : products) 
                    {
                        if (toUpperCase(product.productId) == productId) 
                        {
                            quantity = getQuantity();
                            cart.addProduct(product, quantity);
                            found = true;
                            break;
                        }
                    }

                    if (!found) 
                    {
                        cout << "Product not found!" << endl;
                    }

                    addMore = getYesNoResponse("Do you want to add another product? (Y/N): ");
                } while (addMore == 'Y');

                system("cls");
                
                break;

            case 2:
                cout << "====================================================";
                cout << "\n                   ~ Shopping Cart ~";
                cout << "\n====================================================\n\n";
                
                cart.displayCart(orderId);

                if (!cart.getCartItems().empty()) 
                {
                    char checkoutResponse = getYesNoResponse("\nDo you want to check out all the products? (Y/N): ");
                    if (checkoutResponse == 'Y') 
                    {
                        double totalAmount = 0.0;
                        vector<pair<Product, int>> cartItems = cart.getCartItems();

                        for (const auto& item : cartItems) 
                        {
                            totalAmount += item.first.productPrice * item.second;
                        }

                        orders.push_back(Order(orderId, totalAmount, cartItems));
                        orderId++;
                        
                        cart.clearCart();

                        cout << "Checkout successful! Order has been placed.\n\n";
                    }
                }

                waitForKeyPress();
                system("cls");
                
                break;

            case 3:
                cout << "=====================================================";
                cout << "\n                    ~ All Orders ~";
                cout << "\n=====================================================\n";
                
                if (orders.empty()) 
                {
                    cout << "                 No orders have been placed yet.\n";
                } else 
                {
                    for (const auto& order : orders) 
                    {
                        order.displayOrder();
                    }
                }
    
                waitForKeyPress();
                system("cls");
                
                break;

            case 4:
            	cout << "=====================================================";
                cout << "\n    Thank you for visiting Dandy's trinket store!";
                cout << "\n=====================================================\n";
                condition = false;
                break;

            default:
                cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
