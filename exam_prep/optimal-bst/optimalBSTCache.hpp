#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "cache.hpp"
#include "hashFunc.hpp"
#include "sumDB.hpp"

template<typename Key, typename Value, typename Number>
class OptimalBSTCache: public Cache<Key, Value> {
public:
    struct DataEntry {
        Key key;
        Value value;
        Number stat;
    };

    using Data = std::vector<DataEntry>;

private:
    class BST {
    private:
        struct Node {
            uint64_t key;
            Value value;
            Node* left;
            Node* right;

            ~Node() {
                delete left;
                delete right;
            }
        };

        struct Entry {
            Number value;
            std::size_t root;
        };

        struct Builder {
            const Data& data;
            HashFunc<Key>& hashFunc;
            const std::vector<std::vector<Entry>>& table;

            Node* build(std::size_t b, std::size_t e) {
                if(b > e) {
                    return nullptr;
                }
                std::size_t r = table[b - 1][e - 1].root + 1;
                DataEntry entry = data[r - 1];
                return new Node{
                    hashFunc.hash(entry.key),
                    entry.value,
                    build(b, r - 1),
                    build(r + 1, e)
                };
            }
        };

    private:
        static std::pair<bool, const Value*> find(const Node* node, uint64_t key) {
            if(node == nullptr) {
                return std::make_pair(false, nullptr);
            }
            if(node->key == key) {
                return std::make_pair(true, &node->value);
            }
            if(node->key < key) {
                return find(node->right, key);
            }
            return find(node->left, key);
        }

    private:
        std::pair<Node*, Number> tree;

    private:
        static std::pair<Node*, Number> findOptimal(Data& data, HashFunc<Key>& hashFunc) {
            std::size_t n = data.size();
            std::sort(data.begin(), data.end(), [&hashFunc](const DataEntry& a, const DataEntry&b) {
                return hashFunc.hash(a.key) < hashFunc.hash(b.key);
            });
            SumDB<Number> sumDB(takeStat(data));
            auto t = std::vector<std::vector<Entry>>(n, std::vector<Entry>(n, {0, n}));
            for(std::size_t i = 0; i < n; i++) {
                t[i][i] = {data[i].stat, i};
            }
            for(std::size_t d = 1; d < n; d++) {
                for(std::size_t b = 0; b < n - d; b++) {
                    std::size_t e = b + d;
                    for(std::size_t r = b; r <= e; r++) {
                        Number c = sumDB.query(b + 1, e + 1);
                        if(b <= r - 1) {
                            c += t[b][r - 1].value;
                        }
                        if(r + 1 <= e) {
                            c += t[r + 1][e].value;
                        }
                        Number curr = t[b][e].value;
                        if(curr == 0 || c < curr) {
                            t[b][e] = {c, r};
                        }
                    }
                }
            }
            Builder builder = {data, hashFunc, t};
            return std::make_pair(builder.build(1, n), t[0][n - 1].value);
        }

        static void print(std::ostream& out, const Node* node) {
            if(node == nullptr) {
                out << "<>";
            } else {
                out << "[";
                print(out, node->left);
                out << node->value;
                print(out, node->right);
                out << "]";
            }
        } 

    public:
        BST(Data& data, HashFunc<Key>& hashFunc): tree(findOptimal(data, hashFunc)) { }

        ~BST() {
            auto root = tree.first;
            if(root != nullptr) {
                delete root;
                root = nullptr;
            }
        }

        std::pair<bool, const Value*> find(uint64_t key) {
            return find(tree.first, key);
        }

        Number score() const {
            return tree.second;
        }

        void print(std::ostream& out) const {
            print(out, tree.first);
        }
    };

private:
    static typename SumDB<Number>::Array takeStat(const Data& data) {
        std::size_t n = data.size();
        auto stat = typename SumDB<Number>::Array(n);
        for(std::size_t i = 0; i < n; i++) {
            stat[i] = data[i].stat;
        }
        return stat;
    }

private:
    HashFunc<Key>& hashFunc;
    BST bst;

public:
    OptimalBSTCache(Data& data, HashFunc<Key>& hashFunc)
    : hashFunc(hashFunc), bst(data, hashFunc) { }

    std::pair<bool, const Value*> get(const Key& key) override {
        return bst.find(hashFunc.hash(key));
    }

    Number score() const {
        return bst.score();
    }

    void print(std::ostream& out) const {
        bst.print(out);
    }
};