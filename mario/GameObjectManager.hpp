/** @file */
#pragma once
#include <string>

//! Game object manager
/**
 * Holds game objects
 * Because it is a generic class all code is in header
 */
template<typename T> class GameObjectManager {
public:

	/**
	 * Basic class constructor null initialize node head and last item pointers
	*/
	GameObjectManager()
	{
		nodeHead = nullptr;
		nodeLastItem = nullptr;
	}

	/**  
	 * Operator overload
	 * Adds a new node to the list using "+" sign
	 */
	void operator + (T const& obj)
	{
		addItem(obj);
	}

	/**
	 * Operator overload
	 * Removes node form the list using "-" sign
	 */
	void operator - (T const& obj)
	{
		deleteItem(obj);
	}

	//! Node struct
	/**
	 * One item in the list
	 */
	struct Node
	{
		T* gameObject;  ///< Stored item
		std::string objectName; ///< Stored item name
		Node* next = nullptr;   ///< Next element
		Node* prev = nullptr;   ///< Previous element

		/**
		 * Removes stored item form memory
		 */
		~Node()
		{
			delete gameObject;
		}

		/**
		 * Constructor which creates a new node element
		 *
		 * @param object to store
		 * @param object name
		 */
		Node(T* gameObject, std::string objectName)
		{
			this->gameObject = gameObject;
			this->objectName = objectName;
			next = nullptr;
			prev = nullptr;
		}

		/**
		 * Operator overload
		 * Select next element in the list using "++"
		 */
		Node& operator++()
		{
			this = this->next;
			return *this;
		}

	};

	/**
	 * Adds a new item to the list
	 */
	void addItem(T* gameObject, std::string objectName)
	{
		Node* item = new Node(gameObject, objectName);

		if (nodeHead == nullptr) {
			nodeHead = item;
		}
		if (nodeLastItem != nullptr) {
			nodeLastItem->next = item;
			item->prev = nodeLastItem;
		}
		nodeLastItem = item;
	}

	/**
	 * Removes item form the list
	 */
	void deleteItem(Node* item)
	{
		if (nodeHead == item) {
			if (item->next != nullptr) {
				nodeHead = item->next;
			}else {
				nodeHead = nullptr;
			}
		}
		if (item->next != nullptr) {
			if (item->prev != nullptr) {
				item->next->prev = item->prev;
			}
			else {
				item->next->prev = nullptr;
			}
		}
		if (item->prev != nullptr) {
			if (item->next != nullptr) {
				item->prev->next = item->next;
			}
			else {
				item->prev->next = nullptr;
			}
		}
		item = nullptr;
		delete item;
	}

	/**
	 * Finds a given object by the name
	 */
	Node* findByObjectName(std::string objectName)
	{
		Node* m = getNodeHead();
		while (m != nullptr) {
			if (objectName == m->objectName)
				return m;
			m = m->next;
		}
		return nullptr;
	}

	/**
	 * Get the head of list
	 */
	Node* getNodeHead()
	{
		return nodeHead;
	}


	/**
	 * Destructor
	 * Deletes all items from the list.
	 */
	~GameObjectManager()
	{
		freeMem(nodeHead);
	}

private:

	Node* nodeHead; ///< Pointer to the first element in the list
	Node* nodeLastItem; ///< Pointer to the last element in the list

	/**
	 *
	 * Deletes all items from the list.
	 * This is the part of the code where all memory reserved by the list is freed.
	 */
	void freeMem(Node* node) const
	{
		if (node == nullptr) {
			return;
		}
		if ((node->next) != nullptr)  freeMem(node->next);
		node = nullptr;
		delete node;
	}
	
};
