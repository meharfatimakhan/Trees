#include <iostream>
using namespace std;

class node
{
	friend class stack;
	friend class queue;
	friend class linkedList;
	friend class BST;

	int data;
	node *left;
	node *right;

	node *next;
public:

	node()//default constructor for node class
	{
		data = 0;
		left = nullptr;
		right = nullptr;
		next = nullptr;
	}

	node(int key)//parameterized constructor for node class
	{
		data = key;//assigns key to data
		left = nullptr;
		right = nullptr;
		next = nullptr;
	}
};

class stack //linked stack class
{
	friend class node;
	friend class BST;
	node *stackTop;
public:

	stack()
	{
		stackTop = nullptr; //constructor of stack
	}

	~stack()//destructor
	{
		node *temp;
		while (stackTop != nullptr) //while the value of stack isn't nullptr
		{
			temp = stackTop;  //temp is stacktop
			stackTop = stackTop->next; //stacktop becomes the prev node in stack
			delete temp;  //deletes prev stacktop
		}
	}

	bool isEmptyStack()
	{
		return (stackTop == nullptr);//returns true when stackTop is null
	}

	bool isFullStack()//returns true when stack is full
	{
			node* newNode;
			try
			{
				newNode = new node();
				delete newNode;
				return false;
			}
			catch (std::bad_alloc exception)//when stack is full catch exception
			{
				return true;
			}
	}

	void push(node* key) //pushes a member of node class in stack
	{
		node* newNode;
		newNode = new node;
		newNode = key;             //assigning value of the incoming key node to newNode 
		newNode->next = stackTop;  //stackTop becomes the previous node present in stack
		stackTop = newNode;       //stackTop has the value of key now 
	}

	node* top()
	{
		if (stackTop != nullptr) //if stack is not null, return the value at top of stack
			return stackTop;
	}

	node * pop()
	{
		node *temp;
		if (stackTop != nullptr) //if stack is not nullptr
		{
			temp = stackTop;     //temp becomes stackTop
			stackTop = stackTop->next;  //stackTop is the previous value in stack
			return temp; //returns value of the popped node
		}
	}

};

class queue
{
private:

	node *front;
	node *rear;

public:
	queue() //default constructor
	{
		front = nullptr;
		rear = nullptr;
	}

	~queue()//destructor
	{
		node *temp;
		while (front != nullptr)//deletes until front is not null
		{
			temp = front;
			front = front->next;
			delete temp;
		}
	}

	bool isEmptyQueue() const
	{
		return (front == nullptr);//if front is null,then return true
	}

	bool isFullQueue()//true when queue is full
	{
		node *newNode;
		try
		{
			newNode = new node();
			delete newNode;
			return false;
		}
		catch (std::bad_alloc exception)//if full,the catch
		{
			return true;
		}
	}

	void enQueue(node *key)//adds a new element at the the rear of queue
	{
		node *newNode = new node();//initializing newNode to 0
		newNode = key;//assigning new node the value of key
		newNode->next = nullptr;
		if (front == nullptr)//if front is null, key would be first entry in queue
		{
			front = newNode;
			rear = newNode;//front and real point to the same node
		}
		else
		{
			rear->next = newNode;//if not empty, the inserts key at rear's next
			rear = rear->next;//move rear to the new entry
		}
	}

	node* deQueue() //deletes an element from the front of the queue
	{
		node *temp;
		if (!isEmptyQueue()) //if queue is not empty, then perform deletion
		{
			temp = front; //temp is the front
			front = front->next;//front moves while dequeue-ing is being performed
			if (front == nullptr) //if front becomes null, then rear should also become null
				rear = nullptr;
			return temp;
		}
		else
			return 0; //if queue is empty, return null
	}

};

class linkedList
{
public:
	friend class BST;

	node *head;

	node *tail;

	linkedList() //default constructor
	{
		head = tail = nullptr; //head and tail both are nullptr
	}

	~linkedList()//destructor
	{
		node* temporary;
		while (head != nullptr) //while head doesnot become null,keep on moving it and deleting its previous value
		{
			temporary = head;
			head = head->right;//right is synonymous for next
			delete temporary;
		}
		tail = nullptr;
	}

	void print(node *key)
	{
		node *temporary = key;
		if (temporary == nullptr)//if linkedList is empty
			cout << "No Data to Display\n";
		while (temporary != nullptr)//if not empty, then print data
		{
			cout << temporary->data << ' ';
			temporary = temporary->right;//right is synonymous for next
		}
	}
};

class BST
{

public:
	node *root;

	BST()//default constructor
	{
		root = nullptr;
	}

	void deleteTree(node *temp)//deletes tree recursively
	{
		if (temp)
		{
			deleteTree(temp->left);//first: deletes left subtree of root
			deleteTree(temp->right);//second: deletes right subtree of root
			delete temp;
		}
	}

	~BST()//destructor
	{
		deleteTree(root);//calls the deletetree function
	}

	bool insert(int data)//insertion
	{
		node *newNode = new node(data);
		if (root == nullptr)//if root is null, then first entry into the tree is newNode
		{
			root = newNode;
			return true; //returns true when insertion performed
		}
		else
		{
			node *current = root; //for tree traversal
			while (current != nullptr)
			{
				if (current->data == data)//if data is already present in tree, then delete the newNode and return false
				{
					delete newNode;
					return false;
				}
				else if (current->data < data)//if data is greater then tree's data,then goto its right
				{
					if (current->right == nullptr)//if nothing present at right, then insert there
					{
						current->right = newNode;
						return true;
					}
					else
					{
						current = current->right;//else traverse the tree until inserted
					}
				}
				else//if data is less then tree's data,then goto its left
				{
					if (current->left == nullptr)//if nothing present at left, then insert there
					{
						current->left = newNode;
						return true;
					}
					else
					{
						current = current->left;//else traverse the tree until inserted
					}
				}//end inner else
			}//end while
		}//end outer else
	}//end function

	node* search(int key)
	{
		node* current = root;
		while (current != nullptr)
		{
			if (current->data == key)
			{
				cout << "Key found successfully!"<<endl;
				return current;
			}
			else if (current->data < key)//go to right subtree is key is greater than current's data
			{
				current = current->right;
			}
			else//go to left subtree is key is less than current's data
				current = current->left;
		}//end while

		cout << "Key not found!" << endl; 
		return 0;//if nothing returned from while,then return 0
	}

	void deleteNode(int key)
	{ 
		node* current = root; 
		node* parent = nullptr; //parent of current
		bool flag = false;

		//finding parent of the node we want to delete
		while (current != nullptr)
		{
			if (current->data == key)//key found
			{
				flag = true;
				break;
			}
			else
			{
				parent = current;
				if (key < (current->data))//if key is less than currentdata then go to left subtree
					current = current->left;
				else//else go to right
					current = current->right;
			}
		}

		if (!flag)//means key not found,flag is still false
		{
			cout << "Key not found!" << endl;
			return;
		}
		//if deleting leaf node
		if (current->left == nullptr && current->right == nullptr)//both left and right child should be null for leaf deletion
		{
			if (parent->left == current)//if parent's left is current, then point parent's left to null and delete current afterwards
				parent->left = nullptr;
			else//else if parent's right is current, then point parent's right to null and delete current afterwards
				parent->right = nullptr;

			delete current;

			cout << "Key deleted successfully!" << endl;
			return;
		}

		//if node's left child is null
		else if (current->left == nullptr)//current has right child only
		{
			if (parent->right == current)//if parent's right is current, then point its right to current's right, and delete current
				parent->right = current->right;
			else
				parent->left = current->right;//if parent's left is current, then point its left to current's right, and delete current

			delete current;

			cout << "Key deleted successfully!" << endl;
			return;
		}

		//if node's right child is null
		else if (current->right == nullptr)//current has right child only
		{
			if (parent->left == current)//if parent's left child is current, then point its left child to current's left, and delete current
				parent->left = current->left;
			else//if parent's right is current, then point its right to current's left, and delete current
				parent->right = current->left;

			delete current;

			cout << "Key deleted successfully!" << endl;
			return;
		}
		else //if both children are not null
		{
			int temporaryElement = 0;
			node *temporary = nullptr;
			node *traverse = current->left;//for traversing left subtree
			bool check = false;
			while (traverse->right > traverse)//finding largest element in the left subtree i.e the rightmost element
			{
				temporary = traverse;//parent of traverse
				traverse = traverse->right;//parent's right child
				check = true;
			}

			if (!check)//if no largest element present in tree
				temporary = current;

			//swapping current's data with its left's subtree's largest element
			temporaryElement = current->data;
			current->data = traverse->data;
			traverse->data = temporaryElement;

			//if current is swapped with leaf node
			if (traverse->left == nullptr && traverse->right == nullptr)//both left and right children are null
			{
				if (temporary->left == traverse)//if temporary's left is current, then point temporary's left to null and delete traverse afterwards
					temporary->left = nullptr;
				else//else if parent's right is traverse, then point parent's right to null and delete traverse afterwards
					temporary->right = nullptr;

				delete traverse;

				cout << "Key deleted successfully!" << endl;
				return;
			}

			//if node's right child is null
			else if (traverse->right == nullptr)//traverse has right child only
			{
				if (temporary->left == traverse)//if parent's left child is traverse, then point its left child to traverse's left, and delete traverse
					temporary->left = traverse->left;
				else//if parent's right is traverse, then point its right to traverse's left, and delete traverse
					temporary->right = traverse->left;

				delete traverse;

				cout << "Key deleted successfully!" << endl;
				return;
			}
		}
	}

	void postOrder(node  *print)//performing LRV
	{
		stack Stack; ///creating object of stack
		node *current = print;//this has value of root node
		node *temporary1 = nullptr;
		node *temporary2 = nullptr;

		do //while stack is not empty
		{
			while (current != nullptr)//while current is not null
			{
				if (current->right != nullptr)//if current's right is not null,then push it to stack
					Stack.push(current->right);

				Stack.push(current);//push/visit current
				current = current->left;//then go to its left
			}

			bool check = false;
			temporary1 = Stack.pop();//pop stack and get the value

			if (temporary1->right == nullptr)//if no right child,then print
			{
				cout << temporary1->data << ' ';
				check = true;
			}

			current = nullptr;

			if (!check)//if not check
			{
				if (temporary1->right == Stack.top())//temporary's right is the top of stack
				{
					temporary2 = Stack.pop();//assign this top of stack's value
					Stack.push(temporary1);//push visit in stack
					current = temporary1->right;//go to current's right
				}
				else
					cout << temporary1->data << ' ';//print data
			}

		} while (!Stack.isEmptyStack());

	}

	void levelOrder(node* print)
	{
		node *current = print;//root's value to current
		queue Queue;

		while (current != nullptr)//traverse tree
		{
			cout << current->data << ' ';//print level's value

			if (current->left != nullptr)//if left child not null, then enqueue
				Queue.enQueue(current->left);

			if (current->right != nullptr)//if right not null then enqueue
				Queue.enQueue(current->right);
			current = Queue.deQueue();//dequeue left first, and then right
		}
	}

	void preOrder(node  *print)//VLR
	{
		if (print == nullptr)
			return;
		cout << print->data << ' ';  //  visit/print
		preOrder(print->left);//go to left subtree
		preOrder(print->right);//go to right subtree
	}

	void inOrder(node *print)//LVR
	{
		if (print == nullptr)
			return;
		inOrder(print->left);//go to left subtree
		cout << print->data << ' ';    //visit/print
		inOrder(print->right);//go to right subtree
	}

	int height(node *findHeight)
	{
		if (findHeight == nullptr)//if node is null, return 0
			return 0;

		int left = height(findHeight->left); //goto left recursively
		int right = height(findHeight->right);//go to right recursively

		if (left > right)//if left is greater than right,add 1 and return
			return left + 1;
		else//else if right is greater than left,add 1 and return
			return right + 1;
	}

	int totalNodes(node * findNodeNumber)
	{
		 if (findNodeNumber == nullptr)//if node is null, return 0
			 return 0;
		 else//first go to left subtree and then go to right and add 1
			 return totalNodes(findNodeNumber->left) + totalNodes(findNodeNumber->right) + 1;
	}

	int totalLeaves(node *leafNodes)
	{
		if (leafNodes == nullptr)//if node is null, return 0
			return 0;
		else if (leafNodes->left == nullptr && leafNodes->right == nullptr)//if both children, 0 then return 1
			return 1;
		else//goto left subtree and find leaves, then go to right and find leaves and then return null
			return (totalLeaves(leafNodes->left) + totalLeaves(leafNodes->right));
	}

	void doublyLinkedList(node *rootNode,linkedList &object)//following inOrder traversal
	{
		if (rootNode == nullptr)//if root is null,then return from function
		{
			root = nullptr;//return null, because nothing present in BST now
			return;
		}
		 doublyLinkedList(rootNode->left, object);//first traverse left subtree
		if (object.tail == nullptr)//if no tail, it means linkedList is null, so gives root's value to head
			object.head = rootNode;
		else//if linkedlist isnt empty
		{
			rootNode->left = object.tail;//left is previous, so tail becomes newNode's prev
			object.tail->right= rootNode;//tail's right aka next becomes newNode
		}
		object.tail = rootNode;//newNode becomes the tail
		 doublyLinkedList(rootNode->right, object);//traverse right subtree
	}

	int leftHeight(node *height)
	{
		if (height == nullptr)//if height is null, return 0
			return 0;

		return leftHeight(height->left) + 1;//goto left subtree recursively and add 1
	}

	int rightHeight(node *height)
	{
		if (height == nullptr)//if height is null, return 0
			return 0;

		return rightHeight(height->right) + 1;//goto right subtree recursively and add 1
	}

	int balanceFactorTree(int number)//balance factor to balance a binary tree
	{
		node *calculateBF = root;
		while (calculateBF != nullptr)//search for number in tree
		{
			if (calculateBF->data == number)
			{
				break;
			}
			else
			{
				if (number < (calculateBF->data))
					calculateBF = calculateBF->left;
				else
					calculateBF = calculateBF->right;
			}
		}

		int zero = 0;
		//balanceFactor=leftHeight-rightHeight
		if (calculateBF == nullptr)//if node is null, return 0
			return 0;
		else if (calculateBF->right == nullptr && calculateBF->left == nullptr)//if leaf node, then return 0
			return 0;
		else if (calculateBF->left == nullptr)//if only right child
			return zero - rightHeight(calculateBF);
		else if (calculateBF->right == nullptr)//if only left child
			return leftHeight(calculateBF) - zero;
		else//if both children are present
			return height(calculateBF->left) - height(calculateBF->right);
	}

	int balanceFactorNode(int number)
	{
		node *calculateBF = root;
		while (calculateBF != nullptr)//search for node in tree
		{
			if (calculateBF->data == number)
			{
				break;
			}
			else
			{
				if (number < (calculateBF->data))
					calculateBF = calculateBF->left;
				else
					calculateBF = calculateBF->right;
			}
		}

		// returns balanceFactor=leftHeight-rightHeight
			return height(calculateBF->left) - height(calculateBF->right);
	}

	void rotateTree(int balanceNode)
	{
		node *currentB = root;//child
		while (currentB != nullptr) //search for required node in tree
		{
			if (currentB->data == balanceNode)
			{
				break;
			}
			else
			{
				if (balanceNode < (currentB->data))
					currentB = currentB->left;
				else
					currentB = currentB->right;
			}
		}


		if (currentB->left != nullptr)
			rotateTree(currentB->left->data);//traverse left subtree recursively
		if (currentB->right != nullptr)
			rotateTree(currentB->right->data);//traverse right subtree recursively

		node* currentParent = nullptr;
		node* current = nullptr;//parent of parent
		node* currentA = nullptr;//parent
		currentB = root;//child
		node* currentC = nullptr;
		bool check = false;
		while (currentB != nullptr)//tracing parent and parent of parent of node in tree
		{
			if (currentB->data == balanceNode)
			{
				break;
			}
			else
			{
				current = currentA;//parent of A
				currentA = currentB;//parent of B
				if (balanceNode < (currentB->data))
					currentB = currentB->left;
				else
					currentB = currentB->right;
			}
		}

		if (balanceFactorTree(currentB->data) > 1)//if balanceFactor of the node is greater than 1
		{
			//LEFTLEFT
			if (balanceFactorTree(currentB->left->data) >= 0 && currentA->left->data == currentB->data)//if bF of node's left is >= zero 
			{
				check = false;
				if (currentA->data == root->data)//if parent is root
					check = true;

				//swapping pointers for LL rotation
				currentA->left = currentB->right; 
				currentB->right = currentA;

				if (check)//root is updated
					root = currentB;
				else//parent of parent's left child becomes currentB
					current->left = currentB;
			}
			else//LEFT RIGHT ;if bf of its left child is less than 0
			{
				check = false;
				//updating pointers 
				currentC = currentB;//child
				currentB = currentA;
				currentA = current;//parent
				if (currentA->data == root->data)//if parent is root
					check = true;

				//swapping pointers for LR rotation
				currentA->left = currentC->right;
				currentB->right = currentC->left;
				currentC->right = currentA;
				currentC->left = currentB;

				if (!check)//A's parent left child becomes currentB
					currentParent->left = currentC;
				else // root is updated
					root = currentC;
			}
		}
		else if (balanceFactorTree(currentB->data) < -1)//if balance factor of node is less than -1
		{
			//RIGHTRIGHT
			if (balanceFactorTree(currentB->right->data) <= 0 )//if node's  right bf is <=0
			{
				check = false;
				if (currentB != root)//if node is root, then dont't perform 
				{
					if (currentA->data == root->data)//if A's data is root's data
						check = true;

					//swapping pointers for RR rotation
					currentA->right = currentB->left;
					currentB->left = currentA;

					if (check)//root is updated
						root = currentB;
					else//A's parent right is updated
						current->right = currentB;
				}
			}
			else//RIGHTLEFT; if bf node's right is greater than 1
			{
				check = false;
				//updating pointers 
				currentC = currentB;//child
				currentB = currentA;
				currentA = current;//parent

				if (currentA->data == root->data) // if parent is root
					check = true;

				//swapping pointers for RL rotation
				currentA->right = currentC->left;
				currentB->left = currentC->right;
				currentC->right = currentB;
				currentC->left = currentA;

				if (!check)//A's parent right child becomes currentB
					currentParent->left = currentC;
				else//root is updated
					root = currentC;
			}//enter inner else
		}//end outer elseif
	}//endoffunction

	void rotateNode(int key)
{
	node* parent = nullptr;
	node *current = root;
	while (current != nullptr)//search for key in tree
	{
		if (current->data == key)
		{
			break;
		}
		else
		{
			parent = current;
			if (current->data < key)
				current = current->right;
			else
				current = current->left;
		}
	}

	if (current->left!=nullptr)
		rotateNode(current->left->data); //goto left subtree recursively
	if (current->right != nullptr)
		rotateNode(current->right->data);//go to right subtree recursively

	if (balanceFactorNode(key) == -1 || balanceFactorNode(key) == 0 || balanceFactorNode(key) == 1)//if balancrFactor of the node is this, then it is balanced
		return;

	current = root;
	while (current != nullptr)//traversing tree for parent of node
	{
		if (current->data == key)
		{
			break;
		}
		else
		{
			parent = current;//parent of node
			if (current->data < key)
				current = current->right;
			else
				current = current->left;
		}
	}

	node *currentP = nullptr;
	node *currentC = nullptr;
	bool check = false;

	if (balanceFactorNode(current->data) < -1)//if balance factor is less than -1
	{
		//RR
		if (balanceFactorNode(current->right->data) <= 0)//if balancefactor of right child is less than equals to 0
		{
			 check = false;
			if (current->data == root->data)//if current is root
				check = true;

			//swapping pointers for RR rotation
			currentP = current;
			current = currentP->right;
			currentP->right = current->left;
			current->left = currentP;

			if (check)//root updated
				root = current;
			else//parent's right links to current
				parent->right = current;
		}
		else //RL; if bf of right child is greater than 0
		{
			 check = false;
			if (current->data == root->data)//if current is root
				check = true;

			//swapping pointers for RR rotation
			currentP = current;//parent
			current = currentP->right;
			currentC = current->left;//child

			current->left = currentC->right;
			currentP->right = currentC->left;
			currentC->left = currentP;
			currentC->right = current;

			if (check)//root updated
				root = currentC;
			else//parent's left links to child
				parent->left = currentC;
		}
	}
	else if (balanceFactorNode(current->data) > 1)//if bf is greater than 1
	{
		//LL
		if (balanceFactorNode(current->left->data) >= 0)//if bf of left child is greater than equals to zero
		{
			check = false;

			if (current->data == root->data)//if current is root
				check = true;

			//swapping pointers for LL rotation
			currentP = current;
			current = currentP->left;
			currentP->left = current->right;
			current->right = currentP;

			if (check)//root update
				root = current;
			else//parent's left links to current
				parent->left = current;
		}
		else //LR; if bf of left child is less than 0
		{
			check = false;
			if (current->data == root->data)//if current is root
				check = true;

			//swapping pointers for LR rotation
			currentP = current;//parent
			current = currentP->left;
			currentC = current->right;//child

			current->right = currentC->left;
			currentP->left = currentC->right;
			currentC->left = current;
			currentC->right = currentP;

			if (check)//root is updated
				root = currentC;
			else//parent's left is linked to C
				parent->left = currentC;

		}
	}
}

	bool balancedInsertion(int data)//insertion
	{
		node *newNode = new node(data);
		if (root == nullptr)//if root is null, then first entry into the tree is newNode
		{
			root = newNode;
			return true; //returns true when insertion performed
		}
		else
		{
			node *current = root; //for tree traversal
			while (current != nullptr)
			{
				if (current->data == data)//if data is already present in tree, then delete the newNode and return false
				{
					delete newNode;
					return false;
				}
				else if (current->data < data)//if data is greater then tree's data,then goto its right
				{
					if (current->right == nullptr)//if nothing present at right, then insert there
					{
						current->right = newNode;
						rotateNode(root->data);//balancing through AVL rotations
						return true;
					}
					else
					{
						current = current->right;//else traverse the tree until inserted
					}
				}
				else//if data is less then tree's data,then goto its left
				{
					if (current->left == nullptr)//if nothing present at left, then insert there
					{
						current->left = newNode;
						rotateNode(root->data);//balancing through AVL rotations
						return true;
					}
					else
					{
						current = current->left;//else traverse the tree until inserted
					}
				}//end inner else
			}//end while
		}//end outer else
	}//end function

	void balancedDeletion(int key)
	{
		node* current = root;
		node* parent = nullptr; //parent of current
		bool flag = false;

		//finding parent of the node we want to delete
		while (current != nullptr)
		{
			if (current->data == key)//key found
			{
				flag = true;
				break;
			}
			else
			{
				parent = current;
				if (key < (current->data))//if key is less than currentdata then go to left subtree
					current = current->left;
				else//else go to right
					current = current->right;
			}
		}

		if (!flag)//means key not found,flag is still false
		{
			return;
		}
		//if deleting leaf node
		if (current->left == nullptr && current->right == nullptr)//both left and right child should be null for leaf deletion
		{
			if (parent->left == current)//if parent's left is current, then point parent's left to null and delete current afterwards
				parent->left = nullptr;
			else//else if parent's right is current, then point parent's right to null and delete current afterwards
				parent->right = nullptr;

			delete current;

			rotateNode(root->data); //balancing through AVL rotations
		
			return;
		}

		//if node's left child is null
		else if (current->left == nullptr)//current has right child only
		{
			if (parent->right == current)//if parent's right is current, then point its right to current's right, and delete current
				parent->right = current->right;
			else
				parent->left = current->right;//if parent's left is current, then point its left to current's right, and delete current

			delete current;

			rotateNode(root->data); //balancing through AVL rotations

			return;
		}

		//if node's right child is null
		else if (current->right == nullptr)//current has right child only
		{
			if (parent->left == current)//if parent's left child is current, then point its left child to current's left, and delete current
				parent->left = current->left;
			else//if parent's right is current, then point its right to current's left, and delete current
				parent->right = current->left;

			delete current;

			rotateNode(root->data); //balancing through AVL rotations

			return;
		}
		else //if both children are not null
		{
			int temporaryElement = 0;
			node *temporary = nullptr;
			node *traverse = current->left;//for traversing left subtree
			bool check = false;
			while (traverse->right > traverse)//finding largest element in the left subtree i.e the rightmost element
			{
				temporary = traverse;//parent of traverse
				traverse = traverse->right;//parent's right child
				check = true;
			}

			if (!check)//if no largest element present in tree
				temporary = current;

			//swapping current's data with its left's subtree's largest element
			temporaryElement = current->data;
			current->data = traverse->data;
			traverse->data = temporaryElement;

			//if current is swapped with leaf node
			if (traverse->left == nullptr && traverse->right == nullptr)//both left and right children are null
			{
				if (temporary->left == traverse)//if temporary's left is current, then point temporary's left to null and delete traverse afterwards
					temporary->left = nullptr;
				else//else if parent's right is traverse, then point parent's right to null and delete traverse afterwards
					temporary->right = nullptr;

				delete traverse;

				rotateNode(root->data); //balancing through AVL rotations

				return;
			}

			//if node's right child is null
			else if (traverse->right == nullptr)//traverse has right child only
			{
				if (temporary->left == traverse)//if parent's left child is traverse, then point its left child to traverse's left, and delete traverse
					temporary->left = traverse->left;
				else//if parent's right is traverse, then point its right to traverse's left, and delete traverse
					temporary->right = traverse->left;

				delete traverse;

				rotateNode(root->data); //balancing through AVL rotations

				return;
			}
		}
	}

};

void driver()
{
		BST tree1;
		cout << "Inserting Keys in Tree 1:  7, 4, 9, 2, 6, 8, 11, 1, 3, 5, 10 " << endl << endl;
		tree1.insert(7);
		tree1.insert(4);
		tree1.insert(9);
		tree1.insert(2);
		tree1.insert(6);
		tree1.insert(8);
		tree1.insert(11);
		tree1.insert(1);
		tree1.insert(3);
		tree1.insert(5);
		tree1.insert(10);

		cout << "Traversing Tree 1:\n\n";
		cout << "InOrder Traversal: ";
		tree1.inOrder(tree1.root);
		cout << endl;

		cout << "PostOrder Traversal: ";
		tree1.postOrder(tree1.root);
		cout << endl;

		cout << "LevelOrder Traversal: ";
		tree1.levelOrder(tree1.root);
		cout << endl;

		cout << "PreOrder Traversal: ";
		tree1.preOrder(tree1.root);
		cout << endl;

		cout << "Height of Tree: ";
		cout << tree1.height(tree1.root);
		cout << endl;

		cout << "Total No of Nodes: ";
		cout << tree1.totalNodes(tree1.root);
		cout << endl;

		cout << "Total Leaves: ";
		cout << tree1.totalLeaves(tree1.root);
		cout << endl << endl;

		cout << "   Testing Search\n" << endl;

		cout << "Search(6) : ";
		tree1.search(6);
		cout << "Search(8) : ";
		tree1.search(6);
		cout << "Search(13) : ";
		tree1.search(13);
		cout << endl;

		cout << "Delete(8) : ";
		tree1.deleteNode(8);
		cout << "Tree1 after Deletion : " << endl;
		cout << "InOrder Traversal: ";
		tree1.inOrder(tree1.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree1.levelOrder(tree1.root);
		cout << endl << endl;

		cout << "Delete(11) : ";
		tree1.deleteNode(11);
		cout << "Tree1 after Deletion : " << endl;
		cout << "InOrder Traversal: ";
		tree1.inOrder(tree1.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree1.levelOrder(tree1.root);
		cout << endl << endl;

		cout << "Delete(7) : ";
		tree1.deleteNode(7);
		cout << "Tree1 after Deletion : " << endl;
		cout << "InOrder Traversal: ";
		tree1.inOrder(tree1.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree1.levelOrder(tree1.root);
		cout << endl << endl;

		cout << "Delete(50) : ";
		tree1.deleteNode(50);
		cout << endl << endl;

		linkedList object;
		cout << "       Converting Tree 1 to Linked List\n\n";
		cout << "Linked List Before Conversion: ";
		object.print(object.head);
		cout << endl;
		cout << "Linked List After Conversion: ";
		tree1.doublyLinkedList(tree1.root, object);

		object.print(object.head);
		cout << endl;

		cout << "\nTree1 after conversion:\n";
		cout << "InOrder Traversal: ";
		tree1.inOrder(tree1.root);
		cout << endl;

		cout << "LevelOrder Traversal: ";
		tree1.levelOrder(tree1.root);
		cout << endl;

		cout << "\n   Testing Balancing\n\nInserting Keys in Tree 2 (Simple Insertion):       6,5,7,4,8,3,9,2,10,1,11\n\n";

		BST tree2;
		tree2.insert(6);
		tree2.insert(5);
		tree2.insert(7);
		tree2.insert(4);
		tree2.insert(8);
		tree2.insert(3);
		tree2.insert(9);
		tree2.insert(2);
		tree2.insert(10);
		tree2.insert(1);
		tree2.insert(11);

		cout << "Tree 2 Before Balancing:\n\n";
		cout << "InOrder Traversal: ";
		tree2.inOrder(tree2.root);
		cout << endl;
		cout << "PreOrder Traversal: ";
		tree2.preOrder(tree2.root);
		cout << endl;
		cout << "PostOrder Traversal: ";
		tree2.postOrder(tree2.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree2.levelOrder(tree2.root);
		cout << endl;

		tree2.rotateTree(6);

		cout << "Tree 2 After Balancing:\n\n";
		cout << "InOrder Traversal: ";
		tree2.inOrder(tree2.root);
		cout << endl;
		cout << "PreOrder Traversal: ";
		tree2.preOrder(tree2.root);
		cout << endl;
		cout << "PostOrder Traversal: ";
		tree2.postOrder(tree2.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree2.levelOrder(tree2.root);
		cout << endl << endl;


		cout << "   Testing Balanced Insertion\n\n";

		BST tree3;
		cout << "Key: 8\n";
		tree3.balancedInsertion(8);
		cout << "InOrder Traversal: ";
		tree3.inOrder(tree3.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree3.levelOrder(tree3.root);
		cout << endl << endl;


		cout << "Key: 9\n";
		tree3.balancedInsertion(9);
		cout << "InOrder Traversal: ";
		tree3.inOrder(tree3.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree3.levelOrder(tree3.root);
		cout << endl << endl;

		cout << "Key: 10\n";
		tree3.balancedInsertion(10);
		cout << "InOrder Traversal: ";
		tree3.inOrder(tree3.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree3.levelOrder(tree3.root);
		cout << endl << endl;

		cout << "Key: 2\n";
		tree3.balancedInsertion(2);
		cout << "InOrder Traversal: ";
		tree3.inOrder(tree3.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree3.levelOrder(tree3.root);
		cout << endl << endl;

		cout << "Key: 1\n";
		tree3.balancedInsertion(1);
		cout << "InOrder Traversal: ";
		tree3.inOrder(tree3.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree3.levelOrder(tree3.root);
		cout << endl << endl;

		cout << "Key: 5\n";
		tree3.balancedInsertion(5);
		cout << "InOrder Traversal: ";
		tree3.inOrder(tree3.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree3.levelOrder(tree3.root);
		cout << endl << endl;

		cout << "Key: 3\n";
		tree3.balancedInsertion(3);
		cout << "InOrder Traversal: ";
		tree3.inOrder(tree3.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree3.levelOrder(tree3.root);
		cout << endl << endl;

		cout << "Key: 6\n";
		tree3.balancedInsertion(6);
		cout << "InOrder Traversal: ";
		tree3.inOrder(tree3.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree3.levelOrder(tree3.root);
		cout << endl << endl;


		cout << "Key: 4\n";
		tree3.balancedInsertion(4);
		cout << "InOrder Traversal: ";
		tree3.inOrder(tree3.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree3.levelOrder(tree3.root);
		cout << endl << endl;

		cout << "Key: 7\n";
		tree3.balancedInsertion(7);
		cout << "InOrder Traversal: ";
		tree3.inOrder(tree3.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree3.levelOrder(tree3.root);
		cout << endl << endl;

		cout << "Key: 11\n";
		tree3.balancedInsertion(11);
		cout << "InOrder Traversal: ";
		tree3.inOrder(tree3.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree3.levelOrder(tree3.root);
		cout << endl << endl;

		cout << "Key: 12\n";
		tree3.balancedInsertion(12);
		cout << "InOrder Traversal: ";
		tree3.inOrder(tree3.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree3.levelOrder(tree3.root);
		cout << endl << endl;

		cout << "   Testing Balanced Deletion\n\n";

		cout << "Tree 2 after Deleting 5\n";
		tree2.balancedDeletion(5);
		cout << "InOrder Traversal: ";
		tree2.inOrder(tree2.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree2.levelOrder(tree2.root);
		cout << endl << endl;

		cout << "Tree 2 after Deleting 1\n";
		tree2.balancedDeletion(1);
		cout << "InOrder Traversal: ";
		tree2.inOrder(tree2.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree2.levelOrder(tree2.root);
		cout << endl << endl;

		cout << "Tree 2 after Deleting 2\n";
		tree2.balancedDeletion(2);
		cout << "InOrder Traversal: ";
		tree2.inOrder(tree2.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree2.levelOrder(tree2.root);
		cout << endl << endl;

		cout << "Tree 2 after Deleting 4\n";
		tree2.balancedDeletion(4);
		cout << "InOrder Traversal: ";
		tree2.inOrder(tree2.root);
		cout << endl;
		cout << "LevelOrder Traversal: ";
		tree2.levelOrder(tree2.root);
		cout << endl << endl;
}

void main()
{
	driver();

	system("pause");
}