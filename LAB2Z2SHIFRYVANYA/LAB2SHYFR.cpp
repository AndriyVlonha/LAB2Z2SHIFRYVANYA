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

    cout << "������ 8 ����� ������ (�� 8 ������� �����):\n";
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

            // ����� ����� � ������� �������
            int rowNum = i & 0x07;      // 3 ��� ��� ������
            int posNum = j & 0x07;      // 3 ��� ��� ������� 

            // ���������� �� ��� � ����� 6 �������
            encryptedChar |= rowNum;        // 0-2 ��� ��� ������ �����
            encryptedChar |= (posNum << 3); // 3-5 ��� ��� ������� �������

            // ��� ������� ��� ������ ���� ���� (����� � �������)
            int parity1 = parityBit(encryptedChar, 6);
            encryptedChar |= (parity1 << 6); // 6 �� - �� ������� ������ ����

            // ASCII-��� �������
            int asciiCode = static_cast<int>(lines[i][j]);
            encryptedChar |= (asciiCode << 7); // 7-14 ��� - ASCII-���

            // ��� ������� ��� ASCII-����
            int parity2 = parityBit(asciiCode, 8);
            encryptedChar |= (parity2 << 15); // 15 �� - �� ������� ASCII

            // �������� � ����
            outFile.write(reinterpret_cast<const char*>(&encryptedChar), sizeof(encryptedChar));
        }
    }

    outFile.close();
    cout << "���������� ���������, ��������� �������� � ���� encrypted.bin." << endl;

    return 0;
}
