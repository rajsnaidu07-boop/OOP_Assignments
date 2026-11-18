#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Student {
    int id;
    string name;
    float marks;
};

// WRITE: append a record to the end of the file
void writeRecord(const string& file, const Student& s) {
    ofstream out(file, ios::app);
    out << s.id << "," << s.name << "," << s.marks << "\n";
    cout << "Saved. Write pointer (tellp) = " << out.tellp() << "\n";
}

// READ: display all records
void readAll(const string& file) {
    ifstream in(file);
    string line;
    cout << "\nID\tName\tMarks\n";
    while (getline(in, line)) {
        stringstream ss(line);
        string id, name, marks;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, marks, ',');
        cout << id << "\t" << name << "\t" << marks << "\n";
    }
}

// SEEK: jump to the Nth record (1-based) using seekg + tellg
void readNth(const string& file, int n) {
    ifstream in(file);
    string line;
    in.seekg(0, ios::beg);                  // start of file
    for (int i = 1; i <= n && getline(in, line); i++) {
        if (i == n) {
            cout << "Record " << n << ": " << line << "\n";
            cout << "Read pointer (tellg) = " << in.tellg() << "\n";
            return;
        }
    }
    cout << "Record not found.\n";
}

// UPDATE: overwrite a record's marks in place using seekp
// (marks must keep the same number of characters, e.g. 85.5 -> 90.5)
void updateMarks(const string& file, int id, const string& newMarks) {
    fstream f(file, ios::in | ios::out);
    string line;
    while (true) {
        streampos pos = f.tellg();          // remember where this line starts
        if (!getline(f, line)) break;
        if (stoi(line.substr(0, line.find(','))) == id) {
            size_t lastComma = line.rfind(',');
            f.seekp(pos + (streamoff)(lastComma + 1));  // move write pointer
            f << newMarks;
            cout << "Updated ID " << id << "\n";
            return;
        }
    }
    cout << "ID not found.\n";
}

int main() {
    string file = "students.csv";

    writeRecord(file, {101, "Aman", 85.5});
    writeRecord(file, {102, "Riya", 92.0});
    writeRecord(file, {103, "Karan", 78.5});

    readAll(file);
    readNth(file, 2);

    updateMarks(file, 101, "90.5");
    readAll(file);
    return 0;
}
