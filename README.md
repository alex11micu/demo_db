montare:
CMD cu drepturi de admin

0. cd C:\
1. git clone https://github.com/microsoft/vcpkg
2. cd vcpkg
3. bootstrap-vcpkg.bat
4. vcpkg install nanodbc:x64-windows
5. vcpkg integrate install
6. In proiectul din VS, Project->Properties->Configuration Properties->VC++ Directories-> Include Directories se adauga "C:\vcpkg\installed\x64-windows\include\nanodbc" sau calea catre nanodbc.h.

Deschideti SSMS sau orice SGBT si creati baza de date POO. (connection string-ul se afla in main.cpp)

Tabela din DB poate fi creata astfel:
CREATE TABLE users (
    id INT IDENTITY(1,1) PRIMARY KEY,
    username NVARCHAR(255) NOT NULL,
    email NVARCHAR(255) NOT NULL UNIQUE
);
