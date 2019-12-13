#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
const char Filename[] = "data.dat"; // Data file directory
fstream fp; // fstream instance for saving and loading data from file

// Structure for participants
struct Participant {
	int num; // Participant's number
	char name[30]; // Participant's name
	int age; // Participant's age
	bool gender; // Participant's gender, male = true, female = false
	float hip; // Participant's hip size
	float shoulder; // Participant's shoulder size
	float neck; // Participant's neck size
	float calf; // Participant's calf size
	float total; // Participant's total score - hip/(shoulder+neck+calf)
};

// Constructor for participant structure
Participant input() {
	char ch; // Choice for female/male
	Participant a = { 0 }; // Create instance a of participants as a buffer
	cout << "\nNumber: ";
	cin >> a.num; // Enter new participant's number
	cin.ignore();
	cout << "Name: ";
	cin.getline(a.name, 30); // Enter new participant's name
	cout << "Age: ";
	cin >> a.age; // Enter new participant's age
	// Ask for gender until male or female is selected
	do {
		cout << "Gender [M/F]: ";
		cin >> ch; // Enter new participant's gender
	} while (!(ch == 'm' || ch == 'M' || ch == 'f' || ch == 'F')); // Lowercase and uppercase both accepted
	if (ch == 'm' || ch == 'M') // Lowercase and uppercase both accepted
		a.gender = true; // Male = true, Female = false
	else if (ch == 'f' || ch == 'F') // Lowercase and uppercase both accepted
		a.gender = false; // Male = true, Female = false
	cout << "Hip size (cm): ";
	cin >> a.hip; // Enter new participant's hip size
	cout << "Shoulder size (cm): ";
	cin >> a.shoulder; // Enter new participant's shoulder size
	cout << "Neck size (cm): ";
	cin >> a.neck; // Enter new participant's neck size
	cout << "Calf size (cm): ";
	cin >> a.calf; // Enter new participant's calf size
	return(a); // Return the new participant to the caller function
}

// Functions menu
int menu() {
	int ch; // Function choice
	// Repeat until 1-7 is selected
	do {
		cout << "\n\n \tMenu";
		cout << "\n1. New participant";
		cout << "\n2. New list of participants";
		cout << "\n3. Print participants";
		cout << "\n4. Split participants into categories";
		cout << "\n5. Print winners of categories";
		cout << "\n6. Query menu";
		cout << "\n7. Exit\n";
		cin >> ch; // Enter your choice
	} while (ch < 1 || ch>7);
	return (ch); // Return your choice to the caller function
}


// Add one new participant
void addParticipant(Participant list[], Participant* listSort[], int n) {
	cout << "\nAdd a new participant\n";
	cout << "\nParticipant " << n + 1;
	list[n] = input(); // Create new participant and insert it into the main array
	listSort[n] = &list[n]; // Insert the new participant into the array used only for sorting
}

// Add multiple new participants
int addParticipantList(Participant list[], Participant* listSort[], int n) {
	int i, m; // i = for counter, m = amount of new participants to enter
	// Repeat until participants entered are less than the maximum allowed by array
	do {
		cout << "\nHow many participants to enter (max " << (30 - n) << "): ";
		cin >> m; // Enter amount of new participants to enter
	} while (m < 1 || m + n>30);
	if (m + n <= 30) { // Check if new amount of participants don't overflow the array
		for (i = n; i < n + m; i++) {
			cout << "\nParticipant " << i + 1;
			list[i] = input(); // Create new participant and insert it into the main array
			listSort[i] = &list[i]; // Insert the new participant into the array used only for sorting
		}
	}
	else {
		cout << "\nNo free places\n";
	}
	return(n + m); // Return the new length of the array to the caller function
}

// Save the new data in a file
void saveFile(Participant list[], int n) {
	fp.open(Filename, ios::binary | ios::out); // Open the data file
	fp.write((char*)&n, sizeof(n)); // Insert the length of the main array into the data file
	fp.write((char*)list, n * sizeof(Participant)); // Insert the data of the main array into the data file
	fp.close(); // Close the data file
}

// Load the data from a file
int loadFile(Participant list[], Participant* listSort[], int n) {
	fp.open(Filename, ios::binary | ios::in); // Open the data file
	fp.read((char*)&n, sizeof(n)); // Read the length of the main array from the data file
	fp.read((char*)list, n * sizeof(Participant)); // Read the data of the main array from the data file
	// Insert the data from the main array into the sorting array
	for (int i = 0; i < n; i++) {
		listSort[i] = &list[i];
	}
	fp.close(); // Close the data file
	return n; // Return the array length to the caller function
}

// Print all the data
void printAll(Participant list[], int n) {
	cout << "\nParticipants: " << n << "\n";
	for (int i = 0; i < n; i++) {
		cout << "\nParticipant " << i + 1;
		cout << "\nNumber: " << list[i].num; // Prints the participant's number
		cout << "\nName: " << list[i].name; // Prints the participant's name
		cout << "\nAge: " << list[i].age; // Prints the participant's age
		cout << "\nHip size: " << list[i].hip << "cm"; // Prints the participant's hip size in centimeters
		cout << "\nShoulder size: " << list[i].shoulder << "cm"; // Prints the participant's shoulder size in centimeters
		cout << "\nNeck size: " << list[i].neck << "cm"; // Prints the participant's neck size in centimeters
		cout << "\nCalf size: " << list[i].calf << "cm"; // Prints the participant's calf size in centimeters
		// Checks if the gender is true or false
		if (list[i].gender)
			cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
		else
			cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
	}
}

// Splits participants into category aged 14-16
int splitCategory1(Participant list[], Participant* cat1[], int n, int j) {
	int i; // For counter
	j = 0; // Category 1 array length
	// Go through the whole category 1 array
	for (i = 0; i < n; i++) {
		// Insert into category 1 array only participants aged 14-16
		if (list[i].age >= 14 && list[i].age <= 16) {
			// Insert participant into category 1
			cat1[j] = &list[i];
			j++; // Increase category 1 array length
		}
	}
	cout << "\nCategory 14-16\n";
	for (int i = 0; i < j; i++) {
		cout << "\nParticipant " << i + 1;
		cout << "\nNumber: " << cat1[i]->num; // Prints the participant's number
		cout << "\nName: " << cat1[i]->name; // Prints the participant's name
		cout << "\nAge: " << cat1[i]->age; // Prints the participant's age
		cout << "\nHip size: " << cat1[i]->hip << "cm"; // Prints the participant's hip size in centimeters
		cout << "\nShoulder size: " << cat1[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
		cout << "\nNeck size: " << cat1[i]->neck << "cm"; // Prints the participant's neck size in centimeters
		cout << "\nCalf size: " << cat1[i]->calf << "cm"; // Prints the participant's calf size in centimeters
		// Checks if the gender is true or false
		if (cat1[i]->gender)
			cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
		else
			cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
	}
	if (!j)
		cout << "No participants found";
	return (j);
}

// Splits participants into category aged 17-19
int splitCategory2(Participant list[], Participant* cat2[], int n, int k) {
	int i; // For counter
	k = 0; // Category 2 array length
	// Go through the whole category 2 array
	for (i = 0; i < n; i++) {
		// Insert into category 2 array only participants aged 17-19
		if (list[i].age >= 17 && list[i].age <= 19) {
			// Insert participant into category 2
			cat2[k] = &list[i];
			k++; // Increase category 2 array length
		}
	}
	cout << "\nCategory 17-19\n";
	for (int i = 0; i < k; i++) {
		cout << "\nParticipant " << i + 1;
		cout << "\nNumber: " << cat2[i]->num; // Prints the participant's number
		cout << "\nName: " << cat2[i]->name; // Prints the participant's name
		cout << "\nAge: " << cat2[i]->age; // Prints the participant's age
		cout << "\nHip size: " << cat2[i]->hip << "cm"; // Prints the participant's hip size in centimeters
		cout << "\nShoulder size: " << cat2[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
		cout << "\nNeck size: " << cat2[i]->neck << "cm"; // Prints the participant's neck size in centimeters
		cout << "\nCalf size: " << cat2[i]->calf << "cm"; // Prints the participant's calf size in centimeters
		// Checks if the gender is true or false
		if (cat2[i]->gender)
			cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
		else
			cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
	}
	if (!k)
		cout << "No participants found";
	return (k);
}

// Splits participants into category aged 20-22
int splitCategory3(Participant list[], Participant* cat3[], int n, int l) {
	int i; // For counter
	l = 0; // Category 3 array length
	// Go through the whole category 3 array
	for (i = 0; i < n; i++) {
		// Insert into category 3 array only participants aged 22-22
		if (list[i].age >= 20 && list[i].age <= 22) {
			// Insert participant into category 3
			cat3[l] = &list[i];
			l++; // Increase category 3 array length
		}
	}
	cout << "\nCategory 20-22\n";
	for (int i = 0; i < l; i++) {
		cout << "\nParticipant " << i + 1;
		cout << "\nNumber: " << cat3[i]->num; // Prints the participant's number
		cout << "\nName: " << cat3[i]->name; // Prints the participant's name
		cout << "\nAge: " << cat3[i]->age; // Prints the participant's age
		cout << "\nHip size: " << cat3[i]->hip << "cm"; // Prints the participant's hip size in centimeters
		cout << "\nShoulder size: " << cat3[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
		cout << "\nNeck size: " << cat3[i]->neck << "cm"; // Prints the participant's neck size in centimeters
		cout << "\nCalf size: " << cat3[i]->calf << "cm"; // Prints the participant's calf size in centimeters
		// Checks if the gender is true or false
		if (cat3[i]->gender)
			cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
		else
			cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
	}
	if (!l)
		cout << "No participants found";
	return (l);
}

// Splits participants into category aged 23-25
int splitCategory4(Participant list[], Participant* cat4[], int n, int m) {
	int i; // For counter
	m = 0; // Category 4 array length
	// Go through the whole category 4 array
	for (i = 0; i < n; i++) {
		// Insert into category 4 array only participants aged 23-25
		if (list[i].age >= 20 && list[i].age <= 22) {
			// Insert participant into category 4
			cat4[m] = &list[i];
			m++; // Increase category 4 array length
		}
	}
	cout << "\nCategory 23-25\n";
	for (int i = 0; i < m; i++) {
		cout << "\nParticipant " << i + 1;
		cout << "\nNumber: " << cat4[i]->num; // Prints the participant's number
		cout << "\nName: " << cat4[i]->name; // Prints the participant's name
		cout << "\nAge: " << cat4[i]->age;  // Prints the participant's age
		cout << "\nHip size: " << cat4[i]->hip << "cm"; // Prints the participant's hip size in centimeters
		cout << "\nShoulder size: " << cat4[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
		cout << "\nNeck size: " << cat4[i]->neck << "cm"; // Prints the participant's neck size in centimeters
		cout << "\nCalf size: " << cat4[i]->calf << "cm";  // Prints the participant's calf size in centimeters
		// Checks if the gender is true or false
		if (cat4[i]->gender)
			cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
		else
			cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
	}
	if (!m)
		cout << "No participants found";
	return (m);
}

// Print all the winners from the different categories
void printWinners(Participant* cat1[], Participant* cat2[], Participant* cat3[], Participant* cat4[], int j, int k, int l, int m) {
	Participant* temp; // Temporary structure used for bubble sort algorithm
	int top, search, i; // i = for counter, top and search used for sorting algorithm
	// Calculate total score for different participants of different categories
	for (i = 0; i < j; i++)
		cat1[i]->total = (cat1[i]->hip / (cat1[i]->shoulder + cat1[i]->neck + cat1[i]->calf));
	for (i = 0; i < k; i++)
		cat2[i]->total = (cat2[i]->hip / (cat2[i]->shoulder + cat2[i]->neck + cat2[i]->calf));
	for (i = 0; i < l; i++)
		cat3[i]->total = (cat3[i]->hip / (cat3[i]->shoulder + cat3[i]->neck + cat3[i]->calf));
	for (i = 0; i < m; i++)
		cat4[i]->total = (cat4[i]->hip / (cat4[i]->shoulder + cat4[i]->neck + cat4[i]->calf));

	// Bubble sort algorithm to calculate total score descending
	for (top = 0; top < j - 1; top++) {
		for (search = top + 1; search < j; search++) {
			if (cat1[top]->total < cat1[search]->total) {
				temp = cat1[top];
				cat1[top] = cat1[search];
				cat1[search] = temp;
			}
		}
	}

	// Print category 1 total value of 0.54 - 0.62 / Winners
	cout << "\nCategory 14-16\n";
	for (int i = 0; i < j; i++) {
		if (cat1[i]->total > 0.54 && cat1[i]->total < 0.62) {
			cout << "\nNumber: " << cat1[i]->num; // Prints the participant's number
			cout << "\nName: " << cat1[i]->name; // Prints the participant's name
			cout << "\nAge: " << cat1[i]->age; // Prints the participant's age
			cout << "\nHip size: " << cat1[i]->hip << "cm"; // Prints the participant's hip size in centimeters
			cout << "\nShoulder size: " << cat1[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
			cout << "\nNeck size: " << cat1[i]->neck << "cm"; // Prints the participant's neck size in centimeters
			cout << "\nCalf size: " << cat1[i]->calf << "cm"; // Prints the participant's calf size in centimeters
			cout << "\nTotal proportions: " << cat1[i]->total;
			// Checks if the gender is true or false
			if (cat1[i]->gender)
				cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
			else
				cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
		}
	}

	// Bubble sort algorithm to calculate total score ascending of category 1
	for (top = 0; top < j - 1; top++) {
		for (search = top + 1; search < j; search++) {
			if (cat1[top]->total > cat1[search]->total) {
				temp = cat1[top];
				cat1[top] = cat1[search];
				cat1[search] = temp;
			}
		}
	}
	// Print category 1 total value of > 0.63
	for (int i = 0; i < j; i++) {
		if (cat1[i]->total >= 0.63) {
			cout << "\nNumber: " << cat1[i]->num; // Prints the participant's number
			cout << "\nName: " << cat1[i]->name; // Prints the participant's name
			cout << "\nAge: " << cat1[i]->age; // Prints the participant's age
			cout << "\nHip size: " << cat1[i]->hip << "cm"; // Prints the participant's hip size in centimeters
			cout << "\nShoulder size: " << cat1[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
			cout << "\nNeck size: " << cat1[i]->neck << "cm"; // Prints the participant's neck size in centimeters
			cout << "\nCalf size: " << cat1[i]->calf << "cm"; // Prints the participant's calf size in centimeters
			cout << "\nTotal proportions: " << cat1[i]->total;
			// Checks if the gender is true or false
			if (cat1[i]->gender)
				cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
			else
				cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
		}
	}
	// Print category 1 total value of < 0.53
	for (int i = 0; i < j; i++) {
		if (cat1[i]->total <= 0.53) {
			cout << "\nNumber: " << cat1[i]->num; // Prints the participant's number
			cout << "\nName: " << cat1[i]->name; // Prints the participant's name
			cout << "\nAge: " << cat1[i]->age; // Prints the participant's age
			cout << "\nHip size: " << cat1[i]->hip << "cm"; // Prints the participant's hip size in centimeters
			cout << "\nShoulder size: " << cat1[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
			cout << "\nNeck size: " << cat1[i]->neck << "cm"; // Prints the participant's neck size in centimeters
			cout << "\nCalf size: " << cat1[i]->calf << "cm"; // Prints the participant's calf size in centimeters
			cout << "\nTotal proportions: " << cat1[i]->total;
			// Checks if the gender is true or false
			if (cat1[i]->gender)
				cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
			else
				cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
		}
	}

	// Bubble sort algorithm to calculate total score descending of category 2
	for (top = 0; top < k - 1; top++) {
		for (search = top + 1; search < k; search++) {
			if (cat2[top]->total < cat2[search]->total) {
				temp = cat2[top];
				cat2[top] = cat2[search];
				cat2[search] = temp;
			}
		}
	}
	cout << "\nCategory 17-19\n";
	// Print category 2 total value of 0.54 - 0.62 / Winners
	for (int i = 0; i < k; i++) {
		if (cat2[i]->total > 0.54 && cat2[i]->total < 0.62) {
			cout << "\nNumber: " << cat2[i]->num; // Prints the participant's number
			cout << "\nName: " << cat2[i]->name; // Prints the participant's name
			cout << "\nAge: " << cat2[i]->age; // Prints the participant's age
			cout << "\nHip size: " << cat2[i]->hip << "cm"; // Prints the participant's hip size in centimeters
			cout << "\nShoulder size: " << cat2[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
			cout << "\nNeck size: " << cat2[i]->neck << "cm"; // Prints the participant's neck size in centimeters
			cout << "\nCalf size: " << cat2[i]->calf << "cm"; // Prints the participant's calf size in centimeters
			cout << "\nTotal proportions: " << cat2[i]->total;
			// Checks if the gender is true or false
			if (cat2[i]->gender)
				cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
			else
				cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
		}
	}
	// Bubble sort algorithm to calculate total score ascending of category 2
	for (top = 0; top < k - 1; top++) {
		for (search = top + 1; search < k; search++) {
			if (cat2[top]->total > cat2[search]->total) {
				temp = cat2[top];
				cat2[top] = cat2[search];
				cat2[search] = temp;
			}
		}
	}
	// Print category 2 total value of > 0.63
	for (int i = 0; i < k; i++) {
		if (cat2[i]->total >= 0.63) {
			cout << "\nNumber: " << cat2[i]->num; // Prints the participant's number
			cout << "\nName: " << cat2[i]->name; // Prints the participant's name
			cout << "\nAge: " << cat2[i]->age; // Prints the participant's age
			cout << "\nHip size: " << cat2[i]->hip << "cm"; // Prints the participant's hip size in centimeters
			cout << "\nShoulder size: " << cat2[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
			cout << "\nNeck size: " << cat2[i]->neck << "cm"; // Prints the participant's neck size in centimeters
			cout << "\nCalf size: " << cat2[i]->calf << "cm"; // Prints the participant's calf size in centimeters
			cout << "\nTotal proportions: " << cat2[i]->total;
			// Checks if the gender is true or false
			if (cat2[i]->gender)
				cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
			else
				cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
		}
	}
	// Print category 2 total value of < 0.53
	for (int i = 0; i < k; i++) {
		if (cat2[i]->total <= 0.53) {
			cout << "\nNumber: " << cat2[i]->num; // Prints the participant's number
			cout << "\nName: " << cat2[i]->name; // Prints the participant's name
			cout << "\nAge: " << cat2[i]->age; // Prints the participant's age
			cout << "\nHip size: " << cat2[i]->hip << "cm"; // Prints the participant's hip size in centimeters
			cout << "\nShoulder size: " << cat2[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
			cout << "\nNeck size: " << cat2[i]->neck << "cm"; // Prints the participant's neck size in centimeters
			cout << "\nCalf size: " << cat2[i]->calf << "cm"; // Prints the participant's calf size in centimeters
			cout << "\nTotal proportions: " << cat2[i]->total;
			// Checks if the gender is true or false
			if (cat2[i]->gender)
				cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
			else
				cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
		}
	}

	//

	cout << "\nCategory 20-22\n";
	// Bubble sort algorithm to calculate total score descending of category 3
	for (top = 0; top < l - 1; top++) {
		for (search = top + 1; search < l; search++) {
			if (cat3[top]->total < cat3[search]->total) {
				temp = cat3[top];
				cat3[top] = cat3[search];
				cat3[search] = temp;
			}
		}
	}
	// Print category 3 total value of 0.54 - 0.62 / Winners
	for (int i = 0; i < l; i++) {
		if (cat3[i]->total > 0.54 && cat3[i]->total < 0.62) {
			cout << "\nNumber: " << cat3[i]->num; // Prints the participant's number
			cout << "\nName: " << cat3[i]->name; // Prints the participant's name
			cout << "\nAge: " << cat3[i]->age; // Prints the participant's age
			cout << "\nHip size: " << cat3[i]->hip << "cm"; // Prints the participant's hip size in centimeters
			cout << "\nShoulder size: " << cat3[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
			cout << "\nNeck size: " << cat3[i]->neck << "cm"; // Prints the participant's neck size in centimeters
			cout << "\nCalf size: " << cat3[i]->calf << "cm"; // Prints the participant's calf size in centimeters
			cout << "\nTotal proportions: " << cat3[i]->total;
			// Checks if the gender is true or false
			if (cat3[i]->gender)
				cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
			else
				cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
		}
	}
	// Bubble sort algorithm to calculate total score ascending of category 3
	for (top = 0; top < l - 1; top++) {
		for (search = top + 1; search < l; search++) {
			if (cat3[top]->total > cat3[search]->total) {
				temp = cat3[top];
				cat3[top] = cat3[search];
				cat3[search] = temp;
			}
		}
	}
	// Print category 3 total value of > 0.63
	for (int i = 0; i < l; i++) {
		if (cat3[i]->total >= 0.63) {
			cout << "\nNumber: " << cat3[i]->num; // Prints the participant's number
			cout << "\nName: " << cat3[i]->name; // Prints the participant's name
			cout << "\nAge: " << cat3[i]->age; // Prints the participant's age
			cout << "\nHip size: " << cat3[i]->hip << "cm"; // Prints the participant's hip size in centimeters
			cout << "\nShoulder size: " << cat3[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
			cout << "\nNeck size: " << cat3[i]->neck << "cm"; // Prints the participant's neck size in centimeters
			cout << "\nCalf size: " << cat3[i]->calf << "cm";  // Prints the participant's calf size in centimeters
			cout << "\nTotal proportions: " << cat3[i]->total;
			// Checks if the gender is true or false
			if (cat3[i]->gender)
				cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
			else
				cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
		}
	}
	// Print category 3 total value of < 0.53
	for (int i = 0; i < l; i++) {
		if (cat3[i]->total <= 0.53) {
			cout << "\nNumber: " << cat3[i]->num; // Prints the participant's number
			cout << "\nName: " << cat3[i]->name; // Prints the participant's name
			cout << "\nAge: " << cat3[i]->age; // Prints the participant's age
			cout << "\nHip size: " << cat3[i]->hip << "cm"; // Prints the participant's hip size in centimeters
			cout << "\nShoulder size: " << cat3[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
			cout << "\nNeck size: " << cat3[i]->neck << "cm"; // Prints the participant's neck size in centimeters
			cout << "\nCalf size: " << cat3[i]->calf << "cm"; // Prints the participant's calf size in centimeters
			cout << "\nTotal proportions: " << cat3[i]->total;
			// Checks if the gender is true or false
			if (cat3[i]->gender)
				cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
			else
				cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
		}
	}

	//

	cout << "\nCategory 23-25\n";
	// Bubble sort algorithm to calculate total score descending of category 4
	for (top = 0; top < m - 1; top++) {
		for (search = top + 1; search < m; search++) {
			if (cat4[top]->total < cat4[search]->total) {
				temp = cat1[top];
				cat1[top] = cat1[search];
				cat1[search] = temp;
			}
		}
	}
	// Print category 4 total value of 0.54 - 0.62 / Winners
	for (int i = 0; i < m; i++) {
		if (cat4[i]->total > 0.54 && cat4[i]->total < 0.62) {
			cout << "\nNumber: " << cat4[i]->num; // Prints the participant's number
			cout << "\nName: " << cat4[i]->name; // Prints the participant's name
			cout << "\nAge: " << cat4[i]->age; // Prints the participant's age
			cout << "\nHip size: " << cat4[i]->hip << "cm"; // Prints the participant's hip size in centimeters
			cout << "\nShoulder size: " << cat4[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
			cout << "\nNeck size: " << cat4[i]->neck << "cm"; // Prints the participant's neck size in centimeters
			cout << "\nCalf size: " << cat4[i]->calf << "cm"; // Prints the participant's calf size in centimeters
			cout << "\nTotal proportions: " << cat4[i]->total;
			// Checks if the gender is true or false
			if (cat4[i]->gender)
				cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
			else
				cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
		}
	}
	// Bubble sort algorithm to calculate total score ascending of category 4
	for (top = 0; top < m - 1; top++) {
		for (search = top + 1; search < m; search++) {
			if (cat4[top]->total > cat4[search]->total) {
				temp = cat4[top];
				cat4[top] = cat1[search];
				cat4[search] = temp;
			}
		}
	}
	// Print category 4 total value of > 0.63
	for (int i = 0; i < m; i++) {
		if (cat4[i]->total >= 0.63) {
			cout << "\nNumber: " << cat4[i]->num; // Prints the participant's number
			cout << "\nName: " << cat4[i]->name; // Prints the participant's name
			cout << "\nAge: " << cat4[i]->age; // Prints the participant's age
			cout << "\nHip size: " << cat4[i]->hip << "cm"; // Prints the participant's hip size in centimeters
			cout << "\nShoulder size: " << cat4[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
			cout << "\nNeck size: " << cat4[i]->neck << "cm"; // Prints the participant's neck size in centimeters
			cout << "\nCalf size: " << cat4[i]->calf << "cm"; // Prints the participant's calf size in centimeters
			cout << "\nTotal proportions: " << cat4[i]->total;
			// Checks if the gender is true or false
			if (cat4[i]->gender)
				cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
			else
				cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
		}
	}
	// Print category 4 total value of < 0.53
	for (int i = 0; i < m; i++) {
		if (cat4[i]->total <= 0.53) {
			cout << "\nNumber: " << cat4[i]->num; // Prints the participant's number
			cout << "\nName: " << cat4[i]->name; // Prints the participant's name
			cout << "\nAge: " << cat4[i]->age; // Prints the participant's age
			cout << "\nHip size: " << cat4[i]->hip << "cm"; // Prints the participant's hip size in centimeters
			cout << "\nShoulder size: " << cat4[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
			cout << "\nNeck size: " << cat4[i]->neck << "cm"; // Prints the participant's neck size in centimeters
			cout << "\nCalf size: " << cat4[i]->calf << "cm"; // Prints the participant's calf size in centimeters
			cout << "\nTotal proportions: " << cat4[i]->total;
			// Checks if the gender is true or false
			if (cat4[i]->gender)
				cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
			else
				cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
		}
	}
}

// Audit functions menu
int auditmenu() {
	int ch; // Audit functions choice
	// Repeat until choice is one of the functions
	do {
		cout << "\n\n \t Query menu";
		cout << "\n1. Sort by age";
		cout << "\n2. Print youngest male and female participants";
		cout << "\n3. Print participants with biggest shoulder width";
		cout << "\n4. Back\n";
		cin >> ch; // Enter your choice
	} while (ch < 1 || ch>5);
	return (ch); // Return choice to claler function
}

// Sort participants by age ascending
void sortByAge(Participant* listSort[], int n) {
	Participant* temp; // Temporary structure used for bubble sort algorithm
	int top, search, i; // i = for counter, top and search used for sorting algorithm
	// Bubble sort algorithm sorted by ascending by age
	for (top = 0; top < n - 1; top++) {
		for (search = top + 1; search < n; search++) {
			if (listSort[top]->age > listSort[search]->age) {
				temp = listSort[top];
				listSort[top] = listSort[search];
				listSort[search] = temp;
			}
		}
	}
	// Print all participants
	for (i = 0; i < n; i++) {
		cout << "\nNumber: " << listSort[i]->num; // Prints the participant's number
		cout << "\nName: " << listSort[i]->name; // Prints the participant's name
		cout << "\nAge: " << listSort[i]->age; // Prints the participant's age
		cout << "\nHip size: " << listSort[i]->hip << "cm"; // Prints the participant's hip size in centimeters
		cout << "\nShoulder size: " << listSort[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
		cout << "\nNeck size: " << listSort[i]->neck << "cm"; // Prints the participant's neck size in centimeters
		cout << "\nCalf size: " << listSort[i]->calf << "cm"; // Prints the participant's calf size in centimeters
		// Checks if the gender is true or false
		if (listSort[i]->gender)
			cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
		else
			cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
	}
}

// Prints the youngest male and female participants
void printYoungest(Participant* listSort[], int n) {
	Participant* temp; // Temporary structure used for bubble sort algorithm
	int top, search, i; // i = for counter, top and search used for sorting algorithm
	// Bubble sort algorithm
	for (top = 0; top < n - 1; top++) {
		for (search = top + 1; search < n; search++) {
			if (listSort[top]->age > listSort[search]->age) {
				temp = listSort[top];
				listSort[top] = listSort[search];
				listSort[search] = temp;
			}
		}
	}
	// Print participants
	for (i = 0; i < n; i++) {
		if (listSort[i]->gender) { // If gender is male
			cout << "\nNumber: " << listSort[i]->num; // Prints the participant's number
			cout << "\nName: " << listSort[i]->name; // Prints the participant's name
			cout << "\nAge: " << listSort[i]->age; // Prints the participant's age
			cout << "\nHip size: " << listSort[i]->hip << "cm"; // Prints the participant's hip size in centimeters
			cout << "\nShoulder size: " << listSort[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
			cout << "\nNeck size: " << listSort[i]->neck << "cm"; // Prints the participant's neck size in centimeters
			cout << "\nCalf size: " << listSort[i]->calf << "cm"; // Prints the participant's calf size in centimeters
			// Checks if the gender is true or false
			if (listSort[i]->gender)
				cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
			else
				cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
			break; // Stop the for loop if a male participant is found
		}
	}
	for (i = 0; i < n; i++) {
		if (!listSort[i]->gender) { // If gender is female
			cout << "\nNumber: " << listSort[i]->num; // Prints the participant's number
			cout << "\nName: " << listSort[i]->name; // Prints the participant's name
			cout << "\nAge: " << listSort[i]->age; // Prints the participant's age
			cout << "\nHip size: " << listSort[i]->hip << "cm"; // Prints the participant's hip size in centimeters
			cout << "\nShoulder size: " << listSort[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
			cout << "\nNeck size: " << listSort[i]->neck << "cm"; // Prints the participant's neck size in centimeters
			cout << "\nCalf size: " << listSort[i]->calf << "cm"; // Prints the participant's calf size in centimeters
			// Checks if the gender is true or false
			if (listSort[i]->gender)
				cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
			else
				cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
			break; // Stop the loop if a female participant is found
		}
	}
}

// Print participants sorted by shoulder size descending
void sortByShoulder(Participant* listSort[], int n) {
	Participant* temp; // Temporary structure used for bubble sort algorithm
	int top, search, i; // i = for counter, top and search used for sorting algorithm
	// Bubble sort algorithm
	for (top = 0; top < n - 1; top++) {
		for (search = top + 1; search < n; search++) {
			if (listSort[top]->shoulder < listSort[search]->shoulder) {
				temp = listSort[top];
				listSort[top] = listSort[search];
				listSort[search] = temp;
			}
		}
	}
	// Print all participants
	for (i = 0; i < n; i++) {
		cout << "\nNumber: " << listSort[i]->num; // Prints the participant's number
		cout << "\nName: " << listSort[i]->name; // Prints the participant's name
		cout << "\nAge: " << listSort[i]->age; // Prints the participant's age
		cout << "\nHip size: " << listSort[i]->hip << "cm"; // Prints the participant's hip size in centimeters
		cout << "\nShoulder size: " << listSort[i]->shoulder << "cm"; // Prints the participant's shoulder size in centimeters
		cout << "\nNeck size: " << listSort[i]->neck << "cm"; // Prints the participant's neck size in centimeters
		cout << "\nCalf size: " << listSort[i]->calf << "cm"; // Prints the participant's calf size in centimeters
		// Checks if the gender is true or false
		if (listSort[i]->gender)
			cout << "\nGender: Male\n"; // If the gender is true, prints that the gender is male
		else
			cout << "\nGender: Female\n"; // If the gender is false, prints that the gender is female
	}
}

// The main function of the program
int main() {
	char ans = 'y'; // Choice for creating a new participant
	int choice; // Choice for function selection
	int n = 0, j = 0, k = 0, l = 0, m = 0; // Array lengths
	Participant list[30]; // Main array
	Participant* listSort[30]; // Array used for sorting
	Participant* cat1[30]; // Array used for category 1
	Participant* cat2[30]; // Array used for category 2
	Participant* cat3[30]; // Array used for category 3
	Participant* cat4[30]; // Array used for category 4
	n = loadFile(list, listSort, n); // Load data from data file
	// Repeat until choice is 7
	do {
		choice = menu(); // Choose a function
		// Calculate your choice
		switch (choice) {
		case 1:
			// Repeat until choice is no
			do {
				addParticipant(list, listSort, n); // Add a new participant
				n++; // Increase array length by one
				saveFile(list, n); // Save data in data file
				cout << "\n One more? [Y/N]: ";
				cin >> ans; // Enter your choice
			} while (!(ans == 'N' || ans == 'n')); // Lowercase and uppercase accepted
			break; // End case 1
		case 2:
			n = addParticipantList(list, listSort, n); // Add a list of participants and change array length to returned variable
			saveFile(list, n); // Save data in data file
			break; // End case 2
		case 3:
			printAll(list, n); // Print all participants
			break; // End case 3
		case 4:
			j = splitCategory1(list, cat1, n, j); // Split participants into category 14-16
			k = splitCategory2(list, cat2, n, k); // Split participants into category 17-19
			l = splitCategory3(list, cat3, n, l); // Split participants into category 20-22
			m = splitCategory4(list, cat4, n, m); // Split participants into category 23-25
			break; // End case 4
		case 5:
			printWinners(cat1, cat2, cat3, cat4, j, k, l, m); // Print the winners of the competition
			break; // End case 5
		case 6:
			int auchoice; // Choice for audit menu functions
			// Repeat until choice is 4
			do {
				auchoice = auditmenu(); // Choose an audit menu function
				// Calculate audit menu choice
				switch (auchoice) {
				case 1:
					sortByAge(listSort, n); // Sort participants by age ascending
					break; // End case 1
				case 2:
					printYoungest(listSort, n); // Print youngest male and female participants
					break; // End case 2
				case 3:
					sortByShoulder(listSort, n); // Print participants by shoulder size descending
					break; // End case 3
				case 4:
					// Exits the audit menu
					break; // End case 4
				}
			} while (auchoice != 4);
			break; // End case 6
		case 7:
			saveFile(list, n); // Saves data in data file
			break; // End case 7
		}
	} while (choice != 7);
	system("pause"); // Pause console
	return 0; // Return in order to end program
}