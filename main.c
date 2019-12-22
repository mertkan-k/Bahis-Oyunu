#include "main.h"

main() {
	srand(time(NULL)); setlocale(LC_ALL, "Turkish");
	int ran; int i; int j; int myMoney = randomRange(startingMoney[0], startingMoney[1]); char komut[50]; double puanList[__CAR_COUNT]; bool endgame = false; int komutsayisi = 0; int oyunsayisi = 0; int tursayisi = 1;

	printSyntax();
	
	while (0<myMoney && myMoney<finishMoney){
		system("color a");
		// sleep(1);
		// system("CLS");
		

		for (i=0; i<__CAR_COUNT; i++){
			puanList[i]=0;
			while(puanList[i]<1 || 15<puanList[i]){
				puanList[i] = 0;
				for ( j=0; j<10; j++ ){
					ran = randomizer(true);
					randoms[i][j] = ran;
					puanList[i] += ran;
				}
			}
		}

#ifdef __ENABLE_TEST_MODE
		printf("X Degerleri:: ");
		
		
		for (i=0; i<10; i++){
			printf("%d ", randoms[0][i]);
		}
		printf(" ::: X Puani: %f\n", puanList[0]);
		
		printf("Y Degerleri:: ");
		
		
		for (i=0; i<10; i++){
			printf("%d ", randoms[1][i]);
		}
		printf(" ::: Y Puani: %f\n", puanList[1]);
#endif
		
		double oranTable[2];
		oranTable[0]=(puanList[1]/puanList[0])+1;
		oranTable[0]=precisioner(oranTable[0], 2);//Precissing X
		oranTable[1]=(puanList[0]/puanList[1])+1;
		oranTable[1]=precisioner(oranTable[1], 2);//Precissing Y
		
		//Controlling Values
		while ( oranTable[0] == oranTable[1] ){// (5-5 -> 5-5.5 || 4-4 -> 4-4.4 || 3-3 -> 5-5.5 ||  6-6 -> 5-5.5)
			// if ( oranTable[0]>=4.5 ) { oranTable[0]-=(rand()%21/10); oranTable[1]-=(rand()%21/10); }
			if ( oranTable[0]>=4.5 ){
				if ( rand()%2==1 ) { oranTable[1]-=(rand()%31/10); }
				else { oranTable[0]-=(rand()%31/10); }
			}
			else{
				if ( rand()%2==1 ) { oranTable[0]+=(rand()%11/10); }
				else { oranTable[1]+=(rand()%11/10); }
			}
		}
		//End Of Controlling Values
		
		printf("\n");
		printf("Paraniz: %d$\n", myMoney);
		printf("%d. tur:\n",tursayisi++);
		for (i=0; i<__CAR_COUNT; i++){
			printf("%c Arabasinin Orani: %.2f\n", carNames[i], oranTable[i]);
		}
		
		int raceHe = randomRange(raceLenghts[0], raceLenghts[1]);
		printf("Yaris Uzunlugu: %d\n\n", raceHe);
		
		while(true){
			komutsayisi++;
			printf("Komut bekleniyor.. (Komut listesini gormek icin \'yardim\' yaziniz.)\n");
			printf("Komutlar, buyuk/kucuk harf duyarlidir.\n");
			gets(komut);
			// scanf("%s",&komut);
#ifdef __ENABLE_TEST_MODE
			printf("komut:::: %s\n", komut);
#endif
			if ( strcmp(komut, "yardim")==0 ) {printHelp();}
			else if ( strcmp(komut, "araba")==0 ){
				printf("Arabanin ismini giriniz.\n");
				char arabaIsmi[1]; int arabaSec=-1;
				//scanf("%s",&arabaIsmi);
				gets(arabaIsmi);
				//Find car Name in list
				for (i=0; i<__CAR_COUNT; i++){
					if ( carNames[i] == *arabaIsmi ){//Normalde pointer pek bilmiyorum ama verdiði warninden yola çýkarak doðrusunu buldum.
						arabaSec=i+1;
						break;
					}
				}
				if ( arabaSec<0 || arabaSec>__CAR_COUNT+1 ){
					printf("Gecersiz araba ismi!\n");
				}
				else
					yatirilanAraba=arabaSec;
			}
			else if ( strcmp(komut, "para")==0 ){
				printf("Yatirilacak para miktarini giriniz.(Max: %d$)\n", myMoney);
				int yatirPara; char yatirParaChr[10];
				// scanf("%d", &yatirPara);
				gets(yatirParaChr);
				yatirPara = my_atoi(yatirParaChr);
				if ( yatirPara<=myMoney && yatirPara>=0 ){
					yatirilanPara=yatirPara;
				}
				else
					printf("Gecersiz para girisi!\n");
			}
			else if ( strcmp(komut, "baslat")==0 ){
				break;
			}
			else if ( strcmp(komut, "bilgiler")==0 ){
				printf("Paraniz: %d$\n", myMoney);
				printf("X Oran: %.2f\n", oranTable[0]);
				printf("Y Oran: %.2f\n", oranTable[1]);
				printf("Oyun Uzunlugu: %d\n\n", raceHe);
			}
			else if ( strcmp(komut, "farketmez")==0 ){
				printf("O zaman bi farkez yapalim :)\n");
			}
			else if ( strcmp(komut, "bitir")==0 ){
				endgame = true;
				break;
			}
			else if ( strcmp(komut, "oyunmantigi")==0 ) {printSyntax();}
			else {printf("Gecersiz komut!\n");}
			
			printYatirimDurum();
		}
		
		if (endgame)
			break;
		
		if ( yatirilanPara<=0 || yatirilanAraba<1 ){
			system("CLS");
			printf("Bahis yapilmadigi icin tur atlandi.");
			sleep(2);
			continue;
		}
		
		oyunsayisi++;
		myMoney -= yatirilanPara;
		int winner = startGame(raceHe);
		printf("%d\n", winner);
		if ( winner == yatirilanAraba ){
			printf("Kazandiniz!\n");
			myMoney += (yatirilanPara*oranTable[yatirilanAraba-1]);
		}
		else if (winner == 0){
			printf("Berabere!\n");
		}
		else {
			printf("Kaybettiniz!\n");
		}
		// printf("Paraniz: %d\n", myMoney);
		// printf("-----------------------\n");
		// printf("Puan y: %d\n", localizations[0]);
	
	}//while
	system("CLS");
	system("color d");
	printf("Oyun bitti. Istatistikler:\n");
	printf("Girilen toplam komut sayisi: %d\n", komutsayisi);
	printf("Oynanan toplam oyun sayisi: %d\n", oyunsayisi);
	printf("Bitis parasi: %d$\n", myMoney);
	
}//main

void printHelp(){
	system("CLS");
	printf("Komut Listesi::\n");
	printf("\t\'oyunmantigi\' - Oyun hakkinda bilgilendirme almanizi saglar.\n");
	printf("\t\'yardim\' - Bu ekranin acilmasini saglar.\n");
	printf("\t\'para\' - Para girisi yapmanizi saglar.\n");
	printf("\t\'araba\' - Yatirmak istediginiz arabayi belirlemenizi saglar.\n");
	printf("\t\'baslat\' - Oyunu baslatmanizi saglar.\n");
	printf("\t\'bilgiler\' - Tur bilgilerini gosterir.\n");
	printf("\t\'farketmez\' - :)\n");
	// printf("\t\'araba\' - \n");
}
void printSyntax(){
	system("CLS");
	system("color e");
	printf("Oyun mantigi: Temel olarak bahis mantigi uzerine yazilmistir.\nHer tur size iki adet araba ve bunlara ait oranlar verilir.\nSiz de \'para\' ve \'araba\' komutlarini kullanarak seciminizi belirlersiniz.\nDaha sonra ise \'baslat\' komutunu kullanarak turu baslatýrsýnýz.\nEðer isterseniz herhangi bir secim yapmayarak turu es gecebilirsiniz.\nEger seciminiz tutar ise oran kadar para kazanirsiniz ve oyun bu þekilde devam eder.\ Belirli bir miktar paraya sahip olunca ve ya iflas edince oyun otomatik oalrak biter ve size istatistikler verilir.\nOyuna baþlangýç paranýz belirli miktarlar arasýnda random olarak deðiþmektedir.\nÝyi oyunlar..\n\nDevam etmek içinn \'ENTER\' tuþunu kullanýn..");
	getch();
	system("CLS");
}
void printYatirimDurum(){
	printf("Yatirilan Araba-Para: %c-%d\n", (yatirilanAraba<=__CAR_COUNT && yatirilanAraba>0) ? carNames[yatirilanAraba-1] : '*', yatirilanPara);
}

int startGame(int finish_num)
{
	system("color c");
	
	int localizations[__CAR_COUNT]; int random = 0; int i; int j;
	
	while (true){
		
		sleep(1);
		system("CLS");
		
		printf("Seciminiz: %c, Yatirilan Miktar: %d$\n", carNames[yatirilanAraba-1], yatirilanPara);
		printf("Yaris Uzunlugu: %dm\n", finish_num);
		for (i=0; i<finish_num; i++)
			printf("-");
		printf("\n");
		random = 1+rand()%10;
#ifdef __ENABLE_TEST_MODE
		printf("RANDOM KEY: %d\n", random);
#endif
		
		for (j=0; j<__CAR_COUNT; j++){
			localizations[j]+=randoms[j][random];
			if (localizations[j]<0)
				localizations[j] = 0;
			for (i=0; i<localizations[j]; i++)
				printf(" ");
			printf("%c", carNames[j]);
			
			for (i=0; i<finish_num - (localizations[j]+1); i++)
				printf(" ");
			printf("|%dm\n", localizations[j]);
		}
		
		for (i=0; i<finish_num; i++)
			printf("-");
		printf("\n");
		
		{//Calculating for Winner
			int winner=__CAR_COUNT+1;
			
			for(i=0; i<__CAR_COUNT; i++){
				if ( localizations[i]>=finish_num && 
				localizations[i]>=localizations[winner] ){
					winner = i;
				}
			}
			
			if ( winner != __CAR_COUNT+1 )
				return winner+1;
			
		}//End Of Calculating for Winner
		
	}//while
	
}

int randomizer(bool negative){
	int numb = rand()%11;
	int ispos = rand()%3;
	if ( numb>6 && ispos!=0 )
		numb-=2;
	if (negative && ispos==0)
		numb=-numb;
	return numb;
}

double precisioner(double numb, int pre){ return floor(numb*pow(10, pre))/pow(10, pre); }//10.123123 to 10.120000

int randomRange(int min, int max){ return min+(rand()%(max-min)); }

int my_atoi(const char* snum)//https://stackoverflow.com/questions/7021725/how-to-convert-a-string-to-integer-in-c
{
	int idx, strIdx = 0, accum = 0, numIsNeg = 0;
	const unsigned int NUMLEN = (int)strlen(snum);

	/* Check if negative number and flag it. */
	if(snum[0] == 0x2d)
		numIsNeg = 1;

	for(idx = NUMLEN - 1; idx >= 0; idx--)
	{
		/* Only process numbers from 0 through 9. */
		if(snum[strIdx] >= 0x30 && snum[strIdx] <= 0x39)
			accum += (snum[strIdx] - 0x30) * pow(10, idx);

		strIdx++;
	}

	/* Check flag to see if originally passed -ve number and convert result if so. */
	if(!numIsNeg)
		return accum;
	else
		return accum * -1;
}
