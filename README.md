# 🔐 Bitwise Gamma Encryptor (C++)

## 📚 Описание

Этот проект представляет собой простой, но показательный **шифровальщик текста на языке C++**, использующий **симметричное шифрование** с применением:
- побитовой операции `XOR` между текстом и числовым ключом,
- циклического сдвига битов,
- записи/чтения в бинарный файл.

Программа может как шифровать, так и расшифровывать сообщения, используя один и тот же **целочисленный пароль** (gamma key).

---

## 🧪 Как это работает

1. Текст преобразуется в последовательность байтов (`bitset<8>`).
2. К каждому байту применяется `XOR` с расширенным двоичным ключом.
3. Полученные биты проходят **циклический сдвиг вправо на 2 бита** (при шифровании) или **влево** (при расшифровке).
4. Результат сохраняется в бинарный файл или выводится в консоль.

---

## ⚙️ Сборка и запуск

### 🔧 Требования

- Поддержка компиляции C++11 (`g++`, `clang++`, MSVC)
- OS: Windows / Linux / macOS

### 🔨 Сборка

```bash
g++ -std=c++11 -o encryptor encryptor.cpp
```
## 🚀 Использование

### 🔒 Шифрование
```bash
./encryptor encryption output_file.bin
```
Затем программа запросит ввод строки и ключа:
```bash
Введите строку для шифрования: Hello, World!
Введите пароль (целое число): 123
```
### 🔓 Расшифровка
```bash
./encryptor decryption output_file.bin
```
Затем введите тот же пароль:
```bash
Введите пароль (целое число): 123
```

## 💡 Пример
```shell
$ ./encryptor encryption secret.dat
Введите строку для шифрования: Привет
Введите пароль (целое число): 42
Ваше зашифрованное сообщение: íî×÷ñò

$ ./encryptor decryption secret.dat
Введите пароль (целое число): 42
Ваше расшифрованное сообщение: Привет
```
