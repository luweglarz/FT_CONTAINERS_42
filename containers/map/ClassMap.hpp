#ifndef map_HPP
#define map_HPP

#include <iostream>
#include <memory>
#include <functional>
#include "utility/pair.hpp"
#include "../../iterators/map_iterator.hpp"
#include "../../iterators/map_reverse_iterator.hpp"
#include "utility/StructRBT.hpp"
#include "../../SFINAE/enable_if.hpp"
#include "../../SFINAE/is_integral.hpp"
#include "../../iterators/lexicographical_compare.hpp"

namespace ft
{

    template < class Key, class T, class Compare = std::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map{
    public:
        typedef Key                                                 key_type;
        typedef T                                                   mapped_key;
        typedef ft::pair<const key_type, mapped_key>                value_type;
        typedef size_t                                              size_type;
        typedef std::ptrdiff_t                                      difference_type;
        typedef Compare                                             key_compare;

        typedef Alloc                                               allocator_type;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
    private:
        typedef RBT<value_type, key_compare>                        Tree;
        typedef typename Tree::node                                 node;
        typedef typename Tree::pointer                              ptrnode;
        typedef typename Tree::allocator_type                       Nalloc;
    public:
        typedef ft::map_iterator<Tree, value_type>                              iterator;
        typedef ft::map_iterator<const Tree, const value_type>    const_iterator;
        typedef ft::map_reverse_iterator<iterator>                  reverse_iterator;
        typedef ft::map_reverse_iterator<const_iterator>            const_reverse_iterator;

        explicit map(const Compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): _mallocator(alloc), _size(0), _cmp(comp), 
                    _RBT(), _nallocator(){
        }

        template <class InputIterator>
        explicit map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0):
                    _mallocator(alloc),_size(0), _cmp(comp), _RBT(), _nallocator(){
            insert(first, last);
        }

        map(const map &x):_size(0), _RBT(){
            *this = x;
        }

        map &operator=(const map &x){
            _mallocator = x._mallocator;
            clear();
            _cmp = x._cmp;
            const_iterator it = x.begin();
            
            node def;
            _RBT.leafs = _nallocator.allocate(1);
            _nallocator.construct(_RBT.leafs, def);
            _RBT.leafs->content = NULL;
            _RBT.last = _RBT.leafs;

			while(it != x.end()){
				insert(*it);
                it++;
			}
            
            return (*this);
        }

        ~map(){
            if (_size > 0)
                erase(begin(), end());
        }

        iterator begin(){
            return (iterator(_RBT.first, &_RBT));
        }
        
        const_iterator begin() const{
            return (const_iterator(_RBT.first, &_RBT));
        }

        iterator end(){
            return (iterator(_RBT.last, &_RBT));
        }

        const_iterator end() const{
            return (const_iterator(_RBT.last, &_RBT));
        }

        reverse_iterator rbegin(){
            return (reverse_iterator(iterator(_RBT.last, &_RBT)));
        }

        const_reverse_iterator rbegin() const{
            return (const_reverse_iterator(const_iterator(_RBT.last, &_RBT)));
        }

        reverse_iterator rend(){
            return (reverse_iterator(iterator(_RBT.first, &_RBT)));
        }

        const_reverse_iterator rend() const {
            return (const_reverse_iterator(const_iterator(_RBT.first, &_RBT)));
        }

        allocator_type get_allocator() const{
            return (_mallocator);
        }

        bool empty() const{
            if(_size == 0)
                return (true);
            else
                return (false);
        }

        size_type size() const{
            return (_size);
        }

        size_type max_size() const{
            return ((_nallocator.max_size()));
        }

        mapped_key &operator[](const Key &key){
            iterator itret;
            if (_size > 0 && (itret = find(key)) != end())
                return (itret->second);
            ft::pair<iterator, bool> ret = insert(ft::make_pair(key, mapped_key()));
            return (ret.first->second);
        }
        void clear(){
            if (_size > 0)
                erase(begin(), end());
        }

        void erase(iterator pos){
           erase(pos->first);
        }

        void erase(iterator first, iterator last){
            iterator tmp = first;
            while (first != last){
                tmp++;
                erase(first);
                first = tmp;
            }
        }

        size_type erase(const Key &key){
            ptrnode current = _RBT.root;
            if (_size == 1){
                _mallocator.destroy(current->content);
                _nallocator.destroy(current);
                _mallocator.deallocate(current->content, 1);
                _nallocator.deallocate(current, 1);
                _size--;
                _RBT.root = NULL;
                _RBT.last = NULL;
                _RBT.first = NULL;
                return (1);
            }
            while (current != _RBT.leafs && current->content->first != key){
                if (key < current->content->first)
                    current = current->left;
                else
                    current = current->right;
            }
            if (current == _RBT.leafs)
                return (0);
            ptrnode tmp1, tmp2;
            tmp1 = current;
            int tmp1_color = tmp1->color;
            if (current->left == _RBT.leafs){
                tmp2 = current->right;
                _RBT.transplant(current, current->right);
            }
            else if (current->right == _RBT.leafs){
                tmp2 = current->left;
                _RBT.transplant(current, current->left);
            }
            else{
                tmp1 = _RBT.find_min(current->right);
                tmp1_color = tmp1->color;
                tmp2 = tmp1->right;
                if (tmp1->parent == current)
                    tmp2->parent = tmp1;
                else{
                    _RBT.transplant(tmp1, tmp1->right);
                    tmp1->right = current->right;
                    tmp1->right->parent = tmp1;
                }
                _RBT.transplant(current, tmp1);
                tmp1->left = current->left;
                tmp1->left->parent = tmp1;
                tmp1->color = current->color;
            }
            _mallocator.destroy(current->content);
            _nallocator.destroy(current);
            _mallocator.deallocate(current->content, 1);
            _nallocator.deallocate(current, 1);
            if (tmp1_color == BLACK)
                check_rules_delete(tmp2);
            _size--;
            _RBT.first = _RBT.find_min(_RBT.root);
            return (1);
        }

        pair<iterator, bool> insert(const value_type &val){
            node  def;
            ptrnode newnode = _nallocator.allocate(1);
            _nallocator.construct(newnode, def);
            newnode->right = _RBT.leafs;
            newnode->left = _RBT.leafs;
            ptrnode current = _RBT.root;
            ptrnode newnode_parent;
            newnode->content = _mallocator.allocate(1);
            _mallocator.construct(newnode->content, val);
            if (_size == 0){
                _RBT.root = newnode;
                _RBT.first = newnode;
                _size++;
                return (ft::make_pair(begin(),true));
            }
            if (count(val.first) == 1)
                return (ft::make_pair(find(val.first), false));
            while (current != _RBT.leafs){
                newnode_parent = current;
                if (_cmp(*newnode->content, *current->content))
                    current = current->left;
                else
                    current = current->right;
            }
            newnode->parent = newnode_parent;
            if (newnode_parent == _RBT.leafs)
                _RBT.root = newnode;
            if (_cmp(*newnode->content, *newnode_parent->content))
                newnode_parent->left = newnode;
            else
                newnode_parent->right = newnode;
            newnode->color = RED;
            _size++;
            check_rules_insert(newnode);
            if (_cmp(*newnode->content, *_RBT.first->content))
                _RBT.first = newnode;
            return (ft::make_pair(iterator(newnode, &_RBT),true));
        }
        
        iterator insert(iterator hint, const value_type &value){
            (void)hint;
            pair<iterator, bool> ret;
            ret = insert(value);
            return(ret.first);
        }
        
        template<class InputIterator>
        void insert(InputIterator first, InputIterator last,
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0){
            while (first != last){
                insert(*first);
                first++;
            }
        }

        void swap(map &other){
            std::swap(_RBT.root, other._RBT.root);
            std::swap(_RBT.leafs, other._RBT.leafs);
            std::swap(_RBT.last, other._RBT.last);
            std::swap(_RBT.first, other._RBT.first);
            std::swap(_size, other._size);
        }

        size_type count(const Key &key) const{
            if (find(key) != end())
                return (1);
            return (0);
        }

        iterator find(const Key &key){
            ptrnode current = _RBT.root;
            while (current != _RBT.leafs && current->content->first != key){
                if (key < current->content->first)
                    current = current->left;
                else
                    current = current->right;
            }
            if (current != _RBT.leafs)
                return (iterator(current, &_RBT));
			return (end());
        }

        const_iterator find(const Key &key) const{
            ptrnode current = _RBT.root;
            while (current != _RBT.leafs && current->content->first != key){
                if (key < current->content->first)
                    current = current->left;
                else
                    current = current->right;
            }
            if (current != _RBT.leafs)
                return (const_iterator(current, &_RBT));
			return (end());
        }

        ft::pair<iterator,iterator> equal_range(const Key &key){
            ft::pair<iterator, iterator>	ret;

			ret.first = lower_bound(key);
			ret.second = upper_bound(key);
			return (ret);
        }

        ft::pair<const_iterator,const_iterator> equal_range(const Key &key) const{
            ft::pair<const_iterator, const_iterator>	ret;

			ret.first = lower_bound(key);
			ret.second = upper_bound(key);
			return (ret);
        }

        iterator lower_bound(const Key &key){
            iterator it = begin();
            ft::pair<Key, mapped_key> tpair = ft::make_pair(key, mapped_key());
            while (it != end()){
                if (!(_cmp(*it, tpair)))
                    return (it);
                it++;
            }
            return (end());
        }

        const_iterator lower_bound(const Key &key) const{
            const_iterator it = begin();
            ft::pair<Key, mapped_key> tpair = ft::make_pair(key, mapped_key());
            while (it != end()){
                if (!(_cmp(*it, tpair)))
                    return (it);
                it++;
            }
            return (end());
        }

        iterator upper_bound(const Key &key){
            iterator it = begin();
            ft::pair<Key, mapped_key> tpair = ft::make_pair(key, mapped_key());
            while (it != end()){
                if (!(_cmp(*it, tpair)) && _cmp(tpair, *it))
                    return (it);
                it++;
            }
            return (end());
        }

        const_iterator upper_bound(const Key &key) const{  
            const_iterator it = begin();
            ft::pair<Key, mapped_key> tpair = ft::make_pair(key, mapped_key());
            while (it != end()){
                if (!(_cmp(*it, tpair)) && _cmp(tpair, *it))
                    return (it);
                it++;
            }
            return (end());
        }

        class value_compare : public std::binary_function<value_type, value_type, bool>{
        public:
            value_compare(key_compare cmp = key_compare()): comp(cmp) {}

            bool operator()(const value_type &lhs, const value_type &rhs) const {return (comp(lhs.first, rhs.first));}
        protected:
            key_compare comp;
        };

        key_compare key_comp() const{
            return(key_compare());
        }

        value_compare value_comp() const{
            return (value_compare(key_compare()));
        }

    private:
        allocator_type      _mallocator;
        size_type           _size;
        value_compare       _cmp;
        Tree                _RBT;
        Nalloc              _nallocator;
    
        void    check_rules_insert(ptrnode newnode){
            ptrnode def;
            if (newnode->parent == NULL){
                newnode->color = BLACK;
                return ;
            }
            if (newnode->parent->parent == NULL)
                return ;
            while (newnode->parent->color == RED){
                if (newnode->parent == newnode->parent->parent->right){
                    def = newnode->parent->parent->left;
                    if (def && def->color == RED){
                        def->color = BLACK;
                        newnode->parent->color = BLACK;
                        newnode->parent->parent->color = RED;
                        newnode = newnode->parent->parent;
                    }
                    else{
                        if (newnode == newnode->parent->left){
                            newnode = newnode->parent;
                            _RBT.rotate_right(newnode);
                        }
                        newnode->parent->color = BLACK;
                        newnode->parent->parent->color = RED;
                        _RBT.rotate_left(newnode->parent->parent);
                    }
                }
                else{
                    def = newnode->parent->parent->right;
                    if (def && def->color == RED){
                        def->color = BLACK;
                        newnode->parent->color = BLACK;
                        newnode->parent->parent->color = RED;
                        newnode = newnode->parent->parent;
                    }
                    else{
                        if (newnode == newnode->parent->right){
                            newnode = newnode->parent;
                            _RBT.rotate_left(newnode);
                        }
                        newnode->parent->color = BLACK;
                        newnode->parent->parent->color = RED;
                        _RBT.rotate_right(newnode->parent->parent);
                    }
                }
                if (newnode == _RBT.root)
                    break;
            }
            _RBT.root->color = BLACK;
        }
    
        void    check_rules_delete(ptrnode deletednode){
            ptrnode tmp;
            while (deletednode != _RBT.root && deletednode->color == BLACK){
                if (deletednode == deletednode->parent->left){
                    tmp = deletednode->parent->right;
                    if (tmp->color == RED){
                        tmp->color = BLACK;
                        deletednode->parent->color = RED;
                        _RBT.rotate_left(deletednode->parent);
                        tmp = deletednode->parent->right;
                    }
                    if (tmp->left->color == BLACK && tmp->right->color == BLACK){
                        tmp->color = RED;
                        deletednode = deletednode->parent;
                    }
                    else {
                        if (tmp->right->color == BLACK){
                            tmp->left->color = BLACK;
                            tmp->color = RED;
                            _RBT.rotate_right(tmp);
                            tmp = deletednode->parent->right;
                        }
                        tmp->color = deletednode->parent->color;
                        deletednode->parent->color = BLACK;
                        tmp->right->color = BLACK;
                        _RBT.rotate_left(deletednode->parent);
                        deletednode = _RBT.root;
                    }
                }
                else{
                    tmp = deletednode->parent->left;
                    if (tmp->color == RED){
                        tmp->color = BLACK;
                        deletednode->parent->color = RED;
                        _RBT.rotate_right(deletednode->parent);
                        tmp = deletednode->parent->left;
                    }
                    if (tmp->right->color == BLACK && tmp->right->color == BLACK){
                        tmp->color = RED;
                        deletednode = deletednode->parent;
                    }
                    else {
                        if (tmp->left->color == BLACK){
                            tmp->right->color = BLACK;
                            tmp->color = RED;
                            _RBT.rotate_left(tmp);
                            tmp = deletednode->parent->left;
                        }
                        tmp->color = deletednode->parent->color;
                        deletednode->parent->color = BLACK;
                        tmp->left->color = BLACK;
                        _RBT.rotate_right(deletednode->parent);
                        deletednode = _RBT.root;
                    }
                }
            }
            deletednode->color = BLACK;
        }
    };

    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs){
        typename ft::map<Key, T>::const_iterator b1 = lhs.begin();
        typename ft::map<Key, T>::const_iterator b2 = rhs.begin();
        if (lhs.size() != rhs.size())
            return (false);
        while (b1 != lhs.end() && b2 != rhs.end()){
            if (*b1 != *b2)
                return (false);
            b1++;
            b2++;
        }
        return (true);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs){
        return (!(lhs == rhs));
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs){
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), lhs.value_comp()));                
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs){
        return (lhs == rhs || lhs < rhs);              
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs){
        return (rhs < lhs);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs){
        return (lhs == rhs || rhs < lhs);           
    }
}

#endif