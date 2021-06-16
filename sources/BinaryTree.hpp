#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <iomanip>

using namespace  std;
namespace ariel
{
	template<typename T>

	class BinaryTree {

		struct Node {
			T value;
			Node* right = nullptr;
			Node* parent = nullptr;
			Node* left = nullptr;
			Node(T val) : value(val), right(nullptr), left(nullptr), parent(nullptr){}
		};

		// fanctio to search node ;
		Node* searchNode(Node* n, T  val) {
			if (n == nullptr)
			{
				return nullptr;
			}
			if (n->value == val)
			{
				return n;
			}
			Node* _right = searchNode(n->right, val);
			if (_right != nullptr)
			{
				return _right;
			}
			return searchNode(n->left, val);
		}


		Node *root;
		class preorder_iterator {
		private:
			Node* p_node;
			queue<Node*> queue1;
		public:
			void addNodesToQueue(Node* n){
				if (n == nullptr)
					return;
				queue1.push(n);
				addNodesToQueue(n->left);
				addNodesToQueue(n->right);
			}
			preorder_iterator(Node* n = nullptr) : p_node(n) {
				addNodesToQueue(n);
				if (n != nullptr){
					p_node = queue1.front();
				}
			}

			T& operator*() const {
				return p_node->value;
			}

			T* operator->() const {
				return &(p_node->value);
			}

			preorder_iterator &operator++(){
				queue1.pop();
				if (queue1.empty()){
					p_node = nullptr;
				}
				else{
					p_node = queue1.front();
				}
				return *this;
			}

			preorder_iterator operator++(int) {
				preorder_iterator tmp = *this;
				++(*this);
				return tmp;
			}

			bool operator==(const preorder_iterator& other) const {
				return p_node == other.p_node;
			}

			bool operator!=(const preorder_iterator& other) const {
				return p_node != other.p_node;
			}
		};
		////////////////////////
		class inorder_iterator {
		private:
			Node* p_node;
			queue<Node*>queue2;
		public:
			void addNodesToQueue(Node* n){
				if (n == nullptr)
					return;

				addNodesToQueue(n->left);
				queue2.push(n);
				addNodesToQueue(n->right);

			}
			inorder_iterator(Node* n = nullptr) : p_node(n) {
				addNodesToQueue(n); 
				if (n != nullptr){
					p_node = queue2.front();
				}
			}

			T& operator*() const {
				return p_node->value;
			}

			T* operator->() const {
				return &(p_node->value);
			}
			inorder_iterator &operator++()
			{
				queue2.pop();
				if (queue2.empty()){
					p_node = nullptr;
				}
				else{
					
					p_node = queue2.front();
				}
				return *this;
			}
			inorder_iterator operator++(int) {
				inorder_iterator tmp = *this;
				++(*this);
				return tmp;

			}

			bool operator==(const inorder_iterator& other) const {
				return p_node == other.p_node;
			}

			bool operator!=(const inorder_iterator& other) const {
				return p_node != other.p_node;
			}
		};  // end od iterato_inorder!!!!!!

		class postorder_iterator {
		private:
			Node* p_node;
			queue<Node*>queue3;
		public:

			void addNodesToQueue(Node* n){
				if (n == nullptr)
					return;
				
				addNodesToQueue(n->left);
				addNodesToQueue(n->right);
				queue3.push(n);
			}
			postorder_iterator(Node* n = nullptr) : p_node(n) {
				addNodesToQueue(n);
				if (n != nullptr){
					p_node = queue3.front();
				}
			}

			T& operator*() const {
				return p_node->value;
			}

			T* operator->() const {
				return &(p_node->value);
			}

			postorder_iterator& operator++() {
				queue3.pop();
				if (queue3.empty()){
					p_node = nullptr;
				}
				else{
					
					p_node = queue3.front();
				}
				return *this;
			}

			postorder_iterator operator++(int) {
				postorder_iterator tmp = *this;
				++(*this);
				return tmp;

			}

			bool operator==(const postorder_iterator& other) const {
				return p_node == other.p_node;
			}

			bool operator!=(const postorder_iterator& other) const {
				return p_node != other.p_node;
			}
		};



	public:
		BinaryTree() :root(nullptr){};

		~BinaryTree(){
			if (root != nullptr){
				deleteElements(root);
			}
		}
		// bnai m3tek 
		BinaryTree(const BinaryTree &other){
			*this = other;
		}

		// operator shel hsma bshvel h3tka 3moka !
		BinaryTree<T>& operator=(const BinaryTree& other){
			if (this != &other)
			{
				if (this->root != nullptr){
					deleteElements(root);
				}
				if (other.root != nullptr){
					root = copy_of_tree(other.root);
				}
				else {
					throw ("Erorre!!");
				}
			}
			return *this;
		}
        BinaryTree(BinaryTree&& other) noexcept{
			*this = std::move(other);
		}

		BinaryTree& operator=(BinaryTree&& other) noexcept{
			if (this != &other)
			{
				root = other.root;
				other.root = nullptr;
			}
			return *this;
		}

		void deleteElements(Node* n){
			if (n == nullptr){
				return;
			}
			deleteElements(n->left);
			deleteElements(n->right);
			delete n;
		}
		BinaryTree<T>& add_root(T val){
			if (root == nullptr){
				root = new Node(val);
			}
			else {
				root->value = val;
			}
			return *this;
		}
		Node* copy_of_tree(Node *other){
			if (other == nullptr){
				return nullptr;
			}
			Node* n = new Node(other->value);
			n->parent = other->parent;
			n->right = copy_of_tree(other->right);
			n->left = copy_of_tree(other->left);
			return n;
		}


		BinaryTree<T>& add_left(const T& p, const T& l_node){

			Node *d = searchNode(root, p);
			if (d == nullptr){
				throw ("Error!");
			}
			if (d->left != nullptr)
			{
				d->left->value = l_node;
			}
			else
			{
				d->left = new Node(l_node);
				d->left->parent = d;
			}
			return *this;
		}
		


		BinaryTree<T>& add_right(const T& p, const T& r_node){
			Node *d = searchNode(root, p);
			if (d == nullptr){
				throw ("Error!");
			}
			if (d->right != nullptr)
			{
				d->right->value = r_node;
			}
			else
			{
				d->right = new Node(r_node);
				d->right->parent = d;
			}
			return *this;
		}

		inorder_iterator begin(){
			return inorder_iterator{ root };
		}
		inorder_iterator end(){
			return inorder_iterator{ nullptr };
		}

		preorder_iterator begin_preorder(){
			return preorder_iterator{ root };
		}
		preorder_iterator end_preorder(){
			return preorder_iterator{ nullptr };
		}

		postorder_iterator begin_postorder(){
			return postorder_iterator{ root };
		}
		postorder_iterator end_postorder(){
			return postorder_iterator{ nullptr };
		}

		inorder_iterator begin_inorder(){
			return inorder_iterator{ root };
		}

		inorder_iterator end_inorder(){
			return inorder_iterator{ nullptr };
		}

		void printSpaces(ostream &os, int n) const{
			for (int i = 0; i < n; i++)
			{
				os << ' ';
			}
		}

		void print(ostream &os, Node* p, int indent=0) const
		{
			if (p != NULL) {
				print(os, p->right, indent + 4);
				os << endl;
				printSpaces(os, indent);
				os << p->value << endl;
				//printSpaces(os, indent);
				print(os, p->left, indent + 4);
			}
		}

		friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &b)
		{
			b.print(os, b.root);
			return os;
		}
	}; // END OF BinaryTree

}