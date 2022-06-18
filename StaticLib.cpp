#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>    
#include <string>
#include <thread>
#include <chrono>

bool stop = false;

std::wstring GetNameFile()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "===============FILE SEARCH===============";
    std::cout << "\nExample : \nEnter the name of file : some_file.exe \nEnter the name of Folder : Windows";
    std::cout << "\n\nEnter the name of file(folder) : "; // Вводиться назва файлу(з розширинням) або папки 
    std::wstring name;
    std::getline(std::wcin, name);

    return name;


}

void Function_File_Find(const std::wstring& directory, std::wstring name)
{

    std::wstring tmp = directory + L"\\*";
    WIN32_FIND_DATAW file;
    HANDLE search_handle = FindFirstFileW(tmp.c_str(), &file);
    if (search_handle != INVALID_HANDLE_VALUE)
    {
        if (stop == false)
        {
            std::vector<std::wstring> directories;

            do
            {
                if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // перевірка файлу чи не є він папкою 
                {
                    if ((!lstrcmpW(file.cFileName, L".")) || (!lstrcmpW(file.cFileName, L"..")))
                        continue;
                }
                tmp = directory + L"\\" + std::wstring(file.cFileName);
                // std::wcout << tmp << std::endl;
                if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    directories.push_back(tmp);
                }
                if (file.cFileName == name)
                {
                    std::wcout << "\nNAME  :   " << name << "\nDir   :   " << tmp << "\n";
                    stop = true;
                    break;
                }

            } while (FindNextFileW(search_handle, &file));

           // FindClose(search_handle);


            for (std::vector<std::wstring>::iterator i = directories.begin(), end = directories.end(); i != end; i++)// рекурсія при якій відбувається перевірка на кінець дерикторії
                Function_File_Find(*i, name);
        }

    }
}

void StartThread(std::wstring name)
{
    //створюю масив потоків 
    std::wstring folders[] = { L"C:" ,L"C:\\Microsoft" ,L"C:\\Windows" ,L"C:\\Program Files",L"C:\\Program Files (x86)", L"C:\\Users" };
    std::thread myThreads[5];
    for (int i = 0; i < 5; i++)
    {
        myThreads[i] = std::thread(Function_File_Find, folders[i], name);
        // myThreads[i].join();
    }
    for (int i = 0; i < 5; i++)
    {

        myThreads[i].join();
    }

    std::cin.get();
}
