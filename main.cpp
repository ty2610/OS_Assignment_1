#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

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

string leadingZeroCount(string *number);

int main(int argc, char **argv) {
    Student s;
    string id;
    string assignmentCount;
    string firstName;
    string lastName;
    double avg = 0.0;
    string leadingZeros;
    string assignmentScore;
    //boolean had an error so I looked up this site and realized that c/c++ uses bool
    //http://www.learncpp.com/cpp-tutorial/26-boolean-values/
    bool valid = false;
    //looked up basic user input
    //http://www.cplusplus.com/doc/tutorial/basic_io/
    cout << "Please enter the student's id number: ";
    while(!valid) {
        getline(cin, id);
        if(isANumber(&id,false)){
            valid = true;
        } else {
            cout << "Sorry, I can not understand the answer " << id << ". Please enter the student's id number: ";
        }
    }

    leadingZeros = leadingZeroCount(&id);

    valid = false;

    //Do I need any name error checking?
    cout << "Please enter the student's first name: ";
    getline(cin, firstName);
    cout << "Please enter the student's last name: ";
    getline(cin, lastName);
    cout << "Please enter how many assignments were graded: ";
    while(!valid) {
        getline(cin, assignmentCount);
        if(isANumber(&assignmentCount,false)){
            if(stoi(assignmentCount)>0) {
                valid = true;
            } else {
                cout << "You must enter an assignment counter larger than 0. Please enter how many assignments were graded:";
            }
        } else {
            cout << "Sorry, I can not understand the answer " << assignmentCount << ". Please enter how many assignments were graded: ";
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

    double *scores =  new double[s.n_assignments];

    for(int i=1; i<stoi(assignmentCount)+1; i++){
        cout << "Please enter the grade for assignment " << i << ": ";
        while(!valid) {
            getline(cin, assignmentScore);
            if(isANumber(&assignmentScore,true)){
                if(stod(assignmentScore)>100){
                    cout << "Sorry, the score " << assignmentScore << " must be less than 100. " << "Please enter the grade for assignment " << i << ": ";
                } else {
                    scores[i - 1] = stod(assignmentScore);
                    valid = true;
                }
            } else {
                cout << "Sorry, I can not understand the answer " << assignmentScore << ". " << "Please enter the grade for assignment " << i << ": ";
            }
        }
        valid = false;
    }

    s.grades = scores;

    CalculateStudentAverage(&s,&avg);
    cout << endl;
    if (s.id == 0) {
        cout << "Student: " << s.f_name << " " << s.l_name << " [" << leadingZeros << "]" << endl;
    } else {
        cout << "Student: " << s.f_name << " " << s.l_name << " [" << leadingZeros << s.id << "]" << endl;
    }
    // figured out how to round with this
    // https://stackoverflow.com/questions/14596236/rounding-to-2-decimal-points
    cout << "  Average grade: " << fixed << setprecision(1) << floor(avg*10+0.5)/10 ;
    return 0;
}

bool isANumber(string *input, bool canHaveFrac){
    int periodCount = 0;
    for(int i=0; i<input->length();i++) {
        if(!isdigit(input->at(i))){
            if(input->at(i)=='.' && periodCount == 0 && canHaveFrac && input->length()>1){
                periodCount++;
            } else {
                return false;
            }
        }
    }
    // the code should never get here, but it is a safe check to have
    // to catch some one off logic.
    if(stod(*input)<0){
        return false;
    }
    return true;
}

string leadingZeroCount(string *number){
    string ret;
    for(int i=0; i<number->length();i++){
        if(number->at(i)=='0'){
            ret += "0";
            if(i+1<number->length()){
                if(number->at(i+1)!='0'){
                    return ret;
                }
            }
        }
    }
    return ret;
}

void CalculateStudentAverage(void *object, double *avg) {
    Student student = *(Student*)object;
    double sum = 0;
    for(int i=0;i<student.n_assignments;i++) {
        sum += student.grades[i];
    }
    *avg = sum/student.n_assignments;
}