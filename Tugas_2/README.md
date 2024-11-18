## Projek Tugas 2: Demonstrasi OpenCV

### Disclaimer: 

Program, dan semua elemen lain projek ini dibuat 100% tanpa bantuan AI.

### Deskripsi:
Program ini adalah demonstrasi dari penggunaan berbagai teknik computer vision menggunakan library OpenCV

Program dibuat dengan bahasa pemrograman C++ dengan OS Ubuntu 24.10.

Teknik yang dilakukan pada program diantaranya yaitu frame masking dan finding countours.

Demonstrasi dan presentasi penggunaan program ini dapat dilihat pada video berikut:
[opencv_demo.mp4](https://drive.google.com/file/d/1JjDHQUFiaLVQxvhGCBqxuqOIkai0qb5Y/view?usp=sharing)

### Penggunaan:

Pertama, pastikan instalasi opencv telah dilakukan (minimal versi 3.0), panduan instalasi: https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html

Kemudian , compile source .cpp file menggunakan g++:

```bash
g++ opencv_demo.cpp -o demo $(pkg-config opencv4 --cflags --libs)
```

Penggunaan executable:

Jalankan tanpa argumen untuk melakukan demo pada "shape.mp4".
```bash
./demo
```

Dapat digunakan argumen berupa path file video yang lebih spesifik.
```bash
./demo shape.mp4
./demo object.mp4
```

Dapat digunakan flag "--mask" pada argumen kedua untuk melihat mask setiap frame.
```bash
./demo shape.mp4 --mask
./demo object.mp4 --mask
```


