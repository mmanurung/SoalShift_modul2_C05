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
	Bertujuan untuk mengarahkan pointer ke direktori yang ditentukan, lalu isi folder tersebut dibaca. Simpan folder asal dan folder 	tujuan ke array masing-masing, lalu ambil nama file nya dan simpan ke array x. Kemudian tentukan apakah file tersebut berekstensi 	 png atau tidak. Jika ya, maka nama file di tambahkan dengan _grey.png dan di simpan di direktori tujuan.</br></br>

2. Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
</br>Catatan: Tidak boleh menggunakan crontab</br>
Penjelasan:</br>
Buat folder hatiku yang berisi file elen.ku
	```bash
	stat(elen, &sb); //stat system call
	struct passwd *pw = getpwuid(sb.st_uid);
	struct group  *gr = getgrgid(sb.st_gid);
	chmod(elen, S_IRWXU | S_IRWXG | S_IRWXO); //read, write, execute/search by owner or group or other
	if(strcmp(pw->pw_name, "www-data")==0 && (gr->gr_name, "www-data")==0){
		perintah = remove(elen);
	sleep(3);
	```
	
	Diawali dengan mendeteksi owner dan group menggunakan `stat`. Lalu gunakan chmod untuk mengubah permission agar owner, group, other dapat read, write, dan execute. Lalu cek apakah owner dan group merupakan "www-data", jika ya, maka jalankan perintah untuk menghapus elen setiap 3 detik.

3. Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. Buatlah program C yang dapat :
</br>i)  mengekstrak file zip tersebut.
</br>ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
</br>Catatan:  
      - Gunakan fork dan exec.
      - Gunakan minimal 3 proses yang diakhiri dengan exec.
      - Gunakan pipe
      - Pastikan file daftar.txt dapat diakses dari text editor</br></br>
 <h2>Jawaban</h2>
 <h5>Source Code</h5>
 
 ```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int main(){
    chdir("home/bella/modul2");
    int st_parent1, rw_pipe1[2], rw_pipe2[2];
    char tmp[100001];
    char *unzip_argv[]={"unzip","campur2.zip",NULL};
    char *ls_argv[]={"ls","campur2",NULL};
    char *grep_argv[]={"grep",".txt$",NULL};

    if(!fork()){
        struct stat st = {0};
        if(stat("campur2",&st)!=0)
                execv("/usr/bin/unzip",unzip_argv);
        exit(1);
    }
    else {
        while(!wait(&st_parent1));
        pipe(rw_pipe1); pipe(rw_pipe2);
        if(!fork()){
            close(rw_pipe2[0]); close(rw_pipe2[1]); close(rw_pipe1[0]);
            dup2(rw_pipe1[1],STDOUT_FILENO);
            close(rw_pipe1[1]);
            execv("/bin/ls",ls_argv);
         }
         else {
            wait(NULL);
            if(!fork()){
                close(rw_pipe2[0]);
                dup2(rw_pipe2[1],STDOUT_FILENO);
                close(rw_pipe2[1]); close(rw_pipe1[1]);
                dup2(rw_pipe1[0],STDIN_FILENO);
                close(rw_pipe1[0]);
                execv("/bin/grep",grep_argv);
            }
            else {
                close(rw_pipe2[1]); close(rw_pipe1[0]); close(rw_pipe1[1]);
                int byte = read(rw_pipe2[0],tmp,sizeof(tmp));
                freopen("data.txt","w+",stdout);
                printf("%s\n",tmp);
                fclose(stdout);
		 close(rw_pipe2[0]);
            }
        }
    }
}
```

 <h5>Penjelasan</h5>
 <p>
	Seperti yang tertera pada soal, kita diharuskan untuk melakukan unzip untuk file campur2.zip dan menyimpan daftar file yang memiliki ekstensi .txt ke dalam sebuah file daftar.txt. Secara umum, apabila ingin melakukan kegiatan yang telah dideskripsikan diatas, kita dapat melakukannya melalui terminal dengan command unzip campur2.zip | ls campur2 | grep .txt$ . Pada command ditambahkan pipe ( | ) yang memiliki fungsi untuk melanjutkan beberapa command yang lain setelah command sebelumnya dijalankan. Sehingga dapat diartikan bahwa hasil/output dari command sebelumnya akan menjadi input dari proses selanjutnya.<br>

Untuk menyelesaikan soal diatas, kami menggunakan beberapa metode atau cara, yaitu :<br>
a) Melakukan fork,exec, dan wait<br>
Fork digunakan untuk membuat child process yang berfungsi menjalankan command yang dibuat secara bersama-sama dalam satu program. Dalam penyelesaiannya, kami menggunakan dua kali fork. Fork pertama digunakan untuk membuat child process yang akan menjalankan command unzip. Sedangkan fork yang kedua digunakan untuk membuat child process yang menjalankan command ls. Parent process dari fork pertama digunakan untuk pembuatan fork kedua, sedangkan parent process dari fork kedua digunakan untuk menjalankan command grep.<br>

Exec digunakan untuk menjalankan suatu command yang telah terdefinisikan dan dikenali pada terminal. Untuk menyelesaikan soal ini, kami menggunakan tiga exec, yaitu exec untuk command unzip, exec untuk command ls, dan exec untuk command grep. Berikut adalah sintaks yang digunakan pada program :<br>
	<pre>
	char *unzip_argv[]={"unzip","campur2.zip",NULL};
    	char *ls_argv[]={"ls","campur2",NULL};
    	char *grep_argv[]={"grep",".txt$",NULL};
	execv("/usr/bin/unzip",unzip_argv);
	execv("/bin/ls",ls_argv);
	execv("/bin/grep",grep_argv);
	</pre>

Wait digunakan untuk menunggu suatu proses dengan parameternya berupa suatu kondisi. Parameter kondisinya dapat berupa address dari suatu pid ataupun NULL. Untuk penyelesaian soal ini, kami menggunakan dua wait dengan parameter berupa address dari child process dan NULL. Parameter address disini bertujuan untuk menunggu child process hingga selesai menjalankan tugasnya, sehingga proses selanjutnya dapat dijalankan. <br>

b) Melakukan pipe() dan dup()<br>
Pipe disini digunakan untuk melakukan read and write saat menjalankan exec. Pipe disini memiliki dua parameter, yaitu parameter dengan index 0 (misal rw_pipe1[0]) yang digunakan untuk membaca dan  parameter dengan index 1 (misal rw_pipe[1]) yang digunakan untuk menulis. Selain itu, digunakan dup() atau duplikat yang memiliki dua paramter yaitu parameter dari read and write pipe dan file descriptor. Ketika read, maka file descriptor yang digunakan adalah STDOUT_FILENO. Sedangkan ketika write, maka file descriptor yang digunakan adalah STDIN_FILENO.<br>

c) Menggunakan freopen<br>
Freopen yang digunakan untuk menulis hasil dari grep dan disimpan dalam file daftar.txt
</p>

4. Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik). Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.
</br>Contoh:
</br>File makan_enak.txt terakhir dibuka pada detik ke-1
</br>Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt</br>
</br>Catatan: 
      - dilarang menggunakan crontab
      - Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst</br></br>
 <h2>Jawaban</h2>
 <h5>Source Code</h5>
 
 ```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(){
        pid_t pid, sid;
        pid=fork();

        if(pid<0)
                exit(EXIT_FAILURE);
        if(pid>0)
                exit(EXIT_SUCCESS);

        umask(0);

        sid=setsid();
        if(sid<0)
                exit(EXIT_FAILURE);
        if((chdir("/")) < 0)
                exit(EXIT_FAILURE);

        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        while(1){
                chdir("home/bella/Documents/makanan");
                struct stat status={0}, status_file={0};
                time_t waktu; time(&waktu); ctime(&waktu);
                int num=1;
                FILE *find_file;
                if(stat("makanan_enak.txt",&status)<0){
                        printf("Failed\n");
                        exit(1);
                }
                double diff = difftime(waktu,status.st_atime);
                char *filename="home/bella/Documents/makanan";
                strcat(filename,"makan_sehat");
                while(30.00 >= diff && diff>=0){
                        sprintf(filename,"makan_sehat%d.txt",num);
                        if(stat(filename,&status_file)<0){
                                find_file=fopen(filename,"w+");
				fclose(find_file); break;
                        }
                        num++;
                        strcpy(filename,"home/bella/Documents/makanan/makan_sehat");
                }
                sleep(5);
        }
}
```

<h5>Penjelasan</h5>
<p>
Seperti yang tertera pada soal nomor 4, kita diminta untuk membuat file makan_sehat#.txt yang akan dibuat ketika file makan_enak.txt pernah dibuka. Syarat yang lain, yaitu file makan_sehat#.txt akan dibuat ketika file makan_sehat.txt pernah dibuka dalam rentang (0-30 detik). Program berjalan  dengan kurun lima waktu sekali. Untuk menyelesaikan persoalan ini, kami menggunakan program yang akan membuat file makan_sehat#.txt secara berurutan yang berarti bahwa apabila ada file  makan_sehat*.txt dihapus, maka file yang akan dibuat akan memiliki nama makan_sehat*.txt 
</p>
 
5. Kerjakan poin a dan b di bawah:
- Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
</br>Ket:
  - Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
  - Per menit memasukkan log#.log ke dalam folder tersebut
    </br>‘#’ : increment per menit. Mulai dari 1
- Buatlah program c untuk menghentikan program di atas.
</br>NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.
<h2>Jawaban</h2>
<h5>Source Code</h5>
a)<br>

 ```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(){
        int i=1;
        pid_t pid, sid;
        pid=fork();

        if(pid<0)
                exit(EXIT_FAILURE);
        if(pid>0)
                exit(EXIT_SUCCESS);

        umask(0);
        sid=setsid();

        if(sid<0)
                exit(EXIT_FAILURE);
        if((chdir("/"))<0)
                exit(EXIT_FAILURE);

        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        while(1){
                int num=1; char buffer[50],foldername[101];
                time_t waktu = time(NULL);
                if(!((num-1)%30)){
                        memset(buffer,0,sizeof(buffer));
                        strftime(buffer,50,"%d:%m:%Y-%H-%M", localtime(&waktu));
                        sprintf(foldername,"/home/bella/log");
                        strcat(foldername,buffer);
                        mkdir(foldername,0777);
                        num=1;
                }
                strftime(buffer,50,"%d:%m:%Y-%H-%M",localtime(&waktu));
                char filename[101],filename_ext[101];
                sprintf(filename,"/home/bella/log/");
                strcat(filename,buffer);
                snprintf(filename_ext,sizeof(filename_ext),"log%d.log",num);
		               strcat(filename,filename_ext);
                if(!fork()){
                        char *cp_argv[]={"cp","/var/log/syslog",filename,NULL};
                        execv("/bin/cp",cp_argv);
                }
                num++;
                sleep(60);
        }
        exit(EXIT_SUCCESS);
}
```
<br>b)

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <time.h>
#include <signal.h>

int main() {
        char *kill_argv[]={"pkill", "soal5", NULL};
        execv("/usr/bin/pkill",kill_argv);
}
```

<h5>Penjelasan</h5>
<p>
Pada soal nomor 5, kita diminta untuk membuat folder dan file log#i.log yang merupakan salinan dari var/log/syslog/ dan disimpan dalam folder bernama log/[waktu yang telah sesuai peraturan]. Untuk menyelesaikan soal ini, kami menggunakan beberapa langkah yaitu :<br>
a) Menggunakan localtime(&waktu)<br>
    Digunakan untuk menyimpan waktu komputer dan sesuai persyaratan pada soal modul2<br>
b) Melakukan setting nama folder dan nama file<br>
    Setting nama folder dan nama file yang sesuai dengan persyaratan pada soal nomor 5 dengan menggunakan strftime (digunakan untuk memberikan nama suatu array of char dengan waktu) dan menggabungkan nama folder dan nama file dengan sprintf, strcat, dan snprintf.<br>
c)Menggunakan exec<br>
   Exec digunakan untuk menjalankan command cp. Berikut adalah sintaksnya :
	
	<pre>
   	char *cp_argv[]={"cp","/var/log/syslog",filename,NULL};
  	execv("/bin/cp",cp_argv);
	</pre>
	
d)Menggunakan pkill<br>
pkill digunakan untuk membunuh proses, untuk melakukan kill pada program soal 5a, kami menggunakan exec
</p>





