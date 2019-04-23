#ifndef LIST_H
#define LIST_H

#include "node.h"

template <typename Tr>
class List {     
    public:
        typedef typename Tr::T T;
        typedef typename Tr::Operation Operation;
      
    private:
        Node<T>* head;
        Operation cmp;
              
    public:
        List() : head(nullptr) {};

        bool find(T search, Node<T> **pointer) {
		Node<T> *tmp=*pointer;
		while(tmp){
			if(tmp->data==search)
				return true;
			tmp=tmp->next;
		}
		return false;
        }
             
        bool insert(T data){
		if(this->head){
			if(find(data,&(this->head)))
				return false;
			Node<T>*tmp=this->head;
			bool faro=false;
			while(cmp(tmp->data,data)){
				if(!tmp->next){
					faro=true;
					break;
				}
				tmp=tmp->next;
			}
			Node<T>* nuevo=new Node<T>{data};
			if(faro){
				tmp->next=nuevo;
				nuevo->prev=tmp;
			}
			else{
				if(tmp==this->head){
					nuevo->next=tmp;
					tmp->prev=nuevo;
					this->head=nuevo;
				}
				else{
					tmp->prev->next=nuevo;
					nuevo->next=tmp;
					nuevo->prev=tmp->prev;
					tmp->prev=nuevo;
				}
			}
		}
		else
			this->head=new Node<T>(data);

		return true;
        }
             
        bool remove(T item) {
		if(find(item,&(this->head))){
			Node<T>*tmp=this->head;
			while(tmp->data!=item)
				tmp=tmp->next;
			
			if(tmp!=this->head){
				if(tmp->next){
					tmp->prev->next=tmp->next;
					tmp->next->prev=tmp->prev;
				}
				else
					tmp->prev->next=nullptr;
				tmp->killOnlyMe();
			}
			else{
				if(this->head->next){
					tmp=tmp->next;
					this->head->killOnlyMe();
					this->head=tmp;
				}
				else{
					this->head->killOnlyMe();
					this->head=nullptr;
				}
			}
			return true;
		}
		return false;
        }  
             
        int size() {
		int sizel=0;
		Node<T>* tmp=this->head;
		while(tmp!=nullptr){
			tmp=tmp->next;
			sizel++;
		}
		return sizel;
        }

        T operator[](int index) {
		if(index>size()-1)
			throw runtime_error("Indice ingresado es mayor al size de la lista\n");
		

		Node<T>* tmp=head;
		while(index--)
			tmp=tmp->next;
		
		return tmp->data;
        }

        ~List() {
		if(this->head)
			this->head->killSelf();
        }         
};

#endif
