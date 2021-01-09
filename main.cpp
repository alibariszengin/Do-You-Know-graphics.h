#include <winbgim.h> 

#include <stdio.h>

#include <stdlib.h>

#include <conio.h>

#include <math.h>

#include <time.h>

typedef struct {
	double x;
	double y;
}Nokta;

struct Cember { 
    Nokta C; 
    double R; 
}; 

void noktaCiz(Nokta mesafe,int ortala){
	putpixel(mesafe.x+ortala,mesafe.y+ortala,3);
}

void bsplaine(double t, const Nokta points[],int noktaSayisi,int mesafe)
{
	int i=0;
	
    Nokta points2[noktaSayisi-1];
    if(noktaSayisi==1){
    	
    	noktaCiz(points[0],mesafe); // Çizdirme kýsmý 
    	Nokta kopya=points[0],kopya2=points[0];
    	kopya.x=kopya.x-2;
    	noktaCiz(kopya,mesafe);
	}
	else{
		
		noktaSayisi=noktaSayisi-1;
		for(i=0;i<noktaSayisi;i++){
    		points2[i]=points[i];	// 1 eksiði sayida noktayi points 2 ye atama kismi	
		}
    	for ( i = 0; i < noktaSayisi ; i++){
    		
    		points2[i].x = (points[i+1].x)*t + (points[i].x)*(1.0-t);// agýrlýk ortalamasý bulma
    		points2[i].y =(points[i+1].y)*t + (points[i].y)*(1.0-t);
    	}
    	
   		bsplaine(t, points2, noktaSayisi,mesafe); // recursive
	}	    
}
double uzaklikFarki(Nokta ilkNokta,Nokta ikinciNokta) 
{ 
    return sqrt(pow(ilkNokta.x - ikinciNokta.x, 2) + pow(ilkNokta.y - ikinciNokta.y, 2)); 
}

Nokta ikiNoktaCember(Nokta ilkNokta, Nokta ikinciNokta ) { 	

	Nokta C;
 
    C.x= (ilkNokta.x + ikinciNokta.x)/2.0; 
    
    C.y=(ilkNokta.y + ikinciNokta.y)/2.0;

    return C; 
} 


bool min_cember(Cember c, Nokta P[],int NoktaSayisi) 
{ 
    int i=0;
    bool icinde=1;
	double uzaklik;
	
    for (i=0;i<NoktaSayisi;i++){
    	
    	uzaklik=uzaklikFarki(c.C, P[i]);
    	
    	if (uzaklik > c.R){
        	icinde=0; 
		} 
	}
	
    return icinde; 
} 
double cemberMerkeziX(double koordBx, double koordBy,double koordCx, double koordCy){
	
	double koordKare_B,koordKare_C,koord_Mix;
	
	koordKare_C = koordCx * koordCx + koordCy * koordCy; 
	
	koord_Mix = koordBx * koordCy - koordBy * koordCx; 
	
    koordKare_B = koordBx * koordBx + koordBy * koordBy; 
    
   
    
    return ((koordCy * koordKare_B - koordBy * koordKare_C) / (2 * koord_Mix)); 
} 
double cemberMerkeziY(double koordBx, double koordBy,double koordCx, double koordCy){ 

    double koordKare_B,koordKare_C,koord_Mix;
	
	koordKare_C = koordCx * koordCx + koordCy * koordCy; 
	
	koord_Mix = koordBx * koordCy - koordBy * koordCx; 
	
    koordKare_B = koordBx * koordBx + koordBy * koordBy; 
    
    return ((koordBx * koordKare_C - koordCx * koordKare_B) / (2 * koord_Mix)) ; 
} 
  
  
Nokta ucNoktaCember(Nokta A,Nokta B,Nokta C) 
{ 
    Nokta merkez;
    
	merkez.x = cemberMerkeziX(B.x - A.x, B.y - A.y,C.x - A.x, C.y - A.y);
	 
	merkez.y=cemberMerkeziY(B.x - A.x, B.y - A.y,C.x - A.x, C.y - A.y);
	
    merkez.x += A.x; 
    merkez.y += A.y;
    
    return  merkez ; 
}

  

int main(){
	
	int i,j,noktaSayisi,index=0,randx=0,randy=0;

	double temp1=0,mesafe=300;

	
	
	int aralik=30; // Rastgele sayi alirken degerlerin negatif- poztifif / -30/+30 gibi ayarlanmasý
	
	
	printf("Girilecek koordinat nokta sayisini giriniz:");
	scanf("%d",&noktaSayisi);
	Nokta points[noktaSayisi];
	srand(time(0));
	
	FILE *fp =fopen("program.txt", "w+");
	// Dosyaya random sayýlar yazdýrmak adýna
	for(i=0;i<noktaSayisi;i++){
		
		randx=i*10;
		randy=rand()%(aralik*2)-aralik;
		
        fprintf(fp, " %d %d ", randx,randy);    
	}
	fclose(fp);
	
	// Istenilen koordinatlar ile denemek adýna.. -->
	
	/*for(i=0;i<noktaSayisi;i++){
		printf("X ve Y koordinatlarini giriniz");
		scanf("%d %d",&randx,&randy);

        fprintf(fp, " %d %d ", randx,randy);    
	}
	fclose(fp);
	*/

	
	fopen("program.txt", "r");
	
	initwindow( mesafe*3 , mesafe*2 );
	
	setcolor(COLOR(0,0,200));

	float ciz_cember;
	
	for(i=0;i<noktaSayisi;i++){

        fscanf(fp, "%lf", &points[i].x);
        fscanf(fp, "%lf", &points[i].y);
        
		points[i].y=-points[i].y;
		
		circle(mesafe+(int)(points[i].x),mesafe+(int)(points[i].y),2); // pixel olan noktalarý daire olarak buyultmek ýcýn
		
		setcolor(COLOR(200,200,150));
		
		for(ciz_cember=2;ciz_cember>0;ciz_cember-=0.01){ // noktalarýn daire hallerinin içini doldurmak ýcýn 
			
			circle(mesafe+int(points[i].x),mesafe+int(points[i].y),ciz_cember);
		}

	}
	setcolor(COLOR(0,0,200));
	
	fclose(fp);
	
	line(mesafe/2, mesafe, mesafe*3/2,mesafe); // X koordinat düzlemi
	
	line(mesafe, mesafe/2, mesafe,mesafe*3/2); // Y koordinat düzlemi
	
	Cember Middle,tmp;
	
	Middle.R=mesafe*100;
	
	Middle.C.x=mesafe;
	Middle.C.y=mesafe;
	
	tmp.C.x=0;
	tmp.C.y=0;
	tmp.R=0;

	

	// 2 nokta ile kesiþen cember
	for ( i = 0; i < noktaSayisi; i++) {  
        for (j = i + 1; j < noktaSayisi; j++) { 
  
 
            tmp.C = ikiNoktaCember(points[i], points[j]); 
  			tmp.R = uzaklikFarki(points[i], points[j])/2.0 ;
  			//printf("x: %lf y: %lf R:%lf \n ",tmp.C.x,tmp.C.y,tmp.R);

            if (tmp.R <= Middle.R && min_cember(tmp, points,noktaSayisi)){
            	Middle = tmp;
            	index=j;
            
			}        
        } 
    }

	printf("---------------------#######################-------------------------- \n");
	
	// 3 nokta ile kesisen çember
	for ( i = 0; i < noktaSayisi; i++) { 
        for ( j = i + 1; j < noktaSayisi; j++) { 
            for (int k = j + 1; k < noktaSayisi; k++) { 
                
				tmp.C = ucNoktaCember(points[i], points[j], points[k]); 
  				tmp.R=uzaklikFarki(tmp.C, points[i]);
  				//printf("x: %lf y: %lf R:%lf \n ",tmp.C.x,tmp.C.y,tmp.R);

                if (tmp.R <= Middle.R && min_cember(tmp, points,noktaSayisi)){
                	Middle = tmp; 
                	index=j;
				} 
                    
            } 
        } 
    } 


	printf("Middle Point X => %lf and Y => %lf",Middle.C.x,Middle.C.y);
	
	printf("Cemberin Yaricapi : %.2lf " , Middle.R);


	circle(Middle.C.x+mesafe,Middle.C.y+mesafe,Middle.R); 
	
	setcolor(COLOR(250,200,10)); // renk deðiþ
	
	line(Middle.C.x+mesafe, Middle.C.y + mesafe,mesafe+points[index].x, mesafe+points[index].y); // çember üstü olan bir noktaya yarýçapýmýzý çizmek için
	//Oncelikle orta noktanýn koordinatlarý sonrasýnda ise çember uzerý noktanýn koordinatlarýný girdik
	
	setcolor(COLOR(250,0,200)); // renk deðiþ
	
	putpixel(Middle.C.x+mesafe,Middle.C.y+mesafe,10); // Merkez noktanýn pixeli
	
	for(ciz_cember=3;ciz_cember>0;ciz_cember-=0.01){ // Merkez noktanýn daire hallerinin içini doldurmak ýcýn 
			
		circle(Middle.C.x+mesafe,Middle.C.y+mesafe,ciz_cember);
	}
	
	setcolor(COLOR(0,0,200));
	
	double iter;
	
   	for ( iter = 0; iter < 101.0; ++iter){
		bsplaine(iter / 100.0, points,noktaSayisi,mesafe);
	}
	

	while( !kbhit() ); 

	closegraph();  

	getch();

	return( 0 );

}
