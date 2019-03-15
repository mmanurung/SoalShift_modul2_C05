# SoalShift_modul2_C05

Kelompok C05:
- Bella Septina Ika Hartanti (05111740000117)
- Miranda Manurung (05111740000144)

## Soal

1. Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
</br>Catatan : Tidak boleh menggunakan crontab.</br>
Penjelasan:</br>
Buat folder untuk menyimpan file .png (gunakan mkdir dan touch)</br>
Penjelasan program</br>

	```bash
	DIR *dr = opendir("/home/nanda/nama");
	if (dr != NULL)
	while ((de = readdir(dr)) != NULL)
		strcpy(dir_sumber, "/home/nanda/nama/");
		strcpy(dir_tujuan, "/home/nanda/modul2/gambar/");
		strcpy(file_sumber, de->d_name);
		ptr = strrchr(file_sumber, '.');
		strcpy(x, file_sumber);
		if (ptr && (strcmp(ptr, ".png") == 0)){
			*ptr = 0;
			strcpy(y, file_sumber);
            		strcat(y, tambahan);
			strcat(dir_sumber, x);
	      		strcat(dir_tujuan, y);
	      rename(dir_sumber, dir_tujuan
	```   
Bertujuan untuk mengarahkan pointer ke direktori yang ditentukan, lalu isi folder tersebut dibaca. Simpan folder asal dan folder tujuan ke array masing-masing, lalu ambil nama file nya dan simpan ke array x. Kemudian tentukan apakah file tersebut berekstensi png atau tidak. Jika ya, maka nama file di tambahkan dengan _grey.png dan di simpan di direktori tujuan.</br></br>

2. Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
</br>Catatan: Tidak boleh menggunakan crontab</br>
Penjelasan:</br>
Buat folder hatiku yang berisi file elen.ku
Penjelasan program</br>

	```bash
	stat(elen, &sb); //stat system call
	struct passwd *pw = getpwuid(sb.st_uid);
	struct group  *gr = getgrgid(sb.st_gid);
	chmod(elen, S_IRWXU | S_IRWXG | S_IRWXO); //read, write, execute/search by owner or group or other
	if(strcmp(pw->pw_name, "www-data")==0 && (gr->gr_name, "www-data")==0)
		perintah = remove(elen);
	sleep(3);
	```
Diawali dengan program untuk mendeteksi owner dan group menggunakan `stat`. Lalu jangan lupa untuk mengubah permission pada elen dengan membuat baik owner, group, maupun other bisa read, write dan execute menggunakan `chmod`. Setelah itu compare apakah owner dan group nya ialah "www-data". Jika ya, maka lakukan perintah untuk remove file elen.ku setiap 3 detik.</br></br>
3. Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. Buatlah program C yang dapat :
</br>i)  mengekstrak file zip tersebut.
</br>ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
</br>Catatan:  
      - Gunakan fork dan exec.
      - Gunakan minimal 3 proses yang diakhiri dengan exec.
      - Gunakan pipe
      - Pastikan file daftar.txt dapat diakses dari text editor</br></br>
4. Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik). Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.
</br>Contoh:
</br>File makan_enak.txt terakhir dibuka pada detik ke-1
</br>Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt</br>
</br>Catatan: 
      - dilarang menggunakan crontab
      - Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst</br></br>
5. Kerjakan poin a dan b di bawah:
- Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
</br>Ket:
  - Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
  - Per menit memasukkan log#.log ke dalam folder tersebut
    </br>‘#’ : increment per menit. Mulai dari 1
- Buatlah program c untuk menghentikan program di atas.
</br>NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

