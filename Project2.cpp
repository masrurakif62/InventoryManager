//==========================================================
//
// Title:      Project #2
// Course:     CSC 1100
// Author:     Masrur Akif
// Date:       December 17, 2020
// Description:
//   This C++ console application searches a product 
// inventory.  It reads the data from file 
// SnowShepherdsInventory.txt and stores the data in an 
// array of structs.  It then presents the following menu 
// to the user:
// 
//   Snow Shepherds Menu
//   1 - Find product by ID
//   2 - Find product by Name
//   3 - List products
//   4 - Change wholesale price
//   5 - Change retail price
//   6 - Order product
//   7 - Sell product
//   9 - Exit
//   Enter an option :
//
// Option 1 prompts the user for an ID, searches the 
// products array for the ID, and prints an error message
// or prints product information.
// 
// Option 2 prompts the user for a product name, searches 
// the products array for the name, and prints an error 
// message or prints product information.
//
// Option 3 prints all data stored in the products array.
//
// Option 4 prompts user for an ID, searches the products
// array for the ID, and prints an error message or
// uses a validation loop to promt for and get a new
// wholesale price for the product that is greater than
// zero. It stores new wholesale price and prints a
// message.
//
// Option 5 prompts user for an ID, searches the products
// array for the ID, and prints an error message or
// uses a validation loop to promt for and get a new
// retail price for the product that is greater than
// the wholesale price. It stores new retail price and
// prints a message.
//
// Option 6 prompts user for an ID, searches the products
// array for the ID, and prints an error message or
// uses a validation loop to promt for and get a new
// quantity to order for the product that is greater than
// zero. It adds the quantity to existing quantity and
// prints a message.
//
// Option 7 prompts user for an ID, searches the products
// array for the ID, and prints an error message or
// uses a validation loop to promt for and get a new
// quantity to sell for the product that is less than the
// existing quantity. It subtracts the quantity from the
// existing quantity for the product and prints a
// message.
//
// The application continues to read and process options
// until the user enters the sentinel value of 9.
//
//==========================================================
#include <cstdlib> // For several general-purpose functions
#include <fstream> // For file handling
#include <iomanip> // For formatted output
#include <iostream> // For cin, cout, and system
#include <string> // For string data type
using namespace std; // So "std::cout" may be abbreviated to "cout"

//==========================================================
// Globals
//==========================================================

// Declare constants
const int ARRAY_SIZE = 5;
const string INPUT_FILE_NAME = "SnowShepherdsInventory.txt";
const int COLWIDTH1 = 22;
const int COLWIDTH2 = 13;

// Declare structs
struct product
{
  int ID;
  string product;
  double wholesale;
  double retail;
  int quantity;
};

//==========================================================
// menuOption
//==========================================================
int menuOption()
{

  // Declare variables
  int option;

  // Show menu and get option
  cout << "\nSnow Shepherds Menu" << endl;
  cout << "1-Find product by ID" << endl;
  cout << "2-Find product by Name" << endl;
  cout << "3-List products" << endl;
  cout << "4-Change wholesale price" << endl;
  cout << "5-Change retail price" << endl;
  cout << "6-Order product" << endl;
  cout << "7-Sell product" << endl;
  cout << "9-Exit" << endl;
  cout << "\nEnter an option: ";
  cin >> option;
  return option;

}

//==========================================================
// findProductByID
//==========================================================
int findProductByID(product products[], int key)
{
  int index;
  index = 0;
  while (index < ARRAY_SIZE &&
    products[index].ID != key)
    index = index + 1;
  if (index == ARRAY_SIZE)
    index = -1;
  return index;
}

//==========================================================
// findProductByName
//==========================================================
int findProductByName(product products[], string key)
{
  int index;
  index = 0;
  while (index < ARRAY_SIZE &&
    products[index].product != key)
    index = index + 1;
  if (index == ARRAY_SIZE)
    index = -1;
  return index;
}

//==========================================================
// printProduct
//==========================================================
void printProduct(product products[], int index)
{
  cout << "\nProduct " << products[index].ID << endl;
  cout << setw(COLWIDTH1) << left << "Product:"
    << setw(COLWIDTH2) << right
    << products[index].product << endl;
  cout << setw(COLWIDTH1) << left << "Wholesale price ($):"
    << setw(COLWIDTH2) << right
    << products[index].wholesale << endl;
  cout << setw(COLWIDTH1) << left << "Retail price ($):"
    << setw(COLWIDTH2) << right
    << products[index].retail << endl;
  cout << setw(COLWIDTH1) << left << "Quantity in stock:"
    << setw(COLWIDTH2) << right
    << products[index].quantity << endl;
}

//==========================================================
// main
//==========================================================
int main()
{

  // Declare variables
  ifstream inFile;
  int lineCount;
  string line;
  product products[ARRAY_SIZE];
  int option;
  int index;
  int ID;
  string product;
  double WholesalePrice;
  double RetailPrice;
  int AddQuantity;
  int SellQuantity;

  // Format real numbers
  cout << fixed << setprecision(2);

  // Show application header
  cout << "Welcome to Snow Shepherds, v2" << endl;
  cout << "-------------------------" << endl;

  // Attempt to open input file
  inFile.open(INPUT_FILE_NAME);
  if (!inFile.is_open())
    cout << "Error: unable to open file '"
    << INPUT_FILE_NAME << "'." << endl << endl;
  else
  {

    // Scan past header line
    getline(inFile, line);

    // Loop to read input file
    lineCount = 0;
    while (inFile.good())
    {

      // Read line into arrays
      inFile >> products[lineCount].ID;
      inFile >> products[lineCount].product;
      inFile >> products[lineCount].wholesale;
      inFile >> products[lineCount].retail;
      inFile >> products[lineCount].quantity;
      lineCount = lineCount + 1;

    }

    // Close input file
    inFile.close();
    cout << endl << lineCount
      << " line(s) read from file '" << INPUT_FILE_NAME
      << "'." << endl;

    // Loop to process options
    option = menuOption();
    while (option != 9)
    {

      // Handle option
      switch (option)
      {

        // Find product by ID
        case 1:

          // Prompt for and get ID
          cout << "Enter product ID to search for: ";
          cin >> ID;

          // Search for ID
          index = findProductByID(products, ID);
          if (index == -1)
            cout << "Error: product ID '" << ID
            << "' not in inventory." << endl;
          else
            printProduct(products, index);
          break;

          // Find product by name
        case 2:

          // Prompt for and get name
          cout << "Enter product name to search for: ";
          cin >> product;

          // Search for name
          index = findProductByName(products, product);
          if (index == -1)
            cout << "Error: product name '" << product
            << "' not in inventory." << endl;
          else
            printProduct(products, index);
          break;

        // List products
      case 3:

        // Print column headings
        cout << "\nProduct Inventory" << endl;
        cout << setw(COLWIDTH2) << left << "Code"
          << setw(COLWIDTH2) << left << "Product"
          << setw(COLWIDTH2) << right << "Wholesale ($)"
          << setw(COLWIDTH2) << right << "Retail ($)"
          << setw(COLWIDTH2) << right << "Inventory"
          << endl;

        // Loop to print inventory
        for (int i = 0; i < lineCount; i++)
          cout << setw(COLWIDTH2) << left << products[i].ID
            << setw(COLWIDTH2) << left << products[i].product
            << setw(COLWIDTH2) << right << products[i].wholesale
            << setw(COLWIDTH2) << right << products[i].retail
            << setw(COLWIDTH2) << right << products[i].quantity
            << endl;

        break;

        // Change wholesale price
      case 4:

          // Prompt for and get ID
          cout << "Enter product ID to change wholesale price for: ";
          cin >> ID;

          // Search for ID
          index = findProductByID(products, ID);
          if (index == -1)
          {
              cout << "Error: product ID '" << ID
                  << "' not in inventory." << endl;
          }
          else
          {
              // promts user for wholesale price
              cout << "Enter new wholesale price (Currently $" << products[index].wholesale << "): ";
              cin >> WholesalePrice;

              // validation loop
              while (WholesalePrice < 0)
              {
                  cout << "Error: wholesale price must be greater than zero (Currently $" << products[index].wholesale << ")." << endl << endl;
                  cout << "Enter new wholesale price (Currently $" << products[index].wholesale << "): ";
                  cin >> WholesalePrice;
              }

              // Sets new wholesale price
              products[index].wholesale = WholesalePrice;
              cout << "Wholesale price changed to $" << products[index].wholesale << endl;
          }

          break;

          // Change retail price
      case 5:

          // Prompt for and get ID
          cout << "Enter product ID to change retail price for: ";
          cin >> ID;

          // Search for ID
          index = findProductByID(products, ID);
          if (index == -1)
          {
              cout << "Error: product ID '" << ID
                  << "' not in inventory." << endl;
          }
          else
          {
              // prompts user for new retail price
              cout << "Enter new retail price (Currently $" << products[index].retail << "): ";
              cin >> RetailPrice;

              // validation loop
              while (RetailPrice < products[index].wholesale)
              {
                  cout << "Error: retail price must be greater than wholesale price (currently $" << products[index].wholesale << ")." << endl << endl;
                  cout << "Enter new retail price (Currently $" << products[index].retail << "): ";
                  cin >> RetailPrice;
              }

              // sets new retail price
              products[index].retail = RetailPrice;
              cout << "Retail price changed to $" << products[index].retail << endl;
          }

          break;

          // Order Product
      case 6:

          // Prompt for and get ID
          cout << "Enter product ID to order: ";
          cin >> ID;

          // Search for ID
          index = findProductByID(products, ID);
          if (index == -1)
          {
              cout << "Error: product ID '" << ID
                  << "' not in inventory." << endl;
          }
          else
          {
              // promts user for quantity to order
              cout << "Enter quantity to order (Currently " << products[index].quantity << "): ";
              cin >> AddQuantity;

              // validation loop
              while (AddQuantity < 0)
              {
                  cout << "Error: quantity to order must be greater than zero." << endl << endl;
                  cout << "Enter quantity to order (Currently " << products[index].quantity << "): ";
                  cin >> AddQuantity;
              }

              // adds user input to quantity
              products[index].quantity = products[index].quantity + AddQuantity;
              cout << "Quantity in stock is now " << products[index].quantity << endl;
          }

          break;

          // Sell Product
      case 7:

          // Prompt for and get ID
          cout << "Enter product ID to sell: ";
          cin >> ID;

          // Search for ID
          index = findProductByID(products, ID);
          if (index == -1)
          {
              cout << "Error: product ID '" << ID
                  << "' not in inventory." << endl;
          }
          else
          {
              // promts user for quantity to sell
              cout << "Enter quantity to sell (Currently " << products[index].quantity << "): ";
              cin >> SellQuantity;

              // validation loop
              while (SellQuantity > products[index].quantity)
              {
                  cout << "Error: quantity must be less than or equal to " << products[index].quantity << endl << endl;
                  cout << "Enter quantity to sell (Currently " << products[index].quantity << "): ";
                  cin >> SellQuantity;
              }

              // subtracts user input from quantity
              products[index].quantity = products[index].quantity - SellQuantity;
              cout << "Quantity in stock is now " << products[index].quantity << endl;
          }

          break;

        // Handle invalid option
      default:
        cout << "Error: unknown option." << endl;

      }

      // Get next option
      option = menuOption();

    }

  }

  // Show application close
  cout << "\nEnd of Snow Shepherds, v2" << endl;

}
