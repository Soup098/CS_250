

/*
* TODO:
* *fix case 3 to show prereqs
* *comment all methods, classes and structures
* *Title
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Course {
    string Id;
    string Name;
    vector<string> preReqs;
};

struct Node {
    Course course;
    Node* left;
    Node* right;

    //default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    //initialize with course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

class BinaryTree {//COMMENT HERE
    private:

        Node* root;
        void inOrder(Node* node);
    public:
        BinaryTree();
        void InOrder();
        void Insert(const Course& course);
        Course* Search(const string& courseId);
};

BinaryTree::BinaryTree() : root(nullptr) {}//COMMENT HERE

void BinaryTree::InOrder() {//COMMENT HERE
    inOrder(root);
}

void BinaryTree::inOrder(Node* node) {//COMMENT HERE
    if (node != nullptr) {
        inOrder(node->left);
        cout << endl;
        if (!node->course.preReqs.empty()) {
            cout << "Course ID: " << node->course.Id << ", Course Name: " << node->course.Name << ", Prerequisites: ";
            for (const string& prereq : node->course.preReqs) {
                cout << prereq << " ";
            }  
        }
        else {
            cout << "Course ID: " << node->course.Id << ", Course Name: " << node->course.Name;
        }
        inOrder(node->right);
    }
    
}

void BinaryTree::Insert(const Course& course) {//COMMENT HERE
    Node* newNode = new Node(course);

    if (root == nullptr) {
        root = newNode;
        return;
    }

    Node* current = root;
    while (current != nullptr) {
        if (course.Id < current->course.Id) {
            if (current->left == nullptr) {
                current->left = newNode;
                return;
            }
            current = current->left;
        }
        else {
            if (current->right == nullptr) {
                current->right = newNode;
                return;
            }
            current = current->right;
        }
    }
}

Course* BinaryTree::Search(const string& courseId) {// COMMENT HERE
    Node* current = root;
    
    while (current != nullptr) {
        if (courseId == current->course.Id) {
            return &(current->course);
        }
        else if (courseId < current->course.Id) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return nullptr;
}

void loadCourses(BinaryTree& tree, const string& filename) {// COMMENT HERE
    ifstream file(filename);
    string line;

    if (file.is_open()) {//COMMENT HERE
        while (getline(file, line)) {
            Course newCourse;
            istringstream iss(line);
            string courseId;
            string courseName;
            string preReq;

            getline(iss, courseId, ',');
            newCourse.Id = courseId;
            getline(iss, courseName, ',');
            newCourse.Name = courseName;

            while (getline(iss, preReq, ',')) {
                newCourse.preReqs.push_back(preReq);
            }

            tree.Insert(newCourse);
        }
        file.close();
    }
    else {
        cerr << "file not opened" << "Course.txt" << endl;
    }
}

int main() {
    BinaryTree tree;// create new binary tree object called tree
    int choice = 0;//initiate the users choice at 0

    while (choice != 4) {// menu for user choices
        cout << endl;
        cout << "Please make a selection" << endl;
        cout << "1: Load Data Structure" << endl;
        cout << "2: Print Course List" << endl;
        cout << "3: Print Course" << endl;
        cout << "4: Exit Program" << endl;
        
        cin >> choice;

        switch (choice){
            case 1:// user choice number one loads the courses from the file into the program.
                loadCourses(tree, "Courses.txt");
                cout << endl;
                cout << "File Loaded" << endl;
                break;
            case 2: // user choice number two prints out all of the courses in the file
                tree.InOrder();
                break;
            case 3:// user choice number 3 takes the course ID as an input and outputs the course in question
            {
                string courseId;
                cout << "Enter ID for course you wish to see: ";
                cin >> courseId;
                Course* courseChoice = tree.Search(courseId);
                if (courseChoice != nullptr) {
                    cout << endl;
                    cout << "Course Found" << endl;
                    cout << "ID: " << courseChoice->Id << " " << "Name: " << courseChoice->Name << " " << endl;
                }
                else {
                    cout << "Course not found..." << endl;
                }
            }
                
            break;
            case 4: // user choice 4 outputs a farewall message and breaks the while loop, exiting the program
                cout << endl;
                cout << "Have a nice day" << endl;
                break;
        }
    }
}

