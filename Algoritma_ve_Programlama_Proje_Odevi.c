#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <windows.h>
#define LEN 10000

const char matrix_bigram_strings[10][3] ={"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};

const char matrix_trigram_strings[10][4]={"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};

const char languages[2][8]={"english", "german"};

//İngilizce dilinin frekans değerleri
 const float frequency_eng[20]={ 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };
 //Almanca dilinin frekans değerleri
 const float frequency_germ[20]={ 0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62 };


float calculated_frequencies[20];
float distances [2]={0,0};
float eng_distance;
float germ_distance;


void filter_str(char str[]);
void calculate_frequencies_bi(char str[]);
void calculate_frequencies_tri(char str[]);
void calculate_distances();
void detect_lang();

int main()
{

    char str[LEN]={};

    system("color B0");//renk katmak için :)

    printf("printf(\"\tYAPIMCILAR\t\t\");\nprintf(\"\tAhmet Talha TURKMEN\t\"); \nprintf(\"\tOnur YAZKILI\t\t\"); \nprintf(\"\tAysenur ERKIN\t\t\"); \n***************************************************************************\n");

    printf("metni giriniz:\n"
           "(Lutfen girilen metni tek satirda yaziniz)\n");

    gets(str);

    printf("\n***************************************************************************\n");

    filter_str(str);

    printf("Girilen metnin temizlenmis ve kucultulmus hali:\n");

    puts(str);

    printf("\n***************************************************************************\n");

    printf("Girilen metinde%4.0d tane karakter var(bosluklar dahil)\n",strlen(str)); //boslukta karakter olarak algilaniyor

    calculate_frequencies_bi(str);

    printf("\n***************************************************************************\n");

    calculate_frequencies_tri(str);

    calculate_distances();

    printf("\n***************************************************************************\n");

    detect_lang();

    printf("\n***************************************************************************\n");
	return 0;
}

/*kullanıcıdan alınan metindeki A-Z(büyük harf) arasındaki harfleri küçük harfe çeviren , a-z(küçük harf) ve boşluk karakteri(ASCII:32)
dışındaki tüm karakterleri boşluk karakteriyle değiştiren fonksiyon */

void filter_str(char str[])
{
    int i=0;
    while(str[i]!='\0'){
          for(i;i<strlen(str);i++){
                if(str[i]>'z'){ //boşluk karakterine değiştiren döngü
                    str[i]=32;
                }
                if(str[i]>'Z' && str[i]<'a'){ //boşluk karakterine değiştiren döngü
                    str[i]=32;
                }
                if(str[i]<'A'){ //boşluk karakterine değiştiren döngü
                    str[i]=32;
                }
                if(str[i]>='A' && str[i]<='Z'){ //Küçülten döngü
                    str[i]+=32;
                }
          }
    }
}

/* verilen bigramları kullanarak, kullanıcıdan alınan metindeki
frekanslarını hesaplayan fonksiyon */

void calculate_frequencies_bi(char str[LEN])
{
    float sayac[]={0,0,0,0,0,0,0,0,0,0}; //her bir bigramın kaç defa geçtiğini tutan dizi

    int i=0,k=0,uzunluk=0;

    for(int i=0;i<strlen(str);i++) //kullanıcıdan alınan metindeki toplam harf sayısını hesaplayan döngü
    {

        if(str[i]!=32 || (str[i]<='z' && str[i]>='a' ))
        {
            uzunluk++;
        }
    }
    printf("Girilen metinde%4.0d tane harf var(sadece harfler)\n",uzunluk);
    printf("\n***************************************************************************\n");

        //kullanıcıdan alınan metnin, verilmiş olan bigramlar ile karşılaştırılması
        for(k;k<strlen(str);k++){
            for(i=0;i<10;i++){
                    if(matrix_bigram_strings[i][0]==str[k]){
                        if(matrix_bigram_strings[i][1]==str[k+1]){
                            sayac[i]+=1;
                        }
                            calculated_frequencies[i]=(100*sayac[i])/uzunluk; //bigramların frekanslarının hesaplanıp bir dizide tutulması
                    }
            }
        }
    for(int m=0;m<10;m++) //elde edilen her bir bigramın sayısının ve frekanslarının ekrana yazdırılması
        printf("Metinde %c%c Bigramindan %2.0f tane var ve metinde bulunma yuzdesi:%f \n",matrix_bigram_strings[m][0],matrix_bigram_strings[m][1],sayac[m],calculated_frequencies[m]);
        //matrix_bigram_string matris oldugundan %s olarak alamadim ben de %c%c seklinde aldim
}

/* verilen trigramları kullanarak, kullanıcıdan alınan metindeki
frekanslarını hesaplayan fonksiyon */

void calculate_frequencies_tri(char str[LEN])
{
    float sayac[]={0,0,0,0,0,0,0,0,0,0}; //her bir trigramın kaç defa geçtiğini tutan dizi

    int i=0,k=0,uzunluk=0;

    for(int i=0;i<strlen(str);i++) //kullanıcıdan alınan metindeki toplam harf sayısını hesaplayan döngü
    {
        if(str[i]!=32 || (str[i]<='z' && str[i]>='a' ))
        {
           uzunluk++;
        }
    }
        //kullanıcıdan alınan metnin, verilmiş olan trigramlar ile karşılaştırılması
        for(k;k<strlen(str);k++){

                for(i=0;i<10;i++){
                    if(matrix_trigram_strings[i][0]==str[k]){
                        if(matrix_trigram_strings[i][1]==str[k+1]){
                            if(matrix_trigram_strings[i][2]==str[k+2]){
                                    sayac[i]+=1;
                            }
                        }
                                calculated_frequencies[i+10]=(100*sayac[i])/uzunluk; //trigramların frekanslarının hesaplanıp bir dizide tutulması
                    }
                }
        }
    for(int m=0;m<10;m++) //elde edilen her bir trigramın sayısının ve frekanslarının ekrana yazdırılması
        printf("Metinde %c%c%c Trigramindan %2.0f tane var ve metinde bulunma yuzdesi: %f \n",matrix_trigram_strings[m][0],matrix_trigram_strings[m][1],matrix_trigram_strings[m][2],sayac[m],calculated_frequencies[m+10]);
        //Burada da ayni sorun oldugu icin %s yerine %c%c%c kullandim
}

/* verilmiş olan frequencies_eng ve frequencies_germ frekans matrisleri ile
elde edilen calculated_frequencies frekans matrisi arasındaki uzaklık hesabını yapan fonksiyon */

void calculate_distances()
{

    float eng_frekans=0;

    float eng_uzaklik[20]={};

    float eng_uzaklik_toplam=0;

    float germ_frekans=0;

    float germ_uzaklik[20]={};

    float germ_uzaklik_toplam=0;

    for(int i=0;i<20;i++)
    {
        eng_frekans=abs(frequency_eng[i]-calculated_frequencies[i]);//verilmiş olan ingilizce frekans matrisi ile elde edilen ingilizce frekans matrisi arasındaki farkın mutlak değerinin hesaplanması
        eng_uzaklik[i]=eng_frekans;
        germ_frekans=abs(frequency_germ[i]-calculated_frequencies[i]);//verilmiş olan frekans matrisi ile elde edilen frekans matrisi arasındaki farkın mutlak değerinin hesaplanması
        germ_uzaklik[i]=germ_frekans;
        eng_uzaklik_toplam=eng_uzaklik_toplam+eng_uzaklik[i]; //elde edilen ingilizce matris farklarının toplanması
        germ_uzaklik_toplam=germ_uzaklik_toplam+germ_uzaklik[i];//elde edilen almanca matris farklarının toplanması
    }
    eng_distance=eng_uzaklik_toplam;
    germ_distance=germ_uzaklik_toplam;


  //elde edilen değerlerin distances dizisindeki indislere aktarılması
    distances[0]=eng_distance;

    distances[1]=germ_distance;
}

 //metnin yazıldığı dili tahmin eden fonksiyon
void detect_lang()
{
    if(distances[0]<distances[1])
    {
        printf("Metin Ingilizce dilindedir.");
    }
    else
    {
        printf("Metin Almanca dilindedir.");
    }

}
