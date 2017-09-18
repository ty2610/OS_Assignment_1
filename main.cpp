#include <iostream>
#include <string>

using namespace std;

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

void CalculateStudentAverage(void *object, double *avg);

bool isANumber(string *input, bool canHaveFrac);

int main(int argc, char **argv) {
    Student s;
    string id;
    string assignmentCount;
    string firstName;
    string lastName;
    double avg = 0.0;
    //boolean had an error so I looked up this site and realized that c/c++ uses bool
    //http://www.learncpp.com/cpp-tutorial/26-boolean-values/
    bool valid = false;
    //looked up basic user input
    //http://www.cplusplus.com/doc/tutorial/basic_io/
    cout << "Please enter the student's id number: ";
    //make sure to do negative number checking
    while(!valid) {
        cin >> id;
        if(isANumber(&id,false)){
            valid = true;
        } else {
            cout << "Sorry, I can not understand the answer " << id << ". Please enter the student's id number: ";
        }
    }

    valid = false;

    cout << "Please enter the student's first name: ";
    cin >> firstName;
    cout << "Please enter the student's last name: ";
    cin >> lastName;
    cout << "Please enter how many assignments were graded: ";
    while(!valid) {
        cin >> assignmentCount;
        if(isANumber(&assignmentCount,false)){
            valid = true;
        } else {
            cout << "Sorry, I can not understand the answer " << assignmentCount << ". Please how many assignments were graded: ";
        }
    }

    valid = false;

    s.id = stoi(id);
    // https://stackoverflow.com/questions/7352099/stdstring-to-char
    // this is used to switch between string and c*
    s.f_name = &firstName[0u];
    s.l_name = &lastName[0u];
    s.n_assignments = stoi(assignmentCount);
    // had to google a way to change a string to dec, and for future swapping of string into double
    // http://www.cplusplus.com/reference/string/stoi/

    double assignmentScore;

    for(int i=0; i<stoi(assignmentCount); i++){
        cout << "Please enter grade for assignment " << i << ": ";
        cin >> assignmentScore;
        while(!valid) {
            cin >> assignmentScore;
            if(isANumber(&assignmentCount,true)){
                valid = true;
            } else {
                cout << "Sorry, I can not understand the answer " << assignmentScore << ". Please enter the student's id number: ";
            }
        }
    }


    //CalculateStudentAverage(,&avg);
    //cout << id << " " << firstName << " " << lastName << " " << assignmentCount << endl;
    return 0;
}

bool isANumber(string *input, bool canHaveFrac){
    int periodCount = 0;
    for(int i=0; i<input->length();i++) {
        if(!isdigit(input->at(i))){
            if(input->at(i)=='.' && periodCount == 0 && canHaveFrac){
                periodCount++;
            } else {
                return false;
            }
        }
    }
    return true;
}

void CalculateStudentAverage(void *object, double *avg) {

}

/*int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}*/