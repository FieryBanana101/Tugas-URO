## Projek Tugas 1: Automatic Sudoku Solver menggunakan algoritma backtracking
#### Motivasi:
Algoritma backtracking dapat digunakan pada robot search and rescue maka dari itu, dibuatlah implementasi algortima backtracking ini

#### Deskripsi:
Program ini adalah implementasi algoritma backtracking untuk menyelesaikan puzzle sudoku dengan menggunakan bahasa pemrograman c++ yang berbentuk command line interface application.


Program akan mendapat file .txt berupa input dari pengguna yang berisi puzzle sudoku.


Program kemudian akan mencari solusi dari sudoku tersebut dengan menggunakan algoritma backtracking yang akan mencoba seluruh kemungkinan angka yang mungkin pada suatu kotak. Kemudian jika tidak ada angka yang mungkin, algoritma akan mundur kembali ke langkah sebelumnya dan mencoba angka lain. Hal ini dilakukan terus hingga ditemukan solusi.


Jika sudoku tidak memiliki solusi, program akan melaporkan hal tersebut ke pengguna.


Jika terdapat solusi, program akan menampilkannya beserta dengan total waktu runtime dari program.


Dapat juga dilihat proses step by step ketika algoritma backtracking berjalan (namun tidak direkomendasikan, karena akan memakan runtime yang sangat lama).


#### Penggunaan:

Untuk Windows, download file "sudoku.exe". Sedangkan untuk Linux, download file "sudoku.elf".

Penggunaan pada shell yaitu:

```sh
./sudoku.elf file.txt
```

atau

```sh
./sudoku.exe file.txt
```

Dapat ditambah opsi verbose dengan '-v' untuk melihat step by step algoritma. 

Contoh:  

```sh
./sudoku.elf -v file.txt
```

atau

```sh
./sudoku.exe -v file.txt
```

Dengan file.txt berupa file yang berisi sudoku yang telah diformat (9 x 9 angka)

Contoh:  
```console
6 0 0 1 0 7 0 0 4  
0 0 5 0 4 0 0 0 0  
0 2 7 0 6 0 0 0 0  
0 3 0 0 0 5 0 7 0  
0 9 0 0 3 0 0 0 2  
0 0 0 2 0 0 0 3 0  
0 0 0 0 0 6 0 0 5  
0 0 0 0 5 1 0 0 6  
2 0 0 4 0 0 8 0 0  
```

Dengan '0' merepresentasikan kotak kosong pada sudoku. 


**Note:** 

file.txt tidak harus space atau newline sensitive, artinya dapat ditambahkan newline atau space tambahan dimana saja dan tidak akan ada masalah (selama terdapat minimal 9 x 9 angka).
