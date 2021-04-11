#pragma once
// Заголовочный файл с объявлением структуры данных

#include <mmcobj.h>

namespace itis {

    // Tip 1: объявите здесь необходимые структуры, функции, константы и прочее

    // Пример: объявление константы времени компиляции в заголовочном файле
    inline constexpr auto kStringConstant = "Hello, stranger!";

    // Пример: объявление структуры с полями и методами
    enum nodeColor {
        BLACK, RED
    };


    struct Node {
    public:
        Node *left;
        Node *right;
        Node *parent;
        nodeColor color;
        int data;
    };

    Node sentinel = {nullptr, nullptr, 0, BLACK, 0};
    Node *root = &sentinel;

    // Tip 2: На начальном этапе разработки структуры данных можете определения методов задавать в
    // заголовочном файле, как только работа будет завершена, можно будет оставить здесь только объявления.

    Node *insertNode(int data) {
        Node *current;
        Node *parent;
        Node *newNode = nullptr;
        current = root;
        parent = 0;
        while (current != nullptr) {
            if (data == current->data) {
                return current;
            }
            parent = current;
            if (data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        newNode->data = data;
        newNode ->parent = parent;
        newNode->left = nullptr;
        newNode-> right = nullptr;
        newNode ->color = RED;
        if(parent){
            if(data < current->data){
                parent->left = newNode;
            }else{
                parent->right = newNode;
            }
        }else{
            root = newNode;
        }
        insertFix(newNode);
        return (newNode);
    };

}  // namespace itis
