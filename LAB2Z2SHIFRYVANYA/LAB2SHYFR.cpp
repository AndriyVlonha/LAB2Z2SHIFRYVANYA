#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <windows.h>

using namespace std;
int parityBit(int value, int bits) {
    int count = 0;
    for (int i = 0; i < bits; ++i) {
        if (value & (1 << i)) {
            ++count;
        }
    }
    return count % 2;
}

int main() {
    SetConsoleOutputCP(1251); 
    string lines[8];

    cout << "Введіть 8 рядків тексту (до 8 символів кожен):\n";
    for (int i = 0; i < 8; ++i) {
        getline(cin, lines[i]);
        if (lines[i].size() < 8) {
            lines[i].append(8 - lines[i].size(), ' ');  
        }
    }

    ofstream outFile("encrypted.bin", ios::binary);

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            unsigned short encryptedChar = 0;  

            // Номер рядка і позиція символу
            int rowNum = i & 0x07;      // 3 біта для номера
            int posNum = j & 0x07;      // 3 біти для позиції 

            // Вставляємо ці біти в перші 6 позицій
            encryptedChar |= rowNum;        // 0-2 біти для номера рядка
            encryptedChar |= (posNum << 3); // 3-5 біти для позиції символу

            // Біт парності для перших двох полів (рядок і позиція)
            int parity1 = parityBit(encryptedChar, 6);
            encryptedChar |= (parity1 << 6); // 6 біт - біт парності перших полів

            // ASCII-код символу
            int asciiCode = static_cast<int>(lines[i][j]);
            encryptedChar |= (asciiCode << 7); // 7-14 біти - ASCII-код

            // Біт парності для ASCII-коду
            int parity2 = parityBit(asciiCode, 8);
            encryptedChar |= (parity2 << 15); // 15 біт - біт парності ASCII

            // Записуємо у файл
            outFile.write(reinterpret_cast<const char*>(&encryptedChar), sizeof(encryptedChar));
        }
    }

    outFile.close();
    cout << "Шифрування завершено, результат записано у файл encrypted.bin." << endl;

    return 0;
}
