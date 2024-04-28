/*
 * GroceryTracker.cpp
 * Author: Darian Gernand
 * Date: 04/21/2024
 * Description: Item tracker
 */


#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits> 

using namespace std;

class ItemTracker {
private:
    map<string, int> frequencyMap;

public:
    // Load records from the given file and update the frequency map
    void loadRecords(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file " << filename << endl;
            return;
        }

        string item;
        while (file >> item) {
            frequencyMap[item]++;
        }

        file.close();
    }

    // Retrieve the frequency of a specific item from the frequency map
    int getItemFrequency(const string& item) {
        return frequencyMap[item];
    }

    // Print a list of all items along with their frequencies
    void printFrequencyList() {
        for (const auto& pair : frequencyMap) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Print a histogram representation of item frequencies
    void printHistogram() {
        for (const auto& pair : frequencyMap) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }

    // Backup the frequency map data to a file
    void backupData(const string& filename) {
        ofstream backupFile(filename);
        if (!backupFile.is_open()) {
            cout << "Error: Unable to create backup file " << filename << endl;
            return;
        }

        for (const auto& pair : frequencyMap) {
            backupFile << pair.first << " " << pair.second << endl;
        }

        backupFile.close();
    }
};

int main() {
    ItemTracker tracker;

    // Load records from file
    tracker.loadRecords("CS210_Project_Three_Input_File.txt");

    int choice;
    do {
        // Display menu options
        cout << "Menu:\n"
            << "1. Check frequency of specific item\n"
            << "2. Print frequency list of all items\n"
            << "3. Print histogram\n"
            << "4. Exit\n"
            << "Enter your choice: ";

        // Input validation loop to ensure a valid choice is entered
        while (!(cin >> choice)) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number between 1 and 4: ";
        }

        switch (choice) {
        case 1: {
            string item;
            cout << "Enter the item to check frequency: ";
            cin >> item;
            cout << "Frequency of " << item << ": " << tracker.getItemFrequency(item) << endl;
            break;
        }
        case 2:
            cout << "Frequency List:\n";
            tracker.printFrequencyList();
            break;
        case 3:
            cout << "Histogram:\n";
            tracker.printHistogram();
            break;
        case 4:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    } while (choice != 4);

    // Backup data
    tracker.backupData("frequency.dat");

    return 0;
}
