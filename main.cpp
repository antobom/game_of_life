#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
#include <fstream>
#include <string>
#include <sstream>
#define DIM 100

//#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


void init_tab(vector<vector<int>>& tab)//(DIM, vector<int>(DIM, 0)))
{
    //int tab[DIM][DIM];
    ifstream fichier("data.csv");
    if (!fichier)
    {
        cout << "fichier non trouvé" << endl;
    }

    int n_ligne = 0;
    string ligne;
    while (getline(fichier, ligne))
    {
        for (int i = 0; i < DIM; i++)
        {
            tab[n_ligne][i] = ligne[i * 2] - '0';
        }
        n_ligne++;
        if (n_ligne == DIM)
        {
            break;
        }
    }
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }
}

void draw_a_grid(Mat &img)
{
    int h = img.size().height;
    int w = img.size().width;

    for(int i =0;i<h;i=i+10)
    {
        line(img,Point(0,i),Point(w,i),Scalar(255,255,255),1);
    }
    for(int i =0;i<w;i=i+10)
    {
        line(img,Point(i,0),Point(i,h),Scalar(255,255,255),1);
    }
}

void fill_grid(Mat &img,vector<vector<int>> tab)
{
    for(int i =0;i<DIM;i++)
    {
        for(int j=0;j<DIM;j++)
        {
            if(tab[i][j] ==1)
            {
                rectangle(img,Point(j*10,i*10),Point(j*10+10,i*10+10),Scalar(255,255,255),-1);
            }
            else
            {
                rectangle(img,Point(j*10,i*10),Point(j*10+10,i*10+10),Scalar(0,0,0),-1);
            }
        }
    }
}
void vie(vector<vector<int>> &tab)
{
    vector<vector<int>> tab_mem(tab);
    int compteur;
    for(int i=0;i<DIM;i++)
    {
        for(int j=0;j<DIM;j++)
        {
            compteur=0;
            for(int x=-1;x<2;x++)
            {
                for(int y=-1;y<2;y++)
                {
                    if(i+x>0 && j+y>0 && i+x<DIM && y+j<DIM)//pour ne pas sortir du tableau
                    {
                        if(tab_mem[x+i][y+j]==1)//cellule vivante de trouvée
                        {
                            compteur++;
                        }                        
                    }
                }

            }
            if(tab_mem[i][j]==0&&compteur==3)//cellule morte + 3 vivante autour
            {
                tab[i][j]=1;
            }
            if(tab_mem[i][j]==1&&(compteur<3||compteur>4))//cellule vivante 
            {
                tab[i][j]=0;//qui meurre 
            }
        }
    }
}


int main()
{
    Mat image = Mat::zeros(DIM*10,DIM*10,CV_8UC1);
    vector<vector<int>> tab(DIM,vector<int> (DIM,0));
    namedWindow("image",WINDOW_AUTOSIZE); 
  /*  tab[3][3]=1;
    tab[3][4]=1;
    tab[3][5]=1;
    tab[4][5] = 1;
    tab[4][7] = 1;
    tab[6][5] = 1;*/
    //for (int i = 0; i < DIM; i++)
    //{
    //    for (int j = 0; j < DIM; j++)
    //    {
    //        tab[i][j] = rand() % 2;
    //        //cout << tab[i][j] << endl;
    //    }
    //}
    init_tab(tab);

    fill_grid(image,tab);

    draw_a_grid(image);;
    imshow("image",image);
    waitKey(0);


    while(1)
    {

        vie(tab);
        fill_grid(image,tab);

        draw_a_grid(image);

        imshow("image",image);
        if(waitKey(1)==27)
        {
            break;
        }
    }
}