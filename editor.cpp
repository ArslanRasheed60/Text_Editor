#include <fstream>
#include <iostream>
#include <stdlib.h>

# include "myconsole.h"
# include "editor.h"

using namespace std;

static int iterator_count = 0;
static int store_x_cursor = 0;
static int store_y_cursor = 0;
static int storing_array[50] = { 0 };

//-------------------------------Color Codes------------------------------//
// Color Codes Hexadecimal values for both Fore Ground and Back Ground //ForeGround|BackGround
int B_BLACK			= 0x00;	int B_Royal_Blue	= 0x10;	int B_Dark_Green	= 0x20;
int B_Tale_Blue		= 0x30;	int B_Dark_Red		= 0x40;	int B_Purple		= 0x50;
int B_Tale_Green	= 0x60;	int B_Light_Grey	= 0x70; int B_Dark_Gray		= 0x80;	
int B_Light_Blue	= 0x90; int B_Light_Green	= 0xA0;	int B_Sky_Blue		= 0xB0;
int B_Red			= 0xC0;	int B_Pink			= 0xD0;	int B_Yellow		= 0xE0;
int B_White			= 0xF0;

int F_BLACK			= 0x00;	int F_Royal_Blue	= 0x01; int F_Dark_Green = 0x02;
int F_Tale_Blue		= 0x03;	int F_Dark_Red		= 0x04;	int F_Purple	 = 0x05;
int F_Tale_Green	= 0x06;	int F_Light_Grey	= 0x07; int F_Dark_Gray	 = 0x08;
int F_Light_Blue	= 0x09; int F_Light_Green	= 0x0A;	int F_Sky_Blue	 = 0x0B;
int F_Red			= 0x0C;	int F_Pink			= 0x0D;	int F_Yellow	 = 0x0E;
int F_White			= 0x0F;

//-------------------------------POINT CLASS------------------------------//
//initialize MaxPoint
point point::MaxPoint(MAX_X, MAX_Y);
bool point::incrementX()
{
	bool returnValue = true;
	if (x<MaxPoint.x)
		x++;
	else if (y<MaxPoint.y)
	{
		x = 0;
		y = y + 1;
	}
	else
		returnValue = false;

	return returnValue;
}

bool point::incrementY()
{
	bool returnValue = true;
	if (y<MaxPoint.y)
		y++;
	else
		returnValue = false;

	return returnValue;

}
bool point::decrementX()
{
	bool returnValue = true;
	if (x>0)
		x--;
	else if (y>0)
	{
		y--;
		x = MaxPoint.x;
	}
	else
		returnValue = false;

	return returnValue;
}
bool point::decrementY()
{
	bool returnValue = true;
	if (y>0)
		y--;
	else
		returnValue = false;

	return returnValue;

}

//-------------------------------END OF POINT CLASS------------------------------------------------//


//static positions to save user enter data
static int user_x = 0;
static int user_y = 0;

//doubly linklist class 

template <typename T>
class DoublyLinkList
{
public:
	class Node
	{
		T data;
		Node* next;
		Node* prev;
		friend class DoublyLinkList<T>;
	public:
		Node(T dat = NULL, Node* nex = nullptr, Node* pre = nullptr)
		{
			data = dat;
			next = nex;
			prev = pre;
		}
	};
	class iterator
	{
		Node* current;
		friend class DoublyLinkList;
	public:
		iterator(Node* start = nullptr)				//default + paramitized
		{
			current = start;
		}
		iterator& operator++()
		{
			if (current->next != nullptr)
			{
				current = current->next;
			}
			return *this;
		}
		iterator operator++(int)
		{
			iterator t(current);
			if (current != nullptr && current->next != nullptr)
			{
				current = current->next;
			}
			return t;
		}
		iterator& operator--()
		{
			if (current != nullptr && current->prev != nullptr)
			{
				current = current->prev;
			}
			return *this;
		}
		iterator operator--(int)
		{
			iterator t(current);
			if (current->prev != nullptr)
			{
				current = current->prev;
			}
			return t;
		}
		T& operator*()const
		{
			return current->data;
		}
		T& operator->()const
		{
			return current->data;
		}
		bool operator==(iterator& obj)
		{
			if (current == obj.current)
				return true;
			else
				return false;
		}
		bool operator!=(iterator& obj)
		{
			return !(*this == obj);
		}
		bool operator!=(T poin)
		{
			if (this->current != nullptr)
				return true;
			else
				return false;
		}
	};
private:
	Node head;
	int size;						//for creating of iterator array for string working
public:
	DoublyLinkList()
	{
		head.data = 0;
		size = 0;
	}

	int getsize()
	{
		return size;
	}

	//Add an element at the head
	void insertAt_At_Head(T const element)
	{
		Node* n = new Node(element);
		size++;
		if (head.next == nullptr)
		{
			head.next = n;
		}
		else
		{
			n->next = head.next;
			n->next->prev = n;
			head.next = n;
		}
	}

	//Delete an element form the head
	void delete_from_head()
	{
		if (head.next != nullptr)
		{
			Node* curr = head.next;
			head.next = head.next->next;
			head.next->prev = nullptr;
			delete curr;
			size--;
		}
	}

	//search and remove all entries of an element from list.
	bool delete_All(T const element)
	{
		Node* curr = head.next;
		Node* pre = head.next;
		bool flag = false;
		while (curr != nullptr)
		{
			pre = curr;
			curr = curr->next;
			if (pre->data == element && pre->prev == nullptr) // head condition
			{
				head.next = pre->next;
				head.next->prev = nullptr;
				delete pre;
				flag = true;
			}
			else if (pre->data == element && pre->next == nullptr) //tail condition
			{
				pre->prev->next = nullptr;
				delete pre;
				flag = true;
			}
			else if (pre->data == element)
			{
				pre->next->prev = pre->prev;
				pre->prev->next = pre->next;
				delete pre;
				flag = true;
			}

		}
		return flag;
	}

	//Search and replace all entries of element(s) from the list with provided input values.
	bool replace_All(T const repl, T const element)
	{
		Node* curr = head.next;
		bool flag = false;
		while (curr != nullptr)
		{
			if (curr->data == repl)
			{
				curr->data = element;
				flag = true;
			}
			else
			{
				curr = curr->next;
			}

		}
		return flag;
	}

	void replace_All(iterator* obj, iterator& replace, int found_count)
	{
		for (int i = 0; i < found_count; i++)
		{
			Node* temp = replace.current;
			while (temp != nullptr)
			{
				if (obj[i].current == &head)
				{
					Node* n = new Node(temp->data);
					n->next = head.next;
					n->next->prev = n;
					head.next = n;
					n->prev = nullptr;
					obj[i].current = n;
				}
				else
				{
					insert(obj[i], temp->data);
				}
				
				temp = temp->next;
				
			}
		}
	}

	//Swap two nodes of the list
	void swap(T const ele1, T const element2)
	{
		Node* curr1 = head.next;
		Node* curr2 = head.next;
		Node* pre1 = nullptr;
		Node* pre2 = nullptr;
		bool flag1 = false;
		int count1 = 0;
		int count2 = 0;
		while (curr1 != nullptr && !flag1)
		{
			if (curr1->data == ele1)
			{
				flag1 = true;
				//curr2 = curr1->next;
			}
			else
			{
				pre1 = curr1;
				curr1 = curr1->next;
				count1++;
			}
		}

		bool flag2 = false;
		while (curr2 != nullptr && !flag2)
		{
			if (curr2->data == element2)
				flag2 = true;
			else
			{
				pre2 = curr2;
				curr2 = curr2->next;
				count2++;
			}
		}

		if (flag1 == true && flag2 == true && curr1 != curr2)
		{

			if (count1 > count2)
			{
				Node* t = curr1;
				curr1 = curr2;
				curr2 = t;
				t = pre1;
				pre1 = pre2;
				pre2 = t;
			}

			//swap head and tail
			if (curr1->prev == nullptr && curr2->next == nullptr)
			{
				head.next = curr2;
				curr2->next = curr1->next;
				curr1->next->prev = curr2;
				pre2->next = curr1;
				curr1->prev = pre2;
				curr1->next = nullptr;
				curr2->prev = nullptr;
			}
			//swap 1st node and next to it
			else if (curr1->prev == nullptr && curr1->next == curr2)
			{
				curr1->next = curr2->next;
				curr1->next->prev = curr1;
				curr1->prev = curr2;
				curr2->next = curr1;
				curr2->prev = nullptr;
				head.next = curr2;
			}
			//swap 1st node with any other node
			else if (curr1->prev == nullptr)
			{
				Node* temp = curr1->next;
				curr1->next = curr2->next;
				curr1->next->prev = curr1;
				curr2->next = temp;
				temp->prev = curr2;
				head.next = curr2;
				curr2->prev = nullptr;
				pre2->next = curr1;
				curr1->prev = pre2;
			}
			//swap last and 2nd last node
			else if (curr2->next == nullptr && curr1->next == curr2)
			{
				curr1->prev->next = curr2;
				curr2->prev = curr1->prev;
				curr2->next = curr1;
				curr1->prev = curr2;
				curr1->next = nullptr;
			}
			//swap last with any middle node
			else if (curr2->next == nullptr)
			{
				curr2->next = curr1->next;
				curr2->prev = pre1;
				curr2->next->prev = curr2;
				pre1->next = curr2;
				pre2->next = curr1;
				curr1->prev = pre2;
				curr1->next = nullptr;
			}
			//swap any 2 join nodes from center
			else if (curr1->next == curr2)
			{
				curr1->next = curr2->next;
				curr1->next->prev = curr1;
				pre1->next = curr2;
				curr2->prev = pre1;
				curr2->next = curr1;
				curr1->prev = curr2;
			}
			//swaaping any 2 locations
			else
			{
				Node* temp = curr1->next;
				curr1->next = curr2->next;
				curr1->next->prev = curr1;
				pre2->next = curr1;
				curr1->prev = pre2;
				curr2->next = temp;
				curr2->prev = pre1;
				temp->prev = curr2;
				pre1->next = curr2;
			}
		}
		else
		{
			//cout << "\nswapping not possible: ";
		}
	}

	~DoublyLinkList()			//deallocation
	{
		Node* curr = head.next;
		Node* pr = head.next;
		while (curr != nullptr)
		{
			pr = curr;
			curr = curr->next;
			delete pr;
		}
	}

	//iterator funstions
	iterator begin()
	{
		return head.next;
	}
	iterator end()
	{
		return nullptr;
	}
	void insert(iterator& obj, T const element)
	{
		Node* n = new Node(element);
		if (head.next == nullptr)		//head insertion
		{
			head.next = n;
			obj.current = n;
		}
		else if (obj.current->next == nullptr)       //insert at tail
		{
			obj.current->next = n;
			n->prev = obj.current;
			obj.current = n;
		}
		else
		{
			Node* temp = obj.current->next;
			n->next = temp;
			temp->prev = n;
			obj.current->next = n;
			n->prev = obj.current;
			obj.current = n;
		}
		size++;
	}

	void insert_multiple(iterator& obj, T* element)
	{
		int size = strlen(element);
		if (size == 1)
		{
			insert(obj, element[0]);
		}
		else
		{
			Node* n = new Node(element[0]);
			Node* curr = n;
			for (int i = 1; i < size; i++)
			{
				Node* temp = new Node(element[i]);
				curr->next = temp;
				temp->prev = curr;
				curr = curr->next;
			}
			if (obj.current == nullptr)			//head insertion
			{
				head.next = n;
			}
			else if (obj.current->next == nullptr)		//tail inertion
			{
				obj.current->next = n;
				n->prev = obj.current;
			}
			else
			{
				//middle insertion
				curr->next = obj.current->next;
				n->prev = curr->next->prev;
				curr->next->prev = curr;
				n->prev->next = n;
			}
		}
	}

	void Delete(iterator& obj)
	{
		if (obj.current != nullptr)
		{
			if (obj.current->prev == nullptr) //head deletion
			{
				Node* temp = obj.current;
				head.next = obj.current->next;
				obj.current = head.next;
				if (obj.current != nullptr)
				{
					obj.current->prev = nullptr;
				}
				delete temp;
			}
			else if (obj.current->next == nullptr)	//tail deletion
			{
				/*Node* temp = obj.current;
				obj.current->prev->next = nullptr;
				obj.current = obj.current->prev;
				delete temp;*/
			}
			else
			{
				Node* temp = obj.current->next;
				obj.current->next = temp->next;
				if (temp->next != nullptr)
					temp->next->prev = obj.current;			
				delete temp;
			}
		}
	}

	void BackSpace_delete(iterator& obj)
	{
		if (obj.current != nullptr)
		{
			if (obj.current->prev == nullptr) //head deletion
			{
				Node* temp = obj.current;
				head.next = obj.current->next;
				obj.current = head.next;
				if (obj.current != nullptr)
				{
					obj.current->prev = nullptr;
				}
				delete temp;
			}
			else if (obj.current->next == nullptr)	//tail deletion
			{
				Node* temp = obj.current;
				obj.current->prev->next = nullptr;
				obj.current = obj.current->prev;
				delete temp;
			}
			else
			{
				Node* temp = obj.current;
				obj.current->prev->next = obj.current->next;
				obj.current->next->prev = obj.current->prev;
				obj.current = obj.current->prev;
				delete temp;
			}
		}
	}

	void Delete_multiple(iterator* obj, int found_count, int word_count)
	{
		iterator iter;
		for (int i = 0; i < found_count; i++)
		{
			if (obj[i].current == head.next)
			{
				iter.current = obj[i].current;;
				for (int j = 0; j < word_count && iter.current->next != nullptr; j++)
				{
					iter.current = iter.current->next;
				}
				obj[i].current = &head;
				if (iter.current->next == nullptr)		//if last node is pointing to nullptr
				{
					Node* n = new Node;			//creating dummy node
					iter.current->next = n;
					iter.current = iter.current->next;
				}
				Delete_in_range(obj[i], iter);
			}
			else
			{
				Node* curr = obj[i].current;
				iter.current = curr;
				obj[i].current = obj[i].current->prev;
				for (int j = 0; j < word_count && iter.current->next != nullptr; j++)
				{
					iter.current = iter.current->next;
				}
				if (iter.current->next == nullptr)		//if last node is pointing to nullptr
				{
					Node* n = new Node;			//creating dummy node
					iter.current->next = n;
					iter.current = iter.current->next;
				}
				Delete_in_range(obj[i], iter);
			}
		}
	}

	void Delete_in_range(iterator& obj1, iterator& obj2)
	{
		if ((obj1.current != nullptr && obj2.current != nullptr) && (obj1.current != obj2.current))
		{
			Node* curr = head.next;
			Node* pr = head.next;
			while (curr != obj2.current)
			{
				pr = curr;
				curr = curr->next;
			}
			Node* temp = obj1.current->next;
			pr->next = nullptr;
			if (obj2.current->prev == nullptr)		//it means last node is dummy
			{
				obj1.current->next = obj2.current->next;
			}
			else
			{
				obj1.current->next = obj2.current;
				obj2.current->prev = obj1.current;
			}

			while (temp != nullptr)
			{
				Node* t = temp;
				temp = temp->next;
				delete t;
			}
		}
	}

	iterator search_first(iterator& srch, int count, int& f1, bool& flag)
	{
		iterator obj = begin();
		int temp_count = 0;
		int temp_f1 = 0;
		while (obj.current != nullptr)
		{
			temp_count = 0;
			if (srch.current != nullptr && obj.current->data == srch.current->data)
			{
				Node* temp1 = obj.current;
				Node* temp2 = srch.current;
				while (temp2 != nullptr && temp1->data == temp2->data)
				{
					temp_count++;
					temp1 = temp1->next;
					temp2 = temp2->next;
				}
				if (temp_count == count)
				{
					f1 = temp_f1;
					flag = true;
					return obj;
				}
			}
			obj.current = obj.current->next;
			temp_f1++;
		}
		return NULL;
	}

	iterator* search_ALL(iterator& srch, int& found_count, int count)
	{
		iterator obj = begin();

		iterator* arr = new iterator[size / count];				//array will be gerated for small size for worst case handelling

		int f_count = 0;
		int temp_count = 0;
		while (obj.current != nullptr)
		{
			if (srch.current != nullptr && obj.current->data == srch.current->data)
			{
				temp_count = 0;
				Node* temp1 = obj.current;
				Node* temp2 = srch.current;		//temp1 = nullptr added here
				while (temp2 != nullptr && temp1 != nullptr &&  temp1->data == temp2->data)
				{
					temp_count++;
					temp1 = temp1->next;
					temp2 = temp2->next;
				}
				if (temp_count == count)
				{
					arr[f_count] = obj;
					f_count++;
				}
			}
			obj.current = obj.current->next;
		}
		if (f_count != 0)
		{
			found_count = f_count;
			return arr;
		}
		else
		{
			return NULL;
		}
	}

	void file_storage()
	{
		ofstream fout;
		fout.open("data.txt");
		Node* t = head.next;
		while (t != nullptr)
		{
			fout << t->data;
			t = t->next;
		}
		fout.close();
	}
	void print()						
	{
		Node* curr = head.next;
		int count = 0;
		int count_y = 0;
		while (curr != nullptr)
		{
			if (count < storing_array[count_y])
			{
				cout << curr->data;
				SetColorAtPoint(count, count_y, F_BLACK | B_Light_Blue);
				
				count++;
			}
			else
			{
				cout << endl;
				count = 0;
				count_y++;
			}
			curr = curr->next;
		}
	}
	void remaing_print(iterator& obj , int count_x, int count_y)
	{
		Node* curr = obj.current;
		Node* prev = obj.current;
		while (curr != nullptr)
		{
			if (count_x < storing_array[count_y])
			{
				cout << curr->data;
				SetColorAtPoint(count_x, count_y, F_BLACK | B_Light_Blue);

				count_x++;
			}
			else
			{
				cout << endl;
				count_x = 0;
				count_y++;
			}
			prev = curr;
			curr = curr->next;
		}
		obj.current = prev;
	}
};

//--------------------------The function Where you will write code--------------------------------//
int mainEditor()
{
	int key = 0;
	bool stop = false;
	point currentPosition(0, 0);
	currentPosition.setMaxPoint(MAX_X, MAX_Y);
	bool specialKey = false;

	DoublyLinkList<char> list1;
	DoublyLinkList<char>::iterator iter1 = list1.begin();
	while (!stop)
	{
		key = CheckWhichKeyPressed(specialKey);
		//escape key
		if (key == ESCKEY)
			stop = true;
		//printable character...only adds to the end of text
		//this will not do insertions in between text
		//add code here to insert characters within text
		else if (!specialKey&&key >= 32 && key <= 126)
		{
			char ch = (char)key;
			list1.insert(iter1,ch);

			if (user_x < MAX_X)
			{
				user_x++;
				storing_array[user_y] = user_x;
			}	
			else if (user_y < MAX_Y)
			{
				storing_array[user_y] = user_x;
				user_x = 0;
				user_y++;
			}


			if (currentPosition.getX() < MAX_X)
			{
				//cursor and printing handling
				store_x_cursor = currentPosition.getX();
				store_y_cursor = currentPosition.getY();
				currentPosition.setX(0);
				currentPosition.setY(0);
				//cout << (char)key;
				//ClearScreen();
				PlaceCursor(0, 0);
				list1.print();							//handling my own data and cursor
				currentPosition.setX(store_x_cursor);
				currentPosition.setY(store_y_cursor);
				PlaceCursor(store_x_cursor, store_y_cursor);
				/*handling cursor till here*/

				//You can change color of text by calling this function
				SetColorAtPoint(currentPosition.getX(), currentPosition.getY(), F_BLACK|B_White);   //ForeGround|BackGround
				currentPosition.incrementX();
			}
			else if (currentPosition.getY() < MAX_Y)
			{
				currentPosition.incrementY();
				storing_array[user_y] = currentPosition.getX();
				user_y++;
				currentPosition.setX(0);
			}
		}

		else if (specialKey && key == LEFTKEY)
		{
			if (currentPosition.getX() > 0)
			{
				currentPosition.decrementX();
				--iter1;
				
					
			}
			else if (currentPosition.getY() > 0)
			{
				currentPosition.decrementY();
				user_y--;
				currentPosition.setX(storing_array[user_y]);
				--iter1;
				
			}

		}
		else if (specialKey && key == RIGHTKEY)
		{
			if (currentPosition.getX() < MAX_X && currentPosition.getX() < storing_array[user_y])
			{
				currentPosition.incrementX();
				iter1++;
			}
			else if (currentPosition.getY() < MAX_Y && currentPosition.getY() < storing_array[user_y+1] != 0 )
			{
				currentPosition.incrementY();
				currentPosition.setX(0);
				user_y++;
				iter1++;
				
			}
		}
		else if (specialKey && key == UPKEY)
		{
			if (currentPosition.getY() > 0)
			{
				if(storing_array[user_y] > storing_array[user_y - 1])
				{
					for (int i = 0; i <= storing_array[user_y]; i++)
					{
						iter1--;
					}
					currentPosition.decrementY();
					user_y--;
					currentPosition.setX(storing_array[user_y]);
				}
				else
				{
					for (int i = 0; i < storing_array[user_y - 1]; i++)
					{
						iter1--;
					}
					currentPosition.decrementY();
					user_y--;
				}
				
			}
		}	
		else if (specialKey&&key == DOWNKEY)
		{	//Update it so that cursur not move downword if it is at last line of text.
			if (storing_array[user_y + 1] != 0 && storing_array[user_y] > storing_array[user_y + 1])
			{
				for (int i = 0; i < (storing_array[user_y] - currentPosition.getX()) + storing_array[user_y + 1]; i++)
				{
					iter1++;
				}
				currentPosition.incrementY();
				user_y++;
				currentPosition.setX(storing_array[user_y]);
			}
			else if(storing_array[user_y + 1] != 0)
			{
				for (int i = 0; i < storing_array[user_y]; i++)
				{
					iter1++;
				}
				currentPosition.incrementY();
				user_y++;
			}
		}
		else if (key == ENTERKEY){
			//cout << ('\n');
			list1.insert(iter1, '\n');
			//currentPosition.incrementX();
			storing_array[user_y] = currentPosition.getX();
			currentPosition.setX(0);
			currentPosition.incrementY();
			user_y++;
			user_x = 0;
		}
		else if (key == DELKEY)
		{
			//call a function to handle 
			if (currentPosition.getX() < user_x )
			{
				user_x--;
				storing_array[user_y] = user_x;

				list1.Delete(iter1);
				//cursor and printing handling
				store_x_cursor = currentPosition.getX();
				store_y_cursor = currentPosition.getY();
				currentPosition.setX(0);
				currentPosition.setY(0);
				ClearScreen();
				PlaceCursor(0, 0);
				list1.print();							//handling my own data and cursor
				currentPosition.setX(store_x_cursor);
				currentPosition.setY(store_y_cursor);
				PlaceCursor(store_x_cursor, store_y_cursor);
			}
			
			/*handling cursor till here*/
		}
		else if (key == BACKSPACE)
		{
			if (currentPosition.getX() > 0)
			{
				if (user_x != 0)
				{
					user_x--;
					storing_array[user_y] = user_x;
					currentPosition.setX((currentPosition.getX() - 1));
				}
				else if (user_x == 0 && user_y > 0)
				{
					user_y--;
					user_x = storing_array[user_y];
					currentPosition.setX(user_x);
					currentPosition.decrementY();
				}

				list1.BackSpace_delete(iter1);
				store_x_cursor = currentPosition.getX();
				store_y_cursor = currentPosition.getY();
				currentPosition.setX(0);
				currentPosition.setY(0);
				ClearScreen();
				PlaceCursor(0, 0);
				list1.print();							//handling my own data and cursor
				currentPosition.setX(store_x_cursor);
				currentPosition.setY(store_y_cursor);
				PlaceCursor(store_x_cursor, store_y_cursor);
			}
			else if (currentPosition.getX() == 0 && currentPosition.getY() > 0)
			{
				user_y--;
				
				user_x = storing_array[user_y];
				int temp_x = user_x + storing_array[user_y + 1];
				if (temp_x - MAX_X > 0)
				{
					storing_array[user_y] = MAX_X;
					storing_array[user_y + 1] = temp_x - MAX_X;
					user_x = MAX_X;
				}
				else
				{
					storing_array[user_y] = temp_x;
					storing_array[user_y + 1] = 0;
					user_x = temp_x;
				}
				currentPosition.setX(user_x);
				currentPosition.decrementY();
				list1.BackSpace_delete(iter1);
				store_x_cursor = currentPosition.getX();
				store_y_cursor = currentPosition.getY();
				currentPosition.setX(0);
				currentPosition.setY(0);
				ClearScreen();
				PlaceCursor(0, 0);
				list1.print();							//handling my own data and cursor
				currentPosition.setX(store_x_cursor);
				currentPosition.setY(store_y_cursor);
				PlaceCursor(store_x_cursor, store_y_cursor);
			}
		}
		else if (key == F1KEY || key == F2KEY || key == F3KEY)
		{
			//handle search here
			//you can take the cursor at the bottom of the screen and get some input
			//for searching

			int orginal_x = currentPosition.getX();
			int orginal_y = currentPosition.getY();

			PlaceCursor(0, MAX_Y);
			for (int i = 0; i < MAX_X; i++)					//clearing previous input data from search
			{
				cout << ' ';
			}
			PlaceCursor(0, MAX_Y);
			cout << "Enter Search Query: "<<endl;
			currentPosition.setX(0 + strlen("Enter Search Text : "));
			currentPosition.setY(MAX_Y);
			

			if (key == F1KEY) {
				//Search for one instance of string and move cursor there

							//searching input
				int keyword = 0;
				bool itera_stop = false;
				DoublyLinkList<char> sm;
				DoublyLinkList<char>::iterator small = sm.begin();
				int count = 0;
				bool specKey = false;
				int temp_word = 0;
				while (!itera_stop)				//getting data from user for input
				{
					keyword = CheckWhichKeyPressed(specKey);

					if (keyword == ENTERKEY)
						itera_stop = true;
					else if (!specKey && keyword >= 32 && keyword <= 126)
					{
						char itera_ch = (char)keyword;
						sm.insert(small, itera_ch);
						if (count != 0)
						{
							small++;
						}
						count++;
						int temp_x_cursor = currentPosition.getX();
						int temp_y_cursor = currentPosition.getY();
						currentPosition.setX(0 + strlen("Enter Search Text : "));

						currentPosition.setY(MAX_Y);

						PlaceCursor(currentPosition.getX(), MAX_Y);
						sm.print();
						currentPosition.setX(temp_x_cursor);
						currentPosition.setY(temp_y_cursor);
						PlaceCursor(temp_x_cursor, temp_y_cursor);

						SetColorAtPoint(currentPosition.getX(), currentPosition.getY(), F_BLACK | B_Light_Green);

						currentPosition.incrementX();
					}
				}
				small = sm.begin();
				int f1_count = 0;
				bool f1_flag = false;
				DoublyLinkList<char>::iterator* fond = new DoublyLinkList<char>::iterator;
				//DoublyLinkList<char>::iterator fond = list1.search_first(small, count, f1_count, f1_flag);
				*fond = list1.search_first(small, count, f1_count, f1_flag);

				if (f1_flag)
				{
					int iterator_count = 0;
					iter1 = list1.begin();
					bool value_count_found = false;
					int value_count = 0;

					int i = 0;
					int j = 0;
					while (!value_count_found && storing_array[j] != 0)
					{
						i = 0;
						while (i < storing_array[j] && !value_count_found)
						{
							if (value_count == f1_count)
							{
								value_count_found = true;
							}
							else
							{
								i++;
								value_count++;
								iter1++;
							}
						}
						if (!value_count_found)
						{
							j++;
						}
					}

					int value_x;
					if (j == 0)
						value_x = i;
					else
						value_x = i - 1;
					int value_y = j;
					PlaceCursor(0, 0);
					//ClearScreen();
					list1.print();
					currentPosition.setX(value_x);
					currentPosition.setY(value_y);
					PlaceCursor(value_x, value_y);
				}
				else
				{
					currentPosition.setX(orginal_x);
					currentPosition.setY(orginal_y);
				}
			}
			else if(key == F2KEY)
			{
				//Search for all instances of string and Highlight them
				//searching input
				int keyword = 0;
				bool itera_stop = false;
				DoublyLinkList<char> sm;
				DoublyLinkList<char>::iterator small = sm.begin();
				int word_count = 0;
				bool specKey = false;
				while (!itera_stop)				//getting data from user for searching
				{
					keyword = CheckWhichKeyPressed(specKey);

					if (keyword == ENTERKEY)
						itera_stop = true;
					else if (!specKey && keyword >= 32 && keyword <= 126)
					{
						char itera_ch = (char)keyword;
						sm.insert(small, itera_ch);
						if (word_count != 0)
						{
							small++;
						}
						word_count++;
						int temp_x_cursor = currentPosition.getX();
						int temp_y_cursor = currentPosition.getY();
						currentPosition.setX(0 + strlen("Enter Search Text : "));

						currentPosition.setY(MAX_Y);

						PlaceCursor(currentPosition.getX(), MAX_Y);
						sm.print();
						currentPosition.setX(temp_x_cursor);
						currentPosition.setY(temp_y_cursor);
						PlaceCursor(temp_x_cursor, temp_y_cursor);

						SetColorAtPoint(currentPosition.getX(), currentPosition.getY(), F_BLACK | B_Light_Green);

						currentPosition.incrementX();
					}
				}
				small = sm.begin();
				int found_count = 0;
				DoublyLinkList<char>::iterator* fond = list1.search_ALL(small, found_count, word_count);

				if (fond != NULL)
				{
					//int iterator_count = 0;
					iter1 = list1.begin();
					int count_x = 0;
					int count_y = 0;
					for (int i = 0; i < found_count; i++)
					{
						while (fond[i] != iter1)
						{
							if (count_x < storing_array[count_y])
							{
								cout << *iter1;
								SetColorAtPoint(count_x, count_y, F_BLACK | B_Light_Blue);
								count_x++;
							}
							else
							{
								cout << endl;
								count_x = 0;
								count_y++;
							}

							iter1++;
						}
						for (int j = 0; j < word_count; j++)
						{
							if (count_x < storing_array[count_y])
							{
								cout << *iter1;
								SetColorAtPoint(count_x, count_y, F_Dark_Green | B_Yellow);
								count_x++;
							}
							else
							{
								cout << endl;
								count_x = 0;
								count_y++;
							}

							iter1++;
						}
					}
					list1.remaing_print(iter1, count_x, count_y);
					currentPosition.setX(orginal_x);
					currentPosition.setY(orginal_y);
					PlaceCursor(orginal_x, orginal_y);
				}
				else
				{
					currentPosition.setX(orginal_x);
					currentPosition.setY(orginal_y);
					PlaceCursor(orginal_x, orginal_y);
				}
			}
			else
			{
				//Search for all instances of string 
				//searching input
				int keyword = 0;
				int repl_keyword = 0;
				bool itera_stop = false;
				DoublyLinkList<char> sm;
				DoublyLinkList<char> rep;
				DoublyLinkList<char>::iterator small = sm.begin();
				DoublyLinkList<char>::iterator replace = rep.begin();
				int word_count = 0;
				int rep_word_count = 0;
				bool specKey = false;
				//search of a string
				while (!itera_stop)					//getting data from user for searching		
				{
					keyword = CheckWhichKeyPressed(specKey);

					if (keyword == ENTERKEY)
						itera_stop = true;
					else if (!specKey && keyword >= 32 && keyword <= 126)
					{
						char itera_ch = (char)keyword;
						sm.insert(small, itera_ch);
						if (word_count != 0)
						{
							small++;
						}
						word_count++;
						int temp_x_cursor = currentPosition.getX();
						int temp_y_cursor = currentPosition.getY();
						currentPosition.setX(0 + strlen("Enter Search Text : "));

						currentPosition.setY(MAX_Y);

						PlaceCursor(currentPosition.getX(), MAX_Y);
						sm.print();
						currentPosition.setX(temp_x_cursor);
						currentPosition.setY(temp_y_cursor);
						PlaceCursor(temp_x_cursor, temp_y_cursor);

						SetColorAtPoint(currentPosition.getX(), currentPosition.getY(), F_BLACK | B_Light_Green);

						currentPosition.incrementX();
					}
				}
				small = sm.begin();
				int found_count = 0;
				DoublyLinkList<char>::iterator* fond = list1.search_ALL(small, found_count, word_count);

				if (fond != NULL)
				{
					//int iterator_count = 0;
					iter1 = list1.begin();
					int count_x = 0;
					int count_y = 0;
					//printing of data after searching
					for (int i = 0; i < found_count; i++)
					{
						while (fond[i] != iter1)
						{
							if (count_x < storing_array[count_y])
							{
								cout << *iter1;
								SetColorAtPoint(count_x, count_y, F_BLACK | B_Light_Blue);
								count_x++;
							}
							else
							{
								//cout << endl;
								count_x = 0;
								count_y++;
							}

							iter1++;
						}
						for (int j = 0; j < word_count; j++)
						{
							if (count_x < storing_array[count_y])
							{
								cout << *iter1;
								SetColorAtPoint(count_x, count_y, F_Dark_Green| B_Yellow);
								count_x++;
							}
							else
							{
								//cout << endl;
								count_x = 0;
								count_y++;
							}

							iter1++;
						}
					}
					//printing of remaining elements 
					list1.remaing_print(iter1, count_x, count_y);
					//getting input of replace string

					PlaceCursor(0, MAX_Y);
					for (int i = 0; i < MAX_X; i++)					//clearing previous input data from search
					{
						cout << ' ';
					}

					PlaceCursor(0, MAX_Y + 2);
					for (int i = 0; i < MAX_X; i++)					//clearing previous input data from search
					{
						cout << ' ';
					}

					PlaceCursor(0, MAX_Y + 2);
					cout << "Enter Replace Query: " << endl;
					currentPosition.setX(0 + strlen("Enter Search  Text : "));
					currentPosition.setY(MAX_Y + 2);

					itera_stop = false;
					//input of replace string
					while (!itera_stop)				//getting data form user for replace of string
					{
						keyword = CheckWhichKeyPressed(specKey);

						if (keyword == ENTERKEY)
							itera_stop = true;
						else if (!specKey && keyword >= 32 && keyword <= 126)
						{
							char itera_ch = (char)keyword;
							rep.insert(replace, itera_ch);
							if (rep_word_count != 0)
							{
								small++;
							}
							rep_word_count++;
							int temp_x_cursor = currentPosition.getX();
							int temp_y_cursor = currentPosition.getY();
							currentPosition.setX(0 + strlen("Enter Search Text : "));

							currentPosition.setY(MAX_Y + 2);

							PlaceCursor(currentPosition.getX(), MAX_Y + 2);
							rep.print();
							currentPosition.setX(temp_x_cursor);
							currentPosition.setY(temp_y_cursor);
							PlaceCursor(temp_x_cursor, temp_y_cursor);

							SetColorAtPoint(currentPosition.getX(), currentPosition.getY(), F_BLACK | B_Light_Green);

							currentPosition.incrementX();
						}
					}
					replace = rep.begin();

					list1.Delete_multiple(fond, found_count, word_count);
					for (int i = 0; i < word_count * found_count; i++)		//placing cursor after deletion
					{
						if (orginal_x > 0)
						{
							orginal_x--;
							user_x--;
							storing_array[user_y]--;
							//user_max_x--;
						}
						else if(orginal_y > 0)
						{
							orginal_y--;
							user_y--;
							//user_max_x = MAX_X;
							user_x = storing_array[user_y];
							orginal_x = storing_array[user_y];

						}
					}

					list1.replace_All(fond, replace, found_count);

					for (int i = 0; i < rep_word_count * found_count; i++)		//placing cursor after replacement
					{
						if (orginal_x < MAX_X)
						{
							orginal_x++;
							user_x++;
							storing_array[user_y]++;
							//user_max_x++;
						}
						else if (orginal_y <MAX_Y)
						{
							orginal_y++;
							orginal_x = 0;
							user_x = 0;
							user_y++;
							//user_max_y++;
						}
					}

					int max = 0;
					for (int i = 0; i < 50; i++)
					{
						if (max < storing_array[i])
							max = storing_array[i];
					}

					if (max != MAX_X)
					{
						DoublyLinkList<char>::iterator t_travers = list1.begin();
						for (int i = 0; i < list1.getsize(); i++)
						{
							t_travers++;
						}

						DoublyLinkList<char>::iterator t_itera2 = list1.begin();
						for (int i = 0; storing_array[i] != 0; i++)
						{

							int j = 0;
							for (j; j < list1.getsize() && t_itera2 != t_travers; j++)
							{
								if (*t_itera2 == '\n')
								{
									storing_array[i] = j;
									t_itera2++;
									break;
								}
								else
								{
									t_itera2++;
								}
							}
							if (storing_array[i + 1] == 0)
							{
								storing_array[i] = j + 1;
							}
						}
					}

					PlaceCursor(0, 0);
					iter1 = list1.begin();
					count_x = 0;
					count_y = 0; 
					list1.remaing_print(iter1, count_x, count_y);


					currentPosition.setX(orginal_x);
					currentPosition.setY(orginal_y);
					PlaceCursor(orginal_x, orginal_y);
					
				}
				else
				{
					currentPosition.setX(orginal_x);
					currentPosition.setY(orginal_y);
					PlaceCursor(orginal_x, orginal_y);
				}
				store_x_cursor = currentPosition.getX();
				store_y_cursor = currentPosition.getY();
				currentPosition.setX(0);
				currentPosition.setY(0);
				ClearScreen();
				PlaceCursor(0, 0);
				list1.print();							//handling my own data and cursor
				currentPosition.setX(store_x_cursor);
				currentPosition.setY(store_y_cursor);
				PlaceCursor(store_x_cursor, store_y_cursor);
				// 
				//Take a second input string 
				//and replace all instances of first string with second string
			}

		}
		else if (key == F4KEY)
		{
			list1.file_storage();
		}
		PlaceCursor(currentPosition.getX(), currentPosition.getY());

	}

	return 0;
}

//-------------------------------------------End Main Editor--------------------------//
int main()
{
	mainEditor();
	//cout << __cplusplus << endl;
	return 0;
}
