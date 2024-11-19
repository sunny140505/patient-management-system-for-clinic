#include <bits/stdc++.h>
using namespace std;

class patient
{
public:
    string firstname;
    string lastname;
    string blood;
    string problem;
    long long number;
    int age;
    char gender;
    bool emergency;

    patient() : firstname(""), lastname(""), blood(""), problem(""), number(0), age(0), gender(' '), emergency(false) {}
    patient(long long num, const string &fn, const string &ln, const string &bg, const string &pb, int umra, char g, bool em)
    {
        number = num;
        firstname = fn;
        lastname = ln;
        blood = bg;
        problem = pb;
        age = umra;
        gender = g;
        emergency = em;
    }
};

class patientqueue
{
    queue<patient> patients;
    queue<patient> emergencypatients;
    unordered_map<long long, patient> patientMap;

public:
    void saveToFile(const patient &p)
    {
        ofstream file;
        file.open("patients.csv", ios::app);
        if (file.is_open())
        {
            file << p.number << "," << p.firstname << "," << p.lastname << "," << p.blood
                 << "," << p.age << "," << p.gender << "," << p.problem
                 << "," << p.emergency << endl;
            file.close();
        }
        else
        {
            cout << "Unable to open file to save patient data." << endl;
        }
    }

    void loadFromFile()
    {
        ifstream file("patients.csv");
        string line;
        if (file.is_open())
        {
            while (getline(file, line))
            {
                stringstream ss(line);
                string token;
                vector<string> data;
                while (getline(ss, token, ','))
                {
                    data.push_back(token);
                }
                if (data.size() == 8)
                {
                    long long number = stoll(data[0]);
                    string firstname = data[1];
                    string lastname = data[2];
                    string blood = data[3];
                    int age = stoi(data[4]);
                    char gender = data[5][0];
                    string problem = data[6];
                    bool emergency = stoi(data[7]);

                    patient p(number, firstname, lastname, blood, problem, age, gender, emergency);
                    if (emergency)
                    {
                        emergencypatients.push(p);
                    }
                    else
                    {
                        patients.push(p);
                    }
                    patientMap[number] = p;
                }
            }
            file.close();
        }
        else
        {
            cout << "Unable to open file to load patient data." << endl;
        }
    }

    void addpatient()
    {
        cout << "\nEnter Patient details\n";
        string firstname, lastname, blood, problem;
        long long number;
        int age;
        char gender;
        bool emergency;
        cout << "First Name: ";
        cin >> firstname;
        cout << "Last Name: ";
        cin >> lastname;

        while (true)
        {
            cout << "Blood Group (A+, A-, B+, B-, O+, O-, AB+, AB-): ";
            cin >> blood;
            if (blood == "A+" || blood == "A-" || blood == "B+" || blood == "B-" || blood == "O+" || blood == "O-" || blood == "AB+" || blood == "AB-")
                break;
            cout << "Invalid Blood Group. Try Again.\n";
        }

        cout << "Gender (m/f/o): ";
        cin >> gender;

        while (true)
        {
            cout << "Age: ";
            cin >> age;
            if (age > 0 && age < 120)
                break;
            cout << "Invalid Age. Try Again.\n";
        }

        cout << "Mobile Number: ";
        cin >> number;
        cout << "Emergency? (1 for yes, 0 for no): ";
        cin >> emergency;
        cout << "What's troubling you?: ";
        cin >> problem;

        patient newpatient(number, firstname, lastname, blood, problem, age, gender, emergency);
        if (emergency)
        {
            emergencypatients.push(newpatient);
            cout << "Emergency Patient Added\n";
        }
        else
        {
            patients.push(newpatient);
            cout << "Patient Added\n";
        }
        saveToFile(newpatient);
        patientMap[number] = newpatient;
    }

    void takepatienttodoctor()
    {
        if (!emergencypatients.empty())
        {
            patient p = emergencypatients.front();
            emergencypatients.pop();

            cout << "Emergency Patient to operate: " << p.firstname << " " << p.lastname << "\n";
        }
        else if (!patients.empty())
        {
            patient p = patients.front();
            patients.pop();

            cout << "Patient to operate: " << p.firstname << " " << p.lastname << "\n";
        }
        else
        {
            cout << "No patients to operate\n";
        }
    }

    void displayPatient(const patient &i)
    {
        cout << "Patient data:\n"
             << " First Name: " << i.firstname
             << "\n Last Name: " << i.lastname
             << "\n Gender: " << i.gender
             << "\n Age: " << i.age
             << "\n Blood Group: " << i.blood
             << "\n Mobile Number: " << i.number
             << "\n Problem: " << i.problem << "\n";
    }

    void patientlist()
    {
        cout << "\nEmergency Patients:\n";
        if (emergencypatients.empty())
        {
            cout << "No Emergency Patients\n";
        }
        else
        {
            queue<patient> tempQueue = emergencypatients;
            while (!tempQueue.empty())
            {
                displayPatient(tempQueue.front());
                cout<<endl;
                tempQueue.pop();
            }
        }

        cout << "\nPatients:\n";
        if (patients.empty())
        {
            cout << "No Patients\n";
        }
        else
        {
            queue<patient> tempQueue = patients;
            while (!tempQueue.empty())
            {
                displayPatient(tempQueue.front());
                cout<<endl;
                tempQueue.pop();
            }
        }
    }

    void listcurrentqueue()
    {
        cout << "\nCurrent Queue:\n";
        cout << "\nEmergency Patients:\n";
        int s = 1;
        if (emergencypatients.empty())
        {
            cout << "\nNo Emergency Patients\n";
        }
        else
        {
            queue<patient> tempQueue = emergencypatients;
            while (!tempQueue.empty())
            {
                
                patient p = tempQueue.front();
                cout<<s<<". ";
                cout<<p.firstname<<" "<<p.lastname<<"("<<p.number<<")"<<endl;
                tempQueue.pop();
                s++;
            }
        }

        cout << "\nPatients:\n";
        if (patients.empty())
        {
            cout << "\nNo Patients\n";
        }
        else
        {
            queue<patient> tempQueue = patients;
            while (!tempQueue.empty())
            {
                
                patient p = tempQueue.front();
                cout<<s<<". ";
                cout<<p.firstname<<" "<<p.lastname<<"("<<p.number<<")"<<endl;
                tempQueue.pop();
                s++;
            }
        }
    }

    void searchmobile(long long number) 
    {
        
        for (const auto& pair : patientMap) 
        {
            if (pair.first == number) 
            {
                cout << "Patient found:\n";
                displayPatient(pair.second);
                return; 
            }
        }
        cout << "\nNo patient found with entered mobile number\n";
    }
};

int main()
{
    patientqueue clinic;
    clinic.loadFromFile();

    int choice;
    do
    {
        cout << "\n----Welcome----\n\n\n CLINIC MENU\n";
        cout << "[1] Add patient\n";
        cout << "[2] Take patient to Doctor\n";
        cout << "[3] Display list of all patients\n";
        cout << "[4] Show current queue\n";
        cout << "[5] Search patient by mobile number\n";
        cout << "[6] Exit\n";
        cout << "Please enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            clinic.addpatient();
            break;
        case 2:
            clinic.takepatienttodoctor();
            break;
        case 3:
            clinic.patientlist();
            break;
        case 4:
            clinic.listcurrentqueue();
            break;
        case 5:
        {
            long long number;
            cout << "Enter mobile number to search: ";
            cin >> number;
            clinic.searchmobile(number);
            break;
        }
        }
        if (choice < 1 || choice > 6)
        {
            cout<<"Invalide choice."<<endl;
        }
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    } while (choice != 6);
    
    cout << "Thank you!\n";
    return 0;
}