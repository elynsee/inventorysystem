# COMP0002 Coursework 1 - Inventory Management System

## About the Inventory Management System

The inventory system allows you to easily manage the inventory for a small business. You can add and remove items from your inventory, and update stock availability as it changes. The system also enables you to easily search for items in your inventory and can display a list of all the items in your inventory. Lastly, the system allows you to import from and export files to your local repository for easy reference.

### Features of the Inventory Management System

1. Add item into inventory - Users can enter a new item into their inventory. Users will be prompted to key in the name, barcode number, price and stock availability of the item. This value is then stored in an array titled inventory. 
2. Remove item from inventory - Users can remove an existing item from their inventory. Users will be prompted to either enter a barcode number or name. The program checks if the item exists and removes it from the array, inventory if so. If the item does not exist, the program returns to the main menu. 
3. Update stock of item - Users can update the stock available for an existing item. Users will be prompted to enter the name of the item they wish to update. The program checks if the item exists and if so, the old stock value is replaced by the new stock value. If the item does not exist, the program returns to the main menu 
4. Search for item in inventory - Users can search for a particular item in their inventory. Users will be prompted to either enter a barcode number or a name. The program checks if the item exists and if so, displays the name, barcode number, price and stock availability of the item. If the item does not exist, the program returns to the main menu. 
5. List all items in inventory - The program displays all the items in the inventory 
6. Load inventory from an existing file - If users have an existing data file, they are able to import the file into the program. Users will have to ensure that the data file is in the correct sub-directory \(data\) and type in the file name in the program. The program then loads the data and removes any existing data in the database. 
7. Produce a report for inventory - Users will be prompted to enter a file name for the report. The program takes all existing data in the inventory and saves them into a file. The report will then be written to a file in the sub-directory \(data\). 

## Compiling and Running the Program

The block below details the directory & file structures of our inventory management system. If you wish to import a data file into the system, ensure that your file is in the folder named "data". Reports produced from the program will also be stored in the same folder.

```text
COMP0002CW1
├── src
│   └── inventory.c
├── data
│   └── sample_data.txt
│   
└── documentation
    └── readMe.md

```

To run the program, open a terminal program and navigate to the folder named "src". Execute the following line of code to compile the program:

```bash
gcc -o inventory inventory.c
```

After compiling the code, execute the program by executing the following line of code:

```bash
inventory.exe
```

The program is now executed and you can run the inventory management system!

