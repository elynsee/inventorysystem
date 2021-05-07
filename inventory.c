#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define INVENTORY_SIZE 500
#define MAX_LENGTH_OF_STRING 200
#define MAX_LENGTH_OF_PRICE 8
#define MAX_LENGTH_OF_STOCK 20
#define ADD 1
#define REMOVE 2
#define UPDATE 3
#define SEARCH 4
#define LIST 5
#define LOAD 6
#define SAVE 7
#define QUIT 8
#define BY_NAME 1
#define BY_BARCODE 2

struct entry
{
    char *name;
    char *barcode;
    char *price;
    char *stock;
};

struct entry *inventory[INVENTORY_SIZE];
char* readString(char*);
void removeNewLine(char*);
struct entry *createEntry(char*, char*, char*, char*);
void displayMenu(void);
int inputUserOption(void);
void doMenuOption(int);
void startMenu(void);
void addItem(void);
void removeItem(void);
void removeByName(void);
void removeByBarcode(void);
void updateItem(void);
void searchForItem(void);
void searchByName(void);
void searchByBarcode(void);
void listAllInventory(void);
void loadInventoryFromFile(void);
void saveInventoryToFile(void);
void initialiseSampleInventory(void);

char* readString(char* prompt)
{
  char buffer[MAX_LENGTH_OF_STRING];
  printf("%s", prompt);
  fgets(buffer, MAX_LENGTH_OF_STRING, stdin);
  size_t inputLength = strlen(buffer);
  char *input = calloc(sizeof(char), inputLength);
  strncpy(input, buffer, inputLength-1);
  input[inputLength-1] = '\0';
  return input;
}

void removeNewLine(char *buffer)
{
  size_t length = strlen(buffer);
  if (length == 0)
  {
    return;
  }
  if (buffer[length-1] == '\n')
  {
    buffer[length-1] = '\0';
  }
}

struct entry *createEntry(char* name, char* barcode, char* price, char* stock) 
{
  struct entry *entry = calloc(sizeof(struct entry),1);
  entry->name = calloc(sizeof(char), strlen(name) + 1);
  strcpy(entry->name, name);
  entry->barcode = calloc(sizeof(char), strlen(barcode) + 1);
  strcpy(entry->barcode, barcode);
  entry->price = calloc(sizeof(char), strlen(price) + 1);
  strcpy(entry->price, price);
  entry->stock = calloc(sizeof(char), strlen(stock) + 1);
  strcpy(entry->stock, stock);
  return entry;
}

void displayMenu()
{
    printf("Welcome to your inventory system!\n");
    printf("Please enter the number corresponding to the task you wish to complete.\n");
    printf("%i) Add a new item to the inventory\n", ADD);
    printf("%i) Remove an existing item from the inventory\n", REMOVE);
    printf("%i) Update an item's stock\n", UPDATE);
    printf("%i) Search for an item\n", SEARCH);
    printf("%i) List all items in inventory\n", LIST);
    printf("%i) Load inventory from an existing file\n", LOAD);
    printf("%i) Generate a report of all items in inventory\n", SAVE);
    printf("%i) Quit\n", QUIT);
}

int inputUserOption()
{
    int userInput;
    char *input = readString("Enter number here: ");
    sscanf(input, "%i", &userInput);
    free(input);
    return userInput;
}

void doMenuOption(int userInput)
{
    switch (userInput)
    {
        case ADD : addItem(); break;
        case REMOVE : removeItem(); break;
        case UPDATE : updateItem(); break;
        case SEARCH : searchForItem(); break;
        case LIST : listAllInventory(); break;
        case LOAD : loadInventoryFromFile(); break;
        case SAVE : saveInventoryToFile(); break;
        default : printf("Please enter a valid number!\n");
    }
}

void startMenu()
{
    while (true)
    {
        displayMenu();
        int userInput = inputUserOption();
        if (userInput == QUIT)
        {
            printf("Program terminated!\n");
            break;
        }
        else
        {
            doMenuOption(userInput);
        }
    }
}

void addItem()
{
    printf("You selected: 1) Add a new item to the inventory\n");
    int index = -1;
    while(inventory[++index] != NULL);
    if (index > INVENTORY_SIZE-2)
    {
        printf("Your inventory is full!\n");
        return;
    }
    char *name = readString("Please enter the item's name: ");
    char *barcode = readString("Please enter the item's barcode number: ");
    char *price = readString("Please enter the price of the item: ");
    char *stock = readString("Please enter the number of stock available: ");
    struct entry *entry = createEntry(name, barcode, price, stock);
    printf("Item has been added to inventory!\n");
    inventory[index] = entry;
    inventory[index+1] = NULL;
    free(name);
    free(barcode);
    free(price);
    free(stock);    
}

void removeItem()
{
    printf("You selected: 2) Remove an existing item from the inventory\n");
    printf("Do you wish to: \n");
    printf("1) Remove item by name\n");
    printf("2) Remove item by barcode number\n");
    int userInput = inputUserOption();
    if (userInput == BY_NAME)
    {
        removeByName();
        return;
    }
    else if (userInput == BY_BARCODE)
    {
        removeByBarcode();
        return;
    }
    else
    {
        printf("Please enter a valid number!\n");
    }
}

void removeByName()
{
    printf("You selected: 1) Remove item by name\n");
    int index = 0;
    char *name = readString("Please enter the name of item you wish to remove: ");
    while ((inventory[index] != NULL) && (strcmp(inventory[index]->name, name)))
    {
        index++;
    }
    if (inventory[index] == NULL)
    {
        printf("No entry found for item named %s.\n", name);
        free(name);
        return;
    }
    struct entry *removed = inventory[index];
    do 
    {
        inventory[index] = inventory[index+1];
    } while (inventory[++index] != NULL);
    printf("Item has been removed from inventory!\n");
    free(removed->name);
    free(removed->barcode);
    free(removed->price);
    free(removed->stock);
    free(removed);
    free(name);
}

void removeByBarcode()
{
    printf("You selected: 2) Remove item by barcode\n");
    int index = 0;
    char *barcode = readString("Please enter the barcode number of the item you wish to remove: ");
    while ((inventory[index] != NULL) && (strcmp(inventory[index]->barcode, barcode)))
    {
        index++;
    }
    if (inventory[index] == NULL)
    {
        printf("No entry found for item with barcode number %s.\n", barcode);
        free(barcode);
        return;
    }
    struct entry *removed = inventory[index];
    do 
    {
        inventory[index] = inventory[index+1];
    } while (inventory[++index] != NULL);
    printf("Item has been removed from inventory!\n");
    free(removed->name);
    free(removed->barcode);
    free(removed->price);
    free(removed->stock);
    free(removed);
    free(barcode);
}

void updateItem()
{
    printf("You selected: 3) Update an item's stock\n");
    char *name = readString("Please enter the name of item you wish to update: ");
    int index = 0;
    if (inventory[index] != NULL && !strcmp(inventory[index]->name,name))
    {
        printf("Current stock for %s: %s\n", inventory[index]->name, inventory[index]->stock);
        char *stock = readString("Please enter new stock for item: ");
        strcpy(inventory[index]->stock, stock);
        free(name);
        free(stock);
        return;
    }
    printf("No entry with item name %s was found\n", name);
    free(name);
}

void searchForItem()
{
    printf("You selected: 4) Search for an item\n");
    printf("Do you wish to: \n");
    printf("1) Search for item by name\n");
    printf("2) Search for item by barcode number\n");
    int userInput = inputUserOption();
    if (userInput == BY_NAME)
    {
        searchByName();
        return;
    }
    else if (userInput == BY_BARCODE)
    {
        searchByBarcode();
        return;
    }
    else
    {
        printf("Please enter a valid number!\n");
    }
}

void searchByName()
{
    printf("You selected: 1) Search for item by name\n");
    char *name = readString("Please enter the item's name: ");
    int index = 0;
    while (inventory[index] != NULL)
    {
        if (!strcmp(inventory[index]->name,name))
        {
            printf("Name of item: %s\n", inventory[index]->name);
            printf("Barcode number of %s: %s\n", inventory[index]->name, inventory[index]->barcode);
            printf("Price of %s: %s\n", inventory[index]->name, inventory[index]->price);
            printf("Available stock for %s: %s\n", inventory[index]->name, inventory[index]->stock);
            free(name);
            return;
        }
        index++;
    }
    printf("No entry with item name %s was found\n", name);
    free(name);
}

void searchByBarcode()
{
    printf("You selected: 2) Search for item by barcode number\n");
    char *barcode = readString("Please enter the barcode number of the item you wish to search: ");
    int index = 0;
    while (inventory[index] != NULL)
    {
        if (!strcmp(inventory[index]->barcode,barcode))
        {
            printf("Name of item: %s\n", inventory[index]->name);
            printf("Barcode number of %s: %s\n", inventory[index]->name, inventory[index]->barcode);
            printf("Price of %s: %s\n", inventory[index]->name, inventory[index]->price);
            printf("Available stock for %s: %s\n", inventory[index]->name, inventory[index]->stock);
            free(barcode);
            return;
        }
        index++;
    }
    printf("No entry with barcode number %s was found\n", barcode);
    free(barcode);
}

void listAllInventory()
{
    printf("You selected: 5) List all items in inventory\n");
    if (inventory[0] == NULL)
    {
        printf("No inventory has been recorded!\n\n");
        return;
    }
    int index = 0;
    while (inventory[index] != NULL)
    {
        printf("Entry %i - Item: %s, Barcode Number: %s, Price: %s, Stock Available: %s\n",
                index + 1, inventory[index]->name, inventory[index]->barcode, inventory[index]->price, inventory[index]->stock);
        index++;
    }
}

void loadInventoryFromFile()
{
    printf("You selected: 6) Load inventory from an existing file\n");
    char* fileName = readString("Please enter the file name: ");
    char dir[50] = "../data/";
    strcat(dir, fileName);
    FILE *inputFile = fopen(dir, "r");
    if (inputFile == NULL)
    {
        printf("\nUnable to read from file named %s\n", fileName);
        free(fileName);
        return;
    }
    int index = 0;
    char name[MAX_LENGTH_OF_STRING];
    char barcode[MAX_LENGTH_OF_STRING];
    char price[MAX_LENGTH_OF_PRICE];
    char stock[MAX_LENGTH_OF_STOCK];
    while (index < INVENTORY_SIZE-1)
    {
        fgets(name, MAX_LENGTH_OF_STRING-1, inputFile);
        fgets(barcode, MAX_LENGTH_OF_STRING-1, inputFile);
        fgets(price, MAX_LENGTH_OF_PRICE-1, inputFile);
        char *input = fgets(stock, MAX_LENGTH_OF_STOCK-1, inputFile);
        if (input == NULL)
        {
            break;
        }
        removeNewLine(name);
        removeNewLine(barcode);
        removeNewLine(price);
        removeNewLine(stock);
        inventory[index] = createEntry(name, barcode, price, stock);
        index++;
    }
    inventory[index] = NULL;
    fclose(inputFile);
    free(fileName);
}

void saveInventoryToFile()
{
    printf("You selected: 7) Generate a report of all items in inventory\n");
    char *fileName = readString("Please enter the report name: ");
    char dir[50] = "../data/";
    strcat(dir, fileName);
    FILE *outputFile = fopen(dir, "w");
    if (outputFile == NULL)
    {
        printf("Please enter a valid name for the report!\n");
        free(fileName);
        return;
    }
    int index = 0;
    while (inventory[index] != NULL)
    {
        fprintf(outputFile, "%s\n", inventory[index]->name);
        fprintf(outputFile, "%s\n", inventory[index]->barcode);
        fprintf(outputFile, "%s\n", inventory[index]->price);
        fprintf(outputFile, "%s\n", inventory[index]->stock);
        index++;
    }
    fclose(outputFile);
    free(outputFile);
}

void initialiseSampleInventory()
{
    inventory[0] = createEntry("Frozen Pizza", "18642357", "$1.99", "100");
    inventory[1] = createEntry("Taco Shells", "95148632", "$0.99", "250");
}

int main(void)
{
    inventory[0] = NULL;
    initialiseSampleInventory();
    startMenu();
    return 0;
}