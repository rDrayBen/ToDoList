#include <iostream>
#include <string>
#include <fstream>
using namespace std;

enum Choise {
	ADD_NOTE = 1, 
	SHOW_ALL_NOTES, 
	FIND_ONE_NOTE, 
	REMOVE_ONE_NOTE,
	REMOVE_ALL_NOTES
};

void show_Menu() {
	cout << "[1]: Add note" << endl;
	cout << "[2]: Show all notes" << endl;
	cout << "[3]: Find note" << endl;
	cout << "[4]: Remove one note" << endl;
	cout << "[5]: Remove all notes" << endl;
	cout << "[6]: Exit" << endl;
}

void AddNewNote(const string& your_note) {
	fstream WriteInFile;
	WriteInFile.open("Notes for ToDoList.txt", ios::app);
	if (WriteInFile.is_open()) {
		WriteInFile << your_note << endl;

	}
	WriteInFile.close();
	cout << "Note added!" << endl;
}

void ShowAllNotes() {
	ifstream file("Notes for ToDoList.txt");
	if (!file.is_open()) {
		cout << "No notes yet" << endl;
		return;
	}
	string one_note;
	for (int i = 1; !file.eof(); i++) {
		getline(file, one_note);
		if (one_note.empty()) {
			continue;
		}
		cout << "[" << i << "]" << one_note << endl;
	}
	file.close();
}

void RemoveAllNotes() {
	ofstream file;
	ifstream ReadFromFile;
	
	
	file.open("Notes for ToDoList.txt");
	file.close();
	cout << "All notes deleted succesfully" << endl;
}

string* FindOneNote(const string& note_to_find, int& n_count) {
	ifstream ReadFromFile;
	ReadFromFile.open("Notes for ToDoList.txt");
	if (!ReadFromFile.is_open()) {
		cout << "Error";
	}
	string one_note;
	string* found_notes = nullptr;
	string* found_notes_tm = nullptr;
	int count = 0;

	while (!ReadFromFile.eof()) {
		getline(ReadFromFile, one_note);
		if (one_note.find(note_to_find) != -1) {
			count++;
			found_notes_tm = new string[count];
			for (int i = 0; i < count - 1; i++) {
				found_notes_tm[i] = found_notes[i];
			}
			found_notes_tm[count - 1] = one_note;

			delete[] found_notes;

			found_notes = found_notes_tm;
			found_notes_tm = nullptr;


		}
	}

	ReadFromFile.close();
	n_count = count;
	return found_notes;
}

string* all_notes(int& n_count) {
	string* all_notes = nullptr;
	string* all_notes_ptr = nullptr;

	ifstream file;
	file.open("Notes for ToDoList.txt");

	string one_note;
	int count = 0;
	while (!file.eof()) {
		getline(file, one_note);
		if (one_note.empty()) {
			continue;
		}
		count++;
		all_notes_ptr = new string[count];
		for (int i = 0; i < count - 1; i++) {
			all_notes_ptr[i] = all_notes[i];
		}
		all_notes_ptr[count - 1] = one_note;
		delete[] all_notes;
		all_notes = all_notes_ptr;

		all_notes_ptr = nullptr;

	}
	file.close();
	n_count = count;
	return all_notes;
}

void RemoveOneNote(string* all_notes_arr, int count, int your_choise) {
	ofstream WriteInFile;
	WriteInFile.open("Notes for ToDoList.txt");
	for (int i = 0; i < count; i++) {
		if (i == your_choise - 1) {
			continue;
		}
		WriteInFile << all_notes_arr[i] << endl;
	}
	
	WriteInFile.close();
}

int main()
{
	cout << "Hi! That's a ToDoList. After cliking \"Enter\" you can see 6 options to pick from." << endl;
	cout << "All you need is just to write the number of option you want to use." << endl;
	cout << "Good luck!" << endl;
	system("pause");
	system("cls");
	while (true) {
		system("cls");
		show_Menu();
		cout << "Your choise: ";
		int choise = 0;
		cin >> choise;
		if (choise == ADD_NOTE) {
			system("cls");
			string your_note;
			getline(cin, your_note);
			cout << "Write your note here: " << endl;
			getline(cin, your_note);
			AddNewNote(your_note);
			system("pause");
		}
		else if (choise == SHOW_ALL_NOTES) {
			system("cls");
			ShowAllNotes();
			system("pause");
		}
		else if (choise == FIND_ONE_NOTE) {
			system("cls");
			int n_found = 0;
			string note_to_find;
			getline(cin, note_to_find);
			cout << "Enter your note: ";
			getline(cin, note_to_find);
			string* found_notes = FindOneNote(note_to_find, n_found);

			if (found_notes) {
				cout << "Found notes: ";
				for (int i = 0; i < n_found; i++) {
			cout << found_notes[i] << endl;
				}
			delete[] found_notes;
		}
		else {
			cout << "No such notes" << endl;
		}
			system("pause");
		}
		else if (choise == REMOVE_ONE_NOTE) {
			system("cls");
			int count = 0;
			string *all_notes_arr = all_notes(count);
			cout << "All notes: " << endl;
			for (int i = 0; i < count; i++) {
				cout << "[" << i + 1 << "]" << all_notes_arr[i] << endl;
			}
			cout << "Which note you want to remove: ";
			int your_choise;
			cin >> your_choise;
			RemoveOneNote(all_notes_arr, count, your_choise);
			cout << "This note is removed" << endl;
			delete[] all_notes_arr;
			system("pause");
		}
		else if (choise == REMOVE_ALL_NOTES) {
			system("cls");
			RemoveAllNotes();
			system("pause");
		}
		else if (choise == 6) {
			break;
		}
	}
	
	return 0;
}