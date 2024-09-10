#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <vector>
#include <cmath>
#include <iosfwd>

std::string dec_to_bin(int a) {
    std::string bin;
    while (a > 0) {
        bin = std::to_string(a % 2) + bin;
        a /= 2;
    }
    return bin;
}
std::bitset<8> shift_2_byte_right_block(std::string block,int step) {
    int byte = 8;
    auto part1 = std::bitset<8>(block) >> step;
    auto part2 = std::bitset<8>(block) << byte - step;
    return part1 | part2;
}
std::bitset<8> shift_2_byte_left_block(std::string block, int step) {
    int byte = 8;
    auto part1 = std::bitset<8>(block) << step;
    auto part2 = std::bitset<8>(block) >> byte - step;
    return part1 | part2;
}

int main(int argc, const char* argv[])
{   
    setlocale(LC_ALL, "Russian");
    if (argc != 3) {
        std::cerr << "Ошибка: используйте три параметра\n";
        system("pause");
        return 1;
    }

    const std::string mode(argv[1]);
    const std::string file_name(argv[2]);
    if (mode == "encryption") {
        std::ofstream target_file(file_name,std::ios::out|std::ios::binary);
        std::string target_string;
        int gamma_Key;
        std::vector<std::bitset<8>> bin_letter;
        std::cout << "Введите строку для шифрования: ";
        std::getline(std::cin, target_string);
        for (size_t i = 0; i < target_string.length(); ++i) {
            std::bitset<8> bs4(target_string[i]);
            bin_letter.push_back(bs4);
        }
        std::cout << "Введите пароль (целое число): ";
        std::cin >> gamma_Key;
        std::string bin_key = dec_to_bin(gamma_Key);
        for (size_t i = 0; i < bin_letter.size();++i) {
            while (bin_key.length() != bin_letter[i].size()) {
                bin_key += '0';
            }
        }
        std::vector<std::string> xorvec;
        for (size_t i = 0; i < bin_letter.size();++i) {
            std::string xorstring;
            for (size_t j = bin_key.length()-1; j !=-1;--j) {
                int c = ((bin_letter[i][j]) ^ (bin_key[fabs(bin_key.length()-1-j)]));
                xorstring += char(c);
            }
            xorvec.push_back(xorstring);
        }
        std::vector<std::bitset<8>> shifted_vec;
        for (size_t i = 0; i < xorvec.size();++i) {
            shifted_vec.push_back(shift_2_byte_right_block(xorvec[i], 2));
        }
        std::vector<unsigned char> encrypted;
        for (size_t i = 0; i < shifted_vec.size();++i) {
            encrypted.push_back(char(shifted_vec[i].to_ulong()));            
        }
        std::cout << "Ваше зашифрованное сообщение: ";
        for (size_t i = 0; i < encrypted.size();++i) {
            std::cout << encrypted[i];
        }
        std::copy(encrypted.cbegin(), encrypted.cend(),
            std::ostream_iterator<char>(target_file));
        target_file.close();
    }
    else if (mode == "decryption") {
        std::ifstream encrypted_file(file_name);
        std::vector<char> encrypted_vector;
        char c;
        while (encrypted_file >> c) {
            encrypted_vector.push_back(c);
        }
        int gamma_key;
        std::cout << "Введите пароль (целое число): ";
        std::cin >> gamma_key;
        std::string bin_key = dec_to_bin(gamma_key);
        std::vector<std::bitset<8>> bin_letter;
        for (size_t i = 0; i < encrypted_vector.size(); ++i) {
            std::bitset<8> bs4(encrypted_vector[i]);
            bin_letter.push_back(bs4);
        }
        for (size_t i = 0; i < bin_letter.size();++i) {
            while (bin_key.length() != bin_letter[i].size()) {
                bin_key += '0';
            }
        }
        std::vector<std::bitset<8>> shifted_vector;
        for (size_t i = 0; i < bin_letter.size();++i) {
            shifted_vector.push_back(shift_2_byte_left_block(bin_letter[i].to_string(), 2));
        }
        std::vector<std::string> xorvec;
        for (size_t i = 0; i < shifted_vector.size();++i) {
            std::string xorstring;
            for (size_t j = bin_key.length() - 1; j != -1;--j) {
                int c = ((shifted_vector[i][j]) ^ (bin_key[fabs(bin_key.length() - 1 - j)]));
                xorstring += char(c);
            }
            xorvec.push_back(xorstring);
        }
        std::vector<unsigned char> decrypted;
        for (size_t i = 0; i < xorvec.size();++i) {
            decrypted.push_back(char(std::stoi(xorvec[i],0,2)));
        }
        std::cout << "Ваше расшифрованное сообщение: ";
        for (size_t i = 0; i < decrypted.size();++i) {
            std::cout << decrypted[i];
        }
        encrypted_file.close();
    }
    return 0;
}
