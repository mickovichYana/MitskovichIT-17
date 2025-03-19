#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <string>
using namespace std;

//Структура для узла дерева Хаффмана
struct Huffman {
    char ch; // Символ
    int freq; // Частота символа
    Huffman* left, * right; // Указатели на левого и правого потомка
    Huffman(char ch, int freq) {
        this->ch = ch;
        this->freq = freq;
        left = right = nullptr;
    }
};

//Очередь с приоритетом
struct compare {
    bool operator()(Huffman* l, Huffman* r) {
        return l->freq > r->freq;
    }
};

// Функция для обхода дерева Хаффмана и создания кодов
void encode(Huffman* root, string str, map<char, string>& huffmanCode) {
    if (root == nullptr)
        return;

    // Если узел - лист, то добавляю его код в map
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

// Основная функция для построения дерева Хаффмана и кодирования
void HuffmanTree(string text, map<char, int>& freq, map<char, string>& huffmanCode) {

    // Считаю сколько раз встречается каждый символ
    for (char ch : text) {
        freq[ch]++;
    }

    // Создаю приоритетную очередь для хранения узлов дерева
    priority_queue<Huffman*, vector<Huffman*>, compare> pq;

    // Создаю узлы для каждого символа и добавляю их в очередь
    for (map<char, int>::iterator it = freq.begin(); it != freq.end(); ++it) {
        pq.push(new Huffman(it->first, it->second));
    }

    // Строю дерево Хаффмана
    while (pq.size() != 1) {
        Huffman* left = pq.top(); pq.pop();
        Huffman* right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        Huffman* node = new Huffman('\0', sum);
        node->left = left;
        node->right = right;
        pq.push(node);
    }

    // Получаю корень дерева
    Huffman* root = pq.top();

    // Строю коды Хаффмана
    encode(root, "", huffmanCode);
}

int main() {
    string text = "ГОСТИНАЯ АННЫ ПАВЛОВНЫ НАЧАЛА ПОНЕМНОГУ "
        "НАПОЛНЯТЬСЯ ПРИЕХАЛА ВЫСШАЯ ЗНАТЬ "
        "ПЕТЕРБУРГА ЛЮДИ САМЫЕ РАЗНОРОДНЫЕ ПО ВОЗРАСТАМ И ХАРАКТЕРАМ НО ОДИНАКОВЫЕ ПО ОБЩЕСТВУ В КАКОМ ВСЕ ЖИЛИ ПРИЕХАЛА ДОЧЬ КНЯЗЯ ВАСИЛИЯ "
        "КРАСАВИЦА ЭЛЕН ЗАЕХАВШАЯ ЗА ОТЦОМ ЧТОБЫ С НИМ ВМЕСТЕ ЕХАТЬ НА ПРАЗДНИК ПОСЛАННИКА ОНА БЫЛА В ШИФРЕ И БАЛЬНОМ ПЛАТЬЕ ПРИЕХАЛА И МОЛОДАЯ МАЛЕНЬКАЯ КНЯГИНЯ " 
        "БОЛКОНСКАЯ ПРОШЛУЮ ЗИМУ ВЫШЕДШАЯ ЗАМУЖ И ТЕПЕРЬ НЕ ВЫЕЗЖАВШАЯ В БОЛЬШОЙ СВЕТ ПО ПРИЧИНЕ СВОЕЙ БЕРЕМЕННОСТИ НО ЕЗДИВШАЯ ЕЩЕ НА НЕБОЛЬШИЕ ВЕЧЕРА ПРИЕХАЛ "
        "КНЯЗЬ ИППОЛИТ СЫН КНЯЗЯ ВАСИЛИЯ С МОРТЕМАРОМ КОТОРОГО ОН ПРЕДСТАВИЛ ПРИЕХАЛ И АББАТ МОРИО И МНОГИЕ ДРУГИЕ";
    map<char, int> freq;
    map<char, string> huffmanCode;
    HuffmanTree(text, freq, huffmanCode);
    cout << "Количество:\n";
    for (map<char, int>::iterator it = freq.begin(); it != freq.end(); ++it) {
        cout << it->first << " : " << it->second << endl;
    }
    cout << "Коды Хаффмана:\n";
    for (map<char, string>::iterator it = huffmanCode.begin(); it != huffmanCode.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    return 0;
}