//Rebecca Norwood
//Email: norwo009@cougars.csusm.edu
//Student ID: 200430599

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct Node{
	int data; 
	Node* LC; 
	Node* RC; 
};

//=====================================

Node* NewNode(int data); //Create new node
Node* leftMostNode(Node* node); 
void PrintPreOrder(Node* root);
void PrintInOrder(Node* root); 
void PrintPostOrder(Node* root); 

//=====================================

//Insert data into tree
Node* Insert(Node* root, int data)
{
	if(root == NULL){
		root = NewNode(data); 
	}
	else if(data < root->data){
		root->LC = Insert(root->LC, data); 
	}
	else{
		root->RC = Insert(root->RC, data); 
	}
	
	return root; 
}

//Function to create new node
Node* NewNode(int data)
{
	Node* newNode = new Node; 
	newNode->data = data; 
	newNode->LC = newNode->RC = NULL; 
	
	return newNode; 
}

void PrintPreOrder(Node* root)
{
	//Pre Order, print root, then left, then right 
	if(root != NULL)
	{
		cout << root->data << "\t"; 
		PrintPreOrder(root->LC);
		PrintPreOrder(root->RC);
	}
}

void PrintInOrder(Node* root)
{
	//In Order, print in ascending order: left 
	if (root == NULL)
		return;
	PrintInOrder(root->LC);
	cout << root->data << "\t";
	PrintInOrder(root->RC);
}

void PrintPostOrder(Node* root) 
{
	//Post Order: left, right, then print 
	if(root != NULL)
	{
		PrintPostOrder(root->LC);
		PrintPostOrder(root->RC);
		cout << root->data << "\t"; 
	}
}

//Search binary tree, if key found return pointer, else return NULL
Node* search(Node* root, int key)
{
	//If root isn't in tree or if found is root node, return root
	if(root == NULL || root->data == key){
		return root; 
	}
	//Search left side of tree if number is less than root node
	else if(key < root->data){
		return search(root->LC, key); 
	}
	//Last case: search right side if number is greater than root node
	else{
		return search(root->RC, key); 
	}
			
}


Node* remove(Node* root, int key)
{
	// base case
    if (root == NULL){
        return root;
	}
    // If the key to be deleted is 
    // smaller than the root's, then it's to the left 
    if (key < root->data){
        root->LC = remove(root->LC, key);
	}
    // If the key to be deleted is
    // greater than the root's, then it's to the right 
    else if (key > root->data){
        root->RC = remove(root->RC, key);
	}
   
    else {
        // node with only one child or no child
        if (root->LC == NULL) {
            Node* temp = root->RC;
            free(root);
            return temp;
        }
        else if (root->RC == NULL) {
            Node* temp = root->LC;
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor
        Node* temp = leftMostNode(root->RC);
 
        // Copy the inorder successor's content to this node
        root->data = temp->data;
 
        // Delete the inorder successor
        root->RC = remove(root->RC, temp->data);
    }
    return root;
}

Node* leftMostNode(Node* node)
{
	Node* curr = node; 
	while(curr->RC != NULL){
		curr = curr->RC; 
		return curr; 
	}
}

int RandomKey(vector<int> input)
{
	srand(time(NULL)); 
	
	int key = rand() % input.size(); 
	
	return input[key];
}

void Display(Node* Root)
{
	cout << "\nIn Order\t"; 
	PrintInOrder(Root); 
	cout << "\n"; 
	cout << "Pre Order\t"; 
	PrintPreOrder(Root); 
	cout << "\n"; 
	cout << "Post Order\t"; 
	PrintPostOrder(Root); 
}


int main()
{
	Node* Root = NULL; 
	
	vector<int> userInput; 
	
	cout << "Enter numbers seperated by a space" << endl; 
	int i = 0; 
	
	while (true){
		cin >> i; 
		userInput.push_back(i); 
		Root = Insert(Root, i); //Insert to tree
		if(cin.peek() == '\n'){ //When new line is found end insertion 
			break;
		}
	}
	
	Display(Root); 
	
	
	int nodetobeDeleted = RandomKey(userInput); 
	
	cout << "\n\nRandom Node to be Deleted " << nodetobeDeleted << endl; 
	remove(Root, nodetobeDeleted); 
	
		
	Display(Root); 
	
}
