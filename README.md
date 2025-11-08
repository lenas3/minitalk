# minitalk

kullanılacak bazı fonksiyonlar:

  ✅ SIGNAL:
* sinyal fonksiyonu cagırıldıgında hemen bir islem yapmaz. sadece hangi sinyal geldiginde hangi fonksiyon calısacak onu belirtir.
* signal(int signum, void (*handler)(int) syntax'ıyla çalısıyor. burada signum yakalanacak sinyal, handler ise sinyal geldiginde cagrılacak fonksiyonun adresi oluyor.
* Örnegin,  CTRL + C basmak SIGINT sinyalini gönderir.  __signal(SIGINT, handler);__ cagrısı isletim sistemine SIGINT gelirse ne yapacagını söyler. Eğer sinyal gelirse handler olarak belirlenen fonksiyon calısır. __Handler bittiginde program normal akışıına geri döner.__

✅ SIGEMPTYSET:
* C dilinde kullanıcının olusturdugu, bir degisken olan sinyal setleri vardır. sinyal seti icinde programın ilgilendiği veya bloke ettiği sinyaller tutulur. set icinde hangi sinyallerin         olacagını da biz belirliyoruz. işletim sistemi bu sete bakarak hangi sinyalleri kullanabilecegini, hangilerini engelleyebilecegini ogrenir.
* SIGEMPTYSET, bu belirlenen seti temizlemek icin kullanılır. bu saeede setin içi temizlenir ve farklı fonksiyonlar kullanılarak (sigaddset gibi) yeni bir veri seti oluşturulabilir.
*   sigset_t myset;
    sigemptyset(&myset);
yukarıdaki sekilde cagırıldıgında myset icindeki tüm sinyaller silinir.

   ✅ SIGADDSET:
* Bir sinyal setine belirli bir sinyali eklemek icin kullanılır. önce sigset_t ile bir set olusturulur set, icinde rastgele verilerle dolu olarak olusur, temiz bir set olarak degil. (sigset_t myset; gibi bir tanımlama yapıldıgında ici bos bir set degildir.). Sonrasında daha saglıklı bir ekleme yapabilmek icin sıgemptyset kullanıyoruz.
* Bu adımların ardından SIGADDSET kullanmak daha saglıklıdır. ve __sigaddset(&set, SIGINT);__ benzeri bir syntax ile set icine istedigimiz sinyali ekleyebilriz.

✅ SIGACTION:
* sinyal fonksiyonuna benzer şekilde sinyalleri yakalamak ve islemek icin kullanılır. signal'in daha güvenli bir alternatifidir.
* signal fonksiyonu sinyal ilk kez geldiginde handler fonksiyonu calıstırır. sinyalin bir sonraki gelisinde tekrar calısması icin yeniden cagrılmaya ihtiyac duyabilir. sigaction ile bir sinyal icin handler gonderdiyseniz bu kalıcıdır. yeniden cagrılmaya ihityac duymadan sinyalin her gelisinde sigaction ile belirlenmis handler calısır.

* sigaction syntax'ı:
*     t sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
          signum → yakalanacak sinyal (SIGINT, SIGTERM, vb.)
          act → yeni sinyal davranışını belirten yapı (handler, maskeler vb.)
          oldact → eski davranışı kaydetmek için kullanılır, NULL verilebilir.

✅ KILL:
* bir process ID'ye veya process grubuna __sinyal göndermeye__ yarar. (PID, işletim sisteminin her çalışan program icin otomatik atadıgı benzersiz bir tam sayıdır.).
* adı bir programı sonlandırmayı anımsatıyo ama mutlaka bir süreci bitirmek icin kllanılmaz ve her tür sinyal gönderilebilir.
* sytnax'ı:
*     int kill(pid_t pid, int sig);
      pid → sinyalin gönderileceği süreç ID’si (PID)
      sig → gönderilecek sinyal (SIGKILL, SIGTERM, SIGUSR1, vb.)
      Başarılı olursa 0, hata olursa -1 döner.
* kill(pid, SIGKILL); kullanımı pid degeri gonderilen process'i zorla öldürür.

✅ GETPID:
* anlık olarak çalışan programın PID'sini döndüren bir sistem çağrısıdır.
* __pid_t getpid(void);__ --> _pid_t, process id'yi temsil eden bir integer türüdür._
* pid_t pid = getpid(); denildigi zaman, program kendi PID'sini alır.

* kill ve getpid kullanımı iceren bir örnek:
*     int main() {
        signal(SIGUSR1, handler);      // handler tanımla
        kill(getpid(), SIGUSR1);       // kendi process'ine gönder
        return 0;
      }

* SIGUSR1, kullanıcı tarafından tanımlanacak ve istedigi amacla kullanabilecegi bir sinyaldir. genellikle bir process'e bildirim göndermek veya tetikleme icin kullanıılır.
* Buradaki örnekte "signal" fonksiyonu ile SIGUSR1 sinyali icin bir handler tanımlıyoruz. sonrasında  "getpid" ile programımızın pid'sini alıp, bu pid'yi kullanarak "kill" ile kendi processimize sinyal yolluyoruz. 

✅ PAUSE:
* programı bir sinyal alınana kadar duraklatır.
* Çağrıldıgınfa progrma pause noktasına geldiginde uyku moduna gecer. sinyal geldiginde sinyalin bir handler'ı varsa o çalıştırılır. __handler tamamlandıgında pause() cagrısı -1 doner.__

✅ SLEEP:
* pause'a benzer çalışır ama buradaki fark, sleep fonksiyonunun programı parametre olarak aldıgı saniye süresince uyutmasıdır. __hem pause hem de sleep bekleme süresince CPU harcamaz.__
* !!sleep fonksiyonunda, bekletme süresi bitince program kaldıgı yerden devam eder. eğer bekleme süresince bir sinyal gonderirlirse sleep erken biter ve __sleep'in dönus degeri kalan süre olur.__ Eğer herhangi bir bölünme olmadan __süre tamamen dolarsa, sleep 0 döner.__

    ✅ USLEEP:
* sleep fonksiyonunun __mikrosaniye__ cinsinde duraklatan hali denebilir.
* __Eğer usleep süresince bir kesilme olursa program -1 döner.__

    ➡️ _Neden sleep varken bu kadar kücük uyutmalara ihtiyacimiz olsun?_

CPU'yu yormamak veya hassas zamanlamalar icin kullanabiliyoruz. 

Bir program sürekli bir şey kontrol ediyor diyelim. Bu durumda CPU durmadan döngüde kalır,  arada hiç nefes almaz. CPU %100’e yakın kullanılır, fan döner, pil biter, verimsizdir.
usleep kullanılırsa program hâlâ “sürekli kontrol ediyor” gibi görünür — çünkü 1 ms çok kısa bir süredir. Ama bu arada CPU o 1 ms boyunca tamamen boş kalır. İşletim sistemi o çekirdeği başka işler için kullanabilir. Ama aynı zamanda rogramın tepki süresi hâlâ insan gözünün fark edemeyeceği kadar hızlıdır.

CPU haricinde de oyun ve animasyonlarda ya da hassas çalısan sistemlerde çok kücük sürelerde uyutmalara ihityac duyulur.
