Для компиляции клиента и сервера необходимо установить OpenSSL:
https://slproweb.com/products/Win32OpenSSL.html
Зайти в Visual Studio и зайти в настройки проекта->компоновщик->общие->дополнительные
каталоги библиотек и добавить туда следющее:
OpenSSL\include
OpenSSL\bin\VC
Здесь OpenSSL --- папка, куда был установлен OpenSSL.
Также необходимо добавить OpenSSL\include в дополнительные каталоги включаемых
библиотек.
В настройках компоновщика зайти в Ввод->Дополнительные зависимости и добавить
библиотеки libcrypto64MD.lib;libssl64MD.lib. Если Вы установили 64x версию, то
ее нужно также указать при компиляции.