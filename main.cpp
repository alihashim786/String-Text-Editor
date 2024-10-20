#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct File {
    string name;
    vector<string> content;
};

vector<File*> files;

void createFile() {
    string fileName;
    cout << "Enter the new file name: ";
    cin >> fileName;
    
    int numLines;
    cout << "Enter the number of lines in the file: ";
    cin >> numLines;

    File* newFile = new File;
    newFile->name = fileName;

    cin.ignore(); // Ignore any newline left in the input buffer
    cout << "Enter the file content (max 60 characters per line):" << endl;
    for (int i = 0; i < numLines; i++) {
        string line;
        cout << i + 1 << ". ";
        getline(cin, line);

        // If line exceeds 60 characters, split into multiple lines
        while (line.length() > 60) {
            newFile->content.push_back(line.substr(0, 60));
            line = line.substr(60);
        }
        newFile->content.push_back(line);
    }

    files.push_back(newFile);
    cout << "File '" << fileName << "' created successfully!" << endl;
}

File* findFile(const string& fileName) {
    for (File* file : files) {
        if (file->name == fileName) {
            return file;
        }
    }
    return nullptr;
}

void viewFile() {
    string fileName;
    cout << "Enter the file name to view: ";
    cin >> fileName;

    File* file = findFile(fileName);
    if (file) {
        cout << "File: " << file->name << endl;
        for (int i = 0; i < file->content.size(); i++) {
            cout << i + 1 << ". " << file->content[i] << endl;
        }
    } else {
        cout << "File not found!" << endl;
    }
}

void editFile() {
    string fileName;
    cout << "Enter the file name to edit: ";
    cin >> fileName;

    File* file = findFile(fileName);
    if (!file) {
        cout << "File not found!" << endl;
        return;
    }

    int choice;
    cout << "Press 1 to edit a specific line.\n";
    cout << "Press 2 to replace a specific word.\n";
    cin >> choice;

    if (choice == 1) {
        int lineNum;
        cout << "Enter the line number to edit: ";
        cin >> lineNum;

        if (lineNum > 0 && lineNum <= file->content.size()) {
            cin.ignore(); // Ignore newline character
            string newText;
            cout << "Enter the new text for line " << lineNum << ": ";
            getline(cin, newText);

            file->content[lineNum - 1] = newText;
            cout << "Line " << lineNum << " updated successfully!" << endl;
        } else {
            cout << "Invalid line number!" << endl;
        }
    } else if (choice == 2) {
        string oldWord, newWord;
        cout << "Enter the word to replace: ";
        cin >> oldWord;
        cout << "Enter the new word: ";
        cin >> newWord;

        for (string& line : file->content) {
            size_t pos;
            while ((pos = line.find(oldWord)) != string::npos) {
                line.replace(pos, oldWord.length(), newWord);
            }
        }

        cout << "Word '" << oldWord << "' replaced with '" << newWord << "' successfully!" << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }
}

void copyFile() {
    string fileName;
    cout << "Enter the name of the file to copy: ";
    cin >> fileName;

    File* file = findFile(fileName);
    if (!file) {
        cout << "File not found!" << endl;
        return;
    }

    string newFileName;
    cout << "Enter the new file name: ";
    cin >> newFileName;

    File* newFile = new File;
    newFile->name = newFileName;
    newFile->content = file->content;

    files.push_back(newFile);
    cout << "File '" << fileName << "' copied to '" << newFileName << "' successfully!" << endl;
}

void deleteFile() {
    string fileName;
    cout << "Enter the file name to delete: ";
    cin >> fileName;

    auto it = find_if(files.begin(), files.end(), [&](File* file) { return file->name == fileName; });
    if (it != files.end()) {
        delete *it;  // Free the dynamically allocated memory
        files.erase(it);
        cout << "File '" << fileName << "' deleted successfully!" << endl;
    } else {
        cout << "File not found!" << endl;
    }
}

void listFiles() {
    cout << "List of all files:" << endl;
    for (File* file : files) {
        cout << file->name << endl;
    }
}

int main() {
    int choice;
    
    do {
        cout << "\nMain Menu:\n";
        cout << "1. Create a new file\n";
        cout << "2. View an existing file\n";
        cout << "3. Edit an existing file\n";
        cout << "4. Copy an existing file to a new file\n";
        cout << "5. Delete an existing file\n";
        cout << "6. View list of all files\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createFile();
                break;
            case 2:
                viewFile();
                break;
            case 3:
                editFile();
                break;
            case 4:
                copyFile();
                break;
            case 5:
                deleteFile();
                break;
            case 6:
                listFiles();
                break;
            case 7:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);

    // Clean up dynamically allocated memory
    for (File* file : files) {
        delete file;
    }

    return 0;
}
